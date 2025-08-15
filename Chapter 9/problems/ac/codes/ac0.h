#ifndef Aho_
#define Aho_

#define nsize 8001        //结点池 size 
#define dsize 26         //字符集 size  
#define idsize 256   

typedef struct node
{
    int    cnt; //output 计数 
    int    state; //状态标号   
    node* fail;
    node* go[dsize];
    vector<string> output;
}tnode;

class Aho
{
private:
    int    size;
    tnode* root;
    int idx[idsize]; 
    tnode nmap[nsize+1];// 防内存泄漏自建结点池 
tnode* Q[nsize+1];
        
    void index()
    {// 预先计算idx Code9
        for(int i=0;i<dsize;i++)idx['a'+i]=i;
    }
        
    tnode* newnode()
    {// 建立新的状态结点 Code10 
        nmap[size].cnt=0;
        nmap[size].state=size;
        nmap[size].fail=root;
        return &nmap[size++];
    }
        
    void init()
    {
        index();
        memset(nmap,0,sizeof(nmap));
        root=NULL;size=0;root=newnode();
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
                    cur->go[i]->fail=p?p->go[i]:root;
                    if(p){
                        cur->go[i]->fail=p->go[i];
                        cur->go[i]->cnt=addout(cur->go[i],p->go[i]);
                    }
                    q.push(cur->go[i]);
                }
                else cur->go[i]=cur==root?root:cur->fail->go[i];//构建 Trie图 
        }
    }
            
    void outout(tnode *p)
    {
        for(int i=0;i<p->output.size();i++)cout<<p->output[i]<<endl;
    }

    tnode* findNxt(tnode *cur, char nxt) 
    { 
	    tnode *v=cur; 
	    // If goto is not defined, use failure function 
	    while (!v->go[idx[nxt]])v=v->fail;
	    return v->go[idx[nxt]];
    } 
    
    int mult_search0(const string& text) 
	{// AC自动机多子串搜索 Code13 
        int cnt=0;
        tnode *cur=root;
        for(int i=0;i<text.length();++i)
            if(cur->go[idx[text[i]]]!=root){
                cur=cur->go[idx[text[i]]];
                if(cur->cnt)cnt+=cur->cnt,outout(cur);
            }
        return cnt;
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
        
    void outtree() 
    {
        cout<<size<<endl;
        for(int i=0;i<size;i++){
            int f=-1;
            if(nmap[i].fail)f=nmap[i].fail->state;
            cout<<"i="<<i<<" f="<<f<<endl;
            outout(&nmap[i]);
        }
    }
};

#endif
