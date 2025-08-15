#include <bits/stdc++.h>
using namespace std;

const int maxn=5e6+2,sz=10000;
int prm[maxn],mk[maxn],seg[sz];

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

int segsiv(int n)
{
    int ret=0,m=sqrt(n),k,i,j,id,s,p;
    getp(m);
    for(k=0;k*sz<=n;k++){
        memset(seg,1,sizeof(seg));
        for(i=1,s=k*sz;i<=prm[0];i++){
        	p=prm[i];id=(s+p-1)/p;
            for(j=max(id,p)*p-s;j<sz;j+=p)seg[j]=0;
        }
        if(k==0)seg[0]=seg[1]=0;
        for(i=0;i<sz && s+i<=n;i++)if(seg[i])ret++;
    }
    return ret;
}

void segsiv(int L,int R)
{
    int m=sqrt(R),i,j,k;
    getp(m);
    memset(mk,1,sizeof(mk));
    for(k=1;k<=prm[0];k++)
	    for(i=prm[k],j=max(i*i,(L+i-1)/i*i);j<=R;j+=i)
            mk[j-L]=0;
    if(L==1)mk[0]=0;
}

void out(unsigned k,unsigned n)
{
	int cnt=0;
	for(int i=0;i<n-k;i++)if(mk[i])cnt++;
	cout<<cnt<<endl;
	if(cnt==0||cnt>50)return;
	for(int i=0;i<n-k;i++)
    		if(mk[i])cout<<k+i<<" ";
	cout<<endl;
}

int chek()
{
    unsigned k,n;
    while(cin>>k>>n){
    	if(n<k)cout<<-1<<endl;
		else{
    	    segsiv(k,n);
    	    out(k,n);
		}
    }
    return 0;
}

int main()
{
	chek();
	return 0;
}



