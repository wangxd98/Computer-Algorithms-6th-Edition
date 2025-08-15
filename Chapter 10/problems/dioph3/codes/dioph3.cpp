#include <bits/stdc++.h>
using namespace std;

const int maxn=100;

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

int exgcd3(int n,int a[],int x[])
{
	int c=1,d=a[0];x[0]=1;
	for(int i=1;i<n;i++)d=exgcd(d,a[i],a[i],x[i]);
	for(int i=n-1;i>=0;i--)x[i]*=c,c*=a[i];
	return d;
}

bool dioph3(int n,int c,int a[],int x[])
{
	int i,d=exgcd3(n,a,x);
	if (c%d) return false;
	for(i=0,c/=d;i<n;i++)x[i]*=c;
	return true;
}

bool tst(int n,int c,int a[],int x[])
{
	int s=0;
	for(int i=0;i<n;i++)s+=a[i]*x[i];
	if(s==c)return true;
	else return false;
}

void out(int n,int x[])
{
	for(int i=0;i<n;i++)cout<<x[i]<<" ";
	cout<<endl;
}

void chk()
{
	int n,c,d,a[maxn],y[maxn],x[maxn];
	while(cin>>n>>c){
		for(int i=0;i<n;i++)cin>>a[i],y[i]=a[i];
		d=dioph3(n,c,a,x);
		if(d && tst(n,c,y,x)) out(n,x);
		else cout<<"-1"<<endl;
	}
}

int main() 
{
	chk();
	return 0;
}

