void *PrintHello(void *threadid)
{
  int *id_ptr, taskid;
  id_ptr = (int *) threadid;
  taskid = *id_ptr;
  cout << "Thread " << taskid << endl;
  pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
  pthread_t = threads[NUM_THREADS];
  int *taskids[NUM_THREADS];
  int rc, t;

  for(t = 0; t<NUM_THREADS; t++)
  {
    taskids[t] = t;
    cout << "Creating thread " << t << endl;
    rc = pthread_create(&threads[t], NULL, PrintHello, (void *) taskids[t]);
    if(rc)
    {
      cout << "ERROR; return code from pthread_create() is " << rc << endl;
      exit(-1);
    }
  }

  for(t = 0; t < NUM_THREADS; t++)
  {
    if(pthread_join(threads[t], NULL))
    {
      cout << "error joining threads" << endl;
      exit(-1);
    }
    cout << t << endl;
  }

  pthread_exit(NULL);
}
