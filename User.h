#pragma once
//////////////////////////////////////////////////////
// Класс пользовтелей чата                          //
//////////////////////////////////////////////////////
#include <string>
#include "XArray.h"
using namespace std;
class User
{
public:
	User() = default;
	User(string nickname, string password);
	User(string nickname, string password, bool admin);
	~User();
	void setNickname(string nickname);
	string getNickname() const;
	void setPassword(string password);
	string getPassword() const;
	void setAdmin(bool admin);
	bool getAdmin();
	void setAutorized(bool autorized);
	bool getAutorized();
	bool ShowUserList(XArray<User>& user_arr);
	bool SearchNick(string Nick, XArray<User>& user_arr, int& user_id);
	bool Registration(XArray<User>& user_arr, int &user_num);
	bool Authorization(XArray<User>& user_arr, int& user_id);
	
private:
	
	string _nickname;
	string _password;
	bool _admin;
	bool _autorized;
};


