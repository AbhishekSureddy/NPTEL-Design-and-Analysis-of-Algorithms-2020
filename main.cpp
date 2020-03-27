#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

#define MAX 100000

using namespace std;
struct Edge
{
    int out;
    int dist;
};

void FindRemove(vector<struct Edge> &v, int from)
{
    int j = 0;
    int status = 0;
    for (; j < v.size(); j++)
    {
        if(v[j].out == from)
            {
                status = 1;
                break;
            }
    }
    if (status) v.erase(v.begin()+j);
}

int ShortPath(vector<vector<struct Edge>> outList, int maxi, int source, int destination)
{
    bool visited[maxi+1] = {false};
    int dist[maxi + 1];
    for (int i = 0; i < maxi+1; i++)
        dist[i] = MAX;
    visited[0] = true;
    // source
    dist[source] = 0;
    // iterating through nodes and finding min dist edge
    for (int i = 1; i < maxi+1; i++)
    {   //if (visited[destination] == true) break;
        int u ;
        int mini = MAX;
        for (int j =1; j< maxi+1; j++)
        {
            if(visited[j]==false && mini > dist[j])
                {
                    mini = dist[j];
                    u = j;
                }
        }
        visited[u] = true;
        for (int j = 0; j < outList[u].size(); j++)
        {
            if (visited[outList[u][j].out] == false)
            {
                int v = outList[u][j].out;
                dist[v] = min(dist[v], dist[u]+ outList[u][j].dist);
            }
        }
    }
    return dist[destination];

}

int main()
{
   vector<vector<struct Edge>> outList(500);
   vector<int> cycles;
   int n;
   int maxi = 0;
   cin >> n;
   for (int i = 0; i < n; i++)
   {
       struct Edge e;
       int v1,v2,d;
        cin >> v1 >> v2 >> d;
        int temp = max(v1,v2);
        maxi = max(maxi, temp);
        e.out = v2;
        e.dist = d;
        outList[v1].push_back(e);
        e.out = v1;
        outList[v2].push_back(e);
   }
   // removing terminal edges
   for (int i = 1; i < maxi+1 ; i++)
   {
       if (outList[i].size() == 1)
       {
           FindRemove(outList[outList[i][0].out], i);
           outList[i].pop_back();
       }
   }

   for (int i = 1; i < maxi+1 ; i++)
   {
        int outs = outList[i].size();
        int j = 0;
        int k = 0;
        while(k <outs)
        {
            if (i < outList[i][j].out)
            {
                struct Edge e = outList[i][j];
                // removing this edge
                FindRemove(outList[outList[i][j].out] , i);
                FindRemove(outList[i],outList[i][j].out);
                // now find the shortest path between i and outList[i][j].out
                int s = ShortPath(outList,maxi,i,e.out);

                if (s < MAX) cycles.push_back(s+e.dist);
                // adding the edge removed
                outList[i].push_back(e);
                e.out = i;
                outList[outList[i][outs-1].out].push_back(e);

            }
            else j++;
            k++;
        }
   }
   cout << *min_element(cycles.begin(), cycles.end())<<'\n';


    return 0;
}
