#include <limits.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "timer.h"
#include <assert.h>
  
struct AdjListNode { 
  int dest; 
  float weight; 
  struct AdjListNode* next; 
}; 
  
struct AdjList { 
  struct AdjListNode* head; // pointer to head node of list 
}; 
  
struct Graph { 
  int V; 
  struct AdjList* array; 
}; 
  
struct AdjListNode* newAdjListNode(int dest, float weight) 
{ 
  struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode)); 
  newNode->dest = dest; 
  newNode->weight = weight; 
  newNode->next = NULL; 
  return newNode; 
} 
  
struct Graph* createGraph(int V) { 
  struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph)); 
  graph->V = V; 
  
  graph->array = (struct AdjList*)malloc(V * sizeof(struct AdjList)); 
  
  for (int i = 0; i < V; ++i) 
    graph->array[i].head = NULL; 
    
  return graph; 
} 
  
void addEdge(struct Graph* graph, int src, int dest, float weight) { 
  struct AdjListNode* newNode = newAdjListNode(dest, weight); 
  newNode->next = graph->array[src].head; 
  graph->array[src].head = newNode; 
  
  newNode = newAdjListNode(src, weight); 
  newNode->next = graph->array[dest].head; 
  graph->array[dest].head = newNode; 
} 
  
// Structure to represent a min heap node 
struct MinHeapNode { 
  int v; 
  int key; 
}; 
  
// Structure to represent a min heap 
struct MinHeap { 
  int size; // Number of heap nodes present currently 
  int capacity; // Capacity of min heap 
  int* pos; // This is needed for decreaseKey() 
  struct MinHeapNode** array; 
}; 
  
// A utility function to create a new Min Heap Node 
struct MinHeapNode* newMinHeapNode(int v, int key) { 
  struct MinHeapNode* minHeapNode = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode)); 
  minHeapNode->v = v; 
  minHeapNode->key = key; 
  return minHeapNode; 
} 
  
// A utilit function to create a Min Heap 
struct MinHeap* createMinHeap(int capacity) { 
  struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap)); 
  minHeap->pos = (int*)malloc(capacity * sizeof(int)); 
  minHeap->size = 0; 
  minHeap->capacity = capacity; 
  minHeap->array = (struct MinHeapNode**)malloc(capacity * sizeof(struct MinHeapNode*)); 
  return minHeap; 
} 
  
// A utility function to swap two nodes of min heap. Needed for min heapify 
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) { 
  struct MinHeapNode* t = *a; 
  *a = *b; 
  *b = t; 
} 
  
// A standard function to heapify at given idx 
// This function also updates position of nodes when they are swapped. 
// Position is needed for decreaseKey() 
void minHeapify(struct MinHeap* minHeap, int idx) { 
  int smallest, left, right; 
  smallest = idx; 
  left = 2 * idx + 1; 
  right = 2 * idx + 2; 
  if (left < minHeap->size && minHeap->array[left]->key < minHeap->array[smallest]->key) 
    smallest = left; 
  
  if (right < minHeap->size && minHeap->array[right]->key < minHeap->array[smallest]->key) 
    smallest = right; 
  
  if (smallest != idx) { 
    // The nodes to be swapped in min heap 
    MinHeapNode* smallestNode = minHeap->array[smallest]; 
    MinHeapNode* idxNode = minHeap->array[idx]; 
  
    // Swap positions 
    minHeap->pos[smallestNode->v] = idx; 
    minHeap->pos[idxNode->v] = smallest; 
  
    // Swap nodes 
    swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]); 
  
    minHeapify(minHeap, smallest); 
  } 
} 
  
// A utility function to check if the given minHeap is ampty or not 
int isEmpty(struct MinHeap* minHeap) { 
    return minHeap->size == 0; 
} 
  
// Standard function to extract minimum node from heap 
struct MinHeapNode* extractMin(struct MinHeap* minHeap) { 
  if (isEmpty(minHeap)) 
    return NULL; 
  
  // Store the root node 
  struct MinHeapNode* root = minHeap->array[0]; 
  // Replace root node with last node 
  struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1]; 
  minHeap->array[0] = lastNode; 
  
  // Update position of last node 
  minHeap->pos[root->v] = minHeap->size - 1; 
  minHeap->pos[lastNode->v] = 0; 
  
  // Reduce heap size and heapify root 
  --minHeap->size; 
  minHeapify(minHeap, 0); 
  
  return root; 
} 
  
// Function to decrease key value of a given vertex v. This function 
// uses pos[] of min heap to get the current index of node in min heap 
void decreaseKey(struct MinHeap* minHeap, int v, int key) { 
  // Get the index of v in  heap array 
  int i = minHeap->pos[v]; 
 
  // Get the node and update its key value 
  minHeap->array[i]->key = key; 
  
  // Travel up while the complete tree is not hepified. 
  // This is a O(Logn) loop 
  while (i && minHeap->array[i]->key < minHeap->array[(i - 1) / 2]->key) { 
    // Swap this node with its parent 
    minHeap->pos[minHeap->array[i]->v] = (i - 1) / 2; 
    minHeap->pos[minHeap->array[(i - 1) / 2]->v] = i; 
    swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]); 
  
    // move to parent index 
    i = (i - 1) / 2; 
  } 
} 
  
// A utility function to check if a given vertex 
// 'v' is in min heap or not 
bool isInMinHeap(struct MinHeap* minHeap, int v) { 
  if (minHeap->pos[v] < minHeap->size) 
    return true; 
  return false; 
} 
  
// A utility function used to print the constructed MST 
void printArr(int arr[], int n, float key[]) {
  FILE* output;

  output = fopen("output.txt", "w");

  for (int i = 1; i < n; ++i) {
    if (arr[i] != -1)
      printf("src: %d dst: %d weight: %.4f\n", arr[i], i, key[i]);
      fprintf(output, "%d %d %.4f\n", arr[i], i, key[i]); 
  }
  printf("\n");
} 
  
// The main function that constructs Minimum Spanning Tree (MST) 
// using Prim's algorithm 
void PrimMST(struct Graph* graph) { 
  int V = graph->V; // Get the number of vertices in graph 
  int parent[V]; // Array to store constructed MST 
  float key[V]; // Key values used to pick minimum weight edge in cut 
  // minHeap represents set E 
  struct MinHeap* minHeap = createMinHeap(V); 
  
  // Initialize min heap with all vertices. Key value of 
  // all vertices (except 0th vertex) is initially infinite 
  for (int v = 1; v < V; ++v) { 
    parent[v] = -1; 
    key[v] = INT_MAX; 
      minHeap->array[v] = newMinHeapNode(v, key[v]); 
      minHeap->pos[v] = v; 
  } 
  
  // Make key value of 0th vertex as 0 so that it 
  // is extracted first 
  key[0] = 0; 
  minHeap->array[0] = newMinHeapNode(0, key[0]); 
  minHeap->pos[0] = 0; 
  
  // Initially size of min heap is equal to V 
  minHeap->size = V; 
  
  // In the followin loop, min heap contains all nodes 
  // not yet added to MST. 
  while (!isEmpty(minHeap)) { 
    // Extract the vertex with minimum key value 
    struct MinHeapNode* minHeapNode = extractMin(minHeap); 
    int u = minHeapNode->v; // Store the extracted vertex number 
  
    // Traverse through all adjacent vertices of u (the extracted 
    // vertex) and update their key values 
    struct AdjListNode* pCrawl = graph->array[u].head; 
    while (pCrawl != NULL) { 
      int v = pCrawl->dest; 
  
      // If v is not yet included in MST and weight of u-v is 
      // less than key value of v, then update key value and 
      // parent of v 
      if (isInMinHeap(minHeap, v) && pCrawl->weight < key[v]) { 
        key[v] = pCrawl->weight; 
        parent[v] = u; 
        decreaseKey(minHeap, v, key[v]); 
      } 
      pCrawl = pCrawl->next; 
    } 
  } 
  // print edges of MST
  printArr(parent, V, key);
} 
  
int main() {
  FILE *fileRead;
  int V = 0;
  char str[500];
  int vector1 = 0;
  int vector2 = 0;
  int choice;
  int b = 1;
  float edge;
  
  stopwatch_init();
  struct stopwatch_t* timer = stopwatch_create();
  assert (timer);

  do {
    printf("OPTION: \n1. sparse_100000.txt"
                    "\n2. dense_100000.txt"
                    "\n3. exit"
                    "\n\n Enter one of the options: ");

    scanf("%d", &choice);  
    printf("\n");
  
    switch(choice) {
    case 1:
    { 
      fileRead = fopen("sparse_100000.txt", "r");
      fscanf(fileRead, "%d", &V);

      struct Graph* graph1 = createGraph(V);

      while (fscanf(fileRead, "%d %d %f", &vector1, &vector2, &edge) == 3) {
        //printf("%f\n", edge);
        addEdge(graph1, vector1, vector2, edge);

      }

      stopwatch_start(timer);
      PrimMST(graph1);
      long double t_qs = stopwatch_stop(timer);
      printf("Sparse_100000 takes %Lg seconds\n", t_qs);
      stopwatch_destroy(timer);
      //return 0;
    }
      break;

    case 2:
    {
      fileRead = fopen("dense_100000.txt", "r");
      fscanf(fileRead, "%d", &V);

      struct Graph* graph2 = createGraph(V);

      while (fscanf(fileRead, "%d %d %f", &vector1, &vector2, &edge) == 3) {
        addEdge(graph2, vector1, vector2, edge);
      }
      
      stopwatch_start(timer);
      PrimMST(graph2); 
      long double t_qs = stopwatch_stop(timer);
      printf("Dense_100000 takes %Lg seconds\n", t_qs);
      stopwatch_destroy(timer);
      //return 0;    
    }

      break;
  
    case 3:
    
      b = 2;

      break;

    default:
      printf("Wrong Input. Try Again: ");
  
    }
  } while (b == 1);
}
