#include"String.h"




////////////////////////////////////////////////////////////////////////////////
////////////////  class defenition - ����������� ������ ////////////////////////

//:: - �������� ���������� ��������� (Scope operator)
int String::get_size()const
{
	return size;
}
const char* String::get_str()const
{
	return str;
}
char* String::get_str()
{
	return str;
}
//              Constructors:

String::String(int size) :size(size), str(new char[size] {})
{
	//this->size = size;
	//this->str = new char[size] {};
	cout << "Default1ArgConstructor:\t" << this << endl;
}
String::String(const char* str) :String(strlen(str) + 1)  //���������� ��������� ������ ������������ �� ���������
{
	//this->size = strlen(str) + 1;
	//this->str = new char[size] {};
	for (int i = 0; i < size; i++)this->str[i] = str[i];
	cout << "Constructor:\t\t" << this << endl;
}
String::String(const String& other) :String(other.str)
{
	//Deep copy (��������� �����������):
	//this->size = other.size;
	//this->str = new char[size] {};
	//for (int i = 0; i < size; i++)this->str[i] = other.str[i];
	cout << "CopyConstructor:\t" << this << endl;
}
String::String(String&& other) :size(other.size), str(other.str)
{
	//Shallow copy (������������� �����������):
	//this->size = other.size;
	//this->str = new char[size] {};
	other.size = 0;
	other.str = nullptr;
	cout << "CopyConstructor:\t" << this << endl;
}
String::~String()
{
	delete[] this->str;
	cout << "Destructor:\t\t" << this << endl;
}
//              Operators:
//type      name    (parameters)
String& String::operator=(const String& other)
{
	//Deep copy (��������� �����������):
	int a = 2;
	int b = 3;
	a = b;

	//0) ���������, �� �������� �� �������� �������� ����� ��������:
	if (this == &other)return *this;

	//1) ������� ������ ������:
	delete[] this->str;

	//2) ��������� ��������� �����������:
	this->size = other.size;
	this->str = new char[size] {};
	for (int i = 0; i < size; i++)this->str[i] = other.str[i];
	cout << "CopyAssignment:\t\t" << this << endl;
	return *this;
}
String& String::operator=(String&& other)
{
	if (this == &other)return *this;
	delete[] this->str;
	//Shallow copy (������������� �����������):
	this->size = other.size;
	this->str = other.str;
	other.size = 0;
	other.str = nullptr;
	cout << "MoveAssignment:\t\t" << this << endl;
}

//              Operators:
String& String::operator+=(const String& other)
{
	return *this = *this + other;
}

const char& String::operator[](int i)const
{
	return str[i];
}
char& String::operator[](int i)
{
	return str[i];
}

//              Methods:
void String::print()const
{
	cout << "Size:\t" << size << endl;
	cout << "Str:\t" << str << endl;
}

String operator+(const String& left, const String& right)
{
	String cat(left.get_size() + right.get_size() - 1);
	for (int i = 0; i < left.get_size(); i++)
		cat.get_str()[i] = left.get_str()[i];
	for (int i = 0; i < right.get_size(); i++)
		cat.get_str()[i + left.get_size() - 1] = right.get_str()[i];
	return cat;
}


std::ostream& operator<<(std::ostream& os, const String& obj)
{
	//os - Output Stream
	//obj - Object
	return os << obj.get_str();
}
std::istream& operator>>(std::istream& is, String& obj)
{
	//is - Input Stream
	const int SIZE = 102400;
	char buffer[SIZE]{};
	is >> buffer;
	obj = buffer;
	return is; // >> obj.get_str();
}

/////////////////////class defenition end - ����� ����������� ������ ///////////
////////////////////////////////////////////////////////////////////////////////