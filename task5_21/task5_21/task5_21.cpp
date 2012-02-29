/*
21.	Заданий вектор розмірності п, компонентами якого є відомості про складання іспитів студентами деякого вузу. 
Інформація про кожного студента задана в слідуючому вигляді: прізвище, номер групи, оцінка_1, оцінка_2, оцінка_3. 
Визначити процедуру пошуку
а)	студентів, що мають заборгованості хоча б з одного з предметів;
б)	предмета, який було здано краще за усі інші;
в)	студентів, що склали всі іспити на 5 і 4.
*/
#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
using namespace std;
class Stud
{
	char name[20];
	char group[8];
	int point[3];
public:
	char* getName(void);
	char*getGroup(void);
	int getPoint(int n);
	void setName(char*);
	void setGroup(char*);
	void setPoint(int n,int p);
	Stud();
	Stud(char*,char*,int,int,int);
	Stud(Stud&);
	~Stud();
	int hasDebt(void);
	int isGoodStud(void);
	void print (void);
};
//******Implementation******//
char* Stud::getName(void)
{
	return name; 
}

char* Stud::getGroup(void)
{
	return group; 
}

int Stud::getPoint(int i)
{
	return point[i];
}

void Stud::setName(char*n)
{
	strcpy(name,n);
}

void Stud::setGroup(char*g)
{
	strcpy(group,g);
}

void Stud::setPoint(int i,int p)
{
	if((i<(int)3)&&(i>(int)-1)&&(p>=(int)0)&&(p<=(int)5))
		point[i]=p;
}
//non-argument destructor;
Stud::Stud()
{
	*name='\0';
	*group='\0';
	point[0]=0;
	point[1]=0;
	point[2]=0;
}

//=====constructor with arguments; 
Stud::Stud(char*n,char*g,int p1,int p2,int p3)
{
	setName(n);
	setGroup(g);
	setPoint((int)0,p1);
	setPoint((int)1,p2);
	setPoint((int)2,p3);
}

//====copy constructor;
Stud::Stud(Stud& p)
{
	setName(p.getName());
	setGroup(p.getGroup());
	setPoint((int)0,p.getPoint(int(0)));
	setPoint((int)1,p.getPoint(int(1)));
	setPoint((int)2,p.getPoint(int(2)));
}

//====destructor;
Stud::~Stud(){}

//*****functionality******//
int Stud::hasDebt(void)
{
	for(int i=0;i<(int)3;i++)
		if(getPoint(i)==0) return 1;
	return 0;
}

void Stud::print(void)
{
	printf("%20s %8s %4d %4d %4d\n",name,group,point[0],point[1],point[2]);
}

int Stud::isGoodStud(void)
{
	for(int i=(int)0;i<3;i++)
		if(point[i]<(int)4) return (int)0;//has at least one 3 or 2;
	return (int)1;
}


class Exam
{
	int n;
	Stud *p;
public:
	int getNumber(void);
	Stud getStud(int i);
	void setStud(int, Stud*);
	Exam();
	Exam(int p);
	Exam(Exam&e);
	~Exam();
	void printLostStud(void);
	void print(void);
	void printBestCourse(void);
	void printGoodStud(void);
};
//****implementation****//
int Exam::getNumber()
{
	return n;
}

Stud Exam::getStud(int i)
{
	return *(p+i); 
}

void Exam::setStud(int i,Stud* s)
{
	*(p+i)=*s;
}

Exam::Exam()
{
	n=0;
	p=NULL;
}
Exam::Exam(int pn)
{
	char bf[20];
	int b;
	n=pn;
	p=new Stud[pn];
	for(int i=0;i<n;i++)
	{
		cout<<"Enter name->";
		gets(bf);
		(p+i)->setName(bf);
		cout<<"Enter group->";
		gets(bf);
		(p+i)->setGroup(bf);
		cout<<"Enter marks->";
		for(int j=0;j<3;j++){
			cin>>b;
			(p+i)->setPoint(j,b);
		}
		getchar();
	}
}
//====copy constructor;
Exam::Exam(Exam& e)
{
	n=e.getNumber();
	p=new Stud[n];
	memcpy(p,e.p,n);
}

//=======destructor;
Exam::~Exam()
{
	delete[]p;
	p=NULL;
}
//*******functionality********//
void Exam::print(void)
{
	for(int i=0;i<n;i++){
		(p+i)->print();
	}
} 
//print students who have doubts;
void Exam::printLostStud(void)
{
	for(int i=0;i<n;i++)
		if((p+i)->hasDebt())
			(p+i)->print();
}
//function print course which points are hightest;
void Exam::printBestCourse(void)
{
	int max,imax;
	int p1=0,p2=0,p3=0;
	for(int i=0;i<n;i++){
		p1+=(p+i)->getPoint(0);
		p2+=(p+i)->getPoint(1);
		p3+=(p+i)->getPoint(2);
	}
	if(p1>p2){
		max=p1;
		imax=(int)1;
	}else{
		max=p2;
		imax=(int)2;
	}
	if(p3>max){
		max=p3;
		imax=(int)3;
	}
	printf("Most successful course # %d\n",imax);	
}
void Exam::printGoodStud(void)
{
	for(int i=(int)0;i<n;i++)
		if((p+i)->isGoodStud())
			(p+i)->print();
}
int _tmain(int argc, _TCHAR* argv[])
{
	int c;
	cout<<"Enter number of students->";
	cin>>c;
	getchar();
	Exam e1(c);
	e1.print();
	puts("Students that have debts:");
	e1.printLostStud();
	e1.printBestCourse();
	puts("Good students:");
	e1.printGoodStud();
	getchar();
	return 0;
}

