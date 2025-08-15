#include <bits/stdc++.h>
using namespace std;

const int maxn=100;

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

bool excrt1(int k,int a[],int m[])
{
    for(int u,v,i=k-1;i>0;i--){
        int d=exgcd(m[i],m[i-1],u,v);
        if((a[i-1]-a[i])%d)return 0;
        u=(a[i-1]-a[i])/d*u%(m[i-1]/d);
        a[i-1]=a[i]+u*m[i];
        m[i-1]=m[i]/d*m[i-1];
    }
    a[0]=(a[0]+m[0])%m[0];
    return 1;
}

bool excrt(int k,int a[],int m[])
{
    int u,v,d=exgcd(m[k-1],m[k-2],u,v);
    if((a[k-2]-a[k-1])%d)return 0;
    u=(a[k-2]-a[k-1])/d*u%(m[k-2]/d);
    a[k-2]=a[k-1]+u*m[k-1];
    m[k-2]=m[k-1]/d*m[k-2];
    if(k<3){
    	a[0]=(a[0]+m[0])%m[0];
        return 1;
	}
	else excrt(k-1,a,m);
}

void chk()
{
    int r,n,k,i,s,a[maxn],d[maxn],x[maxn],m[maxn],aa[maxn],mm[maxn];
    while(cin>>k){
	    for(i=0;i<k;i++){
	    	cin>>a[i]>>m[i];
	    	aa[i]=a[i],mm[i]=m[i];
		}
        //s=excrt(k,a,m,r,n);
        s=excrt1(k,a,m);
        if(s){
        	for(i=0;i<k;i++)if((a[0]-aa[i])%mm[i])cout<<"!!!!!!!!!!!!!!!!"<<endl;;
            cout<<a[0]<<endl;
		}
 	}
}

int main()
{
	chk();
	return 0;
}


