#include <pthread.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <sstream>

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
  int num_trans = stoi(num_founder_transactions);
  string buf;
  stringstream ss(founder_transactions);

  vector<string> tokens;

  while (ss >> buf)
  {
    tokens.push_back(buf);
  }

  for(int i = 0; i < tokens.size(); ++i)
  {
    string transaction = tokens[i];
    stringstream transaction_amount_string;
    int transaction_amount = 0;
    if(transaction[0] == 'Q')
    {
      balance_query();
    }else if(transaction[0] == 'D')
    {
      for(int j = 0; j < transaction.size(); ++j)
      {
        transaction_amount_string << transaction[j];
      }
      transaction_amount_string >> transaction_amount;

      deposit(transaction_amount);
    }else if(transaction[0] == 'W')
    {
      for(int j = 0; j < transaction.size(); ++j)
      {
        transaction_amount_string << transaction[j];
      }
      transaction_amount_string >> transaction_amount;

      deposit(transaction_amount);
    }
  }
}

void *thread_acc1(void *arg)
{
  int num_trans = stoi(num_acc1_transactions);
  string buf;
  stringstream ss(acc1_transactions);

  vector<string> tokens;

  while (ss >> buf)
  {
    tokens.push_back(buf);
  }

  for(int i = 0; i < tokens.size(); ++i)
  {
    string transaction = tokens[i];
    stringstream transaction_amount_string;
    int transaction_amount = 0;
    if(transaction[0] == 'Q')
    {
      balance_query();
    }else if(transaction[0] == 'D')
    {
      for(int j = 0; j < transaction.size(); ++j)
      {
        transaction_amount_string << transaction[j];
      }
      transaction_amount_string >> transaction_amount;

      deposit(transaction_amount);
    }else if(transaction[0] == 'W')
    {
      for(int j = 0; j < transaction.size(); ++j)
      {
        transaction_amount_string << transaction[j];
      }
      transaction_amount_string >> transaction_amount;

      deposit(transaction_amount);
    }
  }
}

void *thread_acc2(void *arg)
{
  int num_trans = stoi(num_acc2_transactions);
  string buf;
  stringstream ss(acc2_transactions);

  vector<string> tokens;

  while (ss >> buf)
  {
    tokens.push_back(buf);
  }

  for(int i = 0; i < tokens.size(); ++i)
  {
    string transaction = tokens[i];
    stringstream transaction_amount_string;
    int transaction_amount = 0;
    if(transaction[0] == 'Q')
    {
      balance_query();
    }else if(transaction[0] == 'D')
    {
      for(int j = 0; j < transaction.size(); ++j)
      {
        transaction_amount_string << transaction[j];
      }
      transaction_amount_string >> transaction_amount;

      deposit(transaction_amount);
    }else if(transaction[0] == 'W')
    {
      for(int j = 0; j < transaction.size(); ++j)
      {
        transaction_amount_string << transaction[j];
      }
      transaction_amount_string >> transaction_amount;

      withdrawal(transaction_amount);
    }
  }
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

    pthread_create(&thread_ids[0], NULL, thread_founder, NULL);
    pthread_create(&thread_ids[1], NULL, thread_acc1, NULL);
    pthread_create(&thread_ids[2], NULL, thread_acc2, NULL);

    pthread_join(thread_ids[0], NULL);
    pthread_join(thread_ids[1], NULL);
    pthread_join(thread_ids[2], NULL);
  }
  return 0;
}
