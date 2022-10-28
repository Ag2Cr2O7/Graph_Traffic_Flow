clc,clear,close all
jds=39;  qd=1;  zd=39;
s=load('s.txt'); t=load('t.txt'); w=load('w.txt'); 
%  w1=randi([1,14],1,124); %随机生成流量
%  x=0;
%  while x~=19
%      w1=randi([1,14],1,124); %随机生成流量
%      G1 = digraph(s,t,w1); %directed graph
%    [mf,gf,cs,ct] = maxflow(G1,qd,zd);
%   m=size(cs); n=size(ct);
%   x=m(1);
%  end
w1=load('final.txt'); 
w2=w./60./w1;
juli=sparse(s,t,w,jds,jds); %有向图描述转换成邻接矩阵(距离矩阵)
shijian=sparse(s,t,w2,jds,jds); %有向图描述转换成邻接矩阵(矩阵)
G = digraph(s,t,w); %directed graph
G1 = digraph(s,t,w1); %directed graph

% end%图1为原始网络的带权图描述
figure
% plot(G,'EdgeLabel',G.Edges.Weight,'Layout','force');
plot(G,'EdgeLabel',G.Edges.Weight,'Layout','force');
title("原始交通网络距离带权图");


%图1.1为原始网络的流量描述
figure
plot(G1,'EdgeLabel',G1.Edges.Weight,'Layout','force');
title("原始交通网络流量带权图");

%图2求出所有增广路径并组成网络，图中把增广路径高亮
% 最大流，有向图对象，最大流集合和最小割集合
% mf:max flow, gf:directed graph, cs: first part of the cut, ct:second
figure
[mf,gf,cs,ct] = maxflow(G1,qd,zd);
H = plot(G1,'Layout','force');
highlight(H,gf,'EdgeColor','r','LineWidth',2); %maximum flow
st = gf.Edges.EndNodes;
labeledge(H,st(:,1),st(:,2));%突出显示非零流的图并对其添加标签。
title("所有增广路径构成的网络");

% 那个特别复杂的图
% figure
% H = plot(G,'Layout','layered','Sources',cs,'Sinks',ct); %minimum cut
% % layout(H,'force','UseGravity',true)
% highlight(H,cs,'NodeColor','red')
% highlight(H,ct,'NodeColor','green')
% title("最大流最小割对应的关键路径");

%图3将增广路径图单独拿出来
figure
myplot1=plot(gf);
layout(myplot1,'force','UseGravity',true)
title("增广路径构成的网络");


%提取增广路径并由距离和流量计算时间代价
x=gf.Edges.EndNodes(:,1); %起点
y=gf.Edges.EndNodes(:,2); %终点
z=gf.Edges.Weight; %权值
for i=1:size(x)
%     z(i)=juli(x(i),y(i))./z(i); %z(i)数值为流量
 z(i)=juli(x(i),y(i))./z(i); %交通网络的时间权值
 z(i)=roundn(z(i),-1); %保留1位小数
end

%图4求出所有增广路径中时间消耗最短的图
G2 = digraph(s,t,w2);
[P,d]=shortestpath(G,qd,zd);
[P2,d2]=shortestpath(G2,qd,zd);

% 最短路径
figure
myplot=plot(G,'EdgeColor','k');
highlight(myplot,P,'EdgeColor','r','LineWidth',2);
layout(myplot,'force','UseGravity',true)
title("起点到终点的最短路径");


figure
subplot(1,2,1)
myplot=plot(G,'EdgeColor','k');
highlight(myplot,P,'EdgeColor','r','LineWidth',2);
title("最短路径");
subplot(1,2,2)
myplot=plot(G,'EdgeColor','k');
highlight(myplot,P2,'EdgeColor','g','LineWidth',2);
title("最优路径");

%图5将最优路径与最短路径对比画图
figure
myplot=plot(G,'EdgeLabel',G.Edges.Weight,'EdgeColor','k');
highlight(myplot,P2,'EdgeColor','g','LineWidth',2);
[P,d]=shortestpath(G,qd,zd);
highlight(myplot,P,'EdgeColor','r','LineWidth',2); %最短路径
title("最短路径图(红)和最优路径图(绿)");

%求出最优路径的距离
ans1=0;  ans2=0; ans3=0; ans4=0; m=size(P)-1;n=size(P2)-1;%n是一个二维数组
for k=1:n(2) %最小增广路的结点数
  ans1=ans1+juli(P2(k),P2(k+1));
  ans2=ans2+shijian(P2(k),P2(k+1));
end
for k=1:m(2) %最小增广路的结点数
  ans4=ans4+shijian(P(k),P(k+1)); %最短路径时间为
end
fprintf("最大流为：%d\n",mf);
fprintf("最短路径长度为：%d米\n",d);
fprintf("最短路径时间为：%2.1f分钟\n",ans4);
fprintf("最优路径长度为：%d米\n",ans1);
fprintf("最优路径时间为：%2.1f分钟\n",ans2);





