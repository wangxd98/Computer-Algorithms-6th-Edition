
#include <bits/stdc++.h>
using namespace std;
#include "2darray.h"
#include "maxheap.h"

class bbnode 
{
    friend class Clique;
    private:
        bbnode *parent;// 指向父结点的指针
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
        bbnode *ptr; // 指向活结点在子集树中相应结点的指针
};

class Clique 
{
    public:
    	Clique(int n=0,int **a=0){this->n=n;this->a=a;}
	    int BBMaxClique(int[]);
    private:
        void AddLiveNode(MaxHeap<CliqueNode> &H,
            int cn,int un,int level,bbnode E[],bool ch);
        int **a,// 图G的邻接矩阵
            n; // 图G的顶点数
};

void Clique::AddLiveNode(MaxHeap<CliqueNode>
    &H,int cn,int un,int level,bbnode E[],bool ch)
{// 将活结点加入到子集空间树中并插入最大堆中
    bbnode *b=new bbnode;
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
    bbnode *E=0;
    int i=1,
        cn=0,
        bestn=0;
    // 搜索子集空间树
    while(i!=n+1){// 非叶结点
        // 检查顶点i与当前团中其它顶点之间是否有边相连
        bool OK=true;
        bbnode *B=E;
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

int main()
{
    cout<<"Test MaxClique"<<endl;
    int n,m,x,y,v[100],**a;
    make2dArray(a,100,100);
    while(cin>>n>>m){
        for(int i=0;i<=n;i++)
            for(int j=0;j<=n;j++)a[i][j]=0;
        for(int i=1;i<=m;i++){
        	cin>>x>>y;a[x][y]=a[y][x]=1;
		}
	    Clique C(n,a);
	    cout<<C.BBMaxClique(v)<<endl;
	    for(int i=1;i<=n;i++)if(v[i])cout<<i<<" ";cout<<endl;
	}
	delete2dArray(a,100);
	return 0;
}