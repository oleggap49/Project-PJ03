#include "User.h"
#include <exception>
#include "MyExceptions.h"
string hor_line = "\n----------------------------------\n";
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
bool User::ShowUserList(XArray<User>& user_arr)

{
	int userN = user_arr.getLength();
	cout << "\n----------------------------------\n"
		<< "� ���� " << userN << " ����������:" << endl;
	for (int i{ 0 }; i < userN; ++i)
		cout << i + 1 << " : " << user_arr[i].getNickname() << endl;

	return true;
}
//��������� ������ �� Nick � ���������� ������������� user_arr
// ��� �������� ������ ������������� ������������� ���������� ������������ user_id � ���������� true
// ���� �� ����� -���������� false
bool User::SearchNick(string Nick, XArray<User>& user_arr, int& user_id)
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
bool User::Registration(XArray<User>& user_arr, int& user_num)
{
	string Nick;
	string Pass;
	cout << " �����������" << endl;
	cout <<
		" ���������� ���:" << endl;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	getline(cin, Nick);
	try
	{
		if (Nick == "ALL") throw ALLisreserved(); //��� ALL ��������������� ��� ��������� ��������
		for (int i{ 0 }; i < user_arr.getLength(); ++i)
			if (user_arr[i].getNickname() == Nick)  throw UsernameExist();     // ��������, ���� ����� ������������

		cout <<
			" ���������� ������:" << endl;

		getline(cin, Pass);
		User user(Nick, Pass);         // �������� ������ ������������

		user_num++;

		user_arr.resize(user_num);
		user_arr[user_num - 1] = user; // ���������� ������ ������������ � ����������
		cout << "������������, " << user_arr[user_num - 1].getNickname() << "!\n"
			<< endl;
		return true;
	}
	catch (exception& e)
	{
		cout << e.what();
	}
}
bool User::Authorization(XArray<User>& user_arr, int& user_id)
{
	string Nick;
	string Pass;
	cout << " �����������" << endl;
	cout <<
		" ������� ���:" << endl;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	getline(cin, Nick);
	try
	{
		if (!this->SearchNick(Nick, user_arr, user_id)) 
			throw UsernameNotExist(); //��������, ��������������� �� ����� ������������

		cout <<
			" ������� ������:" << endl;
		getline(cin, Pass);
		if (user_arr[user_id].getPassword() == Pass) // �������� ������
		{
			user_arr[user_id].setAutorized(true);  //������� , ��� ������������ �����������
			cout << user_arr[user_id].getNickname() << ", �� ������� ������������!" << hor_line;
		}
		else  throw WrongPassword();
		return true;
	}
	catch (exception& e)
	{
		cout << e.what();
	}

}