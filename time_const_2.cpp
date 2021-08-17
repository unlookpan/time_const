#include <iostream>
#include <algorithm>
using namespace std;
/*--------------------------程序简介---------------------------
满足条件：
1. 手中有物品和手中无物品选择的不一样
2. 手中有物品的情况下，只能选择偶数，且离开时，台上一定有加工
3. 手中无物品，可以选择所有奇数和有物品的偶数。同时若选择偶数，则离开时台上无加工
4. 如果去了奇数台，且去之前台上有加工，则手中有物品

过程：
1. 根据手中有无物品及台面上是否有东西判断去哪？
2. 更新位置，手上东西，台面信息，时间

程序过程：
while：
	1. 计算时间代价
	2. 根据手上是否有东西第一次判断左右边
	3. 分情况：如果有东西，则去左边。如果没东西，则还要限制不能去空台面

	4. 所有时间更新
	5. 平台和手中是否有东西更新
	6. 是否有清洗更新
-----------------------------------------------------------------*/






/*---------------------------变量定义-----------------------------*/

/*全局状态变量*/


int time_const[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};/*用来体会时间流逝的*/
int time_const_2[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};/*用来体会时间流逝的*/

int time_wait[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};//剩余等待时间

int location = 1;//当前位置

int choose = 0;//所选择的位置

int *min_time = 0;//计算的最小时间代价
int min_index = 0;//计算的最小时间代价的索引

int judge = 0;//判断机械手是否有东西
int judge_1 = 0;

int isno_have[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};//判断工作台现在是否在加工

int isno_clean = 0;//判断机器清洗的位置是否有东西




/*全局固定信息*/

int time_come[9][9] = {/*从i到j的时间*/
	0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 23, 23, 41, 41, 59, 59,
	0, 0, 0, 23, 23, 41, 41, 59, 59,
	0, 23, 23, 0, 0, 23, 23, 41, 41,
	0, 23, 23, 0, 0, 23, 23, 41, 41,
	0, 41, 41, 23, 23, 0, 0, 23, 23,
	0, 41, 41, 23, 23, 0, 0, 23, 23,
	0, 59, 59, 41, 41, 23, 23, 0, 0,
	0, 59, 59, 41, 41, 23, 23, 0, 0
};

int time_feed[9] = {0, 30, 35, 30, 35, 30, 35, 30, 35};//上料的时间

int time_clean[9] = {0, 30, 30, 30, 30, 30, 30, 30, 30};//清洗的时间

int time_work = 580;//机器工作的时间

int i_1 = 1;//全局循环参数的初始化

/*-------------------------------------------------------------------------*/








/*-----------------------------函数定义-----------------------------------*/

/*1. 计算时间代价*/

void time_const_s() {
	for (int i = 1; i < 9; i++)
		time_const[i] = time_come[location][i] + time_wait[i];
	for (int i = 1; i < 9; i++)
		time_const_2[i] = time_const[i];
}




/*2. 根据手上是否有东西第一次判断左右边                              */
/*3. 分情况：如果有东西，则去左边。如果没东西，则还要限制不能去空台面*/

void select_judge() {
	if (judge) {
		for (int i = 1; i < 9; i += 2)
			time_const_2[i] = 1000;
		for (int i = 1; i < 9; i ++ )
			cout << time_const_2[i] << " ";
	} else {
		for (int i = 2; i < 9; i += 2) {
			if (isno_have[i] == 0)
				time_const_2[i] = 1000;
		}
		for (int i = 1; i < 9; i ++ )
			cout << time_const_2[i] << " ";
	}
	cout << endl;
}

void min_index_v() {//计算最小值(做选择实施)
	//计算最小值地址
	min_time = min_element(time_const_2 + 1, time_const_2 + (sizeof(\
	                       time_const_2) / sizeof(time_const_2[0])));
	//cout << "最小值是：" << *min_time << endl;

	//计算最小值索引
	min_index = (min_time - &time_const_2[0]);
	cout << "到达：" << min_index << endl;
	choose = min_index;
	location = choose;
}




/*4. 所有时间更新*/

void time_gose() {
	if (choose % 2 == 1) {
		//其余机器：等待 = 等待-(come+wait+上料)
		for (int i = 1; i < 9; i++)
			time_wait[i] = time_wait[i] - (*min_time + time_feed[i]);
		//处理机器：等待 = 工作总时间
		time_wait[choose] = time_work;
	} else {
		location = choose;
		if (isno_clean) {
			//其余机器：等待 = 等待-(come+wait+上料+清洗)
			for (int i = 1; i < 9; i++)
				time_wait[i] = time_wait[i] - (*min_time + time_feed[i] + time_clean[i]);
			//处理机器：等待 = 工作总时间-清洗
			time_wait[choose] = time_work - time_clean[choose];
		} else {
			//其余机器：等待 = 等待-(come+wait+上料)
			for (int i = 1; i < 9; i++)
				time_wait[i] = time_wait[i] - (*min_time + time_feed[i]);
			//处理机器：等待 = 工作总时间
			time_wait[choose] = time_work;
		}
	}
}




/*5. 平台和手中是否有东西更新*/

void select_s() {
	judge_1 = judge;

	//定义这次手上是拿到了东西
	if (choose % 2 == 1) {
		if (isno_have[choose] == 1)
			judge = 1;
		else
			judge = 0;
	} else {
		judge = 0;
	}

	//在平台上放上东西
	isno_have[choose] = 1;
	//根据去之前手上是否有东西，判断走后台上是否有东西
	if (judge_1) {
	} else {
		if (choose % 2 == 0)
			isno_have[choose] = 0;
	}
	cout << judge << endl;
}




/*6. 是否有清洗更新*/
void have_clean_s() {
	//定义是否有清洗的东西
	if (choose % 2 == 0) {
		if (isno_have[choose])
			isno_clean = 1;
	}
}

void const_postive() {//辅助函数，将所有等待时间取正
	for (int i_2 = 1; i_2 < 9; i_2++) {
		if (time_wait[i_2] < 0)
			time_wait[i_2] = 0;
	}
}
/*--------------------------------------------------------------------------*/








/*----------------------------------主函数---------------------------------*/

int main() {
	for (i_1 = 1; i_1 < 100; i_1++) {

		/*1. 计算时间代价*/
		time_const_s();


		/*2. 根据手上是否有东西第一次判断左右边*/
		/*3. 分情况：如果有东西，则去左边。如果没东西，则还要限制不能去空台面*/
		select_judge();
		min_index_v();//计算最小索引及值


		/*4. 所有时间更新*/
		time_gose();


		/*5. 平台和手中是否有东西更新*/
		select_s();


		/*6. 是否有清洗更新*/
		have_clean_s();
		const_postive();//等待时间取正
	}
}
/*---------------------------------------------------------------------------*/