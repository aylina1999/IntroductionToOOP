#include<iostream>
using namespace std;

class String;
String operator+(const String& left, const String& right);

#define delimiter "\n--------------------------------------------------------\n"

class String
{
	int size;            //размер строки в байтах
	char* str;           //адресс строки в динамической пам€ти
public:
	int get_size()const
	{
		return size;
	}
	const char* get_str()const
	{
		return str;
	}
	char* get_str()
	{
		return str;
	}
	//              Constructors:

	explicit String(int size = 256)
	{
		this->size = size;
		this->str = new char[size] {};
		cout << "Default1ArgConstructor:\t" << this << endl;
	}
	String(const char* str)
	{
		this->size = strlen(str) + 1;
		this->str = new char[size] {};
		for (int i = 0; i < size; i++)this->str[i] = str[i];
		cout << "Constructor:\t\t" << this << endl;
	}
	String(const String& other)
	{
		//Deep copy (побитовое копирование):
		this->size = other.size;
		this->str = new char[size] {};
		for (int i = 0; i < size; i++)this->str[i] = other.str[i];
		cout << "CopyConstructor:\t" << this << endl;
	}
	String(String&& other)
	{
		//Shallow copy (поверхностное копирование):
		this->size = other.size;
		this->str = new char[size] {};
		other.size = 0;
		other.str = nullptr;
		cout << "CopyConstructor:\t" << this << endl;
	}
	~String()
	{
		delete[] this->str;
		cout << "Destructor:\t\t" <<this << endl;
	}
	//              Operators:
	String& operator=(const String& other)
	{
		//Deep copy (побитовое копирование):
		int a = 2;
		int b = 3;
		a = b;

		//0) ѕровер€ем, не €вл€етс€ ли прин€тый параметр нашим объектом:
		if (this == &other)return *this;

		//1) ”дал€ем старую строку:
		delete[] this->str;

		//2) ¬ыполн€ем побитовое копирование:
		this->size = other.size;
		this->str = new char[size] {};
		for (int i = 0; i < size; i++)this->str[i] = other.str[i];
		cout << "CopyAssignment:\t\t" << this << endl;
		return *this;
	}
	String& operator=(String&& other)
	{
		if (this == &other)return *this;
		delete[] this->str;
		//Shallow copy (поверхностное копирование):
		this->size = other.size;
		this->str = other.str;
		other.size = 0;
		other.str = nullptr;
		cout << "MoveAssignment:\t\t" << this << endl;
	}

	//              Operators:
	String& operator+=(const String& other)
	{
		return *this = *this + other;
	}

	const char& operator[](int i)const
	{
		return str[i];
	}
	char& operator[](int i)
	{
		return str[i];
	}

	//              Methods:
	void print() const
	{
		cout << "Size:\t" << size << endl;
		cout << "Str:\t" << str << endl;
	}
};

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
	return os << obj.get_str();
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

//#define CONSTRUCTORS_CHECK
//#define HOME_WORK_1
//#define ISTREAM_OPERATOR


void main()
{
	setlocale(LC_ALL, "");

#ifdef CONSTRUCTORS_CHECK
	String str1;           //Default constructor
	str1.print();

	//Single-argiment constructor
	//String str2 = 16;      //explicit constructor невозможно вызвать оператором присвоить
	String str2(16);          //его можно вызвать только так
	str2.print();

	String str3 = "Hello";
	str3 = str3;
	str3.print();

	//String str4 = str3;      //Copy constructor
	String str4;
	str4 = str3;               //CopyAssignment
	str4.print();
#endif // CONSTRUCTORS_CHECK

#ifdef HOME_WORK_1
	String str1 = "Hello";
	String str2 = "World";
	//String str3 = str1 + " " + str2;   //Move constructor
	//String str3;
	//str3 = str1 + str2;                //Move assignment
	//cout << str1 << " + " << str2 << " = " << str3 << endl;
	str1 += str2;
	cout << delimiter << endl;
	cout << str1 << endl;
	cout << delimiter << endl;
#endif // HOME_WORK_1



#ifdef ISTREAM_OPERATOR
	String last_name;
	String first_name;
	//str.print();
	cout << "¬ведите ваше им€: ";

	cin >> last_name >> first_name;


	//str.print();
	cout << last_name << " " << first_name << endl;
#endif // ISTREAM_OPERATOR

}