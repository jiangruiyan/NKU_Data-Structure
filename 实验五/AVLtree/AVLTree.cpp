#include<iostream>
#include<fstream>
#include<string>
using namespace std;
class BinaryTreeNode {
public:
    int bf = 0;//平衡因子
    int data;//数据
    BinaryTreeNode* leftChild, * rightChild, * father;
    BinaryTreeNode() { 
        leftChild = rightChild = father = nullptr;
    }
    BinaryTreeNode(const int& e) {
        data = e;
        leftChild = rightChild = father = nullptr;
    }
    BinaryTreeNode(const int& e, BinaryTreeNode* left, BinaryTreeNode* right) {
        data = e;
        leftChild = left;
        rightChild = right;
        father = nullptr;
    }
    BinaryTreeNode(const int& e, BinaryTreeNode* left, BinaryTreeNode* right, BinaryTreeNode* t)
    {
        data = e;
        leftChild = left;
        rightChild = right;
        father = t;
    }
};
class AVLTree {
public:
    BinaryTreeNode* root;
    AVLTree() { 
        root = nullptr;
    }
    AVLTree(int element) { 
        root = new BinaryTreeNode(element); 
    }
    ~AVLTree() {};

    //判断是否为空
    bool IsEmpty();
    //插入操作
    void Insert(const int x);
    //删除操作
    void Delete(const int x);
    //LL型不平衡旋转
    void LL(BinaryTreeNode* x);
    //RR型不平衡旋转
    void RR(BinaryTreeNode* x);
    //LR型不平衡旋转
    void LR(BinaryTreeNode* x);
    //RL型不平衡旋转
    void RL(BinaryTreeNode* x);
    //搜索指定节点
    BinaryTreeNode* Sereach(int a);
    //节点子树信息查询
    void Subtree(BinaryTreeNode* r, int& x, int& y);
    //中序遍历(从小到大）,区间值总和查询
    void Sum(BinaryTreeNode* r, int& x, int a, int b);
};

bool AVLTree::IsEmpty()
{
    return (root) ? false : true;
}

void AVLTree::Insert(const int x) {
    if (root == NULL) {
        root = new BinaryTreeNode(x);
        return;
    }

    BinaryTreeNode* p = root, * pp = nullptr;
    while (p != nullptr) {
        pp = p;
        if (x < p->data) {
            p = p->leftChild;
        }
        else if (x > p->data) {
            p = p->rightChild;
        }
        else {
            cout << "输入重复" << endl;
            return;
        }
    }
    p = new BinaryTreeNode(x);
    if (x < pp->data) {
        pp->leftChild = p;
        p->father = pp;
    }
    else {
        pp->rightChild = p;
        p->father = pp;
    }
    while (pp != nullptr) {
        if (pp->leftChild == p) {
            ++pp->bf;
        }
        else {
            --pp->bf;
        }
        if (pp->bf == 0) {
            break;
        }
        else {
            if (pp->bf == 1 || pp->bf == -1)
            {
                p = pp;
                pp = pp->father;
            }
            else {
                if (pp->bf == 2 || pp->bf == -2)
                {
                    if (pp->bf == 2 && p->bf == 1) {
                        LL(pp);
                    }
                    else {
                        if (pp->bf == -2 && p->bf == -1) {
                            RR(pp);
                        }
                        else {
                            if (pp->bf == 2 && p->bf == -1) {
                                LR(pp);
                            }
                            else {
                                if (pp->bf == -2 && p->bf == 1) {
                                    RL(pp);
                                }
                            }
                        }
                    }
                    break;
                }
            } 
        }
    }
}

void AVLTree::Delete(const int x) {
    BinaryTreeNode* p = root, * pp = nullptr;
    if (p->leftChild == nullptr && p->rightChild == nullptr && p->data == x)
    {
        root = nullptr;
        return;
    }
    while (p != nullptr) {
        if (x == p->data) {
            break;
        }
        pp = p;
        if (x < p->data) {
            p = p->leftChild;
        }
        else {
            if (x > p->data) {
                p = p->rightChild;
            }
        }
    }//找到删除节点
    if (p == nullptr) {
        return;
    }
    if (p->leftChild != nullptr && p->rightChild != nullptr) {//被删除节点左右子树均存在
        pp = p;
        BinaryTreeNode* Right_Left = p->rightChild;
        while (Right_Left->leftChild != nullptr) {
            pp = Right_Left;
            Right_Left = Right_Left->leftChild;
        }//寻找被删除节点的右子树最小值
        swap(p->data, Right_Left->data);
        p = Right_Left;//该节点左子树为空
    }
    BinaryTreeNode* Child = nullptr;
    if (p->leftChild != nullptr) {
        Child = p->leftChild;
    } 
    else {
        if (p->rightChild != nullptr) {
            Child = p->rightChild;
        }
    }
    if (pp == nullptr) {
        root = Child;
        if (Child != nullptr) {
            Child->father = nullptr;
        }
    }//被删节点为根节点
    else{
        if (pp->leftChild == p) {
            --pp->bf;
            pp->leftChild = Child;
        }
        else {
            ++pp->bf;
            pp->rightChild = Child;
        }
        if (Child != nullptr) {
            Child->father = pp;
        }
        int t = 0;
        while (pp != nullptr) {
            if (t != 0) {
                if (pp->leftChild == Child) {
                    --pp->bf;
                }
                else {
                    ++pp->bf;
                }
            }
            t = 1;
            if (pp->bf == -1 || pp->bf == 1){
                break;
            }
            else {
                if (pp->bf == -2 || pp->bf == 2){
                    int m = 0;
                    BinaryTreeNode* w = nullptr;
                    if (pp->bf < 0){
                        m = -1;
                        w = pp->rightChild;
                    }
                    else{
                        m = 1;
                        w = pp->leftChild;
                    }
                    if (w->bf == 0){
                        if (m < 0){
                            RR(pp);
                            pp->bf = -1;
                            w->bf = 1;
                        }
                        else{
                            LL(pp);
                            pp->bf = 1;
                            w->bf = -1;
                        }
                        break;
                    }
                    else {
                        if (w->bf == m) {
                            if (m < 0) {
                                RR(pp);
                                pp = w;
                                Child = pp->leftChild;
                            }
                            else {
                                LL(pp);
                                pp = w;
                                Child = pp->rightChild;
                            }
                        }
                        else {
                            if (m < 0) {
                                BinaryTreeNode* tmp = pp->rightChild->leftChild;
                                RL(pp);
                                pp = tmp;
                                Child = pp->leftChild;
                            }
                            else {
                                BinaryTreeNode* tmp = pp->leftChild->rightChild;
                                LR(pp);
                                pp = tmp;
                                Child = pp->rightChild;
                            }
                        }
                    }
                }
            }
            Child = pp;
            pp = pp->father;
        }//平衡调整
    }
}

void AVLTree::LL(BinaryTreeNode* x) {
    BinaryTreeNode* xl = x->leftChild;
    BinaryTreeNode* xlr = xl->rightChild;
    x->leftChild = xlr;
    if (xlr) {
        xlr->father = x;
    }
    xl->rightChild = x;
    BinaryTreeNode* tmp = x->father;
    x->father = xl;
    xl->father = tmp;
    if (tmp == nullptr) {
        root = xl;
    }
    else {
        if (tmp->leftChild == x) {
            tmp->leftChild = xl;
        }
        else tmp->rightChild = xl;
    }
    x->bf = xl->bf = 0;
}

void AVLTree::RR(BinaryTreeNode* x) {
    BinaryTreeNode* xr = x->rightChild;
    BinaryTreeNode* xrl = xr->leftChild;
    x->rightChild = xrl;
    if (xrl) {
        xrl->father = x;
    }
    xr->leftChild = x;
    BinaryTreeNode* tmp = x->father;
    x->father = xr;
    xr->father = tmp;
    if (tmp == nullptr) {
        root = xr;
    }
    else {
        if (tmp->leftChild == x) {
            tmp->leftChild = xr;
        }
        else {
            tmp->rightChild = xr;
        }
    }
    x->bf = xr->bf = 0;
}

void AVLTree::LR(BinaryTreeNode* x) {
    BinaryTreeNode* xl = x->leftChild;
    BinaryTreeNode* xlr = xl->rightChild;
    int bf = xlr->bf;
    RR(xl);
    LL(x);
    if (bf == 0){
        x->bf = 0;
        xl->bf = 0;
        xlr->bf = 0;
    }
    else {
        if (bf == 1) {
            x->bf = -1;
            xl->bf = 0;
            xlr->bf = 0;
        }
        else {
            if (bf == -1) {
                x->bf = 0;
                xl->bf = 1;
                xlr->bf = 0;
            }
        }
    }
}

void AVLTree::RL(BinaryTreeNode* x) {
    BinaryTreeNode* xr = x->rightChild;
    BinaryTreeNode* xrl = xr->leftChild;
    int bf = xrl->bf;
    LL(xr);
    RR(x);
    if (bf == 0) {
        x->bf = 0;
        xr->bf = 0;
        xrl->bf = 0;
    }
    else {
        if (bf == 1) {
            x->bf = 0;
            xr->bf = -1;
            xrl->bf = 0;
        }
        else {
            if (bf == -1) {
                x->bf = 1;
                xr->bf = 0;
                xrl->bf = 0;
            }
        } 
    }
}

BinaryTreeNode* AVLTree::Sereach(int a) {
    BinaryTreeNode* p = root, * pp = nullptr;
    while (p != nullptr) {
        if (a == p->data) {
            return p;
        }
        pp = p;
        if (a < p->data) {
            p = p->leftChild;
        }
        else {
            if (a > p->data) {
                p = p->rightChild;
            }
        }
    }
    return nullptr;
}//寻找指定节点

void AVLTree::Subtree(BinaryTreeNode* r, int& x, int& y) {
    if (r == nullptr) {
        return;
    }
    Subtree(r->leftChild, x, y);
    x++;
    y += r->data;
    Subtree(r->rightChild, x, y);
}//节点子树信息查询

void AVLTree::Sum(BinaryTreeNode* r, int& x, int a, int b) {
    if (r == nullptr) {
        return;
    }
    Sum(r->leftChild, x, a, b);
    if (r->data >= a && r->data <= b) {
        x += r->data;
    }
    Sum(r->rightChild, x, a, b);
}//中序遍历(从小到大），区间值总和查询

int main() {
    string str;//操作类型
    int a = 0, b = 0, c = 0, d = 0, e = 0;
    ifstream inFile;

    //~~~~~~~~~读数据——在此设置要对哪一个输入样例进行操作@@@@@#####$$$$$%%%%%&&&&&!!!!!
    //可供选择：
    //input1.txt
    //input2.txt
    //input3.txt
    inFile.open("input3.txt");
    //结果会被写入output_student.txt

    ofstream outFile("output_student.txt");
    if (!inFile.is_open()) {
        cerr << "ERROR1" << endl;
        return 0;
    }//检查文件是否存在并读取
    int n = 0;//n代表操作总次数
    if (!(inFile >> n) || n < 1 || n>100000 || (n - int(n)) != 0) {
        cerr << "ERROR" << endl;
        return 0;
    }//确认输入的第一行是否为有效的正整数，且在1-100000范围内。
    AVLTree Tree;
    BinaryTreeNode* Node;
    for (int i = 0; i < n; i++) {
        inFile >> str;
        if (str == "Insert") {
            inFile >> a;
            Tree.Insert(a);
        }
        else {
            if (str == "Delete") {
                inFile >> a;
                Tree.Delete(a);
            }
            else {
                if (str == "Subtree") {
                    inFile >> a;
                    c = d = 0;
                    Node = Tree.Sereach(a);
                    if (Node != NULL) {
                        Tree.Subtree(Node, c, d);
                        outFile << c << " " << d << endl;
                    }
                    else {
                        cout << "NOT FOUND" << endl;
                    }
                }
                else {
                    if (str == "Sum") {
                        e = 0;
                        Node = Tree.root;
                        inFile >> a >> b;
                        Tree.Sum(Node, e, a, b);
                        outFile << e << endl;
                    }
                }
            }
        }
    }
    inFile.close();
    outFile.close();
    return 0;
}