
#include "../seller.h"
seat seat_chart[10][10];
bool done_working_for_this_minute[10];
seller::seller(int s_type,string seller_name,int pID){
    this->s_type=s_type;
    this->seller_name = seller_name;
    this->pID = pID;
}

int seller::fRanInt(int min , int max){return rand()%(max-min + 1) + min;}

int seller::gen_aT(){
     if (this->s_type == H_SELLER)
            return fRanInt(1,2);
     else if(this->s_type == M_SELLER)
            return fRanInt(2,4);
        else
            return fRanInt(4,7);
}

void seller::fill_cQ(int N){
      srand(seed);
      customer tmp[N];
        
        for (int i = 0; i<N; i++){
            tmp[i] = customer();
            tmp[i].set_aT(gen_aT());
        }
        
        sort(tmp, tmp+N,
             [](customer const & p1, customer const & p2) -> bool
             { return p1.aT < p2.aT; } );
        
        for (int i = 0; i<N; i++){
            cQ.push(tmp[i]);
        }
    }

bool seller::are_all_sellers_done(){
    if(done_working_for_this_minute[0]&&done_working_for_this_minute[1]&&done_working_for_this_minute[2]&&
          done_working_for_this_minute[3]&&done_working_for_this_minute[4]&&done_working_for_this_minute[5]&&
          done_working_for_this_minute[6]&&done_working_for_this_minute[7]&&done_working_for_this_minute[8]&&
          done_working_for_this_minute[9]){
                for(int i = 0; i < 10 ; i ++)
                     done_working_for_this_minute[i]=false;
        return true;
    }
    else
        return false;
}
