// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#include <cmath>

TBitField::TBitField(int len)
{
	if (len < 0)
	{
		throw "Negative length";
	}

	BitLen = len;
	MemLen = (len) / (sizeof(TELEM) * 8) + 1;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = 0;
	}
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[bf.MemLen]{};

	for (int i = 0; i < MemLen; i++)
	{
		this->pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	delete[] pMem;

	if (pMem != nullptr)
	{
		pMem = NULL;
		MemLen = NULL;
	}
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n < 0 || n >= BitLen)
	{
		throw "Out of bounds(GetMemIndex)";
	}

	return int(floor(n / (sizeof(TELEM) * 8)));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1 << (n % (sizeof(TELEM) * 8));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n < 0 || n >= BitLen)
	{
		throw "Out of bounds(SetBit)";
	}

	pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0 || n >= BitLen)
	{
		throw "Out of bounds(ClrBit)";
	}

	pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < 0 || n >= BitLen)
	{
		throw "Out of bounds(GetBit)";
	}

	return static_cast<bool>(pMem[GetMemIndex(n)] & GetMemMask(n));

	/*if ((pMem[GetMemIndex(n)] & GetMemMask(n)) != 0)
	{
		return 1;
	}
	return 0;*/
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
	if (this == &bf)
	{
		return *this;
	}

	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	delete[] pMem;
	pMem = new TELEM[bf.MemLen]{};


	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}

	return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
	int logValue = 1;
	if (BitLen == bf.BitLen)
	{
		for (int i = 0; i < BitLen; i++)
		{
			if (this->GetBit(i) != bf.GetBit(i))
			{
				logValue = 0;
			}
		}
	}
	else
	{
		logValue = 0;
	}
	return logValue;
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
	return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
	if (bf.MemLen >= MemLen)
	{
		TBitField result(bf);
		for (int i = 0; i < MemLen; i++)
		{
			result.pMem[i] = pMem[i] | bf.pMem[i];
		}	
		return result;
	}
	else
	{
		TBitField result(*this);
		for (int i = 0; i < bf.MemLen; i++)
		{
			result.pMem[i] = pMem[i] | bf.pMem[i];
		}	
		return result;
	}
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
	if (BitLen < bf.BitLen)
	{
		TBitField result(bf.BitLen);
		for (int i = 0; i < BitLen; i++)
		{
			if (GetBit(i) & bf.GetBit(i))
			{
				result.SetBit(i);
			}
			
		}
		return result;
	}
	else
	{
		TBitField result(BitLen);
		for (int i = 0; i < bf.BitLen; i++)
		{
			if (GetBit(i) & bf.GetBit(i))
			{
				result.SetBit(i);
			}
			
		}
		return result;
	}
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField bf(BitLen);
	for (int i = 0; i < MemLen; i++)
	{
		bf.pMem[i] = ~pMem[i];
	}
	return bf;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
	int i = 0;
	char ch;

	do
	{
		istr >> ch;
		if (ch == '1')
		{
			bf.SetBit(i++);
		}
		else if (ch == '0')
		{
			bf.ClrBit(i++);
		}
		else break;
	} while ((ch == '1') || (ch == '0'));
	return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
	{
		ostr << bf.GetBit(i);
	}
	return ostr;
}