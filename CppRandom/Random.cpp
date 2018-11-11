#include "pch.h"
#include "Random.h"

CRandom* CRandom::m_pInst = nullptr;

CRandom::CRandom()
{
}


CRandom::~CRandom()
{
	if (m_pInst != nullptr)
		delete m_pInst;
}

void CRandom::SetRange(int _min, int _max)
{
	if (_min < _max)
	{
		m_min = _min;
		m_max = _max;
	}
}

int CRandom::Random()
{
	static auto dice = std::bind(dis, engine);
	int _rand = dice();
	if (m_min == m_max)
	{
		return _rand;
	}
	else
	{
		int rtn = _rand % (m_max - m_min);
		rtn += m_min;
		return rtn;
	}
}

CRandom * CRandom::GetInstence()
{
	if (m_pInst == nullptr)
		m_pInst = new CRandom();
	return m_pInst;
}
