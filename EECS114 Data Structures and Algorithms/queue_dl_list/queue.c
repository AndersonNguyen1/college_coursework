#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "timer.c"

struct QueueNode* CreateQueueList(float value);
struct QueueNode* first;
struct QueueNode* last;

void Enqueue(float value);

struct QueueNode  {
  float key;
  struct QueueNode* next; 
};

float Random() {
  float randomNum = (float)(rand()/(float)(RAND_MAX));
  return randomNum;
}

float Queue(int n, int t) {
  for(int i = 0; i < n; i++)  {
    float randNum = Random();
    Enqueue(randNum);
  }

  // dequeue 
  float firstPerson = first->key;
  first = first->next;

  for(int j = 0; j < t; j++)  {
    Enqueue(firstPerson);
  }
}

long double Timer(int N, int T)  {
  stopwatch_init();
  struct stopwatch_t* timer = stopwatch_create();
  assert(timer);
  stopwatch_start(timer);
  
  Queue(N, T);
  long double t_qs = stopwatch_stop(timer);
  return t_qs;
}

struct QueueNode* CreateQueueList(float value)  {
  struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
  newNode->key = value;
  newNode->next = NULL; 
  return newNode;
}

void Enqueue(float value) {
  if(last == NULL)  {
    last = CreateQueueList(value);
    first = last;
  }
  else  {
    struct QueueNode* temp = CreateQueueList(value);
    last->next = temp;
    last = temp;
  } 
}

int main(int argc, char* argv[]) {
  int N, T = -1;

  if (argc == 3)  {
    N = atoi (argv[1]);
    T = atoi (argv[2]);
    assert (N > 0);
  }
  else  {
    fprintf (stderr, "usage: %s <n>\n", argv[0]);
    fprintf (stderr, "where <n> is the length of the list to sort.\n");
    return -1;
  }
  srand(time(NULL));
  float randFloat = Random();
  struct QueueNode *a = CreateQueueList(randFloat);
  long double totalTime = Timer(N, T);
  printf("% Lg seconds \n\n", totalTime/T);
  return 0;
}

