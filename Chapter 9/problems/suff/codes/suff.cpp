#include <bits/stdc++.h> 
using namespace std; 

//#include "sufdp.h"
#include "sufdc3.h"

int check()
{
    string text; 
    while(cin>>text){
        suffix suf(text);
        int *sa=suf.sa;
        for(int i=0;i<text.size();i++)cout<<sa[i]<<" ";cout<<endl;
    }
    return 0;       
}

int main()
{
    check();
    return 0;
}

