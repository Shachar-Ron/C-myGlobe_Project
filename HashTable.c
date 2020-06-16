/*
 * HashTable.c
 *
 *  Created on: Nov 30, 2018
 *      Author: ise
 */


#include  "HashTable.h"
#include  "keyValuePair.h"
#include "LinkedList.h"



struct hashTable_s
{

	int hashNumber;
	pLinkedlist *llArray;
	copyFunction copyFuncKey;
	freeFunction freeFuncKey;
	printFunction PrintFuncKey;
	transformIntoNumberFunction TransformFuncKey;
	equalFunction EqualFuncKey;
	copyFunction copyFuncValue;
	freeFunction freeFuncValue;
	printFunction PrintFuncValue;
	transformIntoNumberFunction TransformFuncValue;
	equalFunction EqualFuncValue;

}hashTable_s;


hashTable createHashTable(copyFunction copyKey, freeFunction freeKey, printFunction printKey,
		copyFunction copyValue, freeFunction freeValue, printFunction printValue,
		equalFunction equalKey, transformIntoNumberFunction transformKeyIntoNumber, int hashNumber)
{
	hashTable hasht =(hashTable)malloc(sizeof(hashTable_s));
	if (hasht == NULL) {
			printf("No memory available");
			return NULL;
	}
	if(copyKey==NULL|| freeKey==NULL || printKey==NULL ||copyValue==NULL||freeValue==NULL || printValue==NULL||equalKey==NULL||transformKeyIntoNumber==NULL)
	{
		return NULL;
	}


	hasht->hashNumber = hashNumber;
	hasht->copyFuncKey = copyKey;
	hasht->freeFuncKey = freeKey;
	hasht->PrintFuncKey = printKey;
	hasht->copyFuncValue = copyValue;
	hasht->freeFuncValue = freeValue;
	hasht->PrintFuncValue = printValue;
	hasht->EqualFuncKey = equalKey;
	hasht->TransformFuncKey = transformKeyIntoNumber;

	hasht->llArray = (pLinkedlist*)malloc(sizeof(pLinkedlist)*hashNumber);
	if(hasht->llArray==NULL)
	{
		printf("No memory available");
		free(hasht);
		return NULL;
	}


	int i=0;
	for(i=0;i<hashNumber;i++)
	{
		hasht->llArray[i] = createLinkedList(copyKeyValuePair,freeKeyValuePair,printKeyValuePair,compareKey);
	}

	return hasht;
}


status destroyHashTable(hashTable hashtable)
{
	if(hashtable==NULL)
	{
		return failure;
	}
	int size = hashtable->hashNumber;
	int i=0;
	for(i=0;i<size;i++)
	{
		if(hashtable->llArray[i]!=NULL)
		{
			if(destroyList(hashtable->llArray[i])==failure)
			{
				return failure;
			}
		}

	}
	free(hashtable->llArray);
	free(hashtable);
	return success;
}

status addToHashTable(hashTable hasht, Element key,Element value)
{
	if(hasht==NULL||key==NULL||value==NULL)
	{
		return failure;
	}
	pKeyValuePair pkvp = createKeyValuePair(key,value,hasht->copyFuncValue, hasht->freeFuncValue,hasht->PrintFuncValue,hasht->TransformFuncValue,
			hasht->EqualFuncValue,hasht->copyFuncKey, hasht->freeFuncKey,hasht->PrintFuncKey,
			hasht->TransformFuncKey,hasht->EqualFuncKey);
	if(pkvp==NULL)
	{
		return failure;
	}

	int asciValue = hasht->TransformFuncKey(key);
	int index = asciValue%hasht->hashNumber;
	if( appendNode(hasht->llArray[index],pkvp)==failure)
	{

		return failure;
	}
	destroyKeyValuePair(pkvp);
	//free(pkvp);
	return success;


}

Element lookupInHashTable(hashTable hasht, Element key)
{
	if(hasht==NULL||key==NULL)
	{
			return NULL;
	}
	Element hairy = NULL;
	pKeyValuePair pkvp = createKeyValuePair(key,hairy,hasht->copyFuncValue, hasht->freeFuncValue,hasht->PrintFuncValue,hasht->TransformFuncValue,
			hasht->EqualFuncValue,hasht->copyFuncKey, hasht->freeFuncKey,hasht->PrintFuncKey,
			hasht->TransformFuncKey,hasht->EqualFuncKey);
	if(pkvp==NULL)
	{
		return failure;
	}

	int hasci = (hasht->TransformFuncKey(key));
	int index = hasci%(hasht->hashNumber);
	Element element = searchInList(hasht->llArray[index],pkvp);
	if(element==NULL)
	{
		destroyKeyValuePair(pkvp);
		//free(pkvp);
		return NULL;
	}

	destroyKeyValuePair(pkvp);
	//free(pkvp);
	return getValue(element);

}
status removeFromHashTable(hashTable hasht, Element key)
{
	if(hasht==NULL||key==NULL)
	{
		return failure;
	}
	pKeyValuePair pkvp = createKeyValuePair(key,NULL,hasht->copyFuncValue, hasht->freeFuncValue,hasht->PrintFuncValue,hasht->TransformFuncValue,
		hasht->EqualFuncValue,hasht->copyFuncKey, hasht->freeFuncKey,hasht->PrintFuncKey,
		hasht->TransformFuncKey,hasht->EqualFuncKey);


	int hasci = (hasht->TransformFuncKey(key));
	int index = hasci%(hasht->hashNumber);

	if(deleteNode(hasht->llArray[index],pkvp)==failure)
	{
		destroyKeyValuePair(pkvp);
		return failure;
	}
	destroyKeyValuePair(pkvp);
	//free(pkvp);
	return success;


}
status displayHashElements(hashTable hasht)
{
	if(hasht == NULL)
	{
		return failure;
	}
	int i=0;
	for(i=0;i<hasht->hashNumber;i++)
	{
		displayList(hasht->llArray[i]);
	}
	return success;

}


