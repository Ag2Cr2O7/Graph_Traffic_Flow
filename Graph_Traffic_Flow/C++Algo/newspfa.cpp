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
   queue<int>q;//存储每次更新的所有的点
   dist[s] = 0;
   q.push(s);
   st[s] = true;
   while(!q.empty())
   {
       int t = q.front();//每次从队列取出一个来更新所有它能够到达的点
       q.pop();
       st[t]=false;
       for(int i=h[t];i!=-1;i=ne[i])
       {
           int j = e[i];
           if(dist[j] > dist[t] + w[i])
           {
               dist[j] = dist[t] + w[i];//更新操作
               if(!st[j])//如果队列里面没有这个点就入队
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
  fps=fopen("s.txt","r"); fpt=fopen("t.txt","r"); fpw=fopen("w.txt","r"); //读文件
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

   double start=clock();		//程序开始计时
   spfa(s);
   double end=clock();		//程序结束用时

   if(dist[t] == 0x3f3f3f3f) cout<<"impossible";
   else
   {
     cout<<"使用SPFA算法计算最短路径"<<endl;
     for(int i=2;i<=n;i++)
       printf("  从顶点%3d到顶点%3d 的最短路径长度为：%4d\n",s,i,dist[i]);
     //cout<<endl;
   }
   double endtime=(double)(end-start)/CLOCKS_PER_SEC;
   //cout<<"Total time:"<<endtime<<endl;		//s为单位
   cout<<"算法执行用时："<<endtime*1000<<" ms"<<endl;	//ms为单位
   return 0;
}
