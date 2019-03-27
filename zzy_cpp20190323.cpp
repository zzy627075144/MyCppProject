// zzy_cpp20190323.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
using namespace std;
// 常量定义
// 定义方向
const int RIGHT = 0;
const int DOWN = 1;
const int LEFT = 2;
const int UP = 3;
const int WAY_NUM = 4;
// 定义行走状态用的
const int YES = 5;
const int NO = 6;
// 抽象迷宫节点类型
class MazeNode
{
public:
	MazeNode()
	{
		for (int i = 0; i < WAY_NUM; ++i)
		{
			mstate[i] = YES;
		}
		isPath = false;
	}
	void setvalue(int val,int x,int y)
	{
		mval = val;
		mx = x;
		my = y;
	}
	int getval()
	{
		return mval;
	}
	int getmx()
	{
		return mx;
	}
	int getmy()
	{
		return my;
	}
	int getstate(int position)
	{
		return mstate[position];
	}
	void setstate(int position)
	{
		mstate[position] = NO;
	}
	void setcopystate(int position,int state)
	{
		mstate[position] = state;
	}
	void setIsPathYes()
	{
		isPath = true;
	}
	void setIsPathNo()
	{
		isPath = false;
	}
	bool getIsPath()
	{
		return isPath;
	}
private:
	int mval; // 节点的值
	int mx; // 节点坐标
	int my; // 节点坐标
	int mstate[WAY_NUM]; // 节点四个方向的状态
	bool isPath;//标志是否是可行路径
};
// 抽象顺序栈结构
class CStack
{
public:
	CStack(int size = 50) // 构造函数，给对象成员变量进行初始化
	{
		mtop = 0;
		msize = size;
		mpstack = new MazeNode[msize];
	}
	~CStack() // 析构函数，释放对象
	{
		delete[]mpstack;
		mpstack = nullptr;
	}
	void push(MazeNode val) // 入栈
	{
		int state = 0;
		if (full())
		{
			resize();
		}
		else
		{
		//	mpstack[mtop++] = val;
			mpstack[mtop].setvalue(val.getval(),val.getmx(),val.getmy());
			for (int i = 0;i < 4;i++)
			{
				state = val.getstate(i);
				mpstack[mtop].setcopystate(i,state);
			}
			mtop++;
		}
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
	MazeNode top()
	{
		if (empty())
			throw "stack is empty!";
		return mpstack[mtop - 1];
	}
	bool full() { return mtop == msize; }
	bool empty() { return mtop == 0; }
private:
	MazeNode *mpstack; // 存储栈的数据
	int mtop; // 表示栈顶下标
	int msize; // 表示栈的总长度
	void resize()
	{
		MazeNode *ptmp = new MazeNode[msize * 2];
		for (int i = 0; i < msize; ++i)
		{
			ptmp[i] = mpstack[i];
		}
		delete[]mpstack;
		mpstack = ptmp;
		msize *= 2;
	}
	CStack(const CStack &src);
	void operator=(const CStack &src);
};
// 抽象迷宫类型
class Maze
{
public:
	Maze(int row, int col)
	{
		mrow = row ;
		mcol = col ;
		printpath = true;
		mpMaze = new MazeNode*[mrow];
		for (int i = 0;i< mrow;i++)
		{
			mpMaze[i] = new MazeNode[mcol];
		}
	}
	~Maze()
	{
		for (int j = 0;j< mrow;j++)
		{
			delete[]mpMaze[j];
		}
		delete[] mpMaze;
	}
	void initMazeNode(int data, int row, int col)
	{
		mpMaze[row][col].setvalue(data,row,col);
	}
	void addWall()
	{
		for (int j = 0; j < mcol; ++j)
		{
			mpMaze[0][j].setvalue(1,0,j);			
		}
		for (int i = 0; i < mrow; ++i)
		{
			mpMaze[i][0].setvalue(1, i, 0);
		}
		for (int k = 1; k < mcol; ++k)
		{
			mpMaze[mrow-1][k].setvalue(1, mrow-1, k);
		}
		for (int n = 1; n < mrow; ++n)
		{
			mpMaze[n][mcol-1].setvalue(1, n, mcol-1);
		}
	}
	void adjustMaze()
	{
		for (int i = 1;i < mrow - 1;i++)
		{
			for (int j = 1;j < mcol - 1;j++)
			{
				//四个方向处理
				if ((mpMaze[i][j + 1].getval() == 1))			//右方向
				{
					mpMaze[i][j].setstate(RIGHT);
				//	cout << "x: " << i << "y: " << j << "  " << " RIGHT: " << mpMaze[i][j].getstate(RIGHT) << endl;
				}

				if ((mpMaze[i + 1][j].getval() == 1))			//下方向
				{
					mpMaze[i][j].setstate(DOWN);
				//	cout << "x: " << i << "y: " << j << "  " << " DOWN: " << mpMaze[i][j].getstate(DOWN) << endl;
				}

				if ((mpMaze[i][j - 1].getval() == 1))			//左方向
				{
					mpMaze[i][j].setstate(LEFT);
				//	cout << "x: " << i << "y: " << j << "  " << " LEFT: " << mpMaze[i][j].getstate(LEFT) << endl;
				}

				if ((mpMaze[i - 1][j].getval() == 1))			//上方向
				{
					mpMaze[i][j].setstate(UP);
				//	cout << "x: " << i << "y: " << j << "  " << " UP: " << mpMaze[i][j].getstate(UP) << endl;
				}					
			}
		}
	}
	void findMazePath()
	{
		int count = 0;
		for (int n = 0;n < 2;n++)
		{
			if (mpMaze[1][1].getstate(n) == NO)
			{
				count++;
			}
		}
		if (count == 2 || mpMaze[1][1].getval() == 1)
		{
			cout << "起始位置不能移动，该迷宫没有可走路径" << endl;
			exit(0);
		}
		int i = 1;
		int j = 1;
		mstack.push(mpMaze[i][j]);
		mpMaze[i][j].setIsPathYes();
		while (i < (mrow - 2)||j < (mcol - 2))
		{		
			if (mstack.top().getstate(RIGHT) == YES)		//向右寻路
			{
				mpMaze[i][j].setstate(RIGHT);
				j = j + 1;
				mpMaze[i][j].setstate(LEFT);
				mstack.push(mpMaze[i][j]);
				mpMaze[i][j].setIsPathYes();
			}
			if (mstack.top().getstate(DOWN) == YES)			//向下寻路
			{
				mpMaze[i][j].setstate(DOWN);
				i = i + 1;
				mpMaze[i][j].setstate(UP);
				mstack.push(mpMaze[i][j]);
				mpMaze[i][j].setIsPathYes();
			}
			if (mstack.top().getstate(LEFT) == YES)			//向左寻路
			{
				mpMaze[i][j].setstate(LEFT);
				j = j - 1;
				mpMaze[i][j].setstate(RIGHT);
				mstack.push(mpMaze[i][j]);
				mpMaze[i][j].setIsPathYes();
			}
			if (mstack.top().getstate(UP) == YES)			//向上寻路
			{
				mpMaze[i][j].setstate(UP);
				i = i - 1;
				mpMaze[i][j].setstate(DOWN);
				mstack.push(mpMaze[i][j]);
				mpMaze[i][j].setIsPathYes();
			}
			if ((mstack.top().getstate(RIGHT) == NO) && (mstack.top().getstate(DOWN) == NO) && (mstack.top().getstate(LEFT) == NO) && (mstack.top().getstate(UP) == NO))
			{
				mpMaze[i][j].setIsPathNo();
				mstack.pop();
				if (i != (mrow - 2) && j != (mcol - 2))
				{
					i = mstack.top().getmx();
					j = mstack.top().getmy();
				}
			}
			if (mstack.empty())
			{
				cout << "该迷宫没有可行路径。" << endl;
				printpath = false;
				break;
			}
		}
		mpMaze[mrow - 2][mcol - 2].setIsPathYes();
	}
	void showResult()
	{
		if (printpath)
		{
			cout << "该迷宫的可行路径为：" << endl;
			for (int i = 1; i < mrow - 1; i++)
			{
				for (int j = 1; j < mcol - 1; j++)
				{
					if (true == mpMaze[i][j].getIsPath())
					{
						cout << "*" << " ";
					}
					else
					{
						cout << mpMaze[i][j].getval() << " ";
					}
				}
				cout << endl;
			}
		}
	}
private:
	int mrow;
	int mcol;
	CStack mstack;
	MazeNode **mpMaze;
	bool printpath;
	//为了防止对象浅拷贝出现问题，私有化那两个函数
	Maze(const Maze &src);
	void operator= (const Maze &src);
};
int main()
{
	int mrow, mcol;
	cout << "请输入迷宫路径的行列数：";
	int row, col;
	cin >> row >> col;
	mrow = row + 2;
	mcol = col + 2;
	Maze maze(mrow, mcol);
	cout << "请输入迷宫的具体路径信息(0表示能走，1表示不能走)：" << endl;
	for (int i = 1; i < mrow - 1;++i)
	{
		for (int j = 1; j < mcol - 1;++j)
		{
			int data;
			cin >> data;
			maze.initMazeNode(data, i, j);
		}
	}
	// 加入边界防止越界
	maze.addWall();
	// 调整迷宫所有节点的方向的行走状态
	maze.adjustMaze();
	// 寻找迷宫路径
	maze.findMazePath();
	// 打印寻找结构
	maze.showResult();
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
