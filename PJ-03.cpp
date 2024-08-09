// PJ-03.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include "User.h"
#include "XArray.h"
#include "Message.h"
#include <exception>
#include "MyExceptions.h"
 
using namespace std;

int main()
{
    setlocale(LC_ALL, "");
    string hor_line = "\n----------------------------------\n";
    cout << "Добро пожаловать в чат!" << hor_line;
    char oper;
    int  user_num = 1;  // количество юзеров в чате
    int  user_id = 0;  // id текущего юзера 
    int mess_count = 1; // количество непрочтенных сообщений
    int  logm_count = 1;   // количество архивных сообщений
    string Nick = "admin";
    string Pass = "admin";
    
    User  auser(Nick, Pass,true);   // создали учетную запись администратора
    Message amessage(0, 0, hor_line);
        XArray<User> user_arr(user_num); // создали контейнер для пользователей
       
        XArray<Message> mes_arr(mess_count); // создали контейнер для непрочтенных сообщений
                    
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
            auser.Registration(user_arr, user_num);
        }
        break;
        case 'a':
        {
            auser.Authorization(user_arr, user_id);
           
            
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
                         if (user_id != rec_id)            // самому себе не посылаем
                         {
                             Message message(user_id, rec_id, Text);
                             if (!message.SendMessage(mess_count, mes_arr)) // сообщение всем, кроме себя
                                 throw MessNotSent(); // если SendMessage вернула false, аварийное сообщение - не отправлено
                         }
                        
                     }
                }
                  else          // сообщение одному пользователю

                  {
                      if (!user_arr[user_id].SearchNick(Nick, user_arr, rec_id))   throw UsernameNotExist(); //проверка, есть ли такой пользователь
                      {
                          Message message(user_id, rec_id, Text);
                          if (!message.SendMessage(  mess_count, mes_arr))
                              throw MessNotSent(); // если SendMessage вернула false, аварийное сообщение - не отправлено;
                      }
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
         auser.ShowUserList(user_arr);
        
         
   } while (oper != 'q');
    
    return 0;
}

