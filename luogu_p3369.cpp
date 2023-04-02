#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::min;

#define MAXNUM 15000000

struct NODE
{
    int cnt;
    int size;
    int val;
    NODE *lef;
    NODE *rig;

    NODE(int val) :  cnt(1),size(1),val(val),lef(nullptr),rig(nullptr)
    {}

};

class TREAP
{
private:


    void delAll(NODE *node);

public:
    NODE *root;

    void addNode(int val,NODE *&root);
    void remNode(int val,NODE *&root);
    int findRank(int val,NODE *root);
    int findVal(int rank,NODE *root);
    int findBef(int val,NODE *root);
    int findAft(int val,NODE *root);

    NODE remMaxNode(NODE *&root);



    TREAP()
    {
        root = nullptr;
    }

    ~TREAP()
    {
        if(root != nullptr)
            delAll(root);
    }

};

void TREAP::delAll(NODE *node)
{
    if(node -> lef != nullptr)
        TREAP::delAll(node -> lef);
    if(node -> rig != nullptr)
        TREAP::delAll(node -> rig);
    // NODE *mid = node;
    delete node;
    node = nullptr;
}

void TREAP::addNode(int val,NODE *&root)
{
    if(root == nullptr)
    {
        root = new NODE(val);
        return;
    }
    root -> size ++;
    if(root -> val == val)
    {
        root -> cnt ++;
    }
    else if(root -> val < val)
    {
        TREAP::addNode(val,root -> rig);
    }
    else if(root -> val > val)
    {
        TREAP::addNode(val,root -> lef);
    }
}

void TREAP::remNode(int val,NODE *&root)
{
    if(root == nullptr)
    {
        printf("error,node is not exist\n");
        return ;
    }
    root -> size --;
    if(val < root -> val)
    {
        TREAP::remNode(val , root -> lef );
    }
    else if(root -> val < val)
    {
        TREAP::remNode(val , root -> rig);
    }
    else
    {
        if(root -> cnt > 1)
        {
            root -> cnt --;
            return ;
        }
        if(root -> lef == nullptr && root -> rig == nullptr)
        {
            delete root;
            root = nullptr;
            return ;
        }
        if(root -> lef == nullptr )
        {
            NODE *mid = root -> rig;
            delete root;
            root = mid;
            return;
        }
        if(root -> rig == nullptr )
        {
            NODE *mid = root -> lef;
            delete root;
            root = mid;
            return;
        }

        NODE midNode = remMaxNode(root -> lef);
        root -> val = midNode.val;
        root -> cnt = midNode.cnt;
        if(root -> lef == nullptr)
            root -> size = root -> rig -> size + root -> cnt;
        else
            root -> size = root -> lef -> size + root -> rig -> size + root -> cnt;


   }
}

NODE TREAP::remMaxNode(NODE *&root)
{
    if(root -> rig == nullptr)
    {
        NODE midNode = *(root );
        
        NODE *node = root;
        delete node;

        root = root -> lef;
        return midNode;
    }
    NODE midNode = remMaxNode(root -> rig);
    root -> size -= midNode.cnt;
    return midNode;
}



int TREAP::findRank(int val,NODE *root)
{
    if(root == nullptr)
    {
        printf("val is not exist\n");
        return -1;
    }
    if(root -> val == val)
    {
        return root -> lef == nullptr ? 1 : (root -> lef -> size + 1);
    }
    if(val < root -> val)
    {
        return TREAP::findRank(val , root -> lef);
    }
    if(root -> val < val)
    {
        if(root -> lef == nullptr)
            return root -> cnt + TREAP::findRank(val , root -> rig) ;
        else
            return root -> lef -> size + root -> cnt + TREAP::findRank(val , root -> rig) ;
    }
}

int TREAP::findVal(int rank ,NODE *root)
{
    int lefSize = root -> lef == nullptr ? 0 : root -> lef -> size;
    if(rank <= lefSize )
    {
        return TREAP::findVal(rank,root -> lef);
    }
    else if( lefSize < rank && rank <= lefSize + root -> cnt )
    {
        return root -> val;
    }
    else
    {
        return TREAP::findVal(rank - lefSize - root -> cnt ,root -> rig);
    }
}

int TREAP::findBef(int val ,NODE *root)
{
    if(root == nullptr)
    {
        return -MAXNUM;
    }
    if(val <= root -> val)
    {
        if(root -> lef == nullptr)
        {
            return -MAXNUM;
        }
        return TREAP::findBef(val , root -> lef);
    }
    if(root -> val < val)
    {
        if(root -> rig == nullptr)
            return root -> val ;
        return max(root -> val , findBef(val , root -> rig));
    }
}

int TREAP::findAft(int val ,NODE *root)
{
    if(root == nullptr)
    {
        return MAXNUM;
    }
    if(root -> val <= val)
    {
        if(root -> rig == nullptr)
        {
            return MAXNUM;
        }
        return TREAP::findAft(val , root -> rig);
    }
    if(val < root -> val)
    {
        if(root -> lef == nullptr)
            return root -> val ;
        return min(root -> val , findAft(val , root -> lef));
    }
}


int main()
{
    TREAP treap;
    int n;
    cin>>n;
    for(int i = 1; i <= n ; i ++)
    {
        int mid;
        int x;
        cin>>x;
        switch(x)
        {
        case 1 :
            cin >> mid;
            treap.addNode(mid,treap.root);
            break;
        case 2 :
            cin >> mid;
            treap.remNode(mid,treap.root);
            break;
        case 3 :
            cin >> mid;
            cout << treap.findRank(mid,treap.root)<<endl;
            break;
        case 4 :
            cin >> mid;
            cout << treap.findVal(mid,treap.root)<<endl;
            break;
        case 5 :
            cin >> mid;
            cout << treap.findBef(mid,treap.root)<<endl;
            break;
        case 6 :
            cin >> mid;
            cout << treap.findAft(mid,treap.root)<<endl;
            break;
        }

    }
    return 0;
}
