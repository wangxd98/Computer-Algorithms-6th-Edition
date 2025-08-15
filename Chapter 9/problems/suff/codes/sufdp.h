#ifndef Suffix_
#define Suffix_

class suffix
{
    #define maxn 13003
    private:
        int m,n;
        int a[maxn],b[maxn],cnt[maxn],t[maxn];
        
        int cmp(int *t,int u,int v,int l)
        {
		    return t[u]==t[v]&& u+l<n && v+l<n && t[u+l]==t[v+l];
		}
        
        void radix(int *x,int *y,int *z,int n,int m)
        {
            for(int i=0;i<m;i++)cnt[i]=0;
            for(int i=0;i<n;i++)cnt[x[y[i]]]++;
            for(int i=1;i<m;i++)cnt[i]+=cnt[i-1];
            for(int i=n-1;i>=0;i--)z[--cnt[x[y[i]]]]=y[i];
        }
        
        void sort2(int *x,int *y,int h)
        {
            int t=0;
            for(int i=n-h;i<n;i++)y[t++]=i;
            for(int i=0;i<n;i++)if(sa[i]>=h)y[t++]=sa[i]-h;
            radix(x,y,sa,n,m);
        }
        
        void doubling(int *t)
        {
            int *x=a,*y=b;
            for(int i=0;i<n;i++)x[i]=t[i],y[i]=i;
            radix(x,y,sa,n,m);
            for(int h=1;h<n;h*=2){
                sort2(x,y,h);
                swap(x,y);x[sa[0]]=0;m=1;
                for(int i=1;i<n;i++)x[sa[i]]=cmp(y,sa[i-1],sa[i],h)?m-1:m++;
            }
        }
        
        void kasai(int *t,int n)
        {
            int k=0;sa[n]=n;
            for(int i=0;i<n;i++)rank[sa[i]]=i;
            for(int i=0;i<n;i++){
                int j=sa[rank[i]+1];
                while(i+k<n && j+k<n && t[i+k]==t[j+k])k++;
                lcp[rank[i]]=k;
                if(k>0)k--;
            }
        }
        
        int rmq(int low,int high)
        {
            int v=lcp[low];
            for(int i=low+1;i<high;i++)if(lcp[i]<v)v=lcp[i];
            return v;
        }
        
        void init()
        {
            memset(a,0,sizeof(a));
            memset(b,0,sizeof(b));
            memset(t,0,sizeof(t));
            memset(cnt,0,sizeof(cnt));
            memset(sa,0,sizeof(sa));
            memset(rank,0,sizeof(rank));
            memset(lcp,0,sizeof(lcp));
        }

    public:
        int sa[maxn],rank[maxn],lcp[maxn];

        suffix(string txt)
        {
            init();
			m=128,n=txt.length();
            for(int i=0;i<n;i++)t[i]=txt[i];
            doubling(t);
            kasai(t,n);
        }
        
        suffix(int *txt,int len)
        {
            init();
			m=128,n=len;
            for(int i=0;i<n;i++)t[i]=txt[i];
            doubling(t);
            kasai(t,n);
        }
        
        int lce(int l,int r)
        {
            if(l==r)return(n-l);
            return rmq(min(rank[l],rank[r]),max(rank[l],rank[r]));
        }
        
        int length(){return n;}
        
        int select(int i){return sa[i];}
        
        int index(int i){return rank[i];}
        
        int llcp(int i){return lcp[i];}
};

#endif
 



