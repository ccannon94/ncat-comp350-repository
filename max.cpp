/******************************************************************************
* FILE: max.cpp
* DESCRIPTION:
*   A Pthreads program which finds the maximum value of each column of a
*   given array.
* AUTHOR: Ed Carr
* LAST REVISED: 09/17/08
******************************************************************************/
#include <pthread.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;
int mymatrix[5][5], sum;
const int myrow = 5;
const int mycol = 5;
//pthread_mutex_t mymutex=PTHREAD_MUTEX_INITIALIZER;

void *my_max(void *threadid)
{
   int *id_ptr, col, i, max;
   id_ptr = (int *) threadid;
   col = *id_ptr;
   max = mymatrix[0][col];
   for(i = 1; i< myrow; i++)
     if(mymatrix[i][col] > max) max = mymatrix[i][col];
   cout << " max for col " << col+1 << " is :" << max << endl;
  // pthread_mutex_lock(&mymutex);
   sum = sum + max;
  // pthread_mutex_unlock(&mymutex);
   pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
pthread_t threads[5];
int *taskids[5];
int rc, t, temp, i,j;
ifstream fin("indata.txt");
for(i = 0; i<myrow; i++)
  for(j = 0; j< mycol; j++)
	fin >> mymatrix[i][j];

for(t=0;t<mycol;t++) {
  taskids[t] = (int *) malloc(sizeof(int));
  *taskids[t] = t;
  cout << "Creating thread " << t << endl;
  rc = pthread_create(&threads[t], NULL, my_max, (void *) taskids[t]);
  if (rc) {
    cout << "ERROR; return code from pthread_create() is "<< rc << endl;
    exit(-1);
    }
  }
for(t = 0; t<mycol; t++){
  if( pthread_join(threads[t], NULL)) {
  cout << "error joining threads."<<endl;
  return -1;
  }
 }
 cout << "Sum = " << sum << endl;
pthread_exit(NULL);
}
