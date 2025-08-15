
int naive(const string& t,const string& p)
{// 简单子串搜索算法 Code1
    int n=t.length();
    int m=p.length();
    int i=0;
    while(i<=n-m){
        int j=0;
        while(j<m && t[i+j]==p[j])j++;
        if(j==m) return i;
        i++;
    }
    return -1;
}

int n,m,r=16,q=101;

void build(const string& p, int *next)
{// 计算前缀函数 Code3
    next[0]=-1;
    int j=-1;
    for(int i=1;i<=m-1;i++){
        while(j>-1 && p[j+1]!=p[i])j=next[j];
        if(p[j+1]==p[i])j++;
        next[i]=j;
    }
}

int KMPmatcher(const string& t,const string& p)
{// KMP算法 Code2
    int n=t.length();
    int m=p.length();
    int *next=new int[m];
    build(p,next);
    int j=-1;
    for (int i=0;i<n;i++){
        while(j>-1 && p[j+1]!=t[i])j=next[j];
        if(p[j+1]==t[i])j++;
        if(j==m-1)return i-m+1;
    }
    return -1;
}

long hash1(const string& p,int i,int m)
{// 计算子串的散列值 Code4
    long h=0;
    for(int j=0;j<m;j++)h=(r*h+p[i+j])%q;
    return h;
}

int Rabin_Karp0(const string& t,const string& p)
{// Rabin-Karp算法 Code5
    int m=p.length();
    int n=t.length();
    long hp=hash1(p,0,m);
    for(int i=0;i<=n-m;i++){
        long ht=hash1(t,i,m);
        if(hp==ht)return i;
    }
    return n;
}

bool check(const string& t,const string& p,int i,int m) 
{
    for(int j=0;j<m;j++)
       if(p[j]!=t[i+j])return false;
    return true;
}

int Rabin_Karp(const string& t,const string& p)
{// Rabin-Karp子串搜索算法 Code6
    int m=p.length();
    int n=t.length();
    if(n<m) return n;
    long ht=hash1(t,0,m);
    long hp=hash1(p,0,m);
    long rm=1;
    for(int i=1;i<m;i++)  rm=(r*rm)%q; // 计算 r^m-1) % q 
    if((hp==ht) && check(t,p,0,m))return 0;
    // 检测散列匹配; 然后检测精确匹配
    for(int i=m;i<n;i++) {
        //检测匹配
        ht=(ht+q-rm*t[i-m]%q)%q;
        ht=(ht*r+t[i])%q;
        // 匹配
        int offset=i-m+1;
        if((hp==ht) && check(t,p,offset,m))return offset;
    }
    // 不匹配
    return n;
}

#define nsize 8001        //结点池 size 
#define dsize 26           //字符集 size  
#define idsize 256   

typedef struct node
{// AC自动机的状态结点 Code7
    int  cnt;
    int  state;
    node* fail;
    node* go[dsize];
    vector<string> output;
}tnode;

class Aho
{
    private:
        int    size;
        tnode* root;
        int idx[idsize]; 
        tnode nmap[nsize+1];// 防内存泄漏自建结点池 
        
        void idex()
        {// 预先计算idx Code9
            for(int i=0;i<dsize;++i)idx['a'+i]=i;
        }
        
        tnode* newnode()
        {// 建立新的状态结点 Code10 
            nmap[size].cnt=0;
            nmap[size].state=size;
            nmap[size].fail=root;
            return &nmap[size++];
        }
        
        void init()
        {
            idex();
            memset(nmap,0,sizeof(nmap));
            root=NULL;size=0;root=newnode();
        }
        
    int addout(tnode* p,tnode* q)
    { // 合并两结点p和q的output Code12 
        p->output.insert(p->output.begin(),q->output.begin(),q->output.end());
        return p->output.size();
    }
    
public:
        
Aho(){init();}
        
Aho(vector<string>& keywords)
{
    init();
    for(int i=0;i<keywords.size();i++)insert(keywords[i]);
    build_failure();
}

void insert(const string& word)
{// 插入关键词树 Code8
    tnode* cur=root;
    for(int i=0;i<word.length();++i){
       if(!cur->go[idx[word[i]]])cur->go[idx[word[i]]]=newnode();
       cur=cur->go[idx[word[i]]];
    }
    cur->output.push_back(word);
    cur->cnt=1;
}

void build_failure()
{// 计算失败函数 Code11 
    queue<tnode*> q;
    root->fail=NULL;
    q.push(root);
    while(!q.empty()){
        tnode* cur=q.front();
        q.pop();
        for(int i=0;i<dsize;++i)
            if(cur->go[i]){
                tnode* p=cur->fail;
                while(p && !p->go[i])p=p->fail;
                if(p){
                    cur->go[i]->fail=p->go[i];
                    cur->go[i]->cnt=addout(cur->go[i],p->go[i]);
                }
                q.push(cur->go[i]);
            }
            else cur->go[i]=cur==root?root:cur->fail->go[i];
    }
}

void outout(tnode *p)
{
    for(int i=0;i<p->output.size();i++)cout<<p->output[i]<<endl;
}

int mult_search(const string& text) 
{// AC自动机多子串搜索 Code13 
    int cnt=0;
    tnode *cur=root;
	for(int i=0;i<text.length();i++){
		while (!cur->go[idx[text[i]]])cur=cur->fail;
	    cur=cur->go[idx[text[i]]];
		cnt+=cur->cnt;
	} 
	return cnt;      
}

void outtree() 
{
    cout<<size<<endl;
    for(int i=0;i<size;++i ){
        int f=-1;
        if(nmap[i].fail)f=nmap[i].fail->state;
        cout<<"i="<<i<<" f="<<f<<endl;
        outout(&nmap[i]);
    }
}
};

class suffix
{// 后缀数组类 Code14 
private:
    string *t,*suff;
    int n,*sa;
public:
    suffix(string txt)
	{
        n=txt.length();
        t=new string[n];suff=new string[n];sa=new int[n];
        for(int i=0;i<n;i++)t[i]=txt[i];
        for(int i=0;i<n;i++)sa[i]=i;
        build();
    }

    void build()
	{
        for(int i=0;i<n;i++){
            string text="";
            for(int j=i;j<n;j++)text+=t[j];
            suff[i]=text;
        }
        for(int i=1,j;i<n;i++){
            string key=suff[i];
            int idx=sa[i];
            for(j=i-1;j>=0;j--)
                if(suff[j].compare(key)>0){
                    suff[j+1]=suff[j];sa[j+1]=sa[j];
                }
                else break;
            suff[j+1]=key;sa[j+1]=idx;
        }
    }
    
    void out()
    {
    	for(int i=0;i<n;i++)
    		cout<<i<<" : "<<sa[i]<<" "<<suff[i]<<endl;
	}
};

class suffix2
{
    #define maxn 13003
    private:
        int m,n;
        int a[maxn],b[maxn],cnt[maxn],t[maxn];
        
        int cmp(int *t,int u,int v,int l)
        {// 比较h前缀元素对 Code16 
		    return t[u]==t[v]&& u+l<n && v+l<n && t[u+l]==t[v+l];
		}
        
        void radix(int *x,int *y,int *z,int n,int m)
        {// 根据y的序将x排序为z Code17
            for(int i=0;i<m;i++)cnt[i]=0;
            for(int i=0;i<n;i++)cnt[x[y[i]]]++;// 出现次数
            for(int i=1;i<m;i++)cnt[i]+=cnt[i-1];
            for(int i=n-1;i>=0;i--)z[--cnt[x[y[i]]]]=y[i];// 排序
        }
        
        void sort2(int *x,int *y,int h)
        {// 对2元序列对序列排序 Code18
            int t=0;
            for(int i=n-h;i<n;i++)y[t++]=i;
            for(int i=0;i<n;i++)if(sa[i]>=h)y[t++]=sa[i]-h;
            radix(x,y,sa,n,m);
        }
        
        void doubling(int *t)
        {// 构造后缀数组的倍前缀算法 Code15 
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

        suffix2(string txt)
        {
            init();
			m=128,n=txt.length();
            for(int i=0;i<n;i++)t[i]=txt[i];
            doubling(t);
            kasai(t,n);
        }
        
        suffix2(int *txt,int len)
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
        
        int idx(int i){return rank[i];}
        
        int llcp(int i){return lcp[i];}
};

class suffix3
{
    #define maxn 13003
    #define add1(p)((p)/3+((p)%3==1?0:a1))
    #define add2(p)((p)<a1?(p)*3+1:((p)-a1)*3+2)
    private:
        int m,n;
        int a[maxn],b[maxn],c[maxn],t[maxn],cnt[maxn];
        
        int cmp(int *t,int u,int v)
        {// 比较函数 Code21
		    return t[u]==t[v]&&t[u+1]==t[v+1]&&t[u+2]==t[v+2];
		}
        
        int cmp2(int k,int *t,int u,int v)
        {// 比较两个队列中队首元素 Code26
		    if(k==2)return t[u]<t[v]||t[u]==t[v]&&cmp2(1,t,u+1,v+1);
            else return t[u]<t[v]||t[u]==t[v]&&c[u+1]<c[v+1];
		}
        
        void radix(int *x,int *y,int *z,int n,int m)
        {
            for(int i=0;i<m;i++)cnt[i]=0;
            for(int i=0;i<n;i++)cnt[x[y[i]]]++;
            for(int i=1;i<m;i++)cnt[i]+=cnt[i-1];
            for(int i=n-1;i>=0;i--)z[--cnt[x[y[i]]]]=y[i];
        }
        
        int divide(int *t,int *sa,int *t12,int n,int m,int a1,int a12)
        {// 非对称分割 Code20 
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
        {// 递归后缀排序 Code23
            int i,a0=0;
            if(p<a12)dc3(t12,sa12,a12,p);
            else for(i=0;i<a12;i++)sa12[t12[i]]=i;
            for(i=0;i<a12;i++)if(sa12[i]<a1)b[a0++]=sa12[i]*3;
            if(n%3==1)b[a0++]=n-1;
            radix(t,b,a,a0,m);
        }
        
        void merge(int *t,int *sa,int *sa12,int n,int m,int a0,int a1,int a12)
        {// 后缀合并 Code24
            int i,j,p;
            for(i=0;i<a12;i++)b[i]=add2(sa12[i]);
            for(i=0;i<a12;i++)c[b[i]]=i;
            for(i=0,j=0,p=0;i<a0 && j<a12;p++)
            sa[p]=cmp2(b[j]%3,t,a[i],b[j])?a[i++]:b[j++];
            for(;i<a0;p++)sa[p]=a[i++];
            for(;j<a12;p++)sa[p]=b[j++];
        }
        
        void dc3(int *t,int *sa,int n,int m)
        {// 构造后缀数组的DC3分治法 Code19
            int *t12=t+n,*sa12=sa+n,a0=(n+2)/3,a1=(n+1)/3,a12=a1+n/3;
            t[n]=t[n+1]=0;
            int p=divide(t,sa,t12,n,m,a1,a12);
            conquer(t,sa12,t12,n,m,p,a1,a12);
            merge(t,sa,sa12,n,m,a0,a1,a12);
            return;
        }
        
        void kasai(int *t,int n)
        {// 构造最长公共前缀数组lcp Code27
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
        {// 区间最小查询 Code29
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

        suffix3(string txt)
        {
        	init();
            m=128,n=txt.length();
            for(int i=0;i<n;i++)t[i]=txt[i];
            dc3(t,sa,n,m);
            kasai(t,n);
        }
        
        suffix3(int *txt,int len)
        {
            init();
			m=128,n=len;
            for(int i=0;i<n;i++)t[i]=txt[i];
            dc3(t,sa,n,m);
            kasai(t,n);
        }
        
        int lce(int l,int r)
        {// 最长公共扩展 Code28
            if(l==r)return(n-l);
            return rmq(min(rank[l],rank[r]),max(rank[l],rank[r]));
        }
};

bool diff(int *sa,int m,int i)
{// 相邻两个后缀判断 Code32 
    return (m<sa[i] && m>sa[i+1])||(m>sa[i] && m<sa[i+1]);
}

void change(string s1,string s2,string& t)
{// 字符串变换 Code31 
    int m=s1.length(),n=s2.length();
    t.resize(n+m+1);
    for(int i=0;i<m;i++)t[i]=s1[i];
    for(int i=0;i<n;i++)t[m+i+1]=s2[i];
    n=m+n+1;t[m]=t[n]=0;
}

int lcss(string s1,string s2)
{// 最长公共子串算法 Code30 
    int *sa,*lcp,m,n,ans=0;
    string t;
    m=s1.length();n=s1.length()+s2.length();
    change(s1,s2,t);
    suffix3 suf(t);sa=suf.sa;lcp=suf.lcp;
    for(int i=0;i<n-1;i++)
        if(lcp[i]>ans && diff(sa,m,i))ans=lcp[i];
    return ans;
}

string x,y;
int dt=1;
int d[maxn][maxn],d1[maxn];

void init()
{
	memset(d,0,sizeof(d));
	memset(d1,0,sizeof(d1));
}

int ed()
{// 编辑距离的动态规划算法 Code33
    for(int i=0;i<=n;i++)d[i][0]=i;
    for(int i=0;i<=m;i++)d[0][i]=i;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            if (x[i]==y[j])d[i+1][j+1]=d[i][j];
            else d[i+1][j+1]=min(d[i][j]+dt,min(d[i][j+1],d[i+1][j])+1);
	return d[n][m];
}

void back(int i,int j)
{// 构造最优编辑序列 Code34 
    if(i==0){while(j--)cout<<"i("<<j<<")"<<endl;return;} 
    if(j==0){while(i--)cout<<"d("<<i<<")"<<endl;return;} 
    if(x[i-1]==y[j-1])back(i-1,j-1);
    else if(d[i-1][j-1]+dt<min(d[i-1][j],d[i][j-1])+1){
        back(i-1,j-1);
        cout<<"r("<<i-1<<","<<j-1<<")"<<endl;
    }
    else if(d[i-1][j]<d[i][j-1]){
        back(i-1,j);
        cout<<"d("<<i-1<<")"<<endl;
    }
    else{
        back(i,j-1);
        cout<<"i("<<j-1<<")"<<endl;
    }
}

int edn()
{// O(n)空间算法 Code35 
    memset(d1,0,sizeof d1);
    int oldd,newd;
    for(int i=0;i<=n;i++)
        for(int j=0;j<=m;j++){
            if(i==0)oldd=d1[j],d1[j]=j;
            else if(j==0)oldd=d1[j],d1[j]=i;
            else{
                if(x[i-1]==y[j-1])newd=oldd;
                else newd=min(oldd+dt,min(d1[j-1],d1[j])+1);
                oldd=d1[j],d1[j]=newd;
            }
        }
    return d1[m];
}

int a[maxn],b[maxn];
int f[maxn][maxn];

int lcis()
{// 最长公共递增子序列 Code36 
    memset(f,0,sizeof(f));
    for(int i=1;i<=n;i++){
        int max=0;
        for(int j=1;j<=m;j++){
            f[i][j]=f[i-1][j];
            if(a[i-1]>b[j-1] && max<f[i-1][j])max=f[i-1][j];
            if(a[i-1]==b[j-1])f[i][j]=max+1;
        }
    }
    int ret=0;
    for(int i=1;i<=m;i++)if(ret<f[n][i])ret=f[n][i];
    return ret;
}

