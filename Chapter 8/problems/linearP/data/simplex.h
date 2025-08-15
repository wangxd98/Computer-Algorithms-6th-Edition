
template <class Type>
void make2dArray(Type ** &x,int rows,int cols)
{
    x=new Type *[rows];
	for (int i=0;i<rows;i++)
	    x[i]=new Type[cols];
}

template <class Type>
void delete2dArray(Type ** &x,int rows)
{
    for (int i=0;i<rows;i++)
        delete[]x[i];
	delete[]x;
    x=0;
}

class LinearProgram 
{
    public:
	    LinearProgram(char *filename);
	    LinearProgram(double minmax,int m,int n,int m1,int m2,int m3,double **a);
        ~LinearProgram();
        void solve0();
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
		    *nonbasic; // 非基本变量下标
	    double **a,minmax;
};

LinearProgram::LinearProgram(char *filename)
{
    ifstream inFile;
    int i,j;
    double value;
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
    n1=n+m3;
    n2=n+m1+m3;
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
    cout<<endl;
    // 引入人工变量，构造第1阶段的辅助目标函数
    for(j=1;j<=n;j++){
        for(i=m1+1,value=0.0;i<=m;i++)value+=a[i][j];
        a[m+1][j]=value;
    }
    inFile.close();
    //problem();
} 

LinearProgram::LinearProgram(double minmax,int m,int n,int m1,int m2,int m3,double **a)
{
    int i,j;
    double value;
    error=0;
    this->minmax=minmax,this->m=m,this->n=n;
    this->m1=m1,this->m2=m2,this->m3=m3;
    this->a=a;
    if( m!=m1+m3+m2 )error=1;
    n1=n+m3;
    n2=n+m1+m3;
    basic=new int[m+2];
    nonbasic=new int[n1+1];
    for(j=0;j<=n1;j++)nonbasic[j]=j;
    // 引入松驰变量和人工变量
    for(i=m-m3+1,j=n+1;i<=m;i++,j++){
	    a[i][j]=-1.0;
        a[m+1][j]=-1.0;
    }
    for(i=1,j=n1+1;i<=m;i++,j++)basic[i] =j;
    // 引入人工变量，构造第1阶段的辅助目标函数
    for(j=1;j<=n;j++){
        for(i=m1+1,value=0.0;i<=m;i++)value+=a[i][j];
        a[m+1][j]=value;
    }
    //problem();
} 

LinearProgram::~LinearProgram()
{
	delete []nonbasic;
	delete []basic;
	//delete2dArray(a,m+2);
}

void LinearProgram::problem()
{
   int width=8;	
   cout.setf(ios::fixed|ios::showpoint|ios::right);
   cout.precision(2);
   if (minmax > 0) cout<<"Maximize:"<<endl;
   else cout<<"Minimize:"<<endl;
   for (int j=1;j<=n;j++){
      cout<<setw(width)<<minmax*a[0][j]<<" * x"<<j;
      if (j != n) cout<<" + ";
      cout<<endl;
   }
   cout<<endl;
   cout<<"约束条件:"<<endl;
   for (int i=1;i<=m;i++){
      for (int j=1;j<=n;j++){
         if (j==1) cout<<"#"<<i<<"...";
         else cout<<" ";
         cout<<setw(width)<<a[i][j]<<" * x"<<j;
         if (j != n) cout<<" + ";
	  }
      if (i<=m1) cout<<" <= ";
      else if (i>m1+m2) cout<<" >= ";
      else cout<<" =  ";
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
	        break;                    // Bland 避循环法则
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

void LinearProgram::solve0()
{
    error=compute();
    switch(error){
        case 0: output();break;
        case 1: cout<<endl<<"输入数据错误"<<endl<<endl;break;
        case 2: cout<<endl<<"无界解"<<endl<<endl;break;
        case 3: cout<<endl<<"无可行解"<<endl<<endl;
    }
} 

void LinearProgram::solve()
{
	cout<<fixed<<setprecision(2);
    if(compute())cout<<"******"<<endl;
	else cout<<-minmax*a[0][0]<<endl;
    //else output();

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
    cout<<"最优值："<<-minmax*a[0][0]<<endl<<endl;
    cout<<"最优解："<<endl;
    for(int j=1;j<=n;j++){
        cout<<"x"<<j<<" =";
        if(basicp[j]!=0)cout<<setw(width)<<a[basicp[j]][0];
        else cout<<setw(width)<<zero;
        cout<<endl;
	}
    cout<<endl;
	delete []basicp;
}


