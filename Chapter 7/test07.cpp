#include <bits/stdc++.h>
using namespace std;
#include "ch07.h"

void tst01()
{
    cout<<"Test TossCoins"<<endl;
    tst();
}
/*
tst01.out:
Test TossCoins
     0  *
     1  *
     2    *
     3         *
     4               *
     5                  *
     6               *
     7         *
     8    *
     9  *
    10  *
*/

void tst02()
{
    cout<<"Test Darts"<<endl;
    cout<<Darts(1000000)<<endl;
}
/*
tst02.out:
TTest Darts
3.14104
*/

void tst03()
{
    cout<<"Test Darts1"<<endl;
    cout<<Darts1(1000000)<<endl;
}
/*
tst03.out:
Test Darts1
0.333767
*/

void tst04()
{
    cout<<"Test Integration"<<endl;
    cout<<Integration(5,9,1000000)<<endl;
}
/*
tst04.out:
Test Integration
201.341
*/

void tst05()
{
    cout<<"Test NonLinear"<<endl;
	int n=2,Steps=10000,M=1000;
    double  a0=0.001,epsilon=0.01,k=1.1;
    double x0[10],dx0[10],x[10];
	x0[1]=2.5,x0[2]=3.0;
	dx0[1]=0.01,dx0[2]=0.01;
    while (1)
        if(NonLinear(x0,dx0,x,a0,epsilon,k,n,Steps,M)) break;
	for (int i=1;i<=n;i++)cout<<"x"<<i<<"="<<x[i]<<" ";
	cout<<endl;
	cout<<f(x,n)<<endl;
	cout<<f1(x)<<" "<<f2(x)<<endl;
}
/*
tst05.in:
f1=x[1]*x[1]*x[1]-x[2]*x[2]-16;
f2=x[1]*x[2]+x[2]-15;
tst05.out:
Test NonLinear
x1=3.08893 x2=3.66976 
6.20277e-05
0.00575407 0.00537758
*/

void tst06()
{
    cout<<endl<<"Test Select"<<endl;
    int n=2231,k=n/2,a[5000];
	for(int i=0;i<n;i++)a[i]=1+rand()%n;
	//for(int i=0;i<n;i++)cout<<a[i]<<" ";cout<<endl;
	cout<<Select(a,n,k)<<endl;
	sort(a,a+n);
	cout<<a[k-1]<<endl;
	//for(int i=0;i<n;i++)cout<<a[i]<<" ";cout<<endl;
}
/*
Test Select
1084
1084
*/

void tst07()
{
    cout<<endl<<"Test Shuffle"<<endl;
    int n=50,a[50];
	for(int i=0;i<n;i++)a[i]=i+5;
	for(int i=0;i<n;i++)cout<<a[i]<<" ";cout<<endl;
	Shuffle(a,n);
	for(int i=0;i<n;i++)cout<<a[i]<<" ";cout<<endl;
}
/*
Test Shuffle
5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 
53 28 10 15 49 7 19 44 6 46 36 14 24 8 16 21 45 31 35 33 20 41 40 52 17 9 23 22 25 50 51 54 34 13 43 5 18 42 30 32 48 47 11 12 37 29 39 27 26 38 
*/

void tst08()
{
    cout<<endl<<"Test OrderedList"<<endl;
	static RandomNumber rnd;
	OrderedList<int> lst(0,INT_MAX,1000);
	int n=37,m=9;
	for(int i=0;i<n;i++){
		int x = rnd.Random(999)+1;
		lst.Insert(x);
	}
	lst.Output();cout<<endl;
	for(int i=0;i<m;i++){
		int idx=lst.n;
		int x = rnd.Random(idx);
		x=lst.value[idx];
		bool found=lst.Search(x,idx);
		if(found){
			lst.Delete(x);
			cout<<x<<" deleted."<<endl;
		}
		else cout<<x<<" not found."<<endl;
	}
	cout<<endl;
	lst.Output();
}
/*
Test OrderedList
n=37
46 81 88 117 166 184 189 204 241 325 389 427 434 445 449 478 493 500 503 521 531 537 563 567 584 585 622 701 714 750 781 790 824 867 907 941 965 
941 deleted.
584 deleted.
537 deleted.
503 deleted.
449 deleted.
500 deleted.
493 deleted.
88 deleted.
563 deleted.
n=28
46 81 117 166 184 189 204 241 325 389 427 434 445 478 521 531 567 585 622 701 714 750 781 790 824 867 907 965 
*/

void tst09()
{
    cout<<endl<<"Test SkipList"<<endl;
	static RandomNumber rnd;
	SkipList<int,int> lst(INT_MAX,1000,0.5);
	int n=37,m=520;
	for(int i=0;i<n;i++){
		int x = rnd.Random(999)+1;
		lst.Insert(x);
	}
	lst.Output();cout<<endl;
	for(int i=0;i<m;i++){
		int y,x = rnd.Random(999)+1;
		bool found=lst.Search(x,y);
		if(found){
			lst.Delete(x,y);
			cout<<x<<" deleted."<<endl;
		}
		//else cout<<x<<" not found."<<endl;
	}
	cout<<endl;
	lst.Output();
}
/*
tst09.out:
Test SkipList
9 26 37 49 112 113 124 131 169 170 182 273 290 304 308 329 363 390 421 432 449 537 583 594 609 626 644 733 840 852 887 897 933 935 954 959 989 
583 deleted.
537 deleted.
112 deleted.
421 deleted.
887 deleted.
363 deleted.
432 deleted.
37 deleted.
9 deleted.
852 deleted.
933 deleted.
49 deleted.
273 deleted.
644 deleted.
840 deleted.
26 113 124 131 169 170 182 290 304 308 329 390 449 594 609 626 733 897 935 954 959 989 
*/

void tst10()
{
    cout<<endl<<"Test nQueen1"<<endl;
	nQueen1(8);
}
/*
tst10.out:
Test nQueen
3  6  2  7  5  1  8  4  
*/

void tst11()
{
    cout<<endl<<"Test nQueen"<<endl;
    int n=12;  
    while(!nQueen(n));  
}
/*
tst11.out:
Test nQueen
6  11  9  1  12  5  2  8  10  4  7  3  
*/

void tst12()
{
    cout<<endl<<"Test Split"<<endl;
    cout<<Split(15)<<endl;
    cout<<Split(29)<<endl;
}
/*
tst12.out:
Test Split
3
1
*/

void tst13()
{
    cout<<endl<<"Test Pollard"<<endl;
    int n = 1024;
    Pollard(n);
    Pollard(2889);
}
/*
tst13.out:
Test Pollard
128
9
*/

void tst14()
{
    cout<<endl<<"Test Majority"<<endl;
    int n=12;
    int a[]={1,3,6,8,8,8,8,8,8,8,3,6};
    int b[]={1,3,6,8,8,8,8,8,8,1,3,6};
    cout<<Majority(a,n)<<endl;
    cout<<Majority(b,n)<<endl;
}
/*
tst14.out:
Test Majority
1
0
*/

void tst15()
{
    cout<<endl<<"Test Majority2"<<endl;
    int n=12;
    int a[]={1,3,6,8,8,8,8,8,8,8,3,6};
    int b[]={1,3,6,8,8,8,8,8,8,1,3,6};
    cout<<Majority2(a,n)<<endl;
    cout<<Majority2(b,n)<<endl;
}
/*
tst15.out:
Test Majority2
1
0
*/

void tst16()
{
    cout<<endl<<"Test MajorityMC"<<endl;
    int n=12;
    float e=0.001;
    int a[]={1,3,6,8,8,8,8,8,8,8,3,6};
    int b[]={1,3,6,8,8,8,8,8,8,1,3,6};
    cout<<MajorityMC(a,n,e)<<endl;
    cout<<MajorityMC(b,n,e)<<endl;
}
/*
tst16.out:
Test MajorityMC
1
0
*/

void tst17()
{
    cout<<endl<<"Test Prime1"<<endl;
    cout<<Prime1(53)<<endl;
    cout<<Prime1(52)<<endl;
}
/*
tst17.out:
Test Prime1
1
0
*/

void tst18()
{
    cout<<endl<<"Test Prime"<<endl;
    cout<<Prime(53)<<endl;
    cout<<Prime(52)<<endl;
}
/*
tst18.out:
Test Prime
1
0
*/

void tst19()
{
    cout<<endl<<"Test PrimeMC"<<endl;
    int n=53,k=5;
    cout<<PrimeMC(n,k)<<endl;
    cout<<PrimeMC(1351,k)<<endl;
}
/*
tst19.out:
Test PrimeMC
1
0
*/

int main() 
{
	//tst01();
	//tst02();
	//tst03();
	//tst04();
	//tst05();
    //tst06();
    //tst07();
    //tst08();
    //tst09();
    //tst10();
    //tst11();
    //tst12();
    //tst13();
    //tst14();
    //tst15();
    //tst16();
    //tst17();
    //tst18();
    tst19();
	return 0;
}
