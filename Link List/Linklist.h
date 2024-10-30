#pragma once
#include<iostream>
template<class T>
class LNode
{
public:
	T data;
	LNode* prior;
	LNode* next;

public:
	// 默认构造函数，不初始化为哨兵节点
	LNode():prior(nullptr),next(nullptr)
	{
		
	}

	explicit LNode(const T& _data) :data(_data), prior(nullptr), next(nullptr)
	{

	}


	// 构造函数，从数组初始化双向链表 
	LNode(T all[], int num):prior(nullptr), next(nullptr)
	{
		initFromArray(all, num);
	}


	// 构造函数，从另一个链表复制
	LNode(const LNode<T>* pHead)
	{
		initFromHead(pHead);
	}

	bool ListEmpty()const
	{
		if (this->next == this)return true;
		else return false;
	}

	int ListLength()const
	{
		int length = 0;
		LNode<T>* p = this->next;
		while (p != this)
		{
			length++;
			p = p->next;
		}
		return length;
	}

	T GetElem(int i)
	{
		LNode<T>* p = this->Locate(i);
		if (p)
			return p->data;
		else return -1;
	}


	int Locate_subscript(const LNode<T>* obj)const
	{
		if (this->ListEmpty())
		{
			std::cout << "List is Empty" << std::endl;
			return NULL;
		}
		else
		{
			int locate = 0;
			for (const LNode<T>* p = this->next; p != this; p = p->next)
			{
				locate++;
				if (p == obj)return locate;
			}
			return -1;
		}
	}


	LNode<T>* Locate_ptr(int i)//ptr
	{
		if (this->ListEmpty())
		{
			std::cout << "List is Empty" << std::endl;
			return NULL;
		}
		else if (i <= 0 || i > this->ListLength())
		{
			std::cout << "Error" << std::endl;
			exit(1);
		}
		else
		{
			LNode<T>* p = this;
			for (int k = 0; k < i; k++)
			{
				p = p->next;
			}
			return p;
		}
	}

	int Locate_subscript(const T& e)const//subscript
	{
		if (this->ListEmpty())
		{
			std::cout << "List is Empty" << std::endl;
			return -1;
		}

		int locate = 0;
		for (const LNode<T>* p = this->next; p != this; p = p->next)
		{
			locate++;
			if (p->data == e)return locate;
		}
		return -1;	
	}


	LNode<T>& operator=(const LNode<T>* pHead)
	{
		if (this == pHead)
		{
			return *this;
		}
		else
		{
			if (this->next = this)
			{
				this->clearList();
			}
			//哨兵节点初始化
			this->next = this;
			this->prior = this;

			LNode* tail = this;
			LNode* other_tail = pHead->next;

			while (other_tail != pHead)
			{
				LNode* p = new LNode<T>(other_tail->data);
				if (!p)
				{
					perror("Creat node fial");
					exit(1);
				}
				tail->next = p;
				p->next = tail;
				this->prior = p;
				p->prior = tail;
				tail = p;
				other_tail = other_tail->next;
			}
			return *this;
		}
	}

	T& operator[](int i)//类似数组的下标
	{
		/*system("Pause");*/
		LNode<T>* obj = Locate_ptr(i + 1);
		return obj->data;
	}

	const T& operator[](int i)const//类似数组的下标
	{
		LNode<T>* obj = Locate_ptr(i + 1);
		return obj->data;
	}




	void ListInsert_prior(LNode<T>* p, const T& data)
	{

		if (!p)
		{
			std::cout << "Error" << std::endl;
			return;
		}
		p = p->prior;

		LNode<T>* new_node = new LNode<T>(data);

		if (!new_node)
		{
			perror("Creat node fial");
			exit(1);
		}

		new_node->next = p->next;
		p->next->prior = new_node;
		p->next = new_node;
		new_node->prior = p;

		return;
	}

	void ListInsert_prior(LNode<T>* p, LNode<T>* new_node)
	{

		if (!p)
		{
			std::cout << "Error" << std::endl;
			return;
		}
		p = p->prior;

		if (!new_node)
		{
			perror("Creat node fial");
			exit(1);
		}

		new_node->next = p->next;
		p->next->prior = new_node;
		p->next = new_node;
		new_node->prior = p;

		return;
	}

	void ListInsert_prior(int i,const T& data)
	{
		
		LNode<T>* p = Locate_ptr(i);
		this->ListInsert_prior(p, data);
		return;
	}

	void ListInsert_prior(int i, LNode<T>* new_node)
	{

		LNode<T>* p = Locate_ptr(i);
		this->ListInsert_prior(p, new_node);

		return;
	}

	void ListInsert_next(LNode<T>* p, LNode<T>* new_node)
	{

		if (!p)
		{
			std::cout << "Error" << std::endl;
			return;
		}


		if (!new_node)
		{
			perror("Creat node fial");
			exit(1);
		}

		new_node->next = p->next;
		p->next->prior = new_node;
		p->next = new_node;
		new_node->prior = p;

		return;

	}

	void ListInsert_next(LNode<T>*p, const T& data)
	{


		if (!p)
		{
			std::cout << "Error" << std::endl;
			return;
		}
		LNode<T>* new_node = new LNode<T>(data);

		if (!new_node)
		{
			perror("Creat node fial");
			exit(1);
		}

		new_node->next = p->next;
		p->next->prior = new_node;
		p->next = new_node;
		new_node->prior = p;

		return;

	}

	void ListInsert_next(int i, LNode<T>* new_node)
	{
		LNode<T>* p = Locate_ptr(i);

		this->ListInsert_next(p, new_node);

		return;

	}

	void ListInsert_next(int i, const T& data)
	{
		LNode<T>* p = Locate_ptr(i);

		this->ListInsert_next(p, data);

		return;
		
	}

	void ListInsert_Head(const T& data)
	{
		this->ListInsert_prior(1, data);
		return;
	}

	void ListInsert_Head(LNode<T>* data)
	{
		this->ListInsert_prior(1, data);
		return;
	}

	void ListInsert_Tail(const T& data)
	{
		int len = this->ListLength();
		this->ListInsert_next(len , data);
		return;
	}

	void ListInsert_Tail(LNode<T>* data)
	{
		int len = this->ListLength();
		this->ListInsert_next(len, data);
		return;
	}

	void ListDelete(int i)
	{
		LNode<T>* p = Locate_ptr(i);
		if (!p)
		{
			std::cout << "Error" << std::endl;
			return;
		}

		LNode<T>* prev = p->prior;
		LNode<T>* next = p->next;
		prev->next = next;
		next->prior = prev;

		//变为空表状态，防止delete时析构导致原链表断裂；
		p->next = p;
		p->prior = p;

		delete p;

		return;
	}

	//利用头插法逆转链表
	void Reverse_HeadInsert()
	{
		LNode<T>* cur = this->next;

		//空链表
		if (cur == this)return;

		//第二个结点最后为尾结点
		LNode<T>* tail = cur;

		//断开this和cur
		this->next = nullptr;
		cur->prior = nullptr;

		while (cur->next != this)
		{
			LNode<T>* q = cur;

			//cur后移
			cur = cur->next;

			//插入q到this后面,cur前面
			this->next = q;
			q->prior = this;

			q->next = cur;
			cur->prior = q;
		}

		//处理首尾相连
		tail->next = this;
		this->prior = tail;

		return;
	}


	void Reverse()
	{
		LNode<T>* cur = this->next;
		if (cur == this)return;//防止prev最后为空

		LNode<T>* prev = nullptr;
		LNode<T>* nextnode = nullptr;
		
		while (cur != this)
		{

			/*system("Pause");
			std::cout << cur->data << " "  << std::endl;*/
			//测试
			prev = cur->prior;
			nextnode = cur->next;

			cur->next = prev;
			prev->prior = cur;

			cur = nextnode;
		}
		
		LNode<T>* new_head = prev->prior;

		this->next = new_head;

		new_head->prior = this;

	}

	LNode<T>* Quick_Froandback_partsort(LNode<T>* left, LNode<T>* right)//左闭右开,右边为边界值即开始为this.
	{
		auto swap = [](LNode<T>* x,LNode<T>* y)->void
		{
			T temp = x->data;
			x->data = y->data;
			y->data = temp;
			return;
		};

		LNode<T>* prev = left;
		LNode<T>* cur = left->next;
		LNode<T>* keyptr = left;//基准

		while (cur!= right)
		{
			while (cur->data <= keyptr->data)
			{
				prev = prev->next;
				if (prev == cur)break;
				else {
					swap(cur, prev);
				}
			}
			cur = cur->next;
		}

		swap(prev, keyptr);

		keyptr = prev;

		return keyptr;

	}

	void Quick_Sort(LNode<T>* left, LNode<T>* right)
	{
		if (left == right)return;//退出递归
		/*std::cout << left->data << " " << right->prior->data << std::endl;
		system("Pause");*/
		LNode<T>* keyptr = this->Quick_Froandback_partsort(left, right);
		/*std::cout << keyptr->data << " " << left->data << " " << right->prior->data << std::endl;
		std::cout << this << std::endl;
		system("Pause");*/

		Quick_Sort(left, keyptr
		);

		Quick_Sort(keyptr->next, right);


	}


	void Selection_Sort()
	{
		LNode<T>* p = this;

		while (p->next != this)
		{
			LNode<T>* r = p->next;

			LNode<T>* min = r;//找最小值

			while (r != this)
			{
				if (r->data < min->data)min = r;
				r = r->next;
			}

			min->prior->next = min->next;
			min->next->prior = min->prior;

			this->ListInsert_next(p, min);
			
			p = p->next;
		}

		return;
	}


	void Insertion_Sort()
	{
		LNode<T>* p = this->next;

		while (p != this)
		{
			LNode<T>* r = this->next;
			while (r != p && r->data < p->data)r = r->next;


			if(r!=p)
			{
				LNode<T>* now_node = p;

				now_node->prior->next = now_node->next;
				now_node->next->prior = now_node->prior;

				this->ListInsert_prior(r, p);
			}

			p = p->next;
		}



	}


	~LNode()
	{
		clearList();
	}


private:

	    void clearList() {
		    LNode<T>* current = this->next;
		    while (current != this) {
			    LNode<T>* now_node = current;
			    delete now_node;
			    current =current->next;
		    }
	    }

		void initFromArray(T all[], int num) {
			if (num <= 0 || !all) return;

			LNode<T>* first = new LNode<T>(all[0]);
			LNode<T>* tail = first;
			for (int i = 1; i < num; ++i) {
				LNode<T>* p = new LNode<T>(all[i]);
				tail->next = p;
				p->prior = tail;
				tail = p;
			}
			tail->next = this;
			this->prior = tail;
			this->next = first;
			first->prior = this;
		}

		void initFromHead(const LNode<T>* pHead) {
			if (!pHead || !pHead->next) return;

			LNode<T>* tail = this;
			for (const LNode<T>* p = pHead->next; p != pHead; p = p->next) {
				LNode<T>* new_node = new LNode<T>(p->data);
				tail->next = new_node;
				new_node->prior = tail;
				tail = new_node;
			}

			tail->next = this;
			this->prior = tail;			
		}

	template<class K>
	friend std::ostream& operator <<(std::ostream& out, const LNode<K>* pHead);

};


template<class K>
std::ostream& operator <<(std::ostream& out, const LNode<K>* pHead)
{
	LNode<K>* tail = pHead->next;
	
	while (tail != pHead)
	{
		out << tail->data << std::endl;
		tail = tail->next;
	}

	return out;
}

