/* 
Author: Alejandro Fernandez Hernandez
*/
#include <thread>
#include <stdio.h>
#include <mutex>
#include <unistd.h>
#include <map>
#include <iostream>

/*
    Variables that will specify the range of pid values
    basically it says that process identifiers are constant
    integers (final key word) between 300 and 5000.
    */
#define MIN_PID 300
#define MAX_PID 5000
/*
    variables that identify availability of a particular process identifier
    with 0 being available and 1 being currently in use
    */
#define Available 0
#define Busy 1

//Create a map as our data structure to keep track of our PIDS
std::map<int,int> map_pid;

//Create a mutex lock
std::mutex mtx;


 //Prototypes of our functions
int allocate_map();

int allocate_pid();

void release_pid(int pid);

void routine_thread();
/*
Each thread requests an identifier.
If all identifiers are used by other threads, it should wait for another one that becomes available.
Once the thread gets the pid, it sleeps for some time which is randomly generated and during that time thread compeletes
its task. After the thread wakes up it releases the pid to be used by another thread.
*/

int main()
{
  std::thread newthread[50];



allocate_map();

//create 50 Threads
for (int i=0;i<50;i++) {

newthread[i] = std::thread(routine_thread);

    }
//Wait for the 50 threads to finish
for (int i=0;i<50;i++) {
        newthread[i].join();


    }

std::cout<<"end of Main\n";


}
/*
     int allocate_map(void) - Creates and initializes a data structure for representing pids; returns -1 if unsuccessful and 1 if successful
     This method allocates a  map of possible pids.
     The map has Key/Value principle.
     Key is an Integer, Value is "available (0) /Busy (1)" for allocation to an active process.
     */
int allocate_map(){

   //allocated map for certain capacity

  for(int i=MIN_PID; i <= MAX_PID; i++){
    map_pid.insert({i,Available}); //values for all the keys are set to 0

  }
  //confirmation
  std::cout<<"Successfully created and initialized a map of PIDS\n";
  return 1;

};
 /*
    int allocate_pid(void) - Allocates and returns a pid; returns -1 if if unable to allocate a pid (all pids are in use)
     */
 int allocate_pid(){

   static int i=1;//counter for threads
   for (const auto& [key, value] : map_pid) {

        if( value == Available){
          // critical section (exclusive access to std::cout signaled by locking mtx):
  mtx.lock();
          map_pid[key]=Busy;
           std::cout<<"Process: "<<key<<" is now allocated and busy with THREAT #"<<i++<<"\n";
  mtx.unlock();
          return key;
        }
    }
    return -1;
 };
 /*
   	void release_pid(int_pid) - Releases a pid.
     */
 void release_pid(int pid){

           // method releases used process identifier which is passes as parameter-Integer pid
        // critical section (exclusive access to std::cout signaled by locking mtx):
   mtx.lock();


        map_pid[pid]=Available;
        std::cout<<"Process: "<<pid<<" is now release and available\n";
                                   //if it is valid pid, it becomes released and the pid can be used by another process. It is set to available (0)
   mtx.unlock();

 };
 //Funtion for each threat
 void routine_thread(){
   int PID=allocate_pid();
  sleep(rand());  //Thread sleeps for a while - time is random
  release_pid(PID);

 };
