//狄克斯特拉算法－求单源最短路径
#include "Graph.cpp"
#include<ctime>
int dist[MAXV],path[MAXV];
int S[MAXV];
void Dispath(MGraph g,int dist[],int path[],int S[],int v)
//输出从顶点v出发的所有最短路径
{	int i,j,k;
	int apath[MAXV],d;					//存放一条最短路径(逆向)及其顶点个数
	for (i=0;i<g.n;i++)					//循环输出从顶点v到i的路径
		if (S[i]==1 && i!=v)
		{
			printf("从顶点%3d到顶点%3d的最短路径长度为：%4d，路径为:",v+1,i+1,dist[i]);
			d=0; apath[d]=i;			//添加路径上的终点
			k=path[i];
			if (k==-1)				//没有路径的情况
				printf("无路径\n");
			else						//存在路径时输出该路径
			{
				while (k!=v)
				{	d++; apath[d]=k;
					k=path[k];
				}
				d++; apath[d]=v;		//添加路径上的起点
				printf("%d->",apath[d]);	//先输出起点
				for (j=d-1;j>=1;j--)	//再输出其他顶点
					printf("%d->",apath[j]);
				printf("%d",apath[0]);
				printf("\n");
			}
		}
}
void Dijkstra(MGraph g,int v)			//Dijkstra算法
{
	int mindis,i,j,u;
	for (i=0;i<g.n;i++)
	{	dist[i]=g.edges[v][i];		//距离初始化
		S[i]=0;						//S[]置空
		if (g.edges[v][i]<INF)		//路径初始化
			path[i]=v;				//顶点v到顶点i有边时，置顶点i的前一个顶点为v
		else
			path[i]=-1;				//顶点v到顶点i没边时，置顶点i的前一个顶点为-1
	}
	S[v]=1;path[v]=0;				//源点编号v放入s中
	for (i=0;i<g.n;i++)				//循环直到所有顶点的最短路径都求出
	{	mindis=INF;					//mindis求最小路径长度
		for (j=0;j<g.n;j++)			//选取不在s中且具有最小距离的顶点u
			if (S[j]==0 && dist[j]<mindis)
			{	u=j;
				mindis=dist[j];
			}
		S[u]=1;						//顶点u加入s中
		for (j=0;j<g.n;j++)			//修改不在S中的顶点的距离
			if (S[j]==0)
				if (g.edges[u][j]<INF && dist[u]+g.edges[u][j]<dist[j])
				{	dist[j]=dist[u]+g.edges[u][j];
					path[j]=u;
				}
	}
	//Dispath(g,dist,path,S,v);		//输出最短路径
	//cout<<dist[g.n-1]<<endl;
}
int main()
{
	FILE *fps,*fpt,*fpw;
	fps=fopen("s.txt","r"); fpt=fopen("t.txt","r"); fpw=fopen("w.txt","r");
	int u,v1,c;
	int n=39,e=124;
	int A[n][MAXV];
	for(int i=0;i<MAXV;i++)
		for(int j=0;j<MAXV;j++)
 	   A[i][j]=INF;
	for(int i=0;i<MAXV;i++)
	  A[i-1][i-1]=0;
	for(int i=0;i<e;i++)
	{
		fscanf(fps,"%d",&u); fscanf(fpt,"%d",&v1); fscanf(fpw,"%d",&c);
		//printf("%3d: %2d %2d %2d\n",i+1,u,v1,c);
		A[u-1][v1-1]=c;
	}
	int v=0;
  MGraph g;
	/*
	int n=7,e=12;
	int A[7][MAXV]={
		{0,4,6,6,INF,INF,INF},
		{INF,0,1,INF,7,INF,INF},
		{INF,INF,0,INF,6,4,INF},
		{INF,INF,2,0,INF,5,INF},
		{INF,INF,INF,INF,0,INF,6},
		{INF,INF,INF,INF,1,0,8},
		{INF,INF,INF,INF,INF,INF,0}};*/

	CreateMat(g,A,n,e);		//创建图的邻接矩阵存储结构g
	//printf("图的邻接矩阵:\n");
	//DispMat(g);				//输出邻接矩阵g
	//printf("从%d顶点出发的最短路径:\n",v);
	double start=clock();		//程序开始计时
	Dijkstra(g,v);
	double end=clock();		//程序结束用时

	Dispath(g,dist,path,S,v);		//输出最短路径


	double endtime=(double)(end-start)/CLOCKS_PER_SEC;
	//cout<<"Total time:"<<endtime<<endl;		//s为单位
	cout<<"O(N*N)最短路算法的执行用时："<<endtime*1000<<" ms"<<endl;	//ms为单位
	fclose(fps);  fclose(fpt);  fclose(fpw);
	return 0;
}
