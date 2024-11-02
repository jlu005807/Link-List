#pragma once
#include<iostream>
#include<map>

//跳表 (Skip List) 是一种查找数据结构，支持对数据的快速查找，插入和删除。
//跳表是对有序链表的改进,默认为 升序 排序
//引入了 分层 的概念。首先，跳表的每一层都是一个有序链表,特别地，最底层是初始的有序链表


//定义跳表节点模板，每个节点为一组键值<key,value>,在List中key不重复
template<class K,class V>
class SkipListNode
{
public:
	int level;//节点的层数

	K key;//键

	V value;//值

	SkipListNode** forward;//指向各层的指针数组

	//构造函数
	SkipListNode() = default;

	//默认K,V有默认构造函数，并且K支持<运算符
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

	//跳表的长度，即表中元素数量
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

	//查询跳表中是否存在键值为 key 的节点。若存在返回Value
	V& find(const K& key)
	{
		//获得哨兵结点
		SkipListNode<K, V>* p = head;

		//遍历，找到该层最后一个键值小于 key 的节点，然后走向下一层
		for (int i = level; i >= 0; i--)
		{
			//找到该层最接近Key并小于Key的节点
			while (p->forward[i]->key < key)
			{
				p = p->forward[i];//前移
			}
		}

		// 现在是小于，所以还需要再往后走一步
		p = p->forward[0];

		//现在p->key大于或者等于key,需要再判断
		//找到节点
		if (p->key == key)
		{
			return p->key;
		}

		// 节点不存在，返回 INVALID
		return tail->value;
	}


	//插入键值为<key,value>的元素
	//先执行一遍查询的过程，中途记录新节点是要插入哪一些节点的后面，最后再执行插入。
	//每一层最后一个键值小于 key 的节点，就是需要进行修改的节点。
	void Insert(const K& key, const V& value)
	{
		//用于记录需要更新的节点
		SkipListNode<K, V>* updata[MAX_LEVEL + 1];

		SkipListNode<K, V>* p = head;

		//遍历找到每层要更新的节点
		for (int i = level; i >= 0; i--)
		{
			while (p->forward[i]->key < key)
			{
				p = p->forward[i];
			}

			//将当前层要更新的节点放入update
			updata[i] = p;
		}

		p = p->forward[i];

		//若已存在则修改value
		if (p->key == key)
		{
			p->value = value;
		}

		//获取新节点的最大层数
		int max_level = randomLevel();

		//如果大于当前最大层数
		if (max_level > level)
		{
			max_level = ++level;

			//在新一层存放head
			updata[max_level] = head;
		}

		//新建节点
		SkipListNode<K, V>* newnode = new SkipListNode<K, V>(key, value, max_level);

		//在0~level层插入新节点
		for (int i = level; i >= 0; i--)
		{
			//插入到p后面
			p = updata[i];

			newnode->forward[i] = p->forward[i];
			p->forward[i] = newnode;
		}

		//增加跳表长度
		++length;
	}

	//删除键值为 key 的节点,返回是否删除成功
	//过程和插入相似，不过为删除
	bool erase(const K& key)
	{
		//用于记录需要更新的节点
		SkipListNode<K, V>* updata[MAX_LEVEL + 1];

		SkipListNode<K, V>* p = head;

		//遍历找到每层要更新的节点
		for (int i = level; i >= 0; i--)
		{
			while (p->forward[i]->key < key)
			{
				p = p->forward[i];
			}

			//将当前层要更新的节点放入update
			updata[i] = p;
		}

		p = p->forward[i];

		//如果节点不存在
		if (p->key != key)
		{
			return false;
		}

		//从最底层开始删除
		for (int i = 0; i <= level; i++)
		{
			// 如果这层没有 p 删除就完成了
			if (update[i]->forward[i] != p) {
				break;
			}
			// 断开 p 的连接
			update[i]->forward[i] = p->forward[i];
		}

		//回收删除节点的空间
		delete p;

		// 删除节点可能导致最大层数减少
		while (level > 0 && head->forward[level] == tail) --level;

		// 跳表长度
		--length;

		return true;
	}
};


