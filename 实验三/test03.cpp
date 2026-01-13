#include<iostream>
using namespace std;

//求a,b较大者函数
int max(int a, int b) {
	return a >= b ? a : b;
}

//判断左右路径，true为左路径，false为右路径（a为b的祖先序号）
bool leftOrRight(int a, int b) {
	while (b / 2 != a) {
		b /= 2;
	}
	return b == 2 * a ? true : false;
}

//节点类TreeNode
class TreeNode {
public:
	int value;
	int num;
	TreeNode* leftChild, * rightChild;
	TreeNode* parent;
	TreeNode(int value, int num);//构造函数
};
TreeNode::TreeNode(int value, int num) {
	this->value = value;
	this->num = num;
	this->leftChild = this->rightChild = nullptr;
}

//二叉树类BinaryTree
class BinaryTree {
public:
	TreeNode* root;
	int maxNumber = 0;//最大节点序号
	BinaryTree();//构造函数

	//以下函数的treeNode参数均表示将treeNode作为根节点来看
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
	//以上两函数参数rec一定不要忘引用（否则形参不能改变实参）

	//创建一个值为value、序号为n的节点
	void insertNode(int value, int num);

	//输出从节点ancestor到节点descendant的路径，其中ancestor是descendant祖先
	void printOnePath(TreeNode* ancestor, TreeNode* descendant);
	//以treeNode为根节点遍历到其所有叶节点的路径，与上两函数一起使用
	void printPath(TreeNode* treeNode);

	//判断序号为a的节点是否为序号为b的祖先
	bool isAncestor(int a, int b);

	//返回以treeNode为根节点的最大路径和（路径不一定经过根节点）
	int maxPathVal(TreeNode* treeNode);
	//返回以treeNode为根节点的最大路径和（路径经过根节点）
	int maxPath(TreeNode* treeNode);
	//返回从节点ancestor到节点descendant的路径最大和，其中ancestor是descendant祖先
	int onePathMax(TreeNode* ancestor, TreeNode* descendant);
	//返回从节点ancestor到节点descendant的路径和，其中ancestor是descendant祖先
	int pathSum(TreeNode* ancestor, TreeNode* descendant);
};
BinaryTree::BinaryTree() {
	root = nullptr;
}
void BinaryTree::judgeNumExisted(TreeNode* treeNode, int n, bool& flag) {
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
bool BinaryTree::isNumExisted(TreeNode* treeNode, int n) {
	bool flag = false;
	judgeNumExisted(treeNode, n, flag);
	return flag;
}
void BinaryTree::judgeValExisted(TreeNode* treeNode, int n, bool& flag) {
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
bool BinaryTree::isValExisted(TreeNode* treeNode, int n) {
	bool flag = false;
	judgeValExisted(treeNode, n, flag);
	return flag;
}
void BinaryTree::getNumNode(TreeNode* treeNode, int n, TreeNode*& rec) {
	if (treeNode->num == n) {
		rec = treeNode;
		return;
	}
	else {
		if (treeNode->leftChild != nullptr) {
			getNumNode(treeNode->leftChild, n,rec);
		}
		if (treeNode->rightChild != nullptr) {
			getNumNode(treeNode->rightChild, n,rec);
		}
	}
	return;
}
void BinaryTree::getValNode(TreeNode* treeNode, int n, TreeNode*& rec) {
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
void BinaryTree::insertNode(int value, int num) {
	if (isNumExisted(this->root, num)) {
		cout << "创建失败，节点已存在！" << endl;
		return;
	}//若序号重复，则创建失败
	if (isValExisted(this->root, value)) {
		cout << "创建失败，值重复！" << endl;
		return;
	}//若值重复，则创建失败
	if (num == 1) {
		TreeNode* temp = new TreeNode(value, num);
		this->root = temp;
		this->root->parent = nullptr;//根节点的父节点为空
		if (num > this->maxNumber) {
			this->maxNumber = num;
		}
		cout << "创建成功！" << endl;
		return;
	}//创建序号为1的节点（即根节点）
	//下面创建其他节点时，先判断父节点（序号为(int)num/2）是否存在
	if (isNumExisted(this->root, num / 2)) {
		TreeNode* temp = new TreeNode(value, num);
		getNumNode(this->root, num / 2, temp->parent);
		//若存在，则若num为偶数则为父节点的左孩子，若num为奇数则为父节点的右孩子
		if (num % 2 == 0) {
			temp->parent->leftChild = temp;
		}
		else {
			temp->parent->rightChild = temp;
		}
		if (num > this->maxNumber) {
			this->maxNumber = num;
		}
		cout << "创建成功！" << endl;
		return;
	}
	cout << "创建失败，没有找到父节点！" << endl;
	return;//没有找到父节点的情况
}
void BinaryTree::printOnePath(TreeNode* ancestor, TreeNode* descendant) {
	if (descendant->parent == ancestor) {
		cout << "->" << descendant->value;
	}
	else {
		printOnePath(ancestor, descendant->parent);
		cout << "->" << descendant->value;
	}
}
void BinaryTree::printPath(TreeNode* treeNode) {
	cout << "路径列表：" << endl;
	TreeNode* temp = nullptr;
	int count = 1;
	for (int i = 1; i <= this->maxNumber; i++) {
		getNumNode(treeNode, i, temp);
		//找到所有叶子结点，再调用printOnePath函数即可
		//满足1.序号为i的节点存在；2.treeNode是序号为i的节点的祖先；3.序号为i的节点左右子树均为空
		if (isNumExisted(treeNode, i) && isAncestor(treeNode->num, i) && temp->leftChild == nullptr && temp->rightChild == nullptr) {
			cout << "路径" << count << "：" << treeNode->value;
			printOnePath(treeNode, temp);
			cout << endl;
			count++;
		}
	}
}
bool BinaryTree::isAncestor(int a, int b) {
	if (a >= b) {
		return false;
	}
	while (b) {
		if (a == b) {
			return true;
		}
		b /= 2;
	}
	return false;
}
int BinaryTree::maxPathVal(TreeNode* treeNode) {
	int maxRoute = INT_MIN;
	TreeNode* temp = nullptr;
	//以所有符合条件的节点作为根节点，求出各自的最大路径和，结果取最大即可
	for (int i = 1; i <= this->maxNumber; i++) {
		getNumNode(treeNode, i, temp);
		//节点需存在并且是treeNode或者treeNode的后代
		if (isNumExisted(treeNode, i) && (temp == treeNode || isAncestor(treeNode->num, i))) {
			if (maxPath(temp) > maxRoute) {
				maxRoute = maxPath(temp);
			}
		}
	}
	return maxRoute;
}
int BinaryTree::maxPath(TreeNode* treeNode) {
	TreeNode* temp = nullptr;
	int maxPathValue = treeNode->value;
	int leftPathMax = treeNode->value;
	int rightPathMax = treeNode->value;
	for (int i = 1; i <= this->maxNumber; i++) {
		getNumNode(treeNode, i, temp);
		//找到所有叶子结点，再调用onePathMax函数
		//分别计算左路径、右路径、左路径+右路径，取最大
		//满足1.序号为i的节点存在；2.treeNode是序号为i的节点的祖先；3.序号为i的节点左右子树均为空
		if (isNumExisted(treeNode, i) && isAncestor(treeNode->num, i) && temp->leftChild == nullptr && temp->rightChild == nullptr) {
			if (leftOrRight(treeNode->num, temp->num)) {
				if (onePathMax(treeNode, temp) > leftPathMax) {
					leftPathMax = onePathMax(treeNode, temp);
				}
			}
			else {
				if (onePathMax(treeNode, temp) > rightPathMax) {
					rightPathMax = onePathMax(treeNode, temp);
				}
			}
		}
	}
	if (leftPathMax > maxPathValue) {
		maxPathValue = leftPathMax;
	}
	if (rightPathMax > maxPathValue) {
		maxPathValue = rightPathMax;
	}
	if (rightPathMax + leftPathMax - treeNode->value > maxPathValue) {
		maxPathValue = rightPathMax + leftPathMax - treeNode->value;
	}
	return maxPathValue;
}
int BinaryTree::onePathMax(TreeNode* ancestor, TreeNode* descendant) {
	int maxPath = INT_MIN;
	while (descendant != ancestor) {
		if (pathSum(ancestor, descendant) > maxPath) {
			maxPath = pathSum(ancestor, descendant);
		}
		descendant = descendant->parent;
	}
	return maxPath;
}
int BinaryTree::pathSum(TreeNode* ancestor, TreeNode* descendant) {
	int path = ancestor->value;
	while (descendant != ancestor) {
		path += descendant->value;
		descendant = descendant->parent;
	}
	return path;
}

int main() {
	//创建二叉树
	BinaryTree myBinaryTree;
	cout << "输入i插入节点，输入其他任意字符停止插入" << endl;
	char con;
	cin >> con;
	int num, val;
	while (con == 'i') {
		cout << "请输入插入节点的序号：";
		cin >> num;
		cout << "请输入插入节点的值：";
		cin >> val;
		myBinaryTree.insertNode(val, num);
		cin >> con;
	}
	
	//输入两个指定节点
	int val1, val2;//两个指定节点的值
	bool loopFlag1 = true;
	while (loopFlag1) {
		cout << "请输入两个指定节点的值：";
		cin >> val1 >> val2;
		if (!(myBinaryTree.isValExisted(myBinaryTree.root, val1) && myBinaryTree.isValExisted(myBinaryTree.root, val2))) {
			cout << "值在二叉树中不存在，请重新输入！" << endl;
			continue;
		}//若值不存在，则跳过本次循环，重新输入
		if (val1 == val2) {
			cout << "两个值不能相同，请重新输入！" << endl;
			continue;
		}//若输入的两个值相同，则跳过本次循环，重新输入
		loopFlag1 = false;
	}

	//输出公共祖先
	TreeNode* temp1 = nullptr;
	TreeNode* temp2 = nullptr;
	TreeNode* loopTemp1 = nullptr;
	TreeNode* loopTemp2 = nullptr;
	TreeNode* commonAncestor = nullptr;//公共祖先节点
	myBinaryTree.getValNode(myBinaryTree.root, val1, temp1);
	myBinaryTree.getValNode(myBinaryTree.root, val2, temp2);
	loopTemp1 = temp1;
	loopTemp2 = temp2;
	bool loopFlag2 = true;
	while (loopTemp1 != nullptr && loopFlag2) {
		myBinaryTree.getValNode(myBinaryTree.root, val2, loopTemp2);
		while (loopTemp2 != nullptr && loopFlag2) {
			if (loopTemp1->num == loopTemp2->num) {
				commonAncestor = loopTemp1;
				loopFlag2 = false;
			}
			loopTemp2 = loopTemp2->parent;
		}
		loopTemp1 = loopTemp1->parent;
	}
	cout << "最近公共祖先：" << commonAncestor->value << endl;

	//输出所有路径
	myBinaryTree.printPath(commonAncestor);

	//输出最大路径和
	cout << "最大路径和：" << myBinaryTree.maxPathVal(commonAncestor) << endl;
}