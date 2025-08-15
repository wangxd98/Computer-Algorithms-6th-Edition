#ifndef Queue_
#define Queue_

template <class Item>
class Queue
{
private:
    vector<Item> s; int N;
public:
        Queue(int maxN) : s(maxN+1), N(0) {}
        bool empty() const{ return N == 0; }
        int size() const{ return N; }
       
	    bool exist(Item item)
	    {
		    for(int i=0;i<N;i++) if(s[i]==item) return true;
		    return false;
	    }

        void put(Item item)
        {
		    if (N>=s.size()) {cout<<"queue over flow"<<" s.ize="<<s.size()<<" N="<<N<<endl;return;}
		    s[N++] = item; 
		}

        void update(Item x) { }
        Item get()
        { 
            Item t = s[0];
		    for (int i=1;i<N;i++) s[i-1] = s[i];
		    N--;
            return t; 
	    }

		void init(int n){N=0;}
};

#endif
