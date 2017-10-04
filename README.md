
ГИТ: СТРАТЕГИИ СЛИЯНИЯ

https://habrahabr.ru/post/195674/

https://webhamster.ru/mytetrashare/index/mtb0/1403174393wno3ejl1g3


МНОГОПОТОЧНОСТЬ В С++11:

https://habrahabr.ru/post/182610/






Все, что вы хотели знать о сексе, но боялись спросить

http://gidonline.club/2016/02/vse-chto-vy-xoteli-znat-o-sekse-no-boyalis-sprosit/


Алан Пол - ОБЪЕКТНО-ОРИЕНТИРОВАННОЕ ПРОГРАММИРОВАНИЕ НА C++ 
  
http://fis.tntu.edu.ua/data/elibrary/3/oop_cpp.pdf


  С++ библиотеки ВСЕХ мастей и на ВСЕ случаи жизни
  
https://github.com/fffaraz/awesome-cpp#bittorrent


  Е. В. Пышкин - Структуры данных и алгоритмы: реализация на С/С++
  
http://kspt.icc.spbstu.ru/media/files/people/pyshkin/books/AlgDataStrA5_2009.pdf



# My-Notes
My first Project on Github


Простой нагрузочный тест с Apache JMeter / Хабрахабр


	Object()
	{}

#include <cstring>
#include <iostream>

class Object
{
public:
	char  mas[32];
	char* arr;

	Object()
	{}

	~Object()
	{if(arr) delete arr;}

	void operator=(const Object& _obj)
	{
		//memcpy(this, _obj, sizeof(_obj));

		//this->mas = _obj.mas; // must be a modified lvalue
		memcpy(this->mas, _obj.mas, sizeof(_obj.mas)); // must be a modified lvalue
		if (_obj.arr)
		{ this->arr = _obj.arr;} // Два объекта будут указывать на одну и ту же память
		//когда вызовется  delete()  то 
	}

};

}

	void operator=(const Object& _obj)
	{
		//memcpy(this, _obj, sizeof(_obj));

		//this->mas = _obj.mas; // must be a modified lvalue
		memcpy(this->mas, _obj.mas, sizeof(_obj.mas)); // must be a modified lvalue
		if (_obj.arr)
		{ this->arr = _obj.arr;} // Два объекта будут указывать на одну и ту же память
		//когда вызовется  delete()  то 
	}

{
/*
	Мои фейлы:
	1) 
	arr[100];
	ar[100];
	ar = arr; // ТАК НЕЛЬЗЯ !!
	memcpy(ar, arr);

	2) есть 
	char* a;

	a = b; // НЕЛЬЗЯ
	и a и b будут казывать на одну и ту же память.
	и после если будет
	delete a;
	то и b будет невалидным указателем, как и а !!!
	
	

*/
}




https://stackoverflow.com/questions/39383936/correctly-overload-assignment-operator-for-classes-with-pointer-members

{

class Array
{

private:
    int size;    //array elements
    int *arr;    //dynamic array pointer

public:
    Array(int N)
    {
         size = N;
         arr = new int[N];
    }
   
    ~Array()  //destructor
    {
        delete[] arr;
    }
    
    Array(const Array& arr2) //copy constructor
    {
        size = arr2.size;
        arr = new int[size];
        std::memcpy(arr, arr2.arr, size);
    }
    
    Array& operator=(const Array& arr2) //overload = operator
    {
        if (this == &arr2)
            return *this; //self assignment
        if (arr != NULL)
            delete[] arr; //clean up already allocated memory

        size = arr2.size;
        arr = new int[size];
        std::memcpy(arr, arr2.arr, size);
        return *this;
    }
    
};

}











Hallo
Main Name ist Paul Winterberg
Ich komme u
Bin Programmierer von Beruf
Arbeite hier in Moskau fur Siemens
in einer von der Siemens Tochter Firmen

Und hier kommt Deutsch Aktiv ins Spiel
Kollegen von De




Я проверяи Инстаграмм и твиттор Кетики каждый день
ЧТО ЭТО ... Твитнула фоточку ???????!!!!!!!
ТЭК КЭТ БЛЭТ

Где мои плюхи Я вас спрашиваю
Почему я вынужден ждать их по пол года,
ежедневно пересматривать свои сообщения в Вк, Скайпе и Телеграмме,
чтобы узнать, что очередной дедлайн просран
Я бы и заказал плюхи у других поставщиков,
Но они либо заняти пилением своего канала и
не годных плюх, а годного контента на Ютубе...
НЭГОДНЫЕ ПЛЬЮХИ
Либо подсовывают мне ширпотеп от Хасбро, под видом собственного изделия
А некоторые так вообще просят меня приехать к лавочке в тёмном переулке, и крепят плюхи на магнитик в самые неочевидные места, чтобы 

УралПлюхЗавод имени Кетики так ещё и не открыли, чтобы удовлетворить массового потрелителя
Остаётся довольствоваться продукцией Хасбро или поделками других Плюходелов... и их подмастерьев


Ведь если не полюхи, то какие альтенрнативы ...
Докимакуры
Плюшевые Докимакура

ЧТО мне делать.... !!!!!!!!!!!!!!!!!!!!!!!!! ??????
Распечатывать плюхи на 3Д принтере
Покупать игрушки от Бэддрегона
Покупать игрушки от Хасбро ....






Секс - словот-то какое заморское
ЧТобы это выяснить обратимся к тем кто ведает
и НЕТ не к вкипедии, ибо она женщина, нам же нужны реальные Эксперты
Гугл, берём выше, Вассерман, надо бы ещё выше - Патриарх Кирил




