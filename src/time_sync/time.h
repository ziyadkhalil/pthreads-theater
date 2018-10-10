/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   time.h
 * Author: ziyad
 *
 * Created on October 6, 2018, 1:51 AM
 */

#ifndef TIME_H
#define TIME_H
#include<pthread.h>
extern int time_counter;
extern pthread_mutex_t time_mutex;
extern pthread_cond_t time_cond;
extern pthread_mutex_t start_mutex;
extern pthread_cond_t start_cond;

#endif /* TIME_H */

