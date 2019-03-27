// zzy_cpp20190316.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <stdio.h>
#include <iostream>
using namespace std;

// OOP实现一个链表结构
class Link
{
public:
	Link() // 构造函数
	{
		mphead = new Node();
	}
	~Link() // 析构函数
	{
		Node *poor = mphead;
		while (poor!=nullptr)
		{
			mphead = mphead->mpnext;
			delete poor;
			poor = mphead;
		}
	}
	void insertHead(int val)
	{
		Node *mnode = new Node(val);
		mnode->mpnext = mphead->mpnext;
		mphead->mpnext = mnode;
		
	}
	void insertTail(int val)
	{
		Node *mnode = mphead;
		while (mnode->mpnext!=nullptr)
		{
			mnode = mnode->mpnext;
		}
		mnode->mpnext = new Node(val);
	}
	void remove(int val) // 删除所有值为val的节点
	{
		Node *mnode = mphead;
		Node *mmnode = mphead->mpnext;
		while (mmnode!=nullptr)
		{
			if (mmnode->mdata==val)
			{
				mnode->mpnext = mmnode->mpnext;
				delete mmnode;
				mmnode = mnode->mpnext;
			}
			else
			{
				mnode = mmnode;
				mmnode = mmnode->mpnext;
			}
		}
	}

	bool findvalue(int val)
	{
		Node *mnode = mphead;
		Node *mmnode = mphead->mpnext;
		while (mmnode != nullptr)
		{
			if (mmnode->mdata == val)
			{
				return true;
			}
			else
			{
				mnode = mmnode;
				mmnode = mmnode->mpnext;
			}
		}
		return false;
	}

	bool empty()
	{
		if (nullptr == mphead->mpnext)
		{
			return true;
		}
		return false;
	}

	int front()
	{
		return mphead->mpnext->mdata;
	}

	void deletefront()
	{
		Node *mnode = mphead;
		Node *mmnode = mphead->mpnext;
		mnode->mpnext = mmnode->mpnext;
		delete mmnode;
	}

	void show()
	{
		Node *mnode = mphead->mpnext;
		while (mnode!=nullptr)
		{
			cout << mnode->mdata;
			mnode = mnode->mpnext;
		}
		cout << endl;
	}
private:
	// 节点类型
	struct Node
	{
		Node(int data = 0)
		{
			mdata = data;
			mpnext = nullptr;
		}
		int mdata;
		Node *mpnext;
	};

	// private化拷贝构造和赋值重载函数
	Link(const Link&);
	void operator=(const Link&);

	Node *mphead;
};

class CCircleQueue
{
public:
	CCircleQueue(int size = 10) // 构造函数
	{
		msize = size;
		mpQue = new int[msize];
		mfront = 0;
		mrear = 0;
	}
	~CCircleQueue() // 析构函数
	{
		delete[] mpQue;
		mpQue = nullptr;
	}
	CCircleQueue(const CCircleQueue &src) // 拷贝构造函数
	{
		mpQue = new int[src.msize];
		for (int i = mfront; i != src.mrear; i = (i + 1) % src.msize)
		{
			mpQue[i] = src.mpQue[i];
		}
		mfront = src.mfront;
		mrear = src.mrear;
		msize = src.msize;
	}
	void operator=(const CCircleQueue &src)// 赋值重载函数
	{
		if (this == &src)
		{
			return;
		}
		delete[]mpQue;
		mpQue = new int[src.msize];
		for (int i = mfront; i != src.mrear; i = (i + 1) % src.msize)
		{
			mpQue[i] = src.mpQue[i];
		}
		mfront = src.mfront;
		mrear = src.mrear;
		msize = src.msize;
	}

	void addQue(int val) // 入队
	{
		if (full())
		{
			return;
		}
		mpQue[mrear] = val;
		mrear = (mrear + 1)% msize;
	}
	void delQue()// 出队
	{
		if (empty())
		{
			return;
		}
		mfront = (mfront + 1) % msize;
	}
	int front()// 返回队头元素
	{
		return mpQue[mfront];
	}
	int back()// 返回队尾元素
	{
		return mpQue[(mrear - 1 +msize) % msize];
	}

	bool full() // 判满
	{
		if (((mrear + 1) % msize)== mfront)
		{
			return true;
		}
		return false;
	}
	bool empty() // 判空
	{
		if (mfront == mrear)
		{
			return true;
		}
		return false;
	}
	void erastvalue(int val)
	{
		for (int i = mfront; i != mrear; i = (i + 1) % msize)
		{
			if (mpQue[i]==val)
			{
				delQue();
			}
		}
	}
	bool findvalue(int val)
	{
		bool statu = false;
		for (int i = mfront; i != mrear; i = (i + 1) % msize)
		{
			if (mpQue[i] == val)
			{
				statu = true;
			}
		}
		return statu;
	}
	void print()
	{
		if (empty())
		{
			cout << "myQue is empty!" << endl;
		}
		else
		{ 
			for (int i = mfront;i != mrear;i = (i + 1)% msize)
			{
				cout << mpQue[i] ;
			}
			cout << endl;
		}
	}

private:
	int *mpQue; //保存队列元素的数据结构
	int mfront; //队头下标
	int mrear; //队尾下标
	int msize; //扩容的总长度

	void resize() // 2倍扩容循环队列
	{
		int *newQue = new int[msize * 2]();
		int count = 0;
		for (int i = mfront;i < mrear;i = (i+1) % msize)
		{
			newQue[count++] = mpQue[i];
		}
		delete[] mpQue;
		msize = msize * 2;
		mfront = 0;
		mrear = count;
		mpQue = newQue;
	}
};

class CStack
{
public:
	// CStack() CStack(int)
	CStack(int size = 3) // 构造函数，给对象成员变量进行初始化
	{
		mtop = 0;
		msize = size;
		mpstack = new int[msize];
	}
	// 拷贝构造对象 默认做的是浅拷贝
	CStack(const CStack &src)
	{
		mpstack = new int[src.msize];
		for (int i = 0; i < src.msize; ++i)
		{
			mpstack[i] = src.mpstack[i];
		}
		mtop = src.mtop;
		msize = src.msize;
	}
	// 赋值重载函数  stack1 = stack1
	void operator=(const CStack &src)
	{
		// 防止自赋值
		if (this == &src)
			return;

		// 先释放this指向对象现有的外部资源
		delete[]mpstack;

		// 根据src引用的对象资源尺寸，重新开辟空间，拷贝数据
		mpstack = new int[src.msize];
		for (int i = 0; i < src.msize; ++i)
		{
			mpstack[i] = src.mpstack[i];
		}
		mtop = src.mtop;
		msize = src.msize;
	}
	~CStack() // 析构函数，释放对象
	{
		delete[]mpstack;
		mpstack = nullptr;
	}
	void push(int val) // 入栈
	{
		if (full())
			resize();
		mpstack[mtop++] = val;
	}
	void pop() // 出栈
	{
		if (empty())
		{
			cout << "the stack is empty." << endl;
			return;
		}
		else
		{
			mtop--;
		}
	}
	void erastvalue(int val)	//删除指定值
	{
		CStack localstack;
		while (!empty())
		{
			if (top()==val)
			{
				pop();
			}
			else
			{
				localstack.push(top());
				pop();
			}
		}
		while (!localstack.empty())
		{
			push(localstack.top());
			localstack.pop();
		}
	}
	bool findvalue(int val)
	{
		bool statu = false;
		for (int i = mtop;i>0;i--)
		{
			if (mpstack[i] == val)
			{
				statu = true;
			}
		}
		return statu;
	}
	int top()
	{
		if (empty())
			throw "stack is empty!";
		return mpstack[mtop - 1];
	}
	bool full() { return mtop == msize; }
	bool empty() { return mtop == 0; }

	void print()
	{
		if (empty())
		{
			cout << "the stack is empty." << endl;
		}
		else
		{
			for (int i = 0;i<msize;++i)
			{
				cout << mpstack[i] << " ";
			}
			cout << endl;
		}
	}

private:
	int *mpstack; // 存储栈的数据
	int mtop; // 表示栈顶下标
	int msize; // 表示栈的总长度

	void resize()
	{
		int *ptmp = new int[msize * 2];
		//memcpy(ptmp, mpstack, sizeof(int)*msize);
		//realloc  对象扩容禁止使用realloc/memcpy这些函数!!!
		for (int i = 0; i < msize; ++i)
		{
			ptmp[i] = mpstack[i];
		}
		delete[]mpstack;
		mpstack = ptmp;
		msize *= 2;
	}
};
/*
软件运行如下：
加载数据当中...加载完成！
-------------
1.单链表
2.栈
3.队列
4.退出系统 => 保存内存数据
-------------
请选择：1

-------------
当前数据结构是：xxx
1.查看
2.增加
3.删除
4.查询
5.返回上一级菜单
-------------
请选择：
*/
// 数据结构系统类
class DSSystem
{
public:

	DSSystem()
	{
		filecontrol = true;
	}
	
	void run() // 系统的启动函数
	{
		// 1.加载文件中的数据
		if (filecontrol)
		{
			ReadInFile();
		}
		// 2.显示主菜单
		cout << "-------------" << endl;
		cout << "1.单链表" << endl;
		cout << "2.栈" << endl;
		cout << "3.队列" << endl;
		cout << "4.退出系统" << endl;
		cout << "-------------" << endl;
		cout << "请选择:";
		cin >> mDsChoice;

		switch (mDsChoice)
		{
		case 1:
		case 2:
		case 3:
			runChild();
			break;
		case 4:
			cout << "保存数据中...";
			// 保存数据，写入文件
			if (!filecontrol)
			{
				WriteToFile();
			}

			cout << "保存成功！欢迎下次使用！" << endl;
			exit(0);
		}
	}
	void runChild() // 系统二级菜单的启动函数
	{

		int choice = 0;
		int addvalue = 0;
		int deletevalue = 0;
		int findvalue = 0;
		while(1)
		{ 
			cout << "-------------" << endl;
			switch (mDsChoice)
			{
			case 1:
				cout << "当前选择的数据结构是:单链表" << endl;
				break;
			case 2:
				cout << "当前选择的数据结构是:栈" << endl;
				break;
			case 3:
				cout << "当前选择的数据结构是:队列" << endl;
				break;
			}
			cout << "1.查看" << endl;
			cout << "2.增加" << endl;
			cout << "3.删除" << endl;
			cout << "4.查询" << endl;
			cout << "5.返回" << endl;
			cout << "-------------" << endl;
			cout << "请选择:";
			cin >> choice;
			switch (choice)
			{
			case 1:
				FindSeek();
				break;
			case 2:
				cout << "请输入要插入的值：" << endl;
				cin >> addvalue;
				AddData(addvalue);
				cout << "插入成功" << endl;
				break;
			case 3:
				cout << "请输入要删除的值：" << endl;
				cin >> deletevalue;
				DeleteData(deletevalue);
				cout << "删除成功" << endl;
				break;
			case 4:
				cout << "请输入要查找的值：" << endl;
				cin >> findvalue;
				if (InquiryData(findvalue))
				{
					cout << "查找的值存在" << endl;
				}
				else
				{
					cout << "查找的值不存在" << endl;
				}
				break;
			case 5:
				run();
				break;
			}
		}
	}

	void FindSeek()			//查看
	{
		switch (mDsChoice)
		{
		case 1:
			mlink.show();
			break;
		case 2:
			mstack.print();
			break;
		case 3:
			mqueue.print();
			break;
		}
	}

	void AddData(int val)	//增加
	{
		switch (mDsChoice)
		{
		case 1:
			mlink.insertTail(val);
			break;
		case 2:
			mstack.push(val);
			break;
		case 3:
			mqueue.addQue(val);
			break;
		}
	}

	void DeleteData(int val)		//删除
	{
		switch (mDsChoice)
		{
		case 1:
			mlink.remove(val);
			break;
		case 2:
			mstack.erastvalue(val);
			break;
		case 3:
			mqueue.erastvalue(val);
			break;
		}
	}

	bool InquiryData(int val)		//查询
	{
		bool statu = false;
		switch (mDsChoice)
		{
		case 1:
			statu = mlink.findvalue(val);
			break;
		case 2:
			statu = mstack.findvalue(val);
			break;
		case 3:
			statu = mqueue.findvalue(val);
			break;
		}
		return statu;
	}

private:
	CStack mstack;
	CCircleQueue mqueue;
	Link mlink;
	FILE *mflie;
	bool filecontrol;
	int mDsChoice; // 表示主菜单选择的数据结构
	void WriteToFile()		//写入文件
	{
		CStack stack;
		mflie = fopen("CSeqStack.txt", "w");
		if (nullptr == mflie)
		{
			cout << "写入失败!" << endl;
		}
		
		while (!mstack.empty())
		{
			stack.push(mstack.top());
			mstack.pop();
		}
		
		while (!stack.empty())
		{
			fprintf(mflie,"%d ", stack.top() );
			stack.pop();
		}
		fclose(mflie);
		mflie = nullptr;
		
		mflie = fopen("CCircleQueue.txt", "w");
		while (!mqueue.empty())
		{
			fprintf(mflie, "%d ", mqueue.back());
			mqueue.delQue();
		}
		fclose(mflie);
		mflie = nullptr;
		
		mflie=fopen("Link.txt", "w");
		while (!mlink.empty())
		{
			fprintf(mflie, "%d ", mlink.front());
			mlink.deletefront();
		}
		fclose(mflie);
		mflie = nullptr;
		cout << "数据保存成功... ..." << endl;
	}
	void ReadInFile()		//读入文件数据
	{
		cout << "数据加载中... ..." << endl;
		mflie = fopen("CSeqStack.txt", "r");
		if (nullptr == mflie)
		{
			cout << "加载失败!" << endl;
		}
		int num = 0;
		while (!feof(mflie))
		{
			int a = fgetc(mflie);
			if (a != ' ')
			{
				num *= 10;
				num += (a - 48);
			}
			else
			{
				mstack.push(num);
				num = 0;
			}
		}
		cout << "CStack加载完成... ..." << endl;
		fclose(mflie);
		mflie = nullptr;
		mstack.print();
		num = 0;
		mflie = fopen("CCircleQueue.txt", "r");
		while (!feof(mflie))
		{
			int a = fgetc(mflie);
			if (a != ' ')
			{
				num *= 10;
				num += (a - 48);
			}
			else
			{
				mqueue.addQue(num);
				num = 0;
			}
		}
		cout << "CCircleQueue加载完成... ..." << endl;
		fclose(mflie);
		mflie = nullptr;
		mqueue.print();
		num = 0;
		mflie = fopen("Link.txt", "r");
		while (!feof(mflie))
		{
			int a = fgetc(mflie);
			if (a != ' ')
			{
				num *= 10;
				num += (a - 48);
			}
			else
			{
				mlink.insertTail(num);
				num = 0;
			}
		}
		cout << "Link加载完成... ..." << endl;
		fclose(mflie);
		mflie = nullptr;
		mlink.show();
		cout << "数据加载成功... ..." << endl;
		filecontrol = false;
	}
};

int main()
{
	DSSystem dssy;
	dssy.run();
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
