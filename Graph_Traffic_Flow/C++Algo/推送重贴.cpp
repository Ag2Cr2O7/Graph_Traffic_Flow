#include<bits/stdc++.h>
#include<iostream>
#include<ctime>
using namespace std;
const int N = 2e4 + 5, M = 2e5 + 5, INF = 0x3f3f3f3f;
int n, m, s, t;
int Head[N << 1], Next[M << 1], W[M << 1], To[M << 1], tot = 1;
int h[N], e[N], gap[N << 1], inq[N];
//e[i]����ǰi���ĳ�����
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
//�������
*/
struct cmp
{
    bool operator()(int a, int b)
    {
      return h[a] < h[b];  //���ȶ���ָ�Ӵ�С��
    }
};//�Ը߶�Ϊ��ֵ�����ȶ��У�����һԪ�����ȶ���
queue <int> que;
priority_queue<int,vector<int>, cmp> pque;
void Add_Edge(int x, int y, int z)
{
    Next[++tot] = Head[x], Head[x] = tot, To[tot] = y, W[tot] = z;
    Next[++tot] = Head[y], Head[y] = tot, To[tot] = x, W[tot] = 0;
}
bool bfs()
{//��������������
    memset(h, -1, sizeof(h));
    h[t] = 0;
    que.push(t);
    while (!que.empty()) {
        int x = que.front();
        que.pop();
        for (int i = Head[x]; i; i = Next[i])
        {
            int v = To[i];
          // ��Ϊ�Ǵӻ��������ߵ��Ƿ���ߣ��������������ʼΪ0������Ҫ���������
            if (W[tot ^ 1] && h[v] == -1)
                h[v] = h[x] + 1, que.push(v);
        }
    }
    return h[s] != -1;
}
void push(int x)
{//����ǰ�����������ͳ�ȥ
    for (int i = Head[x];i; i = Next[i])
    {
        int v = To[i];
        if (W[i] && h[v] + 1 == h[x])
        {
            int tmp = min(e[x], W[i]);
            W[i] -= tmp, W[i ^ 1] += tmp;
            e[x] -= tmp, e[v] += tmp;
            if (v != s && v != t && !inq[v])//��ӵĵ��Լ�Դ��ͻ�㲻�����
                pque.push(v), inq[v] = 1;//������
            if (!e[x])//�����ǰ��㳬����Ϊ0���ɲ�������
                break;
        }
    }
    return;
}
void relabel(int x)
{//������ǩ
    h[x] = INF;
    for (int i = Head[x]; i; i = Next[i])
    {
        int v = To[i];
      //�ӳ������������Լ���Ͳ������ң����������ISPA�ĸ��½���������˼������Ϊ���øõ��´��б߿���
        if (W[i] && h[v] + 1 < h[x])
            h[x] = h[v] + 1;
    }
    return;
}
int Hlpp()
{
    if (!bfs())//s��t����ͨ,����ֱ���˳�
        return 0;
    h[s] = n;//��s�Ĳ�������Ϊn
    memset(gap, 0, sizeof(gap));
    for (int i = 1; i <= n; i++)
        if (h[i] < INF)
            ++gap[h[i]];//ͳ�Ƶ�ǰ�������ĸ���
    for (int i = Head[s]; i; i = Next[i])
    {
        int v = To[i], tmp = W[i];
        if (tmp)
        {
            W[i] -= tmp;
            W[i ^ 1] += tmp;
            e[s] -= tmp;
            e[v] += tmp;//���Ƚ�Դ�����������ı��ϵ��������Ƴ�ȥ����Ӧ���Ľ����
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
        push(x);//��x����������ͳ�ȥ
        if (e[x])
        {//�����ǰ���г�����
            if (!(--gap[h[x]]))//gap�Ż�����Ϊ��ǰ�ڵ�����ߵ������޸ĵĽڵ�һ���������ȶ����У����ص����޸Ķ����ȶ��л����Ӱ��
                for (int i = 1; i <= n; i++)//��ΪҪ�޸ĵ�ǰ��Ĳ����������ǰ��Ĳ����Ѿ����˵Ļ�����ô�൱�ڶϲ㣬
				//���ڵ�ǰ�����������޷�������ȥ�����Խ��߶���Ϊn + 1����ǰ���ĳ��������ͻ�Դ��
                    if (i != s && i != t && h[i] > h[x] && h[i] < n + 1)
                        h[i] = n + 1;
            relabel(x);//��h[x]������ǩ
            ++gap[h[x]];//����ǰ���Ĳ���gap++
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
    n = 39, m = 124, s = 1, t = 39; //��㣬�ߣ���㣬�յ�
    int u, v, c;
    printf("%d����㣬%d����\n",n,m);
    //printf("���  s  t  f\n");
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
    double start=clock();		//����ʼ��ʱ
    auto x=Hlpp();
    double end=clock();		//���������ʱ

    printf("Push-Relabel��������Ĵ�%d��%d�������Ϊ��%d\n",s,t,x);
  	double endtime=(double)(end-start)/CLOCKS_PER_SEC;
  	//cout<<"Total time:"<<endtime<<endl;		//sΪ��λ
  	cout<<"O(V*V*E)�㷨ִ����ʱ��"<<endtime*1000<<" ms"<<endl;	//msΪ��λ
    fclose(fps);  fclose(fpt);  fclose(fpw);
    return 0;
}
