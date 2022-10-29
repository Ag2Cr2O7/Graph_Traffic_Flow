clc,clear,close all
jds=39;  qd=1;  zd=39;
s=load('s.txt'); t=load('t.txt'); w=load('w.txt'); 
%  w1=randi([1,14],1,124); %�����������
%  x=0;
%  while x~=19
%      w1=randi([1,14],1,124); %�����������
%      G1 = digraph(s,t,w1); %directed graph
%    [mf,gf,cs,ct] = maxflow(G1,qd,zd);
%   m=size(cs); n=size(ct);
%   x=m(1);
%  end
w1=load('final.txt'); 
w2=w./60./w1;
juli=sparse(s,t,w,jds,jds); %����ͼ����ת�����ڽӾ���(�������)
shijian=sparse(s,t,w2,jds,jds); %����ͼ����ת�����ڽӾ���(����)
G = digraph(s,t,w); %directed graph
G1 = digraph(s,t,w1); %directed graph

% end%ͼ1Ϊԭʼ����Ĵ�Ȩͼ����
figure
% plot(G,'EdgeLabel',G.Edges.Weight,'Layout','force');
plot(G,'EdgeLabel',G.Edges.Weight,'Layout','force');
title("ԭʼ��ͨ��������Ȩͼ");


%ͼ1.1Ϊԭʼ�������������
figure
plot(G1,'EdgeLabel',G1.Edges.Weight,'Layout','force');
title("ԭʼ��ͨ����������Ȩͼ");

%ͼ2�����������·����������磬ͼ�а�����·������
% �����������ͼ������������Ϻ���С���
% mf:max flow, gf:directed graph, cs: first part of the cut, ct:second
figure
[mf,gf,cs,ct] = maxflow(G1,qd,zd);
H = plot(G1,'Layout','force');
highlight(H,gf,'EdgeColor','r','LineWidth',2); %maximum flow
st = gf.Edges.EndNodes;
labeledge(H,st(:,1),st(:,2));%ͻ����ʾ��������ͼ��������ӱ�ǩ��
title("��������·�����ɵ�����");

% �Ǹ��ر��ӵ�ͼ
% figure
% H = plot(G,'Layout','layered','Sources',cs,'Sinks',ct); %minimum cut
% % layout(H,'force','UseGravity',true)
% highlight(H,cs,'NodeColor','red')
% highlight(H,ct,'NodeColor','green')
% title("�������С���Ӧ�Ĺؼ�·��");

%ͼ3������·��ͼ�����ó���
figure
myplot1=plot(gf);
layout(myplot1,'force','UseGravity',true)
title("����·�����ɵ�����");


%��ȡ����·�����ɾ������������ʱ�����
x=gf.Edges.EndNodes(:,1); %���
y=gf.Edges.EndNodes(:,2); %�յ�
z=gf.Edges.Weight; %Ȩֵ
for i=1:size(x)
%     z(i)=juli(x(i),y(i))./z(i); %z(i)��ֵΪ����
 z(i)=juli(x(i),y(i))./z(i); %��ͨ�����ʱ��Ȩֵ
 z(i)=roundn(z(i),-1); %����1λС��
end

%ͼ4�����������·����ʱ��������̵�ͼ
G2 = digraph(s,t,w2);
[P,d]=shortestpath(G,qd,zd);
[P2,d2]=shortestpath(G2,qd,zd);

% ���·��
figure
myplot=plot(G,'EdgeColor','k');
highlight(myplot,P,'EdgeColor','r','LineWidth',2);
layout(myplot,'force','UseGravity',true)
title("��㵽�յ�����·��");


figure
subplot(1,2,1)
myplot=plot(G,'EdgeColor','k');
highlight(myplot,P,'EdgeColor','r','LineWidth',2);
title("���·��");
subplot(1,2,2)
myplot=plot(G,'EdgeColor','k');
highlight(myplot,P2,'EdgeColor','g','LineWidth',2);
title("����·��");

%ͼ5������·�������·���ԱȻ�ͼ
figure
myplot=plot(G,'EdgeLabel',G.Edges.Weight,'EdgeColor','k');
highlight(myplot,P2,'EdgeColor','g','LineWidth',2);
[P,d]=shortestpath(G,qd,zd);
highlight(myplot,P,'EdgeColor','r','LineWidth',2); %���·��
title("���·��ͼ(��)������·��ͼ(��)");

%�������·���ľ���
ans1=0;  ans2=0; ans3=0; ans4=0; m=size(P)-1;n=size(P2)-1;%n��һ����ά����
for k=1:n(2) %��С����·�Ľ����
  ans1=ans1+juli(P2(k),P2(k+1));
  ans2=ans2+shijian(P2(k),P2(k+1));
end
for k=1:m(2) %��С����·�Ľ����
  ans4=ans4+shijian(P(k),P(k+1)); %���·��ʱ��Ϊ
end
fprintf("�����Ϊ��%d\n",mf);
fprintf("���·������Ϊ��%d��\n",d);
fprintf("���·��ʱ��Ϊ��%2.1f����\n",ans4);
fprintf("����·������Ϊ��%d��\n",ans1);
fprintf("����·��ʱ��Ϊ��%2.1f����\n",ans2);





