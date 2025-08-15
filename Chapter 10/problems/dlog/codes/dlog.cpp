//ÀëÉ¢¶ÔÊıËã·¨ 
#include <bits/stdc++.h>
using namespace std;

int dlog(int a,int b,int n)
{
    unordered_map<int,int>mp;
    int q=1,m=sqrt(n)+1;
    for(int i=0;i<m;++i)q=(q*a)%n;
    for(int j=0;j<=m;j++)mp[b]=j,b=(b*a)%n;
    for(int i=1,r=1;i<=m;i++){
        r=(r*q)%n;
        if(mp.count(r))return m*i-mp[r];
    }
    return -1;
}

int chek()
{
	int n,a,b;
	while(cin>>a>>b>>n){
		int r=dlog(a,b,n);cout<<r<<endl;
	}
    return 0;
}

int main()
{
	chek();
	return 0;
}



