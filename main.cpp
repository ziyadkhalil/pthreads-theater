
#include "seller.h"
#include "time.h"
#include <unistd.h>

int seat::soldSeats = 0 ;
// create a global 2d array of seats
 //That's enough and no need for gen_seatchart() as I made the default values to be sold = false and sold_by = 0;
void* start_selling(void* arg){
    seller* s = (seller*)arg;
    s->sell_tickets();
//    sleep(s->pID);
    int x =3 ;
    pthread_exit(&x);
}
void print_seats(){
    for (int i = 0; i<10; i++) {
        for (int j = 0; j<10; j++) {
            cout << "[" << setfill(' ') << setw(4) << seat_chart[i][j].sold_by << "] ";
        }
        cout << endl;
    }
}
bool are_all_sellers_ready_to_start(){
    if((ready_to_start[0]||done_working_for_good[0])&&
            (ready_to_start[1]||done_working_for_good[1])&&
            (ready_to_start[2]||done_working_for_good[2])&&
            (ready_to_start[3]||done_working_for_good[3])&&
            (ready_to_start[4]||done_working_for_good[4])&&
            (ready_to_start[5]||done_working_for_good[5])&&
            (ready_to_start[6]||done_working_for_good[6])&&
            (ready_to_start[7]||done_working_for_good[7])&&
            (ready_to_start[8]||done_working_for_good[8])&&
            (ready_to_start[9]||done_working_for_good[9])){
        for(int i = 0 ; i < 10 ; i ++)
            ready_to_start[i]=0;
        return true;
    }
    return false;
}
int main() {
//    init_mutexes();
    
    for(int i =0;i<10;i++)
        for(int j =0;j<10;j++)
            seat_chart[i][j].setIJ(i,j);
    pthread_t threads [10];
    seller* sellers[10];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
    for(int i = 0 ; i < 10 ; i++){
        if(i<1){
        string name = "H"+to_string(i+1);
        sellers[i] = new high_seller(name,i);
                sellers[i]->fill_cQ(20);
        }
        else if (i<4){
            string name = "M"+to_string(i);
            sellers[i] = new mid_seller(name,i);
            sellers[i]->fill_cQ(10);
        }
        else {
            string name = "L"+to_string(i-3);
            sellers[i]=new low_seller(name,i);
            sellers[i]->fill_cQ(10);
            
        }
       
        pthread_create(&threads[i],&attr,start_selling,sellers[i]);
    }
    int not_ready_cnt=0;
    sleep(2);
    bool has_work=true;
    while(has_work){
        while(true){
            if(pthread_mutex_trylock(&start_mutex)!=0){
                sleep(1);
                cout<<"not ready\n";
                not_ready_cnt++;
            }
            else if (are_all_sellers_ready_to_start()){
                cout<<"ready\n";
                pthread_cond_broadcast(&start_cond);
                pthread_mutex_unlock(&start_mutex);
                break;
            }
            else{
                not_ready_cnt++;
                cout<<"not reeadyyy\n";
                pthread_mutex_unlock(&start_mutex);
                sleep(1);
            }
        }
        pthread_mutex_lock(&time_mutex);
        pthread_cond_wait(&time_cond,&time_mutex);  // WAITING 
        
        string current_time_string = to_string(time_counter);
        if(time_counter-1<10)
            current_time_string="0"+current_time_string;
        cout<<"00:"<<current_time_string<<endl;
        for(int i=0 ; i<10 ;i++){
            cout<<(sellers[i]->seller_name)<<": "<<sellers[i]->event_log[time_counter]<<endl;
            
        }
                cout<<endl;
                time_counter++;
         if(done)
             has_work = false;        
      pthread_mutex_unlock(&time_mutex);
//        sleep(1);
       
    }
//    pthread_join(thread,NULL);
    for(int i = 0 ; i <10 ; i++){
        pthread_join(threads[i],NULL);
    }
        cout<<"SEATS SOLD: "<<seat::soldSeats<<endl;
 print_seats();  
 cout<<not_ready_cnt<<endl;
}

