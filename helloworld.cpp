#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    typedef vector< vector<int> > matmul;
    matmul ope(matmul f1,matmul f2)
    {
        matmul mid(f1);
        for(int i = 0; i < f1.size() ; i++)
        {
            for(int j = 0; j < f1[0].size() ; j++)
            {
                mid[i][j] = 0;
                for(int k = 0; k < f1.size() ; k++)
                {
                    mid[i][j] += f1[i][k] * f2[k][j] ;
                }
            }
        }
        // cout<<"=============\n";
        // print(f1);
        // print(f2);
        // print(mid);
        return mid;
    }
    matmul qp(matmul f, int x)
    {
        matmul ans = f;
        for(int i = 0 ; i < f.size() ; i++)
        for(int j = 0 ; j < f.size() ; j++)
            if(i == j)
                ans[i][j] = 1;
            else
                ans[i][j] = 0;
        
        while(x)
        {
            if(x&1)
            {
                ans = ope(ans , f);
            }
            f = ope(f,f);
            x >>= 1;
        }

        return ans;
    }
    int fib(int n) {
        if(n == 0)
            return 0;
        if(n == 1)
            return 1;
        matmul factor = {{1,1} , {1,0}};
        factor = qp(factor, n - 1);
        return factor[0][0];
    }

    void print(matmul f)
    {
        cout<<endl;
        cout<<f[0][0]<<"\t"<<f[0][1]<<"\n"<<f[1][0]<<"\t"<<f[1][1]<<"\n";
        cout<<endl;
    }
};

int main()
{
    Solution solution;
    cout<<solution.fib(5)<<endl;
}