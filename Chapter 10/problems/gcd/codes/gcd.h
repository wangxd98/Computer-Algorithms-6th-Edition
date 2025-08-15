#ifndef Gcd_
#define Gcd_

	int gcd0(int a,int b)
	{
	    if(b==0)return a;
	    else return gcd0(b,a%b);
	}

	int gcd1(int a, int b)
	{
	    while(b){a%=b;swap(a,b);}
	    return a;
	}
 
	int gcd2(int a, int b)
	{
	    while(a!=b){
	        if(a>b)a-=b;
	        else b-=a;
	    }
	    return a;
	}
 
	int gcd(int a,int b)
	{
	    if(a<b)swap(a,b);
	    else if(b==0 || a==b)return a;
	    if((a & 1)==0 &&(b & 1)==0)return gcd(a>>1,b>>1)<<1;// a even,b even
	    else if((a & 1)==0 &&(b & 1))return gcd(a>>1,b);// a even,b odd
	    else if((a & 1)&&(b & 1)==0)return gcd(a,b>>1);// a odd,b even
	    else return gcd(a-b,b);// a odd,b odd
	}
 
	int gcd5(int a,int b)
	{
	    int c=0;
	    while((a & 1)==0 &&(b & 1)==0){// both evev
	         a>>=1;b>>=1;c++;
	    }// now at least one of a, b is odd 
	    while((a & 1)==0)a>=1;
	    while((b & 1)==0)b>=1;
	    if(a<b)swap(a,b);
	    while((a =(a-b)>>1)!= 0){// both odd
	        while((a & 1)==0)a>>=1;// a evev, b odd
	        if(a<b)swap(a,b);
	    }
	    return b<<c;
	}
 
	int gcd6(int n,int a[])
	{
		int t=1,e=n-1,c,i,u;
		while(t){
			for(i=0,t=0,c=a[0];i<=e;i++)
			    if(u=a[i]%c)a[t++]=u;
			a[t]=c,e=t;
		}
	    return c;
	}
 
	int gcd7(int n,int a[])
	{
		int t=1,e=n-1,c=a[0],d=a[0],i,u;
		while(t){
			for(i=0,t=0;i<=e;i++)
			    if(u=a[i]%c)a[t++]=u,d=min(u,d);
			a[t]=c,e=t,c=d;
		}
	    return d;
	}

#endif 
