#include <bits/stdc++.h>
using namespace std;

#include "dioph2.h"

void chk()
{
	int a,b,c,x,y,d;
	while(cin>>a>>b>>c){
		d=dioph2(a,b,c,x,y);
		if(d &&(a*x+b*y==c))cout<<x<<" "<<y<<endl;
		else cout<<"-1";
	}
}

int main() 
{
	chk();
	return 0;
}


