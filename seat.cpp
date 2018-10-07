#include "seat.h"
using namespace std;
pthread_mutex_t sold_seats_mutex;
seat::seat(){
    this->sold_by="-";
    this->sold=false;
}
void seat::sell_me(string seller_name){
     this->sold = true;
//        this->sold_by = sID;
     this->sold_by = seller_name;
        pthread_mutex_lock(&sold_seats_mutex);   //Needs Lock here since soldSeats is shared with all freakin' seats
        soldSeats++;
        pthread_mutex_unlock(&sold_seats_mutex);

}
        void seat::setIJ(int i,int j){
            this->i=i;
            this->j=j;
        }