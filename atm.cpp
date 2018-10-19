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

int main(int argc, char *argv[])
{
  account_balance = 0;

  ifstream inputFile(argv[1]);
  num_founder_transactions = "";
  num_acc1_transactions = "";
  num_acc2_transactions = "";
  founder_transactions = "";
  acc1_transactions = "";
  acc2_transactions = "";
  if(inputFile.isOpen())
  {
    getline(inputFile);
    getline(inputFile, num_founder_transactions);
    getline(inputFile, founder_transactions);
    getline(inputFile, num_acc1_transactions);
    getline(inputFile, acc1_transactions);
    getline(inputFile, num_acc2_transactions);
    getline(inputFile, acc2_transactions);
    
  }
}
