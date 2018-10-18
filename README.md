# pthreads-theater
a project on POSIX threads and synchronization using C/C++.
it simulates ticket sellers simultaneously selling concert tickets during one hour.
there are 100 seats available to a concert. One ticket seller named H sells
high-priced tickets, three ticket sellers named M1, M2, and M3 sell medium-priced
tickets, and six ticket sellers named L1, L2, L3, L4, L5, and L6 sell low-priced
tickets. Each ticket seller has a separate customer queue.
All the ticket sellers work simultaneously during one hour. Each seller can expect
N customers to arrive at random times during the hour, where N is a command-line parameter.
### To Compile:
1 - Go to root.\
2 - use the Makefile in terminator. 
```aidl
make build
```
### To Run: 
```aidl
./pthreads-theater N
```
Where N is the number of customers per queue. \
\
You can add "mbm" after N as a second paramter to enable minute by minute simulation.
```aidl
./pthreads-theater N mbm
```
 
