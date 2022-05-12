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
string minLexRotation(string str)
{
    str = str+str;
    vector<int> sa = suffix_array(str);
    int index = 0;
    int len = str.length();
    for(int i=0;i<sa.size();i++)
    {
        if(sa[i]<len/2)
        {
            index = sa[i];
            break;
        }
    }
    string ans = str.substr(index, len/2);
    return ans;
}
int main()
{
    string str;
    cin>>str;
    cout<<minLexRotation(str)<<endl;
    return 0;
}
