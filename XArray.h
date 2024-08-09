 
#pragma once
//////////////////////////////////////////////////////
// Ўаблонный класс -контейнер                       //
// может хранить объекты любого типа                //
// динамически измен€ет свой размер                 //
//////////////////////////////////////////////////////
#include <iostream>
#include <exception>

using namespace std;

 
  class BadLength : public exception
{
public:
    virtual const char* what() const noexcept override
    {
        return "ќшибка: неверный аргумент длины массива!\n"  ;
    }
};
 
class BadRange : public exception
{
public:
    virtual const char* what() const noexcept override
    {
        return "ќшибка: выход за пределы массива!\n";
    }
};
class NotFound : public exception
{
public:
    virtual const char* what() const noexcept override
    {
        return "Ёлемент не найден!\n";
    }
};

template <typename X> class XArray
{
//private:
protected:
     int m_length;
    X* m_data;
public:
    XArray() = default;
    XArray(int length);
    XArray(const XArray& a);
    ~XArray();

    XArray& operator=(const XArray& a);
    void erase();
    X& operator[](int index);
    void reallocate(int newLength);
    void resize(int newLength);
    void insertBefore(X value, int index);
    void remove(int index);
    void insertAtBeginning(X value);
    void insertAtEnd(X value);
    int find(X elem);
    int  getLength() const;
};


template <typename X>  XArray <X>::XArray(int length) : m_length(length)
{



    if (m_length < 0) { throw BadLength(); }

  //  m_length = length;
    if (m_length > 0)
        m_data = new X[length]{};
}
template <typename X> XArray <X> ::XArray(const XArray& a) : XArray(a.getLength())
{
    std::copy_n(a.m_data, m_length, m_data);
}

template <typename X>  XArray <X>:: ~XArray()
{
    delete[] m_data;
}
template <typename X>  XArray<X>& XArray <X> ::operator=(const XArray& a)
{

    if (&a == this)
        return *this;


    reallocate(a.getLength());
    std::copy_n(a.m_data, m_length, m_data);

    return *this;
}
template <typename X> void XArray<X>::erase()
{
    delete[] m_data;

    m_data = nullptr;
    m_length = 0;
}

template <typename X> X& XArray <X> ::operator[](int index)
{
    //assert(index >= 0 && index < m_length);
    if (index < 0 || index >= m_length) throw BadRange();
    return m_data[index];
}
template <typename X> void XArray<X>::reallocate(int newLength)
{

    erase();
    if (newLength <= 0)
        return;
    m_data = new int[newLength];
    m_length = newLength;
}
template <typename X> void XArray<X>::resize(int newLength)
{
    if (newLength == m_length)
        return;
    if (newLength <= 0)
    {
        erase();
        return;
    }
    X* data{ new X[newLength] };
    if (m_length > 0)
    {
        int elementsToCopy{ (newLength > m_length) ? m_length : newLength };
        std::copy_n(m_data, elementsToCopy, data);
    }
    delete[] m_data;
    m_data = data;
    m_length = newLength;
}

template <typename X> void XArray<X>::insertBefore(X value, int index)
{

    // assert(index >= 0 && index <= m_length);
    if (index < 0 || index > m_length) throw BadRange();
    int* data{ new X[m_length + 1] };
    std::copy_n(m_data, index, data);
    data[index] = value;
    std::copy_n(m_data + index, m_length - index, data + index + 1);
    delete[] m_data;
    m_data = data;
    ++m_length;
}

template <typename X> void XArray<X>::remove(int index)
{
    // assert(index >= 0 && index < m_length);
    if (index < 0 || index >= m_length) throw BadRange();
    if (m_length == 1)
    {
        erase();
        return;
    }
    X* data{ new X[m_length - 1] };

    std::copy_n(m_data, index, data);

    std::copy_n(m_data + index + 1, m_length - index - 1, data + index);

    delete[] m_data;
    m_data = data;
    --m_length;
}
template <typename X> void XArray<X>::insertAtBeginning(X value)
{
    insertBefore(value, 0);
}
template <typename X> void XArray<X>::insertAtEnd(X value)
{
    insertBefore(value, m_length);
}
template <typename X> int XArray<X>::find(X elem)
{
    for (int i{ 0 }; i < getLength(); ++i)
        if (m_data[i] == elem) return i;

    throw NotFound();
}

template <typename X>  int XArray <X>::getLength() const
{ return m_length; }

 
