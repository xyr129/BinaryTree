#include"BinaryTree.h"
#include<cassert>

void Test()
{
	char array[] = { '1', '2', '3', '#', '#', '4', '#', '#', '5', '6', };
	BinaryTree<char> t1(array, 10);
	t1.PreOrder();
	t1.InOrder();
	t1.PostOrder();
	t1.LevelOrder();
	cout<<t1.Size()<<endl;
	
	BinaryTree<char> t2(t1);
	BinaryTree<char> t3;
	t3 = t2;
	t2.PreOrder();
	t3.PostOrder();
	cout << "find:" << t3.Find('3') << endl;
	cout << t3.GetLeafNum() << endl;

	char array1[] = { '1', '2', '3', '#', '#', '4', '#', '5', '6', };
	BinaryTree<char> t4(array1, 9);
	cout << t4.Depth() << endl;
	cout << t4.GetLeafNum() << endl;
}

int main()
{
	Test();
	system("pause");
	return 0;
}