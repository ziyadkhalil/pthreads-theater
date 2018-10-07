
#include "../seller.h"
seat seat_chart[10][10];
bool done_working_for_this_minute[10];
bool done_working_for_good[10];
bool ready_to_start[10];
bool done = false;
bool seats_full = false;
pthread_mutex_t mutex;
pthread_mutex_t* mutex_p = &mutex;
seller::seller(int s_type,string seller_name,int pID){
    this->s_type=s_type;
    this->seller_name = seller_name;
    this->pID = pID;
    this->seller_state=WAITING;
    for(int i = 0; i< 70 ;i++){
        this->event_log[i] = "Closed.";
    }
}

void seller::print_ptrs(){
    cout <<endl;
    cout << "*hSPP: ";
    cout<< *hSPP << endl;
    cout << "*mSP: ";
    cout << *mSP << endl;
    cout << "mSPU: ";
    cout << mSPU << endl;
    cout << "mSPD: " ;
    cout << mSPD << endl;
    cout <<"*lSPP: ";
    cout << *lSPP << endl;
    cout <<endl;
}
int seller::fRanInt(int min , int max){return rand()%(max-min + 1) + min;}

int seller::gen_aT(){
    return fRanInt(0,59);
}
int seller::gen_serving_time(){
     if (this->s_type == H_SELLER)
            return fRanInt(1,2);
    else if(this->s_type == M_SELLER)
            return fRanInt(2,4);
        else
            return fRanInt(4,7);
}

void seller::fill_cQ(int N){
      srand(this->pID);
      customer tmp[N];
        
        for (int i = 0; i<N; i++){
            tmp[i] = customer();
            tmp[i].name = this->seller_name+"_"+to_string(i);
            tmp[i].set_aT(gen_aT());
            tmp[i].serving_time=gen_serving_time();
        }
        
        sort(tmp, tmp+N,
             [](customer const & p1, customer const & p2) -> bool
             { return p1.aT < p2.aT; } );
        
        for (int i = 0; i<N; i++){
            cQ.push(tmp[i]);
        }
    }

bool seller::are_all_sellers_done(){
    if((done_working_for_this_minute[0]||done_working_for_good[0])
            &&(done_working_for_this_minute[1]||done_working_for_good[1])
            &&(done_working_for_this_minute[2]||done_working_for_good[2])
            &&(done_working_for_this_minute[3]||done_working_for_good[3])
            &&(done_working_for_this_minute[4]||done_working_for_good[4])
            &&(done_working_for_this_minute[5]||done_working_for_good[5])
            &&(done_working_for_this_minute[6]||done_working_for_good[6])
            &&(done_working_for_this_minute[7]||done_working_for_good[7])
            &&(done_working_for_this_minute[8]||done_working_for_good[8])
            &&(done_working_for_this_minute[9]||done_working_for_good[9])){
                for(int i = 0; i < 10 ; i ++)
                     done_working_for_this_minute[i]=false;
        return true;
    }
    else
        return false;
}
bool seller::are_all_sellers_done_for_good(){
    if(done_working_for_good[0]&&done_working_for_good[1]&&done_working_for_good[2]&&
            done_working_for_good[3]&&done_working_for_good[4]&&done_working_for_good[5]&&
            done_working_for_good[6]&&done_working_for_good[7]&&done_working_for_good[8]&&
            done_working_for_good[9])
        return true;
    return false;
}

string seller::create_ID_for_seat(){
    if(seats_sold_counter<10)
        return this->seller_name+to_string(0)+to_string(seats_sold_counter);
    else
        return this->seller_name+to_string(seats_sold_counter);
        
}

 void seller::sell_tickets(){
    while(this->seller_state!=FINISHED){
//        sleep(1);
       pthread_mutex_lock(&start_mutex);
       ready_to_start[this->pID] = true;
       pthread_cond_wait(&start_cond,&start_mutex); 
       pthread_mutex_unlock(&start_mutex);

       
//       cout<<to_string(this->current_minute)<<" : "<<to_string(this->pID)<<endl;
        if(this->seller_state!=SERVING){
            if(!this->cQ.empty())
             if((this->cQ.front().aT)<=(this->current_minute)){
                serve(cQ.front());
                
            }
            
        }
       if(this->seller_state==WAITING){
           this->event_log[current_minute] = "Waiting for Customers...";
       }
        if(this->seller_state==SERVING){
            this->event_log[current_minute] = "Serving Customer " + cQ.front().name;
            if(cQ.front().serving_time==this->remaining_serving_time)
                this->event_log[current_minute] = "Started Serving Customer "+ cQ.front().name;
            this->remaining_serving_time--;
            if(remaining_serving_time==0){
                this->event_log[current_minute] = "Finished Serving Customer " + cQ.front().name+ 
                        " and Assigned him to Seat["+to_string(current_seat->i)+"]["+to_string(current_seat->j)
                        +"].";
                this->seller_state=WAITING;
                current_seat->sell_me(create_ID_for_seat());
                this->cQ.pop();
                if(this->cQ.empty()||current_minute>59){
                    if(this->event_log[current_minute].empty())
                        this->event_log[current_minute]="Finished working, Closing Window...";
                    else
                        this->event_log[current_minute]+=" Finished working, Closing Window...";
                    this->seller_state=FINISHED;
                    this->done_for_good=true;
                }
            }
        }
        pthread_mutex_lock(&time_mutex);
        this->current_minute=(time_counter+1); //assigns current_minute for the coming cycle (technically should be next_minute)  
        done_working_for_this_minute[this->pID] = true;
        bool all_done = are_all_sellers_done();
         if(this->done_for_good){
             done_working_for_good[this->pID] = true;
             if(are_all_sellers_done_for_good())
                 done=true;
        }
        pthread_mutex_unlock(&time_mutex);
        if(all_done) {// IF all threads are done for this minute, wake up main
            pthread_cond_signal(&time_cond);} //WAKE UP MAIN TO INCREMENT TIME

    }
//     cout<<"yl3n den omk\n";
}
