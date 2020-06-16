/*
 * keyValuePair.h
 *
 *  Created on: Nov 30, 2018
 *      Author: ise
 */

#ifndef KEYVALUEPAIR_H_
#define KEYVALUEPAIR_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Defs.h"

typedef struct keyValuePair* pKeyValuePair;

pKeyValuePair createKeyValuePair(Element key,Element value, copyFunction CopyValue, freeFunction FreeValue,
		printFunction PrintValue, transformIntoNumberFunction TransformValue,
		equalFunction EqualValue,copyFunction CopyKey, freeFunction FreeKey,
		printFunction PrintKey, transformIntoNumberFunction TransformKey,
		equalFunction EqualKey);
status destroyKeyValuePair(pKeyValuePair pkvp);
status displayValue(pKeyValuePair pkvp);
status displayKey(pKeyValuePair pkvp);
Element getValue(pKeyValuePair pkvp);
Element getKey(pKeyValuePair pkvp);


status freeKeyValuePair(Element kvp);
Element copyKeyValuePair(Element kvp);
status printKeyValuePair(Element pkvp);
bool isEqualKey (pKeyValuePair pkvp1, pKeyValuePair pkvp2);
bool compareKey(Element kvp1, Element kvp2);
Element getValueAsElement(Element kvp);



#endif /* KEYVALUEPAIR_H_ */
