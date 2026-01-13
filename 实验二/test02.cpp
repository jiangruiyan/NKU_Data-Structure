#include<iostream>
using namespace std;

class MyCircularQueue {
public:
	//构造函数
	MyCircularQueue(int k) {
		Maxsize = k + 1;//数组大小Maxsize为队列大小k再加1，用于区分队列空和队列满的情况
		queue = new int[Maxsize];
		front = rear = 0;
	}
	//析构函数
	~MyCircularQueue() {
		delete[]queue;
	}
	bool enQueue(int value);//将元素value插入至队列尾部。若队列满，则插入失败，返回false；否则返回true
	bool deQueue();//删除队首元素。如果队列为空，则删除失败，返回false；否则返回true
	int Front();//获取队首元素。如果队列为空，则返回-1
	int Rear();//获取队尾元素。如果队列为空，则返回-1
	bool isEmpty();//判断队列是否为空
	bool isFull();//判断队列是否已满
	void Print();//打印队列所有元素
private:
	int front;
	int rear;
	int Maxsize;
	int* queue;
};
bool MyCircularQueue::enQueue(int value) {
	if (isEmpty()) {
		queue[0] = value;
		rear++;
		return true;
	}
	if (isFull()) {
		return false;
	}
	queue[rear] = value;
	rear = (rear + 1) % Maxsize;
	return true;
}
bool MyCircularQueue::deQueue() {
	if (isEmpty()) {
		return false;
	}
	front = (front + 1) % Maxsize;
	return true;
}
int MyCircularQueue::Front() {
	if (isEmpty()) {
		return  -1;
	}
	return queue[front];
}
int MyCircularQueue::Rear() {
	if (isEmpty()) {
		return  -1;
	}
	return queue[rear == 0 ? Maxsize - 1 : rear - 1];
}
bool MyCircularQueue::isEmpty() {
	return front == rear ? true : false;
}
bool MyCircularQueue::isFull() {
	return front == (rear + 1) % Maxsize ? true : false;
}
void MyCircularQueue::Print() {
	if (isEmpty()) {
		cout << "队列为空！" << endl;
	}
	else {
		for (int i = front; i != rear; i = (i + 1) % Maxsize) {
			cout << queue[i] << " ";
		}
		cout << endl;
	}
}

int main() {
	MyCircularQueue my_queue(100);
	for (int i = 0; i <= 10000; i++) {
		if (my_queue.isFull()) {
			my_queue.deQueue();
			my_queue.enQueue(i);
		}
		else {
			my_queue.enQueue(i);
		}
		if ((my_queue.Front() % 1000 == 0 && my_queue.Front() != 0) || (my_queue.Rear() % 1000 == 0 && my_queue.Rear() != 0)) {
			cout << "环形队列当前内容：" << endl;
			my_queue.Print();
		}
	}
}
