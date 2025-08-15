//求原根算法 
#include <bits/stdc++.h>
using namespace std;

const int maxn=10000;
int prm[maxn],r[maxn];
int fac[100];

int gcd(int a,int b){return !b?a:gcd(b,a%b);}

int exp(int a,int b,int n)
{
    int r=1;
	for(;b;b>>=1,a=a*a%n)
	    if(b&1)r=r*a%n;
	return r;
}

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

void getp()
{
    memset(prm,0,sizeof(prm));
	for(int i=2;i<=maxn;i++){
	    if(!prm[i])prm[++prm[0]]=i;
	    for(int j=1;j<=prm[0] && prm[j]<=maxn/i;j++){
	        prm[prm[j]*i]=1;
	        if(i%prm[j]==0)break;
        }
	}
}

void getf(int x,int &cnt)
{
    cnt=0;
	for(int i=1;prm[i]<=x;i++){
		if(x%prm[i]==0){
		    fac[cnt++]=prm[i];
			while(x%prm[i]==0)x/=prm[i];
		}
	}
}

int getf(int n) 
{
    int cnt=0;
    for(int i=2;i<=sqrt(n);i++)
    	if(n%i==0){
    		fac[cnt++]=i;
    		while(n%i==0)n/=i;
		}
	if(n>1)fac[cnt++]=n;
	return cnt; 
}

int chk(int k,int n,int q,int cnt)
{
	if(gcd(k,n)!=1)return 0;
	for(int i=0;i < cnt;i++){
		int t=q/fac[i];
		if(exp(k,t,n)==1)return 0;
	}
	return 1;
}

void solve(int n,int r[])
{
    if(n==2){r[++r[0]]=1;return;}
	int q=euler(n),cnt=getf(q);
	for(int k=2;k<n;k++)
		if(chk(k,n,q,cnt))r[++r[0]]=k;
}

void out(int p)
{
	r[0]=0;
	solve(p,r);
	if(r[0]==0)cout<<0<<endl;
	else{
		for(int i=1;i<=r[0];i++)cout<<r[i]<<" ";
		cout<<endl;
	}
}

int chek()
{
	int p,n;
	while(cin>>p>>n)
		for(int i=p;i<=n;i++)out(i);
    return 0;
}

int main()
{
	chek();
	return 0;
}



