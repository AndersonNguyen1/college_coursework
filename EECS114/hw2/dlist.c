#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "timer.c"

struct QueueNode* CreateQueueList(int value);
struct QueueNode* first;
struct QueueNode* last;

void appendHead(int value);
void appendTail(int value);

struct QueueNode  {
  int key;
  struct QueueNode* next;
  struct QueueNode* prev;
};

// creates an empty doubly linked list
struct QueueNode* CreateQueueList(int value)  {
  struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
  newNode->key = value;
  newNode->next = NULL;
  newNode->prev = NULL;
  return newNode;
}

//add to front
void appendHead(int value) {
  if(first == NULL)  {
    first = CreateQueueList(value);
    last = first;
    }
  else  {
    struct QueueNode* temp = CreateQueueList(value);
    temp->next = first;
    first->prev = temp;
    temp->next = NULL;
    first = temp;
  }
}

// add to back
void appendTail(int value) {
  if(first == NULL)  {
    first = CreateQueueList(value);
    last = first;
  }
  else  {
    struct QueueNode* temp = CreateQueueList(value);
    temp->prev = last;
    last->next = temp;
    temp->next = NULL;
    last = temp;
  }
}

// return first node
struct QueueNode* firstNode()  {
    return first;
}

//return last node
struct QueueNode* lastNode() {
    return last;
}

// remove specific node
void removeNode(struct QueueNode* queuenode) {
  if(first == NULL || queuenode == NULL){
    return;
  }
  else if(queuenode->prev != NULL)  {
    queuenode->prev->next = queuenode->next;
  }
  else  {
    first = queuenode->next;
  }
  if(queuenode->next != NULL) {
    queuenode->next->prev = queuenode->prev;
  }
}

// return the previous node (given a node)
struct QueueNode* prevNodeGivenNode(struct QueueNode* temp) {
  return temp->prev;
}

// return the next node (given a node)
struct QueueNode* nextNodeGivenNode(struct QueueNode* temp) {
  return temp->next;
}

// search for a node that contains a given value
struct QueueNode* searchNode(int val) {
  struct QueueNode* temp = firstNode();
  while((temp->next != NULL) && (temp->key != val)) {
    temp = temp->next;
  }
  if(temp->key == val)  {
    return temp;
  }  
  else  {
    return NULL;
  }
}

int main(int argc, char* argv[]) {
  int N = -1;

  if (argc == 2)  {
    N = atoi (argv[1]);
    assert (N > 0);
  }
  srand(time(NULL));
 
  for(int i = 1; i <= N; i++) {
    appendTail(i);  
  }
  stopwatch_init();
  struct stopwatch_t* timer = stopwatch_create();
  assert(timer);
  stopwatch_start(timer);

  for(int j = 0; j < 20; j++)  { 
    int x = rand() % (N + 1 - 1) + 1;
    if(searchNode(x) != NULL) {
    removeNode(searchNode(x));
    }
    appendHead(x);
  }
  long double t_qs = stopwatch_stop(timer);
  printf("% Lg seconds \n\n", t_qs/20);
  return 0;
}

