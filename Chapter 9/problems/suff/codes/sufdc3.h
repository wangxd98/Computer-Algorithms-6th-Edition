#ifndef Suffix_
#define Suffix_

class suffix
{
    #define maxn 13003
    #define add1(p)((p)/3+((p)%3==1?0:a1))
    #define add2(p)((p)<a1?(p)*3+1:((p)-a1)*3+2)
    private:
        int m,n;
        int a[maxn],b[maxn],c[maxn],t[maxn],cnt[maxn];
        
        int cmp(int *t,int u,int v)
        {return t[u]==t[v]&&t[u+1]==t[v+1]&&t[u+2]==t[v+2];}
        
        int cmp2(int k,int *t,int u,int v)
        {if(k==2)return t[u]<t[v]||t[u]==t[v]&&cmp2(1,t,u+1,v+1);
        else return t[u]<t[v]||t[u]==t[v]&&c[u+1]<c[v+1];}
        
        void radix(int *x,int *y,int *z,int n,int m)
        {
            for(int i=0;i<m;i++)cnt[i]=0;
            for(int i=0;i<n;i++)cnt[x[y[i]]]++;
            for(int i=1;i<m;i++)cnt[i]+=cnt[i-1];
            for(int i=n-1;i>=0;i--)z[--cnt[x[y[i]]]]=y[i];
        }
        
        int divide(int *t,int *sa,int *t12,int n,int m,int a1,int a12)
        {
            int d=0;
            for(int i=0;i<n;i++)if(i%3!=0)a[d++]=i;
            radix(t+2,a,b,a12,m);
            radix(t+1,b,a,a12,m);
            radix(t,a,b,a12,m);
            d=1;t12[add1(b[0])]=0;
            for(int i=1;i<a12;i++)
                t12[add1(b[i])]=cmp(t,b[i-1],b[i])?d-1:d++;
            return d;
        }
        
        void conquer(int *t,int *sa12,int *t12,int n,int m,int p,int a1,int a12)
        {
            int i,a0=0;
            if(p<a12)dc3(t12,sa12,a12,p);
            else for(i=0;i<a12;i++)sa12[t12[i]]=i;
            for(i=0;i<a12;i++)if(sa12[i]<a1)b[a0++]=sa12[i]*3;
            if(n%3==1)b[a0++]=n-1;
            radix(t,b,a,a0,m);
        }
        
        void merge(int *t,int *sa,int *sa12,int n,int m,int a0,int a1,int a12)
        {
            int i,j,p;
            for(i=0;i<a12;i++)b[i]=add2(sa12[i]);
            for(i=0;i<a12;i++)c[b[i]]=i;
            for(i=0,j=0,p=0;i<a0 && j<a12;p++)
            sa[p]=cmp2(b[j]%3,t,a[i],b[j])?a[i++]:b[j++];
            for(;i<a0;p++)sa[p]=a[i++];
            for(;j<a12;p++)sa[p]=b[j++];
        }
        
        void dc3(int *t,int *sa,int n,int m)
        {
            int *t12=t+n,*sa12=sa+n,a0=(n+2)/3,a1=(n+1)/3,a12=a1+n/3;
            t[n]=t[n+1]=0;
            int p=divide(t,sa,t12,n,m,a1,a12);
            conquer(t,sa12,t12,n,m,p,a1,a12);
            merge(t,sa,sa12,n,m,a0,a1,a12);
            return;
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
            memset(c,0,sizeof(c));
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
            dc3(t,sa,n,m);
            kasai(t,n);
        }
        
        suffix(int *txt,int len)
        {
            init();
			m=128,n=len;
            for(int i=0;i<n;i++)t[i]=txt[i];
            dc3(t,sa,n,m);
            kasai(t,n);
        }
        
        int lce(int l,int r)
        {
            if(l==r)return(n-l);
            return rmq(min(rank[l],rank[r]),max(rank[l],rank[r]));
        }
};

#endif 



