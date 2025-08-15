#include <bits/stdc++.h> 
using namespace std; 

//#include "sufdp.h"
#include "sufdc3.h"

int check()
{
    string text; 
    while(cin>>text){
        suffix suf(text);
        int *lcp=suf.lcp;
        for(int i=0;i<text.size();i++)cout<<lcp[i]<<" ";cout<<endl;
    }
    return 0;       
}

int main()
{
    check();
    return 0;
}

