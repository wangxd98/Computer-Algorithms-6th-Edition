//ÀëÉ¢¶ÔÊıËã·¨ 
#include <bits/stdc++.h>
using namespace std;

int gcd(int a,int b){return !b?a:gcd(b,a%b);}

int exgcd(int a,int b,int &x,int &y)
{
    int c=y=0,d=x=1;
    while(b){
        int q=a/b,t=a;
        a=b;b=t%b;
        t=x;x=c;c=t-q*c;
        t=y;y=d;d=t-q*d;
    }
    return a;
}

int inv(int a,int p)
{
	int x,y;
	exgcd(a,p,x,y);
	return(x%p+p)%p;
}

int dlog(int a,int b,int n)
{
    unordered_map<int,int>mp;
    int q=1,m=sqrt(n)+1;
    for(int i=0;i<m;++i)q=(q*a)%n;
    for(int j=0;j<=m;j++)mp[b]=j,b=(b*a)%n;
    for(int i=1,r=1;i<=m;i++){
        r=(r*q)%n;
        if(mp.count(r))return m*i-mp[r];
    }
    return -1;
}

int elog(int a,int b,int n)
{
    unordered_map<int,int>mp;
    int c=1,k=0,d,y;
    a%=n,b%=n;
    while((d=gcd(a,n))>1){
        if(b==c)return k;
        if(b%d)return -1;
        b/=d,n/=d,k++;
        c=(c*a/d)%n;
    }
    b=b*inv(c,n)%n;
    if((y=dlog(a,b,n))!=-1)y+=k;
	return y;
}

int chek()
{
	int n,a,b;
	while(cin>>a>>b>>n){
		int r=elog(a,b,n);
		if(r>=0)cout<<r<<endl;
	}
    return 0;
}

int main()
{
	chek();
	return 0;
}

