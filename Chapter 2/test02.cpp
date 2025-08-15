#include <bits/stdc++.h>
using namespace std;
#include "ch02.h"

void tst01()
{
	cout<<endl<<"Test factorial"<<endl;
	cout<<factorial(6)<<endl;
}
/*
Test factorial
720
*/	    

void tst02()
{
	cout<<endl<<"Test fibonacci"<<endl;
	cout<<fibonacci(6)<<endl;
}
/*
Test fibonacci
13
*/	    

void tst03()
{
	int lst[50];
	cout<<endl<<"Test Perm"<<endl;
	for(int i=0;i<50;i++)lst[i]=i;
	Perm(lst,5,10);
}
/*
Test Perm
*/	    

void tst04()
{
	cout<<endl<<"Test q"<<endl;
	cout<<q(6,6)<<" "<<q(16,6)<<endl;
}
/*
Test q
11 136
*/	    

void tst05()
{
	cout<<endl<<"Test hanoi"<<endl;
	hanoi(3,1,2,3);
}
/*
1->2
1->3
2->3
1->2
3->1
3->2
1->2
*/	    

void tst06()
{
	int a[5000];
	cout<<endl<<"Test BinarySearch"<<endl;
	int n=50,k;
    srand(time(0));
	for(int i=0;i<n;i++)a[i]=rand()%300;
	//for(int i=0;i<n;i++)cout<<a[i]<<" ";cout<<endl;
	sort(a,a+n);
	for(int i=0;i<n;i++)cout<<a[i]<<" ";cout<<endl;
	int x=a[rand()%n];
	cout<<"x="<<x<<endl;
	int y=BinarySearch(a,x,n);
	if(y<0)cout<<y<<endl;
	else cout<<a[y]<<endl;
}
/*
Test BinarySearch
2 5 11 11 26 32 34 50 54 67 69 69 81 82 96 96 97 98 101 105 112 113 120 125 143 144 156 160 160 164 165 183 189 193 194 201 202 209 209 213 213 219 230 233 236 253 269 272 275 299 
x=213
213
*/	    

void tst07()
{
	cout<<endl<<"Test ChessBoard"<<endl;
	int s=8;
	memset(Board,0,sizeof(Board));
	ChessBoard(0,0,0,1,s);
	for(int i=0;i<s;i++){
		for(int j=0;j<s;j++)
		    cout<<Board[i][j]<<" ";
		cout<<endl;
	}
}
/*
Test ChessBoard
3 0 4 4 8 8 9 9 
3 3 2 4 8 7 7 9 
5 2 2 6 10 10 7 11 
5 5 6 6 1 10 11 11 
13 13 14 1 1 18 19 19 
13 12 14 14 18 18 17 19 
15 12 12 16 20 17 17 21 
15 15 16 16 20 20 21 21 
*/	    

void tst08()
{
    cout<<endl<<"Test MergeSort"<<endl;
    int n=50,a[5000];
	for(int i=0;i<n;i++)a[i]=rand()%n;
	for(int i=0;i<n;i++)cout<<a[i]<<" ";cout<<endl;
	MergeSort(a,n);
	for(int i=0;i<n;i++)cout<<a[i]<<" ";cout<<endl;
}
/*
Test MergeSort
9 26 36 46 25 5 40 48 33 22 38 38 7 32 38 36 26 1 4 15 29 26 25 40 46 45 41 25 48 15 24 41 38 31 18 41 18 21 2 39 30 0 26 44 29 5 37 47 30 4 
0 1 2 4 4 5 5 7 9 15 15 18 18 21 22 24 25 25 25 26 26 26 26 29 29 30 30 31 32 33 36 36 37 38 38 38 38 39 40 40 41 41 41 44 45 46 46 47 48 48 
*/	    

void tst09()
{
    cout<<endl<<"Test QuickSort"<<endl;
    int n=50,a[5000];
	for(int i=0;i<n;i++)a[i]=rand()%n;
	for(int i=0;i<n;i++)cout<<a[i]<<" ";cout<<endl;
	QuickSort(a,0,n-1);
	for(int i=0;i<n;i++)cout<<a[i]<<" ";cout<<endl;
}
/*
Test QuickSort
24 43 8 16 48 27 25 14 45 46 32 5 34 18 16 48 42 28 20 48 48 33 8 19 6 26 27 45 45 38 2 16 43 25 25 41 0 13 12 0 10 7 31 49 5 22 46 8 30 6 
0 0 2 5 5 6 6 7 8 8 8 10 12 13 14 16 16 16 18 19 20 22 24 25 25 25 26 27 27 28 30 31 32 33 34 38 41 42 43 43 45 45 45 46 46 48 48 48 48 49 
*/	    

void tst10()
{
    cout<<endl<<"Test RandomizedQuickSort"<<endl;
    int n=50,a[5000];
	for(int i=0;i<n;i++)a[i]=1+rand()%n;
	for(int i=0;i<n;i++)cout<<a[i]<<" ";cout<<endl;
	RandomizedQuickSort(a,0,n-1);
	for(int i=0;i<n;i++)cout<<a[i]<<" ";cout<<endl;
}
/*
Test RandomizedQuickSort
43 6 9 43 7 24 50 2 31 33 45 20 19 8 33 9 37 8 34 35 22 3 43 2 25 12 7 42 24 35 34 25 23 28 40 13 14 39 13 13 11 16 26 20 28 39 24 18 39 28 
2 2 3 6 7 7 8 8 9 9 11 12 13 13 13 14 16 18 19 20 20 22 23 24 24 24 25 25 26 28 28 28 31 33 33 34 34 35 35 37 39 39 39 40 42 43 43 43 45 50 
*/	    

void tst11()
{
    cout<<endl<<"Test RandomizedSelect"<<endl;
    int n=3852,k=n/2,a[5000];
	for(int i=0;i<n;i++)a[i]=1+rand()%n;
	//for(int i=0;i<n;i++)cout<<a[i]<<" ";cout<<endl;
	cout<<RandomizedSelect(a,0,n-1,k)<<endl;
	RandomizedQuickSort(a,0,n-1);
	cout<<a[k-1]<<endl;
	//for(int i=0;i<n;i++)cout<<a[i]<<" ";cout<<endl;
}
/*
Test RandomizedSelect
1785
1785
*/	    

void tst12()
{
    cout<<endl<<"Test Select"<<endl;
    int n=2231,k=n/2,a[5000];
	for(int i=0;i<n;i++)a[i]=1+rand()%n;
	//for(int i=0;i<n;i++)cout<<a[i]<<" ";cout<<endl;
	cout<<Select(a,0,n-1,k)<<endl;
	RandomizedQuickSort(a,0,n-1);
	cout<<a[k-1]<<endl;
	//for(int i=0;i<n;i++)cout<<a[i]<<" ";cout<<endl;
}
/*
Test Select
1123
1123
*/	    

void tst13()
{
    cout<<endl<<"Test Cpair2"<<endl;
    PointX pa,pb,*X=new PointX [500];
    int n=0;
    float px,py,d;
    while(cin>>px>>py){
    	X[n].ID=n+1;
    	X[n].x=px;X[n++].y=py;
	}
    cout<<fixed<<setprecision(2);
    cout<<"Input:"<<endl;
    cout<<"n="<<n<<endl;
	for(int i=0;i<n;i++)cout<<X[i].ID<<" "<<X[i].x<<" "<<X[i].y<<endl;
    Cpair2(X,n,pa,pb,d);
    cout<<"Output:"<<endl;
    cout<<pa.ID<<" "<<pb.ID<<endl;
    cout<<d<< endl;
    delete [] X;
}
/*
Test Cpair2
Input: tst13.in
n=12
1 -1.00 3.00
2 -2.00 -2.00
3 1.00 -4.00
4 2.00 1.00
5 1.00 5.00
6 3.00 3.00
7 3.00 0.00
8 5.00 1.00
9 7.00 3.00
10 7.00 6.00
11 5.00 6.00
12 3.00 7.00
Output:
7 4
1.41
*/	    

void tst14()
{
    cout<<endl<<"Test Table"<<endl;
    int **b;
    make2dArray(b,9,9);
    Table(3,b);
	for(int i=1;i<9;i++){
		for(int j=1;j<9;j++)cout<<b[i][j]<<" ";
		cout<<endl;
	}
    delete2dArray(b,9);
}
/*
Test Table
1 2 3 4 5 6 7 8 
2 1 4 3 6 5 8 7 
3 4 1 2 7 8 5 6 
4 3 2 1 8 7 6 5 
5 6 7 8 1 2 3 4 
6 5 8 7 2 1 4 3 
7 8 5 6 3 4 1 2 
8 7 6 5 4 3 2 1 
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
    tst14();
	return 0;
}