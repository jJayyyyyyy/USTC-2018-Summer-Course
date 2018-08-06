/*
如果发现了bug或者有更好的解法，欢迎发出issue和PR
:p

BST的插入和查找都不难，可以参考这里
https://github.com/jJayyyyyyy/cs/tree/master/data%20structure/tree/BST


对于结点的删除，可以参考这篇博客
https://www.cnblogs.com/Renyi-Fan/p/8253136.html

TODO: 重构代码，重新命名变量和函数
*/

#include <iostream>
#define MAXSIZE 16
using namespace std;

struct Node{
	int val;
	Node *lchild, *rchild, *parent;
	Node(int _v){
		val = _v;
		lchild = rchild = parent = NULL;
	}
};

void insertBST(Node * & root, int val){
	if( root == NULL ){
		root = new Node(val);
		return;
	}
	if( val < root->val ){
		insertBST(root->lchild, val);
		root->lchild->parent = root;
	}else{
		insertBST(root->rchild, val);
		root->rchild->parent = root;
	}
}


Node * findNode(Node * & root, int val){
	if( root != NULL ){
		if( val == root->val ){
			return root;
		}else if( val < root->val ){
			return findNode(root->lchild, val);
		}else{
			return findNode(root->rchild, val);
		}
	}

	return NULL;
}

void deleteLeaf(Node * & node){
	if( node->parent->lchild == node ){
		node->parent->lchild = NULL;
	}else{
		node->parent->rchild = NULL;
	}
	delete node;
}

void deleteWithLChild(Node * & node){
	if( node->parent->lchild == node ){
		node->parent->lchild = node->lchild;
	}else{
		node->parent->rchild = node->lchild;
	}
	delete node;
}

void deleteWithRChild(Node * & node){
	if( node->parent->lchild == node ){
		node->parent->lchild = node->rchild;
	}else{
		node->parent->rchild = node->rchild;
	}
	delete node;
}

Node * findLargest(Node * node){
	if( node != NULL ){
		if( node->rchild == NULL ){
			return node;
		}else{
			return findLargest(node->rchild);
		}
	}
}

// replace node with the largest node of its lchild 
Node * deleteWithBothChild(Node * & node){
	Node * leftLargest = findLargest(node->lchild);
	swap(node->val, leftLargest->val);
	return leftLargest;
	
}

/*
删除二叉树查找树的结点，总共有三种情况

1.被删除的节点是叶子节点，这时候只要把这个节点删除，再把指向这个节点的父节点指针置为空就行

2.被删除的节点有左子树，或者有右子树，而且只有其中一个，那么只要把当前删除节点的父节点指向被删除节点的左子树或者右子树就行。

3.被删除的节点既有左子树而且又有右子树，这时候需要把左子树的最右边的节点或者右子树最左边的节点提到被删除节点的位置，为什么要这样呢，根据二叉查找树的性质，父节点的指针一定比所有左子树的节点值大而且比右子树的节点的值小，为了删除父节点不破坏二叉查找树的平衡性，应当把左子树最大的节点或者右子树最小的节点放在父节点的位置，这样的话才能维护二叉查找树的平衡性。（我是找的右子树的最小节点）
*/
int deleteNode(Node * & root, int val){
	Node * node = findNode(root, val);
	if( node == NULL ){
		return -1;
	}

	// 如果被删结点是叶子
	if( node->lchild == NULL && node->rchild == NULL ){
		deleteLeaf(node);
	}
	// 如果被删结点只有一个孩子
	else if( node->lchild != NULL && node->rchild == NULL ){
		deleteWithLChild(node);
	}else if( node->lchild == NULL && node->rchild != NULL ){
		deleteWithRChild(node);
	}else{
		Node * leftLargest = deleteWithBothChild(node);
		deleteNode(leftLargest, leftLargest->val);
	}
}

void testFindNode(Node * root){
	while( true ){
		int val = 0;
		cin>>val;
		if( val == 0 ){
			break;
		}else{
			Node * node = findNode(root, val);
			if( node == NULL ){
				cout<<"Not Found\n";
			}else{
				cout<<node->val<<'\n';
			}
		}
	}
}

void testDeleteNode(Node * root){
	int val = 0;
	cin>>val;
	deleteNode(root, val);
}

int main(){
	int n;
	cin>>n;

	Node * root = NULL;
	for( int i = 0; i < n; i++ ){
		int val;
		cin>>val;
		insertBST(root, val);
	}

	testFindNode(root);
	testDeleteNode(root);

	return 0;
}

/*
输入说明

总的结点数 n
接下来的1行中，输入每个结点的值

8
33 88 22 55 90 11 66 99
*/