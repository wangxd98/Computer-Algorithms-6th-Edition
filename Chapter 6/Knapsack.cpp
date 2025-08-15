#include <bits/stdc++.h>
using namespace std;
#include "maxheap.h"

template<class Type>
void Sort(Type a[],int n)
{
	std::sort(a,a+n);
}

class Object 
{
	template<class Tw,class Tp>
    friend Tp Knapsack(Tp [],Tw [],Tw,int,int []);
    public:
        operator float()const {return d;}
    private:
        int ID;
        float d;// 单位重量价值
};

template <class Typew,class Typep> class Knap;
class bbnode 
{
    template<class Tw,class Tp>
    friend class Knap;
    private:
        bbnode *parent;// 指向父结点的指针
        bool LChild;   // 左儿子结点标志
};

template<class Typew,class Typep>
class  HeapNode 
{
    template<class Tw,class Tp>
    friend class Knap;
    public:
        operator Typep()const{return uprofit;}
    private:
        Typep uprofit, // 结点的价值上界
              profit;  // 结点所相应的价值
        Typew weight; // 结点所相应的重量
        int level;    // 活结点在子集树中所处的层序号
        bbnode *ptr;  // 指向活结点在子集树中相应结点的指针
};

template<class Typew,class Typep>
class Knap 
{
	template<class Tw,class Tp>
    friend Tp Knapsack(Tp [],Tw [],Tw,int,int []);
    public:
        Typep MaxKnapsack();
    private:
        MaxHeap<HeapNode<Typep,Typew> >*H;
        Typep Bound(int i);
        void AddLiveNode(Typep up,Typep cp,Typew cw,bool ch,int level);
        bbnode *E;    // 指向扩展结点的指针
        Typew c;      // 背包容量
        int n;         // 物品总数
        Typew *w;    // 物品重量数组
        Typep *p;     // 物品价值数组
        Typew cw;    // 当前装包重量
        Typep cp;     // 当前装包价值
        int *bestx;    // 最优解
};

template<class Typew,class Typep>
Typep Knap<Typew,Typep>::Bound(int i)
{// 计算结点所相应价值的上界
    Typew cleft=c-cw;  // 剩余容量
    Typep b=cp;        // 价值上界
    // 以物品单位重量价值递减序装填剩余容量
    while(i<=n && w[i]<=cleft){
        cleft-=w[i];
        b+=p[i];
        i++;
    }
    // 装填剩余容量装满背包
    if(i<=n)b+=p[i]/w[i] * cleft;
    return b;
}

template<class Typew,class Typep>
void Knap<Typew,Typep>::AddLiveNode(Typep up,Typep cp,Typew cw,bool ch,int lev)
{// 将一个新的活结点插入到子集树和最大堆H中
    bbnode *b=new bbnode;
    b->parent=E;
    b->LChild=ch;
    HeapNode<Typep,Typew> N;
    N.uprofit=up;
    N.profit=cp;
    N.weight=cw;
    N.level=lev;
    N.ptr=b;
    H->Insert(N);
}

template<class Typew,class Typep>
Typep Knap<Typew,Typep>::MaxKnapsack()
{// 优先队列式分支限界法，返回最大价值，bestx返回最优解
    // 定义最大堆的容量为1000
    H=new MaxHeap<HeapNode<Typep,Typew> >(1000);
    // 为bestx分配存储空间
    bestx=new int[n+1];
    // 初始化
    int i=1;
    E=0;
    cw=cp=0;
    Typep bestp=0;     // 当前最优值
    Typep up=Bound(1);// 价值上界
    // 搜索子集空间树
    while(i!=n+1){// 非叶结点
        // 检查当前扩展结点的左儿子结点
        Typew wt=cw+w[i];
        if(wt<=c){// 左儿子结点为可行结点
            if(cp+p[i]>bestp)bestp=cp+p[i];
            AddLiveNode(up,cp+p[i],cw+w[i],true,i+1);
		}
        up=Bound(i+1);
        // 检查当前扩展结点的右儿子结点
        if(up>=bestp)// 右子树可能含最优解
            AddLiveNode(up,cp,cw,false,i+1);
        // 取下一扩展结点
        HeapNode<Typep,Typew> N;
        H->DeleteMax(N);
        E=N.ptr;
        cw=N.weight;
        cp=N.profit;
        up=N.uprofit;
        i=N.level;
    }
    // 构造当前最优解
    for(int j=n;j>0;j--){
        bestx[j]=E->LChild;
        E=E->parent;
    }
    return cp;
}

template<class Typew,class Typep>
Typep Knapsack(Typep p[],Typew w[],Typew c,int n,int bestx[])
{// 返回最大价值，bestx返回最优解
    // 初始化
    Typew W=0;// 装包物品重量
    Typep P=0;// 装包物品价值
    // 定义依单位重量价值排序的物品数组
    Object *Q=new Object[n];
    for(int i=1;i<=n;i++){
        // 单位重量价值数组
        Q[i-1].ID=i;
        Q[i-1].d=1.0*p[i]/w[i];
        P+=p[i];
        W+=w[i];
    }
    if(W<=c)return P;// 所有物品装包
    // 依单位重量价值排序
    Sort(Q,n);
    // 创建类Knap的数据成员
    Knap<Typew,Typep> K;
    K.p=new Typep[n+1];
    K.w=new Typew[n+1];
    for(int i=1;i<=n;i++){
        K.p[i]=p[Q[i-1].ID];
        K.w[i]=w[Q[i-1].ID];
    }
    K.cp=0;
    K.cw=0;
    K.c=c;
    K.n=n;
    // 调用MaxKnapsack求问题的最优解
    Typep bestp=K.MaxKnapsack();
    for(int j =1 ;j<=n;j++)
        bestx[Q[j-1].ID]=K.bestx[j];
    delete[] Q;
    delete[] K.w;
    delete[] K.p;
    delete[] K.bestx;
    return bestp;
}

int main()
{
    cout<<"Test Knapsack"<<endl;
    int n,v[100];
    double c,p[100],w[100];
    while(cin>>n>>c){
       for(int i=1;i<=n;i++)cin>>p[i]>>w[i];
       cout <<Knapsack(p,w,c,n,v)<<endl;
       for(int i=1;i<=n;i++)cout<<v[i]<<" ";cout<<endl;
    }
    return 0;
}
/*
tst07.in:
4 7
9 3
10 5
7 2
4 1
5 10
6 2
3 2
5 6
4 5
6 4
10 100
15 5
17 13
9 7
13 3
7 15
9 16
18 20
15 8
14 11
20 10
tst07.out:
Test Knapsack
20
1 0 1 1 
15
1 1 0 0 1 
130
1 1 1 1 0 1 1 1 1 1 
*/
