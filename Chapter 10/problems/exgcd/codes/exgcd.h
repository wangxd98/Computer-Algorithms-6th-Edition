#ifndef Exgcd_
#define Exgcd_

	int exgcd(int a,int b,int& x,int& y)
	{
	    if(b==0){x=1;y=0;return a;}
	    int x1,y1;
	    int d=exgcd(b,a%b,x1,y1);
	    x=y1,y=x1-y1*(a/b);
	    return d;
	}
 
	int exgcd1(int a,int b,int &x,int &y)
	{
	    int c=y=0,d=x=1;
	    while(b){
	        int q=a/b,t=a;
	        a=b;b=t%b;
	        t=x;x=c;c=t-q*c;
	        t=y;y=d;d=t-q*d;
	    }
	    return a;
	}
 
	int exgcd3(int n,int a[],int x[])
	{
		int u,v,c,d;
	    if(n==2){
	    	d=exgcd(a[0],a[1],x[0],x[1]);
	        return d;
	    }
	    c=exgcd3(n-1,a,x);
	    d=exgcd(c,a[n-1],u,v);
	    for(int i=0;i<n-1;i++)x[i]*=u;
	    x[n-1]=v;
	    return d;
	}
 
	int exgcd4(int n,int a[],int x[])
	{
		int c=1,d=a[0],y[n],z[n];
		y[0]=z[0]=1;
		for(int i=1;i<n;i++)
			d=exgcd(d,a[i],y[i],z[i]);
		for(int i=n-1;i>=0;i--)
			x[i]=c*z[i],c*=y[i];
	    return d;
	}
 
	int exgcd5(int n,int a[],int x[])
	{
		int c=1,d=a[0];x[0]=1;
		for(int i=1;i<n;i++)d=exgcd(d,a[i],a[i],x[i]);
		for(int i=n-1;i>=0;i--)x[i]*=c,c*=a[i];
	    return d;
	}
 
	bool dioph2(int a,int b,int c,int &x,int &y)
	{
	    int d=exgcd(abs(a),abs(b),x,y);
	    if(c%d)return false;
	    x*=c/d; y*=c/d;
	    if(a<0)x=-x;
		if(b<0)y=-y;
	    return true;
	}

#endif 

