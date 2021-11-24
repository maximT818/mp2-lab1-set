// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
    MaxPower = mp;
}

// конструктор копирования

TSet::TSet(const TSet& s) : BitField(s.BitField)
{
    {
        MaxPower = s.MaxPower;
    }
}

// конструктор преобразования типа

TSet::TSet(const TBitField& bf) : MaxPower(bf.GetLength()), BitField(bf)
{
}

TSet::operator TBitField()
{
    return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    if (Elem < 0 || Elem >= MaxPower)
    {
        throw "Out of bounds(IsMember)";
    }
    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    if (Elem < 0 || Elem >= MaxPower)
    {
        throw "Out of bounds(InsElem)";
    }

    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    if (Elem < 0 || Elem >= MaxPower)
    {
        throw "Out of bounds(DelElem)";
    }

    BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet& s) // присваивание
{
    if (this == &s)
    {
        return *this;
    }


    BitField = s.BitField;
    MaxPower = s.MaxPower;
    return *this;
}

int TSet::operator==(const TSet& s) const // сравнение
{
    return (BitField == s.BitField);
}

int TSet::operator!=(const TSet& s) const // сравнение
{
    return !(BitField == s.BitField);
}

TSet TSet::operator+(const TSet& s) // объединение
{
    TSet result(max(MaxPower, s.MaxPower));
    result.BitField = BitField | s.BitField;

    return result;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    BitField.SetBit(Elem);

    return *this;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    BitField.ClrBit(Elem);

    return *this;
}

TSet TSet::operator*(const TSet& s) // пересечение
{
    TSet result(max(MaxPower, s.MaxPower));
    result.BitField = BitField & s.BitField;

    return result;
}

TSet TSet::operator~(void) // дополнение
{
    TSet result(MaxPower);
    result.BitField = ~BitField;

    return result;
}

// перегрузка ввода/вывода

istream& operator>>(istream& istr, TSet& s) // ввод
{
    int saver;
    char ch;

    do
    {
        istr >> ch;
    } while (ch != '{');

    do {
        istr >> saver;
        s.InsElem(saver);

        do
        {
            istr >> ch;
        } while ((ch != '}') && (ch != ','));


    } while (ch != '}');

    return istr;
}

ostream& operator<<(ostream& ostr, const TSet& s) // вывод
{
    int n;
    char ch = '{';

    for (int i = 0; i < s.MaxPower; i++)
    {
        if (s.IsMember(i))
        {
            ostr << ch << i;
            ch = ',';
        }
    }

    ostr << "}";

    return ostr;
}
