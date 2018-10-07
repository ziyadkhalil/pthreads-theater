#include "../seller.h"
seat* lSP = &seat_chart[9][9];
int xx = 0;
pthread_mutex_t lSPMutex;
pthread_mutex_t* l_mutex_ptr = &lSPMutex;
low_seller::low_seller(string seller_name,int pID):seller(L_SELLER,seller_name,pID){}
    void  low_seller::sell_tickets(){
        cout<<"low"<<endl;
    }
    
    int low_seller::serve(customer c){
        seat* s;
        pthread_mutex_lock(l_mutex_ptr);
         s=lSP;
        lSP--;
        pthread_mutex_unlock(l_mutex_ptr);
        if(!s->sold){
           this->seats_sold_counter++;
           s->sold=true;
           this->current_seat=s;
           this->seller_state=SERVING;
           this->remaining_serving_time=c.serving_time;
           return 1;
       }
       return 0;
        
        
        return 0;
    }    