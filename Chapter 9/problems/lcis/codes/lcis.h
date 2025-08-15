#ifndef LCIS_
#define LCIS_

const int maxn=22005;

int n,m,x[maxn],y[maxn],d[maxn];
int f[maxn][maxn];

int lcis()
{// 最长公共递增子序列 Code36 
    memset(f,0,sizeof(f));
    for(int i=1;i<=n;i++){
        int max=0;
        for(int j=1;j<=m;j++){
            f[i][j]=f[i-1][j];
            if(x[i-1]>y[j-1] && max<f[i-1][j])max=f[i-1][j];
            if(x[i-1]==y[j-1])f[i][j]=max+1;
        }
    }
    int ret=0;
    for(int i=1;i<=m;i++)if(ret<f[n][i])ret=f[n][i];
    return ret;
}

int lcisn()
{
    memset(d,0,sizeof(d));
    for(int i=1;i<=n;i++){
        int mx=0;
        for(int j=1;j<=m;j++){
            if(x[i]>y[j])mx=max(mx,d[j]);
            if(x[i]==y[j])d[j]=mx+1;
        }
    }
    int ret=0;
    for(int i=1;i<=m;i++)ret=max(ret,d[i]);
    return ret;
}

#endif 

