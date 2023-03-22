#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using std::endl;
using std::cin;
using std::cout;
using std::vector;
using std::pair;
using std::make_pair;
using std::greater;

#define MAXNODE 5000
#define MAXEDGE 200000

struct EDGE
{
    int val;
    int nodeA;
    int nodeB;
    EDGE *nextA;
    EDGE *nextB;
    EDGE()
    {
        nextA = nullptr;
        nextB = nullptr;
    }
};


struct NODE
{
    EDGE *firstEdge;
    NODE ()
    {
        firstEdge = nullptr;
    }
};


NODE node[MAXNODE + 10];

bool ifAdd[MAXNODE + 10];

vector< pair< int, int > > set;

void addEdge(int nodeA, int nodeB, int val )
{
    EDGE *edge = new EDGE;
    edge -> val = val;
    edge -> nodeA = nodeA;
    edge -> nodeB = nodeB;

    if(node[nodeA].firstEdge != nullptr)
        edge -> nextA = node[nodeA].firstEdge;
    node[nodeA].firstEdge = edge;


    if(node[nodeB].firstEdge != nullptr)
        edge -> nextB = node[nodeB].firstEdge;
    node[nodeB].firstEdge = edge;

}


int main()
{
    int n,m;
    cin>>n>>m;
    for(int i=0;i<m;i++)
    {
        int midx,midy,midz;
        cin  >> midx >> midy >> midz ;
        addEdge(midx,midy,midz);
    }

    int countLen = 0;

    set.push_back( make_pair(0,1) );

    while( !set.empty() ) 
    {
        int midNode = 1;
        int flag = 1;
        while( !set.empty() )
        {
            pair <int,int> mid = *( set.begin() );
            pop_heap(set.begin() , set.end() , greater< pair<int,int> >() );
            set.pop_back();
            midNode = mid.second;
            if( ifAdd[midNode] )
                continue;
            countLen += mid.first;
            ifAdd[midNode] = 1;
            flag = 0;
            break;
        }
        

        if(flag)
            break;
        

        ifAdd[midNode] =1;
        for( EDGE *edge = node[midNode].firstEdge ; edge != nullptr ; edge = ( ( midNode == edge -> nodeA ) ? edge -> nextA : edge -> nextB ) )
        {
            int nextNode = (edge -> nodeA) ^ (edge -> nodeB) ^ (midNode);
            if( ifAdd[nextNode] )
                continue;
            set.push_back(make_pair(edge -> val , nextNode ) );
            push_heap(set.begin(),set.end(),greater< pair<int,int> >() );
        }

    }
    
    for(int i = 1 ; i <= n ; i++)
    {
        if( !ifAdd[i] )
        {

            cout << "orz" << endl;
            return 0;
        }
    }

    cout << countLen << endl;

    return 0;
}