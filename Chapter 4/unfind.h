#pragma once

class UnionFind {
   public:
        UnionFind(int Size=10);
        ~UnionFind(){
		    delete [] parent;
            delete [] root;
		}
        void Union(int, int);
        int Find(int);
    private:
        int *parent;
        bool *root;
};

UnionFind::UnionFind(int n)
{
    root=new bool[n+1];
    parent=new int[n+1];
    for(int e=1;e <= n;e++){
        parent[e]=1;
        root[e]=true;
	}
}

int UnionFind::Find(int e)
{
    int j=e;
    while(!root[j])j=parent[j];
    int f=e;
    while(f!=j){
        int pf=parent[f];
        parent[f]=j;
        f=pf;
	}
    return j;
}

void UnionFind::Union(int i, int j)
{
    if(parent[i]<parent[j]){
        parent[j]+=parent[i];
        root[i]=false;
        parent[i]=j;
	}
    else {
        parent[i]+=parent[j];
        root[j]=false;
        parent[j]=i;
	}
}
