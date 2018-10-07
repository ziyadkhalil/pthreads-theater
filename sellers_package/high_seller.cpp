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
                if(s->sold)
            print_ptrs();
       if(seats_full){
           this->seller_state=FINISHED;
           this->done_for_good=true;
           pthread_mutex_unlock(mutex_p);
           return 555;
       }
        if((*lSPP==mSPD&&first_time_ml)||(*hSPP==mSPU&&first_time_hm)){
        if(*lSPP==mSPD&&first_time_ml){
           cout<<"Meeting done in low seller\n";

           first_time_ml=false;
           lSPP=&mSPU;
           mSP=&mSPU;
           is_toggling=false;
           is_mid_up=true;
           
       }  if(*hSPP==mSPU&&first_time_hm){
             cout<<"Meeting HM done in Mid Seller\n";
             first_time_hm=false;
           hSPP=&mSPD;
           mSP=&mSPD;
           is_toggling=false;
           is_mid_up=false;
       }
        }
        
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
       }
              pthread_mutex_unlock(mutex_p);

    }
    
    
