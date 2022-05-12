#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

vector<int> suffix_array(string str)
{
    vector<int> sa;
    map<string, int> mp;
    string temp ="";
    for(int i=str.length()-1;i>=0;i-- )
    {
        temp = str[i]+ temp;
        mp[temp] = i;
    }
    for(auto m:mp)
    {
        sa.push_back(m.second);
    }
    return sa;
}

vector<int> kasai(string str, vector<int> sa)
{
    int n = sa.size();
    vector<int> lcp(n, 0);
    vector<int> invSuff(n, 0);
    for (int i=0; i < n; i++)
        invSuff[sa[i]] = i;
    int k = 0;
    for (int i=0; i<n; i++)
    {
        if (invSuff[i] == n-1)
        {
            k = 0;
            continue;
        }
        int j = sa[invSuff[i]+1];
        while (i+k<n && j+k<n && str[i+k]==str[j+k])
            k++;
 
        lcp[invSuff[i]] = k; 
        if (k>0)
            k--;
    }
    return lcp;
}
bool isPalindrome(string s)
{
    string r = s;
    reverse(r.begin(),r.end());
    if(r!=s)
        return false;
    return true;
}
string maxPalindrome(string str)
{
    
    int len = str.length();
    if(isPalindrome(str))
        return str;
    string rev = str;
    reverse(rev.begin(),rev.end());
    str = str +"$" + rev; 
    vector<int> sa = suffix_array(str);
    vector<int> lcp = kasai(str,sa);
    int ans = 0;
    int index = 0;
    for(int i=0;i<str.length()-1;i++)
    {
        if(lcp[i]>ans)
        {
            if(sa[i]<len && sa[i+1]>len)
            {
                ans = lcp[i];
                index = sa[i];
            }
            else if (sa[i]>len && sa[i+1]<len)
            {
                ans = lcp[i];
                index = sa[i+1];
            }
        }
    }
    string fans=str.substr(index,ans);
    return fans;
}
int main()
{
    string str;
    cin>>str;
    cout<<maxPalindrome(str)<<endl;
    return 0;
}



