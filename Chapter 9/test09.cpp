#include <bits/stdc++.h>
using namespace std;
#include "ch09.h"

void tst01()
{
    cout<<"Test naive"<<endl;
    string T="abcdefghijk";
    string P="defg";
    cout<<naive(T,P)<<endl;    
}
/*
Test naive
3
*/

void tst02()
{
    cout<<"Test KMPmatcher"<<endl;
    string T="abcdefghijk";
    string P="defg";
    cout<<KMPmatcher(T,P)<<endl;    
}
/*
Test KMPmatcher
3
*/

void tst03()
{
    cout<<"Test Rabin_Karp0"<<endl;
    string t = "abacadabrabracabracadabrabrabracad";
    string p = "rabrabracad";
    cout<<Rabin_Karp0(t,p)<<endl;    
}
/*
Test Rabin_Karp0
23
*/

void tst04()
{
    cout<<"Test Rabin_Karp"<<endl;
    string t = "abacadabrabracabracadabrabrabracad";
    string p = "rabrabracad";
    cout<<Rabin_Karp(t,p)<<endl;    
}
/*
Test Rabin_Karp0
23
*/

void tst05()
{
    cout<<"Test mult_search"<<endl;
    int n;
	string s,kwd;
    vector<string> keywords;
    cin>>n;
	for(int i=0;i<n;i++){
		cin>>kwd;
		keywords.push_back(kwd);
	}
	Aho dd(keywords);
	cin>>s;
	cout<<dd.mult_search(s)<<endl;
}
/*
tst05.in:
3
a
aa
abc
aabcdcbaaab
tst05.out:
Test mult_search
9
*/

void tst06()
{
    cout<<"Test suffix"<<endl;
    string T="AACAAAAC";
	suffix ss(T);
	ss.out();
}
/*
tst06.in:
AACAAAAC
tst06.out:
Test suffix
0 : 3 AAAAC
1 : 4 AAAC
2 : 5 AAC
3 : 0 AACAAAAC
4 : 6 AC
5 : 1 ACAAAAC
6 : 7 C
7 : 2 CAAAAC
*/

void tst07()
{
    cout<<"Test suffix2"<<endl;
    string text;
    cin>>text;
    suffix2 suf(text);
    int *sa=suf.sa;
    for(int i=0;i<text.size();i++)cout<<sa[i]<<" ";cout<<endl;
}
/*
tst07.in:
AACAAAAC
tst07.out:
Test suffix2
3 4 5 0 6 1 7 2 
*/

void tst08()
{
    cout<<"Test suffix3"<<endl;
    string text;
    cin>>text;
    suffix3 suf(text);
    int *sa=suf.sa;
    for(int i=0;i<text.size();i++)cout<<sa[i]<<" ";cout<<endl;
}
/*
tst08.in:
AACAAAAC
tst08.out:
Test suffix3
3 4 5 0 6 1 7 2 
*/

void tst09()
{
    cout<<"Test lcp"<<endl;
    string text;
    cin>>text;
    suffix3 suf(text);
    int *lcp=suf.lcp;
    for(int i=0;i<text.size();i++)cout<<lcp[i]<<" ";cout<<endl;
}
/*
tst09.in:
AACAAAAC
tst09.out:
Test lcp
3 2 3 1 2 0 1 0 
*/

void tst10()
{
    cout<<"Test lce"<<endl;
    int n,l,r;
	string text;
    cin>>text;
    suffix3 suf(text);
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>l>>r;
        cout<<suf.lce(l,r)<<endl;
	}
}
/*
tst10.in:
AACAAAAC
2
1 6
3 4
tst10.out:
Test lce
2
3
*/

void tst11()
{
    cout<<"Test lcss"<<endl;
    string s1,s2;
    while(cin>>s1>>s2) 
        cout<<lcss(s1,s2)<<endl;
}
/*
tst11.in:
AACAAAAC
ACAAAACA
bananabanana
naananbabana
tst11.out:
Test lcss
7
5
*/

void tst12()
{
    cout<<"Test ed"<<endl;
    cin>>x>>y;
	n=x.size();m=y.size();
	cout<<ed()<<endl;
	back(n,m);
}
/*
tst12.in:
intention
execution
tst12.out:
Test ed
5
r(0,0)
r(1,1)
d(2)
r(4,3)
i(4)
*/

void tst13()
{
    cout<<"Test edn"<<endl;
    cin>>x>>y;
	n=x.size();m=y.size();
	cout<<edn()<<endl;
}
/*
tst13.in:
intention
execution
tst13.out:
Test ed
5
*/

void tst14()
{
    cout<<"Test lcis"<<endl;
	cin>>n>>m;
	for(int i=0;i<n;i++)cin>>a[i];
	for(int i=0;i<m;i++)cin>>b[i];
	cout<<lcis()<<endl;
}
/*
tst14.in:
7 6
3 5 1 2 7 5 7
3 5 2 1 5 7
tst14.out:
Test lcis
3
*/

int main() 
{
	//tst01();
	//tst02();
	//tst03();
	//tst04();
	//tst05();
    //tst06();
    //tst07();
    //tst08();
    //tst09();
    //tst10();
    //tst11();
    //tst12();
    //tst13();
    tst14();
	return 0;
}
