// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len < 0)
	{
		throw "Negative length";
	}

	BitLen = len;
	MemLen = len / (sizeof(TELEM) * 8) + 1;
	pMem = new TELEM[MemLen]{};
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
	if (n < 0 || n > BitLen)
	{
		throw "Out of bounds";
	}

	return (n / (sizeof(TELEM) * 8));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n < 0 || n > BitLen)
	{
		throw "Out of bounds";
	}

	TELEM mask0;

	int offset = (n % (sizeof(TELEM) * 8));

	mask0 = 1 << offset;

	return mask0;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n < 0 || n > BitLen)
	{
		throw "Out of bounds";
	}

	pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0 || n > BitLen)
	{
		throw "Out of bounds";
	}

	pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < 0 || n > BitLen)
	{
		throw "Out of bounds";
	}

	return pMem[GetMemIndex(n)] & GetMemMask(n);
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

	return *this;;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
	int logValue = 1;
	if (BitLen == bf.BitLen)
	{
		for (int i = 0; i < MemLen && logValue != 0; i++)
		{
			if (pMem[i] != bf.pMem[i])
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
	int logValue = 1;
	if (BitLen == bf.BitLen)
	{
		for (int i = 0; i < MemLen && logValue != 0; i++)
		{
			if (pMem[i] != bf.pMem[i])
			{
				logValue = 0;
			}
		}
	}
	else
	{
		logValue = 0;
	}
	return !logValue;
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
	TBitField result(std::max(BitLen, bf.BitLen));

	if (BitLen < bf.BitLen)
	{
		for (int i = 0; i < bf.MemLen; i++)
		{
			result.pMem[i] = bf.pMem[i];
		}
		for (int i = 0; i < MemLen; i++)
		{
			result.pMem[i] |= pMem[i];
		}

	}
	else if (BitLen > bf.BitLen)
	{

		for (int i = 0; i < MemLen; i++)
		{
			result.pMem[i] = pMem[i];
		}
		for (int i = 0; i < bf.MemLen; i++)
		{
			result.pMem[i] |= bf.pMem[i];
		}


	}
	else
	{
		for (int i = 0; i < result.BitLen; i++)
		{
			for (int i = 0; i < MemLen; i++)
			{
				result.pMem[i] = pMem[i] | bf.pMem[i];
			}

		}
	}
	return result;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
	TBitField result(std::max(BitLen, bf.BitLen));

	if (BitLen < bf.BitLen)
	{
		for (int i = 0; i < bf.MemLen; i++)
		{
			result.pMem[i] = bf.pMem[i];
		}
		for (int i = 0; i < MemLen; i++)
		{
			result.pMem[i] &= pMem[i];
		}

	}
	else if (BitLen > bf.BitLen)
	{

		for (int i = 0; i < MemLen; i++)
		{
			result.pMem[i] = pMem[i];
		}
		for (int i = 0; i < bf.MemLen; i++)
		{
			result.pMem[i] &= bf.pMem[i];
		}


	}
	else
	{
		for (int i = 0; i < result.BitLen; i++)
		{
			for (int i = 0; i < MemLen; i++)
			{
				result.pMem[i] = pMem[i] & bf.pMem[i];
			}

		}
	}
	return result;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField result(BitLen);

	for (int i = 0; i < MemLen; i++)
	{
		result.pMem[i] = ~pMem[i];
	}

	return result;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
	int i = 0;
	char ch;

	do
	{
		istr >> ch;
	} while (ch != ' ');

	while (true)
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
	}
	return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
	{
		if (bf.GetBit(i))
		{
			ostr << '1';
		}
		else
		{
			ostr << '0';
		}
	}
	return ostr;
}