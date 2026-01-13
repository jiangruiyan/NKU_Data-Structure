#include<iostream>
using namespace std;

//节点类TreeNode
class TreeNode {
public:
	int value;
	int num;
	TreeNode* leftChild, * rightChild;
	TreeNode(int value);//构造函数
};
TreeNode::TreeNode(int value) {
	this->value = value;
	this->leftChild = this->rightChild = nullptr;
}

//搜索二叉树类BinarySearchTree
class BinarySearchTree {
public:
	TreeNode* root;
	int maxNumber = 0;//最大节点序号
	BinarySearchTree();//构造函数

	//插入节点
	void insertNode(int n);

	//打印二叉树
	void print();

	//判断序号为n的节点是否存在（其中包含bool型局部变量flag，值默认为false）
	bool isNumExisted(TreeNode* treeNode, int n);
	//若序号为n的节点存在，则将flag的值修改为true，与上一函数一起使用
	void judgeNumExisted(TreeNode* treeNode, int n, bool& flag);

	//判断值为n的节点是否存在（其中包含bool型局部变量flag，值默认为false）
	bool isValExisted(TreeNode* treeNode, int n);
	//若值为n的节点存在，则将flag的值修改为true，与上一函数一起使用
	void judgeValExisted(TreeNode* treeNode, int n, bool& flag);

	//搜索序号为n的节点的地址，并保存在rec中
	void getNumNode(TreeNode* treeNode, int n, TreeNode*& rec);
	//搜索值为n的节点的地址，并保存在rec中
	void getValNode(TreeNode* treeNode, int n, TreeNode*& rec);

	//后序遍历：输出r的下一个节点的值
	void printPostNext(TreeNode* r);
	//中序遍历：输出r的下一个节点的值
	void printInNext(TreeNode* r);
};
BinarySearchTree::BinarySearchTree() {
	root = nullptr;
}
void BinarySearchTree::insertNode(int n) {
	TreeNode* temp = root;
	TreeNode* tempParent = nullptr;
	while (temp) {
		tempParent = temp;
		if (n == temp->value) {
			cout << "值重复，插入失败！" << endl;
			return;
		}
		if (n < temp->value) {
			temp = temp->leftChild;
		}
		else {
			temp = temp->rightChild;
		}
	}
	TreeNode* r = new TreeNode(n);
	if (this->root == nullptr) {
		this->root = r;
		r->num = 1;
		if (r->num > maxNumber) {
			maxNumber = r->num;
		}
		return;
	}
	if (n < tempParent->value) {
		tempParent->leftChild = r;
		r->num = 2 * tempParent->num;
		if (r->num > maxNumber) {
			maxNumber = r->num;
		}
	}
	else {
		tempParent->rightChild = r;
		r->num = 2 * tempParent->num + 1;
		if (r->num > maxNumber) {
			maxNumber = r->num;
		}
	}
	return;
}
//----------------------------Bad Function!----------------------------
void BinarySearchTree::print() {
	TreeNode* temp1 = nullptr;
	getNumNode(root, 1, temp1);
	TreeNode* temp2 = nullptr;
	getNumNode(root, 2, temp2);
	TreeNode* temp3 = nullptr;
	getNumNode(root, 3, temp3);
	TreeNode* temp4 = nullptr;
	getNumNode(root, 4, temp4);
	TreeNode* temp5 = nullptr;
	getNumNode(root, 5, temp5);
	TreeNode* temp7 = nullptr;
	getNumNode(root, 7, temp7);
	TreeNode* temp8 = nullptr;
	getNumNode(root, 8, temp8);
	TreeNode* temp9 = nullptr;
	getNumNode(root, 9, temp9);
	cout << "结构：" << endl;
	cout << "      " << temp1->value << endl;
	cout << "     / \\" << endl;
	cout << "    " << temp2->value << "  " << temp3->value << endl;
	cout << "   / \\   \\" << endl;
	cout << "  " << temp4->value << "  " << temp5->value << "  " << temp7->value << endl;
	cout << " / \\" << endl;
	cout << temp8->value << "  " << temp9->value << endl;
}
//----------------------------Bad Function!----------------------------
void BinarySearchTree::judgeNumExisted(TreeNode* treeNode, int n, bool& flag) {
	if (treeNode == nullptr) {
		return;
	}//若为空则直接返回，不修改flag
	if (n == treeNode->num) {
		flag = true;
		return;
	}
	if (treeNode->leftChild != nullptr) {
		judgeNumExisted(treeNode->leftChild, n, flag);
	}
	if (treeNode->rightChild != nullptr) {
		judgeNumExisted(treeNode->rightChild, n, flag);
	}
	return;
}
bool BinarySearchTree::isNumExisted(TreeNode* treeNode, int n) {
	bool flag = false;
	judgeNumExisted(treeNode, n, flag);
	return flag;
}
void BinarySearchTree::judgeValExisted(TreeNode* treeNode, int n, bool& flag) {
	if (treeNode == nullptr) {
		return;
	}//若为空则直接返回，不修改flag
	if (n == treeNode->value) {
		flag = true;
	}
	if (treeNode->leftChild != nullptr) {
		judgeValExisted(treeNode->leftChild, n, flag);
	}
	if (treeNode->rightChild != nullptr) {
		judgeValExisted(treeNode->rightChild, n, flag);
	}
	return;
}
bool BinarySearchTree::isValExisted(TreeNode* treeNode, int n) {
	bool flag = false;
	judgeValExisted(treeNode, n, flag);
	return flag;
}
void BinarySearchTree::getNumNode(TreeNode* treeNode, int n, TreeNode*& rec) {
	if (treeNode->num == n) {
		rec = treeNode;
		return;
	}
	else {
		if (treeNode->leftChild != nullptr) {
			getNumNode(treeNode->leftChild, n, rec);
		}
		if (treeNode->rightChild != nullptr) {
			getNumNode(treeNode->rightChild, n, rec);
		}
	}
	return;
}
void BinarySearchTree::getValNode(TreeNode* treeNode, int n, TreeNode*& rec) {
	if (treeNode->value == n) {
		rec = treeNode;
		return;
	}
	else {
		if (treeNode->leftChild != nullptr) {
			getValNode(treeNode->leftChild, n, rec);
		}
		if (treeNode->rightChild != nullptr) {
			getValNode(treeNode->rightChild, n, rec);
		}
	}
	return;
}
void BinarySearchTree::printPostNext(TreeNode* r) {
	int nodeNum = r->num;
	if (nodeNum == 1) {
		cout << "无后续节点！";
		return;
	}
	if (nodeNum % 2 == 1 || !isNumExisted(this->root, nodeNum + 1)) {
		TreeNode* temp01 = nullptr;
		getNumNode(this->root, nodeNum / 2, temp01);
		cout << temp01->value;
		return;
	}
	TreeNode* temp02 = nullptr;
	getNumNode(this->root, nodeNum + 1, temp02);
	while (!(temp02->leftChild == nullptr && temp02->rightChild == nullptr)) {
		if (temp02->leftChild != nullptr) {
			temp02 = temp02->leftChild;
		}
		else {
			temp02 = temp02->rightChild;
		}
	}
	cout << temp02->value;
}
void BinarySearchTree::printInNext(TreeNode* r) {
	//暂不需要
}

//返回数组中比指定元素val大的最小元素
void printNext(int* p, int num, int val) {
	int* rank = new int[num];
	for (int i = 0; i < num; i++) {
		rank[i] = 0;
		for (int j = 0; j < num; j++) {
			if (p[j] < p[i]) {
				rank[i]++;
			}
		}
	}
	for (int i = 0; i < num; i++) {
		if (p[i] == val) {
			for (int j = 0; j < num; j++) {
				if (rank[j] == rank[i] + 1) {
					cout << p[j];
					return;
				}
			}
		}
	}
	cout << "无后续节点！";
	return;
}

int main() {
	//创建搜索二叉树
	BinarySearchTree myBinarySearchTree;

	//插入元素
	int count = 0;
	cout << "请输入元素个数：";
	cin >> count;
	int* input = new int[count];
	for (int i = 0; i < count; i++) {
		cin >> input[i];
		myBinarySearchTree.insertNode(input[i]);
	}

	//输出二叉树
	myBinarySearchTree.print();

	//输出后序遍历的下一个节点
	int nodeVal1 = 0;
	cout << "请输入节点1：";
	cin >> nodeVal1;
	if (myBinarySearchTree.isValExisted(myBinarySearchTree.root, nodeVal1)) {
		cout << "后序遍历下一节点为：";
		TreeNode* temp1 = nullptr;
		myBinarySearchTree.getValNode(myBinarySearchTree.root, nodeVal1, temp1);
		myBinarySearchTree.printPostNext(temp1);
		cout << endl;
	}
	else {
		cout << "节点不存在！" << endl;
	}

	//输出中序遍历的下一个节点
	int nodeVal2 = 0;
	cout << "请输入节点2：";
	cin >> nodeVal2;
	if (myBinarySearchTree.isValExisted(myBinarySearchTree.root, nodeVal2)) {
		printNext(input, count, nodeVal2);
		cout << endl;
	}
	else {
		cout << "节点不存在！" << endl;
	}

	//输出替换后的二叉树
	BinarySearchTree myBinarySearchTree02;
	cout << "替换后为：" << endl;
	int* input02 = new int[count];
	for (int i = 0; i < count; i++) {
		input02[i] = input[i];
		for (int j = 0; j < count; j++) {
			if (input[j] < input[i]) {
				input02[i] += input[j];
			}
		}
		myBinarySearchTree02.insertNode(input02[i]);
	}
	myBinarySearchTree02.print();
}