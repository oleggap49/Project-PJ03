#include "Message.h"
#include <iostream>
#include <chrono>
#include <ctime>
using namespace std;
using namespace chrono;
 
Message:: Message(int sender_id, int recipient_id, string text):
    _sender_id(sender_id), _recipient_id(recipient_id), _text(text),
    _sent(time(nullptr)), _read(time(nullptr)),   _HasBeenRead(false)
{}
Message::~Message()
{}
void Message::setsender_id(int id) { _sender_id = id; }
int Message::getsender_id() { return _sender_id; }
void Message::setrecipient_id(int id) { _recipient_id = id; }
int Message::getrecipient_id() { return _recipient_id; }
void Message::settext(string text) { _text = text; }
string Message::gettext() { return _text; }
void Message::settime(char pr)
{
    time_t t;
    time(&t);
   (pr == 's') ? _sent = t : _read = t;
}

char*  Message::get_time(char pr)
{
    const int SIZE = 80;
    char str[SIZE] = { 0 };
     time_t t = (pr == 's') ?  _sent :  _read; // если признак 's' - установить время посылки
                                               // иначе - время прочтения сообщения
    errno_t err = ctime_s(str, SIZE, &t);
    if (err) {
        std::cout << "Ошибка! Неверное время." << std::endl;
        exit(1);
    }
    return (str);
}
void Message::setHasBeenRead(bool pr)
{
    _HasBeenRead = pr;
}
bool Message::getHasBeenRead()
{
    return (_HasBeenRead);
}
bool Message::SendMessage(int& mess_count, XArray<Message>& mes_arr)
{
    bool res = false;
    this->settime('s');
    mess_count++;
    mes_arr.resize(mess_count);
    mes_arr[mess_count - 1] = *this;
    res = true;
    return(res);
}
void Message::CheckMessage(XArray<Message>& mes_arr, int user_id, string sender)
{
    for (int i{ 1 }; i < mes_arr.getLength(); ++i) //просматриваем непрочтенные сообщения
        //начинаем с  1, 0-е сообщение не читается
        if (mes_arr[i].getrecipient_id() == user_id) // проверяем, есть ли для этого пользователя непрочтенные сообщения
        {
            string ts = mes_arr[i].get_time('s');
            //выводим на экран
            cout << "Сообщение от "
                << sender                                     //автор
                << ":" << endl
                << ts                                                //время создания 
                << mes_arr[i].gettext() << endl;                     // текст
            mes_arr[i].settime('r');           //установил время прочтения
            mes_arr[i].setHasBeenRead(true);   // пометил прочтенным
        }
}
    
 