#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Defs.h"

typedef struct node* pNode;
typedef struct Linkedlist* pLinkedlist;


pLinkedlist createLinkedList(copyFunction Copy, freeFunction Free,printFunction Print,equalFunction Equal);
status appendNode(pLinkedlist List, Element toAddValue);
status deleteNode(pLinkedlist List, Element value);
status destroyList(pLinkedlist ListToRemove);
status displayList (pLinkedlist List);
Element searchInList(pLinkedlist list, Element node);
int getNUmOfElements(pLinkedlist list);

