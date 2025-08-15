#include<bits/stdc++.h>
using namespace std;

#include "ac.h"

void tst()
{
	int n;
	while(cin>>n){
        string s,kwd;
        vector<string> keywords;
	    for(int i=0;i<n;i++){
		    cin>>kwd;
		    keywords.push_back(kwd);
	    }
	    Aho dd(keywords);
	    cin>>s;
	    cout<<dd.mult_search(s)<<endl;
    }
}

int main()
{
    tst();
	return 0;
}
