const int INF = 9999999999;
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
#define MAX 100000
char yard[100][100];
int dis[100][100];
int sx, sy;
int es, ey;
int n, m;
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};
int bfs()
{
    for (int i = 0; i < n; i++)
    {
        memset(dis[i], INF, sizeof(dis[i]));
    }
    queue<pair<int, int>> q;
    q.push(make_pair(sx, sy));
    while (q.empty() == 0)
    {
        int x=q.front().first;
        int y=q.front().second;
        q.pop();
        if (x==es&&y==ey){
            return dis[x][y];
        }
        for (int i=0;i<4;i++){
            int nx=x+dx[i];
            int ny=y+dy[i];
            if (nx>=0&&nx<n&&ny>=0&&ny<m&&yard[nx][ny]=='.'&&dis[nx][ny]==INF){
                dis[nx][ny]=dis[x][y]+1;
                q.push(make_pair(nx,ny));
            }
        }
    }
}
int main(){
    cin>>n>>m;
    for (int i=0;i<n;i++){
        for (int j=0;j<m;j++){
            cin>>yard[i][j];
        }
    }
    cin>>sx>>sy>>es>>ey;
    cout<<bfs()<<endl;
}