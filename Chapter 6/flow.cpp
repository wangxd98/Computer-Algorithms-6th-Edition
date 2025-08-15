#include <bits/stdc++.h>
using namespace std;
#include "swap.h"
#include "2darray.h"
#include "minheap.h"
 
class Flowshop;
class MinHeapNode 
{
    friend Flowshop;
    public:
        operator int()const{return bb;}
    private:
        void Init(int),
           NewNode(MinHeapNode,int,int,int,int);
        int  s, // 已安排作业数
            f1,// 机器1上最后完成时间
            f2,// 机器2上最后完成时间
            sf2,// 当前机器2上的完成时间和
            bb,// 当前完成时间和下界
            *x;// 当前作业调度
};

void MinHeapNode::Init(int n)
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

void MinHeapNode::NewNode(MinHeapNode E,int Ef1,int Ef2,int Ebb,int n)
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
	friend int main();
    public:
        int BBFlow();
    private:
        int  Bound(MinHeapNode,int &,int &,bool **);
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

int Flowshop::Bound(MinHeapNode E,int & f1,int & f2,bool **y)
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
    MinHeap<MinHeapNode> H(1000);
    MinHeapNode E;
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
                    MinHeapNode N;
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
    cout<<"Test BBFlow"<<endl;
    int n,bestx[100],**M,**a,**b;
    bool **y;
    make2dArray(M,100,2);
    make2dArray(a,100,2);
    make2dArray(b,100,2);
    make2dArray(y,100,2);
    while(cin>>n){
	    for(int i=0;i<2;i++)
            for(int j=0;j<n;j++)
                cin>>M[j][i];
        Flowshop F;
	    F.n=n;F.M=M;F.b=b;F.a=a;F.y=y;
	    F.bestx=bestx;
        F.bestc=INT_MAX;
	    cout<<F.BBFlow()<<endl;
	    for(int i=0;i<n;i++)cout<<bestx[i]+1<<" ";cout<<endl;
	}
	delete2dArray(M,100);
	delete2dArray(a,100);
	delete2dArray(b,100);
	delete2dArray(y,100);
	return 0;
}
/*
tst11.in:
3
2 3 2
1 1 3
3
2 5 4
3 2 1
5
2 5 4 1 3
3 2 1 5 2
tst11.out:
Test BBFlow
18
1 3 2 
25
1 3 2 
52
4 3 1 5 2 
*/