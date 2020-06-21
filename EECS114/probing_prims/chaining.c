#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct node {
	int key;
	int value;
	struct node *next;
};
 
/* For storing a Linked List at each index of Hash Table  */
struct arrayitem {
	struct node *head;   
	struct node *tail;   
};
 
struct arrayitem *array;
int size = 0;
int htSize;
 
// finds the given key in LL and returns index, return -1 if key DNE
int find(struct node *list, int key) {
	int retval = 0;
	struct node *temp = list;
	while (temp != NULL) {
		if (temp->key == key) {
			return retval;
		}
    temp = temp->next;
		retval++;
	}
	return -1;
}

float boundedRandVal() {
  int lower = 0;
  int upper = 100000;
  float boundedRandVal;
  return boundedRandVal = (rand() % (upper - lower + 1)) + lower;
}

struct node* get_element(struct node *list, int find_index);
void remove_element(int key);
void rehash();
void createArray();
 
void insert(int key, int value) {
  float n = 0.0;     
	/* n => Load Factor, keeps check on whether rehashing is required or not */
 
  int index = key;
 
	/* Extracting Linked List at a given index */
	struct node *list = (struct node*) array[index].head;
 
	/* Creating an item to insert in the Hash Table */
	struct node *item = (struct node*) malloc(sizeof(struct node));
	item->key = key;
	item->value = value;
	item->next = NULL;
 
	if (list == NULL) {
		/* Absence of Linked List at a given Index of Hash Table */
 
		printf("Inserting %d(key) and %d(value) \n", key, value);
		array[index].head = item;
		array[index].tail = item;
	}
  else {
		/* A Linked List is present at given index of Hash Table */
		int find_index = find(list, key); 
		if (find_index == -1) {
			//Key not found in existing linked list 
      //Adding the key at the end of the linked list
 
			array[index].tail->next = item;
			array[index].tail = item;
		}
    else {
			// key inside linked list
			// update the value of the existing key
 
			struct node *element = get_element(list, find_index);
			element->value = value;
		}
	}
	//Calculating Load factor
	n = (1.0 * size) / htSize;
	if (n >= 0.75) {
		//rehashing
		printf("going to rehash\n");
		rehash();
	}
}
 
void rehash()
{
	struct arrayitem *temp = array;     
	/* temp pointing to the current Hash Table array */
 
	int i = 0, n = htSize;
	size = 0;
	htSize = 2 * htSize;
 
	/*
	 *array variable is assigned with newly created Hash Table
	 *with double of previous array size
	*/
	array = (struct arrayitem*) malloc(htSize * sizeof(struct node));
	createArray();
 
	for (i = 0; i < n; i++) {
		/* Extracting the Linked List at position i of Hash Table array */
 		struct node* list = (struct node*) temp[i].head;
 
		if (list == NULL) {
			/* if there is no Linked List, then continue */
			continue;
		}
    else {
			/*
			 *Presence of Linked List at i
			 *Keep moving and accessing the Linked List item until the end.
			 *Get one key and value at a time and add it to new Hash Table array.
			*/
 
	    while (list != NULL) {
      insert(list->key, list->value);
		  list = list->next;
	    }
		}
	}
	temp = NULL;
}

/* Returns the node (Linked List item) located at given find_index  */
struct node* get_element(struct node *list, int find_index)
{
	int i = 0;
	struct node *temp = list;
	while (i != find_index) 
        {
		temp = temp->next;
		i++;
	}
	return temp;
}
 
/* To remove an element from Hash Table */ 
void search(int key)
{
  int index = key;
	struct node *list = (struct node*) array[index].head;
 
	if (list == NULL) {
		printf("This key does not exists\n");
	}
  else {
		int find_index = find(list, key);
  
		if (find_index == -1) {
			printf("This key does not exists\n");
		}
    else {
 			struct node *temp = list;
			if (temp->key == key) { 
  		  //array[index].head = temp->next;
				printf("This key (%d) has been found\n", index);
				return;
			}
 
			while (temp->next->key != key) {
 				temp = temp->next;
			}

  		if (array[index].tail == temp->next) {
				temp->next = NULL;
				array[index].tail = temp;
			}
      else {
				temp->next = temp->next->next;
			}
			printf("This key has been removed\n");
		}
	}
}
 
/* To display the contents of Hash Table */
void display() {
	int i = 0;
	for (i = 0; i < htSize; i++) {
		struct node *temp = array[i].head;
		if (temp == NULL) {
			printf("array[%d] has no elements\n", i);
		}
    else           {
			printf("array[%d]: ", i);
			while (temp != NULL) {
				printf("key= %d  value= %d\t", temp->key, temp->value);
				temp = temp->next;
			}
			printf("\n");
		}
	}
}
 
/* For initializing the Hash Table */
void createArray() {
	for (int i = 0; i < htSize; i++) {
		array[i].head = NULL;
    array[i].tail = NULL;
	}
}
 
void main() {
  printf("What size do you want your hash table to be? ");
  scanf("%d", &htSize);

	int choice, key, value, n;
  int b = 1;
 
	array = (struct arrayitem*) malloc(htSize * sizeof(struct arrayitem*));
	createArray();
 
	do {
		printf("\nChaining with Singly Linked List \n\n");
		printf("OPTIONS: \n1. Insert"
 
                              "\n2. Search" 
                              "\n3. Display"
                              "\n4. Exit"
		       "\n\n Enter your choice: ");
    scanf("%d", &choice);

		switch(choice) {
 
		case 1:

      for (int i = 0; i < htSize; i++) {
        printf("Inserting element into ht\n");
        float a = 0.6180339887;
        float r = boundedRandVal();
        float armod1 = fmod((a * r), 1);
        int key1 = floor(htSize * armod1);
		    
		    insert(key1, r);
      }
 
		  break;
 
		case 2:
      
      printf("Search Element \n");
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

		  b = 2;
		  break;
 
		default:
 
		  printf("Wrong Input\n");
 
		}
	} while(b == 1);
}
