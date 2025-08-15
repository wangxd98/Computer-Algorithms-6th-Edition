class suffix
{
private:
    string *t,*suff;
    int n,*sa;
public:
    suffix(string txt){
      n=txt.length();
      t=new string[n];suff=new string[n];sa=new int[n];
      for(int i=0;i<n;i++)t[i]=txt[i];
      for(int i=0;i<n;i++)sa[i]=i;
      build();
    }

    void build(){
      for(int i=0;i<n;i++){
        string text="";
        for(int j=i;j<n;j++)text+=t[j];
        suff[i]=text;
      }
      for(int i=1,j;i<n;i++){
        string key=suff[i];
        int idx=sa[i];
        for(j=i-1;j>=0;j--)
          if(suff[j].compare(key)>0){
            suff[j+1]=suff[j];sa[j+1]=sa[j];
          }
          else break;
        suff[j+1]=key;sa[j+1]=idx;
      }
    }
    
    void out()
    {
    	for(int i=0;i<n;i++)
    		cout<<i<<" : "<<sa[i]<<" "<<suff[i]<<endl;
	}
}; 
