#include "../seller.h"
#include <unistd.h>


 seat* mSPD = &seat_chart[5][0];
 seat* mSPU = &seat_chart[4][9];
 seat** mSP = &mSPU; //POINTER TO A POINTER BECAUSE LIFE IS A BITCH  //TODO: REMIND ME TO EXPLAIN 
 pthread_mutex_t mSPMutex;
 bool is_mid_up = true;
 int toggle_counter = 0;
 

mid_seller::mid_seller(string seller_name,int pID):seller(M_SELLER,seller_name,pID){}

void*  mid_seller::sell_tickets(void* arg){
    for(int i  = 0 ;i<10;i++){
       pthread_mutex_lock(&start_mutex);

       pthread_cond_wait(&start_cond,&start_mutex); 
       pthread_mutex_unlock(&start_mutex);
       pthread_mutex_lock(&mSPMutex);   //LOCK POINTER SO NO ANOTHER MID SELLER CAN INCREMENT IT OR DEREFERNCE A WRONG SEAT! 
       seat s = **mSP;
       if(is_mid_up)
           (*mSP)--;
       else
           (*mSP)++;
       toggle_counter++;
       if(toggle_counter==10)
           toggle_mid_pointer();
       s.sell_me(seller_name);

    
               this->xx++;
        pthread_mutex_unlock(&mSPMutex);
        pthread_mutex_lock(&time_mutex);
        done_working_for_this_minute[this->pID] = true;
        bool all_done = are_all_sellers_done();
        pthread_mutex_unlock(&time_mutex);
        if(all_done) // IF all threads are done for this minute, wake up main
            pthread_cond_signal(&time_cond); //WAKE UP MAIN TO INCREMENT TIME
        

        //TODO: CODE TO MAKE SELLER WAIT FOR GENERATED RANDOM TIME
    }
    }
    
 void mid_seller::toggle_mid_pointer(){
     toggle_counter = 0; //Toggles between up and down mid_pointers 
     if(is_mid_up){
         mSP = &mSPD;
         cout<<"Toggled! now going down!\n";
         is_mid_up = false;
     }
     else{
         mSP = &mSPU;
         cout<<"Toggled! now going up!\n";
         is_mid_up = true;
     }
 }   
    