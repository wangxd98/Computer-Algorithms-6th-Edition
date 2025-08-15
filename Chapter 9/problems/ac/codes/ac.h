#ifndef Aho_
#define Aho_

#define dsize 26   //字符集 size  
#define idsize 256   

typedef struct node
{
    int cnt; //output 计数 
    node* fail;
    node* go[dsize];
    vector<string> output;
}tnode;

class Aho
{
private:
    tnode* root;
    int idx[idsize]; 
        
    void index()
    {// 预先计算idx Code9
        for(int i=0;i<dsize;i++)idx['a'+i]=i;
    }
        
    tnode* newnode()
    {// 建立新的状态结点 Code10 
    	tnode *nd=new node();
        nd->cnt=0;nd->fail=root;
        return nd;
    }
        
    void init()
    {
        index();root=NULL;root=newnode();
    }
        
    int addout(tnode* p,tnode* q)
    {// 合并两结点p和q的output Code12 
        p->output.insert(p->output.begin(),q->output.begin(),q->output.end());
        return p->output.size();
    }
        
public:
        
    Aho(){init();}
        
    Aho(vector<string>& keywords)
    {
        init();
        for(int i=0;i<keywords.size();i++)insert(keywords[i]);
        build_failure();
    }
        
    void insert(const string& word)
    {// 插入关键词树 Code8
        tnode* cur=root;
        for(int i=0;i<word.length();i++){
            if(!cur->go[idx[word[i]]])cur->go[idx[word[i]]]=newnode();
            cur=cur->go[idx[word[i]]];
        }
        if(cur->cnt<1)//不允许重复
            cur->output.push_back(word);
        cur->cnt=1;
        //cur->cnt++; //允许重复 
    }
        
    void build_failure()
    {// 计算失败函数 Code11 
        queue<tnode*> q;
        root->fail=NULL;
        q.push(root);
        while(!q.empty()){
            tnode* cur=q.front();
            q.pop();
            for(int i=0;i<dsize;i++)
                if(cur->go[i]){
                    tnode* p=cur->fail;
                    while(p && !p->go[i])p=p->fail;
                    if(p){
                        cur->go[i]->fail=p->go[i];
                        cur->go[i]->cnt=addout(cur->go[i],p->go[i]);
                    }
                    q.push(cur->go[i]);
                }
                else cur->go[i]=cur==root?root:cur->fail->go[i];
        }
    }
        
    void outout(tnode *p)
    {
        for(int i=0;i<p->output.size();i++)cout<<p->output[i]<<endl;
    }

    int mult_search(const string& text) 
	{// AC自动机多子串搜索 Code13 
        int cnt=0;
        tnode *cur=root;
	    for(int i=0;i<text.length();i++){
		    while (!cur->go[idx[text[i]]])cur=cur->fail;
	        cur=cur->go[idx[text[i]]];
			cnt+=cur->cnt;
	    } 
	    return cnt;      
    }
       
};

#endif
