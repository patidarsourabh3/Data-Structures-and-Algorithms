#include<iostream>
#include<queue>
#include<vector>
#include<climits>
using namespace std;

void bfs(vector<vector<int>> &res, int i, int j, int c)
{
    queue<pair<int,int>> q;
    q.push({i,j});
    res[i][j] = 1;
    while(!q.empty())
    {
        pair<int,int> p = q.front();
        q.pop();
        int x = p.first;
        int y = p.second;
        if(res[x][y-1]!=-1 && res[x][y-1]==0)
        {
            res[x][y-1] = res[x][y]+1;
            q.push({x,y-1});
        }
        if(res[x-1][y]!=-1 && res[x-1][y]==0)
        {
            res[x-1][y] = res[x][y]+1;
            q.push({x-1,y});
        }       
        if(res[x][y+1]!=-1 && res[x][y+1]==0)
        {
            res[x][y+1] = res[x][y]+1;
            q.push({x,y+1});
        }       
        if(res[x+1][y]!=-1 && res[x+1][y]==0)
        {
            res[x+1][y] = res[x][y]+1;
            q.push({x+1,y});
        }
    }
}
int main()
{
    int m,n;
    cin>>m>>n;
    vector<vector<char>> grid(m,vector<char>(n));
    vector<pair<int,int>> bikes;
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            cin>>grid[i][j];
        }
    }
    vector<vector<int>> res(m,vector<int>(n));
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(grid[i][j]=='#')
                res[i][j] = -1;
            else
                res[i][j] = 0;
            if(grid[i][j]=='R')
                bikes.push_back({i,j});
        }
    }
    res[1][0] = -1;
    bfs(res,1,1,1);
    int mx = INT_MAX;
    for(int i=0;i<bikes.size();i++)
    {
        mx = min(mx,res[bikes[i].first][bikes[i].second]);
    }
    if(res[m-2][n-2]!=0 && (mx>=res[m-2][n-2] || mx==0))
        cout<<"YES"<<endl<<res[m-2][n-2];
    else
        cout<<"NO"<<endl;
    return 0;
}

