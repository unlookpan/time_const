#include <iostream>
#include <algorithm>
using namespace std;

//变量定义
int time_const[5] = {0, 0, 0, 0, 0};

int time_come[5][5] = {
	0, 0, 0, 0, 0,
	0, 0, 0, 1, 1,
	0, 0, 0, 1, 1,
	0, 1, 1, 0, 0,
	0, 1, 1, 0, 0,
};


//sdfsjfksjklfjskl
int time_wait[5] = {0, 0, 0, 0, 0};
int location = 1;

int time_feed[5] = {0, 1, 1, 1, 1};

int time_clean[5] = {0, 1, 1, 1, 1};
int choose = 0;
int *min_time = 0;
int min_index = 0;
int isno_clean = 0;
int time_work = 5;
//函数定义

//主函数
int main() {
	for (int i_1 = 1; i_1 < 100; i_1++) {

		//计算时间代价
		for (int i = 1; i < 5; i++) {
			time_const[i] = time_come[location][i] + time_wait[i];
		}
		for (int i = 1; i < 5; i++) {
			cout << time_const[i];
		}
		cout << endl;

		//计算最小值地址
		min_time = min_element(time_const + 1, time_const + (sizeof(time_const) / sizeof(\
		                       time_const[0])));
		cout << "最小值是：" << *min_time << endl;

		//计算最小值索引
		min_index = (min_time - &time_const[0]);
		cout << "到达：" << min_index << endl;

		//选择下一次位置
		choose = min_index;

		//时间流逝
		if (isno_clean) {
			location = choose;
			//其余机器：等待 = 等待-(come+wait+上料+清洗)
			for (int i = 1; i < 5; i++) {
				time_wait[i] = time_wait[i] - (*min_time + time_feed[i] + time_clean[i]);
			}
			//处理机器：等待 = 工作总时间-清洗
			time_wait[choose] = time_work - time_clean[choose];
		} else {
			location = choose;
			//其余机器：等待 = 等待-(come+wait+上料)
			for (int i = 1; i < 5; i++) {
				time_wait[i] = time_wait[i] - (*min_time + time_feed[i]);
			}
			//处理机器：等待 = 工作时间
			time_wait[choose] = time_work;
			//开始清洗
			isno_clean = 1;
		}
		for (int i_2 = 1; i_2 < 5; i_2++) {
			if (time_wait[i_2] < 0) {
				time_wait[i_2] = 0;
			}
		}
	}
}
