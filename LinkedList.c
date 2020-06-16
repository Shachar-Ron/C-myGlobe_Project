#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Defs.h"
#include "LinkedList.h"


struct node {
	Element value;
	pNode next;
}node;

struct Linkedlist {

	int NumOfElements;
	pNode head;
	pNode tail;
	copyFunction copyFunc;
	freeFunction freeFunc;
	printFunction PrintFunc;
	equalFunction EqualFunc;
}Linkedlist;


pLinkedlist createLinkedList(copyFunction Copy, freeFunction Free,
		printFunction Print,
		equalFunction Equal)
	{

	pLinkedlist newList = (pLinkedlist) malloc(sizeof(Linkedlist));
	if (newList == NULL) {
		printf("No memory available");
		return NULL;
	}
	newList->head = (pNode)NULL;
	newList->tail = (pNode)NULL;

	if(Copy==NULL||Free==NULL||Print==NULL||Equal==NULL)
	{
		return NULL;
	}

	newList->NumOfElements = 0;
	newList->copyFunc = Copy;
	newList->freeFunc = Free;
	newList->PrintFunc = Print;
	newList->EqualFunc = Equal;
	newList->head=NULL;
	newList->tail=NULL;
	return newList;
}

status destroyList(pLinkedlist ListToRemove) {
	if(ListToRemove==NULL)
	{
		return failure;
	}
	if(ListToRemove->head==NULL)
	{
		free(ListToRemove);
		ListToRemove=NULL;
		return success;
	}
	pNode current=  ListToRemove->head;
	pNode keeper;
	while(current->next!=NULL)
	{
		keeper=current;
		deleteNode(ListToRemove, current->value);
		current = current->next;
		free(keeper);

	}
	deleteNode(ListToRemove, current->value);
	free(current);
	free(ListToRemove);

	ListToRemove=NULL;
	return success;
}

status appendNode(pLinkedlist List, Element toAddValue) {
	if(List==NULL||toAddValue==NULL)
	{
		return failure;
	}
	pNode newNode = (pNode) malloc(sizeof(node));
	if (newNode == NULL) {
		printf("No memory available");
		return failure;
	}

	newNode->value = List->copyFunc(toAddValue);
	newNode->next=NULL;
	int x = getNUmOfElements(List);
	if(x==0)
	{
		List->head=newNode;
		List->tail=newNode;
		List->NumOfElements++;
	}
	else
	{
		List->tail->next=newNode;
		List->tail=newNode;
		List->NumOfElements++;
	}
	//free(newNode);
	return success;
}

status deleteNode(pLinkedlist List, Element value) {
	if(List->head==NULL)
	{
		return failure;
	}
		if(List->NumOfElements==1)
		{
			List->freeFunc((Element)List->head->value);
			List->NumOfElements=0;
			List->head=NULL;
			List->tail=NULL;
			return success;
		}
		else
		{
			pNode current= List->head;
			if(List->EqualFunc(current->value,value)==true)
			{
				List->freeFunc(current->value);
				List->head = current->next;
				List->NumOfElements--;
				return success;
			}
			while(current->next!=NULL)
			{

				if(List->EqualFunc(current->next->value,value)==true)
				{

					List->freeFunc(current->next->value);
					current->next=current->next->next;
					List->NumOfElements--;
					return success;
				}
				current=current->next;
			}
			if(List->EqualFunc(current->value,value)==true)
			{
				List->freeFunc(current->value);
				List->NumOfElements--;
			}

		}

	free(value);
	printf("element is not in list\n");
	return failure;

}


status displayList (pLinkedlist List)
{
	if(List->head==NULL)
	{
		return failure;
	}
	if(List->NumOfElements==1)
	{
		List->PrintFunc(List->head->value);
		return success;
	}
	pNode current= List->head;
	while(current->next!=NULL)
	{
		List->PrintFunc(current->value);
		current=current->next;
	}
	List->PrintFunc(current->value);
	return success;
}

Element searchInList(pLinkedlist list, Element node)
{

	if(list->head==NULL||node==NULL)
	{
		return NULL;
	}
	if(list->NumOfElements==1)
	{
		if(list->EqualFunc(list->head->value,node)==true)
		{
			return list->head->value;
		}
		return NULL;
	}
	pNode current= list->head;
		while(current->next!=NULL)
		{
			if(list->EqualFunc(current->value,node)==true)
			{
				return current->value;
			}
			current=current->next;
		}
		if(list->EqualFunc(current->value,node)==true)
		{
			return current->value;
		}
		return NULL;
}


int getNUmOfElements(pLinkedlist list)
{
	if(list==NULL)
	{
		return -1;
	}
	return list->NumOfElements;
}








