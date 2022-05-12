#include <iostream>
#include <vector>
#include <string>
#include <map>
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
int longestSubstrKtimes(string str, int k)
{
    vector<int> sa = suffix_array(str);
    int len = str.length();
    string ans ="";
    for(int i=0;i<len-k+1;i++)
    {
        int p = sa[i];
        int q = sa[i+k-1];
        string temp ="";
        while(str[p]==str[q] && p<len && q<len)
        {
            temp = temp + str[p];
            p++;
            q++;
        }
        if(ans.length()<temp.length())
            ans = temp;
    }
    if(ans.length()==0)
        return -1;
    return ans.length();
}
int main()
{
    string str;
    cin>>str;
    int k;
    cin>>k;
    cout<<longestSubstrKtimes(str,k)<<endl;
    return 0;
}
