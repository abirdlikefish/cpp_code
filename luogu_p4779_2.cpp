#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
// #include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::pair;
using std::greater;
using std::make_pair;
using std::queue;

#define MAXEDGE 500000
#define MAXNODE 10000

vector< pair<int,int> > edge[MAXEDGE + 10];

int ifInStack[MAXNODE + 10];
int dis[MAXNODE + 10];

queue< int > nodeStack;

int main()
{
    int n,m,s;
    cin >> n >> m >> s;
    // memset(dis,0x3f,sizeof(dis));
    for(int i=0;i<=n;i++)
        dis[i] = (1 << 31) -1;

    for(int i=0; i<m; i++)
    {
        int midU,midV,midVal;
        cin >> midU >> midV >> midVal;
        edge[midU].push_back( make_pair( midV, midVal ) );
    }
    dis[s] = 0;
    nodeStack.push(s);
    ifInStack[s]=1;

    while(!nodeStack.empty())
    {
        int node = nodeStack.front();
        nodeStack.pop();
        // nodeStack.pop_back();
        ifInStack[node] = 0;
        for(auto i : edge[node])
        {
            if(dis[node] + i.second < dis[i.first] )
            {
                dis[i.first] = dis[node] + i.second;
                if(!ifInStack[i.first])
                {
                    nodeStack.push(i.first);
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

