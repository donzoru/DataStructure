#include<bits/stdc++.h>
using namespace std;
const int M = 10;
int t[M];
int l[M],r[M];
int lt[M],rt[M];
void init(){
    //srand(time(NULL));
    cout<<"             ";
    for(int i=1;i<M;++i)
        cout<<i<<' ';
    cout<<endl;
    cout<<"tree array : ";
    for(int i=1;i<M;++i){
        t[i]=rand()%100;
        if(i*2<M) l[i] = i*2,lt[i] = 0;
        else l[i] = 0, lt[i] = 1;
        if(i*2+1<M) r[i] = i*2+1,rt[i] = 0;
        else r[i] = 0,rt[i] = 1;
        cout<<t[i]<<' ';
        //cout<<l[i]<<' '<<r[i]<<endl;
    }
    cout<<endl;
}
void postorderWithout(){
    cout<<"Unthreaded Postorder Traversal : ";
    stack<int> s1,s2;
    int p = 1;
    s1.push(p);
    while(s1.size()){
        p = s1.top(); s1.pop();
        s2.push(p);
        if(l[p]) s1.push(l[p]);
        if(r[p]) s1.push(r[p]);
    }
    while(s2.size()){
        p = s2.top(); s2.pop();
        cout<<t[p]<<' ';
    }
    cout<<endl;
}
void inThread(int p,int &pre){
    if(p){
        inThread(l[p],pre);
        inThread(r[p],pre);
        if(l[p]==0){
            l[p] = pre;
            lt[p] = 1;
        }
        if(pre && r[pre]==0){
            r[pre] = p;
            rt[pre] = 1;
        }
        pre = p;
    }
}
void creatInThread(int p)
{
    int pre = 0;
    if(p){
        inThread(p,pre);
    }
}

void postorderWith(){
    cout<<"Threaded Postorder Traversal :   ";
    stack<int> s;
    int p = 1;
    while(p){
        while(rt[p]==0){
            s.push(p);
            p = r[p];
        }
        s.push(p);
        p = l[p];
    }
    while(s.size()){
        p = s.top(); s.pop();
        cout<<t[p]<<' ';
    }
    cout<<endl;
}
int main(){
    init();
    postorderWithout();
    creatInThread(1);
    postorderWith();
}
