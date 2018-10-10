#include "sellers_package/seller.h"
#include "time_sync/time.h"
#include <unistd.h>
int NUMBER_OF_CUSTOMERS_PER_QUEUE=0;
bool MIN_BY_MIN_SIMULATION = false;
int seat::soldSeats = 0 ;
seller* sellers[10];
void* start_selling(void* arg){
    seller* s = (seller*)arg;
    sleep(s->pID);
    cout <<s->seller_name<<" Starting. (Thread"<<to_string(s->pID)<<")"<<endl;
    s->sell_tickets();
    pthread_exit(nullptr);
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
void print_customers_who_arrived_now(){
    string s = "Customers arrived: \n";
    bool print = false;
    for(int i = 0 ; i<10;i++){
        for(int j =0;j<NUMBER_OF_CUSTOMERS_PER_QUEUE;j++)
            if(sellers[i]->cArr[j].aT==time_counter){
                s+= sellers[i]->cArr[j].name + " at " + sellers[i]->seller_name + "\n";
                print = true;
            }
    }
    if(print)
        cout << s;  
}
int main(int argc,char** argv) {
        if(argc==1)
            exit(0);
        stringstream sstream (argv[1]);
        sstream >> NUMBER_OF_CUSTOMERS_PER_QUEUE;
        if(argc==3){
            if(string(argv[2])=="mbm")
                MIN_BY_MIN_SIMULATION=true;
        }


    for(int i =0;i<10;i++)
        for(int j =0;j<10;j++)
            seat_chart[i][j].setIJ(i,j);
    pthread_t threads [10];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
    
    for(int i = 0 ; i < 10 ; i++){
        if(i<1){
        string name = "H"+to_string(i+1);
        sellers[i] = new high_seller(name,i);
                sellers[i]->cArr = new customer[NUMBER_OF_CUSTOMERS_PER_QUEUE];
                sellers[i]->fill_cQ(NUMBER_OF_CUSTOMERS_PER_QUEUE);
        }
        else if (i<4){
            string name = "M"+to_string(i);
            sellers[i] = new mid_seller(name,i);
            sellers[i]->cArr = new customer[NUMBER_OF_CUSTOMERS_PER_QUEUE];
            sellers[i]->fill_cQ(NUMBER_OF_CUSTOMERS_PER_QUEUE);
        }
        else {
            string name = "L"+to_string(i-3);
            sellers[i]=new low_seller(name,i);
            sellers[i]->cArr = new customer[NUMBER_OF_CUSTOMERS_PER_QUEUE];
            sellers[i]->fill_cQ(NUMBER_OF_CUSTOMERS_PER_QUEUE);
            
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
                not_ready_cnt++;
            }
            else if (are_all_sellers_ready_to_start()){
                pthread_cond_broadcast(&start_cond);
                pthread_mutex_unlock(&start_mutex);
                break;
            }
            else{
                not_ready_cnt++;
                pthread_mutex_unlock(&start_mutex);
                sleep(1);
            }
        }
        pthread_mutex_lock(&time_mutex);
        pthread_cond_wait(&time_cond,&time_mutex);  // WAITING 
        
        string current_time_string = to_string(time_counter);
        if(time_counter<10)
            current_time_string="0"+current_time_string;
        cout<<"00:"<<current_time_string<<endl;
        print_customers_who_arrived_now();
        for(int i=0 ; i<10 ;i++){
            cout<<(sellers[i]->seller_name)<<": "<<sellers[i]->event_log[time_counter]<<endl;
            
        }
        print_seats();
                cout<<endl;
                time_counter++;
         if(done)
             has_work = false;        
      pthread_mutex_unlock(&time_mutex);
      if(MIN_BY_MIN_SIMULATION)
            sleep(1);
       
    }
//    pthread_join(thread,NULL);
    for(int i = 0 ; i <10 ; i++){
        pthread_join(threads[i],NULL);
    }

 cout << endl;  
 cout<<"Number of Customers Served:\n";
 cout << "H: " << to_string(high_customers_served_counter)<<endl;
 cout << "M: " << to_string(mid_customers_served_counter)<<endl;
 cout << "L: " << to_string(low_customers_served_counter)<<endl;
 cout<<"Number of Customers not Served:\n";
 cout << "H: " << to_string((1*NUMBER_OF_CUSTOMERS_PER_QUEUE)-high_customers_served_counter)<<endl;
 cout << "M: " << to_string(3*(NUMBER_OF_CUSTOMERS_PER_QUEUE)-mid_customers_served_counter)<<endl;
 cout << "L: " << to_string(6*(NUMBER_OF_CUSTOMERS_PER_QUEUE)-low_customers_served_counter)<<endl;
 
}