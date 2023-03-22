#include <iostream>
#include <vector>
#include <cstring>
// #include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::pair;
using std::greater;
using std::make_pair;

#define MAXEDGE 500000
#define MAXNODE 10000

vector< pair<int,int> > edge[MAXEDGE + 10];

int ifInStack[MAXNODE + 10];
int dis[MAXNODE + 10];

class stack 
{
public:
    int data[MAXNODE + 10];
    int ptr;
    int ptrH;
    stack()
    {
        ptrH=0;
        ptr = 0;
    }
    void push_back(int x)
    {
        data[ptr] = x;
        ptr++;
        ptr%=MAXNODE;
    }
    int size()
    {
        return (ptr-ptrH+MAXNODE)%MAXNODE;
    }
    int end()
    {
        return data[ptrH];
    }
    void pop_back()
    {
        ptrH++;
        ptrH%=MAXNODE;
    }
    bool empty()
    {
        return ptrH==ptr;
    }
};

stack nodeStack;


int main()
{
    int n,m,s;
    cin >> n >> m >> s;
    for(int i=0;i<=n;i++)
        dis[i] = (1 << 31) -1;

    for(int i=0; i<m; i++)
    {
        int midU,midV,midVal;
        cin >> midU >> midV >> midVal;
        edge[midU].push_back( make_pair( midV, midVal ) );
    }
    dis[s] = 0;
    nodeStack.push_back(s);
    ifInStack[s]=1;

    while(!nodeStack.empty())
    {
        int node = nodeStack.end();
        nodeStack.pop_back();
        ifInStack[node] = 0;
        for(auto i : edge[node])
        {
            if(dis[node] + i.second < dis[i.first] )
            {
                dis[i.first] = dis[node] + i.second;
                if(!ifInStack[i.first])
                {
                    nodeStack.push_back(i.first);
                    ifInStack[i.first] = 1;
                }
            }
        }
    }

    for(int i=1;i<=n;i++)
        cout<<dis[i]<<" ";
    puts("");
    return 0;
}
