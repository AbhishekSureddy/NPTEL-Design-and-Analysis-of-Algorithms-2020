#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <numeric>

using namespace std;

int main()
{
    int n, m, k;
    // n -- number of cities
    // m -- number of roads
    // k -- number of months
    cin >> n >> m >> k;
    // creating adjacency lists for n cities
    vector<vector<int>> outList(n+1);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        // undirected roads
        cin >> u >> v;
        outList[u].push_back(v);
        outList[v].push_back(u);
    }
    // testing the code till now
//    for (int i =0; i < n+1; i++)
//    {
//        for (int j = 0; j < outList[i].size(); j++)
//            cout << outList[i][j] << " ";
//        cout <<endl;
//    }
    // museums
    int museums[n+1];
    museums[0] = 0;
    for (int i = 1; i < n+1; i++)
        cin >> museums[i];
    //cout << "museums done"<<endl;
    bool visited[n+1] = {false};
    visited[0] = true;
    vector <int> connected_components;// museum count for connection components
    int status = true;
    int city = 1;
    while (status)
    {
        queue<int> q;
        q.push(city);
        visited[city] = true;
        int temp = 0;
        while(!q.empty())
        {
            temp += museums[q.front()];
            for (int i = 0; i < outList[q.front()].size(); i++)
                if (visited[outList[q.front()][i]] == false) {
                    q.push(outList[q.front()][i]);
                    visited[outList[q.front()][i]] = true;
                }
            q.pop();
        }
        connected_components.push_back(temp);
        int i;
        //finding next component's city of
        for (i = city+1; i < n+1; i++  )
        {
            if (visited[i]== false) {
                    city = i;
                    break;
            }
        }
        if(i == n+1) status = false;
    }

    if (k > connected_components.size()) cout << -1 << endl;
    else
    {
        sort(connected_components.begin(),connected_components.end());
        int idx = connected_components.size();
        cout << accumulate(connected_components.begin(),connected_components.begin()+floor(k/2),0)
        + accumulate(connected_components.begin()+idx-ceil(k*1.0/2),connected_components.end(),0)<<endl;
    }


    return 0;
}
