/*
23.	Задано вектор Рейс, компонентами якого Рейс(х) є множини міст із вказаного списку, 
в які можна за один рейс доїхати автобусом з міста х.
Визначити процедуру пошуку множини міст, в які можна дістатися автобусом 
(за один рейс або через інші міста) із заданого міста.
*/
#include "stdafx.h"
#include <iostream>
#include <string.h>
using namespace std;
class Route
{
	char start[20];
	char *st;//array of stations;
	int n;//number of stations
public:
	char* getCity();
	void setCity(char*);
	void setStation(char*,int pn);
	char* getStation(int pn);
	void initStations(void);
	int getNumberOfStations();
	void setRoute(int,char*);
	Route::Route();
	Route::Route(int,char*);
	Route(Route&);
	~Route();

	
	void out(void);
	void Route::printStations(void);
};
//*****implementation*****//
int Route::getNumberOfStations()
{
	return n;
}
char* Route::getCity()
{
	return start;
}
//================//
void Route::setCity(char* s)
{
	strcpy(start,s);
}
//================//
void Route::setStation(char* s,int pn)
{
	strcpy(st+20*pn,s);
}
//=================//
char* Route::getStation(int pn)
{
	return (st+20*pn);
}
//============================//
//set stations by user;
void Route::initStations(void)
{
	char bf[20];
	cout<<"Enter stations:"<<endl;
	for(int i=0;i<n;i++){
		cout<<(i+1)<<"->";
		cin>>bf;
		setStation(bf,i);
	}
}
//==================//
void Route::setRoute(int pn,char*pc)
{
	if (pn<1) puts("Error!Number of stations must be more then 0!");
	else
	{
		strcpy(start,pc);
		n=pn;
		st=new char[20*n];
		initStations();
	}
}
//==================//
//****Constructors&Destructors*****//
Route::Route()
{
	n=0;
	st=NULL;
	*start='\0';
}
Route::Route(int pn,char*pc)
{
	if (pn<1) puts("Error!Number of stations must be more then 0!");
	else
	{
		strcpy(start,pc);
		n=pn;
		st=new char[20*n];
		initStations();
	}
}
//====================//
Route::Route(Route&t)
{
	n=t.getNumberOfStations();
	setCity(t.getCity());
	st=new char[20*n];
	memcpy(st,t.getStation(0),20*n);
}
Route::~Route()
{
	delete[]st;
	st=NULL;
}
//*****functionality*****//
void Route::printStations(void)
{
	//cout<<"Stations:";
	for(int i=0;i<n;i++)
		cout<<getStation(i)<<"; ";
	cout<<endl;
}
//=======print Route============//
void Route::out(void)
{
	cout<<"City: "<<getCity()<<endl;
	cout<<"Stations: ";
	printStations();
}

//====Global functions===//

int isHas(char**s,int n,char* value)//check if "s" include "value"
{
	for(int i=0;i<n;i++){
		if(strcmp(s[i],value)==0){ 
			return 1;
		}
	}
	return 0;
}
void printAllStations(char*s,Route* r,int nr)
{
	static int ij;
	static char*m[100];//!!!!!!!!!!!!!!!!!!!
	Route temp;
	int pos,t=(int)1;;
	char bs[20];
	if(isHas(m,ij,s)) return;//check if 's' was counted
	m[ij]=new char[sizeof(s)];
	strcpy((m[ij]),s);
	ij++;										
	for(pos=0;(pos<nr);pos++){//find city;
		 t=strcmp((r+pos)->getCity(),s);
		 if(t==0) break;
	}
	if (pos==nr) {//element isn't found;
		//puts("City not found!");
		return;
	}
	temp=*(r+pos);
	temp.printStations();
	for(int i=0;i<temp.getNumberOfStations();i++){//call printAllStations(...) for each station in temp;
		strcpy(bs,temp.getStation(i));
		printAllStations(bs,r,nr);
		
	}
//!!format
	
}
int _tmain(int argc, _TCHAR* argv[])
{
	int nr,ns;
	char bf[20];
	Route *pr;
	cout<<"Enter number of routs->";
	cin>>nr;
	pr=new Route[nr];
	for(int i=0;i<nr;i++){
		cout<<"Enter city->";
		cin>>bf;
		cout<<"Enter number of stations->";
		cin>>ns;
		(pr+i)->setRoute(ns,bf);
	}
	for(int i=0;i<nr;i++)
		(pr+i)->out();
	
	getchar();
	puts("Enter city->");
	cin>>bf;
	getchar();
	cout<<"Result:"<<endl;
	printAllStations(bf,pr,nr);
	getchar();
	return 0;
}

