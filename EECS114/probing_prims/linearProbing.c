#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
/* elements have value and key */
struct elements {
  int key;
  int value;
};
 
/* each hash table element has a flag and data, which contain a key and value */
struct hashtableElements {
  int flag;
  /*
   * flag = 0 : data does not exist
   * flag = 1 : data exists
  */
 
    struct elements *data;
};
 
struct hashtableElements *array;
int htSize;
int reprobeCountInsert = 0;
float totalReprobeCountInsert = 0;
float avgReprobeCountInsert;

int reprobeCountSearch = 0;
float totalReprobeCountSearch = 0;
float avgReprobeCountSearch = 0;

/* initializing hash table array */
void init_array() {
  int i;
  for (i = 0; i < htSize; i++) 
  {
	  array[i].flag = 0;
	  array[i].data = NULL;
  }
}

// generates random value between the lower and upper limit
float boundedRandVal() {
  int lower = 0;
  int upper = 100000;
  float boundedRandVal;
  return boundedRandVal = (rand() % (upper - lower + 1)) + lower;
}
 
/* to insert an element in the hash table */
void insert(int key, int value) {
  int index = key;
  int keyIndex = index;
 
  /* creating new element to insert in the hash table array */
  struct elements *newElement = (struct elements*) malloc(sizeof(struct elements));
  newElement->key = keyIndex;
  newElement->value = value;
 
  /* probing through the array until we reach an empty space */
  while (array[keyIndex].flag == 1) {  
	  keyIndex = (keyIndex + 1) % htSize;
    //printf("\n\n\ni: %d index:%d\n\n\n", i, index);
	  if (keyIndex == index) {
		  printf("\nHash table is full, cannot insert any more elements \n\n");
	    return;
	  }
    reprobeCountInsert++;
  }
  newElement->key = keyIndex;
  array[keyIndex].flag = 1;
  array[keyIndex].data = newElement;
  totalReprobeCountInsert += reprobeCountInsert;
  avgReprobeCountInsert = totalReprobeCountInsert/htSize;

  printf("\nKey (%d) has been inserted with Value (%d) with (%d) Reprobes \n", keyIndex, value, reprobeCountInsert);
  printf("Total # Reprobes: %.02f\nAverage # Reprobes: %0.2f\n\n", totalReprobeCountInsert, avgReprobeCountInsert);
  reprobeCountInsert = 0;;
}

void search(int key) {
  int index = key;
  int i = index;
  array[i].flag = 0;
  while (array[i].flag == 0) {
    if (array[i].data->key == key) {
      array[i].flag = 1;
      break;
    }
    else {
      reprobeCountSearch++;
      totalReprobeCountSearch += reprobeCountSearch;
    }
  } 

  while (array[i].flag != 0) {
    if (array[i].flag == 1 && array[i].data->key == key) {
      array[i].flag = 2;
      
      avgReprobeCountSearch = totalReprobeCountSearch/htSize;
      printf("\n Key (%d) has been found and has a Value (%d) with (%d) Reprobes \n", array[i].data->key, array[i].data->value, reprobeCountSearch);
      printf("Total # Reprobes: %.02f\nAverage # Reprobes: %.2f\n\n", totalReprobeCountSearch, avgReprobeCountSearch);
      reprobeCountSearch = 0;
   //   totalReprobeCountSearch = 0;
      return;
    }
    //totalReprobeCountSearch += reprobeCountSearch;
    //printf("total: %d count: %d",totalReprobeCountSearch, reprobeCountSearch);
    //avgReprobeCountSearch = totalReprobeCountSearch/htSize;
    //printf("\n Key (%d) has been found and has a Value (%d) with (%d) Reprobes \n", array[i].data->key, array[i].data->value, reprobeCountSearch);
    //printf("# Reprobes: %.02f\nAverage # Reprobes: %.2f\n\n", totalReprobeCountSearch, avgReprobeCountSearch);
    
    reprobeCountSearch = 0;
    i = (i + 1) % htSize;
    if (i == index) {
      break;
    }
  }
  printf("\n (%d) key DNE\n", key);
}

void display() {
  for (int i = 0; i < htSize;i++) {
    struct elements *current = (struct elements*) array[i].data;
    if (current == NULL) {
      printf("\n Array[%d} has no elements \n",i);
    }
    else {
      printf("\n Array[%d] has elements: %d (key) and %d(value) ", i, current->key, current->value);
    }
    printf("\n");
  }
}
 
void main() {
  printf("\nEnter the size of your hash table: ");
  scanf("%d", &htSize);
  printf("\n");

	int option, key, value, n;
  int b = 1;
  float percent = 0.0;
 
	array = (struct hashtableElements*) malloc(htSize * sizeof(struct hashtableElements*));
	init_array();
 
	do {
		printf("OPTIONS: \n1. Insert"
                     "\n2. Search"
                     "\n3. Display"
                     "\n4. Exit"
		                 "\n\nPlease enter one of the options: ");
 
		scanf("%d", &option);
    printf("\n"); 

		switch(option) {
    
		case 1:
          //printf("What percentage of the hash table do you want to fill? (Example (0.64 is 64%))");
          //scanf("%d", &percent);
          for (int i = 0; i < htSize; i++) {
            printf("Inserting element in HashTable\n"); 
            //if (i < floor(htSize * percent)) {
		        float a = 0.6180339887;
            //float a = .01;
            float r = boundedRandVal();
            float s = boundedRandVal();
            float armod1 = fmod((a * s), 1);
            int key1 = floor(htSize * armod1);
		        insert(key1, r);
           // }
          }
 
		      break;
  
    case 2:
      
      //printf("Which key do you want to search? ");
      //scanf("%d", &key);
      printf("Searching element in HashTable(\n");
      float y = 0.6180339887;
      float z = boundedRandVal();
      float yzmod1 = fmod((y * z), 1);
      int key2 = floor(htSize * yzmod1);
      search(key2);
      break;

    case 3:
      
      display();
      break;

    case 4:

      b = 0;
      break;

		default:   
		  printf("Wrong Input\n\n");
		
    }
	} while(b == 1);
}
