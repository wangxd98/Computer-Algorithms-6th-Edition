#include <bits/stdc++.h> 
using namespace std; 

//#include "sufdp.h"
#include "sufdc3.h"

int check()
{
    int n,l,r;
	string text; 
    while(cin>>text){
        suffix suf(text);
        cin>>n;
        for(int i=0;i<n;i++){
        	cin>>l>>r;
        	cout<<suf.lce(l,r)<<endl;
		}
    }
    return 0;       
}

int main()
{
    check();
    return 0;
}

