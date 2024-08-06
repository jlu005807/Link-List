#include"Linklist.h"
using namespace std;

int main()
{
	int a[10] = {6,1,2,7,9,3,4,5,10,8};
	
	LNode<int>* one = new LNode<int>(a,10);
	one->Reverse();
	cout << one<<endl;
	cout << one->next->data << " " << one->prior->data << endl;
	system("Pause");
	one->Quick_Sort(one->next,one);
	cout << one << endl;
	LNode<int>* two = one;
	two->ListDelete(5);
	cout << two;
	system("Pause");
}