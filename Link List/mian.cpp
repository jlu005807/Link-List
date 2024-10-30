#include"Linklist.h"
#include"Static_List.h"
using namespace std;

void TestLinkList()
{
	int a[10] = { 6,1,2,7,9,3,4,5,10,8 };

	LNode<int>* one = new LNode<int>(a, 10);
	one->Reverse();
	cout << one << endl;
	cout << one->next->data << " " << one->prior->data << endl;
	
	one->Quick_Sort(one->next, one);
	cout << one << endl;
	LNode<int>* two = one;
	two->ListDelete(5);
	cout << two;
}

void TestStaticList()
{
	Static_List<int> list(10); // 创建容量为10的静态链表

	list.ListInsert(1, 10); // 在第一个位置插入10
	list.ListInsert(2, 20); // 在第二个位置插入20
	list.ListInsert(3, 30); // 在第三个位置插入30

	std::cout << "List length: " << list.ListLength() << std::endl;
	std::cout << "List contents: ";
	list.PrintList();

	list.ListDelete(2); // 删除第二个位置的节点

	std::cout << "List length after deletion: " << list.ListLength() << std::endl;
	std::cout << "List contents after deletion: ";
	list.PrintList();

}

int main()
{
	TestLinkList();
	system("Pause");

	TestStaticList();
	system("Pause");

}