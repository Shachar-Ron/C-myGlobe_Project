/*
 * main.c
 *
 *  Created on: Dec 4, 2018
 *      Author: ise
 */
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Countries.h"
#include  "HashTable.h"
#include  "keyValuePair.h"
#include "LinkedList.h"
#include "Defs.h"


int main(int argc, char **argv)
{
	int HashNumber = atoi(argv[1]);
	int numberOfCountries = atoi(argv[2]);
		int countriesCounter=0;
		pCountry countries[numberOfCountries];


		char row[300];
		FILE *file;
		char *path =argv[3];
		file = fopen(path,"r");
		if (file == NULL) {
			printf("error opening file");
			return -1;
		}
		while (fgets(row, 300, file) != NULL) {


			if(row[0]!='\t')//if row represent a country
			{

				if(numberOfCountries==countriesCounter)
				{
					break;
				}
				char *countryName = strtok(row,",");
				int x1 = atoi(strtok(NULL, ","));
				int y1 = atoi(strtok(NULL, ","));
				int x2 = atoi(strtok(NULL, ","));
				int y2 = atoi(strtok(NULL, ","));
				pCountry ourCountry = createCountry(countryName, x1,y1, x2, y2);
				countries[countriesCounter]=copyCountry(ourCountry);
				countriesCounter++;
				freeCountry(ourCountry);


			}
			else  //row represent a city
			{
				const char tab[] = "\t";
				char *tmpRow;
				tmpRow = strtok(row,tab);
				char *cityName = strtok(tmpRow,",")	;
				char *favoriteFood = strtok(NULL, ",");
				int residents = atoi(strtok(NULL, ","));
				pCity newCity = createCity(cityName, favoriteFood, residents);
				status result = addCity(countries[countriesCounter-1], newCity);
				if (result == failure) {
					printf("no memory available");
					return -1;
				}

			} //else

	}//while
	fclose(file);


		//// import countries from array to hash-table


	hashTable hasht = createHashTable(copyElementName , freeName, printName,copyCountryAsValue,freeCountryAsValue,
			printCountryAsValue,compCountryName, transformElemnentTonumber, HashNumber);

	for(int i=0;i<numberOfCountries;i++)
	{
		addToHashTable(hasht,getCountryNameAsElement(countries[i]),countries[i]);
	}
	freeWorld(countries,numberOfCountries);

	int choise=0;
	while(choise!=8)
	{
		printMenu();
		scanf("%d", &choise);
		if (choise != 1 && choise != 2 && choise != 3 && choise != 4 && choise != 5 && choise != 6 && choise != 7 && choise != 8)
		{
			printf("please choose a valid number\n");
		}
		switch (choise) {

			case 1:   //print countries
			{
				displayHashElements(hasht);
				break;
			}//case1



			case 2:   //add Country
			{

				printf("please enter a new country name\n");
				char buffer[300];
				scanf("%s", buffer);
				char *countryName = (char*) malloc(sizeof(buffer));
				if (countryName == NULL) {
					printf("no memory available");
					return 0;
				}
				strcpy(countryName,buffer);
				if(lookupInHashTable(hasht,countryName)!=NULL)
				{
					free(countryName);
					printf("country with this name already exist\n");
					break;
				}
				int x1;
				int x2;
				int y1;
				int y2;
				char c1,c2,c3;
				printf("please enter two x and y coordinates :x1,y1,x2,y2\n");
				scanf("%d%c%d%c%d%c%d",&x1,&c1,&y1,&c2,&x2,&c3,&y2);
				pCountry newCountry = createCountry(countryName,x1,y1,x2,y2);
				pCountry ans = copyCountry(newCountry);
				addToHashTable(hasht,getCountryName(ans),ans);
				free(countryName);
				freeCountry(newCountry);

				break;

			}//case2



			case 3:   //add city to country
			{
				printf("please enter a country name\n");
				char buffer[300];
				scanf("%s", buffer);
				char *countryName = (char*) malloc(sizeof(buffer));
				if (countryName == NULL) {
					printf("no memory available");
					return 0;
				}//if
				strcpy(countryName,buffer);
				Element ourNode = lookupInHashTable(hasht,countryName);
				free(countryName);
				if(ourNode==NULL)
				{
					printf("country not exist\n");
					break;
				}//if
				printf("please enter a city name\n");
				char buffer2[300];
				scanf("%s", buffer2);
				char *cityName = (char*) malloc(sizeof(buffer));
				if (cityName == NULL) {
					printf("no memory available");
					return 0;
				}//if
				strcpy(cityName,buffer2);
				int i=0;
				int flag=0;
				for(i=0;i<getNumOfCities(ourNode);i++)
				{
					if(strcmp(getCityName(getCity(ourNode,i)),cityName)==0)
					{
						free(cityName);
						printf("this city already exist in this country\n");
						flag=1;
						break;
					}
				}
				if(flag==1)
				{
					break;
				}
				//enter favorite food
				printf("please enter the city favorite food\n");
				char buffer3[300];
				char *food;
				scanf("%s", buffer3);
				food = (char*) malloc(sizeof(buffer3) + 1);
				if (food == NULL) {
					printf("no memory available");
					return 0;
				}
				strcpy(food, buffer3);

				//enter residents
				printf("please enter number of residents in city\n");
				int residents;
				scanf("%d", &residents);

				pCity newCity = createCity(cityName, food, residents);    //create city
				addCity(ourNode,newCity);

				free(cityName);
				free(food);
				break;

			}//case3




			case 4:   //delete city from country
			{
				printf("please enter a country name\n");
				char buffer[300];
				scanf("%s", buffer);
				char *countryName = (char*) malloc(sizeof(buffer));
				if (countryName == NULL) {
					printf("no memory available");
					return 0;
				}//if
				strcpy(countryName,buffer);
				Element ourNode = lookupInHashTable(hasht,countryName);
				if(ourNode==NULL)
				{
					free(countryName);
					printf("country name not exist\n");
					break;
				}//if
				printf("please enter a city name\n");
				char buffer2[300];
				scanf("%s", buffer2);
				char *cityName = (char*) malloc(sizeof(buffer));
				if (cityName == NULL) {
					printf("no memory available");
					return 0;
				}//if
				strcpy(cityName,buffer2);
				removeCity(ourNode,cityName);
				free(countryName);
				free(cityName);
				break;



			}//case4



			case 5:   //print country by name
			{
				printf("please enter a country name\n");
				char buffer[300];
				scanf("%s", buffer);
				char *countryName = (char*) malloc(sizeof(buffer));
				if (countryName == NULL) {
					printf("no memory available");
					return 0;
				}//if
				strcpy(countryName,buffer);
				Element ourNode = lookupInHashTable(hasht,countryName);
				if(ourNode==NULL)
				{
					printf("country name not exist\n");
					break;
				}//if
				printCountry(ourNode);
				free(countryName);
				break;
			}//case5



			case 6:    //delete country
			{
				printf("please enter a country name\n");
				char buffer[300];
				scanf("%s", buffer);
				char *countryName = (char*) malloc(sizeof(buffer));
				if (countryName == NULL) {
					printf("no memory available");
					return 0;
				}//if
				strcpy(countryName,buffer);
				Element ourNode = lookupInHashTable(hasht,countryName);
				if(ourNode==NULL)
				{
					free(countryName);
					printf("can't delete the country\n");
					break;
				}//if
				if(removeFromHashTable(hasht,countryName)==success)
				{
				printf("country deleted\n");
				}
				else
				{
				printf("can't delete the country\n");
				}
				free(countryName);
				break;

			}//case6




			case 7:    //is country in area
			{
				printf("please enter a country name\n");
				char buffer[300];
				scanf("%s", buffer);
				char *countryName = (char*) malloc(sizeof(buffer));
				if (countryName == NULL) {
					printf("no memory available");
					return 0;
				}//if
				strcpy(countryName,buffer);
				Element ourNode = lookupInHashTable(hasht,countryName);
				if(ourNode==NULL)
				{
					printf("country name not exist\n");
					break;
				}//if
				int x;
				int y;
				char c;
				printf("please enter x and y coordinations:x,y\n");
				scanf("%d%c%d",&x,&c,&y);
				if(checkPoint(ourNode,x,y)==true)
				{
					printf("the coordinate in the country\n");
					break;
				}
				printf("the coordinate not in the country\n");
				free(countryName);
				break;

			}//case7



			case 8:    //exit
			{
				if(destroyHashTable(hasht)==success)
				{
					printf("‫‪all‬‬ ‫‪the‬‬ ‫‪memory‬‬ ‫‪cleaned‬‬ ‫‪and‬‬ ‫‪the‬‬ ‫‪program‬‬ ‫‪is‬‬ ‫‪safely‬‬ ‫‪closed‬‬");
					break;
				}
			}//case8


		}//switch

	}//while
}//main
