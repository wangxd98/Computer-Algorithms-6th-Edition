#ifndef Dioph2_
#define Dioph2_

int exgcd(int a,int b,int &x,int &y) 
{
    int c=y=0,d=x=1;
    while (b){
        int q=a/b,t=a;
        a=b;b=t%b;
        t=x;x=c;c=t-q*c;
        t=y;y=d;d=t-q*d;
    }
    return a;
}

bool dioph2(int a,int b,int c,int &x,int &y) 
{
    int d=exgcd(abs(a),abs(b),x,y);
    if (c%d) return false;
    x*=c/d; y*=c/d;
    if (a<0) x=-x;
	if (b<0) y=-y;
    return true;
}

#endif 
