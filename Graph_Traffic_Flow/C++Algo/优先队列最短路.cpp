#include<iostream>
#include<vector>
#include<queue>
#include<ctime>
using namespace std;
//�ڵ���Ϣ�ࣨ�����ڵ�����·��ֵ��
class info
{
public:
	int node;//�ڵ�
	double weight;//Ȩ��
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

//ͼ��
class cgraph{
public:
	int V;//��������
	vector<info>*adj;//�ڽӾ��󣨼�¼ÿ���ڵ�����бߣ�
	double *dis;//���ž���
public:
	cgraph(int V);//���캯����VΪ�ڵ�����
	void add_edge(int nd1,int nd2,double weight);//��ӱߣ��ڵ�1���ڵ�2����Ȩ�أ�
	void get_shortest_path(int src);//������·��
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
	//���ȶ��У���¼�ڵ��ź����·��ֵ�����·��ֵС������
	dis[src]=0;//Դ������·��ֵΪ0
	current_node.push(info(src,0));//Դ��ѹ�����

	//�����зǿռ���Ѱ��
	while(!current_node.empty())
	{
		int u=current_node.top().node;//u���ڶӶ��ڵ�
		double w=current_node.top().weight;//w���ڶԶ��ڵ����·��ֵ
		current_node.pop();//�����Ӷ��ڵ�
		//�ӶԶ��ڵ���������½ڵ�����·��ֵ
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
	//���dis׷�ټ�¼�����·��ֵ
	//for(int i=0;i<V;i++)
	  //cout<<src+1<<"->"<<i+1<<"      dis="<<dis[i]<<endl;
	//cout<<dis[V-1]<<endl;
}

int main()
{
	FILE *fps,*fpt,*fpw;
	fps=fopen("s.txt","r"); fpt=fopen("t.txt","r"); fpw=fopen("w.txt","r");
	int n=39,e=124;  //������������
	int src=1; //���
	int a,b,c;
	cgraph graph(n);//����ͼ
	for(int i=0;i<e;i++)
	{
		fscanf(fps,"%d",&a); fscanf(fpt,"%d",&b); fscanf(fpw,"%d",&c);
		graph.add_edge(a-1,b-1,c);
	}
	//���
	double start=clock();		//����ʼ��ʱ
	graph.get_shortest_path(src-1);
	double end=clock();		//���������ʱ

	for(int i=0;i<graph.V;i++)
	  cout<<src<<"->"<<i+1<<"      dis="<<graph.dis[i]<<endl;
	double endtime=(double)(end-start)/CLOCKS_PER_SEC;
	//cout<<"Total time:"<<endtime<<endl;		//sΪ��λ
	cout<<"O(ElogV)���·�㷨ִ����ʱ��"<<endtime*1000<<" ms"<<endl;	//msΪ��λ
	//cin.get();
	fclose(fps);  fclose(fpt);  fclose(fpw);
	return 0;
}
