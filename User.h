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
private:
	
	string _nickname;
	string _password;
	bool _admin;
	bool _autorized;
};


