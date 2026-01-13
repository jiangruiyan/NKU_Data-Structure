#include<iostream>
#include<fstream>
using namespace std;
void biDirectionBubbleSort(int num, int a[]) {
	int leftBoundary = 0;
	int rightBoundary = num - 1;
	bool whetherSwap = false;//加入是否交换的判断，如果某轮没有发生交换，则说明数组已经有序，可以提前结束排序过程。
	while (leftBoundary < rightBoundary) {
		whetherSwap = false;
		for (int i = leftBoundary; i <= rightBoundary - 1; i++) {
			if (a[i] > a[i + 1]) {
				swap(a[i], a[i + 1]);
				whetherSwap = true;
			}
		}
		if (whetherSwap == false) {
			return;
		}
		rightBoundary--;//以上为从左至右遍历
		whetherSwap = false;
		for (int i = rightBoundary; i >= leftBoundary + 1; i--) {
			if (a[i] < a[i - 1]) {
				swap(a[i], a[i - 1]);
				whetherSwap = true;
			}
		}
		if (whetherSwap == false) {
			return;
		}
		leftBoundary++;//以上为从右至左遍历
	}
}
int main() {
	ifstream ifs;
	ifs.open("input.txt", ios::in);
	if (!ifs.is_open()) {
		cout << "ERROR" << endl;
		return 0;
	}//检查文件是否存在
	int num;
	ifs >> num;
	if (!(num >= 1 && num <= 100)) {
		cout << "ERROR" << endl;
		return 0;
	}//判断数组大小n是否符合要求
	int* pa = new int[num];
	int i = 0;
	while (ifs >> pa[i]) {
		i++;
	}
	if (i != num) {
		cout << "ERROR" << endl;
		return 0;
	}//判断是否输入了n个数
	ifs.close();
	biDirectionBubbleSort(num, pa);
	for (int i = 0; i < num; i++) {
		cout << pa[i] << " ";
	}
	cout << endl;
}