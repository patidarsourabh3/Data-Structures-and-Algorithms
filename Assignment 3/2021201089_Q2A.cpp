#include<iostream>
#include<vector>
#include<algorithm>
#include <climits>
using namespace std;
vector<vector<string>> ans;

int min_distance(vector<int> &distance, vector<bool> &visited,int n)
{
    int mn =INT_MAX;
    int index =0;
    for(int i=0;i<n;i++)
    {
        if(distance[i]<mn && visited[i]==false)
        {
            mn = distance[i];
            index = i;
        }
    }
    return index;
}
void printPath(vector<vector<int>> v, int src, int des, vector<string> temp)
{
    if(src==des)
    {
        reverse(temp.begin(),temp.end());
        ans.push_back(temp);
        temp.clear();
        return;
    }
    for(auto i: v[src])
    {
        temp.push_back(to_string(i));
        printPath(v,i,des,temp);
        temp.pop_back();
    }
    return;
}
void dijkstra(vector<vector<pair<int,int>>> g,int s, int n,int m)
{   
    vector<bool> visited(n,false);
    vector<int> distance(n,INT_MAX);
    vector<int> previous(n,-1);
    vector<vector<int>> path(n);
    path[s].push_back(s);
    distance[s] = 0;
    for(int i=0;i<n;i++)
    {
        int u = min_distance(distance,visited,n);
        visited[u] = true;
        for(auto it=g[u].begin();it!=g[u].end();it++)
        {
            if(visited[it->first] == false && distance[u]!= INT_MAX && distance[u] + it->second < distance[it->first])
            {
                distance[it->first] = distance[u]+it->second;
                path[it->first].clear();
                path[it->first].push_back(u);  
            }
            if(visited[it->first] == false && distance[u]!= INT_MAX && distance[u] + it->second == distance[it->first])
            {
                //distance[it->first] = distance[u]+it->second;
                path[it->first].push_back(u);  
            }
        }
    }
    // for(int i=0;i<distance.size();i++)
    //     cout<<distance[i]<<" ";
    // cout<<endl;
    // for(int i=0;i<path.size();i++)
    // {
    //     for(int j=0;j<path[i].size();j++)
    //     {
    //         cout<<path[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    ans.clear();
    vector<string> temp;
    temp.push_back(to_string(m));
    printPath(path,m,s,temp);
    temp.clear(); 
    sort(ans.begin(), ans.end());
    // for(int i=0;i<ans.size();i++)
    // {
    //    for(int j=0;j<ans[i].size();j++)
    //         cout<<ans[i][j];
    //     cout<<endl;
    // }
    for(int i=0;i<ans[0].size();i++)
        cout<<ans[0][i]<<" ";
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
    int src;
    cin>>src;
    for(int i=0;i<n;i++)
    {
        if(i!=src)
        { 
            dijkstra(g,i,n,src);
            cout<<endl;
        }
    }
    return 0;
}