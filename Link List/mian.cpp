#include"Linklist.h"
#include"Static_List.h"
#include"Skip_List.h"
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
	Static_List<int> list(10); // ��������Ϊ10�ľ�̬����

	list.ListInsert(1, 10); // �ڵ�һ��λ��ǰ����10
	list.ListInsert(2, 20); // �ڵڶ���λ�ò���20
	list.ListInsert(2, 40); // �ڵڶ���λ�ò���20
	list.ListInsert(3, 30); // �ڵ�����λ�ò���30

	std::cout << "List length: " << list.ListLength() << std::endl;
	std::cout << "List contents: ";
	list.PrintList();

	list.ListDelete(2); // ɾ���ڶ���λ�õĽڵ�

	std::cout << "List length after deletion: " << list.ListLength() << std::endl;
	std::cout << "List contents after deletion: ";
	list.PrintList();

}

void TestSkipList()
{
	SkipList<int, int> L;
	map<int, int> M;

	clock_t s = clock();

	for (int i = 0; i < 1e5; ++i) {
		int key = rand()%INT_MAX-1, value = rand();
		L[key] = value;
	}

	for (int i = 0; i < 1e5; ++i) {
		int key = rand();
		if (i & 1) {
			L.erase(key);
		}
		else {
			int r1 = L.count(key) ? L[key] : 0;
		}
	}

	clock_t e = clock();
	std::cout << "SkipLIst Time elapsed: " << (double)(e - s) / CLOCKS_PER_SEC << std::endl;
	// about 0.2s

	s = clock();

	for (int i = 0; i < 1e5; ++i) {
		int key = rand() % INT_MAX - 1, value = rand();
		M[key] = value;
	}

	for (int i = 0; i < 1e5; ++i) {
		int key = rand();
		if (i & 1) {
			M.erase(key);
		}
		else {
			int r2 = M.count(key) ? M[key] : 0;
		}
	}

    e = clock();
	std::cout << "Map Time elapsed: " << (double)(e - s) / CLOCKS_PER_SEC << std::endl;
	// about 0.2s

	return;
}

int main()
{
	TestLinkList();
	system("Pause");

	TestStaticList();
	system("Pause");

	TestSkipList();
	system("Pause");
}