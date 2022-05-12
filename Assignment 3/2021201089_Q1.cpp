#include<iostream>
#include<vector>
#include<math.h>
using namespace std;
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
    bool search(string s)
    {
        if (head == NULL)
            return false;
        TrieNode* curr = head;
        for(int i=0;i<s.length();i++)
        {
            curr = curr->c[s[i]-'a'];
            if (curr == NULL) 
                return false;
        }
        return curr->Leaf;
    }
    void printWords(TrieNode* curr, char* temp, vector<string> &ans,int pos = 0)
    {
        if(curr == NULL)
            return;
        if(curr->Leaf==true)
        {
            string s = "";
            for(int i=0; i<pos; i++)
                s += temp[i];
            ans.push_back(s);
        }
        for(int i=0; i<26; i++)
        {
            if(curr->c[i] != NULL)
            {
                temp[pos] = i+'a';
                printWords(curr->c[i], temp,ans,pos+1);
            }
        }
    }
    vector<string> autocomplete(string s)
    {
        vector<string> ans;
        if(head==NULL)
            return ans;
        TrieNode *curr = head;
        for(int i=0;i<s.length();i++)
        {
            curr = curr->c[s[i]-'a'];
            if(curr==NULL)
                return ans;
        }
        char temp[100];
        printWords(curr,temp,ans);            
        return ans;
    }   
    int lev_distance(string s, string t)
    {
        int m = s.length();
        int n = t.length();
        int dp[m+1][n+1];
        for(int i=0;i<=m;i++)
        {
            for(int j=0;j<=n;j++)
            {
                if(i==0||j==0)
                    dp[i][j] = max(i,j);
                else if(s[i-1]==t[j-1])
                    dp[i][j] = dp[i-1][j-1];
                else
                    dp[i][j] = 1 + min(dp[i-1][j-1], min(dp[i][j-1],dp[i-1][j]));
            }
        }
        return dp[m][n];
    }
    vector<string> autocorrect(string s)
    {
        vector<string> words;
        vector<string> ans;
        char temp[100];
        printWords(head,temp,words);
        for(auto i : words)
        {
            int diff;
            if(i.length()<=s.length())
                diff = s.length()-i.length();
            else
                diff = i.length()-s.length();
            if(diff<=3)
            {           
                int d = lev_distance(s,i);
                if(d<=3)
                    ans.push_back(i);
            }
        }
        return ans;
    }
};
int main()
{
    TrieNode *t = new TrieNode;
    int n;
    cin>>n;
    vector<string> v(n);
    for(int i=0;i<n;i++)
        cin>>v[i];
    for(int i=0;i<n;i++)
        t->insert(v[i]);
    int ch;
    cin>>ch;
    string word;
    if(ch==1)
    {
        cin>>word;
        cout<<t->search(word)<<endl;
    }
    if(ch==2)
    {
        cin>>word;
        vector<string> ans = t->autocomplete(word);
        cout<<ans.size()<<endl;
        for(auto i: ans)
            cout<<word+i<<endl;
    }
    if(ch==3)
    {
        cin>>word;
        vector<string> ans = t->autocorrect(word);
        cout<<ans.size()<<endl;
        for(auto i: ans)
            cout<<i<<endl;
    }
    return 0;
}