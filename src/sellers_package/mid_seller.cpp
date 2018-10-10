#include "seller.h"
#include <unistd.h>


 seat* mSPD = &seat_chart[5][0];
 seat* mSPU = &seat_chart[4][9];
 seat** mSP = &mSPU; 
 pthread_mutex_t mSPMutex;
 pthread_mutex_t* m_mutex_ptr = &mSPMutex;
 bool is_mid_up = true;
 bool is_toggling = true;
 int toggle_counter = 0;
 pthread_mutex_t dbhm_mutex;
  pthread_mutex_t dbml_mutex;
  int distance_between_high_and_mid=50;
  int distance_between_mid_and_low=50;
   int mid_customers_served_counter=0;


 

mid_seller::mid_seller(string seller_name,int pID):seller(M_SELLER,seller_name,pID){}


int mid_seller::serve(customer c)  {
         pthread_mutex_lock(mutex_p);   //LOCK POINTER SO NO ANOTHER MID SELLER CAN INCREMENT IT OR DEREFERNCE A WRONG SEAT! 
         seat* s=*mSP;  
         if(seats_full){
                this->seller_state=FINISHED;
                this->done_for_good=true;
                 pthread_mutex_unlock(mutex_p);
                return 555;
       }

         if(is_mid_up){
             if(mSPU==*hSPP&&first_time_hm){
                 
                 first_time_hm = false;
                 hSPP=&mSPD;
                 mSP=&mSPD;
                 if(mSPD->sold){
                     seats_full=true;
                 }
                 is_toggling=false;
                 is_mid_up=false;
             }
             else if (*lSPP==*hSPP)
                 seats_full=true;
             else
                 (*mSP)--;
         }else {
             if(*lSPP==mSPD&&first_time_ml){
                 first_time_ml=false;
                 lSPP=&mSPU;
                 mSP=&mSPU;
                 if(mSPD->sold){
                    seats_full=true;
                 }
                 is_toggling=false;
                 is_mid_up=true;
             }
             else if(*lSPP==*hSPP)
                 seats_full=true;
             else
                 (*mSP)++;
             
         }
      
         if((!first_time_hm)&&(!first_time_ml)){
             seats_full=true;
             print_ptrs();
             
             } 
        toggle_counter++;
       if(toggle_counter==10&&is_toggling)
           toggle_mid_pointer();
       if(!s->sold){
           mid_customers_served_counter++;
           this->seats_sold_counter++;
           s->sold=true;
//           cout<<"GONNA SERVE FOR " << to_string(c.serving_time) << endl;
            current_seat = s;
            this->seller_state=SERVING;
            this->remaining_serving_time= c.serving_time;
       }

               pthread_mutex_unlock(mutex_p);
               return 0;

}
 void mid_seller::toggle_mid_pointer(){
     toggle_counter = 0; //Toggles between up and down mid_pointers 
     if(is_mid_up){
         mSP = &mSPD;
         is_mid_up = false;
     }
     else{
         mSP = &mSPU;
         is_mid_up = true;
     }
 }   
    