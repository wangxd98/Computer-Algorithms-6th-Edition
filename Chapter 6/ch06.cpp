
#include <bits/stdc++.h>
using namespace std;

#include "swap.h"
#include "2darray.h"
#include "queue.h"
#include "minheap.h"
#include "maxheap.h"

#define maxint 30000
#define inf 300000

template<class Type>
void Sort(Type a[],int n)
{
	std::sort(a,a+n);
}

template<class Type>
class Graph 
{
	friend void tst01();
    public:
    	Graph(int n=0)
    	{
    		this->n=n;
    		prev=new int[n+1];
    		dist=new Type[n+1];
    		make2dArray(c,n+1,n+1);
    		for(int i=0;i<=n;i++)dist[i]=inf,prev[i]=0;
    		for(int i=0;i<=n;i++)
    		    for(int j=0;j<=n;j++)
    		        c[i][j]=inf;
		}
		~Graph() 
        {
        	delete []dist;
        	delete [] prev;
            delete2dArray(c,n+1);
        }
        void ShortestPaths(int);
    private:
        int  n,    // 图G的顶点数
            *prev;  // 前驱顶点数组
        Type **c,  // 图G的邻接矩阵
             *dist; // 最短距离数组
};

template<class Type>
class MinHeapNode 
{
    friend Graph<Type>;
    public:
        operator int()const{return length;}
    private:
        int i;       // 顶点编号
        Type length;  // 当前路长
};

template<class Type>
void Graph<Type>::ShortestPaths(int v)
{// 单源最短路径问题的优先队列式分支限界法
    // 定义最小堆的容量为1000
    MinHeap< MinHeapNode<Type> >H(1000);
    // 定义源为初始扩展结点
    MinHeapNode<Type> E;
    E.i=v;
    E.length=0;
    dist[v]=0;
    // 搜索问题的解空间
    while(true){
        for(int j=1;j<=n;j++)
            if((c[E.i][j]<inf)&&(E.length+c[E.i][j]<dist[j])){
                // 顶点i到顶点j可达，且满足控制约束
                dist[j]=E.length+c[E.i][j];
                prev[j]=E.i;
                // 加入活结点优先队列
                MinHeapNode<Type> N;
                N.i=j;
                N.length=dist[j];
                H.Insert(N);
			}
        try{H.DeleteMin(E);}         // 取下一扩展结点
        catch(OutOfBounds){break;}  // 优先队列空
    }
}

template<class Type>
void EnQueue(Queue<Type> &Q,Type wt,Type& bestw,int i,int n)
{// 将活结点加入到活结点队列Q中
    if(i==n){// 可行叶结点
        if(wt>bestw)bestw=wt;
	}
    else Q.Add(wt);// 非叶结点
}

template<class Type>
Type MaxLoading1(Type w[],Type c,int n) // 队列式分支限界法，返回最优载重量
{					  
   // 初始化
    Queue<Type> Q;										  // 活结点队列
    Q.Add(-1);											  // 同层结点尾部标志
    int i=1;											  // 当前扩展结点所处的层
    Type Ew=0,										     // 扩展结点所相应的载重量
         bestw=0;										  // 当前最优载重量
    while (true) {     									  // 搜索子集空间树
        if (Ew+w[i]<=c) 									  // 检查左儿子结点
            EnQueue(Q,Ew+w[i],bestw,i,n);
        EnQueue(Q,Ew,bestw,i,n);        	               // 右儿子结点总是可行的
        Q.Delete(Ew);	     		     				       // 取下一扩展结点
        if (Ew==-1) {								      // 同层结点尾部
            if (Q.IsEmpty())return bestw;
            Q.Add(-1);									  // 同层结点尾部标志
            Q.Delete(Ew);								  // 取下一扩展结点
            i++;
        }											     // 进入下一层
    }
    return bestw;
}

template<class Type>
Type MaxLoading2(Type w[],Type c,int n) // 队列式分支限界法，返回最优载重量
{	    
    // 初始化
    Queue<Type> Q;								// 活结点队列
    Q.Add(-1);									// 同层结点尾部标志
    int  i=1;									// 当前扩展结点所处的层
    Type  Ew=0,								    // 扩展结点所相应的载重量
        bestw=0,								// 当前最优载重量
        r=0;							    	// 剩余集装箱重量
    for (int j=2;j<=n;j++)r+=w[j];
    while (true) {     							// 搜索子集空间树
        // 检查左儿子结点
        Type wt=Ew+w[i];  						// 左儿子结点的重量
        if (wt<=c) {				        	// 可行结点
            if (wt>bestw)bestw=wt;
            if (i<n)Q.Add(wt);           		// 加入活结点队列
		}
        if (Ew+r>bestw && i<n)       			// 检查右儿子结点
            Q.Add(Ew);							// 可能含最优解
        Q.Delete(Ew);							// 取下一扩展结点
        if (Ew==-1) {							// 同层结点尾部
            if (Q.IsEmpty())return bestw;
            Q.Add(-1);								// 同层结点尾部标志
            Q.Delete(Ew);							// 取下一扩展结点
            i++;									// 进入下一层
            r-=w[i];					    		// 剩余集装箱重量
        }	
   }
   return bestw;
}

template<class Type>
Type MaxLoading5(Type w[],Type c,int n)
{  // 队列式分支限界法，返回最优载重量
    // 初始化
    Queue<Type> Q;  // 活结点队列
    Q.Add(-1);       // 同层结点尾部标志
    int i=1;         // 当前扩展结点所处的层
    Type Ew=0,    // 扩展结点所相应的载重量
         bestw=0,     // 当前最优载重量
         r=0;          // 剩余集装箱重量
    for(int j=2;j<=n;j++)
        r+=w[j];
    // 搜索子集空间树
    while(true){
        // 检查左儿子结点
        Type wt=Ew+w[i]; // 左儿子结点的重量
        if(wt<=c){     // 可行结点
            if(wt>bestw)bestw=wt;
            // 加入活结点队列
            if(i<n)Q.Add(wt);
		}
        // 检查右儿子结点
        if(Ew+r>bestw && i<n)
            Q.Add(Ew); // 可能含最优解
        Q.Delete(Ew);   // 取下一扩展结点
        if(Ew==-1){     // 同层结点尾部
            if(Q.IsEmpty())return bestw;
            Q.Add(-1);   // 同层结点尾部标志
            Q.Delete(Ew);// 取下一扩展结点
            i++;         // 进入下一层
            r-=w[i];
		}      // 剩余集装箱重量
    }
}

template<class Type>
class  QNode 
{
	public:
    //private:
        QNode *parent;// 指向父结点的指针
        bool LChild;   // 左儿子标志
        Type weight;   // 结点所相应的载重量
};

template<class Type>
void EnQueue(Queue<QNode<Type>*> &Q,Type wt,
     int i,int n,Type bestw,QNode<Type> *E,
     QNode<Type> *&bestE,int bestx[],bool ch)
{// 将活结点加入到活结点队列Q中
    if(i==n){// 可行叶结点
        if(wt==bestw){
            // 当前最优载重量
            bestE=E;
            bestx[n]=ch;
		}
        return;
	}
    // 非叶结点
    QNode<Type> *b;
    b=new QNode<Type>;
    b->weight=wt;
    b->parent=E;
    b->LChild=ch;
    Q.Add(b);
}

template<class Type>
Type MaxLoading3(Type w[],Type c,int n,int bestx[])
{  // 队列式分支限界法，返回最优载重量，bestx返回最优解
    // 初始化
    Queue<QNode<Type>* > Q;// 活结点队列
    Q.Add(0);               // 同层结点尾部标志
    int i=1;                 // 当前扩展结点所处的层
    Type Ew=0,              // 扩展结点所相应的载重量
         bestw=0,            // 当前最优载重量
         r=0;                 // 剩余集装箱重量
    for(int j=2;j<=n;j++)
        r+=w[j];
    QNode<Type> *E=0,   // 当前扩展结点
                *bestE;        // 当前最优扩展结点
    // 搜索子集空间树
    while(true){
        // 检查左儿子结点
        Type wt=Ew+w[i];
        if(wt<=c){// 可行结点
            if(wt>bestw)bestw=wt;
            EnQueue(Q,wt,i,n,bestw,E,bestE,bestx,true);
		}
        // 检查右儿子结点
        if(Ew+r>bestw)EnQueue(Q,Ew,i,n,bestw,E,bestE,bestx,false);
        Q.Delete(E);     // 取下一扩展结点
        if(!E){           // 同层结点尾部
            if(Q.IsEmpty())break;
            Q.Add(0);    // 同层结点尾部标志
            Q.Delete(E);  // 取下一扩展结点
            i++;         // 进入下一层
            r-=w[i];
		}      // 剩余集装箱重量
        Ew=E->weight; // 新扩展结点所相应的载重量
    }
    // 构造当前最优解
    for(int j=n-1;j>0;j--){
        bestx[j]=bestE->LChild;
        bestE=bestE->parent;
    }
    return bestw;
}


template <class Type> class HeapNode;
class bbnode 
{
    template<class T>
    friend T MaxLoading(T w[],T c,int n,int bestx[]);
    template<class T>
    friend void AddLiveNode(MaxHeap<HeapNode<T> > &H,bbnode *E,T wt,bool ch,int lev);
    private:
        bbnode *parent;// 指向父结点的指针
        bool LChild;   // 左儿子结点标志
};

template<class Type>
class HeapNode 
{
    public:
        operator Type()const{return uweight;}
    //private:
        bbnode *ptr;   // 指向活结点在子集树中相应结点的指针
        Type uweight;  // 活结点优先级(上界)
        int level;       // 活结点在子集树中所处的层序号
};


template<class Type>
void AddLiveNode(MaxHeap<HeapNode<Type> > &H,bbnode *E,Type wt,bool ch,int lev)
{// 将活结点加入到表示活结点优先队列的最大堆H中
    bbnode *b=new bbnode;
    b->parent=E;
    b->LChild=ch;
    HeapNode<Type> N;
    N.uweight=wt;
    N.level=lev;
    N.ptr=b;
    H.Insert(N);
}

template<class Type>
Type MaxLoading(Type w[],Type c,int n,int bestx[])
{  // 优先队列式分支限界法，返回最优载重量，bestx返回最优解
    // 定义最大堆的容量为1000
    MaxHeap<HeapNode<Type> >H(1000);
    // 定义剩余重量数组r 
    Type *r=new Type[n+1];
    r[n]=0;
    for(int j=n-1;j>0;j--)
        r[j]=r[j+1]+w[j+1];
    // 初始化
    int i=1;           // 当前扩展结点所处的层
    bbnode *E=0;     // 当前扩展结点
    Type Ew=0;       // 扩展结点所相应的载重量
    // 搜索子集空间树
    while(i!=n+1){// 非叶结点
        // 检查当前扩展结点的儿子结点
        if(Ew+w[i]<=c){// 左儿子结点为可行结点
            AddLiveNode(H,E,Ew+w[i]+r[i],true,i+1);
		}
        // 右儿子结点
        AddLiveNode(H,E,Ew+r[i],false,i+1);
        // 取下一扩展结点
        HeapNode<Type> N;
        H.DeleteMax(N);// 非空
        i=N.level;
        E=N.ptr;
        Ew=N.uweight-r[i-1];
    }
    // 构造当前最优解
    for(int j=n;j>0;j--){
        bestx[j]=E->LChild;
        E=E->parent;
    }
    return Ew;
}

class Position 
{
    public:
        operator int() const {return row;}
        int row,col;
};

int m=0,n=0,grid[50][50];
bool FindPath(Position start,Position finish,int& PathLen,Position *path)
{// 计算从起始位置start到目标位置finish的最短布线路径
    // 找到最短布线路径则返回true，否则返回false
    if((start.row==finish.row)&&(start.col==finish.col)){
	    PathLen=0;
		return true;
	} 
    // 设置方格阵列“围墙”
    for(int i=0;i<=m+1;i++)
        grid[0][i]=grid[n+1][i]=1;// 顶部和底部
    for(int i=0;i<=n+1;i++)
        grid[i][0]=grid[i][m+1]=1;// 左翼和右翼
    // 初始化相对位移
    Position offset[4];
    offset[0].row=0;offset[0].col=1;// 右
    offset[1].row=1;offset[1].col=0;// 下
    offset[2].row=0;offset[2].col=-1;// 左
    offset[3].row=-1;offset[3].col=0;// 上
    int NumOfNbrs=4;// 相邻方格数
    Position here,nbr;
    here.row=start.row;
    here.col=start.col;
    grid[start.row][start.col]=2;
    // 标记可达方格位置
    Queue<Position> Q;
    do{// 标记可达相邻方格
        for(int i=0;i<NumOfNbrs;i++){
            nbr.row=here.row+offset[i].row;
            nbr.col=here.col+offset[i].col;
            if(grid[nbr.row][nbr.col]==0){
                // 该方格未标记
                grid[nbr.row][nbr.col]= grid[here.row][here.col]+1;
                if((nbr.row==finish.row)&&
                  (nbr.col==finish.col))break;// 完成布线
                Q.Add(nbr);
			} 
        }
        // 是否到达目标位置finish?
        if((nbr.row==finish.row)&&
           (nbr.col==finish.col))break;// 完成布线
        // 活结点队列是否非空
        if(Q.IsEmpty())return false;// 无解
        Q.Delete(here);// 取下一个扩展结点
    } while(true);
    // 构造最短布线路径
    PathLen=grid[finish.row][finish.col]-2;
    //path=new Position[PathLen];
    // 从目标位置finish开始向起始位置回溯
    here=finish;
    for(int j=PathLen-1;j>=0;j--){
        path[j]=here;
        // 找前驱位置
        for(int i=0;i<NumOfNbrs;i++){
            nbr.row=here.row+offset[i].row;
            nbr.col=here.col+offset[i].col;
            if(grid[nbr.row][nbr.col]==j+2)break;
        }
        here=nbr;// 向前移动
    }
    return true;
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
class bbnode1 
{
    template<class Tw,class Tp>
    friend class Knap;
    private:
        bbnode1 *parent;// 指向父结点的指针
        bool LChild;   // 左儿子结点标志
};

template<class Typew,class Typep>
class  HeapNode1 
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
        bbnode1 *ptr;  // 指向活结点在子集树中相应结点的指针
};

template<class Typew,class Typep>
class Knap 
{
	template<class Tw,class Tp>
    friend Tp Knapsack(Tp [],Tw [],Tw,int,int []);
    public:
        Typep MaxKnapsack();
    private:
        MaxHeap<HeapNode1<Typep,Typew> >*H;
        Typep Bound(int i);
        void AddLiveNode(Typep up,Typep cp,Typew cw,bool ch,int level);
        bbnode1 *E;    // 指向扩展结点的指针
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
    bbnode1 *b=new bbnode1;
    b->parent=E;
    b->LChild=ch;
    HeapNode1<Typep,Typew> N;
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
    H=new MaxHeap<HeapNode1<Typep,Typew> >(1000);
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
        HeapNode1<Typep,Typew> N;
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

class bbnode2 
{
    friend class Clique;
    private:
        bbnode2 *parent;// 指向父结点的指针
        bool LChild;  // 左儿子结点标志
};

class CliqueNode 
{
    friend class Clique;
    public:
        operator int()const{return un;}
    private:
        int cn,      // 当前团的顶点数
            un,      // 当前团最大顶点数的上界
            level;     // 结点在子集空间树中所处的层次
        bbnode2 *ptr; // 指向活结点在子集树中相应结点的指针
};

class Clique 
{
    public:
    	Clique(int n=0,int **a=0){this->n=n;this->a=a;}
	    int BBMaxClique(int[]);
    private:
        void AddLiveNode(MaxHeap<CliqueNode> &H,
            int cn,int un,int level,bbnode2 E[],bool ch);
        int **a,// 图G的邻接矩阵
            n; // 图G的顶点数
};

void Clique::AddLiveNode(MaxHeap<CliqueNode>
    &H,int cn,int un,int level,bbnode2 E[],bool ch)
{// 将活结点加入到子集空间树中并插入最大堆中
    bbnode2 *b=new bbnode2;
    b->parent=E;
    b->LChild=ch;
    CliqueNode N;
    N.cn=cn;
    N.ptr=b;
    N.un=un;
    N.level=level;
    H.Insert(N);
}

int Clique::BBMaxClique(int bestx[])
{  // 解最大团问题的优先队列式分支限界法
    // 定义最大堆的容量为1000
    MaxHeap<CliqueNode> H(1000);
    // 初始化
    bbnode2 *E=0;
    int i=1,
        cn=0,
        bestn=0;
    // 搜索子集空间树
    while(i!=n+1){// 非叶结点
        // 检查顶点i与当前团中其它顶点之间是否有边相连
        bool OK=true;
        bbnode2 *B=E;
        for(int j=i-1;j>0;B=B->parent,j--)
            if(B->LChild && a[i][j]==0){
                OK=false;
                break;
			}
        if(OK){// 左儿子结点为可行结点
            if(cn+1>bestn)bestn=cn+1;
            AddLiveNode(H,cn+1,cn+n-i+1,i+1,E,true);
		}
        if(cn+n-i>=bestn)
            // 右子树可能含最优解
            AddLiveNode(H,cn,cn+n-i,i+1,E,false);
        // 取下一扩展结点
        CliqueNode N;
        H.DeleteMax(N);// 堆非空
        E=N.ptr;
        cn=N.cn;
        i=N.level;
    }
    // 构造当前最优解
    for(int j=n;j>0;j--){
        bestx[j]=E->LChild;
        E=E->parent;
    }
    return bestn;
}

template<class Type>
class Traveling 
{
    public:
    	Traveling(int n=0,Type **a=0,Type NoEdge=0){
		    this->n=n;this->a=a;this->NoEdge=NoEdge;
		}
        Type BBTSP(int v[]);
    private:
        int  n;      // 图G的顶点数
        Type **a,   // 图G的邻接矩阵
             NoEdge,// 图G的无边标志
             cc,    // 当前费用
             bestc;  // 当前最小费用
};

template<class Type>
class MinHeapNode2 
{
    friend Traveling<Type>;
    public:
        operator Type()const{return lcost;}
    private:
        Type lcost,// 子树费用的下界
             cc,  // 当前费用
             rcost;// x[s:n-1]中顶点最小出边费用和
        int   s,  // 根结点到当前结点的路径为x[0:s]
             *x;  // 需要进一步搜索的顶点是x[s+1:n-1]
};

template<class Type>
Type Traveling<Type>::BBTSP(int v[])
{// 解旅行售货员问题的优先队列式分支限界法
    // 定义最小堆的容量为1000
    MinHeap<MinHeapNode2<Type> >H(1000);
    Type *MinOut=new Type[n+1];
    // 计算MinOut[i]=顶点i的最小出边费用
    Type MinSum=0;// 最小出边费用和
    for(int i=1;i<=n;i++){
        Type Min=NoEdge;
        for(int j=1;j<=n;j++)
            if(a[i][j]!=NoEdge && 
                 (a[i][j]<Min || Min==NoEdge))
                Min=a[i][j];
        if(Min==NoEdge)return NoEdge;// 无回路
        MinOut[i]=Min;
        MinSum+=Min;
    }
    // 初始化
    MinHeapNode2<Type> E;
    E.x=new int[n];
    for(int i=0;i<n;i++)
        E.x[i]=i+1;
    E.s=0;
    E.cc=0;
    E.rcost=MinSum;
    Type bestc=NoEdge;
    // 搜索排列空间树
    while(E.s<n-1){// 非叶结点
        if(E.s==n-2){// 当前扩展结点是叶结点的父结点
            // 再加2条边构成回路
             // 所构成回路是否优于当前最优解
            if(a[E.x[n-2]][E.x[n-1]]!=NoEdge &&
                a[E.x[n-1]][1]!=NoEdge &&(E.cc +
                a[E.x[n-2]][E.x[n-1]]+a[E.x[n-1]][1]
               <bestc || bestc==NoEdge)){
                // 费用更小的回路
                bestc=E.cc+a[E.x[n-2]][E.x[n-1]]+a[E.x[n-1]][1];
                E.cc=bestc;
                E.lcost=bestc;
                E.s++;
                H.Insert(E);
			}
            else delete[] E.x;
		}  // 舍弃扩展结点
        else{// 产生当前扩展结点的儿子结点
            for(int i=E.s+1;i<n;i++)
                if(a[E.x[E.s]][E.x[i]]!=NoEdge){
                    // 可行儿子结点
                    Type cc=E.cc+a[E.x[E.s]][E.x[i]];
                    Type rcost=E.rcost-MinOut[E.x[E.s]];
                    Type b=cc+rcost;// 下界
                    if(b<bestc || bestc==NoEdge){
                        // 子树可能含最优解
                        // 结点插入最小堆
                        MinHeapNode2<Type> N;
                        N.x=new int[n];
                        for(int j=0;j<n;j++)
                            N.x[j]=E.x[j];
                        N.x[E.s+1]=E.x[i];
                        N.x[i]=E.x[E.s+1];
                        N.cc=cc;
                        N.s=E.s+1;
                        N.lcost=b;
                        N.rcost=rcost;
                        H.Insert(N);
					}
                }
            delete[] E.x;}  // 完成结点扩展
            try{H.DeleteMin(E);}        // 取下一扩展结点
            catch(OutOfBounds){break;} // 堆已空
    }
    if(bestc==NoEdge)return NoEdge;// 无回路
    // 将最优解复制到v[1:n]
    for(int i=0;i<n;i++)
        v[i+1]=E.x[i];
    while(true){// 释放最小堆中所有结点
        delete[] E.x;
        try{H.DeleteMin(E);}
        catch(OutOfBounds){break;}
    }
    return bestc;
}

class BoardNode 
{
    friend int BBArrangement(int **,int,int,int*&);
    public:
        operator int()const{return cd;}
    private:
        int  *x, // x[1:n]记录电路板排列
             s,  // x[1:s]是当前结点所相应的部分排列
             cd, // x[1:s]的密度
            *now;// now[j]是x[1:s]所含连接块j中电路板数
};

int BBArrangement(int **B,int n,int m,int *&bestx)
{// 解电路板排列问题的优先队列式分支限界法
    MinHeap<BoardNode> H(1000);// 活结点最小堆
    // 初始化
    BoardNode E;
    E.x=new int[n+1];
    E.s=0;
    E.cd=0;
    E.now=new int[m+1];
    int *total=new int[m+1];
    // now[i]=x[1:s]所含连接块i中电路板数
    // total[i]=连接块i中电路板数
    for(int i=1;i<=m;i++){
        total[i]=0;
        E.now[i]=0;
    }
    for(int i=1;i<=n;i++){
        E.x[i]=i;// 初始排列为12345...n
        for(int j=1;j<=m;j++)
            total[j]+=B[i][j];// 连接块j中电路板数
    }
    int bestd=m+1;// 当前最小密度
    bestx=0;
    do{// 结点扩展
        if(E.s==n-1){// 仅一个儿子结点
            int ld=0;// 最后一块电路板的密度
            for(int j=1;j<=m;j++)
                ld+=B[E.x[n]][j];
            if(ld<bestd){// 密度更小的电路板排列
                delete[] bestx;
                bestx=E.x;
                bestd=max(ld,E.cd);
            }
            else delete[] E.x;
            delete[] E.now;
		}
        else{// 产生当前扩展结点的所有儿子结点
            for(int i=E.s+1;i<=n;i++){
                BoardNode N;
                N.now=new int[m+1];
                for(int j=1;j<=m;j++)
                    // 新插入的电路板
                    N.now[j]=E.now[j]+B[E.x[i]][j];
                int ld=0;// 新插入电路板的密度
                for(int j=1;j<=m;j++)
                if(N.now[j]>0 && total[j]!=N.now[j])
                    ld++;
                N.cd=max(ld,E.cd);
                if(N.cd<bestd){// 可能产生更好的叶结点
                    N.x=new int[n+1];
                    N.s=E.s+1;
                    for(int j=1;j<=n;j++)
                        N.x[j]=E.x[j];
                    N.x[N.s]=E.x[i];
                    N.x[i]=E.x[N.s];
                    H.Insert(N);
				}
                else delete[] N.now;
			}
            delete[] E.x;
		} // 完成当前结点扩展
        try{H.DeleteMin(E);} // 取下一扩展结点
        catch(OutOfBounds){return bestd;}  // 无扩展结点
    } while(E.cd<bestd);
    // 释放最小堆中所有结点
    do{delete[] E.x;
        delete[] E.now;
        try{H.DeleteMin(E);}
        catch(OutOfBounds){break;}
    } while(true);
    return bestd;
}

class Flowshop;
class MinHeapNode3 
{
    friend Flowshop;
    public:
        operator int()const{return bb;}
    private:
        void Init(int),
           NewNode(MinHeapNode3,int,int,int,int);
        int  s, // 已安排作业数
            f1,// 机器1上最后完成时间
            f2,// 机器2上最后完成时间
            sf2,// 当前机器2上的完成时间和
            bb,// 当前完成时间和下界
            *x;// 当前作业调度
};

void MinHeapNode3::Init(int n)
{ // 最小堆结点初始化
    x=new int[n];
    for(int i=0;i<n;i++)
        x[i]=i;
    s=0;
    f1=0;
    f2=0;
    sf2=0;
    bb=0;
}

void MinHeapNode3::NewNode(MinHeapNode3 E,int Ef1,int Ef2,int Ebb,int n)
{ // 最小堆新结点
    x=new int[n];
    for(int i=0;i<n;i++)
        x[i]=E.x[i];
    f1=Ef1;
    f2=Ef2;
    sf2=E.sf2+f2;
    bb=Ebb;
    s=E.s+1;
}

class Flowshop 
{
	friend void tst11();
    public:
        int BBFlow();
    private:
        int  Bound(MinHeapNode3,int &,int &,bool **);
        void Sort();
        int  n,  // 作业数
            **M,// 各作业所需的处理时间数组
            **b, // 各作业所需的处理时间排序数组
            **a, // 数组M和b的对应关系数组
            *bestx,// 最优解
            bestc; // 最小完成时间和
        bool **y;  // 工作数组
};

void Flowshop::Sort()
{ // 对各作业在机器1和2上所需时间排序
    int *c=new int[n];
    for(int j=0;j<2;j++){
        for(int i=0;i<n;i++){
            b[i][j]=M[i][j];
            c[i]=i;
		}
        for(int i=0;i<n-1;i++)
            for(int k=n-1;k>i;k--)
                if(b[k][j]<b[k-1][j]){
                    Swap(b[k][j],b[k-1][j]);
                    Swap(c[k],c[k-1]);
				}
        for(int i=0;i<n;i++)a[c[i]][j]=i;
	}
    delete[] c;
}

int Flowshop::Bound(MinHeapNode3 E,int & f1,int & f2,bool **y)
{ // 计算完成时间和下界
    for(int k=0;k<n;k++)
        for(int j=0;j<2;j++)
            y[k][j]=false;
    for(int k=0;k<=E.s;k++)
        for(int j=0;j<2;j++)
            y[a[E.x[k]][j]][j]=true;
    f1=E.f1+M[E.x[E.s]][0];
    f2=((f1>E.f2)?f1:E.f2)+M[E.x[E.s]][1];
    int sf2=E.sf2+f2;
    int s1=0,s2=0,k1=n-E.s,k2=n-E.s,f3=f2;
    // 计算s1的值
    for(int j=0;j<n;j++)
        if(!y[j][0]){
            k1--;
            if(k1==n-E.s-1)
            f3=(f2>f1+b[j][0])?f2:f1+b[j][0];
            s1+=f1+k1*b[j][0];
		}
        // 计算s2的值
        for(int j=0;j<n;j++)
            if(!y[j][1]){
                k2--;
                s1+=b[j][1];
                s2+=f3+k2*b[j][1];
			}
    // 返回完成时间和下界
    return sf2+((s1>s2)?s1:s2);
}

int Flowshop::BBFlow()
{ // 解批处理作业调度问题的优先队列式分支限界法
    Sort();  // 对各作业在机器1和2上所需时间排序
    // 定义最小堆的容量为1000
    MinHeap<MinHeapNode3> H(1000);
    MinHeapNode3 E;
    // 初始化
    E.Init(n);
    // 搜索排列空间树
    while(E.s<=n){
        if(E.s==n){// 叶结点
            if(E.sf2<bestc){
                bestc=E.sf2;
                for(int i=0;i<n;i++)
                    bestx[i]=E.x[i];
			}
            delete[] E.x;
		}
        else{// 产生当前扩展结点的儿子结点
            for(int i=E.s;i<n;i++){
                Swap(E.x[E.s],E.x[i]);
                int f1,f2;
                int bb=Bound(E,f1,f2,y);
                if(bb<bestc){
                    // 子树可能含最优解
                    // 结点插入最小堆
                    MinHeapNode3 N;
                    N.NewNode(E,f1,f2,bb,n);
                    H.Insert(N);
                    //cout<<"H.Size()="<<H.Size()<<endl;
				}
                Swap(E.x[E.s],E.x[i]);
            }
            delete[] E.x;
		}  // 完成结点扩展
        try{H.DeleteMin(E);}        // 取下一扩展结点
        catch(OutOfBounds){break;} // 堆已空
    }
    return bestc;
}

int main() 
{
	return 0;
}

