#pragma once

#include "xcept.h"

template<class T>
class MaxHeap{
   public:
      MaxHeap(int MaxHeapSize=10);
      ~MaxHeap(){delete [] heap;}
      int Size()const{return CurrentSize;}
      T Max(){if(CurrentSize==0)
                  throw OutOfBounds();
               return heap[1];}
      MaxHeap<T>& Insert(const T& x);
      MaxHeap<T>& DeleteMax(T& x);
      void Initialize(T a[],int size,int ArraySize);
      void Deactivate(){heap=0;}
      void Output()const;
   private:
      int CurrentSize,MaxSize;
      T *heap;
};

template<class T>
MaxHeap<T>::MaxHeap(int MaxHeapSize)
{
    MaxSize=MaxHeapSize;
    heap=new T[MaxSize+1];
    CurrentSize=0;
}

template<class T>
MaxHeap<T>& MaxHeap<T>::Insert(const T& x)
{
    if(CurrentSize==MaxSize)throw NoMem();
    int i=++CurrentSize;
    while(i!=1 && x>heap[i/2]){
        heap[i]=heap[i/2];
        i/=2;
    }
    heap[i]=x;
    return *this;
}

template<class T>
MaxHeap<T>& MaxHeap<T>::DeleteMax(T& x)
{
    if(CurrentSize==0)throw OutOfBounds();
	x=heap[1];
	T y=heap[CurrentSize--];
	int i=1,ci=2;
    while(ci<=CurrentSize){
	    if(ci<CurrentSize && heap[ci]<heap[ci+1])ci++;
		if(y>=heap[ci])break;
		heap[i]=heap[ci];
		i=ci;
		ci*=2;
    }
    heap[i]=y;
	return *this;
}

template<class T>
void MaxHeap<T>::Initialize(T a[],int size,int ArraySize)
{ 
    delete [] heap;
    heap=a;
    CurrentSize=size;
    MaxSize=ArraySize;
	for(int i=CurrentSize/2;i>=1;i--){
        T y=heap[i];
		int c=2*i;
		while(c<=CurrentSize){
		    if(c<CurrentSize && heap[c]<heap[c+1])c++;
			if(y>=heap[c])break;
			heap[c/2]=heap[c];
			c*=2;// move down a level
        }
        heap[c/2]=y;
    }
}

