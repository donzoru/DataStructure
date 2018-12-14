#include<bits/stdc++.h>
using namespace std;
const int M = 10;
int t[M];
int l[M],r[M];
int lt[M],rt[M];
void init()
{
    srand(time(NULL));
    cout<<"             ";
    for(int i=1;i<M;++i)
        cout<<i<<' ';
    cout<<endl;
    cout<<"tree array : ";
    for(int i=1;i<M;++i)
    {
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

void inorderWithout()
{
    cout<<"Unthreaded Inorder Traversal : ";
    stack<int> s;
    int p = 1;
    while(s.size() || p)
    {
        while(p)
        {
            s.push(p);
            p = l[p];
        }
        if(s.size())
        {
            p = s.top(); s.pop();
            cout<<t[p]<<' ';
            p = r[p];
        }
    }
    cout<<endl;
}

void inThread(int p,int &pre)
{
    if(p)
    {
        inThread(l[p],pre);
        if(l[p]==0)
        {
            l[p] = pre;
            lt[p] = 1;
        }
        if(pre && r[pre]==0)
        {
            r[pre] = p;
            rt[pre] = 1;
        }
        pre = p;
        inThread(r[p],pre);
    }
}

void creatInThread(int p)
{
    int pre = 0;
    if(p)
    {
        inThread(p,pre);
        r[pre] = 0;
        rt[pre] = 1;
    }
}

int First(int p)
{
    while(lt[p]==0)
        p = l[p];
    return p;
}

int Next(int p)
{
    if(rt[p]==0)
        return First(r[p]);
    return r[p];
}

void inorderWith()
{
    cout<<"Threaded Inorder Traversal :   ";
    for(int p = First(1);p;p=Next(p))
        cout<<t[p]<<' ';
    cout<<endl;
}

int main()
{
    init();
    inorderWithout();
    creatInThread(1);
    inorderWith();
}
