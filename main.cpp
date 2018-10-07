
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
        if(i<7){
        string name = "M"+to_string(i);
        sellers[i] = new mid_seller(name,i);
                sellers[i]->fill_cQ(12);
        }
        else if(i<10){
            string name = "H"+to_string(i);
            sellers[i]=new high_seller(name,i);
            sellers[i]->fill_cQ(5);
            
        }
       
        pthread_create(&threads[i],&attr,start_selling,sellers[i]);
    }
    
//    string name  = "M1";
//    seller* s = new mid_seller(name,0);
//    s->fill_cQ(100);
//    for(int i  = 0 ; i<s->cQ.size();i++){
//        customer c = s->cQ.front();
//        s->cQ.pop();
//        s->cQ.
//        cout << "Customer " << i << ": \nArrival Time: " << c.aT << "\n Serving Time: " << c.serving_time << endl;        
//    }
//    pthread_create(&thread,&attr,start_selling,s);
    sleep(2);
    cout<<"Minute: 0\n";
    bool has_work=true;
    while(has_work){
    pthread_mutex_lock(&time_mutex);
//    sleep(1);
    pthread_cond_broadcast(&start_cond); //ALL START
    pthread_cond_wait(&time_cond,&time_mutex);  // WAITING 
    if(done)
        has_work = false;
//    sleep(1);
    cout<<"Minute: " + to_string(time_counter)<<endl;
    time_counter++;
    pthread_mutex_unlock(&time_mutex);
    }
//    pthread_join(thread,NULL);
    for(int i = 0 ; i <10 ; i++){
        pthread_join(threads[i],NULL);
    }
        cout<<"SEATS SOLD: "<<seat::soldSeats<<endl;
 print_seats();  
}

