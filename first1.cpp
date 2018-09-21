#include <pthread.h>
#include <iostream>
using namespace std;
int total_sum = 0;

void *thread_sum1(void *arg) {
  int i, sum = 0;
  for (i = 1; i<101; i++ ) sum=sum+i;
  total_sum = total_sum + sum;
  return NULL;
}
void *thread_sum2(void *arg) {
  int i, sum = 0;
  for (i = 101; i<201; i++ ) sum= sum + i;
  total_sum = total_sum + sum;
  return NULL;
}
void *thread_sum3(void *arg) {
  int i, sum = 0;
  for (i = 201; i<301; i++ ) sum = sum +i;
  total_sum = total_sum + sum;
  return NULL;
}
void *thread_sum4(void *arg) {
  int i, sum = 0;
  for (i = 301; i<401; i++ ) sum = sum + i;
  total_sum = total_sum + sum;
  return NULL;
}
void *thread_sum5(void *arg) {
  int i, sum = 0;
  for (i = 401; i<501; i++ ) sum++;
  total_sum = total_sum + sum;
  return NULL;
}

int main(void) {
  int i;
  pthread_t thread1, thread2, thread3, thread4, thread5;

  if ( pthread_create( &thread1, NULL, thread_sum1, NULL) ) {
    cout << "error creating thread."<<endl;
    return -1;
  }
  if ( pthread_create( &thread2, NULL, thread_sum2, NULL) ) {
    cout << "error creating thread."<<endl;
    return -1;
  }
  if ( pthread_create( &thread3, NULL, thread_sum3, NULL) ) {
    cout << "error creating thread."<<endl;
    return -1;
  }
  if ( pthread_create( &thread4, NULL, thread_sum4, NULL) ) {
    cout << "error creating thread."<<endl;
    return -1;
  }
  if ( pthread_create( &thread5, NULL, thread_sum5, NULL) ) {
    cout << "error creating thread."<<endl;
    return -1;
  }
 if ( pthread_join (thread5, NULL ) ) {
    cout <<"error joining thread."<<endl;
    return -1;
  }
  cout << "Our sum is " << total_sum << endl;
  return 0;
}
