#include "2darray.h"

int factorial(int n)
{ 
    if(n==0)return 1;
    return n*factorial(n-1);
}

int fibonacci(int n)
{  
    if(n<=1)return 1;
    return fibonacci(n-1)+ fibonacci(n-2);
}

template<class Type >
inline void Swap(Type & a,Type & b)
{
    Type temp= a;
    a=b;b=temp;
}

template<class Type>
void Perm(Type list[],int k,int m)
{//  产生list[k:m]的所有排列
    if(k==m){// 只剩下1个元素
        for(int i=0;i<=m;i++)cout<<list[i]<<" ";
        cout<<endl;
    }
    else {// 还有多个元素待排列,递归产生排列
        for(int i=k;i<=m;i++){
            Swap(list[k],list[i]);
            Perm(list,k+1,m);
            Swap(list[k],list[i]);
        }
    }
}

int q(int n,int m)
{
    if((n<1)||(m<1))return 0;
    if((n==1)||(m==1))return 1;
    if(n<m)return q(n,n);
    if(n==m)return q(n,m-1)+1;
    return q(n,m-1)+q(n-m,m);
}

void move(int a,int b)
{
	cout<<a<<"->"<<b<<endl;
    a=b;
}

void hanoi(int n,int a,int b,int c)
{
    if(n>0){	 
        hanoi(n-1,a,c,b);
        move(a,b);
        hanoi(n-1,c,b,a);
    }
}

template<class Type>
int BinarySearch(Type a[],const Type& x,int n)
{   // 在a[0]<=a[1]<=...<=a[n-1]中搜索x
    // 找到x时返回其在数组中的位置，否则返回-1
    int left=0;int right=n-1;
    while(left<=right){
        int middle =(left+right)/2;
        if(x==a[middle])
        return middle;
        if(x>a[middle])left=middle+1;
        else right=middle-1;
    }
    return-1; // 未找到x
}

int tile=1;
int Board[8][8];

void ChessBoard(int tr,int tc,int dr,int dc,int size)
{
    if(size==1)return;
    int t=tile++, // L型骨牌号
    s=size/2;// 分割棋盘
    // 覆盖左上角子棋盘
    if(dr<tr+s && dc<tc+s) // 特殊方格在此棋盘中
        ChessBoard(tr,tc,dr,dc,s);
    else { // 此棋盘中无特殊方格
        Board[tr+s-1][tc+s-1]=t; // 用t号L型骨牌覆盖右下角
        ChessBoard(tr,tc,tr+s-1,tc+s-1,s); // 覆盖其余方格
    }   
    if(dr<tr+s&& dc>=tc+s) // 覆盖右上角子棋盘
        ChessBoard(tr,tc+s,dr,dc,s); // 特殊方格在此棋盘中
    else {// 此棋盘中无特殊方格
        Board[tr+s-1][tc+s]=t;// 用t号L型骨牌覆盖左下角
        ChessBoard(tr,tc+s,tr+s-1,tc+s,s);// 覆盖其余方格
    } 
    if(dr>=tr+s && dc<tc+s) // 覆盖左下角子棋盘
        ChessBoard(tr+s,tc,dr,dc,s); // 特殊方格在此棋盘中
    else { // 用t号L型骨牌覆盖右上角
        Board[tr+s][tc+s-1]=t;
        ChessBoard(tr+s,tc,tr+s,tc+s-1,s); // 覆盖其余方格
    }
    if(dr>=tr+s && dc>=tc+s) // 覆盖右下角子棋盘
        ChessBoard(tr+s,tc+s,dr,dc,s); // 特殊方格在此棋盘中
    else { // 用t号L型骨牌覆盖左上角
        Board[tr+s][tc+s]=t;
        ChessBoard(tr+s,tc+s,tr+s,tc+s,s); // 覆盖其余方格
    }
}

template<class Type>
void Merge(Type c[],Type d[],int l,int m,int r)
{ // 合并c[l:m]和c[m+1:r]到d[l:r]
    int i=l,j=m+1,k=l;
    while((i<=m)&&(j<=r))// 书中存在严重错误
        if(c[i]<=c[j])d[k++]=c[i++];
        else d[k++]=c[j++];
    if(i>m) for(int q=j;q<=r;q++)d[k++]=c[q];
    else for(int q=i;q<=m;q++)d[k++]=c[q];
}

template<class Type>
void MergePass(Type x[],Type y[],int s,int n)
{ // 合并大小为s的相邻子数组
    int i=0;
    while(i<=n-2*s){
        Merge(x,y,i,i+s-1,i+2*s-1); // 合并大小为s的相邻2段子数组
        i=i+2*s;
    }
    if(i+s<n)Merge(x,y,i,i+s-1,n-1); // 剩下的元素个数少于2s
    else for(int j=i;j<=n-1;j++)y[j]=x[j];
}

template<class Type>
void MergeSort(Type a[],int n)
{
    Type *b=new Type [n];
    int s=1;
    while(s<n){
        MergePass(a,b,s,n);	 // 合并到数组b
        s+=s;
        MergePass(b,a,s,n);	 // 合并到数组a
        s+=s;
    }
    delete b;
}

template<class Type>
int Partition(Type a[],int p,int r)
{
    int i=p,j=r+1;
    Type x=a[p];
    // 将小于x的元素交换到左边区域，将大于x的元素交换到右边区域
    while(true){
        while(a[++i]<x && i<r);
        while(a[--j]>x);
        if(i>=j)break;
        Swap(a[i],a[j]);
    }
    a[p]=a[j];a[j]=x;
    return j;
}

template<class Type>
void QuickSort(Type a[],int p,int r)
{
    if(p<r){
        int q=Partition(a,p,r);
        QuickSort(a,p,q-1);	 // 对左半段排序
        QuickSort(a,q+1,r);	 // 对右半段排序
    }
}

template<class Type>
void sort(Type a[],int p,int r)
{
	QuickSort(a,p,r);
}

int Random(int p,int r)
{
	return p+rand()%(r-p);
}

//函数参数合法性：0<=p<=r
template<class Type>
int RandomizedPartition(Type a[],int p,int r)
{
    int i=Random(p,r);
    Swap(a[i],a[p]);
    return Partition(a,p,r);
}

//函数参数合法性：0<=p<=r
template<class Type>
void RandomizedQuickSort(Type a[],int p,int r)
{	 
    if(p<r){
        int q=RandomizedPartition(a,p,r);
        RandomizedQuickSort(a,p,q-1); // 对左半段排序
        RandomizedQuickSort(a,q+1,r); // 对右半段排序
    }
}

//函数参数合法性：0<=p<=r,1<=k<=r-p+1
template<class Type>
Type RandomizedSelect(Type a[],int p,int r,int k)
{	 
    if(r-p<2){
    	if(a[r]<a[p])Swap(a[r],a[p]);
    	return a[p+k-1];
	}
    int i=RandomizedPartition(a,p,r),j=i-p+1;
    if(k<=j)return RandomizedSelect(a,p,i,k);
    else return RandomizedSelect(a,i+1,r,k-j);
}

template<class Type>
int Partition(Type a[],int l,int r,Type x)
{ 
    int i=l,j=r+1;
    // 将小于x的元素交换到左边区域，将大于x的元素交换到右边区域
    while(true){
        while(a[++i]<x && i<r);
        while(a[--j]>x);
        if(i>=j)break;
        Swap(a[i],a[j]);
    }
    a[l]=a[j];a[j]=x;
    return j;
}

template<class Type>
Type Select(Type a[],int l,int r,int k)
{	 
    if(r-l<75){  
        //用某个简单排序算法对数组a[l:r]排序;
        sort(a,l,r);
        int s=l+k-1;
        if(s>r)s=r;
        if(s<l)s=l;
        return a[s];//return a[l+k-1];
    }
    for(int i=0;i<=(r-l-4)/5;i++){
    	//将a[l+5*i]至a[l+5*i+4]的第3小元素与a[l+i]交换位置;
        int s=l+5*i;
        int t=s+4;
        sort(a,s,t);
        Swap(a[l+i],a[s+2]);
    }
    Type x=Select(a,l,l+(r-l-4)/5,(r-l+6)/10);
    int i=Partition(a,l,r,x);
    int j=i-l+1;
    if(j==k)return a[i];
    if(j>k)return Select(a,l,i-1,k);
    else return Select(a,i+1,r,k-j);
}

class PointX 
{
public:
    int operator<=(PointX a)const {
        return(x<=a.x);
    }
//private:
    int ID;	 // 点编号
    float x,y; // 点坐标
};

class PointY 
{
public:
    int operator<=(PointY a)const {
        return(y<=a.y);
    }
//private:
    int p;	 // 同一点在数组X中的坐标
    float x,y; // 点坐标
};

//平面上任意两点u和v之间的距离可计算如下：
template<class Type>
inline float dist(const Type& u,const Type& v)
{	 
    float dx=u.x-v.x;
    float dy=u.y-v.y;
    return sqrt(dx*dx+dy*dy);
}

//算法Cpair2中，具体计算最接近点对的工作由函数closest完成。
void closest(PointX X[],PointY Y[],PointY Z[],int l,int r,PointX& a,PointX& b,float& d)
{	
    if(r-l==1){	 // 2点的情形
        a=X[l];
        b=X[r];
        d=dist(X[l],X[r]);
        return;
    }
    if(r-l==2){	 // 3点的情形
        float d1=dist(X[l],X[l+1]);
        float d2=dist(X[l+1],X[r]);
        float d3=dist(X[l],X[r]);
        if(d1<=d2 && d1<=d3){
            a=X[l];
            b=X[l+1];
            d=d1;
            return;
        }
        if(d2<=d3){
            a=X[l+1];
            b=X[r];
            d=d2;
        }
        else { 
            a=X[l];
            b=X[r];
            d=d3;
        }
        return;
    }
    // 多于3点的情形，用分治法
    int m =(l+r)/2;
    int f=l,g=m+1;
    for(int i=l;i<=r;i++){
        if(Y[i].p>m)Z[g++]=Y[i];
        else Z[f++]=Y[i];
    }
    closest(X,Z,Y,l,m,a,b,d);
    float dr;
    PointX ar,br;
    closest(X,Z,Y,m+1,r,ar,br,dr);
    if(dr<d){
        a=ar;
        b=br;
        d=dr;
    }
    Merge(Z,Y,l,m,r); // 重构数组Y
    // d矩形条内的点置于Z中
    int k=l;
    for(int i=l;i<=r;i++){
        if(fabs(X[m].x-Y[i].x)<d)Z[k++]=Y[i];
    }
    for(int i=l;i<k;i++){  // 搜索Z[l:k-1]
        for(int j=i+1;j<k && Z[j].y-Z[i].y<d;j++){
            float dp=dist(Z[i],Z[j]);
            if(dp<d){
                d=dp;
                a=X[Z[i].p];
                b=X[Z[j].p];
            }
        }
    }
}

bool Cpair2(PointX X[],int n,PointX& a,PointX& b,float& d)
{	
    if(n<2)return false;
    MergeSort(X,n);
    PointY *Y=new PointY [n];
    for(int i=0;i<n;i++){ // 将数组X中的点复制到数组Y中
        Y[i].p=i;
        Y[i].x=X[i].x;
        Y[i].y=X[i].y;
    }
    MergeSort(Y,n);
    PointY *Z=new PointY [n];
    closest(X,Y,Z,0,n-1,a,b,d);
    delete [] Z;
    delete [] Y;
    return true;
}

void Table(int k,int**a)
{	 
    int n=1;
    for(int i=1;i<=k;i++)n*=2;
    for(int i=1;i<=n;i++)a[1][i]=i;
    int m=1;
    for(int s=1;s<=k;s++){
        n/=2;
        for(int t=1;t<=n;t++){
            for(int i=m+1;i<=2*m;i++){
                for(int j=m+1;j<=2*m;j++){
                    a[i][j+(t-1)*m*2]=a[i-m][j+(t-1)*m*2-m];
                    a[i][j+(t-1)*m*2-m]=a[i-m][j+(t-1)*m*2];
                }
            }
        }
        m*=2;
    }
}
