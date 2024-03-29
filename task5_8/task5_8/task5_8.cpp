/*
8.	Задана квадратна матриця розмірності m × 3. Матрицю задати в класі Matr. 
Знайти скалярний добуток  головної діагоналі на  перший рядок матриці. 
Розмірність задати в головній програмі константою. Еле¬ментами матриці є цілі числа.
*/
#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

class Matr
{
	int d;
	int *p;
public:
//=========Getters&Setters==========//
//function return matrix dimention;	
	int getDimention(void)
	{
		return d;
	}

//function return element with indxes i,j
	int getElement(int i,int j)
	{
		return *(p+i*d+j);
	}

//function set 'value' on position i,j;
	int setElement(int i,int j,int value)
	{
		if((i>=d)||(j>=d)||(i<0)||(j<0))
		{
			puts("Index out of bound!");
			return -1;
		}
		*(p+i*d+j)=value;
		return value;
	}
//=====Constructors&Destructors=====//
	
	Matr()	//non-argument constructor
	{
		//puts("Construtor()");
		d=0;
		p=NULL;
	}
//======================//
	Matr(int n)	//consructors with parameters;
	{
		int v;
	//	puts("Construtor");
		getchar();
		d=n;
		p=new int[d*d];
		srand (time(NULL));
		for(int i=0;i<d;i++)
			for(int j=0;j<d;j++)
			{
				v=rand()%10;
				setElement(i,j,v);
			}
	}
//=======================//
	Matr(Matr&m)	//copy constructor;
	{
		int v;
		puts("Copy constructor");
		d=m.d;
		p=new int[d*d];
		for(int i=0;i<d;i++)
			for(int j=0;j<d;j++)
			{
				v=m.getElement(i,j);
				setElement(i,j,v);
			}
	}
//=========================//
	~Matr()		//destructor;
	{
	//	puts("Destructor");
		delete []p;
	//	getchar();
		p=NULL;
	}

//======Functionality=========	
	void out(void)	//function that print matrix;
	{
		for(int i=0;i<d;i++){
			for(int j=0;j<d;j++)
				printf("%4d",getElement(i,j));
			cout<<endl;
		}			
	}
//===========================//	
	int getPDialRow(void)//function that calculate product
						//of first row and main diagonal
	{
		int res=0;
		for(int i=0;i<d;i++)
		{
			res+=getElement(i,i)*getElement(0,i);
		}
		return res;
	}
};
//=====================//
int _tmain(int argc, _TCHAR* argv[])
{
	int n;
	cout<<"Enter dimention->";
	cin>>n;
	Matr m1(n);
	cout<<"Matrix"<<endl;
	m1.out();
	getchar();
//	m1.setElement((int)1,(int)1,(int)-1);
//	puts("m1.setElement((int)1,(int)1,(int)-1)");
//	m1.out();
	cout<<"Product of the first row and diagonal - "<<m1.getPDialRow()<<endl;
	getchar();
	return 0;
}

