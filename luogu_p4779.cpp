#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::pair;
using std::greater;
// using std::heap;
using std::make_pair;

#define MAXEDGE 200000
#define MAXNODE 100000

vector< pair<int,int> > edge[MAXEDGE + 10];

int dis[MAXNODE + 10];

vector< pair<int,int> > nodeHeap;

int main()
{
    int n,m,s;
    cin >> n >> m >> s;
    memset(dis,0x3f,sizeof(dis));

    for(int i=0; i<m; i++)
    {
        int midU,midV,midVal;
        cin >> midU >> midV >> midVal;
        edge[midU].push_back( make_pair( midV, midVal ) );
    }
    dis[s] = 0;
    nodeHeap.push_back( make_pair(0,s));

    while(!nodeHeap.empty())
    {
// puts("!");
        auto midNode = nodeHeap[0];
        pop_heap(nodeHeap.begin() , nodeHeap.end() ,greater<pair<int,int> >());
        nodeHeap.pop_back();
        if(dis[midNode.second] != midNode.first)
            continue;
        int node = midNode.second;
        for(auto i : edge[node])
        {
            // int nextNode = i.first;
            if(dis[node] + i.second < dis[i.first] )
            {
                dis[i.first] = dis[node] + i.second;
                nodeHeap.push_back(make_pair(dis[i.first],i.first));
                push_heap(nodeHeap.begin(),nodeHeap.end(),greater< pair<int,int> >());
            }
        }
    }

    for(int i=1;i<=n;i++)
        cout<<dis[i]<<" ";
    puts("");
    return 0;
}

