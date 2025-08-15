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

int kk=0,bb=0,cc=0;

void out(int n,int a[],int x[])
{
	int s=0;
	cc++;
	for(int i=0;i<kk;i++)s+=a[i]*x[i];
	for(int i=0;i<kk;i++)cout<<x[i]<<" ";cout<<endl;
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
	    int c=n/d[k-2],y,dk,nd;
	    dk=meq(a[k-1]*c,b*c,n,y);
	    nd=n/dk; x[k-1]=y-nd;
		for(int i=0;i<dk;i++){
			x[k-1]=(x[k-1]+nd)%n;
			int b1=b-a[k-1]*x[k-1];
			solv(k-1,b1,n,a,d,x);
		}
	}
	else{//一元方程求解 
		int c,y;
		int d0=meq(a[0],b,n,y);
		c=n/d0; x[0]=y-c;
		for(int i=0;i<d0;i++){
			x[0]=(x[0]+c)%n;
			out(n,a,x);// 输出解 
		}
	}
}

int mequa3(int k,int b,int n,int a[],int d[],int x[])
{
	d[0]=gcd(a[0],n);
	for(int i=1;i<k;i++)d[i]=gcd(d[i-1],a[i]);
	int sl=abs(d[k-1]);
	for(int i=1;i<k;i++)sl*=n;
	if(b%d[k-1])return 0;
	cout<<sl<<endl;
	solv(k,b,n,a,d,x);
	return d[k-1];
}

int main() 
{
    int k,b,n,i,a[maxn],d[maxn],x[maxn],y[maxn];
    while(cin>>k>>b>>n){
    	kk=k;bb=b;cc=0;
	    for(i=0;i<k;i++)cin>>a[i],y[i]=a[i];
        int r=mequa3(k,b,n,a,d,x);
	}
	return 0;
}



