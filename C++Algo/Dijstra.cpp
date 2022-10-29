//�ҿ�˹�����㷨����Դ���·��
#include "Graph.cpp"
#include<ctime>
int dist[MAXV],path[MAXV];
int S[MAXV];
void Dispath(MGraph g,int dist[],int path[],int S[],int v)
//����Ӷ���v�������������·��
{	int i,j,k;
	int apath[MAXV],d;					//���һ�����·��(����)���䶥�����
	for (i=0;i<g.n;i++)					//ѭ������Ӷ���v��i��·��
		if (S[i]==1 && i!=v)
		{
			printf("�Ӷ���%3d������%3d�����·������Ϊ��%4d��·��Ϊ:",v+1,i+1,dist[i]);
			d=0; apath[d]=i;			//���·���ϵ��յ�
			k=path[i];
			if (k==-1)				//û��·�������
				printf("��·��\n");
			else						//����·��ʱ�����·��
			{
				while (k!=v)
				{	d++; apath[d]=k;
					k=path[k];
				}
				d++; apath[d]=v;		//���·���ϵ����
				printf("%d->",apath[d]);	//��������
				for (j=d-1;j>=1;j--)	//�������������
					printf("%d->",apath[j]);
				printf("%d",apath[0]);
				printf("\n");
			}
		}
}
void Dijkstra(MGraph g,int v)			//Dijkstra�㷨
{
	int mindis,i,j,u;
	for (i=0;i<g.n;i++)
	{	dist[i]=g.edges[v][i];		//�����ʼ��
		S[i]=0;						//S[]�ÿ�
		if (g.edges[v][i]<INF)		//·����ʼ��
			path[i]=v;				//����v������i�б�ʱ���ö���i��ǰһ������Ϊv
		else
			path[i]=-1;				//����v������iû��ʱ���ö���i��ǰһ������Ϊ-1
	}
	S[v]=1;path[v]=0;				//Դ����v����s��
	for (i=0;i<g.n;i++)				//ѭ��ֱ�����ж�������·�������
	{	mindis=INF;					//mindis����С·������
		for (j=0;j<g.n;j++)			//ѡȡ����s���Ҿ�����С����Ķ���u
			if (S[j]==0 && dist[j]<mindis)
			{	u=j;
				mindis=dist[j];
			}
		S[u]=1;						//����u����s��
		for (j=0;j<g.n;j++)			//�޸Ĳ���S�еĶ���ľ���
			if (S[j]==0)
				if (g.edges[u][j]<INF && dist[u]+g.edges[u][j]<dist[j])
				{	dist[j]=dist[u]+g.edges[u][j];
					path[j]=u;
				}
	}
	//Dispath(g,dist,path,S,v);		//������·��
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

	CreateMat(g,A,n,e);		//����ͼ���ڽӾ���洢�ṹg
	//printf("ͼ���ڽӾ���:\n");
	//DispMat(g);				//����ڽӾ���g
	//printf("��%d������������·��:\n",v);
	double start=clock();		//����ʼ��ʱ
	Dijkstra(g,v);
	double end=clock();		//���������ʱ

	Dispath(g,dist,path,S,v);		//������·��


	double endtime=(double)(end-start)/CLOCKS_PER_SEC;
	//cout<<"Total time:"<<endtime<<endl;		//sΪ��λ
	cout<<"O(N*N)���·�㷨��ִ����ʱ��"<<endtime*1000<<" ms"<<endl;	//msΪ��λ
	fclose(fps);  fclose(fpt);  fclose(fpw);
	return 0;
}
