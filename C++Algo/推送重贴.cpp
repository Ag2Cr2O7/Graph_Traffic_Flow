#include<bits/stdc++.h>
#include<iostream>
#include<ctime>
using namespace std;
const int N = 2e4 + 5, M = 2e5 + 5, INF = 0x3f3f3f3f;
int n, m, s, t;
int Head[N << 1], Next[M << 1], W[M << 1], To[M << 1], tot = 1;
int h[N], e[N], gap[N << 1], inq[N];
//e[i]代表当前i结点的超额流
/*
char nc()
{
    static char buf[100000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}
int read()
{
    char ch = nc();
    int sum = 0;
    while (!(ch >= '0' && ch <= '9')) ch = nc();
    while (ch >= '0' && ch <= '9') sum = sum * 10 + ch - 48, ch = nc();
    return sum;
}
//快读代码
*/
struct cmp
{
    bool operator()(int a, int b)
    {
      return h[a] < h[b];  //优先队列指从大到小排
    }
};//以高度为键值的优先队列，还是一元的优先队列
queue <int> que;
priority_queue<int,vector<int>, cmp> pque;
void Add_Edge(int x, int y, int z)
{
    Next[++tot] = Head[x], Head[x] = tot, To[tot] = y, W[tot] = z;
    Next[++tot] = Head[y], Head[y] = tot, To[tot] = x, W[tot] = 0;
}
bool bfs()
{//将其层数都标出来
    memset(h, -1, sizeof(h));
    h[t] = 0;
    que.push(t);
    while (!que.empty()) {
        int x = que.front();
        que.pop();
        for (int i = Head[x]; i; i = Next[i])
        {
            int v = To[i];
          // 因为是从汇点出发，走的是反向边，而反向边流量初始为0，所以要找其正向边
            if (W[tot ^ 1] && h[v] == -1)
                h[v] = h[x] + 1, que.push(v);
        }
    }
    return h[s] != -1;
}
void push(int x)
{//将当前结点的流都推送出去
    for (int i = Head[x];i; i = Next[i])
    {
        int v = To[i];
        if (W[i] && h[v] + 1 == h[x])
        {
            int tmp = min(e[x], W[i]);
            W[i] -= tmp, W[i ^ 1] += tmp;
            e[x] -= tmp, e[v] += tmp;
            if (v != s && v != t && !inq[v])//入队的点以及源点和汇点不会入队
                pque.push(v), inq[v] = 1;//标记入队
            if (!e[x])//如果当前结点超额流为0即可不再推送
                break;
        }
    }
    return;
}
void relabel(int x)
{//重贴标签
    h[x] = INF;
    for (int i = Head[x]; i; i = Next[i])
    {
        int v = To[i];
      //从出边有流量，以及最低层数来找，可以类比于ISPA的更新结点层数的意思，都是为了让该点下次有边可走
        if (W[i] && h[v] + 1 < h[x])
            h[x] = h[v] + 1;
    }
    return;
}
int Hlpp()
{
    if (!bfs())//s和t不连通,可以直接退出
        return 0;
    h[s] = n;//将s的层数处理为n
    memset(gap, 0, sizeof(gap));
    for (int i = 1; i <= n; i++)
        if (h[i] < INF)
            ++gap[h[i]];//统计当前结点层数的个数
    for (int i = Head[s]; i; i = Next[i])
    {
        int v = To[i], tmp = W[i];
        if (tmp)
        {
            W[i] -= tmp;
            W[i ^ 1] += tmp;
            e[s] -= tmp;
            e[v] += tmp;//首先将源点所有外连的边上的流量都推出去到相应连的结点上
            if (v != s && v != t && !inq[v])
                pque.push(v), inq[v] = 1;
        }
    }
    while (!pque.empty())
    {
        // cout << 1 << endl;
        int x = pque.top();
        inq[x] = 0;
        pque.pop();
        push(x);//将x点的流量推送出去
        if (e[x])
        {//如果当前还有超额流
            if (!(--gap[h[x]]))//gap优化，因为当前节点是最高的所以修改的节点一定不在优先队列中，不必担心修改对优先队列会造成影响
                for (int i = 1; i <= n; i++)//因为要修改当前点的层数，如果当前点的层数已经无了的话，那么相当于断层，
				//高于当前结点的流量都无法推送下去，所以将高度设为n + 1将当前结点的超额流推送回源点
                    if (i != s && i != t && h[i] > h[x] && h[i] < n + 1)
                        h[i] = n + 1;
            relabel(x);//给h[x]重贴标签
            ++gap[h[x]];//给当前结点的层数gap++
            pque.push(x);
            inq[x] = 1;
        }
    }
    return e[t];
}
int main()
{
   FILE *fps,*fpt,*fpw;
   fps=fopen("s.txt","r"); fpt=fopen("t.txt","r"); fpw=fopen("final.txt","r");
    n = 39, m = 124, s = 1, t = 39; //结点，边，起点，终点
    int u, v, c;
    printf("%d个结点，%d条边\n",n,m);
    //printf("序号  s  t  f\n");
    for(int i=0;i<m;i++)
    {
      fscanf(fps,"%d",&u); fscanf(fpt,"%d",&v); fscanf(fpw,"%d",&c);
      //printf("%3d: %2d %2d %2d\n",i+1,u,v,c);
      Add_Edge(u, v, c);
    }
    //printf("\n");
    /*
    for (int i = 1; i <= m; i++) {
        u = read(), v = read(), c = read();
        Add_Edge(u, v, c);
    }
    */
    double start=clock();		//程序开始计时
    auto x=Hlpp();
    double end=clock();		//程序结束用时

    printf("Push-Relabel操作计算的从%d到%d的最大流为：%d\n",s,t,x);
  	double endtime=(double)(end-start)/CLOCKS_PER_SEC;
  	//cout<<"Total time:"<<endtime<<endl;		//s为单位
  	cout<<"O(V*V*E)算法执行用时："<<endtime*1000<<" ms"<<endl;	//ms为单位
    fclose(fps);  fclose(fpt);  fclose(fpw);
    return 0;
}
