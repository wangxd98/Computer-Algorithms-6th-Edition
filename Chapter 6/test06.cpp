#include <bits/stdc++.h>
using namespace std;
#include "ch06.h"

void tst01()
{
    cout<<"Test ShortestPaths"<<endl;
    int n,e,x,y,z;
	cin>>n>>e;
	Graph<int> G(n);
	for(int i=1;i<=e;i++){
		cin>>x>>y>>z;
		G.c[x][y]=z;G.c[y][x]=z;
	}
	G.ShortestPaths(1);
	for(int i=1;i<=n;i++)cout<<G.dist[i]<<" ";cout<<endl;
}
/*
tst01.in:
5 7
1 2 4
1 3 2
1 5 8
2 4 4
2 5 5
3 4 1
4 5 3
tst01.out:
Test ShortestPaths
0 4 2 3 6 
*/

void tst02()
{
    cout<<"Test MaxLoading1"<<endl;
    int n,c,w[100];	
    while(cin>>n>>c){
    	for(int i=1;i<=n;i++)cin>>w[i];
    	cout<<MaxLoading1(w,c,n)<<endl;
	}
}
/*
tst02.in:
4 12
8 6 2 3
5 10
7 2 6 5 4
tst02.out:
Test MaxLoading1
11
10
*/

void tst03()
{
    cout<<"Test MaxLoading2"<<endl;
    int n,c,w[100];	
    while(cin>>n>>c){
    	for(int i=1;i<=n;i++)cin>>w[i];
    	cout<<MaxLoading2(w,c,n)<<endl;
	}
}
/*
tst02.in:
4 12
8 6 2 3
5 10
7 2 6 5 4
tst02.out:
Test MaxLoading1
11
10
*/

void tst04()
{
    cout<<"Test MaxLoading3"<<endl;
    int n,c,w[100],v[100];	
    while(cin>>n>>c){
    	for(int i=1;i<=n;i++)cin>>w[i];
    	cout<<MaxLoading3(w,c,n,v)<<endl;
    	for(int i=1;i<=n;i++)cout<<v[i]<<" ";cout<<endl;
	}
}
/*
tst04.in:
4 12
8 6 2 3
5 10
7 2 6 5 4
tst04.out:
Test MaxLoading3
11
0 1 1 1 
10
0 0 1 0 1 
*/

void tst05()
{
    cout<<"Test MaxLoading"<<endl;
    int n,c,w[100],v[100];	
    while(cin>>n>>c){
    	for(int i=1;i<=n;i++)cin>>w[i];
    	cout<<MaxLoading(w,c,n,v)<<endl;
    	for(int i=1;i<=n;i++)cout<<v[i]<<" ";cout<<endl;
	}
}
/*
tst04.in:
4 12
8 6 2 3
5 10
7 2 6 5 4
tst04.out:
Test MaxLoading
11
0 1 1 1 
10
0 0 1 0 1 
*/

void tst06()
{
    cout<<"Test FindPath"<<endl;
    Position start,finish,p[50];
    int len;	
    while(cin>>n>>m){
    	cin>>start.row>>start.col;
	    cin>>finish.row>>finish.col;
    	for(int i=1;i<=m;i++)
		    for(int j=1;j<=n;j++)
			  cin>>grid[i][j];
    	FindPath(start,finish,len,p);
    	cout<<len<<endl;
    	for(int i=0;i<len;i++)cout<<p[i].col<<" "<<p[i].row<<endl;
	}
}
/*
tst06.in:
7 7
3 2
4 6
0 0 1 0 0 0 0
0 0 1 1 0 0 0
0 0 0 0 1 0 0
0 0 0 1 1 0 0
1 0 0 0 1 0 0
1 1 1 0 0 0 0
1 1 1 0 0 0 0
tst06.out:
Test FindPath
9
2 4
2 5
3 5
4 5
4 6
5 6
6 6
6 5
6 4
*/

void tst07()
{
    cout<<"Test Knapsack"<<endl;
    int n,v[100];
    double c,p[100],w[100];
    while(cin>>n>>c){
       for(int i=1;i<=n;i++)cin>>p[i]>>w[i];
       cout <<Knapsack(p,w,c,n,v)<<endl;
       for(int i=1;i<=n;i++)cout<<v[i]<<" ";cout<<endl;
    }
}
/*
tst07.in:
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
tst07.out:
Test Knapsack
20
1 0 1 1 
15
1 1 0 0 1 
130
1 1 1 1 0 1 1 1 1 1 
*/

void tst08()
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
	    Clique C(n,a);
	    cout<<C.BBMaxClique(v)<<endl;
	    for(int i=1;i<=n;i++)if(v[i])cout<<i<<" ";cout<<endl;
	}
	delete2dArray(a,100);
}
/*
tst08.in:
7 10
1 2
1 4
2 4
2 3
2 5
2 6
3 5
3 6
4 5
5 6
tst08.out:
Test MaxClique
4
2 3 5 6 
*/

void tst09()
{
    cout<<"Test BBTSP"<<endl;
    int n,m,x,y,z,v[100],**a;
    const int NoEdge=0;
    make2dArray(a,100,100);
    while(cin>>n>>m){
        for(int i=0;i<=n;i++)
            for(int j=0;j<=n;j++)a[i][j]=NoEdge;
        for(int i=1;i<=m;i++){
        	cin>>x>>y>>z;a[x][y]=a[y][x]=z;
		}
		Traveling<int> Trav(n,a,NoEdge);
	    cout<<Trav.BBTSP(v)<<endl;
        for(int i=1;i<=n;i++)cout<<v[i]<<" ";
        cout<<v[1]<<endl;
	}
	delete2dArray(a,100);
}
/*
tst09.in:
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
tst09.out:
Test BBTSP
25
1 3 2 4 1
31
1 4 2 6 5 3 7 1
*/

void tst10()
{
    cout<<"Test BBArrangement"<<endl;
    int n,m,**B;
    int *p=new int[500];
    make2dArray(B,100,100);
    while(cin>>n>>m){
        for(int i=1;i<=n;i++) 
            for(int j=1;j<=m;j++)
                cin>>B[i][j];
		cout <<BBArrangement(B,n,m,p)<< endl;
		copy(p+1,p+n+1,ostream_iterator<int>(cout," "));
        cout<<endl;
    }
    delete2dArray(B,100);
}
/*
tst10.in:
8 5
1 1 1 1 1
0 1 0 1 0
0 1 1 1 0
1 0 1 1 0
1 0 1 0 0
1 1 0 1 0
0 0 0 0 1
0 1 0 0 1
tst10.out:
Test BBArrangement
4
2 8 7 3 1 5 6 4 
*/

void tst11()
{
    cout<<"Test BBFlow"<<endl;
    int n,bestx[100],**M,**a,**b;
    bool **y;
    make2dArray(M,100,2);
    make2dArray(a,100,2);
    make2dArray(b,100,2);
    make2dArray(y,100,2);
    while(cin>>n){
	    for(int i=0;i<2;i++)
            for(int j=0;j<n;j++)
                cin>>M[j][i];
        Flowshop F;
	    F.n=n;F.M=M;F.b=b;F.a=a;F.y=y;
	    F.bestx=bestx;
        F.bestc=INT_MAX;
	    cout<<F.BBFlow()<<endl;
	    for(int i=0;i<n;i++)cout<<bestx[i]+1<<" ";cout<<endl;
	}
	delete2dArray(M,100);
	delete2dArray(a,100);
	delete2dArray(b,100);
	delete2dArray(y,100);
}
/*
tst11.in:
3
2 3 2
1 1 3
3
2 5 4
3 2 1
5
2 5 4 1 3
3 2 1 5 2
tst11.out:
Test BBFlow
18
1 3 2 
25
1 3 2 
52
4 3 1 5 2 
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
    tst11();
	return 0;
}
