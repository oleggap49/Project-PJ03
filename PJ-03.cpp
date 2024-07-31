// PJ-03.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include "User.h"
#include "XArray.h"
#include "Message.h"
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
class   MessNotSent: public exception
{
public:
    virtual const char* what() const noexcept override
    {
        return " Сообщение не отправлено!\n";
    }
};

using namespace std;
//процедура поиска по Nick в контейнере пользователей user_arr
// при успешном поиске устанавливает идентификатор найденного пользователя user_id и возвращает true
// если не нашла -возвращает false
bool SearchNick(string Nick, XArray<User>& user_arr, int& user_id)
{
    bool  Found = false;
    for (int i{ 0 }; i < user_arr.getLength(); ++i)
        if (user_arr[i].getNickname() == Nick)
        {
            user_id = i;
            Found = true;          
        }
    return Found;    
    }
//процедура создает новое сообщение и помещает его в контейнер непрочтенных сообщений
// в случае успеха - возвращает true
bool SendMessage(int user_id, int rec_id, string Text,int& mess_count, XArray<Message>& mes_arr)
{
    bool res = false;
    Message message(user_id, rec_id, Text);
 message.settime('s');
 mess_count++;
 mes_arr.resize(mess_count);
  mes_arr[mess_count - 1] = message; 
  res = true;
  return(res);
 }
 
int main()
{
    setlocale(LC_ALL, "");
    string hor_line = "\n----------------------------------\n";
    cout << "Добро пожаловать в чат!" << hor_line;
    char oper;
    int  user_num = 0;  // количество юзеров в чате
    int  user_id = 0;  // id текущего юзера
    string Nick = "admin";
    string Pass = "admin";
    User  auser(Nick, Pass,true);   // создали учетную запись администратора
     user_num++;
        XArray<User> user_arr(user_num); // создали контейнер для пользователей
        int mess_count = 1; // количество непрочтенных сообщений
        XArray<Message> mes_arr(mess_count); // создали контейнер для непрочтенных сообщений
        int  logm_count = 1;               // количество архивных сообщений
        XArray<Message> logm_arr(logm_count); // создали контейнер для архивных  сообщений
    user_arr[user_num - 1] = auser;         // первый пользователь  - админ
   do
    {
       cout <<
           " Bведите команду:" << endl;
       cin >> oper;
        switch (oper)
        {
        case 'r':
        {
            cout << " РЕГИСТРАЦИЯ" << endl;
            cout <<
                " Придумайте НИК:" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            getline(cin, Nick);
            try
            {
                if (Nick == "ALL") throw ALLisreserved(); //имя ALL зарезнрвировано для групповой рассылки
                for (int i{ 0 }; i < user_arr.getLength(); ++i)
                    if (user_arr[i].getNickname() == Nick)  throw UsernameExist();     // проверка, есть такой пользователь

                cout <<
                    " Придумайте Пароль:" << endl;

                getline(cin, Pass);

                User user(Nick, Pass);         // создание нового пользователя

                user_num++;
                  
                user_arr.resize(user_num);
                user_arr[user_num - 1] = user; // сохранение нового пользователя в контейнере
                cout << "Здравствуйте, " << user_arr[user_num - 1].getNickname() << "!\n"
                    << endl;
            }
            catch (exception& e)
            {
                cout << e.what();
            }
        }
        break;
        case 'a':
        {
            cout << " АВТОРИЗАЦИЯ" << endl;
            cout <<
                " Введите НИК:" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            getline(cin, Nick);
            try
            {
                if (!SearchNick(Nick, user_arr, user_id) )   throw UsernameNotExist(); //проверка, зарегистрирован ли такой пользователь
                 
                cout <<
                    " Введите пароль:" << endl;
                getline(cin, Pass);
                if (user_arr[user_id].getPassword() == Pass) // проверка пароля
                {
                    user_arr[user_id].setAutorized(true);  //признак , что пользователь авторизован
                    cout     << user_arr[user_id].getNickname()<<", вы успешно авторизованы!" << hor_line;
                }
                else  throw WrongPassword();
                for (int i{ 1 }; i < mes_arr.getLength(); ++i) //просматриваем непрочтенные сообщения
                                                               //начинаем с  1, 0-е сообщение не читается
                    if (mes_arr[i].getrecipient_id() == user_id) // проверяем, есть ли для этого пользователя непрочтенные сообщения
                    {
                        string ts = mes_arr[i].get_time('s');
                                                                                 //выводим на экран
                        cout << "Сообщение от "
                            << user_arr[mes_arr[i].getsender_id()].getNickname() //автор
                            << ":" << endl
                            << ts                                                //время создания 
                            << mes_arr[i].gettext() << endl;                     // текст
                        mes_arr[i].settime('r');           //установил время прочтения
                        mes_arr[i].setHasBeenRead(true);   // пометил прочтенным
                    }

                for (int i{ 1 }; i < mes_arr.getLength(); ++i)
                    if (mes_arr[i].getHasBeenRead() == true) //все прочтенные переносим в архив
                {
                        logm_count++;
                        logm_arr.resize(logm_count);
                        logm_arr[logm_count - 1] = mes_arr[i]; // добавил а архив
                        mes_arr.remove(i);   // убрал из непрочитанных
                        mess_count--;

                 }
            }
            catch (exception& e)
            {
                cout << e.what();
            }

        }
        break;
        case 'm':
        {
            try
            {
            if (user_arr[user_id].getAutorized()== false)  //проверка на авторизацию
                throw NotAutorized();
            cout << "СООБЩЕНИЕ: " << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string Text;
            getline(cin, Text);                             // ввод текста сообщения
            cout << " Кому:" << endl;
            getline(cin, Nick);
            
                int rec_id;
                  if (Nick == "ALL")             // рассылка всем зарегистрированным пользователям          
                {
                     for (int i{ 0 }; i < user_arr.getLength(); ++i)
                     {
                         rec_id = i;
                         if(user_id != rec_id)            // самому себе не посылаем
                        if( !SendMessage(user_id, rec_id, Text, mess_count, mes_arr)) // сообщение всем, кроме себя
                            throw MessNotSent(); // если SendMessage вернула false, аварийное сообщение - не отправлено
                     }
                }
                  else          // сообщение одному пользователю

                  {
                      if (!SearchNick(Nick, user_arr, rec_id))   throw UsernameNotExist(); //проверка, есть ли такой пользователь
                      if (!SendMessage(user_id, rec_id, Text, mess_count, mes_arr))
                          throw MessNotSent(); // если SendMessage вернула false, аварийное сообщение - не отправлено;
                  }
               
            }
            catch (exception& e)
            {
                cout << e.what();
            }

        } 
        break;
        case 'l':
        {
            try
            {
                if ( user_arr[user_id].getAdmin() == false)  // проверка прав администратора
                    throw NotAdmin();
                 
                for (int i{ 1}; i < logm_arr.getLength(); ++i)
                {
                    string ts = logm_arr[i].get_time('s');  // время создания
                    string tr = logm_arr[i].get_time('r');  // время прочгения
                    cout << " | " << i                    // номер записи
                        <<" | " << user_arr[logm_arr[i].getsender_id()].getNickname() // отправитель
                        << " -> " << user_arr[logm_arr[i].getrecipient_id()].getNickname() << endl //получатель 
                        << "написано | " << ts                               
                        << "прочитано | " << tr 
                        << " | " << logm_arr[i].gettext() << hor_line;  // текст сообщения
                }
            }
            catch (exception& e)
            {
                cout << e.what();
            }
        }
        break;
        case 'h':
        {
            cout <<
                " Допустимые команды:"
                << "'r'  - регистрирaция нового пользователя (имя ALL - зарезервировано)" << endl
                << " 'a' - авторизация" << endl
                << " 'q'   выйти из программы  " << endl
                << "'h' - получить помошь " << endl
                <<"Авторизированный пользователь может"<< endl
                <<"'m'- написать сообщение получателю, " << endl
                << "если в имени получателя ввести ALL - сообщение всем участникам чата. " << endl
                << " Администратор чата может дополнительно " << endl
                << "'l' - прочесть архив ." << endl
                ;
        }                                                                        
        break;
        
        case 'q':
        {
            break;
        }

        default:
        {
            cout << "Неверный оператор!" << endl
                << "'h' - получить помошь " << endl;
            break;
        }
       

        }

        cout << hor_line
            <<"В чате " << user_num   << " участников:" << endl;
        for (int i{ 0 }; i < user_arr.getLength(); ++i)
            cout << i+1 << " : " << user_arr[i].getNickname() <<endl;

   } while (oper != 'q');
    
    return 0;
}

