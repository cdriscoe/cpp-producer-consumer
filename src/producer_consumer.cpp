#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <semaphore.h>
#include <pthread.h>
#include <iostream>
#include <cstdint>

//Declare constants
#define P_NUMBER       6
#define C_NUMBER       4
#define BUFFER_SIZE    12
#define N_P_STEPS      4
#define N_C_STEPS      6

//function prototypes
void Insert(int);

void Remove(int);

void *Consume(void*);

void *Produce(void*);

//variable declarations
int Counter = 0;
// Individual thread IDs are stored below and passed by address.

sem_t NotFull; //= BUFFER_SIZE;
sem_t NotEmpty; //= 0;

pthread_mutex_t mutex;

int main()
{

//initialize semaphores. NotFull = BUFFER_SIZE, NotEmpty = 0
sem_init(&NotFull, 0, BUFFER_SIZE);
sem_init(&NotEmpty, 0, 0);

//Initilize mutex to variable name mutex
pthread_mutex_init(&mutex,NULL);

//C_NUMBER of pthreads at CThreads
pthread_t CThreads[C_NUMBER];
int consumerIds[C_NUMBER];
//P_NUMBER of pthreads at PThreads
pthread_t PThreads[P_NUMBER];
int producerIds[P_NUMBER];


   for(int c=0; c < C_NUMBER; c++)
   {//create Consumer threads using c as index and Consume() function

      consumerIds[c] = c;
      pthread_create(&CThreads[c],NULL,Consume, &consumerIds[c]);

   }

   for(int p = 0; p < P_NUMBER; p++)
   {//create Producer threads using p as index and Produce()function

     producerIds[p] = p;
     pthread_create(&PThreads[p],NULL,Produce, &producerIds[p]);

   }

   for(int x = 0; x < P_NUMBER; x++)
   {//wait for PThreads[x] to terminate
     pthread_join(PThreads[x], NULL);
   }

   for(int i = 0; i < C_NUMBER; i++)
   {//wait for CThreads[i] to terminate
     pthread_join(CThreads[i], NULL);
   }
//destroy semaphores
     sem_destroy(&NotFull);
     sem_destroy(&NotEmpty);
//destroy mutex
     pthread_mutex_destroy(&mutex);

std::cout<< "The semaphores and mutex have been destroyed."<<std::endl;

std::cout << "All threads will now be terminated." <<std::endl;

//exit main thread
  return 0;
}


void Insert(int ThreadID)//lock mutex, increment counter, unloc mutex
{//Lock mutex
  pthread_mutex_lock(&mutex);
//increment counter
  Counter++;
//output ThreadID and counter
std::cout<<"Producer: "<<ThreadID<<" inserted a widget. Total is now: "<<Counter<<std::endl;
//Unlock mutex
  pthread_mutex_unlock(&mutex);

}

void Remove(int ThreadID)//lock mutex, decrement Counter, unlock mutex
{//Lock mutex
  pthread_mutex_lock(&mutex);
//decrement counter
  Counter--;
//output ThreadID and Counter
std::cout<<"Consumer: "<<ThreadID<<" removed a widget. Total is now: "<<Counter<<std::endl;
//unlock mutex
  pthread_mutex_unlock(&mutex);

}

void *Produce(void* threadArg)
{
 const int ThreadID = *static_cast<int*>(threadArg);

 for(int x = 0; x < N_P_STEPS; x++)
  {
    //wait for semaphore to return not full
    sem_wait(&NotFull);
    //call Insert() function 
    Insert(ThreadID);
    //post semaphore NotEmpty
    sem_post(&NotEmpty);
    //allow delay using sleep function for one second
    sleep(1);

  }
 //Terminate thread
 pthread_exit(NULL);

}

void *Consume(void* threadArg)//wait(NotEmpty),Remove(),post(NotFull)
{
 const int ThreadID = *static_cast<int*>(threadArg);

 for( int j = 0; j < N_C_STEPS; j++)
 {
   //wait ofr semaphore to return not empty
   sem_wait(&NotEmpty);
   //call Remove() function
   Remove(ThreadID);
   //post semaphore NotFull
   sem_post(&NotFull);
   //allow delay using sleep function for one second
   sleep(1);

  }
  //terminate thread
  pthread_exit(NULL);
}
