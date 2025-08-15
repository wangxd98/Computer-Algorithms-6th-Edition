#ifndef G_queue_
#define G_queue_

template <class Type>
class GQ
{
    private:
      vector<Type> s;int N;
    public:
        GQ(int maxN): s(maxN+1),N(0){}
        int empty()const
        {return N==0;}
        void put(Type item)
        {s[N++]=item;}
        void update(Type x){}
        Type get()
        {
		    int i=int(N*rand()/(1.0+RAND_MAX));
            Type t=s[i];
            s[i]=s[N-1];
            s[N-1]=t;
            return s[--N];
		}
};

#endif