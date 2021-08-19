clc;clear;
%--------------------定义变量---------------------%
%定义固定变量
time_come = [%从i到j的时间
	0, 0, 23, 23, 41, 41, 59, 59;
	0, 0, 23, 23, 41, 41, 59, 59;
	23, 23, 0, 0, 23, 23, 41, 41;
	23, 23, 0, 0, 23, 23, 41, 41;
	41, 41, 23, 23, 0, 0, 23, 23;
	41, 41, 23, 23, 0, 0, 23, 23;
	59, 59, 41, 41, 23, 23, 0, 0;
	59, 59, 41, 41, 23, 23, 0, 0
];
time_feed = [30, 35, 30, 35, 30, 35, 30, 35];
time_clean = [30, 30, 30, 30, 30, 30, 30, 30];
time_work = 580;
i1 = 1;

%定义状态变量
time_consts = [0, 0, 0, 0, 0, 0, 0, 0];
time_consts_2 = [0, 0, 0, 0, 0, 0, 0, 0];
time_wait = [0, 0, 0, 0, 0, 0, 0, 0];
location = 1;
judge = 0;
isno_work = [0, 0, 0, 0, 0, 0, 0, 0, 0];
isno_clean = 0;

%------------------------主程序------------------------%
for j = 1:100
    %计算时间代价
    time_consts = time_const_s(location,time_wait,time_come);
    %判断左右，同时防止左边去往无加工
    time_consts_2 = select_const(judge,time_consts,isno_work);
    disp(time_consts_2);
    [minx,location] = min(time_consts_2);
    X = sprintf('最小值：%d',minx);
    Y = sprintf('最小值索引：%d',location);
    disp([X,Y])
    %更新时间
    time_wait = time_gise(location,time_wait,minx,isno_clean,time_feed,time_work);
    disp(time_wait);
    %更新状态
    [judge,isno_work] = over_work(location,isno_work,judge);
    %更新清洗状态
    isno_cleans(location,isno_work);
end
disp(isno_work);

%-----------------------定义函数-----------------------%
%计算时间代价
function timeconst = time_const_s(loc,twait,tcome)
    timeconst = [0,0,0,0,0,0,0,0];
    for i = 1:8
        timeconst(i) = twait(i)+tcome(loc,i);
    end
end
%判断左右，同时防止左边去往无加工
function time_consts_2 = select_const(judge,time_constss_2,isno_work)
    if judge ==1
        for i = 1:2:8
            time_constss_2(i) = 1000;
        end
    else
       for i = 2:2:8
          if isno_work(i) == 0
             time_constss_2(i) = 1000; 
          end
       end
    end
    time_consts_2 = time_constss_2;
end
%更新时间
function time_wait = time_gise(location,time_waits,minx,isno_clean,time_feed,time_work)
    if mod(location , 2) == 2
        time_wait = time_waits - (minx + time_feed);
        time_wait(location) = time_work;
    else
        if isno_clean ==1
            time_wait = time_waits - (minx + time_feed + time_clean);
            time_wait(location) = time_work - time_clean(location);
        else
            time_wait = time_waits - (minx + time_feed);
            time_wait(location) = time_work;
        end
    end
    time_wait(time_wait<0) = 0;
end
%更新状态
function [judge,isno_work] = over_work(location,isno_works,judge)
   judges = judge;
   isno_work = isno_works;
   if mod(location,2) == 1
       if isno_works(location) ==1
           judge = 1;
       else
           judge = 0;
       end
   else
       judge = 0;
   end
   isno_work(location) = 1;
   if judges == 1
       
   else
       if mod(location,2) ==0
           isno_work(location) = 0;
       end
   end
   
end
%更新清洗状态
function isno_cleans(location,isno_work)
    global isno_clean
    if mod(location,2) == 0
        if isno_work(location) == 1
            isno_clean = 1;
        end
    end
end