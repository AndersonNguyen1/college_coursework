#include <stdio.h>
#include <stdlib.h>
#include "EditDistance.hpp"

struct QueueNode* CreateQueueList(int value);
struct QueueNode* first;
struct QueueNode* last;

void insertHead(int value);
void insertTail(int value);

struct QueueNode  {
  int key;
  struct QueueNode* next;
  struct QueueNode* prev;
};

struct QueueNode* CreateQueueList(int value)  {
  struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
  newNode->key = value;
  newNode->next = NULL;
  newNode->prev = NULL;
  return newNode;
}

void insertHead(int value) {
  if(first == NULL) {
    first = CreateQueueList(value);
    last = first;
  }
  else {
    struct QueueNode* temp = CreateQueueList(value);
    temp->next = first;
    first->prev = temp;
    temp->next = NULL;
    first = temp;
  }
}

void insertTail(int value) {
  if(first == NULL) {
    first = CreateQueueList(value);
    last = first;
  }
  else {
    struct QueueNode* temp = CreateQueueList(value);
    temp->prev = last;
    last->next = temp;
    temp->next = NULL;
    last = temp;
  }
}  

struct QueueNode* firstNode() {
  return first;
}

struct QueueNode* lastNode() {
  return last;
}

void removeNode(struct QueueNode* queuenode) {
  if(first == NULL || queuenode == NULL){
    return;
  }
  else if (queuenode->prev != NULL) {
    queuenode->prev->next = queuenode->next;
  }
  else {
    first = queuenode->next;
  }
  if(queuenode->next != NULL) {
    queuenode->next->prev = queuenode->prev;
  }
}

struct QueueNode* prevNodeGivenNode(struct QueueNode* temp) {
  return temp->prev;
}

struct QueueNode* nextNodeGivenNode(struct QueueNode* temp) {
  return temp->next;
}

struct QueueNode* searchNode(int val) {
  struct QueueNode* temp = firstNode();
  while((temp->next != NULL) && (temp->key != val)) {
    temp = temp->next;
  }
  if(temp->key == val) {
    return temp;
  }
  else {
    return NULL;
  }  
}

int totalCost = 0;
int choice;
string tempChar;

int findMin(int x, int y, int z) {
  if (x <= y && x <= z) return x;
  if (y <= x && y <= z) return y;
  else return z;
}

int editDistance(string str1, string str2, int m, int n) {
  // create new table
  int dynamicProgrammingTable[m + 1][n + 1]; 

  // fills in table with values
  for (int i = 0; i <= m; i++) {
    for (int j = 0; j <= n; j++) {
      if (i == 0) {
        dynamicProgrammingTable[i][j] = j;
      }
      else if (j == 0) {
        dynamicProgrammingTable[i][j] = i;
      }  
      else if (str1[i - 1] == str2[j - 1]) {
        dynamicProgrammingTable[i][j] = dynamicProgrammingTable[i - 1][j - 1];
      }
      else {
        dynamicProgrammingTable[i][j] = 1 + findMin(dynamicProgrammingTable[i][j - 1], dynamicProgrammingTable[i - 1][j], dynamicProgrammingTable[i - 1][j - 1]);
      }
    }
  }
  
  // prints the table so we can see the values
  
  if (choice == 1) {
  for (int b = 0; b <= n; b++) {
    for (int a = 0; a <= m; a++) {
      printf("%d ", dynamicProgrammingTable[a][b]);
    }
    printf("\n");
  }
  printf("\n");
  

  printf("\nOperation\t\t\tz\t\t\tCost\t\tTotal\n\n");
  printf("initial string\t\t\t%s\t\t%d\t\t%d\n", str1.c_str(), 0, totalCost);
  }
  string a = str2; 
  // backtracks through the table from the bottom right corner of the matrix to find the most efficient edit distance path
  // anything that says left means that there is no cost. I put the words delete, insert, replace after RIGHT to indicate the direction/path I'm taking
  for (int c = m; c > 0; c--) {
    for (int d = n; d > 0; d--) {
       if(dynamicProgrammingTable[c][d] > dynamicProgrammingTable[c - 1][d]) {
          totalCost += 2;
          if (choice == 1) {
            tempChar = str1.substr(c-1, 1);
            str1 = str1.erase(c-1, 1);
            printf("delete %s (%d)\t\t\t%s\t\t%d\t\t%d\n", tempChar.c_str(), dynamicProgrammingTable[c - 1][d], str1.c_str(), 2, totalCost);
          }
          c--;
          d++;
        }
        else if(dynamicProgrammingTable[c][d] > dynamicProgrammingTable[c][d - 1]) {
          totalCost += 3;
          c++;
          if (choice == 1) {
            tempChar = str2.substr(d-1, 1);
            str1 = str1.replace(c-1, 1, str2.substr(d-1,1));
            str2 = str2.erase(d-1,1);
            printf("insert %s (%d)\t\t\t%s\t\t%d\t\t%d\n", tempChar.c_str(), dynamicProgrammingTable[c][d - 1], str1.c_str(), 3, totalCost);
          }
          //c--;
        }
        else if(dynamicProgrammingTable[c][d] > dynamicProgrammingTable[c - 1][d - 1]) {
          totalCost += 4;
          if (choice == 1) {
            tempChar = str2.substr(d-1, 1);
            str1 = str1.replace(c-1, 1, str2.substr(d-1,1));
            str2 = str2.erase(d-1,1);
            printf("replace by %s (%d)\t\t%s\t\t%d\t\t%d\n", tempChar.c_str(), dynamicProgrammingTable[c - 1][d - 1], str1.c_str(), 4, totalCost);
          }
          c--;
        }
        else if(dynamicProgrammingTable[c][d] == dynamicProgrammingTable[c - 1][d]) {
          if (choice == 1) {
            str1 = str1.erase(c-1, 1);
            printf("left del (%d)\t\t\t%s\t\t%d\t\t%d\n", dynamicProgrammingTable[c - 1][d], str1.c_str(), 0, totalCost);
          }
          c--;
          d++;
        }  
        else if(dynamicProgrammingTable[c][d] == dynamicProgrammingTable[c][d - 1]) {
          if (choice == 1) {
           // str1 = str1.erase(c-1, 1);
            printf("left ins (%d)\t\t\t%s\t\t%d\t\t%d\n", dynamicProgrammingTable[c][d - 1], str1.c_str(), 0, totalCost);
          }
          //c--;
        } 
        else {
          if (choice == 1) {
            //str1 = str1.erase(c-1, 1);
            printf("left rep (%d)\t\t\t%s\t\t%d\t\t%d\n", dynamicProgrammingTable[c - 1][d - 1], str1.c_str(), 0, totalCost);
          }
          c--;
        }  
    }
  }
  if (choice == 1) {
    printf("output \t\t\t\t%s\n", a.c_str());
  }  
  return dynamicProgrammingTable[m][n];
}

int main() {
  string str1;
  string str2;
  int b = 1;
  int ed;

  do {
    totalCost = 0;
    printf("OPTIONS: \n 1. ED of EE and CS"
                    "\n 2. input1.txt"
                    "\n 3. input2.txt"
                    "\n 4. input3.txt"
                    "\n 5. exit"
                    "\n\n Enter one of the options: ");

    scanf("%d", &choice);
    //printf("\n");

    switch(choice) {
      case 1:
      {
        string str1 = "electrical engineering";
        string str2 = "computer science";

        int ed = editDistance(str1, str2, str1.length(), str2.length());
        printf("\nEdit Distance: %d\t Total Cost: %d\n\n", ed, totalCost);
      }
      break;

      case 2:
      {
        static const char filename[] = "input1.txt";
        FILE *file = fopen(filename, "r");
        int count = 0;
        if (file != NULL) {
          char line[1000];
          while (fgets(line, sizeof line, file) != NULL) {
            if (count == 0) {
              count++;
              str1 = fgets(line, sizeof line, file);
            }
            else if (count == 1) {
              count++;
              str2 = fgets(line, sizeof line, file);
            }
            else 
              count++;
          }
          fclose(file);
        }

        int ed = editDistance(str1, str2, str1.length(), str2.length());
        printf("\nEdit Distance: %d\t Total Cost: %d\n\n", ed, totalCost);
      }
      break;

      case 3:
      {
        static const char filename[] = "input2.txt";
        FILE *file = fopen(filename, "r");
        int count = 0;
        if (file != NULL) {
          char line[1000];
          while (fgets(line, sizeof line, file) != NULL) {
            if (count == 0) {
              count++;
              str1 = fgets(line, sizeof line, file);
            }
            else if (count == 1) {
              count++;
              str2 = fgets(line, sizeof line, file);
            }
            else
              count++;
          }
          fclose(file);
        }
        int ed = editDistance(str1, str2, str1.length(), str2.length());
        printf("\nEdit Distance: %d\t Total Cost: %d\n\n", ed, totalCost);
      }
      break;

      case 4:
      {
        static const char filename[] = "input3.txt";
        FILE *file = fopen(filename, "r");
        int count = 0;
        if (file != NULL) {
          char line[1000];
          while (fgets(line, sizeof line, file) != NULL) {
            if (count == 0) {
              count++;
              str1 =fgets(line, sizeof line, file);
            }
            else if (count == 1) {
              count++;
              str2 = fgets(line, sizeof line, file);
            }
            else
              count++;
          }
          fclose(file);
        }
        int ed = editDistance(str1, str2, str1.length(), str2.length());
        printf("\nEdit Distance: %d\t Total Cost: %d\n\n", ed, totalCost);
      }
      break;

      case 5:
      {
        b = 2;
      }
      break;

      default:
        printf("Wrong Input. Try Again: ");
    } 
  } while (b == 1);
}
