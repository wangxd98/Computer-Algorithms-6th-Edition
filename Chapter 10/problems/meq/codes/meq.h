#ifndef Meq_
#define Meq_

#define int long long

int exgcd(int a,int b,int& x,int& y)
{
	if(b==0){x=1;y=0;return a;}
	int x1,y1;
	int d=exgcd(b,a%b,x1,y1);
	x=y1,y=x1-y1*(a/b);
	return d;
}

int meq(int a, int b, int n, int &x)
{
	int v;
    int d=exgcd(a,n,x,v);
    if (b%d) return 0;
    n/=d,x=((x*b/d)%n+n)%n;
	return d;
}

#endif 
