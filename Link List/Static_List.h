#pragma once

//��̬����������������������ע�⣺��ǰ���˳��洢��һ����������������ģ������
//û��ָ���������ʱ�������˾�̬�����������ȥģ������
// �ܵ���˵����̬�������Ϊ�˸�û��ָ��ĸ߼�����ʵ�ֵ�����������һ�ַ�����

//�ھ�̬�������и�Լ���׳ƵĹ涨��

//1.��һ�������һ�������Ϊ����Ԫ�ش����������ݡ�

//2.����ͨ����δ��ʹ�õ�����Ԫ�س�֮Ϊ���������������һ��Ԫ�أ����±�Ϊ0��Ԫ�أ���Cur�ʹ�ű�������ĵ�һ�������±ꡣ

//3. �������һ��Ԫ�ص�Cur���ŵ�һ������ֵ��Ԫ�أ���Ԫ��㣩���±꣬�൱�ڵ�������ͷ�������á�
//����������Ϊ�յ�ʱ�����������һ��Ԫ�ص�CurΪ0��

//4.���һ�������һλ�õ�����Ϊ�յ����������ݲ�Ϊ�գ����������Cur��0����ʾ��
//��Ϊ����������һ�������ݵĽ���ˣ�û����һ�������ݵĽ���ˣ�����CurΪ0�൱��ָ���е�NULL��


//�ڵ�
template<class T=int>
class Node
{
public:
	//�������Ԫ�ء�
	T data;

	//�൱�ڵ������е�Nextָ�룬��Ÿ�Ԫ�صĺ���������е��±�
	int cur;
};



template<class T=int>
class Static_List
{
public:

	//�ô�����ģ������
	Node<T>* Datas;

	//����
	int capacity;

	Static_List(int capacity) :capacity(capacity)
	{
		//����ռ�
		Datas = new Node<T>[capacity];

		InitList();
	}

	// �������캯��
	Static_List(const Static_List& other) : capacity(other.capacity) {
		Datas = new Node<T>[capacity];
		for (int i = 0; i < capacity; i++) {
			Datas[i] = other.Datas[i];
		}
	}

	// ��ֵ���������
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

	// ��������
	~Static_List() {
		delete[] Datas;
	}

	//��̬�����ʼ��
	//1.��Cur�α�洢��һ�������±�
	//���һ������Cur�α�洢��һ������ֵ��Ԫ�ص��±ꡣ
	void InitList()
	{
		//��ѭ������i������Cur�α긳ֵΪi+1��
		for (int i = 0; i < capacity; i++)
		{
			Datas[i].cur = i + 1;
		}

		//���һ�����еĽ��Cur��Ϊ0���൱��ָ����ΪNULL
		Datas[capacity - 2].cur = 0;

		//������һ������Cur�α��ʼ��Ϊ0���ȿ�ʼ�ǿձ�����Ϊ0
		Datas[capacity - 1].cur = 0;
	}

	//����ռ䣬����һ�������Cur����λ�ĵ�һ������������±�
	int Malloc_StaticList()
	{
		//��һ���ڵ��cur
		int Pos_cur = Datas[0].cur;

		//������������-1
		if (Pos_cur == 0)
		{
			return 0;
		}

		//���µ�һ������������±�
		Datas[0].cur = Datas[Pos_cur].cur;

		return Pos_cur;	
	}

	//����������
	int ListLength()
	{
		int count = 0;

		//���һ���ڵ������ڱ��ڵ�ָ���һ������
		int i = Datas[capacity - 1].cur;

		while (i != 0)
		{
			count++;
			i = Datas[i].cur;
		}

		return count;
	}

	//����һ����㣬���������Node������֮ǰ
	bool ListInsert(int Node, int data)
	{
		int L = ListLength();
		//Node���Ϸ�
		if (Node<1 || Node>L + 1)
		{
			return false;
		}

		//����ռ�
		int New_cur = Malloc_StaticList();

		//��������
		if (New_cur == 0)
		{
			return false;
		}

		//�������
		Datas[New_cur].data = data;

		//��λ��Ԫ��
		int cur = capacity - 1;

		//�ҵ�Nodeǰ��һ���ڵ�
		for (int i = 0; i < Node; i++)
		{
			cur = Datas[cur].cur;//���������p=p->next
		}

		//�µĽ��ָ��ͨ��Curָ��Node
		Datas[New_cur].cur = Datas[cur].cur;

		Datas[cur].cur = New_cur;

		return true;
	}

	//�ͷſռ䣬���±�Ϊnumber�Ľ�㣬���ճ�Ϊ���������һ����
	void Free_StaticList(int number)
	{
		//numbe���Ϸ�
		if (number<1 || number>capacity - 2)
		{
			return;
		}

		//������number�ڵ��Ƿ��ڱ���������
		Datas[number].cur = Datas[0].cur;

		//����һ���ڵ�ָ��number�ڵ�
		Datas[0].cur = number;
	}

	//ɾ����k������±�λ�õĽ��
	bool ListDelete(int k)
	{
		//k���Ϸ�
		if (k<1 || k>ListLength()) 
		{                            
			return false;
		}

		//�ҵ���k-1���ڵ�
		int cur = capacity - 1;//������ڵ������ڱ��ڵ�

		for (int i = 1; i < k; i++)
		{
			cur = Datas[cur].cur;
		}

		int k_cur = Datas[cur].cur;

		//kǰ��ڵ�Curֱ��ָ��k����Ľ��
		Datas[cur].cur = Datas[k_cur].cur;

		//�ͷſռ�
		Free_StaticList(k_cur);

	}

	//��ӡ����
	void PrintList()
	{
		int i = Datas[capacity-1].cur;//�ӵ�һ�����ݽ�㿪ʼ����
		while (i != 0)//�����е����ݽ���ӡ
		{
			printf("%c-->", Datas[i].data);
			i = Datas[i].cur; // p = p->next;
		}
		printf("Nul.\n");
	}
};