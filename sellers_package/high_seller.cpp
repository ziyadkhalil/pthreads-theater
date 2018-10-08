#include "../seller.h"

        seat* hSP = &seat_chart[0][0];
        seat** hSPP = &hSP;
        pthread_mutex_t hSPMutex;
        pthread_mutex_t* h_mutex_ptr = &hSPMutex;
        bool first_time_hm=true;

    high_seller::high_seller(string seller_name, int pID) :  seller(H_SELLER,seller_name,pID){
    }

    int high_seller::serve(customer c){
       pthread_mutex_lock(mutex_p);
        seat* s=*hSPP;   
        
       if(seats_full){
           this->seller_state=FINISHED;
           this->done_for_good=true;
           pthread_mutex_unlock(mutex_p);
           return 555;
       }
        
        if(*hSPP==mSPU&&first_time_hm){
          
             first_time_hm=false;
           hSPP=&mSPD;
           mSP=&mSPD;
           if(mSPD->sold){
               seats_full=true;
               cout <<" chris\n";
                }
           is_toggling=false;
           is_mid_up=false;
        }
        else if(*lSPP==*hSPP)
            seats_full = true;
         else
           (*hSPP)++;
        
         if((!first_time_hm)&&(!first_time_ml)){
           print_ptrs();
             seats_full=true;
             cout<<"jeeeeez from high\n";
         } 
       
      

       if(!s->sold){
           this->seats_sold_counter++;
           s->sold=true;
           this->current_seat=s;
           this->seller_state=SERVING;
           this->remaining_serving_time=c.serving_time;
       }
       else{ cout<<"ERROR IN HIGH SERVE"<<endl;
       exit(0);
       }
              pthread_mutex_unlock(mutex_p);

    }
    
    
