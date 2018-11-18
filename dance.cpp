#include <pthread.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <semaphore.h>
#include <unistd.h>

using namespace std;

string outputFileName;

//Computational variables
int leaders = 0;
int followers = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t leaderQueue;
sem_t followerQueue;
sem_t rendezvous;

int main(int argc, char *argv[])
{
  sem_init(&leaderQueue, 0, 0);
  sem_init(&followerQueue, 0, 0);
  sem_init(&rendezvous, 0, 0);

  if(argc == 4)
  {
    leaders = stoi(argv[1]);
    followers = stoi(argv[2]);
    outputFileName = argv[3];
  }

  while(true)
  {
    mutex.wait()
    if (followers > 0)
    {
      followers --;
      followerQueue.signal();
    } else
    {
      leaders++;
      mutex.signal();
      leaderQueue.wait();
    }
    dance();
    rendezvous.wait();
    mutex.signal();


    mutex.wait();
    if (leaders > 0)
    {
      leaders--;
      leaderQueue.signal();
    }else
    {
      followers++;
      mutex.signal();
      followerQueue.wait();
    }
    dance();
    rendezvous.signal();
  }
}

void dance()
{
  ofstream outputFile;
  outputFile.open(outputFileName);
  outputFile << "Leader " << leaders << " dancing with follower " << followers << endl;
  outputFile.close();
}
