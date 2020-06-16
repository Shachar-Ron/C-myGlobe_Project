/*
 * keyValuePAir.c
 *
 *  Created on: Nov 30, 2018
 *      Author: ise
 */

#include  "keyValuePair.h"

typedef struct keyValuePair
{
	Element key;
	Element value;
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
}keyValuePair;

pKeyValuePair createKeyValuePair(Element key, Element value, copyFunction CopyValue, freeFunction FreeValue,
		printFunction PrintValue, transformIntoNumberFunction TransformValue,
		equalFunction EqualValue,copyFunction CopyKey, freeFunction FreeKey,
		printFunction PrintKey, transformIntoNumberFunction TransformKey,
		equalFunction EqualKey)
{
	pKeyValuePair kvp = (pKeyValuePair)malloc(sizeof(keyValuePair));
	if(kvp==NULL)
	{
		printf("no memory available");
		return NULL;
	}
	kvp->copyFuncKey = CopyKey;
	kvp->copyFuncValue = CopyValue;

	kvp->value = kvp->copyFuncValue(value);
	kvp->key = kvp->copyFuncKey(key);

	kvp->EqualFuncValue = EqualValue;
	kvp->PrintFuncValue = PrintValue;
	kvp->TransformFuncValue = TransformValue;
	kvp->freeFuncValue = FreeValue;
	kvp->EqualFuncKey = EqualKey;
	kvp->PrintFuncKey = PrintKey;
	kvp->TransformFuncKey = TransformKey;
	kvp->freeFuncKey = FreeKey;
	return kvp;

}
 status destroyKeyValuePair(pKeyValuePair pkvp)
{
	if(pkvp==NULL)
	{
		return failure;
	}
	if(pkvp->key==NULL)
	{
		return success;
	}

	pkvp->freeFuncKey(pkvp->key);
	pkvp->freeFuncValue(pkvp->value);

	free(pkvp);


	return success;
}
status displayValue(pKeyValuePair pkvp)
 {
	if(pkvp==NULL)
	{
		return failure;
	}
	pkvp->PrintFuncValue(pkvp->value);
	return success;
 }
status displayKey(pKeyValuePair pkvp)
 {
	if(pkvp==NULL)
	{
		return failure;
	}
	pkvp->PrintFuncKey(pkvp->key);
	return success;
 }
Element getValue(pKeyValuePair pkvp)
 {
	if(pkvp==NULL)
	{
		return NULL;
	}
	return pkvp->value;
 }
Element getKey(pKeyValuePair pkvp)
 {
	if(pkvp==NULL)
	{
		return NULL;
	}
	return pkvp->key;
 }
bool isEqualKey (pKeyValuePair pkvp1, pKeyValuePair pkvp2)
{
	if(pkvp1==NULL|| pkvp2==NULL)
	{
		return false;
	}
	return (pkvp1->EqualFuncKey(pkvp1->key, pkvp2->key));

}



Element copyKeyValuePair(Element kvp)
{
    pKeyValuePair newKvp = (pKeyValuePair)kvp;
    newKvp = createKeyValuePair(getKey(kvp),getValue(kvp),newKvp->copyFuncValue,newKvp->freeFuncValue,newKvp->PrintFuncValue,
            newKvp->TransformFuncValue,newKvp->EqualFuncValue,newKvp->copyFuncKey,newKvp->freeFuncKey,newKvp->PrintFuncKey,newKvp->TransformFuncKey,newKvp->EqualFuncKey);
    return (Element)newKvp;
}
status freeKeyValuePair(Element kvp)
{
    return destroyKeyValuePair((pKeyValuePair)kvp);
}
status printKeyValuePair(Element pkvp)
{

    return (displayValue((pKeyValuePair) pkvp));
}
bool compareKey(Element kvp1, Element kvp2)
{
    if(kvp1==NULL||kvp2==NULL)
    {
            return false;
    }
    return(isEqualKey((pKeyValuePair)kvp1,(pKeyValuePair)kvp2));

}
Element getValueAsElement(Element kvp)
{
	if(kvp==NULL)
	{
		return NULL;
	}
	return getValue((pKeyValuePair)kvp);
}















