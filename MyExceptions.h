#pragma once
// классы -наследники exception для перхвата нештатных ситуаций связанных с неверным вводом данных
#include <exception>  

class  UsernameExist : public exception
{
public:
    virtual const char* what() const noexcept override
    {
        return " Пользователь с таким именем уже существует! \n";
    }
};
class  UsernameNotExist : public exception
{
public:
    virtual const char* what() const noexcept override
    {
        return " Ошибка! Зарегистрированный пользователь с таким именем не найден! \nЗарегистрируйтесь.\n";
    }
};

class  WrongPassword : public exception
{
public:
    virtual const char* what() const noexcept override
    {
        return " Пользователь зарегистрирован с другим паролем!\n";
    }
};
class  NotAutorized : public exception
{
public:
    virtual const char* what() const noexcept override
    {
        return " Пользователь не авторизован!\n";
    }
};
class  NotAdmin : public exception
{
public:
    virtual const char* what() const noexcept override
    {
        return " Это действие доступно только администратору!\n";
    }
};
class  ALLisreserved : public exception
{
public:
    virtual const char* what() const noexcept override
    {
        return " Имя ALL зарезервировано для групповой рассылки!\n";
    }
};
class   MessNotSent : public exception
{
public:
    virtual const char* what() const noexcept override
    {
        return " Сообщение не отправлено!\n";
    }
};
