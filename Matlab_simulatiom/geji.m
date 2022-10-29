clc,clear,close all
fprintf("ԭ�����Ϊ��13\n���·������Ϊ��5797��\n���·��ʱ��Ϊ��41.5����\n����·������Ϊ��6828��\n����·��ʱ��Ϊ��13.2����\n");
jds=39;  qd=1;  zd=39;
s=load('s.txt'); t=load('t.txt'); w=load('w.txt'); 
w1=load('final.txt'); 
w2=w./60./w1;
a=[19 16 37 12 35];
b=[18 38 15 13 34];
c=[5 4 2 1 1];
juli=sparse(s,t,w,jds,jds); %����ͼ����ת�����ڽӾ���(�������)
shijian=sparse(s,t,w2,jds,jds); %����ͼ����ת�����ڽӾ���(����)
G = digraph(s,t,w); %directed graph
G1 = digraph(s,t,w1); %directed graph
G2 = digraph(a,b,c); %directed graph
G3 = digraph(s,t,w2);
[mf,gf,cs,ct] = maxflow(G1,qd,zd);

% �Ǹ��ر��ӵ�ͼ
figure
H = plot(G,'Layout','layered','Sources',cs,'Sinks',ct); %minimum cut
% layout(H,'force','UseGravity',true)
highlight(H,cs,'NodeColor','red')
highlight(H,ct,'NodeColor','green')
title("�������С��");


figure
H=plot(G,'Layout','force');
j=size(G2.Edges.EndNodes); %�����
k=j(1);
for i=1:k  %��ע�ؼ�·��
  highlight(H,[G2.Edges.EndNodes(i,1),G2.Edges.EndNodes(i,2)],...
  'EdgeColor','r','LineWidth',2);
end
% H = plot(G,'Layout','layered','Sources',cs,'Sinks',ct); %minimum cut
% layout(H,'force','UseGravity',true)
title("�������С���Ӧ�Ĺؼ�·��");

%�������ǵ�����16-38��37-15
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
shijian=sparse(s,t,w2,jds,jds); %����ͼ����ת�����ڽӾ���(����)

[mf,gf,cs,ct] = maxflow(G1,qd,zd);
[P2,d2]=shortestpath(G3,qd,zd);
[P,d]=shortestpath(G,qd,zd);

figure
H = plot(G,'Layout','layered','Sources',cs,'Sinks',ct); %minimum cut
% layout(H,'force','UseGravity',true)
highlight(H,cs,'NodeColor','red')
highlight(H,ct,'NodeColor','green')
title("�Ż�����������С��1");

ans1=0;  ans2=0; ans3=0; ans4=0; m=size(P)-1;n=size(P2)-1;%n��һ����ά����
for k=1:n(2) %��С����·�Ľ����
  ans1=ans1+juli(P2(k),P2(k+1));
  ans2=ans2+shijian(P2(k),P2(k+1));
end
for k=1:m(2) %��С����·�Ľ����
  ans4=ans4+shijian(P(k),P(k+1)); %���·��ʱ��Ϊ
end
fprintf("\n�����1Ϊ��%d\n",mf);
fprintf("���·������Ϊ��%d��\n",d);
fprintf("���·��ʱ��Ϊ��%2.1f����\n",ans4);
fprintf("����·������Ϊ��%d��\n",ans1);
fprintf("����·��ʱ��Ϊ��%2.1f����\n",ans2);
G2 = digraph(s,t,w2);
[P,d]=shortestpath(G,qd,zd);
[P2,d2]=shortestpath(G2,qd,zd);
P2
size(cs);  size(ct);


%�������28-39
w1(94)=w1(94)+7; w1(124)=w1(124)-7; 
w2=w./60./w1;
G1 = digraph(s,t,w1); %directed graph
shijian=sparse(s,t,w2,jds,jds); %����ͼ����ת�����ڽӾ���(����)
[mf,gf,cs,ct] = maxflow(G1,qd,zd);
ans1=0;  ans2=0; ans3=0; ans4=0; m=size(P)-1;n=size(P2)-1;%n��һ����ά����
for k=1:n(2) %��С����·�Ľ����
  ans1=ans1+juli(P2(k),P2(k+1));
  ans2=ans2+shijian(P2(k),P2(k+1));
end
for k=1:m(2) %��С����·�Ľ����
  ans4=ans4+shijian(P(k),P(k+1)); %���·��ʱ��Ϊ
end
fprintf("\n�����2Ϊ��%d\n",mf);
fprintf("���·������Ϊ��%d��\n",d);
fprintf("���·��ʱ��Ϊ��%2.1f����\n",ans4);
fprintf("����·������Ϊ��%d��\n",ans1);
fprintf("����·��ʱ��Ϊ��%2.1f����\n",ans2);
G2 = digraph(s,t,w2);
[P,d]=shortestpath(G,qd,zd);
[P2,d2]=shortestpath(G2,qd,zd);
P2
size(cs);  size(ct);


% myplot=plot(G,'EdgeColor','k');
% highlight(myplot,P2,'EdgeColor','g','LineWidth',2);
% title("����·��");

figure
H = plot(G,'Layout','layered','Sources',cs,'Sinks',ct); %minimum cut
% layout(H,'force','UseGravity',true)
highlight(H,cs,'NodeColor','red')
highlight(H,ct,'NodeColor','green')
title("�Ż�����������С��2");

%��6-37
w1(18)=w1(18)+3;
w2=w./60./w1;
G1 = digraph(s,t,w1); %directed graph
shijian=sparse(s,t,w2,jds,jds); %����ͼ����ת�����ڽӾ���(����)
[mf,gf,cs,ct] = maxflow(G1,qd,zd);
ans1=0;  ans2=0; ans3=0; ans4=0; m=size(P)-1;n=size(P2)-1;%n��һ����ά����
for k=1:n(2) %��С����·�Ľ����
  ans1=ans1+juli(P2(k),P2(k+1));
  ans2=ans2+shijian(P2(k),P2(k+1));
end
for k=1:m(2) %��С����·�Ľ����
  ans4=ans4+shijian(P(k),P(k+1)); %���·��ʱ��Ϊ
end
fprintf("\n�����3Ϊ��%d\n",mf);
fprintf("���·������Ϊ��%d��\n",d);
fprintf("���·��ʱ��Ϊ��%2.1f����\n",ans4);
fprintf("����·������Ϊ��%d��\n",ans1);
fprintf("����·��ʱ��Ϊ��%2.1f����\n",ans2);
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
title("�Ż�����������С��3");
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%




