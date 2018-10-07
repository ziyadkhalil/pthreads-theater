#include "../seller.h"

        seat* hSP = &seat_chart[0][0];
        pthread_mutex_t hSPMutex;
        pthread_mutex_t* h_mutex_ptr = &hSPMutex;

    high_seller::high_seller(string seller_name, int pID) :  seller(H_SELLER,seller_name,pID){
    }

    int high_seller::serve(customer c){
        seat* s;
       pthread_mutex_lock(h_mutex_ptr);
//       pthread_mutex_lock(&dbhm_mutex); 
//       if(distance_between_high_and_mid<=0){
//           pthread_mutex_lock(m_mutex_ptr);
//           hSP = mSPD;
//           s = hSP;
//           hSP++;
//           cout<<hSP;
//           pthread_mutex_unlock(m_mutex_ptr);
//       }
//       else{
           s=hSP;
           hSP++;
//           distance_between_high_and_mid--;
//       }
//              pthread_mutex_unlock(&dbhm_mutex);
       pthread_mutex_unlock(h_mutex_ptr);
       if(!s->sold){
           this->seats_sold_counter++;
           s->sold=true;
           this->current_seat=s;
           this->seller_state=SERVING;
           this->remaining_serving_time=c.serving_time;
           return 1;
       }
       return 0;
    }
    
    
