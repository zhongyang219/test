#pragma once
#include <random>
#include <functional>

class CRandom
{
public:
	~CRandom();

	void SetRange(int _min, int _max);		//设置生成随机数的范围
	int Random();							//生成一个随机数
	static CRandom* GetInstence();			//获取类的唯一对象

private:
	CRandom();
	static CRandom* m_pInst;

	std::random_device rd;
	std::default_random_engine engine{ rd() };
	std::uniform_int_distribution<> dis{ 0, 65536 };

	int m_min{};
	int m_max{};

};

