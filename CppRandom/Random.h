#pragma once
#include <random>
#include <functional>

class CRandom
{
public:
	~CRandom();

	void SetRange(int _min, int _max);		//��������������ķ�Χ
	int Random();							//����һ�������
	static CRandom* GetInstence();			//��ȡ���Ψһ����

private:
	CRandom();
	static CRandom* m_pInst;

	std::random_device rd;
	std::default_random_engine engine{ rd() };
	std::uniform_int_distribution<> dis{ 0, 65536 };

	int m_min{};
	int m_max{};

};

