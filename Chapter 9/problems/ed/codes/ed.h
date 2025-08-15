#ifndef Edit_
#define Edit_

const int maxn=5005;

string x,y;
int n,m,dt=1;
int d[maxn][maxn],d1[maxn];

void init()
{
	memset(d,0,sizeof(d));
	memset(d1,0,sizeof(d1));
}

int ed()
{// 编辑距离的动态规划算法 Code33
    for(int i=0;i<=n;i++)d[i][0]=i;
    for(int i=0;i<=m;i++)d[0][i]=i;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            if (x[i]==y[j])d[i+1][j+1]=d[i][j];
            else d[i+1][j+1]=min(d[i][j]+dt,min(d[i][j+1],d[i+1][j])+1);
    return d[n][m];
}

void back(int i,int j)
{// 构造最优编辑序列 Code34 
    if(i==0){while(j--)cout<<"i("<<j<<")"<<endl;return;} 
    if(j==0){while(i--)cout<<"d("<<i<<")"<<endl;return;} 
    if(x[i-1]==y[j-1])back(i-1,j-1);
    else if(d[i-1][j-1]+dt<min(d[i-1][j],d[i][j-1])+1){
        back(i-1,j-1);
        cout<<"r("<<i-1<<","<<j-1<<")"<<endl;
    }
    else if(d[i-1][j]<d[i][j-1]){
        back(i-1,j);
        cout<<"d("<<i-1<<")"<<endl;
    }
    else{
        back(i,j-1);
        cout<<"i("<<j-1<<")"<<endl;
    }
}

int edn()
{// O(n)空间算法 Code35 
    memset(d1,0,sizeof d1);
    int oldd,newd;
    for(int i=0;i<=n;i++)
        for(int j=0;j<=m;j++){
            if(i==0)oldd=d1[j],d1[j]=j;
            else if(j==0)oldd=d1[j],d1[j]=i;
            else{
                if(x[i-1]==y[j-1])newd=oldd;
                else newd=min(oldd+dt,min(d1[j-1],d1[j])+1);
                oldd=d1[j],d1[j]=newd;
            }
        }
    return d1[m];
}

#endif 

