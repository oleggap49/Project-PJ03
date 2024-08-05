#pragma once
/////////////////////////////////////////////////////
// Класс сообщений                                //
////////////////////////////////////////////////////
#include <string>
#include <ctime>
#include "User.h"
class Message
{
private:
	int _sender_id;
	int _recipient_id;
	string _text;
	time_t _sent;
	time_t _read;
	bool _HasBeenRead;
public: 
	Message() = default;
	Message(int sender_id, int recipier_id, string text);
    ~Message();
	void setsender_id(int id);
	int getsender_id();
	void setrecipient_id(int id);
	int getrecipient_id();
	void settext(string text);
	string gettext();
	void settime(char pr);
	char* get_time(char pr);
	void setHasBeenRead(bool pr);
	bool getHasBeenRead();
	bool SendMessage(int& mess_count, XArray<Message>& mes_arr);
};

