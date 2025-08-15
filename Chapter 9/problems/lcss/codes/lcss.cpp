#include <bits/stdc++.h> 
using namespace std; 

#include "sufdc3.h"

bool diff(int *sa,int m,int i)
{
    return (m<sa[i] && m>sa[i+1])||(m>sa[i] && m<sa[i+1]);
}

void change(string s1,string s2,string& t)
{
    int m=s1.length(),n=s2.length();
    t.resize(n+m+1);
    for(int i=0;i<m;i++)t[i]=s1[i];
    for(int i=0;i<n;i++)t[m+i+1]=s2[i];
    n=m+n+1;t[m]=t[n]=0;
}

int lcss(string s1,string s2)
{
    int *sa,*lcp,m,n,ans=0;
    string t;
    m=s1.length();n=s1.length()+s2.length();
    change(s1,s2,t);
    suffix suf(t);sa=suf.sa;lcp=suf.lcp;
    for(int i=0;i<n-1;i++)
        if(lcp[i]>ans && diff(sa,m,i))ans=lcp[i];
    return ans;
}

int main()
{
    string s1,s2;
    while(cin>>s1>>s2) 
        cout<<lcss(s1,s2)<<endl;
	return 0;
}


