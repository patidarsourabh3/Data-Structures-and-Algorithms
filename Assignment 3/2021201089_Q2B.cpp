#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
vector<string> s = {"0","1","2","3","4","5","6","7","8","9"};
vector<pair<int,string>> ans;
void findAllpaths(vector<vector<pair<int,int>>> g, int src, int des,vector<bool> visited, string path, int wt)
{
    if(src==des)
    {   
        ans.push_back({wt,path});
        return;
    }
    visited[src]=true;
    for(auto it : g[src])
    {
        if(visited[it.first]==false)
        {
            findAllpaths(g,it.first,des,visited,path+s[it.first],wt+it.second);
        }
    }
    visited[src]=false;
}
int main()
{
    int n,m,a,b,c;
    cin>>n>>m;
    vector<vector<pair<int,int>>> g;
    g.assign(n,vector<pair<int,int>>());
    for(int i=0;i<m;i++)
    {
        cin>>a>>b>>c;
        g[a].push_back({b,c});
        g[b].push_back({a,c}); 
    }
    int k;
    cin>>k;
    for(int i=0;i<n-1;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            vector<bool> visited(n,false);
            int wt =0;
            findAllpaths(g,i,j,visited,s[i],wt);
        }
    }
    sort(ans.begin(),ans.end());
    k = k>ans.size()?ans.size():k;
    for(int i=0;i<k;i++)
    {
        for(auto it :ans[i].second)
            cout<<it<<" ";
        cout<<endl;
    }
    return 0;
}

