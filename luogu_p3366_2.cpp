#include <iostream>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::sort;
// using std::pair;

#define MAXEDGE 200000
#define MAXNODE 5000

// pair<int, int> edge[MAXEDGE + 10 ];

struct EDGE
{
    int nodeA;
    int nodeB;
    int val;
};
EDGE edge[MAXEDGE + 10];

int parents[MAXNODE + 10];

bool cmp(EDGE A, EDGE B)
{
    return A.val < B.val;
}
int findP(int x)
{
    if(parents[x] == 0)
        return x;
    if(parents[ parents[x] ] != 0 )
        parents[x] = findP(parents[x]);
    return parents[x];

}

int main()
{
    int n,m;
    cin >> n >> m;
    for(int i = 0; i < m; i++)
    {
        cin >> edge[i].nodeA >> edge[i].nodeB >> edge[i].val ;
    }
    sort(edge,edge+m,cmp);
    int cntLen = 0;
    int cntN = 0;
    for(int i = 0; i < m; i++)
    {
        int AP = findP(edge[i].nodeA);
        int BP = findP(edge[i].nodeB);
        if(AP == BP)
            continue;
        parents[AP] = BP;
        cntLen+=edge[i].val;
        cntN++;
    }
    if(cntN == n-1)
        cout << cntLen << endl;
    else
        cout << "orz" << endl;
    return 0;
}
