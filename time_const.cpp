#include <iostream>
#include <algorithm>
using namespace std;

//��������
int time_const[5] = {0, 0, 0, 0, 0};

int time_come[5][5] = {
	0, 0, 0, 0, 0,
	0, 0, 0, 1, 1,
	0, 0, 0, 1, 1,
	0, 1, 1, 0, 0,
	0, 1, 1, 0, 0,
};

int time_wait[5] = {0, 0, 0, 0, 0};
int location = 1;

int time_feed[5] = {0, 1, 1, 1, 1};

int time_clean[5] = {0, 1, 1, 1, 1};
int choose = 0;
int *min_time = 0;
int min_index = 0;
int isno_clean = 0;
int time_work = 5;
//��������

//������
int main() {
	for (int i_1 = 1; i_1 < 100; i_1++) {

		//����ʱ�����
		for (int i = 1; i < 5; i++) {
			time_const[i] = time_come[location][i] + time_wait[i];
		}
		for (int i = 1; i < 5; i++) {
			cout << time_const[i];
		}
		cout << endl;

		//������Сֵ��ַ
		min_time = min_element(time_const + 1, time_const + (sizeof(time_const) / sizeof(\
		                       time_const[0])));
		cout << "��Сֵ�ǣ�" << *min_time << endl;

		//������Сֵ����
		min_index = (min_time - &time_const[0]);
		cout << "���" << min_index << endl;

		//ѡ����һ��λ��
		choose = min_index;

		//ʱ������
		if (isno_clean) {
			location = choose;
			//����������ȴ� = �ȴ�-(come+wait+����+��ϴ)
			for (int i = 1; i < 5; i++) {
				time_wait[i] = time_wait[i] - (*min_time + time_feed[i] + time_clean[i]);
			}
			//����������ȴ� = ������ʱ��-��ϴ
			time_wait[choose] = time_work - time_clean[choose];
		} else {
			location = choose;
			//����������ȴ� = �ȴ�-(come+wait+����)
			for (int i = 1; i < 5; i++) {
				time_wait[i] = time_wait[i] - (*min_time + time_feed[i]);
			}
			//����������ȴ� = ����ʱ��
			time_wait[choose] = time_work;
			//��ʼ��ϴ
			isno_clean = 1;
		}
		for (int i_2 = 1; i_2 < 5; i_2++) {
			if (time_wait[i_2] < 0) {
				time_wait[i_2] = 0;
			}
		}
	}
}