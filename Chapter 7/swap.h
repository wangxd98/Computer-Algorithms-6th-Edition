#pragma once

template<class Type >
inline void Swap(Type & a,Type & b)
{
    Type temp=a;
    a=b;b=temp;
}
