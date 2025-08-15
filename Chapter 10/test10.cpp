#include <bits/stdc++.h>
using namespace std;
#include "ch10.h"

void tst01()
{
    cout<<"Test gcd0"<<endl;
	cout<<gcd0(135,75)<<endl;
}
/*
Test gcd0
15
*/

void tst02()
{
    cout<<"Test gcd1"<<endl;
	cout<<gcd1(135,75)<<endl;
}
/*
Test gcd1
15
*/

void tst03()
{
    cout<<"Test gcd2"<<endl;
	cout<<gcd1(135,75)<<endl;
}
/*
Test gcd2
15
*/

void tst04()
{
    cout<<"Test gcd"<<endl;
	cout<<gcd(135,75)<<endl;
}
/*
Test gcd
15
*/

void tst05()
{
    cout<<"Test gcd5"<<endl;
	cout<<gcd5(135,75)<<endl;
}
/*
Test gcd5 
15
*/

void tst06()
{
    cout<<"Test gcd6"<<endl;
    int a[3]={135,75,3};
	cout<<gcd6(3,a)<<endl;
}
/*
Test gcd6 
3
*/

void tst07()
{
    cout<<"Test gcd7"<<endl;
    int a[3]={135,75,3};
	cout<<gcd7(3,a)<<endl;
}
/*
Test gcd7 
3
*/

void tst08()
{
    cout<<"Test exgcd"<<endl;
    int x,y;
	cout<<exgcd(198,156,x,y);
	cout<<" "<<x<<" "<<y<<endl;
}
/*
Test exgcd
6 -11 14
*/

void tst09()
{
    cout<<"Test exgcd1"<<endl;
    int x,y;
	cout<<exgcd1(198,156,x,y);
	cout<<" "<<x<<" "<<y<<endl;
}
/*
Test exgcd1
6 -11 14
*/

void tst10()
{
    cout<<"Test exgcd3"<<endl;
    int a[3]={198,156,3},x[3];
	cout<<exgcd3(3,a,x);
	for(int i=0;i<3;i++)
	cout<<" "<<x[i];cout<<endl;
}
/*
Test exgcd3
3 0 0 1
*/

void tst11()
{
    cout<<"Test exgcd4"<<endl;
    int a[3]={198,156,3},x[3];
	cout<<exgcd4(3,a,x);
	for(int i=0;i<3;i++)
	cout<<" "<<x[i];cout<<endl;
}
/*
Test exgcd4
3 0 0 1
*/

void tst12()
{
    cout<<"Test exgcd5"<<endl;
    int a[3]={198,156,3},x[3];
	cout<<exgcd5(3,a,x);
	for(int i=0;i<3;i++)
	cout<<" "<<x[i];cout<<endl;
}
/*
Test exgcd5
3 0 0 1
*/

void tst13()
{
    cout<<"Test dioph2"<<endl;
    int a,b,c,x,y;
    while(cin>>a>>b>>c){
    	if(dioph2(a,b,c,x,y))cout<<x<<" "<<y<<endl;
    	else cout<<-1<<endl;
	}
}
/*
tst13.in:
3 4 5
16 21 5
6 12 11
tst13.out:
Test dioph2
-5 5
20 -15
-1
*/

void tst14()
{
    cout<<"Test dioph3"<<endl;
    int n,c,a[10],x[10];
    while(cin>>n>>c){
    	for(int i=0;i<n;i++)cin>>a[i];
    	if(dioph3(n,c,a,x)){
    		for(int i=0;i<n;i++)cout<<x[i]<<" ";
			cout<<endl;
		}
    	else cout<<-1<<endl;
	}
}
/*
tst14.in:
3 1000 
9 24 -5
4 500 
15 30 45 75
tst14.out:
Test dioph3
6000 -2000 1000 
-1
*/

void tst15()
{
    cout<<"Test dioph4"<<endl;
    int n,c,a[10],x[10];
    while(cin>>n>>c){
    	for(int i=0;i<n;i++)cin>>a[i];
    	if(dioph4(n,c,a,x)){
    		for(int i=0;i<n;i++)cout<<x[i]<<" ";
			cout<<endl;
		}
    	else cout<<-1<<endl;
	}
}
/*
tst15.in:
3 1000 
9 24 -5
4 500 
15 30 45 75
tst15.out:
Test dioph3
6000 -2000 1000 
-1
*/

void tst16()
{
    cout<<"Test euler"<<endl;
    int n=50;
	for(int i=40;i<=n;i++)cout<<i<<" "<<euler(i)<<endl;
}
/*
Test euler
40 16
41 40
42 12
43 42
44 20
45 24
46 22
47 46
48 16
49 42
50 20
*/

void tst17()
{
    cout<<"Test euler(int n,int phi[])"<<endl;
    int n=51,phi[51]={0};
    euler(n,phi);
	for(int i=40;i<n;i++)cout<<i<<" "<<phi[i]<<endl;
}
/*
Test euler(int n,int phi[])
40 16
41 40
42 12
43 42
44 20
45 24
46 22
47 46
48 16
49 42
50 20
*/

void tst18()
{
    cout<<"Test meq"<<endl;
    int x;
    meq(35,10,50,x);
	cout<<x<<endl;
}
/*
Test meq
6
*/

void tst19()
{
    cout<<"Test inv(int a, int n)"<<endl;
	cout<<inv(35,33)<<endl;
}
/*
Test inv(int a, int n)
17
*/

void tst20()
{
    cout<<"Test inv(int n,int x[])"<<endl;
    int n=17,x[18];
    inv(n,x); 
	for(int i=2;i<5;i++)cout<<x[i]<<endl;
}
/*
Test inv(int n,int x[])
9
6
13
*/

void tst21()
{
    cout<<"Test mequa3"<<endl;
    int k,b,n,i,a[10],d[10],x[10],y[10];
    cin>>k>>b>>n;
    kk=k;bb=b;cc=0;
    for(i=0;i<k;i++)cin>>a[i],y[i]=a[i];
    int r=mequa3(k,b,n,a,d,x);
}
/*
Tst21.in
2 6 5 6 9
Tst21.out
Test mequa3
1 0 
2 1 
3 2 
4 3 
0 4 
*/

void tst22()
{
    cout<<"Test crt"<<endl;
    int k,a[100],m[100];
    cin>>k;
	for(int i=0;i<k;i++)cin>>a[i]>>m[i];
    cout<<crt(k,a,m)<<endl;  
}
/*
Tst22.in
3 2 3 4 5 3 7
Tst22.out
Test crt
59
*/

void tst23()
{
    cout<<"Test excrt"<<endl;
    int k,s,a[100],m[100];
    cin>>k;
	for(int i=0;i<k;i++)cin>>a[i]>>m[i];
    s=excrt(k,a,m);
    //s=excrt1(k,a,m);
    if(s)cout<<a[0]<<endl;
}
/*
Tst23.in
3 0 6 4 8 3 9
Tst23.out
Test excrt
12
*/

void tst24()
{
    cout<<"Test wilson"<<endl;
    cout<<wilson(133)<<" "<<wilson(331)<<endl;
}
/*
Test wilson
0 1
*/

void tst25()
{
    cout<<"Test isprm"<<endl;
    cout<<isprm(133)<<" "<<isprm(331)<<endl;
}
/*
Test isprm
0 1
*/

void tst26()
{
    cout<<"Test getf"<<endl;
    int cnt=getf(223092870);
    cout<<cnt<<endl;
    for(int i=0;i<cnt;i++)cout<<fac[i]<<" ";cout<<endl;
}
/*
Test getf
9
2 3 5 7 11 13 17 19 23
*/

void tst27()
{
    cout<<"Test getf1"<<endl;
    getp(999);
    int cnt=getf1(998);
    cout<<cnt<<endl;
    for(int i=0;i<cnt;i++)cout<<fac[i]<<" ";cout<<endl;
}
/*
Test getf1
2
2 499
*/

void tst28()
{
    cout<<"Test sieve"<<endl;
    sieve(50);
	cout<<prm[0]<<endl;
	for(int i=1;i<=prm[0];i++)cout<<prm[i]<<" ";cout<<endl;}
/*
Test sieve
15
2 3 5 7 11 13 17 19 23 29 31 37 41 43 47
*/

void tst29()
{
    cout<<"Test miller"<<endl;
    for(int i=150;i<200;i++)
        if(miller(i))cout<<i<<endl;
}
/*
Test miller
151
157
163
167
173
179
181
191
193
197
199
*/

void tst30()
{
    cout<<"Test primeMC"<<endl;
    for(int i=170;i<200;i++)
        if(primeMC(i,50))cout<<i<<endl;
}
/*
Test primeMC
173
179
181
191
193
197
199
*/

void tst31()
{
    cout<<"Test segsiv(int L,int R)"<<endl;
    segsiv(1,30);
    for(int i=0;i<29;i++)
    		if(mk[i])cout<<1+i<<" ";
	cout<<endl;
}
/*
Test segsiv(int L,int R)
2 3 5 7 11 13 17 19 23 29
*/

void tst32()
{
    cout<<"Test segsiv(int n)"<<endl;
    cout<<segsiv(30);
    //for(int i=0;i<29;i++)if(mk[i])cout<<1+i<<" ";
	//cout<<endl;
}
/*
Test segsiv(int n)
10
*/

void tst33()
{
    cout<<"Test legendre"<<endl;
    init();
    cout<<legendre(10000)<<endl;
}
/*
Test legendre
1229
*/

void tst34()
{
    cout<<"Test meissel"<<endl;
    init();
    cout<<meissel(10000)<<endl;
}
/*
Test meissel
1229
*/

void tst35()
{
    cout<<"Test lehmer"<<endl;
    init();
    cout<<lehmer(10000)<<endl;
}
/*
Test lehmer
1229
*/

void tst36()
{
    cout<<"Test solve(int n,int r[])"<<endl;
	r[0]=0;
	solve(11,r);
	if(r[0]==0)cout<<0<<endl;
	else{
		for(int i=1;i<=r[0];i++)cout<<r[i]<<" ";
		cout<<endl;
	}
}
/*
Test solve(int n,int r[])
2 6 7 8
*/

void tst37()
{
    cout<<"Test solve(int a,int b,int n,int m,int x[])"<<endl;
    int x[100];
    solve(6,172,53,50,x);
    cout<<x[0]<<endl;
    for(int i=1;i<=x[0];i++)cout<<x[i]<<" ";
    cout<<endl;
}
/*
Test solve(int a,int b,int n,int m,int x[])
2
10 36
*/

void tst38()
{
    cout<<"Test dlog"<<endl;
    cout<<dlog(6,172,53)<<endl;
}
/*
Test dlog
10
*/

void tst39()
{
    cout<<"Test elog"<<endl;
    cout<<elog(6,172,53)<<endl;
    cout<<elog(6,4,8)<<endl;
}
/*
Test elog
10
2
*/

void tst40()
{
    cout<<"Test kroot"<<endl;
    cout<<kroot(131,758,317)<<endl;
}
/*
Test kroot
306
*/

void tst41()
{
    cout<<"Test kroot(int a,int b,int n,int r[])"<<endl;
    int m=kroot(16,122,23563,r);
	if(m>0){
		for(int i=0;i<m;i++)cout<<r[i]<<" ";cout<<endl;
	}
}
/*
Test kroot(int a,int b,int n,int r[])
4762 18801
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
    //tst19();
    //tst20();
	//tst21();
	//tst22();
	//tst23();
	//tst24();
	//tst25();
    //tst26();
    //tst27();
    //tst28();
    //tst29();
    //tst30();
	//tst31();
	//tst32();
	//tst33();
	//tst34();
	//tst35();
    //tst36();
    //tst37();
    //tst38();
    //tst39();
    //tst40();
	tst41();
	return 0;
}

