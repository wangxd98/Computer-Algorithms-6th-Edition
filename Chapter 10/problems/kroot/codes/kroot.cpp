#include <bits/stdc++.h>
using namespace std;

const int maxn=50000;
int prm[maxn],r[maxn];

int euler(int n)
{
    int r=n;
    for(int i=2;i*i<=n;i++)
        if(n%i==0){
            r-=r/i;
            while(n%i==0)n/=i;
        }
    if(n>1)r-=r/n;
    return r;
}

int exp(int a,int b,int n)
{
    int r=1;
	while(b){
	    if(b&1)r=r*a%n;
		a=a*a%n,b>>=1;
	}
	return r;
}

int exgcd(int a,int b,int &x,int &y){
	if(!b){x=1,y=0;return a;}
	int Gcd=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return Gcd;
}

int roots(int p)
{
    vector<int> fact;
    int phi=p-1,n=phi;
    for(int i=2;i*i<=n;++i){
        if(n%i==0){
            fact.push_back(i);
            while(n%i==0)n/=i;
        }
    }
    if(n>1)fact.push_back(n);
    for(int res=2;res<=p;++res){
        bool ok=true;
        for(int factor:fact){
            if(exp(res,phi/factor,p)==1){
                ok=false;
                break;
            }
        }
        if(ok)return res;
    }
    return -1;
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

int kroot(int a,int b,int n)
{
	int g=roots(n);
	int c=exp(g,a,n);
	int x=dlog(c,b,n);
	if(x<0)return -1;
	return exp(g,x,n);
}

int meq(int a, int b, int n, int &x)
{
	int v;
    int d=exgcd(a,n,x,v);
    if (b%d) return 0;
    x=((x*b/d)%n+n)%n;
	return d;
}

int kroot(int a,int b,int n,int r[])
{
	int g=roots(n),c=dlog(g,b,n),ph=euler(n);
	int x,d=meq(a,c,ph,x);
	if(d==0)return -1;
	int t=ph/d,e=exp(g,t,n),y=exp(g,x,n),cnt=0;
	for(int i=0;i<d;i++){
		r[cnt++]=y;x+=t;y=y*e%n;
	}
	sort(r,r+cnt);
	return cnt;
}

int chek()
{
	int n,m,a,b;
	while(cin>>a>>b>>n){
		m=kroot(a,b,n,r);
		//m=kroot(a,b,n);
		if(m>0){
			//cout<<m<<endl;
		    for(int i=0;i<m;i++)cout<<r[i]<<" ";cout<<endl;
		}
		else cout<<-1<<endl;
	}
    return 0;
}

int main()
{
	chek();
	return 0;
}

