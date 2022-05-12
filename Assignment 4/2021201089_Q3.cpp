#include<iostream>
#include<math.h>
using namespace std;
class TrieNode
{
    public:
        TrieNode *left;
        TrieNode *right;
};

void insert(TrieNode *root, long long int x)
{
    TrieNode *curr = root;
    for(int i=63;i>=0;i--)
    {
        int b = (x>>i)&1;
        if(b==0)
        {
            if(curr->left == NULL)
            {
                curr->left = new TrieNode();
            }
            curr = curr->left;
        }
        else
        {
            if(curr->right == NULL)
            {
                curr->right = new TrieNode();
            }
            curr = curr->right;
        }
    }
}

long long int query(TrieNode* root, long long int x)
{
    long long int ans =0;
    TrieNode *curr = root;
    for(int i=63;i>=0;i--)
    {
        int b = (x>>i)&1;
        if(b==0)
        {
            if(curr->right)
            {
                ans += pow(2,i);
                curr = curr->right;
            }
            else
                curr = curr->left;
        }
        else
        {
            if(curr->left)
            {
                ans += pow(2,i);
                curr = curr->left;
            }
            else
                curr = curr->right;
        }
    }  
    return ans;
}
int main()
{
    long long int n,q,x;
    cin>>n;
    cin>>q;
    TrieNode *root = new TrieNode();
    for(long long int i=0;i<n;i++)
    {
        cin>>x;
        insert(root,x);
    }  
    while(q--)
    {
        cin>>x;
        long long int ans = query(root,x);
        cout<<ans<<endl;
    }
    return 0;
}
