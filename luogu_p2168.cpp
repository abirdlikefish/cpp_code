#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

#define LL long long 

// (n-1 % k-1)+1

vector< pair<LL,LL> > node;
int main()
{
    int n,k;
    scanf("%d%d",&n,&k);
    for(int i=0;i<n;i++)
    {
        LL mid;
        scanf("%lld",&mid);
        node.push_back( make_pair(mid,0) );
        push_heap(node.begin(),node.end(),greater< pair<LL,LL> >());
    }

    LL len = 0;

    while( node.size() > 1 )
    {
        pair<LL,LL> mid = make_pair( 0 , 0 );

        int branchLen = k;
        if( len == 0 && (n - 1) % (k - 1) != 0 )
        {
            branchLen = (n - 1) % (k - 1) + 1;
        }
        for(int i = 1 ; i <= branchLen && !node.empty() ; i++ )
        {
            pop_heap(node.begin(),node.end(),greater< pair<LL,LL> >() );
            mid.first += ( *(node.end() - 1) ).first;
            mid.second = max( mid.second , ( *(node.end() - 1) ).second );
            node.pop_back();
        }
        mid.second++;
        node.push_back(mid);
        push_heap(node.begin(),node.end(),greater< pair<LL,LL> >() );

        len += mid.first;

    }

    printf("%lld\n%lld\n",len,node[0].second);
    return 0;
}