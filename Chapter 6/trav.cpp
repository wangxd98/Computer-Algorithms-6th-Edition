
#include <bits/stdc++.h>
using namespace std;
#include "2darray.h"
#include "minheap.h"

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
class MinHeapNode 
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
    MinHeap<MinHeapNode<Type> >H(1000);
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
    MinHeapNode<Type> E;
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
                        MinHeapNode<Type> N;
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

int main()
{
    cout<<"Test BBTSP"<<endl;
    int n,m,x,y,z,v[100],**a;
    const int NoEdge=0;
    make2dArray(a,100,100);
    while(cin>>n>>m){
        for(int i=0;i<=n;i++)
            for(int j=0;j<=n;j++)a[i][j]=NoEdge;
        for(int i=1;i<=m;i++){
        	cin>>x>>y>>z;a[x][y]=a[y][x]=z;
		}
		Traveling<int> Trav(n,a,NoEdge);
	    cout<<Trav.BBTSP(v)<<endl;
        for(int i=1;i<=n;i++)cout<<v[i]<<" ";
        cout<<v[1]<<endl;
	}
	delete2dArray(a,100);
	return 0;
}