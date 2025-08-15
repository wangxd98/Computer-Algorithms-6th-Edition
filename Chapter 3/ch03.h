#include "2darray.h"

#define maxn 300
#define INF 0x7fffffff

void error(string ee)
{// not
	cout<<"error"<<endl;
}

template<class Type >
inline void Swap(Type & a,Type & b)
{
    Type temp=a;
    a=b;b=temp;
}

int *p,**s;

void matrixMultiply(int **a,int **b,int **c,int ra,int ca,int rb,int cb)
{
    if(ca!=rb)error("矩阵不可乘");
    for(int i=0;i<ra;i++)
        for(int j=0;j<cb;j++){
            int sum=a[i][0]*b[0][j];
            for(int k=1;k<ca;k++)
                sum+=a[i][k]*b[k][j];
            c[i][j]=sum;
        }
}
 
void MatrixChain(int *p,int n,int **m,int **s)
{
    for(int i=1;i<=n;i++)m[i][i]=0,s[i][i]=0;
    for(int r=2;r<=n;r++)
        for(int i=1;i<=n-r+1;i++){
            int j=i+r-1;
            m[i][j]=m[i+1][j]+p[i-1]*p[i]*p[j];
            s[i][j]=i;
            for(int k=i+1;k<j;k++){
                int t=m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j];
                if(t<m[i][j]){m[i][j]=t;s[i][j]=k;}
            }
        }
}
 
void Traceback(int i,int j,int **s)
{
    if(i==j)return;
    Traceback(i,s[i][j],s);
    Traceback(s[i][j]+1,j,s);
    cout<<"Multiply m "<<i<<","<<s[i][j];
    cout<<" and m "<<(s[i][j]+1)<<","<<j<<endl;
}
 
int RecurMatrixChain(int i,int j)
{
    if(i==j)return 0;
    int u=RecurMatrixChain(i,i)+RecurMatrixChain(i+1,j)+p[i-1]*p[i]*p[j];
    s[i][j]=i;
    for(int k=i+1;k<j;k++){
        int t=RecurMatrixChain(i,k)+RecurMatrixChain(k+1,j)+p[i-1]*p[k]*p[j];
        if(t<u){u=t;s[i][j]=k;}
    }
    return u;
}

int LookupChain(int i,int j,int **m)
{
    if(m[i][j]>0)return m[i][j];
    if(i==j)return 0;
    int u=LookupChain(i,i,m)+LookupChain(i+1,j,m)+p[i-1]*p[i]*p[j];
    s[i][j]=i;
    for(int k=i+1;k<j;k++){
        int t=LookupChain(i,k,m)+LookupChain(k+1,j,m)+p[i-1]*p[k]*p[j];
        if(t<u){u=t;s[i][j]=k;}
    }
    m[i][j]=u;
    return u;
}

int MemoizedMatrixChain(int n,int **m,int **s)
{
    for(int i=1;i<=n;i++)
        for(int j=i;j<=n;j++)m[i][j]=0;
    return LookupChain(1,n,m);
}

void LCSLength(int m,int n,char *x,char *y,int **c,int **b)
{ 
    int i,j;
    for(i=1;i<=m;i++)c[i][0]=0;
    for(i=1;i<=n;i++)c[0][i]=0;
    for(i=1;i<=m;i++)
        for(j=1;j<=n;j++){
            if(x[i]==y[j]){c[i][j]=c[i-1][j-1]+1;b[i][j]=1;}
            else if(c[i-1][j]>=c[i][j-1]){c[i][j]=c[i-1][j];b[i][j]=2;}
            else {c[i][j]=c[i][j-1];b[i][j]=3;}
        }
}
 
void LCS(int i,int j,char *x,int **b)
{
    if(i==0 || j==0)return;
    if(b[i][j]==1){LCS(i-1,j-1,x,b);cout<<x[i];}
    else if(b[i][j]==2)LCS(i-1,j,x,b);
    else LCS(i,j-1,x,b);
}

//int MaxSum(int n,int *a,int& besti,int& bestj)
int MaxSum0(int n,int *a,int& besti,int& bestj)
{
    int sum=0;
    for(int i=1;i<=n;i++)
        for(int j=i;j<=n;j++){
            int thissum=0;
            for(int k=i;k<=j;k++)thissum+=a[k];
            if(thissum>sum){
                sum=thissum;
                besti=i;
                bestj=j;
            }
        }
    return sum;
}
 
//int MaxSum(int n,int *a,int& besti,int& bestj)
int MaxSum1(int n,int *a,int& besti,int& bestj)
{
    int sum=0;
    for(int i=1;i<=n;i++){
        int thissum=0;
        for(int j=i;j<=n;j++){
            thissum+=a[j];
            if(thissum>sum){
                sum=thissum;
                besti=i;
                bestj=j;
            }
        }
    }
    return sum;
}
 
int MaxSubSum(int *a,int left,int right)
{
    int sum=0;
    if(left==right)sum=a[left]>0?a[left]:0;
    else {
        int center=(left+right)/2;
        int leftsum=MaxSubSum(a,left,center);
        int rightsum=MaxSubSum(a,center+1,right);
        int s1=0;
        int lefts=0;
        for(int i=center;i>=left;i--){
            lefts+=a[i];
            if(lefts>s1)s1=lefts;
        }
        int s2=0;
        int rights=0;
        for(int i=center+1;i<=right;i++){
            rights+=a[i];
            if(rights>s2)s2=rights;
        }
        sum=s1+s2;
        if(sum<leftsum)sum=leftsum;
        if(sum<rightsum)sum=rightsum;
    }
    return sum;
}

//int MaxSum(int n,int *a)
int MaxSum2(int n,int *a)
{
    return MaxSubSum(a,1,n);
}

//int MaxSum(int n,int *a)
int MaxSum3(int n,int *a)
{
    int sum=0,b=0;
    for(int i=1;i<=n;i++){
        if(b>0)b+=a[i];
        else b=a[i];
        if(b>sum)sum=b;
    }
    return sum;
}
 
//int MaxSum2(int m,int n,int **a)
int MaxSum21(int m,int n,int **a)
{
    int sum=0;
    int *b=new int [n+1];
    for(int i=1;i<=m;i++){
        for(int k=1;k<=n;k++)b[k]=0;
        for(int j=i;j<=m;j++){
            for(int k=1;k<=n;k++)b[k]+=a[j][k];
            //int max=MaxSum(n,b);
            int max=MaxSum2(n,b);
            if(max>sum)sum=max;
        }
    }
    return sum;
}
 
//int MaxSum(int m,int n,int *a)
int MaxSum4(int m,int n,int *a)
{
    if(n<m || m<1)return 0;
    int **b=new int * [m+1];
    for(int i=0;i<=m;i++)b[i]=new int [n+1];
    for(int i=0;i<=m;i++)b[i][0]=0;
    for(int j=1;j<=n;j++)b[0][j]=0;
    for(int i=1;i<=m;i++)
        for(int j=i;j<=n-m+i;j++)
            if(j>i){
                b[i][j]=b[i][j-1]+a[j];
                for(int k=i-1;k<j;k++)
                    if(b[i][j]<b[i-1][k]+a[j])b[i][j]=b[i-1][k]+a[j];
            }
            else b[i][j]=b[i-1][j-1]+a[j];
    int sum=0;
    for(int j=m;j<=n;j++)
        if(sum<b[m][j])sum=b[m][j];
    return sum;
}
 
//int MaxSum(int m,int n,int *a)
int MaxSum5(int m,int n,int *a)
{
    if(n<m || m<1)return 0;
    int *b=new int [n+1];
    int *c=new int [n+1];
    for(int i=0;i<=n;i++)b[i]=c[i]=0;
    for(int i=1;i<=m;i++){
        b[i]=b[i-1]+a[i];
        c[i-1]=b[i];
        int max=b[i];
        for(int j=i+1;j<=i+n-m;j++){
            b[j]=b[j-1]>c[j-1]?b[j-1]+a[j]:c[j-1]+a[j];
            c[j-1]=max;
            if(max<b[j])max=b[j];
        }
        c[i+n-m]=max;
    }
    int sum=0;
    for(int j=m;j<=n;j++)
        if(sum<b[j])sum=b[j];
    delete []c;delete []b;
    return sum;
}

double len[100][100];

double w(int i,int j,int k)
{
	return len[i][j]+len[i][k]+len[j][k];
}

template<class Type>
void MinWeightTriangulation(int n,Type **t,int **s)
{
    for(int i=1;i<=n;i++)t[i][i]=0;
    for(int r=2;r<=n;r++)
        for(int i=1;i<=n-r+1;i++){
            int j=i+r-1;
            t[i][j]=t[i+1][j]+w(i-1,i,j);
            s[i][j]=i;
            for(int k=i+1;k<j;k++){
                Type u=t[i][k]+t[k+1][j]+w(i-1,k,j);
                if(u<t[i][j]){t[i][j]=u;s[i][j]=k;}
            }
        }
}

void Tback(int i,int j,int **s)
{
	if(i==j) return;
	Tback(i,s[i][j],s);
	Tback(s[i][j]+1,j,s);
	cout<<i-1<<" "<<s[i][j]<<" "<<j<<" :w="<<w(i-1,s[i][j],j)<<endl;
}

int m[maxn+1][maxn+1][2];
int v[maxn+1];
char op[maxn+1];

void MinMax(int n,int i,int s,int j,int& minf,int& maxf)
{
    int e[5];
    int a=m[i][s][0],b=m[i][s][1],r=(i+s-1)%n+1,c=m[r][j-s][0],d=m[r][j-s][1];
    if(op[r]=='t'){minf=a+c;maxf=b+d;}
    else {
        e[1]=a*c;e[2]=a*d;e[3]=b*c;e[4]=b*d;
        minf=e[1];maxf=e[1];
        for(int r=2;r<5;r++){
            if(minf>e[r])minf=e[r];
            if(maxf<e[r])maxf=e[r];
        }
    }
}

int PolyMax(int n)
{
    int minf,maxf;
    for(int j=2;j<=n;j++)
        for(int i=1;i<=n;i++){
        	m[i][j][0]=INF,m[i][j][1]=-INF;
            for(int s=1;s<j;s++){
                MinMax(n,i,s,j,minf,maxf);
                if(m[i][j][0]>minf)m[i][j][0]=minf;
                if(m[i][j][1]<maxf)m[i][j][1]=maxf;
            }
		}
    int temp= m[1][n][1];
    for(int i=2;i<=n;i++)
        if(temp<m[i][n][1])temp=m[i][n][1];
    return temp;
}
 
int length(int i)
{
    int k=1;i=i/2;
    while(i>0){k++;i=i/2;}
    return k;
}
 
void Compress(int n,int p[],int s[],int l[],int b[])
{
    int Lmax=256,header=11;
    s[0]=0;
    for(int i=1;i<=n;i++){
        b[i]=length(p[i]);
        int bmax=b[i];
        s[i]=s[i-1]+bmax;
        l[i]=1;
        for(int j=2;j<=i && j<=Lmax;j++){
            if(bmax<b[i-j+1])bmax=b[i-j+1];
            if(s[i]>s[i-j]+j* bmax){
                s[i]=s[i-j]+j * bmax;
                l[i]=j;
            }
        }
        s[i]+= header;
    }
}

void Traceback(int n,int& i,int s[],int l[])
{
    if(n==0)return;
    Traceback(n-l[n],i,s,l);
    s[i++]=n-l[n] ;
}

void Output(int s[],int l[],int b[],int n)
{
    cout<<"The optimal value is "<<s[n]<<endl;
    int m=0;
    Traceback(n,m,s,l);
    s[m]=n;
    cout<<"Decompose into "<<m<<" segments "<<endl;
    for(int j=1;j<=m;j++){l[j]=l[s[j]];b[j]=b[s[j]];}
    for(int j=1;j<=m;j++)
        cout<<l[j]<<' '<<b[j]<<endl;
}
 
void MNS(int C[],int n,int **size)
{
    for(int j=0;j<C[1];j++)size[1][j]=0;
    for(int j=C[1];j<=n;j++)size[1][j]=1;
    for(int i=2;i<n;i++){
        for(int j=0;j<C[i];j++)size[i][j]=size[i-1][j];
        for(int j=C[i];j<=n;j++)
            size[i][j]=max(size[i-1][j],size[i-1][C[i]-1]+1);
    }
    size[n][n]=max(size[n-1][n],size[n-1][C[n]-1]+1);
}

void Traceback(int C[],int **size,int n,int Net[],int& m)
{
    int j=n;
    m=0;
    for(int i=n;i>1;i--)
        if(size[i][j]!=size[i-1][j]){Net[m++]=i;j=C[i]-1;}
    if(j>=C[1])Net[m++]=1;
}

template<class Type>
void sort(Type a[],int n)
{
	std::sort(a,a+n);
}

class  Jobtype{
public:
    operator int()const {return key;}
    int key,index;
    bool job;
};

int FlowShop(int n,int *a,int *b,int *c)
{
    Jobtype *d=new Jobtype [n];
    for(int i=0;i<n;i++){
        d[i].key=a[i]>b[i]?b[i]:a[i];
        d[i].job=a[i]<=b[i];
        d[i].index=i;
    }
    sort(d,n);
    int j=0,k=n-1;
    for(int i=0;i<n;i++){
        if(d[i].job)c[j++]=d[i].index;
        else c[k--]=d[i].index;
    }
    j=a[c[0]];
    k=j+b[c[0]];
    for(int i=1;i<n;i++){
        j+=a[c[i]];
        k=j<k?k+b[c[i]]:j+b[c[i]];
    }
    delete []d;
    return k;
}

template<class Type>
void Knapsack(Type *v,int *w,int c,int n,Type** m)
{
    int jMax=min(w[n]-1,c);
    for(int j=0;j<=jMax;j++)m[n][j]=0;
    for(int j=w[n];j<=c;j++)m[n][j]=v[n];
	for(int i=n-1;i>1;i--){
        jMax=min(w[i]-1,c);
        for(int j=0;j<=jMax;j++)m[i][j]=m[i+1][j];
        for(int j=w[i];j<=c;j++)m[i][j]=max(m[i+1][j],m[i+1][j-w[i]]+v[i]);
    }
    m[1][c]=m[2][c];
    if(c>=w[1])m[1][c]=max(m[1][c],m[2][c-w[1]]+v[1]);
}
 
template<class Type>
void Traceback(Type **m,int *w,int c,int n,int *x)
{
    for(int i=1;i<n;i++)
       if(m[i][c]==m[i+1][c])x[i]=0;
       else {x[i]=1;c-=w[i];}
    x[n] =(m[n][c])?1:0;
}

template<class Type>
void Traceback(int n,Type *w,Type *v,Type **p,int *head,int *x)
{
    Type j=p[head[0]-1][0],m=p[head[0]-1][1];
    for(int i=1;i<=n;i++){
        x[i]=0;
        for(int k=head[i+1];k<=head[i]-1;k++){
            if(p[k][0]+w[i]==j && p[k][1]+v[i]==m){
                x[i]=1;j=p[k][0];m=p[k][1];break;
            }
        }
    }
}

template<class Type>
Type Knapsack(int n,Type c,Type *v,Type *w,Type **p,int *x)
{
    int *head=new int [n+2];
    head[n+1]=0;p[0][0]=0;p[0][1]=0;
    int left=0,right=0,next=1;
    head[n]=1;
    for(int i=n;i>=1;i--){
        int k=left;
        for(int j=left;j<=right;j++){
            if(p[j][0]+w[i]>c)break;
            Type y=p[j][0]+w[i],m=p[j][1]+v[i];
            while(k<=right && p[k][0]<y){
                p[next][0]=p[k][0];
                p[next++][1]=p[k++][1];
            }
            if(k<=right && p[k][0]==y){
                if(m<p[k][1])m=p[k][1];
                k++;
            }
            if(m>p[next-1][1]){p[next][0]=y;p[next++][1]=m;}
            while(k<=right && p[k][1]<=p[next-1][1])k++;
        }
        while(k<=right){
            p[next][0]=p[k][0];
            p[next++][1]=p[k++][1];
        }
        left=right+1;right=next-1;head[i-1]=next;
    }
    Traceback(n,w,v,p,head,x);
    return p[next-1][1];
}

template<class Type>
void OptimalBinarySearchTree(Type *a,Type *b,int n,Type **m,int **s,Type **w)
{
    for(int i=0;i<=n;i++){w[i+1][i]=a[i];m[i+1][i]=0;}
    for(int r=0;r<n;r++)
        for(int i=1;i<=n-r;i++){
            int j=i+r;
            w[i][j]=w[i][j-1]+a[j]+b[j];
            m[i][j]=m[i+1][j];
            s[i][j]=i;
            for(int k=i+1;k<=j;k++){
                Type t=m[i][k-1]+m[k+1][j];
                if(t<m[i][j]){m[i][j]=t;s[i][j]=k;}
            }
            m[i][j]+=w[i][j];
        }
}

void Inorder(int **s,int i,int j)
{// 二叉搜索树中序列表
	int k=s[i][j];
	cout<<k<<" ";
	if(i<k)Inorder(s,i,k-1);
	if(k<j)Inorder(s,k+1,j);
}

template<class Type>
void OBST(Type *a,Type *b,int n,Type **m,int **s,Type **w)
{
    for(int i=0;i<=n;i++){w[i+1][i]=a[i];m[i+1][i]=0;s[i+1][i]=0;}
    for(int r=0;r<n;r++)
        for(int i=1;i<=n-r;i++){
            int j=i+r,i1=s[i][j-1]>i?s[i][j-1]:i,j1=s[i+1][j]>i?s[i+1][j]:j;
            w[i][j]=w[i][j-1]+a[j]+b[j];
            m[i][j]=m[i][i1-1]+m[i1+1][j];
            s[i][j]=i1;
            for(int k=i1+1;k<=j1;k++){
                Type t=m[i][k-1]+m[k+1][j];
                if(t<=m[i][j]){m[i][j]=t;s[i][j]=k;}
            }
            m[i][j]+=w[i][j];
        }
}

int weight(int i,int j)
{
    return i*j;
}

template<class Type>
void DynamicProgramming(int n,Type **m,int **s,Type **w)
{
    for(int i=1;i<=n;i++){m[i][i]=0;s[i][i]=0;}
    for(int r=1;r<n;r++)
        for(int i=1;i<=n-r;i++){
            int j=i+r;
            w[i][j]=weight(i,j);
            m[i][j]=m[i+1][j];
            s[i][j]=i;
            for(int k=i+1;k<j;k++){
                Type t=m[i][k]+m[k+1][j];
                if(t<=m[i][j]){m[i][j]=t;s[i][j]=k;}
            }
            m[i][j]+=w[i][j];
        }
}

template<class Type>
void SpeedDynamicProgramming(int n,Type **m,int **s,Type **w)
{
    for(int i=1;i<=n;i++){m[i][i]=0;s[i][i]=0;}
    for(int r=1;r<n;r++)
        for(int i=1;i<=n-r;i++){
            int j=i+r,i1=s[i][j-1]>i?s[i][j-1]:i,j1=s[i+1][j]>i?s[i+1][j]:j-1;
            w[i][j]=weight(i,j);
            m[i][j]=m[i][i1]+m[i1+1][j];
            s[i][j]=i1;
            for(int k=i1+1;k<=j1;k++){
                Type t=m[i][k]+m[k+1][j];
                if(t<=m[i][j]){m[i][j]=t;s[i][j]=k;}
            }
            m[i][j]+=w[i][j];
        }
}



