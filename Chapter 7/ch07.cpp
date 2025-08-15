#include <bits/stdc++.h>
using namespace std;

#include "swap.h"
#include "xcept.h"

const unsigned long maxshort=65536L;
const unsigned long multiplier=1194211693L;
const unsigned long adder=12345L;

class RandomNumber
{
    private:
        // 当前种子  
        unsigned long randSeed;
    public:
        // 构造函数，缺省值0表示由系统自动产生种子
        RandomNumber(unsigned long s=0);
        // 产生0:n-1之间的随机整数
        unsigned short Random(unsigned long n);
        // 产生[0,1)之间的随机实数
        double fRandom();
};

// 产生种子 
RandomNumber::RandomNumber(unsigned long s)
{
    if(s==0)randSeed=time(0); // 用系统时间产生种子
    else randSeed=s;      // 由用户提供种子
}

// 产生0:n-1之间的随机整数
unsigned short RandomNumber::Random(unsigned long n)
{
    randSeed=multiplier*randSeed+adder;
    return(unsigned short)((randSeed>>16)%n);
}

// 产生[0,1)之间的随机实数
double RandomNumber::fRandom()
{
    return Random(maxshort)/double(maxshort);
}

int TossCoins(int numberCoins)
{ // 随机抛硬币
    static RandomNumber coinToss;
    int i,tosses=0;
    for(i=0;i<numberCoins;i++)
        // Random(2)=1 表示正面
        tosses+=coinToss.Random(2);
    return tosses;
}

// 测试程序 
void tst()
{ // 模拟随机抛硬币事件
    const int NCOINS=10;
    const long NTOSSES=50000L;
    // heads[i]是得到i次正面的次数
    long i,heads[NCOINS+1];
    int  j,position;
    // 初始化数组heads 
    for(j=0;j<NCOINS+1;j++)
        heads[j]=0;
    // 重复50,000次模拟事件
    for(i=0;i<NTOSSES;i++)
        heads[TossCoins(NCOINS)]++;
    // 输出频率图
    for(i=0;i<=NCOINS;i++){
        position=int(float(heads[i])/NTOSSES*72);
        cout<<setw(6)<<i<<"  ";
        for(j=0;j<position-1;j++)
            cout<<" ";
        cout<<"*"<<endl;
    }
}

double Darts(int n)
{ // 用随机投点法计算pi值
    static RandomNumber dart;
    int k=0;
    for(int i=1;i<=n;i++){
        double x=dart.fRandom();
        double y=dart.fRandom();
        if((x*x+y*y)<=1)k++;
    }
    return 4*k/double(n);
}

double f(double x)
{
	return x*x;
}

double f1(double *x)
{
	return x[1]*x[1]*x[1]-x[2]*x[2]-16;
}

double f2(double *x)
{
	return x[1]*x[2]+x[2]-15;
}

double f(double *x,int n)
{
	return f1(x)*f1(x)+f2(x)*f2(x);
}

double g(double x)
{
	return x*x;
}

double Darts1(int n)
{ // 用随机投点法计算定积分
    static RandomNumber dart;
    int k=0;
    for(int i=1;i<=n;i++){
        double x=dart.fRandom();
        double y=dart.fRandom();
        if(y<=f(x))k++;
    }
    return k/double(n);
}

double Integration(double a,double b,int n)
{ // 用平均值法计算定积分
    static RandomNumber rnd;
    double y=0;
    for(int i=1;i<=n;i++){
        double x=(b-a)*rnd.fRandom()+a;
        y+=g(x);
    }
    return(b-a)*y/double(n);
}

bool NonLinear(double *x0,double *dx0,double *x,double a0,
               double epsilon,double k,int n,int Steps,int M)
{ // 解非线性方程组的随机化算法
    static RandomNumber rnd;
    bool success;         // 搜索成功标志
    double *dx,*r;
    dx=new double [n+1]; // 步进增量向量
    r=new double [n+1];  // 搜索方向向量
    int mm=0;            // 当前搜索失败次数
    int j=0;      // 迭代次数
    double a=a0; // 步长因子
    for(int i=1;i<=n;i++){
        x[i]=x0[i];
        dx[i]=dx0[i];
    }
    double fx=f(x,n); // 计算目标函数值
    double min=fx;   // 当前最优值
    while((min>epsilon)&&(j<Steps)){
        // （1）计算随机搜索步长
        if(fx<min){ // 搜索成功
           min=fx;
           a*=k;
           success=true;
		}
        else { // 搜索失败
            mm++;
            if(mm>M)a/=k;
            success=false;
		}
        // （2）计算随机搜索方向和增量
        for(int i=1;i<=n;i++)
             r[i]=2.0*rnd.fRandom()-1;
        if(success)
            for(int i=1;i<=n;i++)
                dx[i]=a*r[i];
        else
            for(int i=1;i<=n;i++)
                dx[i]=a*r[i]-dx[i];
        // （3）计算随机搜索点
        for(int i=1;i<=n;i++)
            x[i]+=dx[i];
        // （4）计算目标函数值
        fx=f(x,n);
        j++;
    }
    if(fx<=epsilon)return true;
    else return false;
}

template<class Type>
Type select(Type a[],int l,int r,int k)
{// 计算a[l:r]中第k小元素
    static RandomNumber rnd;
    while(true){
        if(l>=r)return a[l];
        int i=l,
        j=l+rnd.Random(r-l+1); // 随机选择的划分基准
        Swap(a[i],a[j]);
        j=r+1;
        Type pivot=a[l];
        // 以划分基准为轴作元素交换
        while(true){
            while(a[++i]<pivot);
            while(a[--j]>pivot);
            if(i>=j)break;
            Swap(a[i],a[j]);
        }
        if(j-l+1==k)return pivot;
        a[l]=a[j];
        a[j]=pivot;
        // 对子数组重复划分过程
        if(j-l+1<k){
            k=k-j+l-1;
            l=j+1;
		}
        else r=j-1;
    }
}

template<class Type>
Type Select(Type a[],int n,int k)
{// 计算a[0:n-1]中第k小元素
    // 假设a[n]是一个键值无穷大的元素
    if(k<1 || k>n)throw OutOfBounds();
    return select(a,0,n-1,k);
}

template<class Type>
void Shuffle(Type a[],int n)
{// 随机洗牌算法
    static RandomNumber rnd;
    for(int i=0;i<n;i++){
        int j=rnd.Random(n-i)+i;
        Swap(a[i],a[j]);
    }
}

template<class Type>
class OrderedList 
{
	friend void tst08();
    public:
        OrderedList(Type small,Type Large,int MaxL);
        ~OrderedList();
        bool Search(Type x,int& index); // 搜索指定元素
        int SearchLast();           // 搜索最大元素
        void Insert(Type k);            // 插入指定元素
        void Delete(Type k);            // 删除指定元素
        void Output();                 // 输出集合中元素
    private:
        int n;               // 当前集合中元素个数
        int MaxLength;      // 集合中最大元素个数
        Type *value;         // 存储集合中元素的数组
        int *link;            // 指针数组
        RandomNumber rnd; // 随机数产生器
        Type Small;         // 集合中元素的下界
        Type TailKey;       // 集合中元素的上界
};

template<class Type>
OrderedList<Type>::OrderedList(Type small,Type Large,int MaxL)
{// 构造函数
    MaxLength=MaxL;
    value=new Type [MaxLength+1];
    link=new int [MaxLength+1];
    Type ailKey=Large;
    n=0;
    link[0]=0;
    value[0]=TailKey;
    Small=small;
}

template<class Type>
OrderedList<Type>::~OrderedList()
{// 析构函数
    delete []value;
    delete []link;
}

template<class Type>
bool OrderedList<Type>::Search(Type x,int& index)
{// 搜索集合中指定元素k.
    index=0;
    Type max=Small;
    int m=floor(sqrt(double(n))); // 随机抽取数组元素次数
    for(int i=1;i<=m;i++){
        int j=rnd.Random(n)+1;    // 随机产生数组元素位置
        Type y=value[j];
        if((max<y)&&(y<x)){
            max=y;
            index=j;
		}
    }
    // 顺序搜索
    while(value[link[index]]<x)index=link[index];
    return(value[link[index]]==x);
}

template<class Type>
void OrderedList<Type>::Insert(Type k)
{// 插入指定元素
    if((n==MaxLength)||(k>=TailKey))return;
    int index;
    if(!Search(k,index)){
        value[++n]=k;
        link[n]=link[index];
        link[index]=n;
	}
}

template<class Type>
int OrderedList<Type>::SearchLast()
{// 搜索集合中最大元素
    int index=0;
    Type x=value[n];
    Type max=Small;
    int m=floor(sqrt(double(n)));  // 随机抽取数组元素次数
    for(int i=1;i<=m;i++){
        int j=rnd.Random(n)+1;     // 随机产生数组元素位置
        Type y=value[j];
        if((max<y)&&(y<x)){
            max=y;
            index=j;
		}
    }
    // 顺序搜索
    while(link[index]!=n)index=link[index];
    return index;
 }

template<class Type>
void OrderedList<Type>::Delete(Type k)
{// 删除集合中指定元素k
    if((n==0)||(k>=TailKey))return;
    int index;
    if(Search(k,index)){
        int p=link[index];
        if(p==n)link[index]=link[p];
        else {
            if(link[p]!=n){
                int q=SearchLast();
                link[q]=p;
                link[index]=link[p];
			}
            value[p]=value[n];
            link[p]=link[n];
        }
        n--;
    }
}

template<class Type>
void OrderedList<Type>::Output()
{
	cout<<"n="<<n<<endl;
	for(int i=0,idx=0;i<n;i++){
		idx=link[idx];
		cout<<value[idx]<<" ";
	}
	cout<<endl;
}

template <class EType,class KType> class SkipList;
template<class EType,class KType>
class SkipNode 
{
    friend SkipList<EType,KType>;
    private:
        SkipNode(int size)
           {next=new SkipNode<EType,KType> *[size];}
        ~SkipNode(){delete [] next;}
        EType data;
        SkipNode<EType,KType> **next; // 指针数组
};

template<class EType,class KType>
class SkipList 
{
    public:
        SkipList(KType Large,int MaxE=10000,float p=0.5);
        ~SkipList();
        bool Search(const KType& k,EType& e)const;
        SkipList<EType,KType>& Insert(const EType& e);
        SkipList<EType,KType>& Delete(const KType& k,EType& e);
        void Output();
    private:
        int Level();
        SkipNode<EType,KType> *SaveSearch(const KType& k);
        int MaxLevel;                   // 跳跃表级别上界
        int Levels;                      // 当前最大级别
        RandomNumber rnd;             // 随机数产生器
        float Prob;                      // 用于分配结点级别
        KType TailKey;                 // 元素键值上界
        SkipNode<EType,KType> *head;  // 头结点指针
        SkipNode<EType,KType> *NIL;   // 尾结点指针
        SkipNode<EType,KType> **last;  // 指针数组
};

template<class EType,class KType>
SkipList<EType,KType>::SkipList(KType Large,int MaxE,float p)
{// 构造函数
    Prob=p ;
    MaxLevel=ceil(log(MaxE)/ log(1/p))- 1;// 初始化跳跃表级别上界
    TailKey=Large;// 元素键值上界
    Levels=0; // 初始化当前最大级别
    // 创建头、尾结点和数组last
    head=new SkipNode<EType,KType>(MaxLevel+1);
    NIL=new SkipNode<EType,KType>(0);
    last=new SkipNode<EType,KType> *[MaxLevel+1];
    NIL->data=Large;
    // 将跳跃表初始化为空表
    for(int i=0;i<=MaxLevel;i++)
        head->next[i]=NIL;
}

template<class EType,class KType>
SkipList<EType,KType>::~SkipList()
{// 析构函数
    SkipNode<EType,KType> *next;
    // 删除所有结点
    while(head!=NIL){
        next=head->next[0];
        delete head;
        head=next;
    }
    delete NIL;
    delete [] last;
}

class element 
{
    public:
        operator long()const {return key;}
        element& operator=(long y)
        {key=y;return *this;}
    private:
        int data;
        long key;
};

template<class EType,class KType>
bool SkipList<EType,KType>::Search(const KType& k,EType& e)const
{// 搜索指定元素k
    if(k>=TailKey)return false;
    // 位置p恰好位于指定元素k之前
    SkipNode<EType,KType> *p=head;
    for(int i=Levels;i>=0;i--)     // 逐级向下搜索
        while(p->next[i]->data<k)   // 在第i级链中搜索
            p=p->next[i];
    e=p->next[0]->data;
    return(e==k);
}

template<class EType,class KType>
SkipNode<EType,KType>*SkipList<EType,KType>::SaveSearch(const KType& k)
{// 搜索指定元素k，并将每一级中遇到的上一个结点存放在数组last中
    // 位置p恰好位于指定元素k之前
    SkipNode<EType,KType> *p=head;
    for(int i=Levels;i>=0;i--){
        while(p->next[i]->data<k)
            p=p->next[i];
            last[i]=p; // 上一个第i级结点
        }
    return(p->next[0]);
}

template<class EType,class KType>
int SkipList<EType,KType>::Level()
{// 产生不超过MaxLevel的随机级别
    int lev=0;
    while(rnd.fRandom()<Prob)lev++;
    return(lev<=MaxLevel)? lev : MaxLevel;
}

template<class EType,class KType>
SkipList<EType,KType>& SkipList<EType,KType>::Insert(const EType& e)
{// 插入指定元素e
    KType k=e;// 取得元素键值
    //if(k>=TailKey)throw BadInput();// 元素键值超界
    if(k>=TailKey)return *this;// 元素键值超界
    // 检查元素是否已存在
    SkipNode<EType,KType> *p=SaveSearch(k);
    //if(p->data==e)throw BadInput();// 元素已存在
    if(p->data==e)return *this;// 元素已存在
    // 元素不存在，确定新结点级别
    int lev=Level();
    // 调整各级别指针
    if(lev>Levels){
        for(int i=Levels+1;i<=lev;i++)
            last[i]=head;
        Levels=lev;
	}
    // 产生新结点，并将新结点插入p之后
    SkipNode<EType,KType> *y=new SkipNode<EType,KType>(lev+1);
    y->data=e;
    for(int i=0;i<=lev;i++){
        // 插入第i级链
        y->next[i]=last[i]->next[i];
        last[i]->next[i]=y;
    }
    return *this;
}

template<class EType,class KType>
SkipList<EType,KType>& SkipList<EType,KType>::Delete
                                     (const KType& k,EType& e)
{// 删除键值为k的元素，并将所删除元素存入e
    if(k>=TailKey)throw BadInput();// 元素键值超界
    // 搜索待删除元素
    SkipNode<EType,KType> *p=SaveSearch(k);
    if(p->data!=k)throw BadInput();// 未找到
    // 从跳跃表中删除结点
    for(int i=0;i<=Levels && last[i]->next[i]==p;i++)
        last[i]->next[i]=p->next[i];
    // 更新当前级别
    while(Levels>0 && head->next[Levels]==NIL)
        Levels--;
    e=p->data;
    delete p;
    return *this;
}

template<class EType,class KType>
void SkipList<EType,KType>::Output()
{// 输出集合中元素
    SkipNode<EType,KType> *y=head->next[0];
    for(;y!=NIL;y=y->next[0])
        cout<<y->data<<' ';
    cout<<endl;
}

/*
void Obstinate(InputType x,OutputType &y)
{// 反复调用拉斯维加斯算法LV(x,y)，直到找到问题的一个解y
    bool success=false；
    while(!success)success=LV(x,y)；
}
*/

class Queen1 
{
    friend void nQueen1(int);
    private:
        bool Place(int k);  // 测试皇后k置于第x[k]列的合法性
        bool QueensLV();  // 随机放置n个皇后拉斯维加斯算法
        int n,           // 皇后个数
            *x,*y ;      // 解向量
};


bool Queen1::Place(int k)
{// 测试皇后k置于第x[k]列的合法性
    for(int j=1;j<k;j++)
        if((abs(k-j)==abs(x[j]-x[k]))||(x[j]==x[k]))return false;
    return true;
}

bool Queen1::QueensLV()
{// 随机放置n个皇后的拉斯维加斯算法
   RandomNumber rnd; // 随机数产生器
   int k=1;             // 下一个放置的皇后编号
   int count=1;
   while((k<=n)&&(count>0)){
       count=0;
       for(int i=1;i<=n;i++){
           x[k]=i;
           if(Place(k))y[count++]=i;
        }
        if(count>0)x[k++]=y[rnd.Random(count)];// 随机位置
    }
    return(count>0);   // count>0表示放置成功
}

void nQueen1(int n)
{// 解n后问题的拉斯维加斯算法
    Queen1 X;
    // 初始化X
    X.n=n;
    int *p=new int [n+1];
    for(int i=0;i<=n;i++)p[i]=0;
    X.x=p;
    X.y=new int[n+1];
    // 反复调用随机放置n个皇后的拉斯维加斯算法，直至放置成功
    while(!X.QueensLV());
        for(int i=1;i<=n;i++)cout<<p[i]<<"  " ;
        cout<<endl;
    delete [] X.y;
    delete [] p;
}

class Queen 
{
    friend bool nQueen(int);
    private:
        bool Place(int k);           // 测试皇后k置于第x[k]列的合法性
        bool Backtrack(int t);       // 解n后问题的回溯法
        bool QueensLV(int stopVegas);// 随机放置n个皇后拉斯维加斯算法
        int n,*x,*y;
};

bool Queen::Place(int k)
{// 测试皇后k置于第x[k]列的合法性
    for(int j=1;j<k;j++)
        if((abs(k-j)==abs(x[j]-x[k]))||(x[j]==x[k]))return false;
    return true;
}

bool Queen::Backtrack(int t)
{// 解n后问题的回溯法
    if(t>n){
        for(int i=1;i<=n;i++)y[i]=x[i];
        return true;
    }
    else
        for(int i=1;i<=n;i++){
            x[t]=i;
            if(Place(t)&& Backtrack(t+1))return true;
        }
    return false;
}

bool Queen::QueensLV(int stopVegas)
{ // 随机放置n个皇后拉斯维加斯算法
    RandomNumber rnd;
    int k=1; // 随机数产生器
    int count=1;
    // 1?stopVegas?n表示允许随机放置的皇后数
    while((k<=stopVegas)&&(count>0)){
        count=0;
        for(int i=1;i<=n;i++){
            x[k]=i;
            if(Place(k))y[count++]=i;
        }
        if(count>0)x[k++]=y[rnd.Random(count)]; // 随机位置
    }
    return(count>0);      // count>0表示放置成功
}

bool nQueen(int n)
{// 与回溯法相结合的解n后问题的拉斯维加斯算法
    Queen X;
    // 初始化X
    X.n=n;
    int *p=new int [n+1];
    int *q=new int [n+1];
    for(int i=0;i<=n;i++){p[i]=0;q[i]=0;}
    X.y=p;X.x=q;
    int stop=5;
    if(n>15)stop=n-15;
    bool found=false;
    while(!X.QueensLV(stop));
    // 算法的回溯搜索部分
    if(X.Backtrack(stop+1)){
        for(int i=1;i<=n;i++)cout<<p[i]<<"  " ;
        cout<<endl;
        found=true;
    }
    delete [] p;delete [] q;
    return found;
}

int Split(int n)
{
    int m=floor(sqrt(double(n)));
    for(int i=2;i<=m;i++)
        if(n%i==0)return i;
    return 1;
}

int gcd(int a,int b)
{// 求整数a和b最大公因数的欧几里得算法
    if(b==0)return a;
    else return gcd(b,a%b);
}

void Pollard(int n)
{// 求整数n因子分割的拉斯维加斯算法
    RandomNumber rnd;
    int i=1;
    int x=rnd.Random(n);// 随机整数
    int y=x;
    int k=2;
    while(true){
        i++;
        x=(x*x-1)%n;
        int d=gcd(y-x,n); // 求n的非平凡因子
        if((d>1)&&(d<n)){
        	cout<<d<<endl;
        	return;
		}
        if(i==k){
            y=x;
            k*=2;
		}
    }
}

RandomNumber rnd;
template<class Type>
bool Majority(Type *T,int n)
{// 判定主元素的蒙特卡罗算法
    int i=rnd.Random(n)+1;
    Type x=T[i];   // 随机选择数组元素
    int k=0;
    for(int j=1;j<=n;j++)
        if(T[j]==x)k++;
    return(k>n/2); // k>n/2 时T含有主元素
}

template<class Type>
bool Majority2(Type *T,int n)
{// 重复2次调用算法Majority
    if(Majority(T,n))return true;
    else return Majority(T,n);
}

template<class Type>
bool MajorityMC(Type *T,int n,double e)
{// 重复log(1/ε)次调用算法Majority
    int k=ceil(log(1/e)/log(2));
    for(int i=1;i<=k;i++)
        if(Majority(T,n))return true;
    return false;
}

bool Prime1(unsigned int n)
{
    RandomNumber rnd;
    int m=floor(sqrt(double(n)));
    unsigned int a=rnd.Random(m-2)+2;
    return(n%a!=0);
}

void power( unsigned int a,unsigned int p,unsigned int n,
            unsigned int &result,bool &composite)
{// 计算 mod n，并实施对n的二次探测
    unsigned int x;
    if(p==0)result=1;
    else {
        power(a,p/2,n,x,composite); // 递归计算
        result=(x*x)%n;           // 二次探测
        if((result==1)&&(x!=1)&&(x!=n-1))
            composite=true;
        if((p%2)==1)     // p是奇数
            result=(result*a)%n;
    }
}

bool Prime(unsigned int n)
{// 素数测试的蒙特卡罗算法
    RandomNumber rnd;
    unsigned int a,result;
    bool composite=false;
    a=rnd.Random(n-3)+2;
    power(a,n-1,n,result,composite);
    if(composite||(result!=1))return false;
    else return true;
}

bool PrimeMC(unsigned int n,unsigned int k)
{// 重复k次调用算法Prime的蒙特卡罗算法
    RandomNumber rnd;
    unsigned int a,result;
    bool composite=false;
    for(int i=1;i<=k;i++){
        a=rnd.Random(n-3)+2;
        power(a,n-1,n,result,composite);
        if(composite||(result!=1))return false;
    }
    return true;
}

int main() 
{
	return 0;
}


 

