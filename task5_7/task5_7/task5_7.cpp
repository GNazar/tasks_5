/*
7.	Задана квадратна матриця розмірності m × 3. Матрицю задати в класі Matr. 
Знайти скалярний добуток  першого рядка матриці на перший стовбець. 
Розмірність задати в головній програмі константою. Елементами матриці є цілі числа.
*/
#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
using namespace std;

//****Class description****//
class Matr
{
	int d;
	int *p;
public:
	int getDimention(void);
	int getElement(int i,int j);
	int setElement(int i,int j,int value);
	Matr();
	Matr(int);
	Matr(Matr&);
	~Matr();
	void out();
	int calculateProductRowColmn(void);
};

//*****Implementtion*****//
//function return dimention; 
int Matr::getDimention()
{
	return d;
}

//=========function return element with index i,j;
int Matr::getElement(int i,int j)
{
	return *(p+d*i+j);
}

//===========function set value on position with index i,j;
int Matr::setElement(int i,int j,int value)
{
	if((i>=d)||(j>=d)||(i<0)||(j<0))
		{
			puts("Index out of bound!");
			return -1;
	}
	*(p+d*i+j)=value;
	return value;
}

//====non-argument constructor;
Matr::Matr()
{
	d=0;
	p=NULL;
}

//=========constructor with parameters;
Matr::Matr(int n)
{
	const int L=10;
	int v;
	if(n<=0){
		puts("Error! Index must be more then 0!");
		d=0;
		p=NULL;
	}else
	{
		srand (time(NULL));
		d=n;
		p=new int[d*d];
		for(int i=0;i<d;i++)
			for(int j=0;j<d;j++)
			{
				v=rand()%L;
				setElement(i,j,v);
			}
	}
}

//=========copy constructor;
Matr::Matr(Matr&m)
{
	d=m.d;
	p=new int[d*d];
	memcpy(p,m.p,d*d*sizeof(int));
}

//=======destructor
Matr::~Matr()
{
	delete[]p;
	p=NULL;
}

//======function that prints array;
void Matr::out (void)
{
	for(int i=0;i<d;i++){
		for(int j=0;j<d;j++)
			printf("%5d",*(p+i*d+j));
		cout<<endl;
	}
}
int Matr::calculateProductRowColmn(void)
{
	int res=0;
	for(int i=0;i<d;i++){
		//puts("AAAAAA");
		res+=getElement(i,0)*getElement(0,i);
	}
	return res;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int dim;
	cout<<"Enter dimention->";
	cin>>dim;
	Matr m1(dim);
	m1.out();
	cout<<"Produce="<<m1.calculateProductRowColmn()<<endl;
	getchar();
//	m1.setElement(1,1,-1);
//	puts("m1.setElement(1,1,-1);");
//	m1.out();
	getchar();
	return 0;
}

