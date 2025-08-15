#include <bits/stdc++.h>
using namespace std;
#include "gcd.h"
const int M=998244353;

ll lcm(int a, int b)
{
	ll r=a/gcd(a,b);
	r=r*b%M;
	return r;
}

ll mlcm(int arr[],int n)
{
    ll ret = arr[0];
    for (int i = 1; i < n; i++)
        //ret=lcm(arr[i],ret);
        ret = ((arr[i]*ret)/gcd(arr[i],ret));
    return ret;
}
 
int main() 
{ 
    int arr[10],k; 
    while(cin>>k){
    	for(int i=0;i<k;i++)cin>>arr[i];
		cout<<mlcm(arr,k)<<endl;
	}
    return 0; 
} 


