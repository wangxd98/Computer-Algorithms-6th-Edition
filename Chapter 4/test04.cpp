#include <bits/stdc++.h>
using namespace std;
#include "ch04.h"

void tst01()
{
    cout<<"Test GreedySelector"<<endl;
    int n=11,s[12]={0,1,3,0,5,3,5,6,8,8,2,12},
	    f[12]={0,4,5,6,7,8,9,10,11,12,13,14};
    bool a[12];
    GreedySelector(n,s,f,a);
	for(int i=1;i<=n;i++)
		if(a[i])cout<<i<<" ";
	cout<<endl;
}
/*
Test GreedySelector
1 4 8 11 
*/

void tst02()
{
    cout<<"Test Knapsack"<<endl;
    int n;
    float M,w[maxint],v[maxint],x[maxint];
    while(cin>>n>>M){
    	for(int i=1;i<=n;i++)cin>>w[i]>>v[i];
    	Knapsack(n,M,v,w,x);
        for(int i=1;i<=n;i++)cout<<w[i]<<" "<<v[i]<<" "<<x[i]<<endl;
	}
}
/*
tst02.in
7 150
35 10
30 40
60 30
50 50
40 35
10 40
25 30
tst02.out
Test Knapsack
10 40 1
30 40 1
25 30 1
50 50 1
40 35 0.875
60 30 0
35 10 0
*/

void tst03()
{
    cout<<"Test Loading"<<endl;
    int n,c,w[maxint],x[maxint];
    while(cin>>n>>c){
    	for(int i=1;i<=n;i++)cin>>w[i];
    	Loading(x,w,c,n);
        for(int i=1;i<=n;i++)cout<<x[i]<<" ";cout<<endl;
	}
}
/*
tst03.in
8 400
100 200 50 90 150 50 20 80
tst03.out
Test Loading
1 0 1 1 0 1 1 1 
*/

void tst04()
{
    cout<<"Test HuffmanTree"<<endl;
    int n=10,f[11];
    BinaryTree<int> x;
    for (int i=1;i<=n;i++)f[i]=2*i;
    x=HuffmanTree(f,n);
    x.PostOutput();
}
/*
tst04.out
Test HuffmanTree
10 3 1 2 0 0 6 0 0 7 8 0 9 4 5 0 0 0 0 
*/

void tst05()
{
    cout<<"Test Dijkstra"<<endl;
    int n,v,x,y,z,dist[500],prev[500],**c;
    make2dArray(c,n+1,n+1);
    cin>>n>>v;
    make2dArray(c,n+1,n+1);
	for(int i=0;i<=n;i++)
		for(int j=0;j<=n;j++)c[i][j]=maxint;
    while(cin>>x>>y>>z){
    	c[x][y]=z;
	}
    Dijkstra(n,v,dist,prev,c);
    for(int i=1;i<=n;i++){
    	if(i!=v)cout<<v<<" -> "<<i<<" : "<<dist[i]<<endl;
	}
	delete2dArray(c,n+1);
}
/*
tst05.in
5 1
1 2 10
1 4 30
1 5 100
2 3 50
3 5 10
4 3 20
4 5 60
tst05.out
Test Dijkstra
1 -> 2 : 10
1 -> 3 : 50
1 -> 4 : 30
1 -> 5 : 60
*/

void tst06()
{
    cout<<"Test Prim"<<endl;
    int n,m,u,v,w,**c;
    make2dArray(c,maxint,maxint);
	while(cin>>n>>m){
		for(int i=0;i<=n;i++)
		    for(int j=0;j<=n;j++)c[i][j]=inf;
		for(int i=1;i<=m;i++){
		    cin>>u>>v>>w;
			c[u][v]=c[v][u]=w;
		}
        cout<<Prim(n,c)<<endl;
    }
	delete2dArray(c,maxint);
}
/*
tst06.in
7 11
1 2 7
1 4 5
2 4 9
2 3 8
2 5 7
4 5 15
4 6 6
6 7 11
5 6 8
5 7 9
3 5 5
tst06.out
Test Prim
4 1
6 4
2 1
5 2
3 5
7 5
39
*/

void tst07()
{
    cout<<"Test Kruskal"<<endl;
    int n,e;
    EdgeNode<int> E[maxint],t[maxint];
	while(cin>>n>>e){
		for(int i=1;i<=e;i++)cin>>E[i].u>>E[i].v>>E[i].weight;
		int sum=0;
		if(Kruskal(n,e,E,t)){
			for(int i=0;i<n-1;i++)sum+=t[i].weight,cout<<t[i].u<<"->"<<t[i].v<<endl;
		}
		cout<<sum<<endl;
    }
}
/*
tst07.in
7 11
1 2 7
1 4 5
2 4 9
2 3 8
2 5 7
4 5 15
4 6 6
6 7 11
5 6 8
5 7 9
3 5 5
tst07.out
Test Kruskal
1->4
3->5
4->6
2->5
1->2
5->7
39
*/

void tst08()
{
    cout<<"Test Greedy"<<endl;
    int n,m;
    JobNode a[10];
	while(cin>>n>>m){
		for(int i=1;i<=n;i++){
			cin>>a[i].time;
		    a[i].ID=i;
		}
        Greedy(a,n,m);
    }
}
/*
tst08.in
7 3
2 14 4 16 6 5 3
tst08.out
Test Greedy
将机器 1 从 0 到 3 的时间段分配给作业 7
将机器 3 从 0 到 16 的时间段分配给作业 4
将机器 2 从 0 到 14 的时间段分配给作业 2
将机器 1 从 3 到 9 的时间段分配给作业 5
将机器 1 从 9 到 14 的时间段分配给作业 6
将机器 2 从 14 到 18 的时间段分配给作业 3
将机器 1 从 14 到 16 的时间段分配给作业 1
*/

void tst09()
{
    cout<<"Test GreedyJob"<<endl;
    int n,d[10],w[10],J[10];
	while(cin>>n){
		int sum=0;
		for(int i=1;i<=n;i++)cin>>d[i]>>w[i],sum+=w[i];
        int k=GreedyJob(n,d,J);
        for(int i=1;i<=k;i++)cout<<J[i]<<" ",sum-=w[J[i]];cout<<endl;
        cout<<sum<<endl;
    }
}
/*
tst09.in
7
4 70
2 60
4 50
3 40
1 30
4 20
6 10
tst09.out
Test GreedyJob
2 4 1 3 7 
50
*/

void tst10()
{
    cout<<"Test FasterJob"<<endl;
    int n,d[10],w[10],J[10];
	while(cin>>n){
		int sum=0;
		for(int i=1;i<=n;i++)cin>>d[i]>>w[i],sum+=w[i];
        int k=FasterJob(n,d,J);
        for(int i=1;i<=k;i++)cout<<J[i]<<" ",sum-=w[J[i]];cout<<endl;
        cout<<sum<<endl;
    }
}
/*
tst10.in
7
4 70
2 60
4 50
3 40
1 30
4 20
6 10
tst10.out
Test FasterJob
1 2 3 4 7 
50
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
    tst08();
    //tst09();
    //tst10();
	return 0;
}
