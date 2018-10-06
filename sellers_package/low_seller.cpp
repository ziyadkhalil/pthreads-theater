#include "../seller.h"
seat* lSP = &seat_chart[9][9];
int xx = 0;
pthread_mutex_t lSPMutex;
low_seller::low_seller(string seller_name,int pID):seller(L_SELLER,seller_name,pID){}
    void*  low_seller::sell_tickets(void* arg){
        cout<<"low"<<endl;
    }