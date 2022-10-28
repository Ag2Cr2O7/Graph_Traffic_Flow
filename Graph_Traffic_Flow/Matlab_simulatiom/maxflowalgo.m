clc,clear,close all
jds=39;  qd=1;  zd=39;
s=load('s.txt'); t=load('t.txt'); w=load('w.txt'); 
w1=load('final.txt'); 
w2=w./60./w1;
% zg=sparse(x,y,z,jds,jds); 
% plot(zg);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
C=sparse(s,t,w1,jds,jds)
[f, maxflow] = Maxflow(C);
fprintf('算法计算得出最大流f=%d\n',maxflow)
%f 流量分配方案
%由C表我们知道，1为s点，9为t点
%maxflow 最大流量
function [f, maxflow] = Maxflow(C)
    [row,column] = size(C);
    s = 1;
    t = column;
    f = zeros(row);%f矩阵为流量分配矩阵，初始化为0矩阵，
    maxflow = 0;
    %运用BFS搜索进行遍历，使用queue
    while 1
        vis = [];%表示已经访问过的节点
        vis = [vis s];
        queue_head = s;%队头
        queue_tail = s;%队尾
        queue = zeros( 1, row);%队列当作存放节点容器，先进先出原则
        queue( queue_head) = s;
        queue_head = queue_head + 1;
        per = zeros( 1, row);%表示每个节点的前驱节点
        per( s) = s;
        while queue_tail ~= queue_head
            pos = queue( queue_tail);
            for nxt = 1:row
                if C( pos, nxt)-f( pos, nxt)>0 && isempty( find(vis == nxt,1))
                    queue( queue_head) = nxt;
                    queue_head = queue_head + 1;
                    vis = [vis nxt];
                    per(nxt) = pos;
                end
            end
            queue_tail = queue_tail + 1;
        end
        
        if per(t) == 0%无法到达汇点，算法结束
            break;
        end
        %从汇点出发反向回到源点
        path = [];%记录路径
        pos_tmp = row;
        e_cnt = 0;%经过的边数
        while pos_tmp ~= s
            if C(per(pos_tmp),pos_tmp)-f(per(pos_tmp),pos_tmp)>0
                e_val = C(per(pos_tmp),pos_tmp)-f(per(pos_tmp),pos_tmp);
                path = [path;per(pos_tmp) pos_tmp e_val 1];%表示正向边
                pos_tmp = per( pos_tmp);
            end
            if C(pos_tmp,per(pos_tmp)) > 0 && f(pos_tmp,per(pos_tmp))>0
                e_val = f(pos_tmp,per(pos_tmp));
                path = [path;per(pos_tmp) pos_tmp e_val -1];%表示反向边
                pos_tmp = per( pos_tmp);
            end
                
            e_cnt = e_cnt + 1;
        end
        min_val = min(path(:,3));
        maxflow = maxflow + min_val;
        for pos = 1:e_cnt
            if path(pos,4) == 1
                f( path(pos,1),path(pos,2)) = f( path(pos,1),path(pos,2)) + min_val;
            else
                f( path(pos,1),path(pos,2)) = f( path(pos,1),path(pos,2)) - min_val;
            end
        end
    end
end
