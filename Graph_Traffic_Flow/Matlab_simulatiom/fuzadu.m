clc,clear,close all
subplot(1,2,1)
k=3;
x=0:0.1:30;
y1=x.*x.*k; %ve
y2=x.*x; %ve
y3=2.*k*x;
y4=k.*x.*log2(x);
y5=x.*log2(x)+k.*x;
% y5=x.*x.*x;
plot(x,y1,'g',x,y2,'m',x,y3,'c',x,y4,'b',x,y5,'r','LineWidth',1.5);
axis([0,30,-50,1000]);
legend('O(VE)','O(V^2)','O(kE)','O(ElogV)','O(VlogV+E)','Location','NorthWest');
title('E=3V');
subplot(1,2,2)
k=4;
x=0:0.1:30;
y1=x.*x.*k; %ve
y2=x.*x; %ve
y3=2.*k*x;
y4=k.*x.*log2(x);
y5=x.*log2(x)+k.*x;
% y5=x.*x.*x;
plot(x,y1,'g',x,y2,'m',x,y3,'c',x,y4,'b',x,y5,'r','LineWidth',1.5);
legend('O(VE)','O(V^2)','O(kE)','O(ElogV)','O(VlogV+E)','Location','NorthWest');
axis([0,30,-50,1000]);
title('E=4V');