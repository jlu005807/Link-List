#pragma once
#include<iostream>
#include<map>

//跳表 (Skip List) 是一种查找数据结构，支持对数据的快速查找，插入和删除。
//跳表是对有序链表的改进,默认为 升序 排序
//引入了 分层 的概念。首先，跳表的每一层都是一个有序链表,特别地，最底层是初始的有序链表


//定义跳表节点模板，每个节点为一组键值<key,valve>,在List中key不重复
template<class K,class V>
class SkipListNode
{
public:
	int level;//节点的层数

	K key;//键

	V valve;//值

	SkipListNode** forward;//指向下一层的指针数组

	//构造函数
	SkipListNode() = default;

	SkipListNode(K k, V v, int l, SkipListNode* next=nullptr) :key(k), value(v), level(l),forward(nullptr)
	{
		//构建指针数组
		forward = new SkipListNode * [l + 1];

		//初始化数组
		for (int i = 0; i <= l; i++)
		{
			forward[i] = next;
		}
	}

	~SkipListNode()
	{
		//存在申请空间的数组
		if (forward)
		{
			delete[] forward;
		}
	}

};



//定义跳表模板
template<class K,class V>
class SkipList
{
public:
	//最大层数
	static const int MAX_LEVEL = 32;

	//层数增长概率
	static constexpr int P = 4;

	//用于随机数生成的掩码
	static constexpr int S = 0xFFFF;

	// 随机数生成的概率分母
	static constexpr int PS = S / P;

	// 无效值
	static constexpr int INVALID = INT_MAX;

	// 头节点和尾节点
	SkipListNode<K, V>* head;
	SkipListNode<K, V>* tail; 

	//表中元素数量
	int length;

	//当前跳表层数
	int level;

	//构造函数
	SkipList()
	{
		//初始化随机数的种子
		srand(time(nullptr));

		//初始化
		level = 0;
		length = 0;
		tail = new SkipList<K, V>(INVALID, 0, 0);
		head = new SkipList<K, V>(INVALID, 0, 0);
	}

	//析构函数
	~SkipList()
	{
		delete head;
		delete tail;
	}

	//生成随机层数
	int randomLevel()
	{
		//每个节点至少有一层
		int lv = 1;

		//循环，直到随机数不足以增加层数
		while ((rand() & S) < PS) ++lv;

		//避免超过最大层数
		return MAX_LEVEL > lv ? lv : MAX_LEVEL;
		
	}

	//插入键值为<key,value>的元素
	void Insert(const K& key, const V& value)
	{
		//用于记录需要更新的节点
		SkipListNode<K, V>* updata[MAX_LEVEL + 1];


		SkipListNode<K, V>* p = head;

	}
};


