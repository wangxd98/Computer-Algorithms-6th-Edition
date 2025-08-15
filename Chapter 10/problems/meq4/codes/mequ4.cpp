#include <bits/stdc++.h>
using namespace std;

const int maxn=10000;

int gcd(int a,int b) 
{
    if (b==0)return a;
    return gcd(b,a%b);
}

int exgcd(int a,int b,int &x,int &y) 
{
    int c=y=0,d=x=1;
    while (b){
        int q=a/b,t=a;
        a=b;b=t%b;
        t=x;x=c;c=t-q*c;
        t=y;y=d;d=t-q*d;
    }
    return a;
}

int meq(int a, int b, int n, int &x)
{
	int v;
    int d=exgcd(a,n,x,v);
    if (b%d) return 0;
    n/=d,x=((x*b/d)%n+n)%n;
	return d;
}

void solv(int k,int b,int n,int a[],int d[],int x[])
{
	if(k>1){//降阶并递推计算 
	    meq(a[k-1]*n/d[k-2],b*n/d[k-2],n,x[k-1]);
	    solv(k-1,b-a[k-1]*x[k-1],n,a,d,x);
	}
	else meq(a[0],b,n,x[0]);//一元方程求解 
}

int mequa4(int k,int b,int n,int a[],int d[],int x[])
{
	d[0]=gcd(a[0],n);
	for(int i=1;i<k;i++)d[i]=gcd(d[i-1],a[i]);
	if(b%d[k-1])return 0;
	solv(k,b,n,a,d,x);
	return d[k-1];
}

void chk()
{
    int k,b,n,i,s,a[maxn],d[maxn],x[maxn],y[maxn];
    while(cin>>k>>b>>n){
	    for(i=0;i<k;i++)cin>>a[i],y[i]=a[i];
        int r=mequa4(k,b,n,a,d,x);
        for(i=0,s=0;i<k;i++)s+=y[i]*x[i];
        for(int i=0;i<k;i++)cout<<x[i]<<" ";cout<<endl;
	}
}

int main() 
{
	chk();
	return 0;
}



