#pragma once

template <class T> class BinaryTree;
template <class T>
class BinaryTreeNode {
   public:
        BinaryTreeNode(){LeftChild=RightChild=0;}
        BinaryTreeNode(const T& e){data=e;LeftChild=RightChild=0;}
        BinaryTreeNode(const T& e,BinaryTreeNode *l,BinaryTreeNode *r)
        {
		    data=e;LeftChild=l;RightChild=r;
		}
		T data;
		BinaryTreeNode<T> *LeftChild,*RightChild;
};

template<class T>
class BinaryTree {
   public:
      BinaryTree(){root=0;};
      ~BinaryTree(){};
      bool IsEmpty()const
        {return((root)? false : true);}
      bool Root(T& x)const;
      void MakeTree(const T& element,
           BinaryTree<T>& left,BinaryTree<T>& right);
      void PostOrder(void(*Visit)(BinaryTreeNode<T> *u))
           {PostOrder(Visit,root);}
      void PostOutput(){PostOrder(Output,root);cout << endl;}
   private:
      BinaryTreeNode<T> *root;
      void PostOrder(void(*Visit)
       (BinaryTreeNode<T> *u),BinaryTreeNode<T> *t);
      static void Output(BinaryTreeNode<T> *t)
                  {cout << t->data << ' ';}
};

template<class T>
bool BinaryTree<T>::Root(T& x)const
{
    if(root){
	    x=root->data;
        return true;
	}
    else return false;
}

template<class T>
void BinaryTree<T>::MakeTree(const T& element,
          BinaryTree<T>& left,BinaryTree<T>& right)
{
    root=new BinaryTreeNode<T>(element,left.root,right.root);
	left.root=right.root=0;
}

template <class T>
void BinaryTree<T>::PostOrder(
           void(*Visit)(BinaryTreeNode<T> *u),
                        BinaryTreeNode<T> *t)
{
    if(t){
	    PostOrder(Visit,t->LeftChild);
        PostOrder(Visit,t->RightChild);
        Visit(t);
	}
}

