/*
22.	Задано вектор С розміру п, компонентами якого є відомості про мешканців деяких міст. 
Інформація про кожного мешканця містить його прізвище, назву міста мешкання; 
адреси мешкання у вигляді: вулиця, будинок, квартира. 
Визначити процедуру пошуку двох будь-яких жителів із списку С, 
що мешкають в різних містах за однаковою адресою.
*/
#include "stdafx.h"
#include <iostream>
#include <stdio.h>
using namespace std;
struct Address
{
	char street[20];
	char b[5];
	int f;
};
int isHas(Address *m,int n,Address value)
{
	int t1,t2,t3;
	for(int i=0;i<n;i++){
		t1=strcmp((m+i)->street,value.street);
		t2=strcmp((m+i)->b,value.b);
		t3=(m+i)->f-value.f;
		if((t1==0)&&(t2==0)&&(t3==0)) return 1;
	}
	return 0;
}
class Inh
{
	char name[25];
	char city[20];
	Address a;
public:
	char* getName();
	char * getCity();
	Address getAddress();
	void setName(char*);
	void setCity(char*);
	void setAddress(char*,char*,int);
	Inh();
	Inh(char*,char*,char*,char*,int);
	Inh(Inh&);
	~Inh();
	int checkAddress(Inh* h);
	void setAddress(Address& s);
	void out(void);
	


};

//======IMPLEMENTATION=======//

char* Inh::getName()
{
	return name;
}
//======================//
char* Inh::getCity()
{
	return city;
}
//======================//
Address Inh::getAddress()
{
	return a;
}
//======================//
void Inh::setName(char*s)
{
	strcpy(name,s);
}
//======================//
void Inh::setCity(char*s)
{
	strcpy(city,s);
}
//=====================//
void Inh::setAddress(char*s1,char*s2,int p)
{
	if(p>0)
	{
		strcpy(a.street,s1);
		strcpy(a.b,s2);
		a.f=p;
	}else puts("Address hasn't been initialized!");
}
void Inh::setAddress(Address& s)
{
	if(s.f>0)
	{
		strcpy(a.street,s.street);
		strcpy(a.b,s.b);
		a.f=s.f;
	}
}
//======Constructors&Destructors=======//
Inh::Inh(){}
Inh::Inh(char*s1,char*s2,char*s3,char*s4,int p)
{
	setName(s1);
	setCity(s2);
	setAddress(s3,s4,p);
}
Inh::Inh(Inh& h)
{
	strcpy(name,h.getName());
	strcpy(city,h.getCity());
	a=h.getAddress();
}
Inh::~Inh(){}
//======functionality=====//
int Inh::checkAddress(Inh* h)
{
	Address temp=h->getAddress();
	int t1,t2,t3,t4;
	t1=strcmp(a.street,temp.street);
	t2=strcmp(a.b,temp.b);
	t3=a.f-temp.f;
	t4=strcmp(city,h->getCity());
	if((t1==0)&&(t2==0)&&(t3==0)&&(t4!=0))
		return 1;
	return 0;
};
void Inh::out(void)
{
	printf("%25s %20s %25s %7s %d\n",name,city,a.street,a.b,a.f);
}
class C
{
	int n;
	Inh* p;
public:
	int getNumber();
	Inh getInh(int);
	void setInh(int,Inh&h);
	C();
	C(int);
	C(C&);
	~C();
	void printSameAddressInDifferentCities(void);
};
int C::getNumber()
{
	return n;
}
Inh C::getInh(int i)
{
	return *(p+i);
}
void C::setInh(int i,Inh&h)
{
	(p+i)->setName(h.getName());
	(p+i)->setCity(h.getCity());
	(p+i)->setAddress(h.getAddress());
}
//****Constructors&Destructors****//
C::C()
{
	n=0;
	p=NULL;

};
C::C(int pn)
{
	if(pn<=0) puts("Error!");
	else{
		char bf[25];
		char tf[5];
		int b;
		n=pn;
		p=new Inh[n];
		for(int i=0;i<n;i++)
		{
			cout<<"Enter name->";
			gets(bf);
			(p+i)->setName(bf);
			cout<<"Enter city->";
			gets(bf);
			(p+i)->setCity(bf);
			cout<<"Enter street->";
			gets(bf);
			cout<<"Enter number of building->";
			gets(tf);
			cout<<"Enter number of flat->";
			cin>>b;
			(p+i)->setAddress(bf,tf,b);
			getchar();
		}
	}//else
}
C::C(C &pc)
{
	n=pc.getNumber();
	p=new Inh[n];
	memcpy(p,&pc,n*sizeof(Inh));//!!!!!!!!!!!!!
}
C::~C()
{
	delete[]p;
}
//****functionality****//
void C::printSameAddressInDifferentCities(void)
{
	
	int b;
	int ij=0;
	Address temp;
	Address* pa=new Address[n];//contain cities which have been printed;
	for(int i=0;i<n-(int)1;i++)
	{
		temp=(p+i)->getAddress();
		if(!isHas(pa,ij,temp)){//if have been printed;
			*(pa+ij)=temp;
			ij++;
			b=1;
			for(int j=i+1;j<n;j++)
			{
				if((p+i)->checkAddress(p+j))
				{
					if(b){//print city which checked one time;
						(p+i)->out();
						b=0;
					}
					(p+j)->out();
				}
			}
		}//if
	}
}
int _tmain(int argc, _TCHAR* argv[])
{
	int n;
	cout<<"Enter number of inhabitants->";
	cin>>n;
	getchar();
	C c1(n);
	cout<<endl;
	cout<<"Inhabitants who lives at the same address in different cities:"<<endl;
	c1.printSameAddressInDifferentCities();
	getchar();
	return 0;
}

