
#include "../seller.h"
seat seat_chart[10][10];
bool done_working_for_this_minute[10];
bool done_working_for_good[10];
bool done = false;
seller::seller(int s_type,string seller_name,int pID){
    this->s_type=s_type;
    this->seller_name = seller_name;
    this->pID = pID;
    this->seller_state=WAITING;
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
      srand(seed);
      customer tmp[N];
        
        for (int i = 0; i<N; i++){
            tmp[i] = customer();
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
       pthread_mutex_lock(&start_mutex);
       pthread_cond_wait(&start_cond,&start_mutex); 
       pthread_mutex_unlock(&start_mutex);
        if(this->seller_state!=SERVING){
            if(!this->cQ.empty())
             if((this->cQ.front().aT)<=(this->current_minute)){
               int feed_back= serve(cQ.front());
                
            }
            
        }
        if(this->seller_state==SERVING){
            this->remaining_serving_time--;
//            cout<< to_string(this->pID)+ ": SERVING....";
            if(remaining_serving_time==0){
                this->seller_state=WAITING;
                current_seat->sell_me(create_ID_for_seat());
                this->cQ.pop();
                if(this->cQ.empty()){
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
//        sleep(this->pID);
        if(all_done) {// IF all threads are done for this minute, wake up main
            pthread_cond_signal(&time_cond);} //WAKE UP MAIN TO INCREMENT TIME
//        cout<<"REEEEEEEM";

    }
//     cout<<"yl3n den omk\n";
}
