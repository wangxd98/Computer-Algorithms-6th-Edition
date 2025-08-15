#include "2darray.h"

template<class Type >
inline void Swap(Type & a,Type & b)
{
    Type temp= a;
    a=b;b=temp;
}

/*
int n,*x;
void Output(int *x);
int f(int n,int t);
int g(int n,int t);
int h(int i);
bool Constraint(int t);
bool Bound(int t);
bool Solution(int t);

void Backtrack(int t)
{
    if(t>n)Output(x);
    else
        for(int i=f(n,t);i<=g(n,t);i++){
            x[t]=h(i);
            if(Constraint(t)&&Bound(t))Backtrack(t+1);
        }
}

void IterativeBacktrack(void)
{
    int t=1;
    while(t>0){
        if(f(n,t)<=g(n,t))
            for(int i=f(n,t);i<=g(n,t);i++){
                x[t]=h(i);
                if(Constraint(t)&&Bound(t)){
                    if(Solution(t))Output(x);
                    else t++;
				}
            }
        else t--;
    }
}

void Backtrack1(int t)
{
    if(t>n)Output(x);
    else
        for(int i=0;i<=1;i++){
            x[t]=i;
            if(Constraint(t)&&Bound(t))Backtrack1(t+1);
        }
}

void Backtrack2(int t)
{
    if(t>n)Output(x);
    else
        for(int i=t;i<=n;i++){
            Swap(x[t],x[i]);
            if(Constraint(t)&&Bound(t))Backtrack2(t+1);
            Swap(x[t],x[i]);
        }
}
*/

template<class Type>
class Loading1
{
	template<class T>
    friend T MaxLoading1(T [],T,int);
    void Backtrack(int i);
    private:
        int   n;     // 集装箱数
        Type *w,    // 集装箱重量数组
              c,     // 第一艘轮船的载重量
              cw,    // 当前载重量
              bestw; // 当前最优载重量
};

template<class Type>
void Loading1<Type>::Backtrack(int i)
{// 搜索第i层结点
    if(i>n){// 到达叶结点
        if(cw>bestw)bestw=cw;
        return;
	}
    // 搜索子树
    if(cw+w[i]<=c){// x[i]=1
        cw+=w[i];
        Backtrack(i+1);
        cw-=w[i];
	}
    Backtrack(i+1);// x[i]=0
}

template<class Type>
Type MaxLoading1(Type w[],Type c,int n)
{// 返回最优载重量
    Loading1<Type> X;
    // 初始化X
    X.w=w;
    X.c=c;
    X.n=n;
    X.bestw=0;
    X.cw=0;
    // 计算最优载重量
    X.Backtrack(1);
    return X.bestw;
}

template<class Type>
class Loading2 
{
	template<class T>
    friend T MaxLoading2(T [],T,int);
    private:
        void Backtrack(int i);
        int   n;     // 集装箱数
        Type *w,     // 集装箱重量数组
              c,     // 第一艘轮船的载重量
              cw,    // 当前载重量
              bestw, // 当前最优载重量
              r;     // 剩余集装箱重量
};

template<class Type>
void Loading2<Type>::Backtrack(int i)
{// 搜索第i层结点
    if(i>n){// 到达叶结点
        bestw=cw;
        return;
	}
    // 搜索子树
    r-=w[i];
    if(cw+w[i]<=c){// x[i]=1
        cw+=w[i];
        Backtrack(i+1);
        cw-=w[i];
	}
    if(cw+r>bestw)// x[i]=0
        Backtrack(i+1);
    r+=w[i];
}

template<class Type>
Type MaxLoading2(Type w[],Type c,int n)
{// 返回最优载重量
    Loading2<Type> X;
    // 初始化X
    X.w=w;
    X.c=c;
    X.n=n;
    X.bestw=0;
    X.cw=0;
    // 初始化r
    X.r=0;
    for(int i=1;i<=n;i++)
        X.r+=w[i];
    // 计算最优载重量
    X.Backtrack(1);
    return X.bestw;
}


template<class Type>
class Loading3 
{
    template<class T>
    friend T MaxLoading3(T [],T,int,int []);
    private:
        void Backtrack(int i);
        int   n,      // 集装箱数
             *x,      // 当前解
             *bestx;   // 当前最优解
        Type *w,      // 集装箱重量数组
             c,       // 第一艘轮船的载重量
             cw,      // 当前载重量
             bestw,   // 当前最优载重量
             r;      // 剩余集装箱重量
};

template<class Type>
void Loading3<Type>::Backtrack(int i)
{// 搜索第i层结点
    if(i>n){// 到达叶结点
        if(cw>bestw){ 
		    for(int j=1;j<=n;j++)bestx[j]=x[j];bestw=cw;
		}
        return;
	}
    // 搜索子树
    r-=w[i];
    if(cw+w[i]<=c){// 搜索左子树
        x[i]=1;
        cw+=w[i];
        Backtrack(i+1);
        cw-=w[i];
	}
    if(cw+r>bestw){// 搜索右子树
        x[i]=0;
        Backtrack(i+1);
	}
    r+=w[i];
}

template<class Type>
Type MaxLoading3(Type w[],Type c,int n,int bestx[])
{// 返回最优载重量
    Loading3<Type> X;
    // 初始化X 
    X.x=new int [n+1];
    X.w=w;
    X.c=c;
    X.n=n;
    X.bestx=bestx;
    X.bestw=0;
    X.cw=0;
    // 初始化r 
    X.r=0;
    for(int i=1;i<=n;i++)
        X.r+=w[i];
    X.Backtrack(1);
    delete []X.x;
    return X.bestw;
}


template<class Type>
Type MaxLoading(Type w[],Type c,int n,int bestx[])
{  // 迭代回溯法
   // 返回最优载重量及其相应解
   // 初始化根结点 
    int i=1; // 当前层
    // x[1:i-1] 为当前路径
    int *x=new int [n+1];
    Type bestw=0, // 当前最优载重量
         cw=0,   // 当前载重量
         r=0;    // 剩余集装箱重量
    for(int j=1;j<=n;j++)
        r+=w[j];
    // 搜索子树
    while(true){
        while(i<=n && cw+w[i]<=c){
            // 进入左子树
            r-=w[i];
            cw+=w[i];
            x[i]=1;
            i++;
        }
        if(i>n){// 到达叶结点
            for(int j=1;j<=n;j++)
                bestx[j]=x[j];
            bestw=cw;}
        else {// 进入右子树
            r-=w[i];
            x[i]=0;
            i++;
		}
        while(cw+r<=bestw){
            // 剪枝回溯
            i--;
            while(i>0 && !x[i]){
                // 从右子树返回
                r+=w[i];
                i--;
            }
            if(i == 0){
			    delete [] x;
                return bestw;
			}
            // 进入右子树
            x[i]=0;
            cw-=w[i];
            i++;
        }
    }
}

class Flowshop 
{
    friend Flow(int**,int,int []);
    private:
        void Backtrack(int i);
        int  **M,  // 各作业所需的处理时间
             *x,    // 当前作业调度
             *bestx, // 当前最优作业调度
             *f2,    // 机器2完成处理时间
             f1,     // 机器1完成处理时间
             f,      // 完成时间和
             bestf,  // 当前最优值
             n;     // 作业数
};

void Flowshop::Backtrack(int i)
{
    if(i>n){
        for(int j=1;j<=n;j++)
            bestx[j]=x[j];
        bestf=f;
    }
    else
        for(int j=i;j<=n;j++){
            f1+=M[x[j]][1];
            f2[i]=((f2[i-1]>f1)?f2[i-1]:f1)+M[x[j]][2];
            f+=f2[i];
            if(f < bestf){
                Swap(x[i],x[j]);
                Backtrack(i+1);
                Swap(x[i],x[j]);
            }
            f1-=M[x[j]][1];
            f-=f2[i];
        }
}

int Flow(int **M,int n,int bestx[])
{
    int ub= INT_MAX;
    Flowshop X;
    X.x=new int [n+1];
    X.f2=new int [n+1];
    X.M=M;
    X.n=n;
    X.bestx=bestx;
    X.bestf =ub;
    X.f1=0;
    X.f=0;
    for(int i=0;i<=n;i++)
        X.f2[i]=0,X.x[i]=i;
    X.Backtrack(1);
    delete [] X.x;
    delete [] X.f2;
    return X.bestf;
}


class Triangle 
{
    friend int Compute(int);
    private:
        void Backtrack(int t);
        int n,     // 第一行的符号个数
            half,  // n*(n+1)/4
            count, // 当前“+”号个数
            **p;  // 符号三角形矩阵
        long sum; // 已找到的符号三角形数
};

void Triangle::Backtrack(int t)
{
    if((count>half)||(t*(t-1)/2-count>half))return;
    if(t>n)sum++;
    else
        for(int i=0;i<2;i++){
            p[1][t]=i;
            count+=i;
            for(int j=2;j<=t;j++){
                p[j][t-j+1]=p[j-1][t-j+1]^p[j-1][t-j+2];
                count+=p[j][t-j+1];
            }
            Backtrack(t+1);
            for(int j=2;j<=t;j++)
                count-=p[j][t-j+1];
            count-=i;
        }
}

int Compute(int n)
{
    Triangle X;
    X.n=n;
    X.count=0;
    X.sum=0;
    X.half=n*(n+1)/2;
    if(X.half%2==1)return 0;
    X.half=X.half/2;
    int **p=new int * [n+1];
    for(int i=0;i <=n;i++)p[i]=new int [n+1];
    for(int i=0;i <=n;i++)
    for(int j=0;j <=n;j++)p[i][j]=0;
    X.p=p;
    X.Backtrack(1);
    for(int i=0;i<=n;i++)delete []p[i];	
	delete []p;
    return X.sum;
}

class Queen 
{
    friend int nQueen(int);
    private:
        bool Place(int k);
        void Backtrack(int t);
        int  n,   // 皇后个数
           *x;   // 当前解
        long sum; // 当前已找到的可行方案数
};

bool Queen::Place(int k)
{
    for(int j=1;j<k;j++)
        if((abs(k-j)==abs(x[j]-x[k]))||(x[j]==x[k]))return false;
    return true;
} 

void Queen::Backtrack(int t)
{
    if(t>n)sum++;
    else
        for(int i=1;i<=n;i++){
            x[t]=i;
            if(Place(t))Backtrack(t+1);
        }
}

int nQueen(int n)
{
    Queen X;
    // 初始化X
    X.n=n;
    X.sum=0;
    int *p=new int [n+1];
    for(int i=0;i <=n;i++)
        p[i]=0;
    X.x=p;
    X.Backtrack(1);
    delete [] p;
    return X.sum;
} 


class Queen1 
{
    friend int nQueen1(int);
    private:
        bool Place(int k);
        void Backtrack(void);
        int  n,   // 皇后个数
            *x;   // 当前解
        long sum; // 当前已找到的可行方案数
};

bool Queen1::Place(int k)
{
    for(int j=1;j<k;j++)
        if((abs(k-j)==abs(x[j]-x[k]))||(x[j]==x[k]))return false;
    return true;
}

void Queen1::Backtrack(void)
{
    x[1]=0;
    int k=1;
    while(k>0){
        x[k]+=1;
        while((x[k]<=n)&& !(Place(k)))x[k]+=1;
        if(x[k]<=n)
            if(k==n)sum++;
            else {
                k++;
                x[k]=0;
            }
        else k--;
    }
}

int nQueen1(int n)
{
    Queen1 X;
    // 初始化X
    X.n=n;
    X.sum=0;
    int *p=new int [n+1];
    for(int i=0;i <=n;i++)
        p[i]=0;
    X.x=p;
    X.Backtrack();
    delete [] p;
    return X.sum;
}


template<class Typew,class Typep>
class Knap 
{
	template<class Tw,class Tp>
    friend Tp Knapsack(Tp *,Tw *,Tw,int);
    private:
        Typep Bound(int i);
        void Backtrack(int i);
        Typew c;     // 背包容量
        int n;        // 物品数
        Typew *w;   // 物品重量数组
        Typep *p;    // 物品价值数组
        Typew cw;   // 当前重量
        Typep cp;    // 当前价值
        Typep bestp;  // 当前最优价值
};

template<class Typew,class Typep>
void Knap<Typew,Typep>::Backtrack(int i)
{
    if(i>n){// 到达叶结点
        bestp=cp;
        return;
	}
    if(cw+w[i]<=c){// 进入左子树
        cw+=w[i];
        cp+=p[i];
        Backtrack(i+1);
        cw-=w[i];
        cp-=p[i];
	}
    if(Bound(i+1)> bestp)// 进入右子树
        Backtrack(i+1);
}

template<class Typew,class Typep>
Typep Knap<Typew,Typep>::Bound(int i)
{// 计算上界
    Typew cleft=c - cw; // 剩余容量
    Typep b=cp;
    // 以物品单位重量价值递减序装入物品
    while(i<=n && w[i]<=cleft){
        cleft-=w[i];
        b+=p[i];
        i++;
    }
    // 装满背包
    if(i<=n)b+=p[i]* cleft/w[i] ;
    return b;
}

template<class Type>
class Object 
{
    template<class Tw,class Tp>
    friend Tp Knapsack(Tp[],Tw[],Tw,int);
    public:
        operator Type()const {return -d;}
    private:
        int ID;
        Type d;
};

template<class Type>
void Sort(Type a[],int n)
{
	std::sort(a,a+n);
}

template<class Typew,class Typep>
Typep Knapsack(Typep p[],Typew w[],Typew c,int n)
{
    // 为Knap::Backtrack初始化
    Typew W=0;
    Typep P=0;
    Object<Typep> *Q=new Object<Typep> [n];
    for(int i=1;i<=n;i++){
        Q[i-1].ID=i;
        Q[i-1].d=1.0*p[i]/w[i];
        P+=p[i];
        W+=w[i];
    }
    if(W<=c)return P; // 装入所有物品
    // 依物品单位重量价值排序
    Sort(Q,n);
    Knap<Typew,Typep> K;
    K.p=new Typep [n+1];
    K.w=new Typew [n+1];
    for(int i=1;i<=n;i++){
        K.p[i]=p[Q[i-1].ID];
        K.w[i]=w[Q[i-1].ID];
    }
    K.cp=0;
    K.cw=0;
    K.c=c;
    K.n=n;
    K.bestp=0;
    // 回溯搜索
    K.Backtrack(1);
    delete [] Q;
    delete [] K.w;
    delete [] K.p;
    return K.bestp;
}

class Clique 
{
    friend MaxClique(int **,int [],int);
    private:
        void Backtrack(int i);
        int  **a,   // 图G的邻接矩阵
            n,     // 图G的顶点数
            *x,    // 当前解
            *bestx, // 当前最优解
            cn,    // 当前顶点数
            bestn;  // 当前最大顶点数
};

void Clique::Backtrack(int i)
{// 计算最大团
    if(i>n){// 到达叶结点
        for(int j=1;j<=n;j++)bestx[j]=x[j];
        bestn=cn;
        return;
	}
    // 检查顶点 i 与当前团的连接
    int OK=1;
    for(int j=1;j < i;j++)
        if(x[j] && a[i][j] == 0){
            // i与j不相连
            OK=0;
            break;
		}
    if(OK){// 进入左子树
        x[i]=1;
        cn++;
        Backtrack(i+1);
        x[i]=0;
        cn--;
	}
    if(cn+n - i>bestn){// 进入右子树
        x[i]=0;
        Backtrack(i+1);
	}
}

int MaxClique(int **a,int v[],int n)
{
    Clique Y;
    // 初始化Y
    Y.x=new int [n+1];
    Y.a=a;
    Y.n=n;
    Y.cn=0;
    Y.bestn=0;
    Y.bestx=v;
    Y.Backtrack(1);
    delete [] Y.x;
    return Y.bestn;
}

class Color 
{
    friend int mColoring(int,int,int **);
    private:
        bool Ok(int k);
        void Backtrack(int t);
        int  n, // 图的顶点数
             m, // 可用颜色数
            **a,// 图的邻接矩阵
            *x; // 当前解
        long sum;// 当前已找到的可m着色方案数
};

bool Color::Ok(int k)
{// 检查颜色可用性
    for(int j=1;j<=n;j++)
        if((a[k][j]==1)&&(x[j]==x[k]))return false;
    return true;
}

void Color::Backtrack(int t)
{
    if(t>n){
        sum++;
        for(int i=1;i<=n;i++)
            cout<<x[i]<<" ";
        cout<<endl;
    }
    else
        for(int i=1;i<=m;i++){
            x[t]=i;
            if(Ok(t))Backtrack(t+1);
            x[t]=0;
        }
}

int mColoring(int n,int m,int **a)
{
    Color X;
    // 初始化X
    X.n=n;
    X.m=m;
    X.a=a;
    X.sum=0;
    int *p=new int [n+1];
    for(int i=0;i <=n;i++)
        p[i]=0;
    X.x=p;
    X.Backtrack(1);
    delete [] p;
    return X.sum;
}

template<class Type>
class Traveling 
{
    template<class T>
    friend T TSP(T **,int [],int,T);
    private:
        void Backtrack(int i);
        int  n,      // 图G的顶点数
            *x,     // 当前解
            *bestx;  // 当前最优解
        Type **a,    // 图G的邻接矩阵
             cc,    // 当前费用
             bestc,  // 当前最优值
             NoEdge;// 无边标记
};

template<class Type>
void Traveling<Type>::Backtrack(int i)
{
    if(i == n){
        if(a[x[n-1]][x[n]] != NoEdge && a[x[n]][1] != NoEdge &&
          (cc+a[x[n-1]][x[n]]+a[x[n]][1] < bestc || bestc == NoEdge)){
               for(int j=1;j<=n;j++)bestx[j]=x[j];
               bestc=cc+a[x[n-1]][x[n]]+a[x[n]][1];
			}
    }
    else {
        for(int j=i;j<=n;j++)
            // 是否可进入x[j]子树?
            if(a[x[i-1]][x[j]] != NoEdge &&
              (cc+a[x[i-1]][x[j]] < bestc || bestc == NoEdge)){
                // 搜索子树
                Swap(x[i],x[j]);
                cc+=a[x[i-1]][x[i]];
                Backtrack(i+1);
                cc-=a[x[i-1]][x[i]];
                Swap(x[i],x[j]);
			}
    }
}

template<class Type>
Type TSP(Type **a,int v[],int n,Type NoEdge)
{
    Traveling<Type> Y;
    // 初始化Y
    Y.x=new int [n+1];
    // 置x为单位排列
    for(int i=1;i<=n;i++)
        Y.x[i]=i;
    Y.a=a;
    Y.n=n;
    Y.bestc=NoEdge;
    Y.bestx=v;
    Y.cc=0;
    Y.NoEdge=NoEdge;
    // 搜索x[2:n]的全排列
    Y.Backtrack(2);
    delete [] Y.x;
    return Y.bestc;
}

class Circle 
{
    friend float CirclePerm(int,float *);
    private:
        float Center(int t);
        void Compute(void);
        void Backtrack(int t);
        float min,  // 当前最优值
            *x,   // 当前圆排列圆心横坐标
            *r;   // 当前圆排列
        int  n;   // 待排列圆的个数
};

float Circle::Center(int t)
{// 计算当前所选择圆的圆心横坐标
    float temp=0;
    for(int j=1;j<t;j++){
        float valuex=x[j]+2.0*sqrt(r[t]*r[j]);
        if(valuex>temp)temp=valuex;
    }
    return temp;
}

void Circle::Compute()
{// 计算当前圆排列的长度
    float low=0,
          high=0;
    for(int i=1;i<=n;i++){
        if(x[i]-r[i]<low)low=x[i]-r[i];
        if(x[i]+r[i]>high)high=x[i]+r[i];
    }
    if(high-low<min)min=high-low;
}

void Circle::Backtrack(int t)
{
    if(t>n)Compute();
    else
        for(int j=t;j<=n;j++){
            Swap(r[t],r[j]);
            float centerx=Center(t);
            if(centerx+r[t]+r[1]<min){//下界约束
                x[t]=centerx;
                Backtrack(t+1);
            }
            Swap(r[t],r[j]);
        }
}

float CirclePerm(int n,float *a)
{
    Circle X;
    X.n=n;
    X.r=a;
    X.min=100000;
    float *x=new float [n+1];
    X.x=x;
    X.Backtrack(1);
    delete [] x;
    return X.min;
}

class Board 
{
    friend Arrangement(int**,int,int,int []);
    private:
        void Backtrack(int i,int cd);
        int  n,      // 电路板数
            m,     // 连接块数
            *x,     // 当前解
            *bestx,  // 当前最优解
            bestd,  // 当前最优密度
            *total,  // total[j]=连接块j的电路板数
            *now,  // now[j]=当前解中所含
                 // 连接块j的电路板数
            **B;  // 连接块数组
};

void Board::Backtrack(int i,int cd)
{// 回溯搜索排列树
    if(i == n){
        for(int j=1;j<=n;j++)
            bestx[j]=x[j];
        bestd=cd;
	}
    else 
        for(int j=i;j<=n;j++){
            // 选择x[j]为下一块电路板
            int ld=0;
            for(int k=1;k<=m;k++){
                now[k]+=B[x[j]][k];
                if(now[k]>0 && total[k] != now[k])
                    ld++;
            }
            // 更新ld
            if(cd>ld)ld=cd;
            if(ld < bestd){// 搜索子树
                Swap(x[i],x[j]);
                Backtrack(i+1,ld);
                Swap(x[i],x[j]);
			}
            // 恢复状态
            for(int k=1;k<=m;k++)
                now[k]-=B[x[j]][k];
        }
}

int Arrangement(int **B,int n,int m,int bestx[])
{
    Board X;
    // 初始化X
    X.x=new int [n+1];
    X.total=new int [m+1];
    X.now=new int [m+1];
    X.B=B;
    X.n=n;
    X.m=m;
    X.bestx=bestx;
    X.bestd=m+1;
    // 初始化total和now
    for(int i=1;i<=m;i++){
        X.total[i]=0;
        X.now[i]=0;
    }
    // 初始化x为单位排列并计算total
    for(int i=1;i<=n;i++){
        X.x[i]=i;
        for(int j=1;j<=m;j++)
            X.total[j]+=B[i][j];
    }
    // 回溯搜索
    X.Backtrack(1,0);
    delete [] X.x;
    delete [] X.total;
    delete [] X.now;
    return X.bestd;
}

class Stamp 
{
    friend int MaxStamp(int,int,int []);
    private:
        void Backtrack(int i,int r);
        int  n,       // 邮票面值数
            m,      // 每张信封最多允许贴的邮票数
            maxvalue,// 当前最优值
            maxint,  // 大整数
            maxl,    // 邮资上界
            *x,      // 当前解
            *y,      // 贴出各种邮资所需最少邮票数
            *bestx;  // 当前最优解
};

void Stamp::Backtrack(int i,int r)
{
    for(int j=0;j<= x[i-2]*(m-1);j++)
        if(y[j]<m)
            for(int k=1;k<=m-y[j];k++)
                if(y[j]+k<y[j+x[i-1]*k])y[j+x[i-1]*k]=y[j]+k;
    while(y[r]<maxint)r++;
    if(i>n){
        if(r-1>maxvalue){
            maxvalue=r-1;
            for(int j=1;j<=n;j++)
                bestx[j]=x[j];
		}
        return;
    }
   int *z=new int [maxl+1];
    for(int k=1;k<=maxl;k++)
        z[k]=y[k];
    for(int j=x[i-1]+1;j<=r;j++){
        x[i]=j;
        Backtrack(i+1,r);
        for(int k=1;k<=maxl;k++)
            y[k]=z[k];
	}
    delete [] z;
}

int MaxStamp(int n,int m,int bestx[])
{
    Stamp X;
    int maxint=32767;
    int maxl=1500;
    X.n=n;
    X.m=m;
    X.maxvalue=0;
    X.maxint=maxint;
    X.maxl=maxl;
    X.bestx=bestx;
    X.x=new int [n+1];
    X.y=new int [maxl+1];
    for(int i=0;i<=n;i++)X.x[i]=0;
    for(int i=1;i<=maxl;i++)X.y[i]=maxint;
    X.x[1]=1;
    X.y[0]=0;
    X.Backtrack(2,1);
    delete [] X.x;
    delete [] X.y;
    return X.maxvalue;
}

/*
int Estimate(int n,Type *x)
{
    int m=1,r=1,k=1;
    while(k<=n){
        SetType T= x[k]的满足约束的可取值集合；
        if(Size(T)==0)return m;
        r*=Size(T);
        m+=r;
        x[k]=Choose(T);
        k++;
	}
    return m;
}

*/
