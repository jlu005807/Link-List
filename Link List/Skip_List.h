#pragma once
#include <cassert>
#include <climits>
#include <ctime>
#include <iostream>
#include <map>

//���� (Skip List) ��һ�ֲ������ݽṹ��֧�ֶ����ݵĿ��ٲ��ң������ɾ����
//�����Ƕ���������ĸĽ�,Ĭ��Ϊ ���� ����
//������ �ֲ� �ĸ�����ȣ������ÿһ�㶼��һ����������,�ر�أ���ײ��ǳ�ʼ����������


//��������ڵ�ģ�壬ÿ���ڵ�Ϊһ���ֵ<key,value>,��List��key���ظ�
template<class K,class V>
class SkipListNode
{
public:
	int level;//�ڵ�Ĳ���

	K key;//��

	V value;//ֵ

	SkipListNode** forward;//ָ������ָ������

	//���캯��
	SkipListNode() = default;

	//Ĭ��K,V��Ĭ�Ϲ��캯��������K֧��<�����,��K����intת��������ת��INT_MIN,INT_MAX
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
	static constexpr int MAX_LEVEL = 32;

	//������������
	static constexpr int P = 4;

	//������������ɵ�����
	static constexpr int S = 0xFFFF;

	// ��������ɵĸ��ʷ�ĸ
	static constexpr int PS = S / P;

	// ��Чֵ:��С�����
	static constexpr int INVALID_MAX = INT_MAX;

	static constexpr int INVALID_MIN = INT_MIN;

	// ͷ�ڵ��β�ڵ�
	SkipListNode<K, V>* head;
	SkipListNode<K, V>* tail; 

	//����ĳ��ȣ�������Ԫ������
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

		//�����ڱ��ڵ㣬����Ա߽�����ۣ�������Ϊ����Ϊ��������ͷ�ڱ��ڵ�headΪ��Сֵ��β�ڱ��ڵ�tailΪ���ֵ

		tail = new SkipListNode<K, V>(INVALID_MAX, 0, 0);

		//headÿһ�㶼�У�����ÿ�����ӵ�tail;
		head = new SkipListNode<K, V>(INVALID_MIN, 0, MAX_LEVEL,tail);
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

	//��ѯ�������Ƿ���ڼ�ֵΪ key �Ľڵ㡣�����ڷ���Value
	V& find(const K& key)
	{
		//����ڱ����
		SkipListNode<K, V>* p = head;

		//�������ҵ��ò����һ����ֵС�� key �Ľڵ㣬Ȼ��������һ��
		for (int i = level; i >= 0; i--)
		{
			//�ҵ��ò���ӽ�Key��С��Key�Ľڵ�,tail�ڵ�Ϊ���ֵ
			while (p->forward[i]->key < key)
			{
				p = p->forward[i];//ǰ��
			}
		}

		// ������С�ڣ����Ի���Ҫ��������һ��
		p = p->forward[0];

		//����p->key���ڻ��ߵ���key,��Ҫ���ж�
		//�ҵ��ڵ�
		if (p->key == key)
		{
			return p->value;
		}

		// �ڵ㲻���ڣ����� INVALID
		return tail->value;
	}


	//�����ֵΪ<key,value>��Ԫ��
	//��ִ��һ���ѯ�Ĺ��̣���;��¼�½ڵ���Ҫ������һЩ�ڵ�ĺ��棬�����ִ�в��롣
	//ÿһ�����һ����ֵС�� key �Ľڵ㣬������Ҫ�����޸ĵĽڵ㡣
	void Insert(const K& key, const V& value)
	{
		//���ڼ�¼��Ҫ���µĽڵ�
		SkipListNode<K, V>* updata[MAX_LEVEL + 1];

		SkipListNode<K, V>* p = head;

		//�����ҵ�ÿ��Ҫ���µĽڵ�
		for (int i = level; i >= 0; i--)
		{
			while (p->forward[i]->key < key)
			{
				p = p->forward[i];
			}

			//����ǰ��Ҫ���µĽڵ����update
			updata[i] = p;
		}

		p = p->forward[0];

		//���Ѵ������޸�value
		if (p->key == key)
		{
			p->value = value;
			return;
		}

		//��ȡ�½ڵ��������
		int max_level = randomLevel();

		//������ڵ�ǰ������
		if (max_level > level)
		{
			max_level = ++level;

			//����һ����head
			updata[max_level] = head;
		}

		//�½��ڵ�
		SkipListNode<K, V>* newnode = new SkipListNode<K, V>(key, value, max_level);

		//��0~level������½ڵ�
		for (int i = max_level; i >= 0; i--)
		{
			//���뵽p����
			p = updata[i];

			newnode->forward[i] = p->forward[i];

			p->forward[i] = newnode;
		}

		//����������
		++length;
	}

	//ɾ����ֵΪ key �Ľڵ�,�����Ƿ�ɾ���ɹ�
	//���̺Ͳ������ƣ���������Ϊɾ��
	bool erase(const K& key)
	{
		//���ڼ�¼��Ҫ���µĽڵ�
		SkipListNode<K, V>* updata[MAX_LEVEL + 1];

		SkipListNode<K, V>* p = head;

		//�����ҵ�ÿ��Ҫ���µĽڵ�
		for (int i = level; i >= 0; i--)
		{
			while (p->forward[i]->key < key)
			{
				p = p->forward[i];
			}

			//����ǰ��Ҫ���µĽڵ����update
			updata[i] = p;
		}

		p = p->forward[0];

		//����ڵ㲻����
		if (p->key != key)
		{
			return false;
		}

		//����ײ㿪ʼɾ��
		for (int i = 0; i <= level; i++)
		{
			// ������û�� p ɾ���������
			if (updata[i]->forward[i] != p) {
				break;
			}
			// �Ͽ� p ������
			updata[i]->forward[i] = p->forward[i];
		}

		//����ɾ���ڵ�Ŀռ�
		delete p;

		// ɾ���ڵ���ܵ�������������
		while (level > 0 && head->forward[level] == tail) --level;

		// ������
		--length;

		return true;
	}

	//���������[]ʹ������map
	V& operator[](const K& key)
	{
		V v = find(key);
		
		//û�ҵ��ڵ㣬����һ����Ĭ�Ͻڵ�
		if (v == tail->value)
		{
			Insert(key, 0);
		}

		//���ؽڵ�ֵ
		return find(key);
	}

	//�鿴key�Ƿ����������
	bool count(const K& key)
	{
		return find(key) != tail->value;
	}

};


