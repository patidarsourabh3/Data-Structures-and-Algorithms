#include<iostream>
#include<string.h>
using namespace std;
char grid[10][10];
int m,n;
class TrieNode
{
  public:
    TrieNode *c[26];
    bool Leaf;
    TrieNode()
    {
        for(int i=0;i<26;i++)
        {
            c[i] = NULL;
        }
        Leaf = false;
    }
    TrieNode *head = NULL;
    void insert(string s)
    {
        if(head==NULL)
        {
            TrieNode* temp = new TrieNode();
            head = temp;
        }
        TrieNode* curr = head;
        for(int i=0;i<s.length();i++)
        {
            if(curr->c[s[i]-'a']==NULL)
            {
                curr->c[s[i]-'a'] = new TrieNode();
            }
            curr = curr->c[s[i]-'a'];
        }   
        curr->Leaf = true;
    }
    bool dfs(int i, int j, int c,string word)
    {
        if(c==word.length())
            return true;
        if(i<0 || i>=m ||j<0 || j>=n || grid[i][j] != word[c] )
            return false;
        char z = grid[i][j];
        grid[i][j] = '*';
        bool r = dfs(i+1,j,c+1,word);
        bool l = dfs(i-1,j,c+1,word);
        bool t = dfs(i,j-1,c+1,word);
        bool d = dfs(i,j+1,c+1,word);
        grid[i][j] = z;
        if(r||l||t||d)
            return true;
        return false;
    }
    void searchWord()
    {
        string temp;
        printWords(head,temp);
    }
    void printWords(TrieNode* curr, string temp)
    {
        if(curr == NULL)
            return;
        if(curr->Leaf==true)
        {
            bool y = false;
            for(int i=0;i<m;i++)
            {
                for(int j=0;j<n;j++)
                {
                    if(grid[i][j]==temp[0])
                    {
                        y = dfs(i,j,0,temp);
                        if(y)
                        {
                            cout<<temp<<" ";
                            break;
                        }
                    }
                }
                if(y)
                    break;
            }
        }
        for(int i=0; i<26; i++)
        {
            if(curr->c[i] != NULL)
            {
                char z = i +'a';
                printWords(curr->c[i], temp+z);
            }
        }
    }
};
int main()
{
    cin>>m>>n;
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            cin>>grid[i][j];
        }
    } 
    TrieNode t;
    int k;
    cin>>k;
    for(int i=0;i<k;i++)
    {  
        string s;
        cin>>s;
        t.insert(s);
    }
    t.searchWord();
    return 0;
}
