#include <pthread.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

int account_balance;
pthread_mutex_t balance_mutex;
pthread_t *thread_ids;
string num_founder_transactions;
string num_acc1_transactions;
string num_acc2_transactions;
string founder_transactions;
string acc1_transactions;
string acc2_transactions;

void balance_query()
{
  cout<<"The account balance is: ";
  pthread_mutex_lock(&balance_mutex);
  cout<<account_balance;
  pthread_mutex_unlock(&balance_mutex);
  cout<<endl;
}

void deposit(int deposit_amount)
{
  pthread_mutex_lock(&balance_mutex);
  account_balance = account_balance + deposit_amount;
  pthread_mutex_unlock(&balance_mutex);
}

void withdrawal(int withdrawal_amount)
{
  pthread_mutex_lock(&balance_mutex);
  account_balance = account_balance - withdrawal_amount;
  pthread_mutex_unlock(&balance_mutex);
}

void *thread_founder(void *arg)
{
  
}

void *thread_acc1(void *arg)
{

}

void *thread_acc2(void *arg)
{

}

int main(int argc, char *argv[])
{
  account_balance = 0;

  thread_ids = new pthread_t[3];

  ifstream inputFile(argv[1]);
  num_founder_transactions = "";
  num_acc1_transactions = "";
  num_acc2_transactions = "";
  founder_transactions = "";
  acc1_transactions = "";
  acc2_transactions = "";
  string throwaway_string = "";
  if(inputFile.is_open())
  {
    getline(inputFile, throwaway_string);
    getline(inputFile, num_founder_transactions);
    getline(inputFile, founder_transactions);
    getline(inputFile, throwaway_string);
    getline(inputFile, num_acc1_transactions);
    getline(inputFile, acc1_transactions);
    getline(inputFile, throwaway_string);
    getline(inputFile, num_acc2_transactions);
    getline(inputFile, acc2_transactions);

    pthread_create(&thread_ids[0], NULL, thread_founder, (void *) args);
    pthread_create(&thread_ids[1], NULL, thread_acc1, (void *) args);
    pthread_create(&thread_ids[2], NULL, thread_acc2, (void *) args);
  }
}
