//Å·À­º¯ÊýËã·¨ 
#include <bits/stdc++.h>
using namespace std;

const int maxn=50000,M=1000000007;;
int prm[maxn],vis[maxn],phi[maxn];

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

void getphi(int n=maxn)
{
    memset(prm,0,sizeof(prm));
	phi[1]=1;
    for(int i=2;i<=n;i++){
        if(!prm[i]){
            prm[++prm[0]]=i;
            phi[i]=i-1;
        }
        for(int j=1;i*prm[j]<=n;j++){
            prm[i*prm[j]]=1;
            if(i%prm[j]==0){
                phi[i*prm[j]]=phi[i]*prm[j];                            
                break;
            }
            phi[i*prm[j]]=phi[i]*(prm[j]-1);
        }
    }
}

void chek0()
{
	int a,b;
	getphi();
	vis[0]=0; 
    for(int i=1;i<maxn;i++)
        vis[i]=(vis[i-1]+phi[i])%M;
	while(cin>>a>>b){
		cout<<vis[b]-vis[a-1]<<endl;
	}
}

void chek()
{
	int a,b;
	getphi();
	vis[0]=0; 
    for(int i=1;i<maxn;i++)
        vis[i]=(vis[i-1]+euler(i))%M;
	while(cin>>a>>b){
		cout<<vis[b]-vis[a-1]<<endl;
	}
}

int main()
{
	chek0();
	return 0;
}



