#include "../seller.h"
#include <unistd.h>


 seat* mSPD = &seat_chart[5][0];
 seat* mSPU = &seat_chart[4][9];
 seat** mSP = &mSPU; //POINTER TO A POINTER BECAUSE LIFE IS A BITCH  //TODO: REMIND ME TO EXPLAIN 
 pthread_mutex_t mSPMutex;
 pthread_mutex_t* m_mutex_ptr = &mSPMutex;
 bool is_mid_up = true;
 bool is_toggling = true;
 int toggle_counter = 0;
 pthread_mutex_t dbhm_mutex;
  pthread_mutex_t dbml_mutex;
  int distance_between_high_and_mid=50;
  int distance_between_mid_and_low=50;

 

mid_seller::mid_seller(string seller_name,int pID):seller(M_SELLER,seller_name,pID){}


int mid_seller::serve(customer c)  {
         pthread_mutex_lock(m_mutex_ptr);   //LOCK POINTER SO NO ANOTHER MID SELLER CAN INCREMENT IT OR DEREFERNCE A WRONG SEAT! 
//       pthread_mutex_lock(&dbhm_mutex); 
//       pthread_mutex_lock(&dbml_mutex); //TODO: make it a ptr
       
//       if(distance_between_high_and_mid<0&&distance_between_mid_and_low<0){
//           return -1;
//       }
//       if(distance_between_high_and_mid<0){
//           mSP = &mSPD;
//           is_toggling = false;
//           is_mid_up = false;
//       }
//       if(distance_between_mid_and_low<0){
//           mSP = &mSPU;
//           is_toggling = false;
//           is_mid_up = true;
//       }
//        if(is_mid_up)
//           distance_between_high_and_mid--;
//       else
//           distance_between_mid_and_low--;
       seat* s = *mSP;
       if(is_mid_up)
           (*mSP)--;
       else
           (*mSP)++;
       
       toggle_counter++;
       if(toggle_counter==10&&is_toggling)
           toggle_mid_pointer();
//       pthread_mutex_unlock(&dbml_mutex);
//       pthread_mutex_unlock(&dbhm_mutex);
       pthread_mutex_unlock(m_mutex_ptr);
       if(!s->sold){
           this->seats_sold_counter++;
           s->sold=true;
//           cout<<"GONNA SERVE FOR " << to_string(c.serving_time) << endl;
            current_seat = s;
            this->seller_state=SERVING;
            this->remaining_serving_time= c.serving_time;
            return 1;
       }
       else{
           cout<<"WE FUCKED UP\n";
           return -1;
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
    