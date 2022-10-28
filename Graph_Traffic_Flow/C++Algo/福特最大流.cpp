// C++ program for implementation of Ford Fulkerson algorithm
#include <iostream>
#include <limits.h>
#include <string.h>
#include <queue>
#include <ctime>
using namespace std;
// Number of vertices in given graph
#define V 39


/* Returns true if there is a path from source 's' to sink 't' in
  residual graph. Also fills parent[] to store the path */
bool bfs(int rGraph[V][V], int s, int t, int parent[])
{
    // Create a visited array and mark all vertices as not visited
    bool visited[V];
    memset(visited, 0, sizeof(visited));
    // Create a queue, enqueue source vertex and mark source vertex as visited
    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    // Standard BFS Loop
    int u;
    while (!q.empty())
    {
        // edge: u -> v
        u = q.front();  // head point u
        q.pop();
        for (int v = 0; v < V; ++v)  // tail point v
        {
            if (!visited[v] && rGraph[u][v] > 0)  // find one linked vertex
            {
                q.push(v);
                parent[v] = u;  // find pre point
                visited[v] = true;
            }
        }
    }
    // If we reached sink in BFS starting from source, then return true, else false
    return visited[t] == true;
}

// Returns the maximum flow from s to t in the given graph
int fordFulkerson(int graph[V][V], int s, int t)
{
    int u, v;
    int rGraph[V][V];

    for (u = 0; u < V; ++u)
    {
        for (v = 0; v < V; ++v)
        {
            rGraph[u][v] = graph[u][v];
        }
    }
    int parent[V];
    int max_flow = 0;
    // Augment the flow while tere is path from source to sink
    while (bfs(rGraph, s, t, parent))
    {
        // edge: u -> v
        int path_flow = INT_MAX;
        for (v = t; v != s; v = parent[v])
        {
            // find the minimum flow
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }
        // update residual capacities of the edges and reverse edges along the path
        for (v = t; v != s; v = parent[v])
        {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;  // assuming v->u weight is add path_flow
        }
        // Add path flow to overall flow
        max_flow += path_flow;
    }

    return max_flow;
}
int main()
{
	FILE *fps,*fpt,*fpw;
	fps=fopen("s.txt","r"); fpt=fopen("t.txt","r"); fpw=fopen("final.txt","r");
	int a,b,c;
	int graph[V][V]={0};
  int n=39,m=124;
	int s=1,t=39;
	printf("%d个结点，%d条边\n",n,m);
	for(int i=0;i<m;i++)
	{
		fscanf(fps,"%d",&a); fscanf(fpt,"%d",&b); fscanf(fpw,"%d",&c);
		graph[a-1][b-1]=c;
	}

	double start=clock();		//程序开始计时
	auto flow=fordFulkerson(graph,s-1,t-1);
	double end=clock();		//程序结束用时

  printf("从%d到%d的最大流量为：%d\n",s,t,flow);
	double endtime=(double)(end-start)/CLOCKS_PER_SEC;
	//cout<<"Total time:"<<endtime<<endl;		//s为单位
	cout<<"O(VE)算法执行用时："<<endtime*1000<<" ms"<<endl;	//ms为单位
	fclose(fps);  fclose(fpt);  fclose(fpw);
  return 0;
}
