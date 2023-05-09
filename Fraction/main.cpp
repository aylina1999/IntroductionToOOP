#include<iostream>
using namespace std;

class Fraction;
Fraction operator*(Fraction left, Fraction right);
Fraction operator/(const Fraction& left, const Fraction& right);

class Fraction
{
	bool minus;
	int integer;       //целая часть
	int numerator;     //числитель
	int denominator;   //знаменатель
public:
	bool get_minus()
	{
		return minus;
	}
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
	Fraction& set_minus(bool minus)
	{
		this->minus = minus;
		return *this;
	}
	void set_integer(int integer)
	{
		this->integer = integer;
	}
	void set_numerator(int numerator)
	{
		this->numerator = numerator;
	}
	void set_denominator(int denominator)         //это знаменатель - делитель 
	{                                             //на 0 делить нельзя => нужна фильтрация данных
		if (denominator == 0)denominator = 1;
		this->denominator = denominator;
	}

	//             Constructors:
	Fraction()                                              //по умолчанию
	{
		this->integer = 0;
		this->numerator = 0;
		this->denominator = 1;
		cout << "DefaultConstructor:" << this << endl;
	}
	Fraction(int integer)                                  //с одним параметром
	{
		this->integer = integer;
		this->numerator = 0;
		this->denominator = 1;
		if (this->integer < 0)this->integer *= (-1);
		minus = true;
		cout << "1ArgConstructor:" << this << endl;
	}
	Fraction(int numerator, int denominator)                //с двумя параметрами
	{
		this->integer = 0;
		this->numerator = numerator;
		set_denominator(denominator);
		if (this->numerator < 0)this->numerator *= (-1);
		minus = true;
		cout << "Constructor:" << this << endl;
	}
	Fraction(int integer, int numerator, int denominator)   //один универсальный конструкстор с параметрами по умолчанию
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
		//метод inverted() обращает дробь:
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

	void print()const                               //выводит дроби на экран
	{
		if (minus)cout << "-";
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
	).to_proper().set_minus(left.get_minus()!=right.get_minus());
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

//#define CONSTRUCTORS_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef CONSTRUCTORS_CHECK
	Fraction A;                        //объект по умолчанию
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

}