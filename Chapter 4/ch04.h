#include "2darray.h"
#include "binary.h"
#include "minheap.h"
#include "unfind.h"
#define maxint 30000
#define inf 300000

template<class Type>
void GreedySelector(int n,Type s[],Type f[],bool A[])
{
    A[1]=true;
    int j=1;
    for(int i=2;i<=n;i++){
        if(s[i]>=f[j]){A[i]=true;j=i;}
        else A[i]=false;
   }
}

void Sort(int n,float v[],float w[])
{
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n-i;j++){
            float t1=v[j]/w[j],t2=v[j+1]/w[j+1];
            if(t1<t2)swap(w[j],w[j+1]),swap(v[j],v[j+1]);
        }
}

void Knapsack(int n,float M,float v[],float w[],float x[])
{
    Sort(n,v,w);
    int i;
    for(i=1;i<=n;i++)x[i]=0;
    float c=M;
    for(i=1;i<=n;i++){
        if(w[i]>c)break;
        x[i]=1;
        c-=w[i];
    }
    if(i<=n)x[i]=c/w[i];
}

template<class Type>
void Sort(Type w[],int t[],int n)
{
	Type v[n+1];
	for(int i=0;i<=n;i++)v[i]=w[i],t[i]=i;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n-i;j++){
            if(v[j]>v[j+1])swap(v[j],v[j+1]),swap(t[j],t[j+1]);
    }
}

template<class Type>
void Loading(int x[],Type w[],Type c,int n)
{
    int t[n+1];
    Sort(w,t,n);
    for(int i=1;i<=n;i++)x[i]=0;
    for(int i=1;i<=n && w[t[i]]<=c;i++){
	    x[t[i]]=1;c-=w[t[i]];
	}
}

template<class Type>
class  Huffman {
   public:
        operator Type () const {return weight;}
		BinaryTree<int> tree;
		Type weight;
};

template <class Type>
BinaryTree<int> HuffmanTree(Type f[],int n)
{
    // 生成单结点树
    Huffman<Type> *w=new Huffman<Type>[n+1];
    BinaryTree<int> z,zero;
    for(int i=1;i<=n;i++){
        z.MakeTree(i,zero,zero);
        w[i].weight=f[i];
        w[i].tree=z;
    }
    // 建优先队列
    MinHeap<Huffman<Type> > Q(1);
    Q.Initialize(w,n,n);
    // 反复合并最小频率树
    Huffman<Type> x,y;
    for(int i=1;i<n;i++){
        Q.DeleteMin(x);
        Q.DeleteMin(y);
        z.MakeTree(0,x.tree,y.tree);
        x.weight+=y.weight;x.tree=z;
        Q.Insert(x);
    }
    Q.DeleteMin(x);
    Q.Deactivate();
    delete[]w;
    return x.tree;
}

template<class Type>
void Dijkstra(int n,int v,Type dist[],int prev[],Type ** c)
{ // 单源最短路径问题的Dijkstra算法
    bool s[maxint];
    for(int i=1;i<=n;i++){
        dist[i]=c[v][i];
        s[i]=false;
        if(dist[i]==maxint)prev[i]=0;
        else prev[i]=v;
    }
    dist[v]=0;s[v]=true;
    for(int i=1;i<n;i++){
        int temp=maxint;
        int u=v;
        for(int j=1;j<=n;j++)
            if((!s[j])&&(dist[j]<temp)){u=j;temp=dist[j];}
        s[u]=true;
        for(int j=1;j<=n;j++)
            if((!s[j])&&(c[u][j]<maxint)){
                Type newdist=dist[u]+c[u][j];
                if(newdist<dist[j]){dist[j]=newdist;prev[j]=u;}
            }
    }
}

/*
void Prim(int n,Type ** c)
{
    T=0;
    S={1};
    while(S!=V){
       (i,j)=i?S且j?V-S的最小权边；
        T=T∪{(i,j)};
        S=S∪{j};
   }
}*/

template<class Type>
Type Prim(int n,Type ** c)
{
    Type lowcost[maxint];
    int closest[maxint];
    bool s[maxint];
    Type sum=0;
    s[1]=true;
    for(int i=2;i<=n;i++){
        lowcost[i]=c[1][i];
        closest[i]=1;
        s[i]=false;
    }
    for(int i=1;i<n;i++){
        Type min=inf;
        int j=1;
        for(int k=2;k<=n;k++)
            if((lowcost[k]<min)&&(!s[k])){min=lowcost[k];j=k;}
        cout<<j<<" "<<closest[j]<<endl;sum+=c[j][closest[j]];
        s[j]=true;
        for(int k=2;k<=n;k++)
            if((c[j][k]<lowcost[k])&&(!s[k])){lowcost[k]=c[j][k];closest[k]=j;}
    }
    return sum;
}

template <class Type>
class EdgeNode {
    public:
        operator Type()const {return weight;}
        Type weight;
        int u,v;
};

template<class Type>
bool Kruskal(int n,int e,EdgeNode<Type> E[],EdgeNode<Type> t[])
{
    MinHeap<EdgeNode<Type> > H(1);
    H.Initialize(E,e,e);
    UnionFind U(n);
    int k=0;
    while(e && k<n-1){
        EdgeNode<int> x;
        H.DeleteMin(x);
        e--;
        int a=U.Find(x.u);
        int b=U.Find(x.v);
        if(a != b){t[k++]=x;U.Union(a,b);}
    }
    H.Deactivate();
    return(k==n-1);
}

class  JobNode 
{
    friend void Greedy(JobNode *,int,int);
    public:
       operator int()const {return time;}
    //private:
       int ID,time;
};

class  MachineNode 
{
    friend void Greedy(JobNode *,int,int);
    public:
        operator int()const {return avail;}
    private:
        int ID,avail;
};

template <class Type>
void Sort(Type a[],int n)
{
	std::sort(a+1,a+n);
}

void Greedy(JobNode a[],int n,int m)
{
    if(n<=m){
        cout<<"为每个作业分配一台机器."<<endl;
        return;
	}
    Sort(a,n);
    MinHeap<MachineNode> H(m);
    MachineNode x;
    for(int i=1;i<=m;i++){
        x.avail=0;
        x.ID=i;
        H.Insert(x);
    }
    for(int i=n;i>=1;i--){
        H.DeleteMin(x);
        cout<<"将机器 "<<x.ID<<" 从 "<<x.avail<<" 到 "
           <<(x.avail + a[i].time)<< " 的时间段分配给作业 "<<a[i].ID<<endl;
        x.avail+=a[i].time;
        H.Insert(x);
    }
}

int GreedyJob(int n,int d[],int J[])
{
    d[0]=0;J[0]=0;
    int k=1;
    J[1]=1;
    for(int i=2;i<=n;i++){
        int r=k;
        while((d[J[r]]>d[i])&&(d[J[r]]!=r))r=r-1;
        if((d[J[r]]<=d[i])&&(d[i]>r)){
            for(int m=k;m>r;m--)J[m+1]=J[m];
            J[r+1]=i;
            k=k+1;
        }
    }
    return k;
}

int FasterJob(int n,int d[],int J[])
{
    int *F=new int[n+1];
    for(int i=0;i<=n;i++)F[i]=i;
    UnionFind U(n);
    int k=0;
    for(int i=1;i<=n;i++){
        int m=(n<d[i])?U.Find(n):U.Find(d[i]);
        if(F[m]>0){
            k=k+1;
            J[k]=i;
            int t=U.Find(F[m]-1);
            U.Union(t,m);
            F[m]=F[t];
        }
    }
    delete []F;
    return k;
}



