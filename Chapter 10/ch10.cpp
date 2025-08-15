#include <bits/stdc++.h>
using namespace std;

    const int maxn=1000,sz=10000,mxm=7,mxpm=510510;//2*3*5*7*11*13*17;

	int gcd0(int a,int b)
	{
	    if(b==0)return a;
	    else return gcd0(b,a%b);
	}

	int gcd1(int a, int b)
	{
	    while(b){a%=b;swap(a,b);}
	    return a;
	}
 
	int gcd2(int a, int b)
	{
	    while(a!=b){
	        if(a>b)a-=b;
	        else b-=a;
	    }
	    return a;
	}
 
	int gcd(int a,int b)
	{
	    if(a<b)swap(a,b);
	    else if(b==0 || a==b)return a;
	    if((a & 1)==0 &&(b & 1)==0)return gcd(a>>1,b>>1)<<1;// a even,b even
	    else if((a & 1)==0 &&(b & 1))return gcd(a>>1,b);// a even,b odd
	    else if((a & 1)&&(b & 1)==0)return gcd(a,b>>1);// a odd,b even
	    else return gcd(a-b,b);// a odd,b odd
	}
 
	int gcd5(int a,int b)
	{
	    int c=0;
	    while((a & 1)==0 &&(b & 1)==0){// both evev
	         a>>=1;b>>=1;c++;
	    }// now at least one of a, b is odd 
	    while((a & 1)==0)a>=1;
	    while((b & 1)==0)b>=1;
	    if(a<b)swap(a,b);
	    while((a =(a-b)>>1)!= 0){// both odd
	        while((a & 1)==0)a>>=1;// a evev, b odd
	        if(a<b)swap(a,b);
	    }
	    return b<<c;
	}
 
	int gcd6(int n,int a[])
	{
		int t=1,e=n-1,c,i,u;
		while(t){
			for(i=0,t=0,c=a[0];i<=e;i++)
			    if(u=a[i]%c)a[t++]=u;
			a[t]=c,e=t;
		}
	    return c;
	}
 
	int gcd7(int n,int a[])
	{
		int t=1,e=n-1,c=a[0],d=a[0],i,u;
		while(t){
			for(i=0,t=0;i<=e;i++)
			    if(u=a[i]%c)a[t++]=u,d=min(u,d);
			a[t]=c,e=t,c=d;
		}
	    return d;
	}
 
	int exgcd(int a,int b,int& x,int& y)
	{
	    if(b==0){x=1;y=0;return a;}
	    int x1,y1;
	    int d=exgcd(b,a%b,x1,y1);
	    x=y1,y=x1-y1*(a/b);
	    return d;
	}
 
	int exgcd1(int a,int b,int &x,int &y)
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
 
	int exgcd3(int n,int a[],int x[])
	{
		int u,v,c,d;
	    if(n==2){
	    	d=exgcd(a[0],a[1],x[0],x[1]);
	        return d;
	    }
	    c=exgcd3(n-1,a,x);
	    d=exgcd(c,a[n-1],u,v);
	    for(int i=0;i<n-1;i++)x[i]*=u;
	    x[n-1]=v;
	    return d;
	}
 
	int exgcd4(int n,int a[],int x[])
	{
		int c=1,d=a[0],y[n],z[n];
		y[0]=z[0]=1;
		for(int i=1;i<n;i++)
			d=exgcd(d,a[i],y[i],z[i]);
		for(int i=n-1;i>=0;i--)
			x[i]=c*z[i],c*=y[i];
	    return d;
	}
 
	int exgcd5(int n,int a[],int x[])
	{
		int c=1,d=a[0];x[0]=1;
		for(int i=1;i<n;i++)d=exgcd(d,a[i],a[i],x[i]);
		for(int i=n-1;i>=0;i--)x[i]*=c,c*=a[i];
	    return d;
	}
 
	bool dioph2(int a,int b,int c,int &x,int &y)
	{
	    int d=exgcd(abs(a),abs(b),x,y);
	    if(c%d)return false;
	    x*=c/d; y*=c/d;
	    if(a<0)x=-x;
		if(b<0)y=-y;
	    return true;
	}
 
	bool dioph3(int n,int c,int a[],int x[])
	{
		int i,d=exgcd3(n,a,x);
		if (c%d) return false;
		for(i=0,c/=d;i<n;i++)x[i]*=c;
		return true;
	}
 
	bool dioph4(int n,int c,int a[],int x[])
	{
		int d=a[0];x[0]=1;
		for(int i=1;i<n;i++)d=exgcd(d,a[i],a[i],x[i]);
		if (c%d) return false;
		c/=d;
		for(int i=n-1;i>=0;i--)x[i]*=c,c*=a[i];
		return true;
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
 
	void euler(int n,int phi[])
	{
	    for(int i=2;i<n;i++)
	        if(!phi[i])
	            for(int j=i;j<n;j+=i){
	                if(!phi[j])phi[j]=j;
	                phi[j]=phi[j]/i*(i-1);
	            }
	}
 
	int meq(int a, int b, int n, int &x)
	{
		int v;
	    int d=exgcd(a,n,x,v);
	    if(b%d)return 0;
	    n/=d,x=((x*b/d)%n+n)%n;
		return d;
	}
 
	int inv(int a, int n)
	{
		int d,x,y;
	    d=exgcd(a,n,x,y);
	    if(d!=1)return 0;
	    else return(x%n+n)%n;
	}
 
	void inv(int n,int x[])
	{
		x[0]=0,x[1]=1;
		for(int i=2;i<n;i++)x[i]=(n-n/i)*x[n%i]%n;
	}

int kk=0,bb=0,cc=0;

void out(int n,int a[],int x[])
{
	int s=0;
	cc++;
	for(int i=0;i<kk;i++)s+=a[i]*x[i];
	for(int i=0;i<kk;i++)cout<<x[i]<<" ";cout<<endl;
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
	
	void solv1(int k,int b,int n,int a[],int d[],int x[])
	{
		if(k>1){//降阶并递推计算 
		    meq(a[k-1]*n/d[k-2],b*n/d[k-2],n,x[k-1]);
		    solv(k-1,b-a[k-1]*x[k-1],n,a,d,x);
		}
		else meq(a[0],b,n,x[0]);//一元方程求解 
	}
	
	int mequa3(int k,int b,int n,int a[],int d[],int x[])
	{
		d[0]=gcd(a[0],n);
		for(int i=1;i<k;i++)d[i]=gcd(d[i-1],a[i]);
		if(b%d[k-1])return 0;
		solv(k,b,n,a,d,x);
		return d[k-1];
	}
 
	int mequa3(int k,int b,int n,int a[],int x[])
	{
		int d=a[0];x[0]=1;a[k++]=n;
		for(int i=1;i<k;i++)d=exgcd(d,a[i],a[i],x[i]);
		b/=d;
		for(int i=k-1;i>=0;i--)x[i]=(x[i]*b+n)%n,b*=a[i];
		for(int i=0;i<k;i++)x[i]=(x[i]+n)%n;
		return d;
	}
 
	int crt(int k,int a[],int m[])
	{
	    int x,y,ni,r=0,n=1;
	    for(int i=0;i<k;i++)n*=m[i];
	    for(int i=0;i<k;i++){
	        ni=n/m[i];
	        exgcd(ni,m[i],x,y);
	        r=(r+ni*x*a[i])%n;
	    }
	    return(r+n)%n;
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
		return 0;
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

    int fac[maxn],prm[maxn],phi[maxn],pi[maxn],mk[maxn],r[maxn],seg[sz],m[mxpm+1],phi1[mxpm+1][mxm+1];
 
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
 
	void sieve(int n=maxn)
	{ 
	    memset(prm,0,sizeof(prm));
	    for(int i=2;i<=n;i++){ 
	        if(!prm[i]){
	            prm[++prm[0]]=i;
	            for(int j=i*i;j<=n;j+=i)prm[j]=1;
	        }
	    }
	}
 
	void getp0(int n=maxn)
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
 
	int getf1(int n)
	{
	    int cnt=0;
		for(int i=1;prm[i]<=sqrt(n);i++)
			if(n%prm[i]==0){
			    fac[cnt++]=prm[i];
				while(n%prm[i]==0)n/=prm[i];
			}
		if(n>1)fac[cnt++]=n;
		return cnt;
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

	int exp(int a,int b,int n)
	{
	    if(b==0)return 1;
	    int p=exp(a,b/2,n)%n;
	    p=(p*p)%n;
	    return(b%2==0)?p:(a*p)%n;
	}
 
	int exp1(int a,int b,int n)
	{
	    int r=1;
		for(;b;b>>=1,a=a*a%n)
		    if(b&1)r=r*a%n;
		return r;
	}
 
	bool miller(int n)
	{
	    int d=n-1,a=rand()%(n-2)+1,s=0;
	    while(!(d&1))d/=2,s++;
	    int x=exp(a,d,n);
	    for(int j=0,y=0;j<s;x=y,j++)
	        if((y=x*x%n)==1&&x!=1&&x!=(n-1))
			    return false;
	    return x==1;
	}
 
	bool primeMC(int n,int k)
	{
	    if(n==2)return true;
	    if(n<2||n%2==0)return false;
	    srand(time(0));
		for(int i=0;i<k;i++)
		    if(!miller(n))return false;
		return true;
	}
 
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

	void init()
	{
	    getp();
	    m[0]=1;
	    for(int i=0;i<=mxpm;i++)phi1[i][0]=i;
	    for(int i=1;i<=mxm;i++){
		    m[i]=prm[i]*m[i-1];
		    for(int j=1;j<=mxpm;++j)phi1[j][i]=phi1[j][i-1]-phi1[j/prm[i]][i-1];
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
	    if(a<=mxm)return phi1[x%m[a]][a]+(x/m[a])*phi1[m[a]][a];
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
	    for(int i=pi[rt3(x)]+1,t=pi[rt2(x)];i<=t;++i)
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
 
	int inv1(int a,int p)
	{
	    return exp(a,p-2,p);
	}
 
	int chk(int k,int n,int q,int cnt)
	{
		if(gcd(k,n)!=1)return 0;
		for(int i=0;i<cnt;i++){
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
 
	int solve(int a,int b,int n,int m,int x[])
	{
		int cnt=0;b%=n;
		for(int i=0,r=1;i<=m;r=(r*a)%n,i++)
		    if((r-b)%n==0)x[++cnt]=i;
		return x[0]=cnt;
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
 
	int elog(int a,int b,int n)
	{
	    unordered_map<int,int>mp;
	    int c=1,k=0,d,y;
	    a%=n,b%=n;
	    while((d=gcd(a,n))>1){
	        if(b==c)return k;
	        if(b%d)return -1;
	        b/=d,n/=d,k++;
	        c=(c*a/d)%n;
	    }
	    b=b*inv1(c,n)%n;
	    if((y=dlog(a,b,n))!=-1)y+=k;
		return y;
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
 
	int kroot(int a,int b,int n)
	{
		int g=roots(n);
		int c=exp(g,a,n);
		int y=dlog(c,b,n);
		if(y<0)return -1;
		return exp(g,y,n);
	}
 
	int kroot(int a,int b,int n,int r[])
	{
		int g=roots(n),c=dlog(g,b,n),ph=n-1;
		int y,d=meq(a,c,ph,y);
		if(d==0)return -1;
		int t=ph/d,e=exp(g,t,n),x=exp(g,y,n),cnt=0;
	    for(int i=0;i<d;i++){
		    r[cnt++]=x;y+=t;x=x*e%n;
	    }
		sort(r,r+cnt);
		return cnt;
	}

int main() 
{
	return 0;
}
	 
