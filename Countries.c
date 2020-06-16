#include "Countries.h"

typedef struct Area {
	int x1;
	int y1;
	int x2;
	int y2;
} area;

typedef struct City {
	char *cityName;
	char *favoriteFood;
	int residents;

} city;

typedef struct Country {

	int citiesNumber;
	char *name;
	area *area;
	city **city;

} country;

//create new country
pCountry createCountry(char *name1, int x1, int y1, int x2, int y2) {

	if(name1==NULL||x1<0||y1<0||x2<0||y2<0)
	{
		return NULL;
	}


	pCountry newCountry;
	newCountry = (pCountry) malloc(sizeof(country));
	if (newCountry == NULL) {
		printf("no memory available");
		return NULL;
	}

	newCountry->name = (char*) malloc(strlen(name1) + 1);
	strcpy(newCountry->name, name1);
	if (newCountry->name == NULL) {
		printf("no memory available");
		return NULL;
	}

	newCountry->area = (pArea) malloc(sizeof(area));
	if (newCountry->area == NULL) {
		printf("no memory available");
		return NULL;
	}

	newCountry->area->x1 = x1;
	newCountry->area->y1 = y1;
	newCountry->area->x2 = x2;
	newCountry->area->y2 = y2;

	newCountry->citiesNumber = 0;
	return newCountry;

}

// add city to country
status addCity(pCountry Country, pCity City) {
	if (Country == NULL || City == NULL) {
		return failure;
	}
	//check if city is in the country.
	int i;
	for (i = 0; i < Country->citiesNumber; i++)
	{
		if (strcmp(Country->city[i]->cityName, City->cityName) == 0) {
			return failure;
	}

	}
	//in case there are no cities yet for the country.
	if (Country->citiesNumber == 0) {
		Country->city = (pCity*) malloc(sizeof(pCity));
	}
	//in case there are cities in the country.
	else {
		Country->city = (pCity*) realloc(Country->city,
		(Country->citiesNumber + 1) * sizeof(pCity));
	}

	if (Country->city == NULL) {
		printf("no memory available");
		return failure;
	} else {

		Country->city[Country->citiesNumber] = City;


		Country->citiesNumber++;
		return success;
	}

}

//remove city from country
status removeCity(pCountry Country, char *cityName) {
	int flag = 0;
	int keeper;
	if (Country == NULL || Country->citiesNumber==0 || Country->city == NULL ||  cityName == NULL) {
		printf("the city not exist in this country\n");
		return failure;
	}

	int i;
	for (i = 0; i < Country->citiesNumber; i++) {
		if (strcmp(Country->city[i]->cityName, cityName) == 0) {
			flag = 1;
			keeper = i;
			break;
		}

	}
	if (flag == 0) {
		printf("the city not exist in this country\n");
		return failure;

	}

	free(Country->city[keeper]->cityName);
	free(Country->city[keeper]->favoriteFood);
	free(Country->city[keeper]);

	if (Country->citiesNumber == 1) {
		free(Country->city);
		Country->citiesNumber--;
	} else {

		Country->city[keeper] = Country->city[Country->citiesNumber - 1];
		Country->citiesNumber--;
	}
	return success;
}

bool checkPoint(pCountry country, int x, int y) {
	if(country==NULL)
	{
		return 0;


	}
	if(x<0||y<0)
	{
		return false;
	}
	if ((country->area->x1 < x) && (country->area->x2 > x)
			&& (country->area->y1) > y && (country->area->y2 < y)) {
		return true;
	}
	return false;
}

status freeCountry(pCountry Country) {

	if (Country == NULL) {
		return failure;
	}
	int tempCityNumber = Country->citiesNumber;
	int i;
	for (i = 0; i < tempCityNumber; i++) {
		removeCity(Country,Country->city[i]->cityName);
	}
	freeCountryName(Country);
	freeArea(Country);
	free(Country);
	return success;
}

pCountry copyCountry(pCountry Country) {



	if (Country == NULL) {
		return NULL;
	}


	pCountry newCopyCountry;
	newCopyCountry = (pCountry) malloc(sizeof(country));
	if (newCopyCountry == NULL) {
		printf("no memory available");
		return NULL;
	}
	//copy name
	newCopyCountry->name = (char*) malloc(strlen(Country->name) + 1);
	if (newCopyCountry->name == NULL) {
		printf("no memory available");
		return NULL;
	}
	strcpy(newCopyCountry->name, Country->name);

	//copy citiesNumber
	newCopyCountry->citiesNumber = Country->citiesNumber;

	//copy area
	newCopyCountry->area = (pArea) malloc(sizeof(area));
	if (newCopyCountry->area == NULL) {
		printf("no memory available");
		return NULL;
	}

	newCopyCountry->area->x1 = Country->area->x1;
	newCopyCountry->area->y1 = Country->area->y1;
	newCopyCountry->area->x2 = Country->area->x2;
	newCopyCountry->area->y2 = Country->area->y2;


	if (Country->citiesNumber > 0) {


		pCity* tempCityArray = (pCity*) malloc(sizeof(city)*Country->citiesNumber);
		int i;
		for (i = 0; i < Country->citiesNumber; i++) {

			pCity tempCity = (pCity)malloc(sizeof(city));
			tempCity->cityName = (char*)malloc(strlen(Country->city[i]->cityName)+1);
			strcpy(tempCity->cityName,Country->city[i]->cityName);
			tempCity->favoriteFood = (char*)malloc(sizeof(Country->city[i]->cityName)+1);
			strcpy(tempCity->favoriteFood,Country->city[i]->favoriteFood);

			tempCity->residents = Country->city[i]->residents;
			tempCityArray[i] = tempCity;
		}
		newCopyCountry->city=tempCityArray;

	}
	return newCopyCountry;



}


status printCountry(pCountry country) {

	if (country == NULL) {
		return failure;
	}

	printf("Country %s coordinates:<%d,%d> , <%d,%d>\n", country->name,
			country->area->x1, country->area->y1, country->area->x2,
			country->area->y2);

	if (country->citiesNumber == 0) {
		return success;
	} else {
		int i;
		for (i = 0; i < country->citiesNumber; i++) {
			printf("\t %s includes %d ‫‪residents‬‬ ‫‪and‬‬ ‫‪their‬‬ ‫‪favorite‬‬ ‫‪food‬‬ ‫‪is‬‬ %s. \n",
					country->city[i]->cityName, country->city[i]->residents,
					country->city[i]->favoriteFood);
		}

		return success;
	}

}

void printMenu() {
	printf("please choose one of the following numbers:\n");
	printf("1 : print countries:\n");
	printf("2 : add country:\n");
	printf("3 : add city to country\n");
	printf("4 : delete city from country\n");
	printf("5 : print country by name\n");
	printf("6 : delete country\n");
	printf("7 : is country in area\n");
	printf("8 : exit\n");
}

pCity createCity(char *cityName, char *favoriteFood, int residents) {
	pCity newCity = (pCity) malloc(sizeof(city));
	if (newCity == NULL) {
		printf("no memory available");
		return NULL;
	}
	newCity->cityName = (char*) malloc(strlen(cityName) + 1);
	strcpy(newCity->cityName, cityName);
	if (newCity->cityName == NULL) {
		printf("no memory available");
		return NULL;
	}
	newCity->favoriteFood = (char*) malloc(strlen(favoriteFood) + 1);
	strcpy(newCity->favoriteFood, favoriteFood);
	if (newCity->favoriteFood == NULL) {
		printf("no memory available");
		return NULL;
	}
	newCity->residents = residents;

	return newCity;
}
//////////////////////////////////////////////////////////////////////////////////
Element copyElementName(Element element) {
	char* nameCopy = (char*)malloc(strlen((char*)element)+1);
	if(nameCopy==NULL)
	{
		return NULL;
	}
	strcpy(nameCopy,element);
	return (Element)nameCopy;
}

status freeName(Element element)
{
	free(element);
	return success;
}

status printName(Element element)
{
	if(element==NULL)
	{
		return failure;
	}
	printf("%s",(char*)element);
	return success;
}

Element copyCountryAsValue(Element element)
{
	if(element==NULL)
	{
		return NULL;
	}
	return (Element) copyCountry((pCountry)element);


}

status freeCountryAsValue(Element element)
{
	if(element==NULL)
	{
		return success;
	}
	return freeCountry((pCountry)element);
}


status printCountryAsValue(Element element)
{
	if(element==NULL)
	{
		return failure;
	}
	return printCountry((pCountry)element);
}


bool compCountryName(Element element1, Element element2)
{
	 if((strcmp((char*)element1,(char*)element2))==0)
	 {
		 return true;
	 }
	 return false;
}


int transformElemnentTonumber(Element name)
{
	if(name==NULL)
	{
		return -1;
	}

	char buffer[300];
	strcpy(buffer,(char*)name);
	int sum=0;
	int i;
	for(i=0;buffer[i]!='\0';i++)
	{
		sum=sum+buffer[i];
	}
	return sum;
}

///////////////////////////////////////////////////////////////////////////////


char* getCountryName(pCountry Country)
{
	if(Country==NULL)
	{
		return NULL;
	}
	if(Country->name==NULL)
	{
		return NULL;
	}
	return Country->name;
}

status freeCountryName(pCountry Country)
{
	if(Country==NULL)
	{
		return failure;
	}
	if(Country->name==NULL)
	{
		return success;
	}
	free(Country->name);
	return success;
}


int transforNameIntoNumber(pCountry country)
{
	if(country==NULL)
	{
		return -1;
	}
	int sum=0;
	int length = strlen(country->name);
	int i=0;
	for(i=0;i<length;i++)
	{
		sum=sum+country->name[i];
	}
	return sum;
}

Element getCountryNameAsElement(Element element)
{
	if(element==NULL)
	{
		return NULL;
	}
	Element name = getCountryName((pCountry)element);
	return name;
}

void freeWorld(pCountry* countries, int numOfCountries)
{
	int i=0;
	for(i=0;i<numOfCountries;i++)
	{
		freeCountry(countries[i]);
	}

}

/////////////////////////////////////////////////////////////////////////////////////////////////////


int getNumOfCities(pCountry country) {
	return country->citiesNumber;
}

char* getCityName(pCity city) {
	return (city->cityName);
}

pCity getCity(pCountry country, int index) {
	return country->city[index];
}
pCity* getCityArray(pCountry country) {
	return country->city;
}

void setCity(pCountry country, int i, pCity city) {
	country->city[i] = city;
}

void freeArea(pCountry Country) {
	free(Country->area);

}
bool equalCountryName(pCountry country1,pCountry country2)
{
	if(country1==NULL||country2==NULL)
	{
		return false;
	}
	return strcmp(country1->name,country2->name);
}








