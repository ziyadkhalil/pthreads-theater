
#include "seller.h"
#include "time.h"
#include <unistd.h>

int seat::soldSeats = 0 ;
// create a global 2d array of seats
 //That's enough and no need for gen_seatchart() as I made the default values to be sold = false and sold_by = 0;
void* start_selling(void* arg){
    seller* s = (seller*)arg;
    s->sell_tickets(arg);
    int** x;
    sleep(s->pID);
    cout<<"exiting thread" + to_string(s->pID)<<endl;
    pthread_exit(x);
}

int main() {
    for(int i =0;i<10;i++)
        for(int j =0;j<10;j++)
            seat_chart[i][j].setIJ(i,j);
    pthread_t threads [10];
    seller* sellers[10];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
    for(int i = 0 ; i < 10 ; i++){
        string name = "M"+to_string(i);
//        cout<<name<<"\n";
        sellers[i] = new mid_seller(name,i);
        pthread_create(&threads[i],&attr,start_selling,sellers[i]);
    }
    sleep(2);
    cout<<"Minute: 0\n";
    for(int i = 1 ;i<11; i ++){
    pthread_mutex_lock(&time_mutex);
    pthread_cond_broadcast(&start_cond); //ALL START
    pthread_cond_wait(&time_cond,&time_mutex);  // WAITING 
    cout<<"Minute: " + to_string(i)<<endl;
    time_counter++;
    cout<<time_counter<<endl;
    pthread_mutex_unlock(&time_mutex);
    }
    cout<<"alo";
    for(int i = 0 ; i <10 ; i++){
        pthread_join(threads[i],NULL);
    }
}

