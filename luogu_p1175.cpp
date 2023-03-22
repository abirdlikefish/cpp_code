#include <bits/stdc++.h>
using namespace std;

#define MAXINPUT 100

char Input[MAXINPUT];

struct node
{
    bool ifOpe;
    int num;
    char ope;
};
node ans1[MAXINPUT];
int ans1Top;

int ans2Stack[MAXINPUT];
int ans2StackTop;

char Stack[MAXINPUT];
int stackTop;

int hashCmp(char x)
{
    switch (x)
    {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '(':
            return 0;
        case ')':
            return 0;
        case '^':
            return 3;
    }
}


void popStack()
{
    ans1[ans1Top].ifOpe = 1;
    ans1[ans1Top].ope = Stack[--stackTop];
    ans1Top++;
}

int main()
{
    fgets(Input,MAXINPUT,stdin);
    for(int i=0;Input[i]!='\n'&&Input[i]!='\0'&&Input[i]!='\r';i++)
    {
        
        if(Input[i]==' ')
            continue;

        switch (Input[i])
        {

            
        case '+':    //1
        case '-':    //2
        case '*':    //3
        case '/':    //4
            while(stackTop!=0&&hashCmp(Stack[stackTop-1]) >= hashCmp(Input[i]) )
            {
                popStack();
            }
            Stack[stackTop] = Input[i];
            stackTop++;
            break;
        case '^':    //5
            while(stackTop!=0&&hashCmp(Stack[stackTop-1]) > hashCmp(Input[i]) )
            {
                popStack();
            }
            Stack[stackTop] = Input[i];
            stackTop++;
            break;
        
        case '(':
            Stack[stackTop] = Input[i];
            stackTop++;
            break;

        case ')':
            while(Stack[stackTop-1]!='(')
                popStack();
            stackTop--;
            break;
        default:
            ans1[ans1Top].ifOpe=0;
            ans1[ans1Top].num=Input[i]-'0';
            ans1Top++;
            break;
        }

    }

    while(stackTop)
        popStack();

    for(int i=0;i<ans1Top;i++)
    {
        if(ans1[i].ifOpe)
            cout<<ans1[i].ope<<" ";
        else
            cout<<ans1[i].num<<" ";
    }
    cout<<endl;

    for(int i=0;i<ans1Top;i++)
    {
        if(ans1[i].ifOpe)
        {
            switch (ans1[i].ope)
            {
                case '+':
                    ans2StackTop--;
                    ans2Stack[ans2StackTop-1]+=ans2Stack[ans2StackTop];
                    break;
                case '-':
                    ans2StackTop--;
                    ans2Stack[ans2StackTop-1]-=ans2Stack[ans2StackTop];
                    break;
                case '*':
                    ans2StackTop--;
                    ans2Stack[ans2StackTop-1]*=ans2Stack[ans2StackTop];
                    break;
                case '/':
                    ans2StackTop--;
                    ans2Stack[ans2StackTop-1]/=ans2Stack[ans2StackTop];
                    break;
                case '^':
                    ans2StackTop--;
                    ans2Stack[ans2StackTop-1]=pow(ans2Stack[ans2StackTop-1],ans2Stack[ans2StackTop]);
                    break;
            }
            for(int j=0; j<ans2StackTop; j++)
                cout<<ans2Stack[j]<<" ";
            for(int j=i+1;j<ans1Top; j++)
            {

                if(ans1[j].ifOpe)
                    cout<<ans1[j].ope<<" ";
                else
                    cout<<ans1[j].num<<" ";
            }
            puts("");
        }
        else
        {
            ans2Stack[ans2StackTop]=ans1[i].num;
            ans2StackTop++;
        }
    }
    return 0;
}
