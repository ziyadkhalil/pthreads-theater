#include "seat.h"
using namespace std;
seat::seat(){
    this->sold_by=0;
    this->sold=false;
}
void seat::sell_me(string seller_name){
     this->sold = true;
//        this->sold_by = sID;
        cout<<"Seat["<<i<<"]["<<j<<"] is SOLD by "<<seller_name<<endl;
        pthread_mutex_lock(&sold_seats_mutex);   //Needs Lock here since soldSeats is shared with all freakin' seats
        soldSeats++;
        pthread_mutex_unlock(&sold_seats_mutex);

}
        void seat::setIJ(int i,int j){
            this->i=i;
            this->j=j;
        }