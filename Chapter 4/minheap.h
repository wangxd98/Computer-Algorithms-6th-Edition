#pragma once

template<class T>
class MinHeap{
   public:
      MinHeap(int MinHeapSize=10);
      ~MinHeap(){delete [] heap;}
      int Size()const {return CurrentSize;}
      T Min(){return heap[1];}
      MinHeap<T>& Insert(const T& x);
      MinHeap<T>& DeleteMin(T& x);
      void Initialize(T a[],int size,int ArraySize);
      void Deactivate(){heap=0;}
    private:
        int CurrentSize,MaxSize;
        T *heap;
};

template<class T>
MinHeap<T>::MinHeap(int MinHeapSize)
{
    MaxSize=MinHeapSize;
    heap=new T[MaxSize+1];
    CurrentSize=0;
}

template<class T>
MinHeap<T>& MinHeap<T>::Insert(const T& x)
{
    int i=++CurrentSize;
    while(i != 1 && x<heap[i/2]){
	    heap[i]=heap[i/2];
        i/=2;
    }
    heap[i]=x;
	return *this;
}

template<class T>
MinHeap<T>& MinHeap<T>::DeleteMin(T& x)
{
    x=heap[1];
	T y=heap[CurrentSize--];
	int i=1,ci=2;
    while(ci<=CurrentSize){
	    if(ci<CurrentSize && heap[ci]>heap[ci+1])ci++;
		if(y<=heap[ci])break;
		heap[i]=heap[ci];
		i=ci;
		ci*=2;
      }
    heap[i]=y;
	return *this;
}

template<class T>
void MinHeap<T>::Initialize(T a[],int size,int ArraySize)
{
    delete [] heap;
    heap=a;
    CurrentSize=size;
    MaxSize=ArraySize;
	for(int i=CurrentSize/2;i>=1;i--){
        T y=heap[i];
		int c=2*i;
		while(c<=CurrentSize){
		    if(c<CurrentSize && heap[c]>heap[c+1])c++;
			if(y<=heap[c])break;
			heap[c/2]=heap[c];
			c*=2;
		}
        heap[c/2]=y;
    }
}

