#include <iostream>
#include <vector>
#include <stack>
#include <cstring>

using std::pair;
using std::make_pair;
using std::vector;
using std::stack;
using std::cin;
using std::cout;
using std::max;
using std::endl;

#define MAXNODE 1500
#define MAXEDGE 50000

vector< pair< int, int > > edge[MAXNODE + 10];

stack <int> topSort;
stack <int> node;

int inDeg[MAXNODE + 10];
int dis[MAXNODE + 10];

int main()
{
    memset(dis,0xff,sizeof(dis));
    int n,m;
    cin >> n >> m;
    for(int i=0;i<m;i++)
    {
        int u,v,w;
        cin >> u >> v >> w;
        edge[n].push_back( make_pair(v,w) );
        inDeg[v] ++;
    }
    for(int i = 1;i<= n;i++)
    {
        if(inDeg[i] == 0)
        {
            node.push(i);
        }
    }
    while(!node.empty())
    {
        int midNode = node.top();
        node.pop();
        topSort.push(midNode);
        for(auto i : edge[midNode])
        {
            inDeg[i.first]--;
            if(inDeg[i.first]==0)
            {
                node.push(i.first);
            }
        }
    }
    while(topSort.top() != n)
        topSort.pop();
    dis[n]=0;
    topSort.pop();
    while(!topSort.empty())
    {
        int midNode = topSort.top();
        topSort.pop();
        for(auto i: edge[midNode])
        {
            if(dis[i.first]==-1)
                continue;
            dis[midNode] = max(dis[midNode],dis[i.first] + i.second);
        }
    }
    cout<<dis[1]<<endl;
    return 0;
}

