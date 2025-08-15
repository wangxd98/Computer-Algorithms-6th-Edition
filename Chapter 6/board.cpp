
#include <bits/stdc++.h>
using namespace std;
#include "2darray.h"
#include "minheap.h"

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

int main()
{
    cout<<"Test BBArrangement"<<endl;
    int n,m,**B;
    int *p=new int[500];
    make2dArray(B,100,100);
    while(cin>>n>>m){
        for(int i=1;i<=n;i++) 
            for(int j=1;j<=m;j++)
                cin>>B[i][j];
		cout <<BBArrangement(B,n,m,p)<< endl;
		copy(p+1,p+n+1,ostream_iterator<int>(cout," "));
        cout<<endl;
    }
    delete2dArray(B,100);
    return 0;
}
/*
tst10.in:
8 5
1 1 1 1 1
0 1 0 1 0
0 1 1 1 0
1 0 1 1 0
1 0 1 0 0
1 1 0 1 0
0 0 0 0 1
0 1 0 0 1
tst10.out:
Test BBArrangement
4
2 8 7 3 1 5 6 4 
*/