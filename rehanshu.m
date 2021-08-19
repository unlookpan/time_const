clc;clear;
%----------------------定义初值----------------------%
%基本常数
h = 14.458;
k = 1.67e-6;
r = 4.437e-11;
%外界温度
T1 = 448;
%基准温度
Tz = 275;
%温度
size_t = 200;
delta_t = 1;
%距离
th_x = 0.15e-3;%0.15mm
delta_x = 1e-6;%1e-3mm
size_x = round(th_x/delta_x+1);%为什么+1，凑奇数
%初始化起始矩阵（T）：填充初值
T = zeros(size_x,size_t);
T(:,1) = ones(size_x,1).*(25+Tz);
%初始化参数（M矩阵）
one1 = h + k/delta_x;
one2 = -k/delta_x;
A = r*delta_t/(2*delta_x^2);
M = zeros(size_x,size_x);
M(1,1) = one1;
M(1,2) = one2;
M(size_x,size_x) = one1;
M(size_x,size_x-1) = one2;
for i = 2:size_x-1
    M(i,i-1) = A;
    M(i,i) = -(2*A + 1);
    M(i,i+1) = A;
end

%----------------------求解--------------------%
%初始化（N）矩阵
N = zeros(size_x,1);
%外循环（每一时刻）
for j = 2:size_t
    %N处边缘的值
    N(1) = h*T1;
    N(size_x) = h*T1;
    %内循环（每一处x的值）
    for i = 2:size_x-1
        N(i) = -1*A*T(i-1,j-1) + (2*A-1)*T(i,j-1) + -1*A*T(i+1,j-1);
    end
    T(:,j) = M\N;
    disp(N);
end

%----------------------显示结果-----------------%
disp(T(75,:));
mesh(T);


 
 