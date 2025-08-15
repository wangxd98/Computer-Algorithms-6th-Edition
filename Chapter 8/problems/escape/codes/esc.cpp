//escape

#include <bits/stdc++.h> 
using namespace std; 

#include "GRAPH.h"
//#include "cycles1.h"
//#include "cycles2.h"
//#include "simplex.h"
#include "shortest1.h"
//#include "shortest2.h"

class ESCAPE
{
    int n,mm,nn,f,s,t,*st;
    
    int btype(int i,int j)
    {
       int b=0;
       if((i==1)||(i==mm)||(j==1)||(j==nn))b++;
       if(start(i,j))b+=2;
       return b;
    }

    int num(int i,int j)
    {
       if((i>=1)&&(i<=mm)&&(j>=1)&&(j<=nn))return((i-1)*nn+j)*2;
        else return -1;
    }

    int start(int i,int j)
    {
        return st[(i-1)*nn+j];
    }

    void constructG(GRAPH<EDGE> &G)
    {
        int u[5],v[5];
        for(int i=1;i<=mm;i++)
            for(int j=1;j<=nn;j++){
                int k=num(i,j);
                int b=btype(i,j);
                u[1]=num(i-1,j);u[2]=num(i,j-1);
                u[3]=num(i+1,j);u[4]=num(i,j+1);
                v[1]=btype(i-1,j);v[2]=btype(i,j-1);
                v[3]=btype(i+1,j);v[4]=btype(i,j+1);
                G.insert(new EDGE(k,k+1,1,0));
                if(b>1)G.insert(new EDGE(s,k,1,0));
                else for(int x=1;x<5;x++)
                    if((u[x]>0)&&((v[x]==0)||(v[x]==2)))
                        G.insert(new EDGE(u[x]+1,k,1,1));
                if((b==1)||(b==3))G.insert(new EDGE(k+1,t,1,0));
            }
        delete []st;
    }
	
    void read()
    {
        int i,j;
        n=mm*nn*2+2;
        st=new int[mm*nn+1];
        for(i=0;i<=mm*nn;i++)st[i]=0;
        s=0;t=1;
        for(int k=0;k<f;k++){
            cin>>i>>j;
            st[(i-1)*nn+j]=1;
        }
    }

    void trans(int i,int &u,int &v)
    {
        int k=i/2;
        u=k/nn;
        v=k%nn;
        if(v==0)v=nn;
        else u++;
    }

    bool succ(GRAPH<EDGE> &G)
    {
        int sum=0;
        adjIterator<EDGE> A(G,s);
        for(EDGE* e=A.beg();!A.end();e=A.nxt())
            if(e->from(s)&&e->flow()>0)sum++;
        if(sum<f)return 0;
        else return 1;
    }
public:
    ESCAPE(int m,int n,int f):mm(m),nn(n),f(f){}
    int solution()
    {
        read();
        GRAPH<EDGE> G(n,1);
        constructG(G);
        MINCOST<GRAPH<EDGE>,EDGE>(G,s,t);
        if(succ(G))return cost<GRAPH<EDGE>,EDGE>(G);
        else return -1;
    }
};

void comp()
{
	while(1){
		int m=0,n=0,f;
		cin>>m>>n>>f;
		if(m==0)return;
		ESCAPE E(m,n,f);
		cout<<E.solution()<<endl;
    }
}

int main()
{
   comp();
   return 0;
}

