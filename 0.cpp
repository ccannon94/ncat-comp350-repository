#include <pthread.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

int *allsums;
int numthreads;
int *vals;
pthread_mutex_t sum_mutex;
pthread_t *thread_ids;

struct thread_data{
  int blocksize;
  int startingval;
};

void *thread_sum(void *thread_input)
{
  int first_val = ((struct thread_data*)thread_input)->startingval;
  int last_val = first_val + ((struct thread_data*)thread_input)->blocksize;
  int sum = 0;
  for(int i = first_val; i < last_val; i++)
  {
    sum = sum + vals[i];
  }
  pthread_mutex_lock(&sum_mutex);
  for(int j = 0; j < numthreads; j++)
  {
    if(allsums[j] == 0)
    {
      allsums[j] = sum;
      break;
    }
  }
  pthread_mutex_unlock(&sum_mutex);
}

int main(int argc, char *argv[])
{
  ifstream inputFile(argv[0]);
  numthreads = atoi(argv[1]);
  thread_ids = new pthread_t[numthreads];
  string arraySizeString = "";
  if(inputFile.is_open())
  {
    getline(inputFile,arraySizeString);
    int arraySize = atoi(arraySizeString.c_str());
    allsums = new int[numthreads];
    vals = new int[arraySize];
    int file_iterator = 0;
    while(inputFile.eof())
    {
      string num;
      getline(inputFile, num);
      vals[file_iterator] = atoi(num.c_str());
      file_iterator++;
    }
    if((arraySize % numthreads) == 0)
    {
      for(int i = 0; i < numthreads; i++)
      {
        int tblocksize = arraySize / numthreads;
        int tstartingval = tblocksize * i;
        struct thread_data *args= (struct thread_data *)malloc(sizeof(struct thread_data));
        args->blocksize = tblocksize;
        args->startingval = tstartingval;
        pthread_create(&thread_ids[i], NULL, thread_sum, (void *) args);
      }
    } else
    {
      int tblocksize = arraySize / numthreads;
      int tstartingval = 0;
      for(int l = 0; l < numthreads; l++)
      {
        tstartingval = tblocksize * l;
        if(l == (numthreads - 1))
        {
          tblocksize = arraySize - tstartingval;
        }
        struct thread_data *args= (struct thread_data *)malloc(sizeof(struct thread_data));
        args->blocksize = tblocksize;
        args->startingval = tstartingval;
        pthread_create(&thread_ids[l], NULL, thread_sum, (void *) args);
      }
    }
    for(int j = 0; j < numthreads; j++)
    {
      if(pthread_join(thread_ids[j], NULL))
      {
        cout<<"error joining thread"<<j<<endl;
        return -1;
      }
    }

    int finalsum = 0;
    for(int k = 0; k < numthreads; k++)
    {
      finalsum = finalsum + allsums[k];
    }
    cout << finalsum << endl;
  }
  return 0;
}
