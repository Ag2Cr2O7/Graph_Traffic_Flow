#include<iostream>
#include<vector>
#include<queue>
#include<ctime>
using namespace std;
//节点信息类（包含节点和最短路径值）
class info
{
public:
	int node;//节点
	double weight;//权重
public:
	info(int node,double weight)
	{
		this->node=node;
		this->weight=weight;
	}
	friend bool operator<(const info &info1 , const info &info2)
	{
		return info1.weight>info2.weight;
	}
};

//图类
class cgraph{
public:
	int V;//顶点数量
	vector<info>*adj;//邻接矩阵（记录每个节点的所有边）
	double *dis;//最优距离
public:
	cgraph(int V);//构造函数（V为节点数）
	void add_edge(int nd1,int nd2,double weight);//添加边（节点1，节点2，边权重）
	void get_shortest_path(int src);//求解最短路径
};

cgraph::cgraph(int V)
{
		this->V=V;
		adj=new vector<info>[V];
		dis=new double[V];
		for(int i=0;i<V;i++)dis[i]=1e8;
}

void cgraph::add_edge(int nd1,int nd2,double weight)
{
		adj[nd1].push_back(info(nd2,weight));
		adj[nd2].push_back(info(nd1,weight));
}

void cgraph::get_shortest_path(int src)
{
	priority_queue<info>current_node;
	//优先队列，记录节点编号和最短路径值，最短路径值小的优先
	dis[src]=0;//源点的最短路径值为0
	current_node.push(info(src,0));//源点压入队列

	//当队列非空继续寻找
	while(!current_node.empty())
	{
		int u=current_node.top().node;//u等于队顶节点
		double w=current_node.top().weight;//w等于对顶节点最短路径值
		current_node.pop();//弹出队顶节点
		//从对顶节点出发，更新节点的最短路径值
		for(int i=0;i<(int)adj[u].size();i++)
		{
			int v=adj[u][i].node;
			if(w+adj[u][i].weight<dis[v])
			{
				dis[v]=w+adj[u][i].weight;
				current_node.push(info(v,dis[v]));
			}
		}
	}
	//输出dis追踪记录的最短路径值
	//for(int i=0;i<V;i++)
	  //cout<<src+1<<"->"<<i+1<<"      dis="<<dis[i]<<endl;
	//cout<<dis[V-1]<<endl;
}

int main()
{
	FILE *fps,*fpt,*fpw;
	fps=fopen("s.txt","r"); fpt=fopen("t.txt","r"); fpw=fopen("w.txt","r");
	int n=39,e=124;  //顶点数，边数
	int src=1; //起点
	int a,b,c;
	cgraph graph(n);//构造图
	for(int i=0;i<e;i++)
	{
		fscanf(fps,"%d",&a); fscanf(fpt,"%d",&b); fscanf(fpw,"%d",&c);
		graph.add_edge(a-1,b-1,c);
	}
	//求解
	double start=clock();		//程序开始计时
	graph.get_shortest_path(src-1);
	double end=clock();		//程序结束用时

	for(int i=0;i<graph.V;i++)
	  cout<<src<<"->"<<i+1<<"      dis="<<graph.dis[i]<<endl;
	double endtime=(double)(end-start)/CLOCKS_PER_SEC;
	//cout<<"Total time:"<<endtime<<endl;		//s为单位
	cout<<"O(ElogV)最短路算法执行用时："<<endtime*1000<<" ms"<<endl;	//ms为单位
	//cin.get();
	fclose(fps);  fclose(fpt);  fclose(fpw);
	return 0;
}
