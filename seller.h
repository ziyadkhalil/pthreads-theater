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
#include "time.h"
#include <iostream>
#include <stdlib.h>
#include <queue>
#include <algorithm>
#include <iomanip>
#include <iostream>
using namespace std;

extern bool done_working_for_this_minute[10];
extern seat seat_chart[10][10];  //EXTERN MAKES IT VISIBLE TO EVERYTHING BASICALLY 

extern seat* hSP;
extern pthread_mutex_t hSPMutex;

extern seat* mSPD;
extern seat* mSPU;
extern seat** mSP;
extern pthread_mutex_t mSPMutex;
extern bool is_mid_up;
extern int toggle_counter;

extern seat* lSP;
extern pthread_mutex_t lSPMutex;

#define  H_SELLER       1
#define  M_SELLER       2
#define  L_SELLER       3


class customer{
public:
    int aT;                                         // arrival time of a customer
    
    void set_aT(int aT){
        this->aT =aT;
    }
};

class seller {
    
public:
    string seller_name;
    int pID;
    int seed = time(NULL);
    int s_type;
    seller(int s_type,string seller_name,int pID);
    queue<customer> cQ;    
    int fRanInt(int,int);
    int gen_aT();
    void fill_cQ(int N);
    bool are_all_sellers_done();
    virtual void* sell_tickets(void* arg) = 0;
    
    
    
private:

};

class high_seller : public seller {
public:
    int s_type;
    high_seller(string seller_name, int pID);
    void* sell_tickets  (void* arg) override;
    
private:

};

class mid_seller : public seller {
public:
    string x;
    int xx=0;
    int s_type;
    mid_seller(string seller_name,int pID);
    void toggle_mid_pointer();
    void* sell_tickets(void* arg);
    
private:

};

class low_seller : public seller {
public:

    int s_type;
    low_seller(string seller_name,int pID);
    void* sell_tickets(void* arg) override;
    
private:

};


#endif /* SELLER_H */

