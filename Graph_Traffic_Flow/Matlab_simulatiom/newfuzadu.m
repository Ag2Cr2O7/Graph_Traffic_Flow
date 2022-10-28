clc,clear,close all
k=3.5;
x=0:0.1:40;
y1=x.*x.*k; %ve
y2=x.*x; %ve
% y3=2.*k*x;
y4=k.*x.*log2(x);
y5=x.*log2(x)+k.*x;
% y5=x.*x.*x;
plot(x,y1,'g',x,y2,'m',x,y4,'b',x,y5,'r','LineWidth',0.8);
axis([0,30,-50,1000]);
legend('O(VE)','O(V^2)','O(ElogV)','O(VlogV+E)','Location','NorthWest');
title('ShortestPath');
grid on;

figure(2);
k=3.5;
x=0:0.1:40;
% f=100;
y1=x.*k.*100; %ve
y2=x.*x.*x.*k;
y3=(2.*k).^2.*x;
y4=x.*k.*30; %ve
plot(x,y1,'g',x,y4,'m',x,y2,'b',x,y3,'r','LineWidth',0.8);
axis([0,30,-50,2000]);
legend('O(Ef=100)','O(Ef=30)','O(VE^2)','O(V^2E)','Location','NorthEast');
title('MaxFlow');
grid on;
