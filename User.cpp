#include "User.h"


User::User(string nickname, string password) : 
	_nickname(nickname), _password(password), _admin(false),_autorized(false)
{}
User::User(string nickname, string password, bool admin) :
	_nickname(nickname), _password(password), _admin(admin), _autorized(false)
{}
	
User::~User() 
{

}
void  User:: setNickname(string nickname)
{
	_nickname = nickname;
}
string User:: getNickname() const
{
return _nickname;
}
void User:: setPassword(string password)
{
	_password = password;
}
string User:: getPassword() const
{
return _password;
}
void User::setAdmin(bool admin)
{
	_admin = admin;
}
bool User::getAdmin() { return _admin; }

void User:: setAutorized(bool autorized)
{
	_autorized = autorized;
}
bool User::getAutorized()
{
	return _autorized;
}