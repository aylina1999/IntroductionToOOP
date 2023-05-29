#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

class Fraction;
Fraction operator*(Fraction left, Fraction right);
Fraction operator/(const Fraction& left, const Fraction& right);

class Fraction
{
	int integer;       //����� �����
	int numerator;     //���������
	int denominator;   //�����������
public:
	int get_integer()const
	{
		return integer;
	}
	int get_numerator()const
	{
		return numerator;
	}
	int get_denominator()const
	{
		return denominator;
	}
	void set_integer(int integer)
	{
		this->integer = integer;
	}
	void set_numerator(int numerator)
	{
		this->numerator = numerator;
	}
	void set_denominator(int denominator)         //��� ����������� - �������� 
	{                                             //�� 0 ������ ������ => ����� ���������� ������
		if (denominator == 0)denominator = 1;
		this->denominator = denominator;
	}

	//             Constructors:
	Fraction()                                              //�� ���������
	{
		this->integer = 0;
		this->numerator = 0;
		this->denominator = 1;
		cout << "DefaultConstructor:" << this << endl;
	}
	explicit Fraction(int integer)                                  //� ����� ����������
	{
		this->integer = integer;
		this->numerator = 0;
		this->denominator = 1;
		cout << "1ArgConstructor:" << this << endl;
	}
	Fraction(double decimal)
	{
		//decimal - ���������� �����
		decimal += 0.0000000001;
		integer = decimal;    //�������� ����� ����� �������� �����
		decimal -= integer;   //������� ����� ����� �� �������� �����
		denominator = 1000000000;
		numerator = decimal * denominator;
		reduce();
		cout << "1DArgConstructor:\t" << this << endl;
	}

	Fraction(int numerator, int denominator)                //� ����� �����������
	{
		this->integer = 0;
		this->numerator = numerator;
		set_denominator(denominator);
		cout << "Constructor:" << this << endl;
	}
	Fraction(int integer, int numerator, int denominator)   //���� ������������� ������������ � ����������� �� ���������
	{
		this->integer = integer;
		this->numerator = numerator;
		this->set_denominator(denominator);
		cout << "Constructor:" << this << endl;
		
	}
	Fraction(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyConstructor:" << this << endl;
	}
	~Fraction()
	{
		cout << "Destructor:\t\t" << this << endl;
	}

	//              Operator:
	
	Fraction& operator=(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyAssignment:\t\t" << this << endl;
		return *this;
	}
	Fraction& operator*=(const Fraction& other)
	{
		/*int a = 2;
		int b = 3;
		a = a * b;*/

		return *this = *this * other;
	}
	Fraction& operator/=(const Fraction& other)
	{
		return *this = *this / other;
	}

	//             Increment/Decrement:
	Fraction& operator++()     //Prefix increment
	{
		integer++;
		return *this;
	}
	Fraction operator++(int)   //Postfix increment
	{
		Fraction old = *this;
		integer++;
		return old;
	}
	
	Fraction& operator--()     //Prefix Decrement
	{
		integer--;
		return *this;
	}
	Fraction operator--(int)   //Postfix Decrement
	{
		Fraction old = *this;
		integer--;
		return old;
	}

	//             Type-cast operators:
	explicit operator int()
	{
		return integer;
	}
	operator double()
	{
		return integer + (double)numerator / denominator;
	}

	//             Methods:
	Fraction& to_improper()
	{
		numerator += integer * denominator;
		integer = 0;
		return *this;
	}
	Fraction& to_proper()
	{
		integer += numerator / denominator;
		numerator %= denominator;
		return *this;
	}

	Fraction inverted()const
	{
		//����� inverted() �������� �����:
		Fraction inverted = *this;
		inverted.to_improper();
		inverted.numerator ^= inverted.denominator;
		inverted.denominator ^= inverted.numerator;
		inverted.numerator ^= inverted.denominator;
		return inverted;
	}

	Fraction& reduce()
	{
		to_proper();
		int more, less, rest;
		if (numerator > denominator)more = numerator, less = denominator;
		else more = denominator,	less = numerator;
		do
		{
			rest = more % less;
			more = less;
			less = rest;
		} while (rest);
		int GCD = more;     //GCD - Greatest Common Divisor; 
		numerator /= GCD;
		denominator /= GCD;
		return* this;
	}

	void print()const                               //������� ����� �� �����
	{
		if (integer)cout << integer;
		if (numerator)
		{
			if (integer)cout << "(";
			cout << numerator << "/" << denominator;
			if (integer)cout << ")";
		}
		else if (integer == 0)cout << 0;
		cout << endl;
	}
};

Fraction operator*( Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	/*Fraction product;
	product.set_numerator(left.get_numerator() * right.get_numerator());
	product.set_denominator(left.get_denominator() * right.get_denominator());*/

	/*Fraction product
	(
		left.get_numerator() * right.get_numerator(),
		left.get_denominator() * right.get_denominator()
	);
	product.to_proper();
	return product;*/

	return Fraction
	(
		left.get_numerator() * right.get_numerator(),
		left.get_denominator() * right.get_denominator()
	).to_proper().reduce();
}

Fraction operator/(const Fraction& left, const Fraction& right)
{
	/*left.to_improper();
	right.to_improper();
	return Fraction
	(
		left.get_numerator() * right.get_denominator(),
		right.get_numerator() * left.get_numerator()
	).to_proper();*/
	return left * right.inverted();
}

bool operator==(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return left.get_numerator() * right.get_denominator() == right.get_numerator() * left.get_denominator();
	/*
	if (left.get_numerator() * right.get_denominator() == right.get_numerator() * left.get_denominator())
		return true;
	else
		return false;*/
}
bool operator!=(const Fraction& left, const Fraction& right)
{
	return !(left == right);
}
bool operator>(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return left.get_numerator() * right.get_denominator() > right.get_numerator() * left.get_denominator();

}
bool operator<(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return left.get_numerator() * right.get_denominator() < right.get_numerator() * left.get_denominator();

}
bool operator>=(const Fraction& left, const Fraction& right)
{
	return !(left < right);
	//return left > right || left == right;
}
bool operator<=(const Fraction& left, const Fraction& right)
{
	return left < right || left == right;
}

Fraction operator-(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return Fraction
	(
		left.get_numerator() * right.get_denominator() - right.get_numerator() * left.get_denominator(),
		left.get_denominator() * right.get_denominator()
	).to_proper();
}
std::ostream& operator << (std::ostream& os, const Fraction& obj)
{
	if (obj.get_integer())os << obj.get_integer();
	if (obj.get_numerator())
	{
		if (obj.get_integer())os << "(";
		os << obj.get_numerator() << "/" << obj.get_denominator();
		if (obj.get_integer())os << ")";
	}
	else if (obj.get_integer() == 0)os << 0;
	return os;
}
std::istream& operator>>(std::istream& is, Fraction& obj)
{
	const int SIZE = 256;
	char buffer[SIZE] = {};
	//is >> buffer;
	is.getline(buffer, SIZE);
	int number[3] = {};  //����� ����� �������� �����, �������� � ����������
	int n = 0; //������� �����
	const char delimiters[] = "( /)";
	for (char* pch = strtok(buffer, delimiters); pch; pch = strtok(NULL, delimiters))
	{
		//��������� 'pch' ������ ����� ������ ������
		//� ������� strtok() ������ ������ ��� ��������� ������� ������, ��� ���� ����������� ������� �� ����� ������� ������ ����� ���������� 'NULL'
		//��� ��������� ������� strtok() ��� ��� �������� � ����� ���������� �������
		//���� ������� ������ �������� ��� ���, �� strtok() ����� ������������ � �������
		number[n++] = atoi(pch);
		//atoi() - SACII-string To Integer (��� ������� ����������� �-������ � �������� ���� 'int')
	}
	//for (int i = 0; i < n; i++)cout << number[i] << "\t"; cout << endl;
	obj = Fraction();
	switch (n)
	{
	case 1: obj.set_integer(number[0]); break;
	case 2: obj.set_numerator(number[0]); obj.set_denominator(number[1]); break;
	case 3: obj.set_integer(number[0]); obj.set_numerator(number[1]); obj.set_denominator(number[2]); break;
	}
	return is;
}

//#define CONSTRUCTORS_CHECK
//#define ARITHMETICAL_OPERATORS_CHECK
//#define ISTREAM_OPERATOR_CHECK
//#define CONVERSION_FROM_OTHER_TO_CLASS
//#define CONVERSION_FROM_CLASS_TO_OTHER
#define HOME_WORK

void main()
{
	setlocale(LC_ALL, "");

#ifdef CONSTRUCTORS_CHECK
	Fraction A;                        //������ �� ���������
	A.print();

	Fraction B = 3;
	B.print();

	Fraction C(1, 2);
	C.print();

	Fraction D(2, 3, 4);
	D.print();

	Fraction E = D;
	E.print();

	A = E;
	A.print();
#endif // CONSTRUCTORS_CHECK

#ifdef ARITHMETICAL_OPERATORS_CHECK
	Fraction A(2, 3, 4);
	A.print();

	Fraction B(3, 4, 5);
	B.print();

	/*double a = 2.5;
	double b = 3.14;
	double c = a * b;

	Fraction C = A * B;
	C.print();

	Fraction D = A / B;
	D.print();

	A.print();
	B.print();*/

	A *= B;
	A.print();

	A /= B;
	A.print();

	(A - B).print();

	for (double i = .75; i < 10; i++)
	{
		cout << i << "\t";
	}
	cout << endl;
	for (Fraction i(3, 4); i.get_integer() < 10; i++)
	{
		i.print();
	}

	for (double i = .75; i > 10; i--)
	{
		cout << i << "\t";
	}
	cout << endl;
	for (Fraction i(3, 4); i.get_integer() > 10; i--)
	{
		i.print();
	}
#endif // ARITHMETICAL_OPERATORS_CHECK

#ifdef ISTREAM_OPERATOR_CHECK
	/*cout << (Fraction(1, 2) == Fraction(5, 10)) << endl;
cout << (Fraction(1, 2)!= Fraction(5, 10)) << endl;
cout << (Fraction(1, 2)> Fraction(5, 10)) << endl;
cout << (Fraction(1, 2)< Fraction(5, 10)) << endl;
cout << (Fraction(1, 2) >= Fraction(5, 10)) << endl;
cout << (Fraction(1, 2) <= Fraction(5, 10)) << endl;*/
//Fraction A(2, 3, 4);
	Fraction A;
	cout << "������� ������� �����: "; cin >> A;

	/*cout << A << endl;
	A.to_improper();*/

	cout << A << endl;
#endif // ISTREAM_OPERATOR_CHECK

#ifdef CONVERSION_FROM_OTHER_TO_CLASS
	Fraction A = (Fraction)5;
	cout << A << endl;
	Fraction B;
	B = Fraction(8);
	cout << B << endl;
#endif // CONVERSION_FROM_OTHER_TO_CLASS

#ifdef CONVERSION_FROM_CLASS_TO_OTHER
	Fraction A(2, 3, 4);
	cout << A << endl;

	int a = (int)A;
	cout << a << endl;

	double b = A;
	cout << b << endl;
#endif // CONVERSION_FROM_CLASS_TO_OTHER

#ifdef HOME_WORK
	Fraction A = 2.75;
	cout << A << endl;
#endif // HOME_WORK

} 