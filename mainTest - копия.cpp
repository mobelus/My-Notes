	#include <iostream>
	
#if 0
	#include <iostream>
	struct My
	{
		My()		{ std::cout << "D"; }
		My(int i)	{ std::cout << "I"; }
		My(char c)  { std::cout << "C"; }
		My(long l)  { std::cout << "L"; }
		My(float f) { std::cout << "F"; }
		//My(double dd) { std::cout << "DD"; }
	};
	
	int main()
	{
		My m1('a');		// C
		My m2('a' + 1); // I
		My m3(1);	 // I
		My m4(0x01); // I
		My m5(0x0001L); // L
		My m6(1.0f);	// F
		//My m6(2.0f);	// F/DD (???)
		return 0;
	}
	#endif
	
	
	#if 0
	
	#include <iostream>
	struct A {
		A(int val) : m_val(val) {}
		int m_val;
	};
	
	struct B : A
	{
		B(int val) : A(val) {}
	};
	
	
	int main()
	{
		try
		{
			try
			{
				throw B(5);
			}
			catch (A a)
			{
				a.m_val *= 2;
				throw;
			}
			catch (B b)
			{
				b.m_val -= 2;
				throw b;
			}
		}
		catch (A a)
		{
			std::cout << a.m_val; // 5
		}
	
		return 0;
	}
	#endif
	
	
	#if 0 // answer
	#include <iostream>
	struct A {
		A(int val) : m_val(val)
		{
			int z = 0;
		}
		A(const A& _obj)
		{
			m_val = _obj.m_val;
		}
		int m_val;
	};
	
	struct B : A
	{
		B(int val) : A(val)
		{
			int z = 0;
		}
		B(const B& _obj) : A(_obj)
		{
			int z = 0;
		}
	};
	
	
	int main()
	{
		try
		{
			try
			{
				throw B(5);
			}
			//catch (A a) // передаётся копия "исходника"
			catch (A& a) // передаётся копия "исходника"
			{
				a.m_val *= 2; // операцию
				throw;	//  THROW ГЕНЕРИТ тсключение того типа, что он получил в рамках catch-а
						// Ссылку A& получил ... ссылку и пробросил далее ....
			}
			//catch (B b)
			catch (B& b)
			{
				b.m_val -= 2;
				throw b;
			}
		}
		catch (A a) // передача копии "исходника"
		{
			//std::cout << a.m_val; // БЕЗ СЫЛОК - 5
			std::cout << a.m_val; // С СЫЛКАМИ - 10
		}
	
		return 0;
	}
	#endif
	
	#if 0
	
	#include <iostream>
	int main()
	{
		try {
			throw std::string("4");
		}
		catch (std::string &s)
		{
			try {
				std::cout << s.c_str();
				throw 2;
			}
			catch (int i)
			{
				std::cout << i;
			}
			catch (...)
			{
				throw;
			}
	
			// БАНАЛЬНАЯ НЕВНИМАТЕЛЬНОСТЬ ПОСЛЕ catch мы ВОЗВРАЩАЕМСЯ И ПРОДОЛЖАЕМ 
			// выполенние кода после ВСЕХ catch-блоков !!!
			std::string str = s;
			std::cout << "s";
			std::cout << str.c_str();
		}
		catch (...)
		{
			std::cout << "all";
		}
	
		return 0;
	}
	
	#endif
	
	
	#if 0
	
	#include <iostream>
	int main()
	{
		try {
			throw std::string("4");
		}
		catch (std::string &s)
		{
			try {
				std::cout << s.c_str();
				throw 2;
			}
			catch (int i)
			{
				std::cout << i;
			}
			catch (...)
			{
				throw;
			}
	
			// БАНАЛЬНАЯ НЕВНИМАТЕЛЬНОСТЬ ПОСЛЕ catch мы ВОЗВРАЩАЕМСЯ И ПРОДОЛЖАЕМ 
			// выполенние кода после ВСЕХ catch-блоков !!!
			std::string str = s;
			std::cout << "s";
			std::cout << str.c_str();
		}
		catch (...)
		{
			std::cout << "all";
		}
	
		return 0;
	}
	
	#endif
	
	
	#if 0
	
	#include <iostream>
	void f()
	{
		int n = std::rand() % 3;
		if (n == 0)
			throw "0";
		if (n == 1)
			throw 1;
		if (n == 2)
			throw 2.2;
	}
	
	int main()
	{
		try {
			f();
		}
		//catch (...) // ERROR // CATCH_ALL - ДОЛЖЕН БЫТЬ В КОНЦЕ !!! ОШИБКА КОМПИЛЯЦИИ !!!!
		//{
		//	int z = 1;
		//}
		catch (int k)
		{
			int z = 2;
		}
		catch (const char* cp)
		{
			int z = 2;
		}
		catch (...) // 	catch (...) !!!! ВСЕГДА ДОЛЖЕН БЫТЬ ВКОНЦЕ !!!! И НИКОГДА ВЫШЕ КОНЦА !!!! 
		{
			int z = 1;
		}
	
		return 0;
	}
	
	#endif
	
	
	#if 0
	
	
	
	#endif
/*

	void __fastcall TFPredstStrach::sComboBox1Change(TObject *Sender)
{
if(sComboBox1->ItemIndex==-1) return;
int res;
TADOQuery *qw=m_api->dbGetCursor(res,"select * from vzr174Pr_predst_yur where id_predst_yur=" + IntToStr((int) sComboBox1->Items->Objects[sComboBox1->ItemIndex]));

sEdit6->Text=qw->FieldByName("dolgnost_yur")->AsString;
sEdit7->Text=qw->FieldByName("pred_yur_r_name")->AsString;
sEdit8->Text=qw->FieldByName("dolgnost_r_yur")->AsString;

sEdit4->Text=qw->FieldByName("doverennost_num_yur")->AsString;
sDateEdit2->Date=qw->FieldByName("doverennost_data_yur")->AsDateTime;
sEdit5->Text=qw->FieldByName("dogovor_num_yur")->AsString;
sDateEdit3->Date=qw->FieldByName("dogovor_data_yur")->AsDateTime;
CheckData();

}
*/


/*
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <iterator>
#include <sstream>
#include <map>

int main()
{
	std::ifstream ifs("1.txt");
	if (ifs)
	{
		std::string s(std::istreambuf_iterator<char>(ifs.rdbuf()), std::istreambuf_iterator<char>());
		for (std::string::iterator it = s.begin(); it != s.end(); ++it)
		{
			if (!isalpha(*it))
			{
				*it = ' ';
			}
			else if (isupper(*it))
			{
				*it = tolower(*it);
			}
		}
		std::map<std::string, std::size_t> map;
		std::istringstream iss(s);
		while (iss >> s)
		{
			++map[s];
		}
		for (std::map<std::string, std::size_t>::const_iterator it = map.begin(); it != map.end(); ++it)
		{
			std::cout << it->first << ' ' << it->second << std::endl;
		}
	}
	else
	{
		std::cerr << "File not found\n";
	}
	ifs.close();
	return 0;
}



	#include <cstdio>
	
	class A
	{
	public:
		virtual void print(int p = 1)
		{ printf("A %d\n", p); }
	};
	
	class B : public A
	{
	public:
		virtual void print(int p = 30)
		{ printf("B %d\n", p); }
	};
	
	
	int main()
	{	
		A* a = new A();
		a->print(); //Используется параметр по-умолчанию класса А, т.е. 1
		A* b = new B();
		b->print(); //Кажется, что используется параметр по-умолчанию класса B, т.е. 30
	
		return 0;
	}


	#include <cassert>
	#include <iostream>
	
	class Fraction
	{
	private:
		int m_numerator;
		int m_denominator;
	
	public:
		// Default constructor
		Fraction(int numerator = 0, int denominator = 1) :
			m_numerator(numerator), m_denominator(denominator)
		{
			assert(denominator != 0);
		}
	
		// Copy constructor
		Fraction(const Fraction &f) :
			m_numerator(f.m_numerator), m_denominator(f.m_denominator)
		{
		}
	
		Fraction& Fraction::operator= (const Fraction &fraction);
	
		friend std::ostream& operator<<(std::ostream& out, const Fraction &f1);
	};
	
	std::ostream& operator<<(std::ostream& out, const Fraction &f1)
	{
		out << f1.m_numerator << "/" << f1.m_denominator;
		return out;
	}
	
	// A better implementation of operator=
	Fraction& Fraction::operator= (const Fraction &fraction)
	{
		// self-assignment guard
		if (this == &fraction)
			return *this;
	
		// do the copy
		m_numerator = fraction.m_numerator;
		m_denominator = fraction.m_denominator;
	
		// return the existing object so we can chain this operator
		return *this;
	}
*/



/*
#include <ctime>
#include <iostream>
#include <string>

void foo(std::string s)
{
	std::string str = s;
}
void bar(const std::string& s)
{
	std::string str = s;
}

int main()
{
	//const std::string s("test string");
	std::string s("test string");

	clock_t start = clock();
	for (int it = 0; it < 1000000; ++it)
		foo(s);
	std::cout << "foo took " << (clock() - start) << " cycles" << std::endl;

	start = clock();
	for (int it = 0; it < 1000000; ++it)
		bar(s);
	std::cout << "bar took " << (clock() - start) << " cycles" << std::endl;
}
*/


/*
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <iterator>
#include <sstream>
#include <map>

void readFile(std::string fileName, std::map<std::string, std::size_t>& mmap)
{
	std::ifstream file;
	file.open(fileName);
	std::string word;
	char x;
	word.clear();

	while (!file.eof())
	{
		x = file.get();
		while (x != ' ')
		{
			word = word + x;
			x = file.get();
		}

		std::cout << word << std::endl;
		word.clear();
	}
}


void writeFile(std::string fileName, std::map<std::string, std::size_t>& mmap)
{
	std::ifstream file;
	file.open(fileName);
	std::string word;
	char x;
	word.clear();

	while (!file.eof())
	{
		x = file.get();
		while (x != ' ')
		{
			word = word + x;
			x = file.get();
		}

		std::cout << word << std::endl;
		word.clear();
	}
}

void main()
{

	std::map<std::string, std::size_t> mapWords;
	std::string readFileName =  "readFrom.txt";
	std::string writeFileName = "writeInto.txt";

	readFile(readFileName, mapWords);
	writeFile(writeFileName, mapWords);
	//return 0;
}

//*/

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <iterator>
#include <sstream>
#include <vector>
#include <map>


void readFile(std::string _fileName, std::map<std::string, std::size_t>& _mmap)
{
	std::ifstream file;
	file.open(_fileName);
	std::string word;
	char x;
	word.clear();

	while (!file.eof())
	{
		x = file.get();
		while (x != ' ')
		{
			word += x;
			x = file.get();
		}

		std::cout << word << std::endl;
		word.clear();
	}
}


void readFile(std::string _fileName, std::vector<std::string>& _vec)
{
	std::ifstream file;
	file.open(_fileName);
	std::string word;
	char x;
	word.clear();

	while (!file.eof())
	{
		x = file.get();
		while (x != ' ')
		{
			word += x;
			x = file.get();
		}

		std::cout << word << std::endl;
		word.clear();
	}
}


void writeFile(std::string _fileName, std::map<std::string, std::size_t>& _map)
{
	std::ifstream file;
	file.open(_fileName);
	std::string word;
	char x;
	word.clear();

	while (!file.eof())
	{
		x = file.get();
		while (x != ' ')
		{
			word = word + x;
			x = file.get();
		}

		std::cout << word << std::endl;
		word.clear();
	}
}

//void mergeFiles(std::string _fileName, std::map<std::string, std::size_t>& _mmap)
void mergeFiles(std::string _fileName, std::map<std::string, std::size_t>& _mmap)
{
	std::map<std::string, std::size_t> mapRes;

}

void main()
{
	std::vector<std::string> vecMas_1, vecMas_2;
	std::string readFirstFileName	= "numMas_1.txt";
	std::string readSecondFileName	= "numMas_2.txt";
	std::string writeFileName		= "resMass.txt";

	readFile(readFirstFileName,	vecMas_1);
	readFile(readSecondFileName,vecMas_2);
	mergeFiles(writeFileName, vecMas_1, vecMas_2);
	//writeFile(writeFileName, mapWords);
	//return 0;
}


