// 树形结构遍历.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <stack>

struct CNode
{
	CNode* pParent{};
	std::string name;
	std::list<CNode*> pChildList;
	int num{};

	CNode(const char* name)
	{
		this->name = name;
	}

	void AddNode(CNode* pNode)
	{
		pNode->pParent = this;
		pChildList.push_back(pNode);
	}

	void GetIndex() const
	{
		//auto 
	}
};

int GetNodeNum(CNode* pRoot, CNode* pNode)
{
	std::stack<CNode*> nodeStack;
	nodeStack.push(pRoot);
	int num{};
	while (!nodeStack.empty())
	{
		CNode* pCurNode = nodeStack.top();
		nodeStack.pop();
		//std::cout << pNode->name << std::endl;
		if (pCurNode == pNode)
			return num;
		num++;

		auto& childList = pCurNode->pChildList;
		if (!childList.empty())
		{
			for (auto iter = childList.rbegin(); iter != childList.rend(); iter++)
			{
				nodeStack.push(*iter);
			}
		}
	}
	return -1;
}

void ErgodicTree(CNode* pRoot)
{
	std::stack<CNode*> nodeStack;
	nodeStack.push(pRoot);
	while (!nodeStack.empty())
	{
		CNode* pNode = nodeStack.top();
		nodeStack.pop();
		std::cout << pNode->name << std::endl;

		auto& childList = pNode->pChildList;
		if (!childList.empty())
		{
			for (auto iter = childList.rbegin(); iter != childList.rend(); iter++)
			{
				nodeStack.push(*iter);
			}
		}
	}
}

int main()
{
	CNode root("root");
	CNode node_1("node_1");
	CNode node_2("node_2");
	root.AddNode(&node_1);
	root.AddNode(&node_2);

	CNode node_2_1("node_2_1");
	CNode node_2_2("node_2_2");
	node_2.AddNode(&node_2_1);
	node_2.AddNode(&node_2_2);

	CNode node_3("node_3");
	root.AddNode(&node_3);

	//ErgodicTree(&root);

	std::cout << "root " << GetNodeNum(&root, &root)<<std::endl;
	std::cout << "node_1 " << GetNodeNum(&root, &node_1)<<std::endl;
	std::cout << "node_2 " << GetNodeNum(&root, &node_2)<<std::endl;
	std::cout << "node_3 " << GetNodeNum(&root, &node_3)<<std::endl;
	std::cout << "node_2_1 " << GetNodeNum(&root, &node_2_1)<<std::endl;
	std::cout << "node_2_2 " << GetNodeNum(&root, &node_2_2)<<std::endl;

    std::cout << "Hello World!\n"; 
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
