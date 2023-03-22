#include <bits/stdc++.h>
using namespace std;

#define MAXLENGTH 1000010

char s1[MAXLENGTH];
char s2[MAXLENGTH];
int Next[MAXLENGTH];
int Nextptr[MAXLENGTH];
int s1len;
int s2len;

void makeNext(int len)
{
    Next[0]=0;
    for(int i=1;i<len;i++)
    {
        int lastLen = Next[i-1];
        while(lastLen!=0 && s2[i]!=s2[lastLen])
        {
            lastLen = Next[lastLen-1];
        }
        Nextptr[i]=Next[i]=lastLen + (bool)(s2[i]==s2[lastLen]);
    }

    for(int i=1;i<len;i++)
    {
        if(s2[i+1]==s2[Next[i]])
        {
            Nextptr[i] = Nextptr[Nextptr[i]-1];
        }
    }

}

int main()
{
    // cin>>s1>>s2;
    scanf("%s%s",s1,s2);
    s1len = strlen(s1);
    s2len = strlen(s2);

    makeNext(s2len);

    int i=0,j=0;
    while(i<s1len)
    {

        if(s2[j] == s1[i])
        {
            i++;
            j++;
        }
        else
        {
            if(j)
                j=Nextptr[j-1];
            else
            {
                i++;
            }
        }

        if(j==s2len)
        {
            cout<<i-s2len+1<<endl;

        }
        
    }

    for(int i=0;i<s2len;i++)
        cout<<Next[i]<<" ";
    cout<<endl;
    return 0;
}