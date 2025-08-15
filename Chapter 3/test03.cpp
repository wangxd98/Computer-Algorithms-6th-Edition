#include <bits/stdc++.h>
using namespace std;
#include "ch03.h"

void tst01()
{
    cout<<endl<<"Test matrixMultiply"<<endl;
    int **a,**b,**c,n,k,l;
    n=5;k=3,l=3;
    make2dArray(a,n,k);
    make2dArray(b,k,l);
    make2dArray(c,n,l);
    for(int i=0;i<n;i++)
	    for(int j=0;j<k;j++)
            a[i][j]=i+j+1;
    for(int i=0;i<n;i++){
    	for(int j=0;j<k;j++)cout<<a[i][j]<<" ";
    	cout<<endl;
	}
	cout<<endl;
    for(int i=0;i<k;i++)
	    for(int j=0;j<l;j++)
            b[i][j]=i+j+3;
    for(int i=0;i<k;i++){
    	for(int j=0;j<l;j++)cout<<b[i][j]<<" ";
    	cout<<endl;
	}
	cout<<endl;
    matrixMultiply(a,b,c,n,k,k,l);
    for(int i=0;i<n;i++){
    	for(int j=0;j<l;j++)cout<<c[i][j]<<" ";
    	cout<<endl;
	}
	cout<<endl;
    delete2dArray(c,n);delete2dArray(b,k);delete2dArray(a,n);
}
/*
Test matrixMultiply
1 2 3 
2 3 4 
3 4 5 
4 5 6 
5 6 7 

3 4 5 
4 5 6 
5 6 7 

26 32 38 
38 47 56 
50 62 74 
62 77 92 
74 92 110 
*/	    

void tst02()
{
	// input: tst02.in
	cout<<endl<<"Test MatrixChain"<<endl;
    int n,*p,**s,**m;
    cin>>n;
    p=new int [n+1];
    make2dArray(s,n+1,n+1);
    make2dArray(m,n+1,n+1);
    for(int i=1;i<=n;i++)
        for(int j=i;j<=n;j++)
            m[i][j]=0;
    for(int i=0;i<=n;i++)cin>>p[i];
    MatrixChain(p,n,m,s);
    cout<<"Minimum cost="<<m[1][n]<<endl;
    Traceback(1,n,s);
    cout<<"m="<<endl;
    for(int i=1;i<=n;i++){
    	for(int j=i;j<=n;j++)cout<<m[i][j]<<" ";
    	cout<<endl;
	}
    cout<<"s="<<endl;
    for(int i=1;i<=n;i++){
    	for(int j=i;j<=n;j++)cout<<s[i][j]<<" ";
    	cout<<endl;
	}
    delete2dArray(m,n+1);delete2dArray(s,n+1);
    delete[]p;
}
/*
tst02.in
6 30 35 15 5 10 20 25
tst02.out
Test MatrixChain
Minimum cost=15125
Multiply m 2,2 and m 3,3
Multiply m 1,1 and m 2,3
Multiply m 4,4 and m 5,5
Multiply m 4,5 and m 6,6
Multiply m 1,3 and m 4,6
m=
0 15750 7875 9375 11875 15125 
0 2625 4375 7125 10500 
0 750 2500 5375 
0 1000 3500 
0 5000 
0 
s=
0 1 1 3 3 3 
0 2 3 3 3 
0 3 3 3 
0 4 5 
0 5 
0 
*/

void tst03()
{
	// input: tst02.in
	cout<<endl<<"Test RecurMatrixChain"<<endl;
    int n;
    cin>>n;
    p=new int [n+1];
    make2dArray(s,n+1,n+1);
    for(int i=0;i<=n;i++)cin>>p[i];
    cout<<"Minimum cost="<<RecurMatrixChain(1,n)<<endl;
    Traceback(1,n,s);
	delete2dArray(s,n+1);
    delete[]p;
}
/*
tst02.in
6 30 35 15 5 10 20 25
tst03.out
Test RecurMatrixChain
Minimum cost=15125
Multiply m 2,2 and m 3,3
Multiply m 1,1 and m 2,3
Multiply m 4,4 and m 5,5
Multiply m 4,5 and m 6,6
Multiply m 1,3 and m 4,6
*/

void tst04()
{
	// input: tst02.in
	cout<<endl<<"Test MemoizedMatrixChain"<<endl;
    int n,**m;
    cin>>n;
    p=new int [n+1];
    make2dArray(s,n+1,n+1);
    make2dArray(m,n+1,n+1);
    for(int i=0;i<=n;i++)cin>>p[i];
    cout<<"Minimum cost="<<MemoizedMatrixChain(n,m,s)<<endl;
    Traceback(1,n,s);
    delete2dArray(m,n+1);delete2dArray(s,n+1);
    delete[]p;
}
/*
tst02.in
6 30 35 15 5 10 20 25
tst04.out
Test MemoizedMatrixChain
Minimum cost=15125
Multiply m 2,2 and m 3,3
Multiply m 1,1 and m 2,3
Multiply m 4,4 and m 5,5
Multiply m 4,5 and m 6,6
Multiply m 1,3 and m 4,6
*/

void tst05()
{
	cout<<endl<<"Test LCSLength"<<endl;
	int **c,**b;
    char x[100]={ "*ABCBDABAABCD" };
    char y[100]={ "&BDCABABCDAA" };
    int m=strlen(x)-1,n=strlen(y)-1;
    cout<<"m="<<m<<" n="<<n<<endl;
    cout<<"x=";
    for(int i=1;i<=m;i++)cout<<x[i];cout<<endl;
    cout<<"y=";
    for(int i=1;i<=n;i++)cout<<y[i];cout<<endl;
    make2dArray(b,m+1,n+1);
    make2dArray(c,m+1,n+1);
    LCSLength(m,n,x,y,c,b);
    cout<<c[m][n]<<endl;
    cout<<"LCS(x,y)=";
    LCS(m,n,x,b);
    delete2dArray(c,m+1);delete2dArray(b,m+1);
}
/*
tst05.out
Test LCSLength
m=12 n=11
x=ABCBDABAABCD
y=BDCABABCDAA
8
LCS(x,y)=BCABABCD
*/

void tst06()
{
	cout<<endl<<"Test MaxSum0"<<endl;
	int n=8,besti,bestj,a[]={0,-2,11,-4,13,-5,6,-2,1};
	cout<<"a=";
	for(int i=1;i<=n;i++)cout<<a[i]<<" ";cout<<endl;
	cout<<MaxSum0(n,a,besti,bestj)<<endl;
	cout<<"besti="<<besti<<" bestj="<<bestj<<endl;
}
/*
tst06.out
Test MaxSum0
a=-2 11 -4 13 -5 6 -2 1 
21
besti=2 bestj=6
*/

void tst07()
{
	cout<<endl<<"Test MaxSum1"<<endl;
	int n=8,besti,bestj,a[]={0,-2,11,-4,13,-5,6,-2,1};
	cout<<"a=";
	for(int i=1;i<=n;i++)cout<<a[i]<<" ";cout<<endl;
	cout<<MaxSum1(n,a,besti,bestj)<<endl;
	cout<<"besti="<<besti<<" bestj="<<bestj<<endl;
}
/*
tst07.out
Test MaxSum1
a=-2 11 -4 13 -5 6 -2 1 
21
besti=2 bestj=6
*/

void tst08()
{
	cout<<endl<<"Test MaxSum2"<<endl;
	int n=8,a[]={0,-2,11,-4,13,-5,6,-2,1};
	cout<<"a=";
	for(int i=1;i<=n;i++)cout<<a[i]<<" ";cout<<endl;
	cout<<MaxSum2(n,a)<<endl;
}
/*
tst08.out
Test MaxSum2
a=-2 11 -4 13 -5 6 -2 1 
21
*/

void tst09()
{
	cout<<endl<<"Test MaxSum3"<<endl;
	int n=8,a[]={0,-2,11,-4,13,-5,6,-2,1};
	cout<<"a=";
	for(int i=1;i<=n;i++)cout<<a[i]<<" ";cout<<endl;
	cout<<MaxSum3(n,a)<<endl;
}
/*
tst09.out
Test MaxSum3
a=-2 11 -4 13 -5 6 -2 1 
21
*/

void tst10()
{
	// input: tst10.in
	cout<<endl<<"Test MaxSum21"<<endl;
	int m=8,n=8,**a;
	cin>>m>>n;
    make2dArray(a,m+1,n+1);
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)cin>>a[i][j];
    cout<<"m="<<m<<" n="<<n<<endl;
    for(int i=1;i<=m;i++){
    	for(int j=1;j<=n;j++)cout<<a[i][j]<<" ";
    	cout<<endl;
	}
	cout<<MaxSum21(m,n,a)<<endl;
	delete2dArray(a,m+1);
}
/*
tst10.in
4 5
1 -2 -7 0 9 
9 2 -6 2 -1
-4 1 -4 1 5 
-1 8 0 -2 -7
tst10.out
Test MaxSum21
m=4 n=5
1 -2 -7 0 9 
9 2 -6 2 -1 
-4 1 -4 1 5 
-1 8 0 -2 -7 
16
*/

void tst11()
{
	cout<<endl<<"Test MaxSum4"<<endl;
	int m=2,n=8,a[]={0,-2,11,-4,13,-5,6,-2,1};
	cout<<"a=";
	for(int i=1;i<=n;i++)cout<<a[i]<<" ";cout<<endl;
	cout<<MaxSum4(m,n,a)<<endl;
}
/*
tst11.out
Test MaxSum4
a=-2 11 -4 13 -5 6 -2 1 
26
*/

void tst12()
{
	cout<<endl<<"Test MaxSum5"<<endl;
	int m=2,n=8,a[]={0,-2,11,-4,13,-5,6,-2,1};
	cout<<"a=";
	for(int i=1;i<=n;i++)cout<<a[i]<<" ";cout<<endl;
	cout<<MaxSum5(m,n,a)<<endl;
}
/*
tst12.out
Test MaxSum5
a=-2 11 -4 13 -5 6 -2 1 
26
*/

struct node{double x,y;}pt[100];

void tst13()
{
	cout<<endl<<"MinWeightTriangulation"<<endl;
	int n=0,**s;
    double x,y,**t;
    while(cin>>x>>y){
     	pt[n].x=x;pt[n++].y=y;
	}
    make2dArray(t,n,n);
    make2dArray(s,n,n);
	cout<<fixed<<setprecision(2);
	for(int i=0;i<n;i++)len[i][i]=0;
	for(int i=0;i<n;i++)
	    for(int j=i+1;j<n;j++){
		    double dx=pt[i].x-pt[j].x,dy=pt[i].y-pt[j].y;
		    len[i][j]=sqrt(dx*dx+dy*dy);
	    }
	MinWeightTriangulation(n-1,t,s);
	cout<<t[1][n-1]<<endl;
	Tback(1,n-1,s);
    delete2dArray(s,n);delete2dArray(t,n);
}
/*
tst13.in
0 0
0 2
3 2
6 1
3 0
tst13.out
25.54
2 3 4 :w=8.32
1 2 4 :w=8.61
0 1 4 :w=8.61
*/

void tst14()
{
	cout<<endl<<"PolyMax"<<endl;
	int n;
	while(cin>>n){
        for(int i=1;i<=n;i++){
            cin>>op[i]>>v[i];
            m[i][1][1]=v[i];
            m[i][1][0]=v[i];
        }
        cout<<PolyMax(n)<<endl;
	}
}
/*
tst14.in
5
x -3 t -1 t -7 t -4 x -2
4
t -7 t 4 x 2 x 5
5
x 2 x 3 t 1 t 7 x 4
3
t 0 x 1 t -2
30
x 1 t 1 x 1 t 1 t 1 x 1 x 1 x 1 x 1 x 1 x 1 t 1 t 1 x 1 t 1 x 1 x 1 t 1 x 1 x 1 t 1 x 1 x 1 x 1 x 1 x 1 t 1 x 1 x 1 x 1
48
x 1 x 2 x 1 x -1 t 1 x -1 x -1 x 1 t 1 t -1 x 1 t 2 x 1 x 2 t 1 x 1 x -1 x -2 x 1 x 1 t 1 x 1 t 1 x 1 x 1 x 1 t 1 x 1 x 1 x 1 x 1 x 1 x 1 x -1 t 1 x 1 x -1 x -1 t 1 x 1 t 1 x 1 x 1 x -1 t 1 t -1 t -1 x 1
tst14.out
PolyMax
30
33
224
0
288
23328
*/

void tst15()
{
	cout<<endl<<"Compress"<<endl;
	const int N=7; 
    int p[]={0,10,12,15,255,1,2};
    int s[N],l[N],b[N]; 
    for(int i=1;i<N;i++)cout<<p[i]<<" ";cout<<endl; 
    Compress(N-1,p,s,l,b); 
    Output(s,l,b,N-1); 
}
/*
tst15.out
Compress
10 12 15 255 1 2 
The optimal value is 57
Decompose into 3 segments 
3 4
1 8
2 2
*/

void tst16()
{
	cout<<endl<<"MNS"<<endl;
	const int N=10;
	int m,Net[N],C[]={0,8,7,4,2,5,1,9,3,10,6};
    int **size;
    make2dArray(size,N+1,N+1);
    MNS(C,N,size);
    cout<<size[N][N]<<endl;
    Traceback(C,size,N,Net,m);
    for(int i=m-1;i>=0;i--)cout<<"("<<Net[i]<<","<<C[Net[i]]<<") ";
    cout<<endl;
    delete2dArray(size,N+1);
}
/*
tst16.out
MNS
4
(3,4)(5,5)(7,9)(9,10) 
*/

void tst17()
{
	cout<<"FlowShop"<<endl;
    int n,a[maxn],b[maxn],c[maxn];
	while(cin>>n){
        for(int i=0;i<n;i++)cin>>a[i]>>b[i];
        int minT=FlowShop(n,a,b,c);
		cout<<"minT="<<minT<<endl;
		for(int i=0;i<n;i++)cout<<c[i]<<" ";cout<<endl;
	}
}
/*
tst17.in
a[]={2,4,3,6,1};
b[]={5,2,3,1,7};
tst17.out
FlowShop
minT=19
4 0 2 1 3 
minT=35
0 3 4 1 2 5 
*/

void tst18()
{
	cout<<"Knapsack"<<endl;
    int n,c,*w,*v,*x,** m;
    w=new int[maxn+1];
    v=new int[maxn+1];
    x=new int[maxn+1];
    make2dArray(m,maxn+1,maxn+1);
	while(cin>>n>>c){
	    for(int i=1;i<=n;i++)cin>>v[i]>>w[i];
	    Knapsack(v,w,c,n,m);
	    Traceback(m,w,c,n,x);
	    cout <<m[1][c]<< endl;
	    for(int i=1;i<=n;i++)cout<<x[i]<<" ";cout<<endl;
	}
	delete2dArray(m,maxn+1);
	delete []x;
	delete []v;
	delete []w;
}
/*
tst18.in
5 10
6 2
3 2
5 6
4 5
6 4
5 12
2 1
3 2
4 3
5 4
6 5
tst18.out
Knapsack
15
1 1 0 0 1 
16
1 1 0 1 1 
*/

void tst19()
{
	cout<<"Knapsack2"<<endl;
    int n,c,*w,*v,*x,** p;
    w=new int[maxn+1];
    v=new int[maxn+1];
    x=new int[maxn+1];
    make2dArray(p,maxn+1,maxn+1);
	while(cin>>n>>c){
	    for(int i=1;i<=n;i++)cin>>v[i]>>w[i];
	    cout <<Knapsack(n,c,v,w,p,x)<< endl;
	    for(int i=1;i<=n;i++)cout<<x[i]<<" ";cout<<endl;
	}
	delete2dArray(p,maxn+1);
	delete []x;
	delete []v;
	delete []w;
}
/*
tst19.in
5 10
6 2
3 2
5 6
4 5
6 4
5 12
2 1
3 2
4 3
5 4
6 5
tst19.out
Knapsack
15
1 1 0 0 1 
16
1 1 0 1 1 
*/

void tst20()
{
	cout<<"OptimalBinarySearchTree"<<endl;
	int n,**s;	
	double **m,**w,a[maxn+1],b[maxn+1];
	make2dArray(m,maxn+1,maxn+1);
	make2dArray(w,maxn+1,maxn+1);
	make2dArray(s,maxn+1,maxn+1);
	while(cin>>n){
		for(int i=0;i<=n;i++)cin>>a[i];
		for(int i=1;i<=n;i++)cin>>b[i];
	    OptimalBinarySearchTree(a,b,n,m,s,w);
	    cout<<m[1][n]<<endl;
	    Inorder(s,1,n);cout<<endl;
    }
	delete2dArray(s,maxn+1);delete2dArray(w,maxn+1);delete2dArray(m,maxn+1);
}
/*
tst20.in
5
0.05 0.10 0.05 0.05 0.05 0.10
0.15 0.10 0.05 0.10 0.20
6
0.06 0.08 0.10 0.07 0.05 0.05 0.10
0.04 0.09 0.08 0.02 0.12 0.14
tst20.out
OptimalBinarySearchTree
2.35
2 1 5 4 3 
2.52
5 2 1 3 4 6 
*/

void tst21()
{
	cout<<"OptimalBinarySearchTree"<<endl;
	int n,**s;	
	double **m,**w,a[maxn+1],b[maxn+1];
	make2dArray(m,maxn+1,maxn+1);
	make2dArray(w,maxn+1,maxn+1);
	make2dArray(s,maxn+1,maxn+1);
	while(cin>>n){
		for(int i=0;i<=n;i++)cin>>a[i];
		for(int i=1;i<=n;i++)cin>>b[i];
	    OBST(a,b,n,m,s,w);
	    cout<<m[1][n]<<endl;
	    Inorder(s,1,n);cout<<endl;
    }
	delete2dArray(s,maxn+1);delete2dArray(w,maxn+1);delete2dArray(m,maxn+1);
}
/*
tst20.in
5
0.05 0.10 0.05 0.05 0.05 0.10
0.15 0.10 0.05 0.10 0.20
6
0.06 0.08 0.10 0.07 0.05 0.05 0.10
0.04 0.09 0.08 0.02 0.12 0.14
tst20.out
OptimalBinarySearchTree
2.35
2 1 5 4 3 
2.52
5 2 1 3 4 6 
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
    tst17();
    //tst18();
    //tst19();
    //tst20();
    //tst21();
	return 0;
}
