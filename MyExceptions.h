#pragma once
#include <exception>
class  UsernameExist : public exception
{
public:
    virtual const char* what() const noexcept override
    {
        return " ������������ � ����� ������ ��� ����������! \n";
    }
};
class  UsernameNotExist : public exception
{
public:
    virtual const char* what() const noexcept override
    {
        return " ������! ������������������ ������������ � ����� ������ �� ������! \n�����������������.\n";
    }
};

class  WrongPassword : public exception
{
public:
    virtual const char* what() const noexcept override
    {
        return " ������������ ��������������� � ������ �������!\n";
    }
};
class  NotAutorized : public exception
{
public:
    virtual const char* what() const noexcept override
    {
        return " ������������ �� �����������!\n";
    }
};
class  NotAdmin : public exception
{
public:
    virtual const char* what() const noexcept override
    {
        return " ��� �������� �������� ������ ��������������!\n";
    }
};
class  ALLisreserved : public exception
{
public:
    virtual const char* what() const noexcept override
    {
        return " ��� ALL ��������������� ��� ��������� ��������!\n";
    }
};
class   MessNotSent : public exception
{
public:
    virtual const char* what() const noexcept override
    {
        return " ��������� �� ����������!\n";
    }
};