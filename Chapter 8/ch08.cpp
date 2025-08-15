#include <bits/stdc++.h>
using namespace std;

#include "2darray.h"
#include "queue.h"
#include "gq.h"
#include "xcept.h"

#define M INT_MAX
#define INF 0x3f3f3f3f

const int SE=2e5+5;

class LinearProgram 
{
    public:
	    LinearProgram(char *filename);
        ~LinearProgram();
        void solve();
    private:
        int enter(int objrow);
        int leave(int col);
        int simplex(int objrow);
	    int phase1();
        int phase2();
	    int compute();
	    void swapbasic(int row,int col);
        void pivot(int row,int col);
        void setbasic(int *basicp);
        void problem();
        void output();
	    int m,          // 约束总数
            n,         // 变量数
            m1,       // 不等式约束数(≤)
            m2,       // 等式约束数
            m3,       // 不等式约束数(≥)
		    n1,n2,    //  n1=n + m3;n2=n 1+ m1;
		    error,     // 记录错误类型
		    *basic,    // 基本变量下标
		    *nonbasic;// 非基本变量下标
	    double **a,minmax;
};

LinearProgram::LinearProgram(char *filename)
{
    ifstream inFile;
    int i,j;
    double value;
    /*cout<< "按照下列格式输入数据:" <<endl;
    cout<<"1:+1(max)或 -1(min);m;n" <<endl;
    cout<<"2:m1;m2;m3 " <<endl;
    cout<<"约束系数和右端项" <<endl;
    cout<<"目标函数系数" <<endl<<endl;*/
    error=0;
    inFile.open(filename);
    inFile>>minmax;
    inFile>>m;
    inFile>>n;
    //  输入各类约束数
    inFile>>m1;
    inFile>>m2;
    inFile>>m3;
    if( m!=m1+m3+m2 )error=1;
    n1=n + m3;
    n2=n + m1 + m3;
    make2dArray(a,m+2,n1+1);
    basic=new int[m+2];
    nonbasic=new int[n1+1];
    // 初始化基本变量和非基本变量
    for(i=0;i<=m+1;i++)
        for(j=0;j<=n1;j++)a[i][j]=0.0;
    for(j=0;j<=n1;j++)nonbasic[j]=j;
    // 引入松驰变量和人工变量
    for(i=1,j=n1+1;i<=m;i++,j++)basic[i] =j;
    for(i=m-m3+1,j=n+1;i<=m;i++,j++){
	    a[i][j]=-1.0;
        a[m+1][j]=-1.0;
    }
    // 输入约束系数和右端项
    for(i=1;i<=m;i++){
        for(j=1;j<=n;j++){
            inFile>>value;
            a[i][j]=value;
	    }
        inFile>>value;
	    if(value<0)error=1;
        a[i][0]=value;
    }
    // 输入目标函数系数
    for(j=1;j<=n;j++){
        inFile>>value;
        a[0][j]=value * minmax;
    }
    // 引入人工变量，构造第1阶段的辅助目标函数
    for(j=1;j<=n;j++){
        for(i=m1+1,value=0.0;i<=m;i++)value+=a[i][j];
        a[m+1][j]=value;
    }
    inFile.close();
    problem();
} 

LinearProgram::~LinearProgram()
{
	delete []nonbasic;
	delete []basic;
	delete2dArray(a,m+2);
}

void LinearProgram::problem()
{
   int width=8;	
   cout.setf(ios::fixed|ios::showpoint|ios::right);
   cout.precision(2);
   // 目标函数
   if (minmax > 0) cout<<"Maximize:"<<endl;
   else cout<<"Minimize:"<<endl;
   for (int j=1;j<=n;j++){
      cout<<setw(width)<<minmax*a[0][j]<<" * x"<<j;
      if (j!=n)cout<<" + ";
      cout<<endl;
   }
   cout<<endl;
   cout<<"约束条件:"<<endl;
   for (int i=1;i<=m;i++){
      for (int j=1;j<=n;j++){
         if (j==1)cout<<"#"<<i<<"...";
         else cout<<" ";
         cout<<setw(width)<<a[i][j]<<" * x"<<j;
         if (j!=n) cout<<" + ";
	  }
      if (i<=m1)cout<<" <= ";
      else if (i>m1+m2) cout<<" >= ";
      else cout<<"= ";
      cout<<setw(width)<<a[i][0]<<endl;
    }
    cout<<endl;
}

int LinearProgram::simplex(int objrow)
{
	for(int row=0;;){
        int col=enter(objrow);
        if( col>0 )row=leave(col);
	    else return 0;
        if( row>0 )pivot(row,col);
	    else return 2;
	}
}

int LinearProgram::enter(int objrow)
{
    double temp=DBL_EPSILON;int col=0;
    for(int j=1;j<=n1;j++){
        if( nonbasic[j]<=n2 && a[objrow][j]>temp ){
            col=j;temp=a[objrow][j];
//	        break;                   // Bland 避循环法则
        }
    }
    return col;
}

int LinearProgram::leave(int col)
{
    double temp=DBL_MAX;int row=0;
    for(int i=1;i<=m;i++){
        double val=a[i][col];
        if( val>DBL_EPSILON ){
            val=a[i][0]/val;
            if( val<temp ){
                row=i;temp=val;
			}
		}
    }
    return row;
}

void LinearProgram::pivot(int row,int col)
{
    for(int j=0;j<=n1;j++)
        if( j!=col )a[row][j]=a[row][j]/a[row][col];
    a[row][col]=1.0/a[row][col];
    for(int i=0;i<=m+1;i++)
        if( i!=row ){
            for(int j=0;j<=n1;j++)
                if( j!=col ){
                    a[i][j]=a[i][j]-a[i][col]*a[row][j];
                    if( fabs(a[i][j])<DBL_EPSILON)a[i][j]=0.0;
			    }
		    a[i][col]=-a[i][col]*a[row][col];
	    }
    swapbasic(row,col);
}

void LinearProgram::swapbasic(int row,int col)
{
    int temp=basic[row];
    basic[row]=nonbasic[col];
    nonbasic[col]=temp;
}

int LinearProgram::compute()
{
    if( error>0 )return error;
    if( m!=m1 ){
	    error=phase1();
	    if(error>0)return error;
    }
    return phase2();
}

int LinearProgram::phase1()
{
    error=simplex(m+1);
    if( error>0 )return error;
    for(int i=1;i<=m;i++)
        if( basic[i]>n2 ){
            if( a[i][0]>DBL_EPSILON )return 3;
		    for(int j=1;j<=n1;j++)
                if( fabs(a[i][j])>=DBL_EPSILON ){
                    pivot(i,j);
                    break;
			    }
	    }
	return 0;
}

int LinearProgram::phase2()
{
    return simplex(0);
}

void LinearProgram::solve()
{
    //cout<<endl<<"*** 线性规划---单纯形算法 ***"<<endl<<endl;
    error=compute();
    switch(error){
        case 0: output();break;
        case 1: cout<<" – 输入数据错误 --"<<endl;break;
        case 2: cout<<" – 无界解 --"<<endl;break;
        case 3: cout<<" – 无可行解 --"<<endl;
    }
    //cout<<"计算结束"<<endl;
} 

void LinearProgram::setbasic(int *basicp)
{
   for(int j=1;j<=n+m;j++){
      basicp[j]=0;
	  for(int i=1;i<=m;i++)
	    if( basic[i]==j ){
		  basicp[j]=i;break;
		}
    }
}

void LinearProgram::output()
{
    int width=8,*basicp;
	double zero=0.0;
    basicp=new int[n+m+1];
    setbasic(basicp);
    cout.setf(ios::fixed|ios::showpoint|ios::right);
    cout.precision(4);
    cout<<endl<<"最优值："<<-minmax*a[0][0]<<endl<<endl;
    cout<<"最优解："<<endl<<endl;
    for(int j=1;j<=n;j++){
        cout<<"x"<<j<<" =";
        if(basicp[j]!=0)cout<<setw(width)<<a[basicp[j]][0];
        else cout<<setw(width)<<zero;
        cout<<endl;
	}
    cout<<endl;
	delete []basicp;
}

void input(char *filename,char *file)
{
    ifstream inFile;
    ofstream outFile;
    double *b,*c,**d;
    int i,j,k,p,q,n,m;
    inFile.open(filename);
    inFile>>n;
    m=n*(n+1)/2;
    b=new double [n];
    c=new double [m];
    make2dArray(d,n,m);
    for(i=0;i<n;i++)inFile>>b[i];
    for(i=0,k=0;i<n;i++)
	    for(j=0;j<n-i;j++)
            inFile>>c[k++];
    inFile.close();
    for(i=0;i<n;i++)
	    for(j=0;j<m;j++)d[i][j]=0;
    for(k=0;k<n;k++){
        p=n-k;q=k*n-k*(k-1)/2;
	    for(i=0;i<p;i++)
            for(j=i;j<p;j++)
                d[i+k][q+j]=1;
    }
    outFile.open(file);
    outFile<<-1<<" "<<n<<" "<<m<<endl;
    outFile<<0<<" "<<0<<" "<<n<<endl;
    for(i=0;i<n;i++){
        for(j=0;j<m;j++)
		    outFile<<d[i][j]<<" ";
        outFile<<b[i]<<endl;
    }
    for(i=0;i<m;i++)outFile<<c[i]<<" ";
    outFile<<endl;
    outFile.close();
    delete []b;delete []c;
    delete2dArray(d,n);
}

template <class keyType> class PQ 
{
    int d,N;
    vector<int> pq,qp;
    const vector<keyType> &a;
    void exch(int i,int j)
    {
        int t=pq[i];pq[i]=pq[j];pq[j]=t;
        qp[pq[i]]=i;qp[pq[j]]=j;
    }
    void fixUp(int k)
    {
        while(k>1 && a[pq[(k+d-2)/d]]<a[pq[k]]){
            exch(k,(k+d-2)/d);k=(k+d-2)/d;
        } 
    }
    void fixDown(int k,int N)
    {
        int j;
        while((j=d*(k-1)+2)<=N){
            for(int i=j+1;i<j+d && i<=N;i++)
               if(a[pq[j]]<a[pq[i]])j=i;
               if(!(a[pq[k]]<a[pq[j]]))break;
               exch(k,j);k=j;
        }
   }
public:
    PQ(int N,const vector<keyType> &a,int d=3): 
    a(a),pq(N+1,0),qp(N+1,0),N(0),d(d){}
    int empty()const{return N==0;}
    void insert(int v){pq[++N]=v;qp[v]=N;fixUp(N);}
    int deletemax(){exch(1,N);fixDown(1,N-1);return pq[N--];}
    void change(int k){fixUp(qp[k]);}
};

class EDGE
{
    int pv, pw, pcap, pcaplow, pcost, pflow, pflag;
public:
    EDGE(int v,int w,int cap,int cost=0,int caplow=0):
        pv(v),pw(w),pcaplow(caplow),pcap(cap),pflow(0),pflag(0),pcost(cost){}
    int v()const{return pv;}
    int w()const{return pw;}
    int cap()const{return pcap;}
    int caplow()const{return pcaplow;}
    int cost()const{return pcost;}
    int wt(int v)const{return from(v)? -pcost : pcost;}
    int flow()const{return pflow;}
    bool from(int v)const {return pv==v;}
    void sublow(){pcap-=pcaplow;}
    void addlow(){pcap+=pcaplow;pflow+=pcaplow;pflag=1;}
    bool residual(int v)const 
    {return(pv==v && pcap-pflow>0 || pw==v && pflow>0 );} 
    int other(int v)const {return from(v)?pw:pv;} 
    int capRto(int v)const{return from(v)?pflow-pcaplow*pflag:pcap-pflow;}
    int costRto(int v)const{return from(v)? -pcost : pcost;}
    void addflowRto(int v,int d){pflow+=from(v)?-d:d;}
};

template <class Edge> class GRAPH
{
    int Vcnt,Ecnt;bool digraph;
    vector<vector<Edge*>> adj;
public:
    GRAPH(int V,bool digraph=false):
    adj(V),Vcnt(V),Ecnt(0),digraph(digraph)
    {for(int i=0;i<V;i++)adj[i].assign(V,0);}
    GRAPH(){}
    int V()const{return Vcnt;}
    int E()const{return Ecnt;}
    bool directed()const{return digraph;}
    bool exist(Edge *e){return adj[e->v()][e->w()]!=0;}
    void insert(Edge *e)
    {
	    int v=e->v(),w=e->w();
        if(adj[v][w]==0)Ecnt++;
        else if(adj[v][w]->cost()<=e->cost())return;//存储费用较小的边
        adj[v][w]=e;
        if(!digraph)adj[w][v]=e;
    } 
    void remove(Edge *e)
    {
	    int v=e->v(),w=e->w();
        if(adj[v][w]!=0)Ecnt--;
        adj[v][w]=0;
        if(!digraph)adj[w][v]=0;
    } 

    void expand()
    {
    	for(int i=0;i<Vcnt;i++)adj[i].push_back(0);
    	vector<Edge*> x(Vcnt+1);
    	adj.push_back(x);
    	Vcnt++;
    } 
		
	Edge* edge(int v,int w)const{return adj[v][w];}
	
    void checksd(int s,int t,int &ss,int &dd)
    {
        ss=0;dd=0;
	    for(int i=0;i<Vcnt;i++){
            if(adj[s][i] && adj[s][i]->from(s)&& adj[s][i]->flow()>0 )
			    ss+=adj[s][i]->flow();
            if(adj[i][t] && adj[i][t]->from(i)&& adj[i][t]->flow()>0 )
			    dd+=adj[i][t]->flow();
	    }
    }

    void outflow()
    {
        for(int s=0;s<Vcnt;s++)
            for(int t=0;t<Vcnt;t++)
		        if(adj[s][t] && adj[s][t]->from(s)&& adj[s][t]->flow()>0)
			        cout<<s+1<<"->"<<t+1<<" "<<adj[s][t]->flow()<<endl;
    }

    /*void outflow()
    {
	    for(int s=0;s<Vcnt;s++)
            for(int t=0;t<Vcnt;t++){
			    if(adj[s][t] && adj[s][t]->flow()>0 )
		            cout<<s+1<<"->"<<t+1<<" "<<adj[s][t]->flow()<<" "<<adj[s][t]->cost()<<endl;
		}
    }*/
};

template <class Edge>
class adjIterator
{
    const GRAPH<Edge> &G;
    int i,j,v;
public:
    adjIterator(const GRAPH<Edge> &G,int v): G(G),v(v),i(0),j(0){}
    Edge *beg(){i=-1;j=-1;return nxt();}
    Edge *nxt()
    {
	    for(i++;i<G.V();i++)
            if(G.edge(v,i))return G.edge(v,i);
	    for(j++;j<G.V();j++)
            if(G.edge(j,v))return G.edge(j,v);
        return 0;
    }
    bool end()const{return(i >= G.V()&& j >= G.V());}
};

template <class Graph,class Edge> 
vector<Edge*> edges(const Graph &G)
{
    int E=0;
    vector<Edge *>a(G.E());
    for(int v=0;v<G.V();v++){
        adjIterator<EDGE> A(G,v);
	    for(Edge*e=A.beg();!A.end();e=A.nxt())
            if(e->from(v))a[E++]=e;
    }
    return a;
}

template <class Graph,class Edge> class MAXFLOW
{
    const Graph &G;
    int s,t,maxf;
    vector<int> wt;
    vector<Edge *> st;
    int ST(int v)const{return st[v]->other(v);}

    void augment(int s,int t)
    {
        int d=st[t]->capRto(t);
        for(int v=ST(t);v!=s;v=ST(v))
            if(st[v]->capRto(v)<d) d=st[v]->capRto(v);
        st[t]->addflowRto(t,d);
	    maxf+=d;
        for(int v=ST(t);v!=s;v=ST(v))
            st[v]->addflowRto(v,d);
    }

    bool pfs();

public:
        MAXFLOW(const Graph &G,int s,int t,int &maxflow): 
           G(G),s(s),t(t),st(G.V()),wt(G.V()),maxf(0)
        {
            while(pfs())augment(s,t);
            maxflow+=maxf;
        }
};
 
template <class Graph,class Edge>
bool MAXFLOW<Graph,Edge>::pfs()
{
    PQ<int> pQ(G.V(),wt);
    for(int v=0;v<G.V();v++){
	    wt[v]=0;st[v]=0;pQ.insert(v);
	}
    wt[s]=M;pQ.change(s);
    while(!pQ.empty()){
        int v=pQ.deletemax();wt[v]=M;
        if(v==t||(v!=s && st[v]==0))break;
        adjIterator<Edge> A(G,v);
        for(Edge* e=A.beg();!A.end();e=A.nxt()){
            int w=e->other(v);
            int cap=e->capRto(w);
            int P=cap<wt[v] ?cap:wt[v];
            if(cap>0 && P>wt[w]){
			    wt[w]=P;pQ.change(w);st[w]=e;
			}
        }
    }
    return st[t]!=0;
}

const int wtM=5555500;

template <class Graph,class Edge> class MAXFLOW1
{
    const Graph &G;
    int s,t;
    vector<int> h,wt,st;
    GQ<int> gQ;

    void initheights()
    {
	    h[s]=G.V();
    }

    void push(Edge* e,int v,int w,int f)
    {
        e->addflowRto(w,f);
        wt[v] -= f;wt[w]+=f;
    }

    void relabel(int v)
    {
        if(v!=s && v!=t && wt[v]>0){
            int hv=INT_MAX;
		    adjIterator<Edge> A(G,v);
            for(Edge* e=A.beg();!A.end();e=A.nxt()){
		        int w=e->other(v);
                if( e->residual(v)&& h[w]<hv)hv=h[w];
		    }
		    if(hv<INT_MAX && hv>=h[v]){
		    	h[v]=hv+1;
		        gQ.put(v);st[v]=1;
			}
	    }
    }

    void discharge(int v)
    {
        adjIterator<Edge> A(G,v);
        for(Edge* e=A.beg();!A.end();e=A.nxt()){
		    int w=e->other(v);
            int cap=e->capRto(w);
            int P=cap<wt[v] ?cap:wt[v];
            if(P>0 &&(v==s || h[v]==h[w]+1)){
		        push(e,v,w,P);
                if((w!=s)&&(w!=t)&&(!st[w])){
			        gQ.put(w);st[w]=1;
			    }
            }
        } 
    }

    void wtmax()
    {
	    adjIterator<Edge> A(G,s);
        for(Edge* e=A.beg();!A.end();e=A.nxt())
		    if(e->from(s))wt[s]+=e->cap();
		if(wt[s]<0 || wt[s]>wtM)wt[s]=wtM;
    }

    void heights()
    {
        Queue<int> queue(G.V());
        for(int i=0;i<G.V();i ++ )h[i]=0;
	    queue.put(t);
        // 广度优先搜索
        while(!queue.empty()){
            int v=queue.get();
            // 搜索与顶点v相连的边
	        adjIterator<Edge> A(G,v);
            for(Edge* e=A.beg();!A.end();e=A.nxt()){
		        int w=e->other(v);
                if( h[w]==0 && e->residual(w)){
			        h[w]= h[v]+1;queue.put(w);
			    }
	        } 
	    } 
	    h[s]=G.V();
    }
    
public:
    MAXFLOW1(Graph &G,int s,int t,int &maxflow): 
        G(G),s(s),t(t),h(G.V(),0),wt(G.V(),0),st(G.V(),0), gQ(G.V())
    {
	    heights();
		wtmax();
        gQ.put(s);st[s]=1;
        while(!gQ.empty()){
	        int v=gQ.get();
	        st[v]=0;
            discharge(v);
            relabel(v);
		}
	    maxflow+=wt[t];
    }
};

template <class Graph,class Edge> class FEASIBLE
{const Graph &G;
public:
    FEASIBLE(const Graph &G,vector<int> sd): G(G)
    {
        int maxflow,ss,dd,supply,demand;
	    Graph F(G.V()+2,1);
        for(int v=0;v<G.V();v++){
            adjIterator<Edge> A(G,v);
            for(Edge* e=A.beg();!A.end();e=A.nxt())
                F.insert(e);
        }    
        int s=G.V(),t=G.V()+1;
	    supply=0;demand=0;
        for(int i=0;i<G.V();i++)
		    if(sd[i]>=0){
                supply+=sd[i];
			    F.insert(new EDGE(s,i,sd[i]));
		    }
		    else{
			    demand-=sd[i];
                F.insert(new EDGE(i,t,-sd[i]));
		    }
        MAXFLOW<Graph,Edge>(F,s,t,maxflow);
	    F.checksd(s,t,ss,dd);
	    if(supply==ss)cout<<"supply ok"<<endl;
	    else cout<<"supply not enough"<<endl;
	    if(demand==dd)cout<<"demand met"<<endl;
	    else cout<<"demand not met"<<endl;
	    F.outflow();
    }
};

template <class Graph,class Edge> class BMATCHING
{
    const Graph &G;
public:
    BMATCHING(const Graph &G,int N1):G(G)
    {
        int s,t,maxflow;
	    Graph F(G.V()+2,1);
        for(int v=0;v<G.V();v++){
            adjIterator<Edge> A(G,v);
            for(Edge* e=A.beg();!A.end();e=A.nxt())
            F.insert(e);
        }
	    s=G.V();t=G.V()+1;
        for(int i=0;i<N1;i++)
            F.insert(new EDGE(s,i,1));
        for(int i=N1;i<s;i++)
            F.insert(new EDGE(i,t,1));
        MAXFLOW<Graph,Edge>(F,s,t,maxflow);
        cout<<maxflow<<endl;
        for(int i=0;i<N1;i++){
            adjIterator<Edge> A(F,i);
            for(EDGE* e=A.beg();!A.end();e=A.nxt())
                if(e->flow()== 1 &&  e->from(i)&& e->capRto(i)==1 )
                    cout<<e->v()+1<<" "<<e->w()+1<<endl;
	    }
    }
};

template <class Graph,class Edge> class LOWER
{
    const Graph &G;
    bool feasible(Graph &G,int s,int t,vector<int> sd)
    {
        int ss,dd,supply,demand,maxflow=0;
	    Graph F(G.V()+2,1);
        for(int v=0;v<G.V();v++){
            adjIterator<Edge> A(G,v);
            for(Edge* e=A.beg();!A.end();e=A.nxt())
		        if(e->from(v)){
				    e->sublow();F.insert(e);
				}
        }  
	    F.insert(new EDGE(t,s,INT_MAX));
	    s=G.V();t=G.V()+1;
	    supply=0;demand=0;
        for(int i=0;i<G.V();i++)
		    if(sd[i]>=0){
                supply+=sd[i];
			    F.insert(new EDGE(s,i,sd[i]));
		    }
		    else{
			    demand-=sd[i];
                F.insert(new EDGE(i,t,-sd[i]));
		    }
        MAXFLOW<Graph,Edge>(F,s,t,maxflow);
	    F.checksd(s,t,ss,dd);
	    bool ret=(supply==ss) && (demand==dd);
        for(int v=0;v<G.V();v++){
            adjIterator<Edge> A(G,v);
            for(Edge* e=A.beg();!A.end();e=A.nxt())
		        if(e->from(v))e->addlow();
        }
        return ret;
    }
public:
    LOWER(Graph &G,int s,int t,vector<int> sd):G(G)
    {
        int maxflow=0;
	    if(!feasible(G,s,t,sd)){
	    	cout<<-1<<endl;
	    	return;
		}
        adjIterator<Edge> A(G,s);
        for(Edge* e=A.beg();!A.end();e=A.nxt())
	        if(e->from(s))maxflow+=e->flow();
        MAXFLOW<Graph,Edge>(G,s,t,maxflow);
        cout<<"Maxflow="<<maxflow<<endl;
        G.outflow();
    }
};

template <class Graph,class Edge> class LOWERm
{
    const Graph &G;
    bool feasible(Graph &G,int s,int t,vector<int> sd)
    {
        int ss,dd,supply,demand,maxflow=0;
	    Graph F(G.V()+2,1);
        for(int v=0;v<G.V();v++){
            adjIterator<Edge> A(G,v);
            for(Edge* e=A.beg();!A.end();e=A.nxt())
		        if(e->from(v)){
				    e->sublow();F.insert(e);
				}
        }
	    F.insert(new EDGE(t,s,INT_MAX));
	    s=G.V();t=G.V()+1;
	    supply=0;demand=0;
        for(int i=0;i<G.V();i++)
		    if(sd[i]>=0){
                supply+=sd[i];
			    F.insert(new EDGE(s,i,sd[i]));
		    }
		    else{
			    demand-=sd[i];
                F.insert(new EDGE(i,t,-sd[i]));
		    }
        MAXFLOW<Graph,Edge>(F,s,t,maxflow);
	    F.checksd(s,t,ss,dd);
	    bool ret=(supply==ss) && (demand==dd);
        for(int v=0;v<G.V();v++){
            adjIterator<Edge> A(G,v);
            for(Edge* e=A.beg();!A.end();e=A.nxt())
		        if(e->from(v))e->addlow();
        }
        return ret;
    }
public:
    LOWERm(Graph &G,int s,int t,vector<int> sd):G(G)
    {
        int maxflow=0;
	    if(!feasible(G,s,t,sd)){
	    	cout<<-1<<endl;
	    	return;
		}
        adjIterator<Edge> A(G,s);
        for(Edge* e=A.beg();!A.end();e=A.nxt())
	        if(e->from(s))maxflow-=e->flow();
        MAXFLOW<Graph,Edge>(G,t,s,maxflow);
        cout<<-maxflow<<endl;
        G.outflow();
    }
};

template <class Graph,class Edge>
static int cost(Graph &G)
{
    int x=0;
    for(int v=0;v<G.V();v++){
        adjIterator<Edge> A(G,v);
        for(Edge* e=A.beg();!A.end();e=A.nxt())
		    if(e->from(v)&& e->costRto(e->w())<INT_MAX)
                x+=e->flow()*e->costRto(e->w());
    }
    return x;
}

template <class Graph,class Edge> class MINCOST
{ 
    Graph &G;
    int s,t;
    vector<int> wt;
    vector <Edge *> st;
  
    int ST(int v)const { 
	    if(st[v]==0){cout<<"error!"<<endl;return 0;}
        else return st[v]->other(v);
	}

    void augment(int s,int t)
    { 
	    int d=st[t]->capRto(t);
	    for(int v=ST(t);v!=s;v=ST(v))
            if(st[v]->capRto(v)<d)d=st[v]->capRto(v);
        st[t]->addflowRto(t,d);
        for( int v=ST(t);v!=s;v=ST(v))st[v]->addflowRto(v,d);
    }

    int negcyc()
	{
	    for(int i=0;i<G.V();i++){
		    int neg=negcyc(i);
			if(neg>=0)return neg;
	    }
	    return -1;
    }

    int negcyc(int ss)
	{
        st.assign(G.V(),0);wt.assign(G.V(),INT_MAX);
        Queue<int> Q(2*G.V()+515);int N=0;
		wt[ss]=0.0;
        Q.put(ss);Q.put(G.V());
        while(!Q.empty()){ 
	        int v;
		    while((v=Q.get())== G.V()){ 
			    if(N++ > G.V())return -1;
			    Q.put(G.V());
		    }
		    adjIterator<Edge> A(G,v);
            for(Edge* e=A.beg();!A.end();e=A.nxt()){
		        int w=e->other(v);
			    if(e->capRto(w)==0 )continue;
			    double P=wt[v]+e->wt(w);
			    if(P<wt[w]){ 
			        wt[w]=P;
				    // 开始搜索负费用圈
					for( int node_test=v;(st[node_test]!=0 && node_test!=ss);node_test=ST(node_test)){ 
				        if( ST(node_test)== w ){
					        st[w]=e;
						    return w;
				        }
			        }
				    st[w]=e;Q.put(w);
			    }
		    }
	    }
        return -1;
    }

public:
    MINCOST(Graph &G,int s,int t)
        : G(G),s(s),t(t),st(G.V()),wt(G.V())
    { 
	    int flow=0;
		MAXFLOW<Graph,Edge>(G,s,t,flow);
        for(int x=negcyc();x!=-1;x=negcyc())augment(x,x);
    }
};

template <class Graph,class Edge> class MINCOST1
{ 
    Graph &G;
    int s,t,flow;
    vector<int> wt;
    vector<Edge*> st;

    int ST(int v)const { 
	    if(st[v]==0){cout<<"error!"<<endl;return 0;}
        else return st[v]->other(v);
	}

    void augment(int s,int t)
    {    
	    int d=st[t]->capRto(t);
	    for(int v=ST(t);v!=s;v=ST(v))
            if(st[v]->capRto(v)<d)d=st[v]->capRto(v);
        if(d>flow)d=flow;
        st[t]->addflowRto(t,d);
        for(int v=ST(t);v!=s;v=ST(v))st[v]->addflowRto(v,d);
	    flow-=d;
    }
	
	bool shortest()
    {
        st.assign(G.V(),0);wt.assign(G.V(),INT_MAX);
        Queue<int> Q(2*G.V()+215);int N=0;
	    if(flow<=0)return false;
        wt[s]=0;
        Q.put(s);Q.put(G.V());

        while(!Q.empty()){ 
		    int v;
            while((v=Q.get())==G.V()){ 
			    if(N++>G.V())return(wt[t]<INT_MAX);
			    Q.put(G.V());
		    }
            adjIterator<Edge> A(G,v);
            for(Edge* e=A.beg();!A.end();e=A.nxt()){
			    int w=e->other(v);
			    if(e->capRto(w)==0)continue;
                int P=wt[v]+e->wt(w);
                if(P<wt[w]){ 
			        wt[w]=P;
			        st[w]=e;Q.put(w);
		        }
		    }
	    }
        return(wt[t]<INT_MAX);
    }

public:
    MINCOST1(Graph &G,int s,int t): 
	    G(G),s(s),t(t),flow(SE),st(G.V()),wt(G.V())
    { 
	    while(shortest())augment(s,t);
    }
};

template <class Graph,class Edge> class MINCOST2
{
	const Graph &G;int s,t;int valid;
    vector<Edge *> st;vector<int> mark,phi;

    void upbound(int &cap,int &cost)
	{
        cap=0;cost=0;
		for(int i=0;i<G.V();i++)
			for(int j=0;j<G.V();j++){
				if(G.edge(i,j)&& cap<G.edge(i,j)->cap())cap=G.edge(i,j)->cap();
				if(G.edge(i,j)&& cost<G.edge(i,j)->cost())cost=G.edge(i,j)->cost();
			}
	}

    void dfsR(Edge *e,int w)
    {
	    int v=e->other(w);
	    st[v]=e;
	    mark[v]=1;mark[w]=1;
	    dfs(v);dfs(w);
	    mark.assign(G.V(),-1);
    }

    // 从顶点v开始做深度优先搜索
	void dfs(int v)
    {
        adjIterator<Edge> A(G,v);
        for(Edge* e=A.beg();!A.end();e=A.nxt()){
		    int w=e->other(v);
		    if(mark[w]==-1){st[w]=e;mark[w]=1;dfs(w);}
	   }
    }

    int ST(int v)const{
	    if(st[v]==0)return 0;
        else return st[v]->other(v);
    }

    int phiR(int v)
    {
        if(mark[v]==valid)return phi[v];
        phi[v]=phiR(ST(v))- st[v]->costRto(v);
        mark[v]=valid;
        return phi[v];
    }

    int lca(int v,int w)
    {
	    mark[v]=++valid;mark[w]=valid;
        while(v!=w){
            if(v!=t)v=ST(v);
            if(v!=t && mark[v]==valid)return v;
            mark[v]=valid;
            if(w!=t)w=ST(w);
            if(w!=t && mark[w]==valid)return w;
            mark[w]=valid;
        }
        return v;
    }

    bool onpath(int a,int b,int c)
    {
        for(int i=a;i!=c;i=ST(i))
            if(i==b)return true;
        return false;
    }
	
	void reverse(int u,int x)
    {
	    Edge *e=st[u];
        for(int i=ST(u);e->other(i)!= x;i=e->other(i))
	    {Edge *y=st[i];st[i]=e;e=y;} 
    }

    void update(Edge *w,Edge *y)
    {
	    if(w==y)return;
	    int u=y->w(),v=y->v(),x=w->w();
        if(x==t || st[x]!=w)x=w->v();
        int r=lca(u,v);
        if(onpath(u,x,r)){reverse(u,x);st[u]=y;return;}
        if(onpath(v,x,r)){reverse(v,x);st[v]=y;return;} 
    }

    int costR(Edge *e,int v)
    {
	    int R=e->cost()+ phi[e->w()]-phi[e->v()];
        return  e->from(v)? R : -R;
    }

    Edge *besteligible()
    {
	    Edge *x=0;
        for(int v=0,min=INT_MAX;v<G.V();v++){
		    adjIterator<Edge> A(G,v);
            for(Edge* e=A.beg();!A.end();e=A.nxt())
                if(e->capRto(e->other(v))> 0)
                    if(e->capRto(v)== 0)
                        if(costR(e,v)< min)
				          {x=e;min=costR(e,v);} 
	    }
        return x;
    }

    Edge *augment(Edge *x)
    {
	    int v=full(x)?x->w():x->v();// 负费用圈的方向
	    int w=x->other(v);
	    int r=lca(v,w);// 顶点v和w的最近公共祖先
        int d=x->capRto(w);
        for(int u=w;u!=r;u=ST(u))
            if(st[u]->capRto(ST(u))< d)
                d=st[u]->capRto(ST(u));
        for(int u=v;u!=r;u=ST(u))
            if(st[u]->capRto(u)< d)
                d=st[u]->capRto(u);
	    x->addflowRto(w,d);Edge* e=x;
        for(int u=w;u!=r;u=ST(u)){
		    st[u]->addflowRto(ST(u),d);
            if(st[u]->capRto(ST(u))== 0)e=st[u];
	    }
        for(int u=v;u!=r;u=ST(u)){
		    st[u]->addflowRto(u,d);
            if(st[u]->capRto(u)== 0)e=st[u];
	    }
        return e;
    }

    bool full(Edge *x)
    {
        return(x->capRto(x->w())==0);
    } 

    bool empty(Edge *x)
    {
        return(x->capRto(x->v())==0);
    } 

public:
    MINCOST2(Graph &G,int s,int t): 
      G(G),s(s),t(t),st(G.V()+1),mark(G.V()+1,-1),phi(G.V()+1)
    {
        int m,c,ss=s;
        G.expand();
	    upbound(m,c);
	    m=m*G.V();
	    c=c*G.V();
        s=G.V()-1;
		Edge *z=new EDGE(s,t,SE,c);
        G.insert(z);
        G.insert(new EDGE(s,ss,SE,0));
        z->addflowRto(t,SE);
        dfsR(z,t);
        for(valid=1;;valid++ ){
            phi[t]=z->costRto(s);
		    mark[t]=valid;
            for(int v=0;v<G.V();v++)
			    if(v!=t)phi[v]=phiR(v);
            Edge *x=besteligible();
            int rcost=costR(x,x->v());
		    if(full(x)&& rcost<=0||empty(x)&& rcost>=0)break;
            update(augment(x),x);
        }
        G.remove(z);delete z;
    }
};

template <class Graph,class Edge> class LOWERc
{ 
    const Graph &G;
	
	bool feasible(Graph &G,int s,int t,vector<int> sd)
    { 
        int ss,dd,supply,demand,maxflow=0;
		Graph F(G.V()+2,1);
		for(int v=0;v<G.V();v++){
            adjIterator<Edge> A(G,v);
            for(Edge* e=A.beg();!A.end();e=A.nxt())
		        if(e->from(v)){e->sublow();F.insert(e);}
        } 
		F.insert(new EDGE(t,s,INT_MAX,0));
		s=G.V();t=G.V()+1;
		supply=0;demand=0;
        for(int i=0;i<G.V();i++)
		    if(sd[i]>=0){
                supply+=sd[i];
				F.insert(new EDGE(s,i,sd[i],0));
		    }
		    else{
			    demand-=sd[i];
				F.insert(new EDGE(i,t,-sd[i],0));
		    }
        MAXFLOW<Graph,Edge>(F,s,t,maxflow);
	    F.checksd(s,t,ss,dd);
	    bool ret=(supply==ss) && (demand==dd);for(int v=0;v<G.V();v++){
            adjIterator<Edge> A(G,v);
            for(Edge* e=A.beg();!A.end();e=A.nxt())
		        if(e->from(v)) e->addlow();
        }
        return ret;
    }

public:
    LOWERc(Graph &G,int s,int t,vector<int> sd):G(G)
    { 
        int maxflow=0;
		if(!feasible(G,s,t,sd)){
	    	cout<<-1<<endl;
	    	return;
		}
        adjIterator<Edge> A(G,s);
        for(Edge* e=A.beg();!A.end();e=A.nxt())
	        if(e->from(s)) maxflow+=e->flow();
		MINCOST<GRAPH<EDGE>,EDGE>(G,s,t);
        maxflow=0;
        for(Edge* e=A.beg();!A.end();e=A.nxt())
	        if(e->from(s)) maxflow+=e->flow();
	    cout<<maxflow<<" "<<cost<GRAPH<EDGE>,EDGE>(G)<<endl;
    }
};

template <class Graph,class Edge> class LOWERc1
{ 
    const Graph &G;
	
	bool feasible(Graph &G,int s,int t,vector<int> sd)
    { 
        int ss,dd,supply,demand,maxflow=0;
		Graph F(G.V()+2,1);
		for(int v=0;v<G.V();v++){
            adjIterator<Edge> A(G,v);
            for(Edge* e=A.beg();!A.end();e=A.nxt())
		        if(e->from(v)){e->sublow();F.insert(e);}
        } 
		F.insert(new EDGE(t,s,INT_MAX,0));
		s=G.V();t=G.V()+1;
		supply=0;demand=0;
        for(int i=0;i<G.V();i++)
		    if(sd[i]>=0){
                supply+=sd[i];
				F.insert(new EDGE(s,i,sd[i],0));
		    }
		    else{
			    demand-=sd[i];
				F.insert(new EDGE(i,t,-sd[i],0));
		    }
        MAXFLOW<Graph,Edge>(F,s,t,maxflow);
	    F.checksd(s,t,ss,dd);
	    bool ret=(supply==ss) && (demand==dd);for(int v=0;v<G.V();v++){
            adjIterator<Edge> A(G,v);
            for(Edge* e=A.beg();!A.end();e=A.nxt())
		        if(e->from(v)) e->addlow();
        }
        return ret;
    }

public:
    LOWERc1(Graph &G,int s,int t,vector<int> sd):G(G)
    { 
        int maxflow=0;
		if(!feasible(G,s,t,sd)){
	    	cout<<-1<<endl;
	    	return;
		}
        adjIterator<Edge> A(G,s);
        for(Edge* e=A.beg();!A.end();e=A.nxt())
	        if(e->from(s)) maxflow-=e->flow();
		MINCOST<GRAPH<EDGE>,EDGE>(G,t,s);
        maxflow=0;
        for(Edge* e=A.beg();!A.end();e=A.nxt())
	        if(e->from(s)) maxflow+=e->flow();
	    cout<<maxflow<<" "<<cost<GRAPH<EDGE>,EDGE>(G)<<endl;
    }
};

template <class Graph,class Edge> class ASSIGNMENT
{ 
    Graph &G;
public:
    ASSIGNMENT(Graph &G):G(G)
    { 
        int s=G.V(),t=G.V()+1,n=s/2;
	    Graph F(G.V()+2,1);
		for (int v=0;v<G.V();v++){
            adjIterator<Edge>A(G,v);
            for (Edge* e=A.beg();!A.end();e=A.nxt())
                F.insert(e);
        }
		for(int i=0;i<n;i++)F.insert(new EDGE(s,i,1,0));
		for(int i=n;i<s;i++)F.insert(new EDGE(i,t,1,0));
		MINCOST<Graph,Edge>(F,s,t);
        int maxf=0;
        adjIterator<Edge> A(F,s);
        for(EDGE* e=A.beg();!A.end();e=A.nxt())
	        if(e->from(s)) maxf+=e->flow();
	    cout<<maxf<<" "<<cost<GRAPH<Edge>,Edge>(G)<<endl;
    }
};

template <class Graph,class Edge> 
class ConsecLP 
{
    Graph &G;
public:
        ConsecLP(Graph &G,int s,int t):G(G)
	    {
	    	MINCOST<Graph,Edge>(G,s,t);
            int maxf=0;
            adjIterator<Edge> A(G,s);
            for(EDGE* e=A.beg();!A.end();e=A.nxt())
	            if(e->from(s)) maxf+=e->flow();
	        cout<<cost<GRAPH<Edge>,Edge>(G)<<endl;
	    }
};

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

int main() 
{
	return 0;
}
