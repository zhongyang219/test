// CppRandom.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <random>
#include <functional>
#include "Random.h"
#include <string>

std::wstring GetRandomString(int length)
{
	std::wstring result;
	int char_type;		//当前要生成的字符类型 0：数字；1：小写字母；2：大写字母
	for (int i{}; i < length; i++)
	{
		char_type = CRandom::GetInstence()->Random() % 3;		//随机确定要生成的字符类型
		wchar_t current_char;
		switch (char_type)
		{
		case 0:
			current_char = L'0' + (CRandom::GetInstence()->Random() % 10);
			break;
		case 1:
			current_char = L'a' + (CRandom::GetInstence()->Random() % 26);
			break;
		case 2:
			current_char = L'A' + (CRandom::GetInstence()->Random() % 26);
			break;
		}
		result.push_back(current_char);
	}
	return result;
}


int main()
{
	//CRandom::GetInstence()->SetRange(0, 20);
	//for (int n = 0; n < 10; n++)
	//	std::cout << CRandom::GetInstence()->Random() << " " << std::endl;
	//std::cout << "Hello World!\n";

	//CRandom::GetInstence()->SetRange(100, 1000);
	//for (int n = 0; n < 10; n++)
	//	std::cout << CRandom::GetInstence()->Random() << " " << std::endl;

 //   std::cout << "Hello World!\n"; 

	//char buff[32];
	//sprintf_s(buff, "%%.%df", 6);
	//printf(buff, 2.1);

	//int rand;
	//for (int i = 0; i < 10; i++)
	//{
	//	std::wstring str = GetRandomString(32);
	//	int a = 0;
	//}

	CRandom::GetInstence()->SetRange(0, 6666);
	int a = CRandom::GetInstence()->Random();


	system("pause");
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
