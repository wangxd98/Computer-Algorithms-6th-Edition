#ifndef Queue_
#define Queue_
#include "xcept.h"

template<class T>
class Queue {
    public:
        Queue(int MaxQueueSize=10);
        ~Queue() {delete [] queue;}
        bool IsEmpty() const {return front==rear;}
        bool empty() const {return front==rear;}
        bool IsFull() const {return (
           ((rear + 1) % MaxSize==front) ? 1 : 0);}
        T First() const;
		T Last() const;
		T get();
		Queue<T>& Add(const T& x);
		void put(const T& x);
		Queue<T>& Delete(T& x);
    private:
        int front;
		int rear;
		int MaxSize;
		T *queue;
};

template<class T>
Queue<T>::Queue(int MaxQueueSize)
{
    MaxSize=MaxQueueSize+1;
    queue=new T[MaxSize];
    front=rear=0;
}

template<class T>
T Queue<T>::First() const
{
    if (IsEmpty()) throw OutOfBounds();
    return queue[(front + 1) % MaxSize];
}

template<class T>
T Queue<T>::get()
{
    if (IsEmpty()) throw OutOfBounds();
    front=(front + 1) % MaxSize;
    return queue[front];
}

template<class T>
T Queue<T>::Last() const
{
    if (IsEmpty()) throw OutOfBounds();
    return queue[rear];
}

template<class T>
Queue<T>& Queue<T>::Add(const T& x)
{
    if (IsFull()) throw NoMem();
    rear=(rear + 1) % MaxSize;
    queue[rear]=x;
    return *this;
}

template<class T>
void Queue<T>::put(const T& x)
{
    if (IsFull()) throw NoMem();
    rear=(rear + 1) % MaxSize;
    queue[rear]=x;
}

template<class T>
Queue<T>& Queue<T>::Delete(T& x)
{
    if (IsEmpty()) throw OutOfBounds();
    front=(front + 1) % MaxSize;
    x=queue[front];
    return *this;
}

#endif
