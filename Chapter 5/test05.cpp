#include <bits/stdc++.h>
using namespace std;
#include "ch05.h"

void tst01()
{
    cout<<"Test MaxLoading1"<<endl;
    int n=5,c=10,w[] = {0,7,2,6,5,4};
	cout<<MaxLoading1(w,c,n)<<endl;
}
/*
tst01.out:
Test MaxLoading1
10
*/

void tst02()
{
    cout<<"Test MaxLoading2"<<endl;
    int n=5,c=10,w[] = {0,7,2,6,5,4};
	cout<<MaxLoading2(w,c,n)<<endl;
}
/*
tst02.out:
Test MaxLoading2
10
*/

void tst03()
{
    cout<<"Test MaxLoading3"<<endl;
    int n=5,c=10,w[] = {0,7,2,6,5,4},bestx[6];
	cout<<MaxLoading3(w,c,n,bestx)<<endl;
	for(int i=1;i<6;i++)cout<<bestx[i]<<" ";cout<<endl;
}
/*
tst03.out:
Test MaxLoading3
10
0 0 1 0 1 
*/

void tst04()
{
    cout<<"Test MaxLoading"<<endl;
    int n=5,c=10,w[] = {0,7,2,6,5,4},bestx[6];
	cout<<MaxLoading(w,c,n,bestx)<<endl;
	for(int i=1;i<6;i++)cout<<bestx[i]<<" ";cout<<endl;
}
/*
tst04.out:
Test MaxLoading
10
0 0 1 0 1 
*/

void tst05()
{
    cout<<"Test Flow"<<endl;
    int n,w[100],bestx[100],**m;
    make2dArray(m,100,100);
    while(cin>>n){
	    for(int i=1;i<=2;i++)
            for(int j=1;j<=n;j++)
                cin>>m[j][i];
	    cout<<Flow(m,n,bestx)<<endl;
	    for(int i=1;i<=n;i++)cout<<bestx[i]<<" ";cout<<endl;
	}
	delete2dArray(m,100);
}
/*
tst05.in:
3
2 3 2
1 1 3
3
2 5 4
3 2 1
5
2 5 4 1 3
3 2 1 5 2
tst05.out:
Test Flow
18
1 3 2 
25
1 3 2 
52
4 3 1 5 2 
*/

void tst06()
{
    cout<<"Test Triangle"<<endl;
    int n;
    while(cin>>n)cout<<Compute(n)<<endl;
}
/*
tst06.in:
3
4
5
6
7
8
11
12
16
18
19
tst06.out:
Test Triangle
4
6
0
0
12
40
171
410
5160
0
32757
*/

void tst07()
{
    cout<<"Test nQueen"<<endl;
    int n;
    while(cin>>n){
        cout<<nQueen(n)<<endl;
	}
}
/*
tst07.in:
4
5
6
7
8
15
tst07.out:
Test nQueen
2
10
4
40
92
2279184
*/

void tst08()
{
    cout<<"Test nQueen1"<<endl;
    int n;
    while(cin>>n){
        cout<<nQueen1(n)<<endl;
	}
}
/*
tst08.in:
4
5
6
7
8
15
tst08.out:
Test nQueen
2
10
4
40
92
2279184
*/

void tst09()
{
    cout<<"Test Knapsack"<<endl;
   int n;
   double c,p[100],w[100];
   while(cin>>n>>c){
       for(int i=1;i<=n;i++)cin>>p[i]>>w[i];
       cout <<Knapsack(p,w,c,n)<<endl;
   }
}
/*
tst09.in:
4 7
9 3
10 5
7 2
4 1
5 10
6 2
3 2
5 6
4 5
6 4
10 100
15 5
17 13
9 7
13 3
7 15
9 16
18 20
15 8
14 11
20 10
tst09.out:
Test Knapsack
20
15
130
*/

void tst10()
{
    cout<<"Test MaxClique"<<endl;
    int n,m,x,y,v[100],**a;
    make2dArray(a,100,100);
    while(cin>>n>>m){
        for(int i=0;i<=n;i++)
            for(int j=0;j<=n;j++)a[i][j]=0;
        for(int i=1;i<=m;i++){
        	cin>>x>>y;a[x][y]=a[y][x]=1;
		}
	    cout<<MaxClique(a,v,n)<<endl;
	    for(int i=1;i<=n;i++)if(v[i])cout<<i<<" ";cout<<endl;
	}
	delete2dArray(a,100);
}
/*
tst10.in:
5 7
1 2
1 4
1 5
2 3
2 5
3 5
4 5
10 30
1 2
1 5
1 6
1 9
1 10
2 4
2 5
2 9
2 10
3 4
3 5
3 7
3 9
3 10
4 5
4 6
4 9
5 7
5 8
5 9
5 10
6 7
6 9
6 10
7 8
7 9
7 10
8 9
8 10
9 10
tst10.out:
Test MaxClique
3
1 2 5 
5
1 2 5 9 10 
*/

void tst11()
{
    cout<<"Test mColoring"<<endl;
    int n,e,m,x,y,v[100],**a;
    make2dArray(a,100,100);
    while(cin>>n>>e>>m){
        for(int i=0;i<=n;i++)
            for(int j=0;j<=n;j++)a[i][j]=0;
        for(int i=1;i<=e;i++){
        	cin>>x>>y;a[x][y]=a[y][x]=1;
		}
	    cout<<mColoring(n,m,a)<<endl;
	}
	delete2dArray(a,100);
}
/*
tst11.in:
5 8 4
1 2
1 3
1 4
2 3
2 4
2 5
3 4
4 5
tst11.out:
mColoring
48
*/

void tst12()
{
    cout<<"Test TSP"<<endl;
    int n,m,x,y,z,v[100],**a;
    const int NoEdge=0;
    make2dArray(a,100,100);
    while(cin>>n>>m){
        for(int i=0;i<=n;i++)
            for(int j=0;j<=n;j++)a[i][j]=NoEdge;
        for(int i=1;i<=m;i++){
        	cin>>x>>y>>z;a[x][y]=a[y][x]=z;
		}
	    cout<<TSP(a,v,n,NoEdge)<<endl;
        for(int i=1;i<=n;i++)cout<<v[i]<<" ";
        cout<<v[1]<<endl;
	}
	delete2dArray(a,100);
}
/*
tst12.in:
4 6
1 2 30
1 3 6
1 4 4 
2 4 10
2 3 5
3 4 20
7 8
1 4 5
4 2 8
2 6 3
6 5 1
5 3 3
3 7 2
7 1 9
1 5 10
tst12.out:
Test TSP
25
1 3 2 4 1
31
1 4 2 6 5 3 7 1
*/

void tst13()
{
    cout<<"Test CirclePerm"<<endl;
	int n;
	float a[100];
	cout<<fixed<<setprecision(2);
	while (cin >> n) {
		for (int i=1;i<=n;i++)cin>>a[i];
		cout <<CirclePerm(n,a)<<endl;
	}
}
/*
tst13.in:
3
1 1 2
4
2 4 1 1
tst13.out:
Test CirclePerm
7.66
13.83
*/

void tst14()
{
    cout<<"Test Arrangement"<<endl;
    int n,m,p[100],**B;
    make2dArray(B,100,100);
    while(cin>>n>>m){
        for(int i=1;i<=n;i++) 
            for(int j=1;j<=m;j++)
                cin>>B[i][j];
		cout <<Arrangement(B,n,m,p)<< endl;
		copy(p+1,p+n+1,ostream_iterator<int>(cout," "));
        cout<<endl;
    }
    delete2dArray(B,100);
}
/*
tst14.in:
8 5
1 1 1 1 1
0 1 0 1 0
0 1 1 1 0
1 0 1 1 0
1 0 1 0 0
1 1 0 1 0
0 0 0 0 1
0 1 0 0 1
tst14.out:
Test Arrangement
4
2 3 4 5 1 6 7 8
*/

void tst15()
{
    cout<<"Test MaxStamp"<<endl;
    int n,m,p[100];
    while(cin>>n>>m){
		cout <<MaxStamp(n,m,p)<< endl;
		copy(p+1,p+n+1,ostream_iterator<int>(cout," "));
        cout<<endl;
    }
}
/*
tst15.in:
5 4
4 6
tst15.out:
Test MaxStamp
70
1 3 11 15 32 
114
1 4 19 33 
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
    tst15();
	return 0;
}
