#include <bits/stdc++.h>
using namespace std;

#include "exgcd.h"

void chk()
{
	int a,b,x,y,d;
	while(cin>>a>>b){
		d=exgcd(a,b,x,y);
		if(a*x+b*y==d)cout<<d;
		else cout<<"-1";
		cout<<" "<<x<<" "<<y<<endl;
	}
}

int main() 
{
	chk();
	return 0;
}


