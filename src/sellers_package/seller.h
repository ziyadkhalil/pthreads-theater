/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   seller.h
 * Author: ziyad
 *
 * Created on October 5, 2018, 2:29 PM
 */
#ifndef SELLER_H
#define SELLER_H
#include "seat.h"
#include "../time_sync/time.h"
#include <iostream>
#include <stdlib.h>
#include <queue>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include "unistd.h"
using namespace std;
extern pthread_mutex_t mutex;
extern pthread_mutex_t* mutex_p;
extern bool done_working_for_this_minute[10];
extern bool done_working_for_good[10];
extern bool ready_to_start[10];
extern bool done;
extern seat seat_chart[10][10];  //EXTERN MAKES IT VISIBLE TO EVERYTHING BASICALLY 

extern seat* hSP;
extern seat** hSPP;
extern bool first_time_hm;
extern bool first_time_ml;
extern bool seats_full;


extern seat* mSPD;
extern seat* mSPU;
extern seat** mSP;
extern bool is_mid_up;
extern bool is_toggling;
extern int toggle_counter;


extern seat* lSP;
extern seat** lSPP;


#define  H_SELLER       1
#define  M_SELLER       2
#define  L_SELLER       3


class customer{
public:
    bool got_served = false;
    string name;
    int aT;                                         // arrival time of a customer
    int serving_time;
    void set_aT(int aT){
        this->aT =aT;
    }
};

class seller {

public:
        enum SELLER_STATE{
        SERVING,
        WAITING,
        FINISHED
    };
    bool done_for_good = false;
    string seller_name;
    int seats_sold_counter=0;
    int pID;
    int seed = time(NULL);
    int s_type;
    seat* current_seat = nullptr;
    seller(int s_type,string seller_name,int pID);
    queue<customer> cQ;
    customer cArr[] = new customer[NUMBER_OF_CUSTOMERS_PER_QUEUE];    
    int fRanInt(int,int);
    int gen_aT();
    int gen_serving_time();
    void fill_cQ(int N);
    bool are_all_sellers_done();
    bool are_all_sellers_done_for_good();
    void sell_tickets();
    string create_ID_for_seat();
    SELLER_STATE seller_state;
    int remaining_serving_time;
    int current_minute = 0;
    string event_log[70];
    void print_ptrs();
    virtual int serve(customer c)=0;
    
    
    
    
    
private:

};

class high_seller : public seller {
public:
    int s_type;
    high_seller(string seller_name, int pID);
    void sell_tickets  ();
    int serve(customer c);
    
private:

};

class mid_seller : public seller {
public:
    string x;
    int xx=0;
    int s_type;
    mid_seller(string seller_name,int pID);
    void toggle_mid_pointer();
    void sell_tickets();
    int serve(customer c) override;
    
private:

};

class low_seller : public seller {
public:

    int s_type;
    low_seller(string seller_name,int pID);
    void sell_tickets() ;
    int serve(customer c);
    
private:

};


#endif /* SELLER_H */

