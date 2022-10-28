#include<iostream>
#include<cstring>
#include<queue>
#include<ctime>
using namespace std;
const int N = 1e5 + 10;
int n,m;
int h[N] , e[N] , w[N] , ne[N] , idx;
int dist[N];
bool st[N];

void add(int a , int b , int c)
{
   e[idx] = b;
   w[idx] = c;
   ne[idx] = h[a];
   h[a] = idx ++;
}

void spfa(int s)
{
   queue<int>q;//�洢ÿ�θ��µ����еĵ�
   dist[s] = 0;
   q.push(s);
   st[s] = true;
   while(!q.empty())
   {
       int t = q.front();//ÿ�δӶ���ȡ��һ���������������ܹ�����ĵ�
       q.pop();
       st[t]=false;
       for(int i=h[t];i!=-1;i=ne[i])
       {
           int j = e[i];
           if(dist[j] > dist[t] + w[i])
           {
               dist[j] = dist[t] + w[i];//���²���
               if(!st[j])//�����������û�����������
               {
                   q.push(j);
                   st[j] = true;
               }
           }
       }
   }
}
int main()
{
  FILE *fps,*fpt,*fpw;
  fps=fopen("s.txt","r"); fpt=fopen("t.txt","r"); fpw=fopen("w.txt","r"); //���ļ�
  int n=39,m=124;
   //cin>>n>>m;
   memset(dist,0x3f,sizeof dist);
   memset(h,-1,sizeof h);
   for(int i=0;i<m;i++)
   {
       int a,b,c;
       fscanf(fps,"%d",&a); fscanf(fpt,"%d",&b); fscanf(fpw,"%d",&c);
       add(a,b,c);
   }
   int s=1,t=39;

   double start=clock();		//����ʼ��ʱ
   spfa(s);
   double end=clock();		//���������ʱ

   if(dist[t] == 0x3f3f3f3f) cout<<"impossible";
   else
   {
     cout<<"ʹ��SPFA�㷨�������·��"<<endl;
     for(int i=2;i<=n;i++)
       printf("  �Ӷ���%3d������%3d �����·������Ϊ��%4d\n",s,i,dist[i]);
     //cout<<endl;
   }
   double endtime=(double)(end-start)/CLOCKS_PER_SEC;
   //cout<<"Total time:"<<endtime<<endl;		//sΪ��λ
   cout<<"�㷨ִ����ʱ��"<<endtime*1000<<" ms"<<endl;	//msΪ��λ
   return 0;
}
