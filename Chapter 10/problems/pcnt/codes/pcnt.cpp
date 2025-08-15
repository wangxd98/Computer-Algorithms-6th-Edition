#include <bits/stdc++.h>
using namespace std;

const int maxn=5e6+2;
const int mxm=7,mxpm=510510;//2*3*5*7*11*13*17
int phi[mxpm+1][mxm+1],m[mxm+1];
int prm[maxn],pi[maxn];

void getp(int n=maxn)
{
    memset(prm,0,sizeof(prm));
    pi[0]=pi[1]=0;
	for(int i=2;i<=n;i++){
	    if(!prm[i])prm[++prm[0]]=i;
	    pi[i]=prm[0];
	    for(int j=1;j<=prm[0] && prm[j]<=n/i;j++){
	        prm[prm[j]*i]=1;
	        if(i%prm[j]==0)break;
        }
	}
}

void init()
{
    getp();
    m[0]=1;
    for(int i=0;i<=mxpm;i++)phi[i][0]=i;
    for(int i=1;i<=mxm;i++){
	    m[i]=prm[i]*m[i-1];
	    for(int j=1;j<=mxpm;++j)phi[j][i]=phi[j][i-1]-phi[j/prm[i]][i-1];
    }
}

int rt2(long long x)
{
    long long r=(long long)sqrt(x-0.1);
    while(r*r<=x)++r;
    return int(r-1);
}

int rt3(long long x)
{
    long long r=(long long)cbrt(x-0.1);
    while(r*r*r<=x)++r;
    return int(r-1);
}

long long getphi(long long x,int a)
{
    if(a==0)return x;
    if(a<=mxm)return phi[x%m[a]][a]+(x/m[a])*phi[m[a]][a];
    if(x<=prm[a]*prm[a])return pi[x]-a+1;
    if(x<=prm[a]*prm[a]*prm[a] && x<maxn){
	    int y=pi[rt2(x)];
	    long long ret=pi[x]-(y+a-2)*(y-a+1)/2;
	    for(int i=a+1;i<=y;++i)ret+=pi[x/prm[i]];
	    return ret;
    }
    return getphi(x,a-1)-getphi(x/prm[a],a-1);
}

long long legendre(long long x)
{
    if(x<2)return 0;
    long long y=rt2(x),z=legendre(y);
    return getphi(x,z)+z-1;
} 

long long meissel(long long x)
{
    if(x<maxn)return pi[x];
    long long ret=getphi(x,pi[rt3(x)])+pi[rt3(x)]-1;
    for(int i=pi[rt3(x)]+1,t=pi[rt2(x)];i<=t;i++)
	    ret-=meissel(x/prm[i])-i+1;
    return ret;
}

long long lehmer(long long x)
{
    if(x<maxn)return pi[x];
    int a=(int)lehmer(rt2(rt2(x)));
    int b=(int)lehmer(rt2(x));
    int c=(int)lehmer(rt3(x));
    long long ret=getphi(x,a)+(long long)(b+a-2)*(b-a+1)/2;
    for(int i=a+1;i<=b;i++){
	    long long v=x/prm[i];
	    ret-=lehmer(v);
	    if(i>c)continue;
	    long long u=lehmer(rt2(v));
	    for(int j=i;j<=u;j++)ret-=lehmer(v/prm[j])-(j-1);
    }
    return ret;
}

int chek()
{
    init();
    long long n;
    while(cin>>n){
	    cout<<legendre(n)<<endl;
	    //cout<<meissel(n)<<endl;
	    //cout<<lehmer(n)<<endl;
    }
    return 0;
}

int main()
{
	chek();
	return 0;
}


