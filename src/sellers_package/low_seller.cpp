#include "seller.h"
seat* lSP = &seat_chart[9][9];
seat** lSPP = &lSP;
bool first_time_ml = true;
int xx = 0;
pthread_mutex_t lSPMutex;
pthread_mutex_t* l_mutex_ptr = &lSPMutex;
low_seller::low_seller(string seller_name,int pID):seller(L_SELLER,seller_name,pID){}

    
    int low_seller::serve(customer c){
         pthread_mutex_lock(mutex_p);
        seat* s=*lSPP;       
        
       if(seats_full){
           this->seller_state=FINISHED;
           this->done_for_good=true;
           pthread_mutex_unlock(mutex_p);
//           cout <<"boom done "<< to_string(this->pID)<<endl;
           return 555;
       }
//        if((*lSPP==mSPD&&first_time_ml)||(*hSPP==mSPU&&first_time_hm)){
//        if(*lSPP==mSPD&&first_time_ml){
//           cout<<"Meeting LM done in low seller\n";
//
//           first_time_ml=false;
//           lSPP=&mSPU;
//           mSP=&mSPU;
//           is_toggling=false;
//           is_mid_up=true;
//           
//       }  if(*hSPP==mSPU&&first_time_hm){
//             cout<<"Meeting HM done in low Seller\n";
//             first_time_hm=false;
//           hSPP=&mSPD;
//           mSP=&mSPD;
//           is_toggling=false;
//           is_mid_up=false;
//       }
//        }
        if(*lSPP==mSPD&&first_time_ml){
            
           first_time_ml=false;
           lSPP=&mSPU;
           mSP=&mSPU;
           if(mSPU->sold){
               seats_full=true;
               cout<<"christ\n";
            }
           is_toggling=false;
           is_mid_up=true;
        }
        else if(*lSPP==*hSPP){
            seats_full = true;
        }
       else
           (*lSPP)--;
        
        
        
         if((!first_time_hm)&&(!first_time_ml)){
           
           print_ptrs();
             seats_full=true;
             cout<<"jeeeeez from low\n";
         } 

       if(!s->sold){
           this->seats_sold_counter++;
           s->sold=true;
           this->current_seat=s;
           this->seller_state=SERVING;
           this->remaining_serving_time=c.serving_time;
       }
       else {cout<<"ERROR IN LOW SERVE"<<endl;
       exit(0);
       }
               pthread_mutex_unlock(mutex_p);

               return 0;
    }    