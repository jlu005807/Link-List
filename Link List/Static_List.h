#pragma once

//静态链表是用数组描述的链表。注意：和前面的顺序存储不一样，这里是用数组模拟链表。
//没有指针这个东西时，衍生了静态链表这个产物去模拟链表
// 总的来说，静态链表就是为了给没有指针的高级语言实现单链表能力的一种方法。

//在静态链表中有个约定俗称的规定：

//1.第一个和最后一个结点作为特殊元素处理，不存数据。

//2.我们通常把未被使用的数组元素称之为备用链表，而数组第一个元素（即下标为0的元素）的Cur就存放备用链表的第一个结点的下标。

//3. 数组最后一个元素的Cur则存放第一个有数值的元素（首元结点）的下标，相当于单链表中头结点的作用。
//当整个链表为空的时候，数组中最后一个元素的Cur为0。

//4.如果一个结点下一位置的数据为空但这个结点数据不为空，则这个结点的Cur用0来表示。
//因为这个这是最后一个有数据的结点了，没有下一个有数据的结点了，所以Cur为0相当于指针中的NULL。


//节点
template<class T=int>
class Node
{
public:
	//存放数据元素。
	T data;

	//相当于单链表中的Next指针，存放该元素的后继在数组中的下标
	int cur;
};



template<class T=int>
class Static_List
{
public:

	//用此数组模拟链表
	Node<T>* Datas;

	//容量
	int capacity;

	Static_List(int capacity) :capacity(capacity)
	{
		//申请空间
		Datas = new Node<T>[capacity];

		InitList();
	}

	// 拷贝构造函数
	Static_List(const Static_List& other) : capacity(other.capacity) {
		Datas = new Node<T>[capacity];
		for (int i = 0; i < capacity; i++) {
			Datas[i] = other.Datas[i];
		}
	}

	// 赋值运算符重载
	Static_List& operator=(const Static_List& other) {
		if (this != &other) {
			delete[] Datas;
			capacity = other.capacity;
			Datas = new Node<T>[capacity];
			for (int i = 0; i < capacity; i++) {
				Datas[i] = other.Datas[i];
			}
		}
		return *this;
	}

	// 析构函数
	~Static_List() {
		delete[] Datas;
	}

	//静态链表初始化
	//1.将Cur游标存储下一个结点的下标
	//最后一个结点的Cur游标存储第一个有数值的元素的下标。
	void InitList()
	{
		//用循环将第i个结点的Cur游标赋值为i+1。
		for (int i = 0; i < capacity; i++)
		{
			Datas[i].cur = i + 1;
		}

		//最后一个空闲的结点Cur置为0，相当于指针置为NULL
		Datas[capacity - 2].cur = 0;

		//最后将最后一个结点的Cur游标初始化为0。先开始是空表所以为0
		Datas[capacity - 1].cur = 0;
	}

	//申请空间，即第一个结点中Cur所定位的第一个备用链表的下标
	int Malloc_StaticList()
	{
		//第一个节点的cur
		int Pos_cur = Datas[0].cur;

		//链表已满返回-1
		if (Pos_cur == 0)
		{
			return 0;
		}

		//更新第一个备用链表的下标
		Datas[0].cur = Datas[Pos_cur].cur;

		return Pos_cur;	
	}

	//返回链表长度
	int ListLength()
	{
		int count = 0;

		//最后一个节点类似哨兵节点指向第一个数据
		int i = Datas[capacity - 1].cur;

		while (i != 0)
		{
			count++;
			i = Datas[i].cur;
		}

		return count;
	}

	//插入一个结点，这个结点插在Node这个结点之前
	bool ListInsert(int Node, int data)
	{
		int L = ListLength();
		//Node不合法
		if (Node<1 || Node>L + 1)
		{
			return false;
		}

		//申请空间
		int New_cur = Malloc_StaticList();

		//链表已满
		if (New_cur == 0)
		{
			return false;
		}

		//存放数据
		Datas[New_cur].data = data;

		//定位首元素
		int cur = capacity - 1;

		//找到Node前面一个节点
		for (int i = 0; i < Node; i++)
		{
			cur = Datas[cur].cur;//类似链表的p=p->next
		}

		//新的结点指针通过Cur指向Node
		Datas[New_cur].cur = Datas[cur].cur;

		Datas[cur].cur = New_cur;

		return true;
	}

	//释放空间，在下标为number的结点，回收成为备用链表的一部分
	void Free_StaticList(int number)
	{
		//numbe不合法
		if (number<1 || number>capacity - 2)
		{
			return;
		}

		//不考虑number节点是否在备用链表里
		Datas[number].cur = Datas[0].cur;

		//将第一个节点指向number节点
		Datas[0].cur = number;
	}

	//删除第k个这个下标位置的结点
	bool ListDelete(int k)
	{
		//k不合法
		if (k<1 || k>ListLength()) 
		{                            
			return false;
		}

		//找到第k-1个节点
		int cur = capacity - 1;//第零个节点类似哨兵节点

		for (int i = 1; i < k; i++)
		{
			cur = Datas[cur].cur;
		}

		int k_cur = Datas[cur].cur;

		//k前面节点Cur直接指向k后面的结点
		Datas[cur].cur = Datas[k_cur].cur;

		//释放空间
		Free_StaticList(k_cur);

	}

	//打印链表
	void PrintList()
	{
		int i = Datas[capacity-1].cur;//从第一个数据结点开始搜索
		while (i != 0)//将所有的数据结点打印
		{
			printf("%c-->", Datas[i].data);
			i = Datas[i].cur; // p = p->next;
		}
		printf("Nul.\n");
	}
};