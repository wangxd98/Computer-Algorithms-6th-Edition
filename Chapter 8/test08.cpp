#include <bits/stdc++.h>
using namespace std;
#include "ch08.h"

void tst01()
{
    cout<<"Test LinearProgram"<<endl;
    char fname[10]="tst01.in";
    LinearProgram X(fname);
    X.solve();
}
/*
tst01.in:
-1 5 4
2 0 3
1 0 0 0 2
0 1 0 0 1.5
300 1000 10 1500 2500
20 110 10 0 200
15 10 8 48 100
50 80 15 180 
tst01.out:
Test LinearProgram
Minimize:
   50.00 * x1 + 
   80.00 * x2 + 
   15.00 * x3 + 
  180.00 * x4
约束条件:
#1...    1.00 * x1 +      0.00 * x2 +      0.00 * x3 +      0.00 * x4 <=     2.00
#2...    0.00 * x1 +      1.00 * x2 +      0.00 * x3 +      0.00 * x4 <=     1.50
#3...  300.00 * x1 +   1000.00 * x2 +     10.00 * x3 +   1500.00 * x4 >=  2500.00
#4...   20.00 * x1 +    110.00 * x2 +     10.00 * x3 +      0.00 * x4 >=   200.00
#5...   15.00 * x1 +     10.00 * x2 +      8.00 * x3 +     48.00 * x4 >=   100.00
最优值：335.2344
最优解：
x1= 0.0000
x2= 1.5000
x3= 6.9010
x4= 0.6207
*/

void tst02()
{
    cout<<"Test input"<<endl;
    char fname[10]="tst02.in";
    char oname[10]= "tst02.out";
	input(fname,oname);
}
/*
tst02.in:
5
232 1165 1901 2108 3790 
271 295 155 369 300 
100 32 135 165 
60 272 113 
202 33 
365
tst02.out:
-1 5 15
0 0 5
1 1 1 1 1 0 0 0 0 0 0 0 0 0 0 232
0 1 1 1 1 1 1 1 1 0 0 0 0 0 0 1165
0 0 1 1 1 0 1 1 1 1 1 1 0 0 0 1901
0 0 0 1 1 0 0 1 1 0 1 1 1 1 0 2108
0 0 0 0 1 0 0 0 1 0 0 1 0 1 1 3790
271 295 155 369 300 100 32 135 165 60 272 113 202 33 365
*/

void tst03()
{
    cout<<"Test MAXFLOW"<<endl;
    int n,m,s,t,x,y,z,maxflow=0;
    cin>>n>>m>>s>>t;
    s--,t--;
    GRAPH<EDGE> G(n,1);
    while(m--){
        cin>>x>>y>>z;
        x--,y--;
        G.insert(new EDGE(x,y,z));
    }
    MAXFLOW<GRAPH<EDGE>,EDGE>(G,s,t,maxflow);
    cout<<maxflow<<endl;
}
/*
tst03.in:
4 5 4 3
4 2 30
4 3 20
2 3 20
2 1 30
1 3 30
tst03.out:
Test MAXFLOW1
50
*/

void tst04()
{
    cout<<"Test MAXFLOW1"<<endl;
    int n,m,s,t,x,y,z,maxflow=0;
    cin>>n>>m>>s>>t;
    s--,t--;
    GRAPH<EDGE> G(n,1);
    while(m--){
        cin>>x>>y>>z;
        x--,y--;
        G.insert(new EDGE(x,y,z));
    }
    MAXFLOW1<GRAPH<EDGE>,EDGE>(G,s,t,maxflow);
    cout<<maxflow<<endl;
}
/*
tst04.in:
4 5 4 3
4 2 30
4 3 20
2 3 20
2 1 30
1 3 30
tst04.out:
Test MAXFLOW
50
*/

void tst05()
{
    cout<<"Test FEASIBLE"<<endl;
    int n,m,x,y,z;
    cin>>n>>m;
    GRAPH<EDGE>G(n,1);
    while(m--){
        cin>>x>>y>>z;
        x--,y--;
        G.insert(new EDGE(x,y,z));
    }
    vector<int> sd(n);
    for(int i=0;i<n;i++)cin>>sd[i];
    FEASIBLE<GRAPH<EDGE>,EDGE>(G,sd);
}
/*
tst05.in:
7 14
1 2 5
1 3 6
1 4 5
2 3 2
2 5 3
3 2 2
3 4 3
3 5 3
3 6 7
4 6 5
5 6 1
6 5 1
5 7 8
6 7 7
11 0 1 2 -7 0 -7
tst05.out:
Test FEASIBLE
supply ok
demand met
1->2 3
1->3 6
1->4 2
2->5 3
3->5 3
3->6 4
4->6 4
5->9 7
6->5 1
6->7 7
7->9 7
8->1 11
8->3 1
8->4 2
*/

void tst06()
{
    cout<<"Test BMATCHING"<<endl;
    int n,m,e,x,y;
    cin>>m>>n>>e;
    GRAPH<EDGE> G(n,1);
    for(int i=0;i<e;i++){
    	cin>>x>>y;
		if(x>y)swap(x,y);
		if(x>=n)cout<<"input error "<<x<<" "<<y<<endl;
    	x--,y--;
        G.insert(new EDGE(x,y,1));
    }
    BMATCHING<GRAPH<EDGE>,EDGE>(G,m);
}
/*
tst06.in:
5 10 10
1 7
1 8
2 6
2 9
2 10
3 7
3 8
4 7
4 8
5 10
tst06.out:
Test BMATCHING
4
1 7
2 9
3 8
5 10
*/

void tst07()
{
    cout<<"Test LOWER"<<endl;
	int n,m,s,t,x,y,caplow,cap,c=0;
    cin>>n>>m>>s>>t;
    	s--,t--;
    	vector<int> sd(n);
        GRAPH<EDGE> G(n,1);
        for(int i=0;i<m;i++){
    	    cin>>x>>y>>caplow>>cap;
    	    x--,y--;
            sd[y]+=caplow,sd[x]-=caplow;
			G.insert(new EDGE(x,y,cap,c,caplow));    	    
        }
        LOWER<GRAPH<EDGE>,EDGE>(G,s,t,sd);
}
/*
tst07.in:
6 8 1 6
1 2 1 3
1 4 0 10
2 3 4 7
4 5 2 8
3 4 1 3
5 2 2 4
3 6 2 5
5 6 2 6
tst07.out:
Test LOWER
Maxflow=10
1->2 3
1->4 7
2->3 5
3->4 1
3->6 4
4->5 8
5->2 2
5->6 6
*/

void tst08()
{
    cout<<"Test LOWERm"<<endl;
	int n,m,s,t,x,y,caplow,cap,c=0;
    cin>>n>>m>>s>>t;
    	s--,t--;
    	vector<int> sd(n);
        GRAPH<EDGE> G(n,1);
        for(int i=0;i<m;i++){
    	    cin>>x>>y>>caplow>>cap;
    	    x--,y--;
            sd[y]+=caplow,sd[x]-=caplow;
			G.insert(new EDGE(x,y,cap,c,caplow));    	    
        }
        LOWERm<GRAPH<EDGE>,EDGE>(G,s,t,sd);
}
/*
tst08.in:
6 8 1 6
1 2 1 3
1 4 0 10
2 3 4 7
4 5 2 8
3 4 1 3
5 2 2 4
3 6 2 5
5 6 2 6
tst08.out:
Test LOWERm
4
1->2 2
1->4 2
2->3 4
3->4 2
3->6 2
4->5 4
5->2 2
5->6 2
*/

void tst09()
{
    cout<<"Test MINCOST cycles"<<endl;
	int n,m,s,t,x,y,cap,c;
    cin>>n>>m>>s>>t;
  	s--,t--;
    GRAPH<EDGE> G(n,1);
    for(int i=0;i<m;i++){
  	    cin>>x>>y>>cap>>c;
  	    x--,y--;
	    G.insert(new EDGE(x,y,cap,c)); 	  
    }
    MINCOST<GRAPH<EDGE>,EDGE>(G,s,t);
    cout<<cost<GRAPH<EDGE>,EDGE>(G)<<endl;
}
/*
tst09.in:
6 8 1 6
1 2 4 1
1 3 8 5
2 3 5 0
3 5 10 1
5 4 8 0
5 6 8 9
4 2 8 1
4 6 8 1
tst09.out:
Test MINCOST cycles
70
*/

void tst10()
{
    cout<<"Test MINCOST1 shortest"<<endl;
	int n,m,s,t,x,y,cap,c;
    cin>>n>>m>>s>>t;
  	s--,t--;
    GRAPH<EDGE> G(n,1);
    for(int i=0;i<m;i++){
  	    cin>>x>>y>>cap>>c;
  	    x--,y--;
	    G.insert(new EDGE(x,y,cap,c)); 	  
    }
    MINCOST1<GRAPH<EDGE>,EDGE>(G,s,t);
    cout<<cost<GRAPH<EDGE>,EDGE>(G)<<endl;
}
/*
tst10.in:
6 8 1 6
1 2 4 1
1 3 8 5
2 3 5 0
3 5 10 1
5 4 8 0
5 6 8 9
4 2 8 1
4 6 8 1
tst10.out:
Test MINCOST1 shortest
70
*/

void tst11()
{
    cout<<"Test MINCOST2 simplex"<<endl;
	int n,m,s,t,x,y,cap,c;
    cin>>n>>m>>s>>t;
  	s--,t--;
    GRAPH<EDGE> G(n,1);
    for(int i=0;i<m;i++){
  	    cin>>x>>y>>cap>>c;
  	    x--,y--;
	    G.insert(new EDGE(x,y,cap,c)); 	  
    }
    MINCOST2<GRAPH<EDGE>,EDGE>(G,s,t);
    cout<<cost<GRAPH<EDGE>,EDGE>(G)<<endl;
}
/*
tst11.in:
6 8 1 6
1 2 4 1
1 3 8 5
2 3 5 0
3 5 10 1
5 4 8 0
5 6 8 9
4 2 8 1
4 6 8 1
tst11.out:
Test MINCOST2 simplex
70
*/

void tst12()
{
    cout<<"Test LOWERc"<<endl;
	int n,m,s,t,se,x,y,caplow,cap,c;
    cin>>n>>m>>s>>t;
  	s--,t--;
    GRAPH<EDGE> G(n,1);
	vector<int> sd(n,0);
    for(int i=0;i<m;i++){
  	    cin>>x>>y>>caplow>>cap>>c;
  	    x--,y--;
		sd[y]+=caplow;sd[x]-=caplow;
	    G.insert(new EDGE(x,y,cap,c,caplow));
    }
    LOWERc<GRAPH<EDGE>,EDGE>(G,s,t,sd);
}
/*
tst12.in:
6 8 1 6
1 2 1 3 87
1 4 0 10 14
2 3 4 7 78
4 5 2 8 45
3 4 1 3 47
5 2 2 4 27
3 6 2 5 19
5 6 2 6 46
tst12.out:
Test LOWERc
10 1562
*/

void tst13()
{
    cout<<"Test LOWERc1"<<endl;
	int n,m,s,t,se,x,y,caplow,cap,c;
    cin>>n>>m>>s>>t;
  	s--,t--;
    GRAPH<EDGE> G(n,1);
	vector<int> sd(n,0);
    for(int i=0;i<m;i++){
  	    cin>>x>>y>>caplow>>cap>>c;
  	    x--,y--;
		sd[y]+=caplow;sd[x]-=caplow;
	    G.insert(new EDGE(x,y,cap,c,caplow));
    }
    LOWERc1<GRAPH<EDGE>,EDGE>(G,s,t,sd);
}
/*
tst13.in:
6 8 1 6
1 2 1 3 87
1 4 0 10 14
2 3 4 7 78
4 5 2 8 45
3 4 1 3 47
5 2 2 4 27
3 6 2 5 19
5 6 2 6 46
tst13.out:
Test LOWERc1
4 971
*/

void tst14()
{
    cout<<"Test ASSIGNMENT"<<endl;
	int n,m,x,y,c;
    cin>>n>>m;
    GRAPH<EDGE> G(2*n,1);
    for(int i=0;i<m;i++){
  	    cin>>x>>y>>c;
		x--,y--;
	    G.insert(new EDGE(x,y+n,1,c));
    }
	ASSIGNMENT<GRAPH<EDGE>,EDGE>H(G);
}
/*
tst14.in:
5 10
1 2 2
1 3 2
2 1 1
2 4 2
2 5 2
3 2 1
3 3 1
4 2 1
4 3 1
5 5 2
tst14.out:
Test ASSIGNMENT
4 5
*/

void tst15()
{
	int n,m,s,t,x,y,c;
    cout<<"Test ConsecLP"<<endl;
    cin>>m>>n;
  	s=0,t=m+2;
    GRAPH<EDGE>G(t+1,1);
	vector<int>a(m+2,0);
	for(int i=1;i<=m;i++){
		cin>>a[i];
		G.insert(new EDGE(i+1,i,INF,0));
	}
    for(int i=1;i<=n;i++){
        cin>>x>>y>>c;
        G.insert(new EDGE(x,y+1,INF,c));
	} 
    for(int i=1;i<=m+1;i++){
        if(a[i]-a[i-1]>0)G.insert(new EDGE(s,i,a[i]-a[i-1],0));
        if(a[i]-a[i-1]<0)G.insert(new EDGE(i,t,a[i-1]-a[i],0));
    }
	ConsecLP<GRAPH<EDGE>,EDGE>(G,s,t);
}
/*
tst15.in:
4 5
5 12 10 6
2 4 1
1 4 2
3 4 3
1 1 4
1 2 5
tst15.out:
Test ConsecLP
17
*/

void tst16()
{
	int n,m,f;
    cout<<"Test ESCAPE"<<endl;
	cin>>m>>n>>f;
	ESCAPE E(m,n,f);
	cout<<E.solution()<<endl;
}
/*
tst16.in:
6 6 10
2 2
2 4
2 6
3 1
3 2
3 4
3 6
4 2
4 4
4 6
tst16.out:
Test ESCAPE
11
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
    tst16();
	return 0;
}
