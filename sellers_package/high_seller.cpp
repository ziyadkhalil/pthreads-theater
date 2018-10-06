#include "../seller.h"

        seat* hSP = &seat_chart[0][0];
        pthread_mutex_t hSPMutex;

    high_seller::high_seller(string seller_name, int pID) :  seller(H_SELLER,seller_name,pID){
    }
    void*  high_seller::sell_tickets(void* arg){
        pthread_mutex_lock(&hSPMutex);   //LOCK POINTER SO NO ANOTHER HIGH SELLER CAN INCREMENT IT OR DEREFERNCE A WRONG SEAT! 
        seat s = *hSP;
        hSP++;
        pthread_mutex_unlock(&hSPMutex);
        s.sell_me(seller_name);
       
            //TODO: Some code to make the seller wait for the random time generated based on his priority 
        
    }
    
    
    
