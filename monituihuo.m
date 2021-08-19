clc;clear;
%---------------------定义变量--------------------%
%温度变量
T = 57000;
%分析值
rande = unifrnd(1,100,100,1);
%每次的执行次数
c = 100;
%退火速度
dt = 0.98;
%温度停止阈值
Tt = 1;
%迭代值
i = 50;
minx = rande(i);%实质都表示最大值（每次迭代的最大值）
maxx = rande(i);%每段迭代后保存的最大值
de = 0;
%以上两个变量迭代的数值集合
minxs = [0,0];
maxxs = [0,0];

%------------------------主程序---------------------%
while T > Tt
    for j = 1:c
        rande_1 = rande(i);
        %扰动初始值
        s = unifrnd(-5,5,1,1);
        s = round(s);
        i = i + s;
        i(i<1) = 1;
        i(i>100) = 100;
        rande_2 = rande(i);

        %判断是否选择
        de = rande_2 - rande_1;
        if de >= 0
            minx = rande_2; 
            minxs = [minxs rande_2];
        else
            if de_1>0 && de<0
                if maxx < rande_1
                    maxx = rande_1;
                    maxxs = [maxxs rande_1];
                end
            end
            if exp(-de / T) > rand(1,1)
                minx = rande_2;
           end
        end
        de_1 = de;
    end
    T = T * dt;
end

%-------------------------显示结果-------------------------%
%显示最大值
X = max(rande);disp(X);
%显示所求的的两个最大值
disp(maxx);
disp(minx);
%对求得的最大值过程绘图
subplot(2,1,1);plot(minxs);
subplot(2,1,2);plot(maxxs);




