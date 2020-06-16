
#ifndef COUNTRY
#define COUNTRY
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Defs.h"


//typedef  enum e_bool { true,false } bool;
//typedef enum e_status{success,failure}status;


typedef struct Country* pCountry;
typedef struct City* pCity;
typedef struct Area* pArea;



pCountry createCountry(char *name1 , int x1 , int y1, int x2, int y2);
status addCity(pCountry Country, pCity City);
status removeCity (pCountry Country, char *cityName);
bool checkPoint (pCountry country ,int x ,int y);
status freeCountry (pCountry Country);
pCountry copyCountry(pCountry Country);
status printCountry(pCountry country);


void printMenu();
pCity createCity(char *cityName,char *favoriteFood,int residents);

char* getCountryName(pCountry Country);
int getNumOfCities(pCountry country);
char* getCityName(pCity city);
pCity getCity( pCountry country,int index);
void setCity(pCountry country,int i, pCity city);
pCity* getCityArray( pCountry country);
void freeArea(pCountry Country);

bool equalCountryName(pCountry country1,pCountry country2);
int transforNameIntoNumber(pCountry country);

Element copyElementName(Element element);
status freeCountryName(pCountry Country);
status printName(Element element);
status freeName(Element element);
Element copyCountryAsValue(Element element);
status freeCountryAsValue(Element element);
status printCountryAsValue(Element element);
bool compCountryName(Element element1, Element element2);
Element getCountryNameAsElement(Element element);
int transformElemnentTonumber(Element name);


void freeWorld(pCountry* countries, int numOfCountries);
#endif
