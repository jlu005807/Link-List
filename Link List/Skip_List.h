#pragma once
#include<iostream>
#include<map>

//���� (Skip List) ��һ�ֲ������ݽṹ��֧�ֶ����ݵĿ��ٲ��ң������ɾ����
//�����Ƕ���������ĸĽ�,Ĭ��Ϊ ���� ����
//������ �ֲ� �ĸ�����ȣ������ÿһ�㶼��һ����������,�ر�أ���ײ��ǳ�ʼ����������


//��������ڵ�ģ�壬ÿ���ڵ�Ϊһ���ֵ<key,valve>,��List��key���ظ�
template<class K,class V>
class SkipListNode
{
public:
	int level;//�ڵ�Ĳ���

	K key;//��

	V valve;//ֵ

	SkipListNode** forward;//ָ����һ���ָ������

	//���캯��
	SkipListNode() = default;

	SkipListNode(K k, V v, int l, SkipListNode* next=nullptr) :key(k), value(v), level(l),forward(nullptr)
	{
		//����ָ������
		forward = new SkipListNode * [l + 1];

		//��ʼ������
		for (int i = 0; i <= l; i++)
		{
			forward[i] = next;
		}
	}

	~SkipListNode()
	{
		//��������ռ������
		if (forward)
		{
			delete[] forward;
		}
	}

};



//��������ģ��
template<class K,class V>
class SkipList
{
public:
	//������
	static const int MAX_LEVEL = 32;

	//������������
	static constexpr int P = 4;

	//������������ɵ�����
	static constexpr int S = 0xFFFF;

	// ��������ɵĸ��ʷ�ĸ
	static constexpr int PS = S / P;

	// ��Чֵ
	static constexpr int INVALID = INT_MAX;

	// ͷ�ڵ��β�ڵ�
	SkipListNode<K, V>* head;
	SkipListNode<K, V>* tail; 

	//����Ԫ������
	int length;

	//��ǰ�������
	int level;

	//���캯��
	SkipList()
	{
		//��ʼ�������������
		srand(time(nullptr));

		//��ʼ��
		level = 0;
		length = 0;
		tail = new SkipList<K, V>(INVALID, 0, 0);
		head = new SkipList<K, V>(INVALID, 0, 0);
	}

	//��������
	~SkipList()
	{
		delete head;
		delete tail;
	}

	//�����������
	int randomLevel()
	{
		//ÿ���ڵ�������һ��
		int lv = 1;

		//ѭ����ֱ����������������Ӳ���
		while ((rand() & S) < PS) ++lv;

		//���ⳬ��������
		return MAX_LEVEL > lv ? lv : MAX_LEVEL;
		
	}

	//�����ֵΪ<key,value>��Ԫ��
	void Insert(const K& key, const V& value)
	{
		//���ڼ�¼��Ҫ���µĽڵ�
		SkipListNode<K, V>* updata[MAX_LEVEL + 1];


		SkipListNode<K, V>* p = head;

	}
};


