//ËØÊýËã·¨ 
#include <bits/stdc++.h>
using namespace std;

const int maxn=50000;
int prm[maxn],r[maxn],vis[maxn],phi[maxn];
int fac[100];

int wilson(int n)
{
    if(n<5)return(n==2||n==3);
	for(int i=1,r=1;i<n;i++)
	    if((r=(r*1ll*i)%n)==0)return 0;
	return 1;
}

int isprm(int n)
{
    for(int i=2;i<=sqrt(n);i++)
        if(n%i==0)return 0;
    return n!=1;
}

void getp(int n=maxn)
{
    memset(prm,0,sizeof(prm));
	for(int i=2;i<=n;i++){
	    if(!prm[i])prm[++prm[0]]=i;
	    for(int j=1;j<=prm[0] && prm[j]<=n/i;j++){
	        prm[prm[j]*i]=1;
	        if(i%prm[j]==0)break;
        }
	}
}

void chk(int &a,int &b)
{
	getp();
	int i=1;
	while(prm[i]<a)i++;
	a=prm[i];
	while(prm[i]<=b)i++;
	if(i>0)i--;
	b=prm[i];
}

void chk1(int &a,int &b)
{
	int i=a;
	while(!isprm(i))i++;
	a=i;i=b;
	while(!isprm(i))i--;
	b=i;
}

void chk2(int &a,int &b)
{
	int i=a;
	while(!wilson(i))i++;
	a=i;i=b;
	while(!wilson(i))i--;
	b=i;
}

void chek()
{
	int a,b;
	while(cin>>a>>b){
		chk(a,b);
		cout<<a<<" "<<b<<endl;
	}
}

int main()
{
	chek();
	return 0;
}

