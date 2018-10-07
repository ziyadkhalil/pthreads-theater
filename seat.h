/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   seat.h
 * Author: ziyad
 *
 * Created on October 5, 2018, 9:18 PM
 */


#ifndef SEAT_H
#define SEAT_H
#include <pthread.h>
#include <iostream>
#include <string>
using namespace std;
extern pthread_mutex_t sold_seats_mutex;
class seat{
public:
    int i;
    int j;
    static int soldSeats;
    bool sold;                                      // status of a seat
    string sold_by;                              // seller who sold the seat
    seat();
    void sell_me(string);
    void setIJ(int i, int j);
};



#endif /* SEAT_H */

