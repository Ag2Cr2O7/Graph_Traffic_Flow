clc,clear,close all
fprintf("原最大流为：13\n最短路径长度为：5797米\n最短路径时间为：41.5分钟\n最优路径长度为：6828米\n最优路径时间为：13.2分钟\n");
jds=39;  qd=1;  zd=39;
s=load('s.txt'); t=load('t.txt'); w=load('w.txt'); 
w1=load('final.txt'); 
w2=w./60./w1;
a=[19 16 37 12 35];
b=[18 38 15 13 34];
c=[5 4 2 1 1];
juli=sparse(s,t,w,jds,jds); %有向图描述转换成邻接矩阵(距离矩阵)
shijian=sparse(s,t,w2,jds,jds); %有向图描述转换成邻接矩阵(矩阵)
G = digraph(s,t,w); %directed graph
G1 = digraph(s,t,w1); %directed graph
G2 = digraph(a,b,c); %directed graph
G3 = digraph(s,t,w2);
[mf,gf,cs,ct] = maxflow(G1,qd,zd);

% 那个特别复杂的图
figure
H = plot(G,'Layout','layered','Sources',cs,'Sinks',ct); %minimum cut
% layout(H,'force','UseGravity',true)
highlight(H,cs,'NodeColor','red')
highlight(H,ct,'NodeColor','green')
title("最大流最小割");


figure
H=plot(G,'Layout','force');
j=size(G2.Edges.EndNodes); %结点数
k=j(1);
for i=1:k  %标注关键路径
  highlight(H,[G2.Edges.EndNodes(i,1),G2.Edges.EndNodes(i,2)],...
  'EdgeColor','r','LineWidth',2);
end
% H = plot(G,'Layout','layered','Sources',cs,'Sinks',ct); %minimum cut
% layout(H,'force','UseGravity',true)
title("最大流最小割对应的关键路径");

%首先我们调整了16-38，37-15
% %19-18
% w1(61)=w1(61)+0;
% w1(56)=w1(56)-0;
%16-38
w1(52)=w1(52)+4;
w1(121)=w1(121)-4;
%37-15
w1(118)=w1(118)+5;
w1(48)=w1(48)-5;
% %12-13
% w1(38)=w1(38)+0;
% w1(39)=w1(39)-0;
% %35-34
% w1(113)=w1(113)+0;
% w1(111)=w1(111)-0;
w2=w./60./w1;
G1 = digraph(s,t,w1); %directed graph
shijian=sparse(s,t,w2,jds,jds); %有向图描述转换成邻接矩阵(矩阵)

[mf,gf,cs,ct] = maxflow(G1,qd,zd);
[P2,d2]=shortestpath(G3,qd,zd);
[P,d]=shortestpath(G,qd,zd);

figure
H = plot(G,'Layout','layered','Sources',cs,'Sinks',ct); %minimum cut
% layout(H,'force','UseGravity',true)
highlight(H,cs,'NodeColor','red')
highlight(H,ct,'NodeColor','green')
title("优化后的最大流最小割1");

ans1=0;  ans2=0; ans3=0; ans4=0; m=size(P)-1;n=size(P2)-1;%n是一个二维数组
for k=1:n(2) %最小增广路的结点数
  ans1=ans1+juli(P2(k),P2(k+1));
  ans2=ans2+shijian(P2(k),P2(k+1));
end
for k=1:m(2) %最小增广路的结点数
  ans4=ans4+shijian(P(k),P(k+1)); %最短路径时间为
end
fprintf("\n最大流1为：%d\n",mf);
fprintf("最短路径长度为：%d米\n",d);
fprintf("最短路径时间为：%2.1f分钟\n",ans4);
fprintf("最优路径长度为：%d米\n",ans1);
fprintf("最优路径时间为：%2.1f分钟\n",ans2);
G2 = digraph(s,t,w2);
[P,d]=shortestpath(G,qd,zd);
[P2,d2]=shortestpath(G2,qd,zd);
P2
size(cs);  size(ct);


%迭代后调28-39
w1(94)=w1(94)+7; w1(124)=w1(124)-7; 
w2=w./60./w1;
G1 = digraph(s,t,w1); %directed graph
shijian=sparse(s,t,w2,jds,jds); %有向图描述转换成邻接矩阵(矩阵)
[mf,gf,cs,ct] = maxflow(G1,qd,zd);
ans1=0;  ans2=0; ans3=0; ans4=0; m=size(P)-1;n=size(P2)-1;%n是一个二维数组
for k=1:n(2) %最小增广路的结点数
  ans1=ans1+juli(P2(k),P2(k+1));
  ans2=ans2+shijian(P2(k),P2(k+1));
end
for k=1:m(2) %最小增广路的结点数
  ans4=ans4+shijian(P(k),P(k+1)); %最短路径时间为
end
fprintf("\n最大流2为：%d\n",mf);
fprintf("最短路径长度为：%d米\n",d);
fprintf("最短路径时间为：%2.1f分钟\n",ans4);
fprintf("最优路径长度为：%d米\n",ans1);
fprintf("最优路径时间为：%2.1f分钟\n",ans2);
G2 = digraph(s,t,w2);
[P,d]=shortestpath(G,qd,zd);
[P2,d2]=shortestpath(G2,qd,zd);
P2
size(cs);  size(ct);


% myplot=plot(G,'EdgeColor','k');
% highlight(myplot,P2,'EdgeColor','g','LineWidth',2);
% title("最优路径");

figure
H = plot(G,'Layout','layered','Sources',cs,'Sinks',ct); %minimum cut
% layout(H,'force','UseGravity',true)
highlight(H,cs,'NodeColor','red')
highlight(H,ct,'NodeColor','green')
title("优化后的最大流最小割2");

%调6-37
w1(18)=w1(18)+3;
w2=w./60./w1;
G1 = digraph(s,t,w1); %directed graph
shijian=sparse(s,t,w2,jds,jds); %有向图描述转换成邻接矩阵(矩阵)
[mf,gf,cs,ct] = maxflow(G1,qd,zd);
ans1=0;  ans2=0; ans3=0; ans4=0; m=size(P)-1;n=size(P2)-1;%n是一个二维数组
for k=1:n(2) %最小增广路的结点数
  ans1=ans1+juli(P2(k),P2(k+1));
  ans2=ans2+shijian(P2(k),P2(k+1));
end
for k=1:m(2) %最小增广路的结点数
  ans4=ans4+shijian(P(k),P(k+1)); %最短路径时间为
end
fprintf("\n最大流3为：%d\n",mf);
fprintf("最短路径长度为：%d米\n",d);
fprintf("最短路径时间为：%2.1f分钟\n",ans4);
fprintf("最优路径长度为：%d米\n",ans1);
fprintf("最优路径时间为：%2.1f分钟\n",ans2);
G2 = digraph(s,t,w2);
[P,d]=shortestpath(G,qd,zd);
[P2,d2]=shortestpath(G2,qd,zd);
P2
size(cs);  size(ct);

figure
H = plot(G,'Layout','layered','Sources',cs,'Sinks',ct); %minimum cut
% layout(H,'force','UseGravity',true)
highlight(H,cs,'NodeColor','red')
highlight(H,ct,'NodeColor','green')
title("优化后的最大流最小割3");
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%




