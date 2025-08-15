#ifndef Queue_
#define Queue_
 
template <typename T, typename Container = std::deque<T>>
class Queue : public std::queue<T,Container> {
public:
	T N;
	Queue(T maxN=0):N(maxN){}
	
    T put(T x) {this->push(x);}	
	
    T get(){
    	T x=N;
    	if(!this->empty()){
		    x=this->front();
    	    this->pop();
		}
    	return x;
    }
};

#endif
