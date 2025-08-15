#pragma once

template <class Type>
void make2dArray(Type ** &x,int rows,int cols)
{
    x=new Type *[rows];
	for(int i=0;i<rows;i++)
	    x[i]=new Type[cols];
}

template <class Type>
void delete2dArray(Type ** &x,int rows)
{
    for(int i=0;i<rows;i++)
        delete[]x[i];
	delete[]x;
    x=0;
}

