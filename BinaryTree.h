#include<iostream>
#include<cassert>
#include<queue>
#include<stack>
using namespace std;

template <class T>
struct BinaryTreeNode
{
	T _data;
	BinaryTreeNode<T>* _left;
	BinaryTreeNode<T>* _right;

	BinaryTreeNode(const char x)
		:_data(x)
		, _left(NULL)
		, _right(NULL)
	{}
};

template<class T>
class BinaryTree
{
public:
	BinaryTree()
		:_root(NULL)
	{}
	BinaryTree(const T* a, size_t size)
	{
		size_t index = 0;
		_root = _CreatTree(a, size, index);
	}
	BinaryTree(const BinaryTree<T>& t)
	{
		_root = _Copy(t._root);
	}
	BinaryTree<T>& operator=(const BinaryTree<T>& t)
	{
		if (this != &t)
		{
			_Destory(_root);
			_root = _Copy(t._root);
		}
		return *this;
	}
	~BinaryTree()
	{
		assert(_root);
		_Destory(_root);
		_root = NULL;
	}
	void PreOrder()
	{
		_PreOrder(_root);
		cout << endl;
	}
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}
	void PostOrder()
	{
		_PostOrder(_root);
		cout << endl;
	}
	void LevelOrder()
	{
		_LevelOrder(_root);
		cout << endl;
	}
	size_t Size()
	{
		return _Size(_root);
	}

	size_t Depth()
	{
		return _Depth(_root);
	}

	size_t GetLeafNum()
	{
		size_t num = 0;
		return _GetLeafNum(_root,num);
	}

	BinaryTreeNode<T>* Find(const T& x)
	{
		return _Find(_root, x);
	}

protected:
	BinaryTreeNode<T>* _CreatTree(const T* a, size_t size, size_t& index)
	{
		BinaryTreeNode<T>* root = NULL;
		if (index < size && a[index] != '#')
		{
			root = new BinaryTreeNode<T>(a[index]);
			root->_left = _CreatTree(a, size, ++index);
			root->_right = _CreatTree(a, size, ++index);
		}
		return root;
	}
	BinaryTreeNode<T>* _Copy(BinaryTreeNode<T>* root)
	{
		if (NULL != root)
		{
			BinaryTreeNode<T>* newRoot = new BinaryTreeNode<T>(root->_data);
			newRoot->_left = _Copy(root->_left);
			newRoot->_right = _Copy(root->_right);
			return newRoot;
		}
		return NULL;
	}
	/*void _Destory(BinaryTreeNode<T>* root)
	{
		if (NULL != root)
		{
			_Destory(root->_left);
			_Destory(root->_right);
			delete root;
		}
	}*/
	void _Destory(BinaryTreeNode<T>* root)
	{
		if (NULL == root)
		{
			return;
		}
		if (NULL == root->_left && NULL == root->_right)
		{
			delete root;
			//root=NULL;
			return;
		}
		_Destory(root->_left);
		_Destory(root->_right);
		delete root;
	}
	/*void _PreOrder(BinaryTreeNode<T>* root)
	{
		if (NULL != root)
		{
			cout << root->_data << " ";
			_PreOrder(root->_left);
			_PreOrder(root->_right);
		}
		return;
	}*/

	//非递归
	void _PreOrder(BinaryTreeNode<T>* root)    
	{
		stack<BinaryTreeNode<T>*> s;
		if (NULL != root)
		{
			s.push(root);
		}
		//不为空，访问，先右后左入栈
		while (!s.empty())
		{
			BinaryTreeNode<T>* top = s.top();
			s.pop();
			cout << top->_data << " ";
			if (NULL != top->_right)
			{
				s.push(top->_right);
			}
			if (NULL != top->_left)
			{
				s.push(top->_left);
			}
		}
	}
	/*void _InOrder(BinaryTreeNode<T>* root)
	{
		if (NULL != root)
		{
			_InOrder(root->_left);
			cout << root->_data << " ";
			_InOrder(root->_right);
		}
		return;
	}*/

	//非递归
	void _InOrder(BinaryTreeNode<T>* root)
	{
		BinaryTreeNode<T>* cur = root;
		stack<BinaryTreeNode<T>*> s;

		while (NULL != cur || !s.empty())
		{
			//左路节点入栈
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}
			//访问节点  并让cur指向右树
			if (!s.empty())
			{
				cur = s.top();   // (此时栈顶元素已是该子树最左节点，直接访问，cur看做根节点指向右子树循环以上操作)
				s.pop();
				cout << cur->_data << " ";
				cur = cur->_right;
			}

		}
	}

	/*void _PostOrder(BinaryTreeNode<T>* root)
	{
		if (NULL != root)
		{
			_PostOrder(root->_left);
			_PostOrder(root->_right);
			cout << root->_data << " ";
		}
		return;
	}*/

	//非递归
	void _PostOrder(BinaryTreeNode<T>* root)
	{
		stack<BinaryTreeNode<T>*> s;
		BinaryTreeNode<T>* cur = root;
		BinaryTreeNode<T>* preVisited = NULL;//指向上一次访问的节点

		while (NULL != cur || !s.empty())
		{
			//左路入栈
			while (NULL != cur)
			{
				s.push(cur);
				cur = cur->_left;
			}
			if (!s.empty())
			{
				BinaryTreeNode<T>* top = s.top();
				if (NULL == top->_right || top->_right == preVisited)//该节点可被访问的条件:right为空或已访问过
				{
					cout << top->_data << " ";
					preVisited = top;
					s.pop();
				}
				else
				{
					cur = top->_right;
				}
			}
		}
		
	}
	void _LevelOrder(BinaryTreeNode<T>* root)      //栈和队列
	{
		queue<BinaryTreeNode<T>*> q;
		if (_root)
		{
			q.push(_root);
		}
		
		while (!q.empty())
		{
			BinaryTreeNode<T>* node = q.front();
			q.pop();
			cout << node->_data << " ";
			if (node->_left)
			{
				q.push(node->_left);
			}
			if (node->_right)
			{
				q.push(node->_right);
			}
		}
		cout << endl;
		
	} 
	//计算第k层节点个数
	size_t _GetNumKthLevel(BinaryTreeNode<T>* root, int k)
	{
		//树为空或k<1
		if (NULL == root || k < 1)
		{
			return 0;
		}
		//数不为空且k==1
		if (1 == k)
		{
			return 1;
		}

		size_t leftNum = _GetNumKthLevel(root->_left, k - 1);//左子树的k-1层
		size_t rightNum = _GetNumKthLevel(root->_right, k - 1);//右子树的k-1层
		return leftNum + rightNum;
	}

	//计算叶子节点个数
	size_t _GetLeafNum(BinaryTreeNode<T>* root,size_t& num)
	{
		if (NULL == root)
		{
			return 0;
		}
		if (NULL == root->_left && NULL == root->_right)
		{
			++num;
			return num;
		}
		_GetLeafNum(root->_left,num);
		_GetLeafNum(root->_right,num);
		return num;
	}

	BinaryTreeNode<T>* _Find(BinaryTreeNode<T>* root,const char& x)
	{
		if (NULL == root)
		{
			return NULL;
		}
		if (x == root->_data)
		{
			return root;
		}
		else
		{
			if (NULL == _Find(root->_left, x))  
			{
				_Find(root->_right, x);
			}
		}
	}
	size_t _Size(BinaryTreeNode<T>* root)
	{
		if (NULL == root)
		{
			return 0;
		}
		return 1 + _Size(root->_left) + _Size(root->_right);
	}

	//线程安全
	size_t _size(BinaryTreeNode<T>* root)   //传参
	{
		static size_t size = 0;
		if (NULL == root)
		{
			return 0;
		}
		else
		{
			++size;
		}
		_size(root->_left);
		_size(root->_right);
		return size;
	}
	size_t _Depth(BinaryTreeNode<T>* root)
	{
		size_t depth = 0;
		if (NULL != root)
		{
			size_t leftDepth = _Depth(root->_left);
			size_t rightDepth = _Depth(root->_right);
			if (leftDepth > rightDepth)
			{
				depth = leftDepth+1;
			}
			else
			{
				depth = rightDepth+1;
			}
		}
		return depth;
	}
private:
	BinaryTreeNode<T>* _root;
};


template <class T>
struct BinaryTreeNode_P
{
	T _data;
	BinaryTreeNode_P<T>* _left;
	BinaryTreeNode_P<T>* _right;
	BinaryTreeNode_P<T>* _parent;

	BinaryTreeNode_P(const char x)
		:_data(x)
		, _left(NULL)
		, _right(NULL)
		, _parent(NULL)
	{}
};

template<class T>
class BinaryTree_P
{
public:
	BinaryTree_P()
		:_root(NULL)
	{}
	BinaryTree_P(const T* a, size_t size)
	{
		size_t index = 0;
		_root = _CreatTree_P(a, size, index);
	}
	BinaryTree_P(const BinaryTree<T>& t)
	{
		_root = _Copy(t._root);
	}
	BinaryTree_P<T>& operator=(const BinaryTree_P<T>& t)
	{
		if (this != &t)
		{
			_Destory(_root);
			_root = _Copy(t._root);
		}
		return *this;
	}
	~BinaryTree_P()
	{
		assert(_root);
		_Destory(_root);
	}
protected:
	BinaryTreeNode<T>* _CreatTree_P(const T* a, size_t size, size_t& index)
	{
		BinaryTreeNode<T>* root = NULL;
		if (index < size && a[index] != '#')
		{
			root = new BinaryTreeNode<T>(a[index]);
			root->_left = _CreatTree_P(a, size, ++index);
			if (NULL != root->_left)
			{
				root->_left->_parent = _root;
			}
			root->_right = _CreatTree_P(a, size, ++index);
			if (NULL != root->_right)
			{
				root->_right->_parent = _root;
			}
		}
		return root;
	}
private:
	BinaryTreeNode_P<T>* _root;
};