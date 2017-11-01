

https://habrahabr.ru/post/182920/


# Десять возможностей C++11, которые должен использовать каждый C++ разработчик 

В данной статье рассматривается ряд возможностей С++11, которые все разработчики должны знать и использовать. Существует много новых дополнений к языку и стандартной библиотеке, эта статья лишь поверхностно охватывает часть из них. Однако, я полагаю, что некоторые из этих новых функций должны стать обыденными для всех разработчиков С++. Подобных статей наверное существует много, в этой я предприму попытку составить список возможностей, которые должны войти в повседневное использование.

Сегодня в программе: 
- auto
- nullptr
- range-based циклы
- override и final
- строго-типизированный enum
- интеллектуальные указатели
- лямбды
- non-member begin() и end()
- static_assert и классы свойств
- семантика перемещения


# 1 — auto

До С++11, ключевое слово auto использовалось как спецификатор хранения переменной (как, например, register, static, extern). В С++11 auto позволяет не указывать тип переменной явно, говоря компилятору, чтобы он сам определил фактический тип переменной, на основе типа инициализируемого значения. Это может использоваться при объявлении переменных в различных областях видимости, как, например, пространство имен, блоки, инициализация в цикле и т.п. 
auto i = 42;        // i - int
auto l = 42LL;      // l - long long
auto p = new foo(); // p - foo*


Использование auto позволяет сократить код (если, конечно, тип не int, который на одну букву меньше). Подумайте об итераторах STL, которые вы должны были всегда писать для прохода контейнеров. Таким образом, это делает устаревшим определение typedef только ради простоты.
	std::map<std::string, std::vector<int>> map;
	for(auto it = begin(map); it != end(map); ++it) 
	{
   	// do smth
	}

	// Или, сравним С++03 и С++11
	// C++03
	for (std::vector<std::map<int, std::string>>::const_iterator it = container.begin(); it != container.end(); ++it)
	{
	   // do smth
	}
	// C++11
	for (auto it = container.begin(); it != container.end(); ++it)
	{
	   // do smth
	}


Стоить отметить, что возвращаемое значение не может быть auto. Однако, вы можете использовать auto вместо типа возвращаемого значения функции. В таком случае, auto не говорит компилятору, что он должен определить тип, он только дает ему команду искать возвращаемый тип в конце функции. В примере ниже, возвращаемый тип функции compose — это возвращаемый тип оператора +, который суммирует значения типа T и E.
	template <typename T, typename E>
	auto compose(T a, E b) -> decltype(a+b) // decltype - позволяет определить тип на основе входного параметра
	{
	   return a+b;
	}
	auto c = compose(2, 3.14); // c - double




# 2 — nullptr

Раньше, для обнуления указателей использовался макрос NULL, являющийся нулем — целым типом, что, естественно, вызывало проблемы (например, при перегрузке функций). Ключевое слово nullptr имеет свой собственный тип std::nullptr_t, что избавляет нас от бывших проблем. Существуют неявные преобразования nullptr к нулевому указателю любого типа и к bool (как false), но преобразования к целочисленных типам нет.

	void foo(int* p) {}

	void bar(std::shared_ptr<int> p) {}

	int* p1 = NULL;
	int* p2 = nullptr;   

	if(p1 == p2)
	{}

	foo(nullptr);
	bar(nullptr);

	bool f = nullptr;
	int i = nullptr; // ошибка: для преобразования в int надо использовать reinterpret_cast



# 3 — range-based циклы

 В С++11 была добавлена поддержка парадигмы foreach для итерации по набору. В новой форме возможно выполнять итерации в случае, если для объекта итерации перегружены методы begin() и end(). 

Это полезно, когда вы просто хотите получить элементы массива/контейнера или сделать с ними что-то, не заботясь об индексах, итераторах или кол-ве элементов.

	std::map<std::string, std::vector<int>> map;
	std::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	map["one"] = v;

	for(const auto &kvp: map) 
	{
	   std::cout << kvp.first << std::endl;
	   for(auto v: kvp.second)
	      std::cout << v << std::endl;
	}

	int arr[] = {1,2,3,4,5};

	for(int &e: arr) 
	   e *= e;



# 4 — override и final

Мне всегда не нравились виртуальные функции в С++. Ключевое слово virtual опционально и поэтому немного затрудняло чтение кода, заставляя вечно возвращаться в вершину иерархии наследования, чтобы посмотреть объявлен ли виртуальным тот или иной метод. Я всегда использовал этой ключевое слово так же и в производных классах (и поощрял людей, кто так делал), чтобы код был понятнее. Тем не менее, есть ошибки, которые могут все таки возникнуть. Возьмем следующий пример:

	class B 
	{
	public:
	   virtual void f(short) {std::cout << "B::f" << std::endl;}
	};

	class D : public B
	{
	public:
	   virtual void f(int) {std::cout << "D::f" << std::endl;}
	};


D::f переопределяет B::f. Однако они имеют разную сигнатуру, один метод принимает short, другой — int, поэтому B::f — это просто другой метод с тем же именем, перегруженный, а не переопределенный. Таким образом, работая через указатель на базовый класс, Вы можете вызвать f() и ожидать вывода «переопределенного» вами метода: «D::f», однако вывод будет «B::f». 

Вот другая возможная ошибка: параметры одни и те же, но в базовом классе метод константный, а в производном — нет.

	class B 
	{
	public:
	   virtual void f(int) const {std::cout << "B::f " << std::endl;}
	};

	class D : public B
	{
	public:
	   virtual void f(int) {std::cout << "D::f" << std::endl;}
	};


И снова это две перегруженные, а не переопределенные функции. 
К счастью, теперь есть способ избавиться от этих ошибок. Были добавлены два новых идентификатора (не ключевые слова): override, для указания того, что метод является переопределением виртуального метода в базовом классе и final, указывающий что производный класс не должен переопределять виртуальный метод. Первый пример теперь выглядит так:

	class B 
	{
	public:
	   virtual void f(short) {std::cout << "B::f" << std::endl;}
	};

	class D : public B
	{
	public:
	   virtual void f(int) override {std::cout << "D::f" << std::endl;}
	};


Теперь это вызовет ошибку при компиляции (точно так же, если бы вы использовали override во втором примере):
'D::f': method with override specifier 'override' did not override any base class methods


С другой стороны, если вы хотите сделать метод, не предназначенный для переопределения (ниже в иерархии), его следует отметить как final. В производном классе можно использовать сразу оба идентификатора.

	class B 
	{
	public:
	   virtual void f(int) {std::cout << "B::f" << std::endl;}
	};

	class D : public B
	{
	public:
	   virtual void f(int) override final {std::cout << "D::f" << std::endl;}
	};

	class F : public D
	{
	public:
	   virtual void f(int) override {std::cout << "F::f" << std::endl;}
	};


Функция, объявленная как final, не может быть переопределена функцией F::f() — в этом случае, она переопределяет метод базового класса (В) для класса D.


# 5 — строго-типизированный enum

У «традиционных» перечислений в С++ есть некоторые недостатки: они экспортируют свои значения в окружающую область видимости (что может привести к конфликту имен), они неявно преобразовываются в целый тип и не могут иметь определенный пользователем тип.

Эти проблемы устранены в С++11 с введением новой категории перечислений, названных strongly-typed enums. Они определяются ключевым словом enum class. Они больше не экспортируют свои перечисляемые значения в окружающую область видимости, больше не преобразуются неявно в целый тип и могут иметь определенный пользователем тип (эта опция так же добавлена и для «традиционных» перечислений").
enum class Options {None, One, All};
Options o = Options::All;




# 6 — интеллектуальные указатели 

 Есть много статей, как на хабре, так и на других ресурсах, написанных на эту тему, поэтому я просто хочу упомянуть об интеллектуальных указателях с подсчетом ссылок и автоматическим освобождением памяти:
- 1.unique_ptr: должен использоваться, когда ресурс памяти не должен был разделяемым (у него нет конструктора копирования), но он может быть передан другому unique_ptr
- 2.shared_ptr: должен использоваться, когда ресурс памяти должен быть разделяемым
- 3.weak_ptr: содержит ссылку на объект, которым управляет shared_ptr, но не осуществляет подсчет ссылок; позволяет избавиться от циклической зависимости

 Приведенный ниже пример демонстрирует unique_ptr. Для передачи владения объектом другому unique_ptr, используйте std::move (эта функция будет обсуждаться в последнем пункте). После передачи владения, интеллектуальный указатель, который передал владение, становится нулевым и get() вернет nullptr.
 
	void foo(int* p)
	{
	   std::cout << *p << std::endl;
	}
	std::unique_ptr<int> p1(new int(42));
	std::unique_ptr<int> p2 = std::move(p1); // transfer ownership

	if(p1)
	  foo(p1.get());

	(*p2)++;

	if(p2)
	  foo(p2.get());


Второй пример демонстрирует shared_ptr. Использование похоже, хотя семантика отличается, поскольку теперь владение совместно используемое.

	void foo(int* p)
	{
	}
	void bar(std::shared_ptr<int> p)
	{
	   ++(*p);
	}
	std::shared_ptr<int> p1(new int(42));
	std::shared_ptr<int> p2 = p1;
   
	bar(p1);   
	foo(p2.get());


Первое объявление эквивалентно следующему:
	auto p3 = std::make_shared<int>(42);


make_shared — это функция, имеющая преимущество при выделении памяти для совместно используемого объекта и интеллектуального указателя с единственным выделением, в отличие от явного получения shared_ptr через конструктор, где требуется, по крайней мере, два выделения. Из-за этого может произойти утечка памяти. В следующем примере как раз это демонстрируется, утечка может произойти в случае, если seed() бросит исключение.

	void foo(std::shared_ptr<int> p, int init)
	{
	   *p = init;
	}
	foo(std::shared_ptr<int>(new int(42)), seed());


Эта проблема решается использованием make_shared.
И, наконец, пример с weak_ptr. Заметьте, что вы должны получить shared_ptr для объекта, вызывая lock(), чтобы получить доступ к объекту. 

	auto p = std::make_shared<int>(42);
	std::weak_ptr<int> wp = p;
	
	{
	  auto sp = wp.lock();
	  std::cout << *sp << std::endl;
	}
	
	p.reset();
	
	if(wp.expired())
	  std::cout << "expired" << std::endl;



# 7 — лямбды

 В новом стандарте наконец-то была добавлена поддержка лямбда-выражений. Мы можете использовать лямбды везде, где ожидается функтор или std::function. Лямбда, вообще говоря, представляет собой более короткую запись функтора, что-то вроде анонимного функтора. Подробнее можно почитать, например, на MSDN.

	std::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	
	std::for_each(std::begin(v), std::end(v), [](int n) {std::cout << n << std::endl;});

	auto is_odd = [](int n) {return n%2==1;};
	auto pos = std::find_if(std::begin(v), std::end(v), is_odd);
	if(pos != std::end(v))
	  std::cout << *pos << std::endl;


Теперь немного более хитрые — рекурсивные лямбды. Представьте лямбду, представляющую функцию Фибоначчи. Если вы попытаетесь записать ее, используя auto, то получите ошибку компиляции:
auto fib = [&fib](int n) {return n < 2 ? 1 : fib(n-1) + fib(n-2);};


	error C3533: 'auto &': a parameter cannot have a type that contains 'auto'
	error C3531: 'fib': a symbol whose type contains 'auto' must have an initializer
	error C3536: 'fib': cannot be used before it is initialized
	error C2064: term does not evaluate to a function taking 1 arguments


Здесь имеет место циклическая зависимость. Чтобы избавиться от нее, необходимо явно определить тип функции, используя std::function.

std::function<int(int)> lfib = [&lfib](int n) {return n < 2 ? 1 : lfib(n-1) + lfib(n-2);};



# 8 — non-member begin() и end()

Вы, вероятно, заметили, что в примерах ранее, я использовал функции begin() и end(). Это новое дополнение к стандартной библиотеке. Они работают со всеми контейнерами STL и могут быть расширены для работы с любым типом. 

Давайте возьмем, например, предыдущий пример, где я выводил вектор и затем искал первый нечетный элемент. Если std::vector заменить С-подобным массивом, то код будет выглядеть так:
	int arr[] = {1,2,3};
	std::for_each(&arr[0], &arr[0]+sizeof(arr)/sizeof(arr[0]), [](int n) {std::cout << n << std::endl;});
	
	auto is_odd = [](int n) {return n%2==1;};
	auto begin = &arr[0];
	auto end = &arr[0]+sizeof(arr)/sizeof(arr[0]);
	auto pos = std::find_if(begin, end, is_odd);
	if(pos != end)
	  std::cout << *pos << std::endl;
	
	
	С begin() и end() его можно переписать следующим образом:
	int arr[] = {1,2,3};
	std::for_each(std::begin(arr), std::end(arr), [](int n) {std::cout << n << std::endl;});
	
	auto is_odd = [](int n) {return n%2==1;};
	auto pos = std::find_if(std::begin(arr), std::end(arr), is_odd);
	if(pos != std::end(arr))
	  std::cout << *pos << std::endl;


Это почти полностью идентично коду с std::vector. Таким образом, мы можем написать один универсальный метод для всех типов, которые поддерживаются функциями begin() и end().

	template <typename Iterator>
	void bar(Iterator begin, Iterator end) 
	{
	   std::for_each(begin, end, [](int n) {std::cout << n << std::endl;});

	   auto is_odd = [](int n) {return n%2==1;};
	   auto pos = std::find_if(begin, end, is_odd);
	   if(pos != end)
	      std::cout << *pos << std::endl;
	}
	
	template <typename C>
	void foo(C c)
	{
	   bar(std::begin(c), std::end(c));
	}

	template <typename T, size_t N>
	void foo(T(&arr)[N])
	{
	   bar(std::begin(arr), std::end(arr));
	}
	
	int arr[] = {1,2,3};
	foo(arr);
	
	std::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	foo(v);



# 9 — static_assert и классы свойств

static_assert проверяет утверждение во время компиляции. Если утверждение — истина, то ничего не происходит. Если — ложь, то компилятор выводит указанное сообщение об ошибке.

	template <typename T, size_t Size>
	class Vector
	{
	   static_assert(Size > 3, "Size is too small");
	   T _points[Size];
	};
	
	int main()
	{
	   Vector<int, 16> a1;
	   Vector<double, 2> a2;
	   return 0;
	}


	error C2338: Size is too small
	see reference to class template instantiation 'Vector<T,Size>' being compiled
	   with
	   [
	      T=double,
	      Size=2
	   ]


static_assert становится более полезен, когда используется с классами свойств. Это набор классов, которые предоставляют информацию о типах во время компиляции. Они доступны в заголовке <type_traits>. Есть несколько видов классов в этом заголовке: классы-помощники, классы преобразований и непосредственно классы свойств. 
В следующем примере, функция add, как предполагается, работает только с целочисленными типами.
template <typename T1, typename T2>
	auto add(T1 t1, T2 t2) -> decltype(t1 + t2)
	{
	   return t1 + t2;
	}


Однако, при компиляции не возникнет ошибки, если написать следующее:
	std::cout << add(1, 3.14) << std::endl;
	std::cout << add("one", 2) << std::endl;


Программа просто выведет «4.14» и «е». Используя static_assert, эти две строки вызовут ошибку во время компиляции.
	template <typename T1, typename T2>
	auto add(T1 t1, T2 t2) -> decltype(t1 + t2)
	{
	   static_assert(std::is_integral<T1>::value, "Type T1 must be integral");
	   static_assert(std::is_integral<T2>::value, "Type T2 must be integral");

	   return t1 + t2;
	}


error C2338: Type T2 must be integral
see reference to function template instantiation 'T2 add<int,double>(T1,T2)' being compiled
   with
	   [
	      T2=double,
	      T1=int
	   ]
error C2338: Type T1 must be integral
see reference to function template instantiation 'T1 add<const char*,int>(T1,T2)' being compiled
	   with
	   [
	      T1=const char *,
	      T2=int
	   ]



# 10 — семантика перемещения

 Это — еще одна важная тема, затронутая в С++11. На эту тему можно написать несколько статей, а не абзацев, поэтому я не буду сильно углубляться. 

C++11 ввел понятие rvalue ссылок (указанных с &&), чтобы отличать ссылка на lvalue (объект, у которого есть имя) и rvalue (объект, у которого нет имени). Семантика перемещения позволяет изменять rvalues (ранее они считались неизменными и не отличались от типов const T&).

Класс/структура раньше имели некоторые неявные функции-члены: конструктор по умолчанию (если другой конструктор не определен), конструктор копирования и деструктор. Конструктор копирования выполняет поразрядное копирование переменных. Это означает, что если у вас есть класс с указателями на какие-то объекты, то конструктор копирования скопирует указатели, а не объекты, на которые они указывают. Если вы хотите получить в копии именно объекты, а не лишь указатели на них, вы должны это явно описать в конструкторе копирования.

Конструктор перемещения и оператор присваивания перемещения — эти две специальные функции принимают параметр T&&, который является rvalue. Фактически, они могут изменять объект. 

Следующий пример показывает фиктивную реализацию буфера. Буфер идентифицируется именем, имеет указатель (обернутый в std::unique_ptr) на массив элементов типа Т и переменную, содержащую размер массива.

	template <typename T>
	class Buffer 
	{
	   std::string          _name;
	   size_t               _size;
	   std::unique_ptr<T[]> _buffer;
	
	public:
	   // default constructor
	   Buffer():
	      _size(16),
	      _buffer(new T[16])
	   {}

	   // constructor
	   Buffer(const std::string& name, size_t size):
	      _name(name),
	      _size(size),
	      _buffer(new T[size])
	   {}
	
 	  // copy constructor
	   Buffer(const Buffer& copy):
	      _name(copy._name),
	      _size(copy._size),
	      _buffer(new T[copy._size])
	   {
	      T* source = copy._buffer.get();
	      T* dest = _buffer.get();
	      std::copy(source, source + copy._size, dest);
	   }

	   // copy assignment operator
	   Buffer& operator=(const Buffer& copy)
	   {
	      if(this != &copy)
	      {
	         _name = copy._name;

	         if(_size != copy._size)
	         {
	            _buffer = nullptr;
 	           _size = copy._size;
	            _buffer = (_size > 0)? new T[_size] : nullptr;
	         }

	         T* source = copy._buffer.get();
	         T* dest = _buffer.get();
	         std::copy(source, source + copy._size, dest);
 	     }

	      return *this;
	   }

	   // move constructor
	   Buffer(Buffer&& temp):
	      _name(std::move(temp._name)),
	      _size(temp._size),
	      _buffer(std::move(temp._buffer))
	   {
	      temp._buffer = nullptr;
	      temp._size = 0;
	   }
	
	   // move assignment operator
	   Buffer& operator=(Buffer&& temp)
	   {
 	     assert(this != &temp); // assert if this is not a temporary
	
 	     _buffer = nullptr;
 	     _size = temp._size;
 	     _buffer = std::move(temp._buffer);
	
	      _name = std::move(temp._name);
	
	      temp._buffer = nullptr;
	      temp._size = 0;
	      
	      return *this;
	   }
	};

	template <typename T>
	Buffer<T> getBuffer(const std::string& name) 
	{
	   Buffer<T> b(name, 128);
	   return b;
	}
	int main()
	{
	   Buffer<int> b1;
	   Buffer<int> b2("buf2", 64);
	   Buffer<int> b3 = b2;
	   Buffer<int> b4 = getBuffer<int>("buf4");
	   b1 = getBuffer<int>("buf5");
	   return 0;
	}


Конструктор копирования по умолчанию и оператор присваивания копии должны быть вам знакомы. Новое в С++11 — это конструктор перемещения и оператор присваивания перемещения, Если вы выполните этот код, то увидите, что когда создается b4 — вызывается конструктор перемещения. Кроме того, когда b1 присваивается значение — вызывается оператор присваивания перемещения. Причина — значение, возвращаемое функцией getBuffer() — rvalue. 

Вы, вероятно, заметили использование std::move в конструкторе перемещения, при инициализации имени переменной и указателя на буфер. Имя — это строка std::string и std::string также реализует семантику перемещения. То же самое касается и unique_ptr. Однако, если бы мы записали просто _name(temp._name), то был бы вызван конструктор копирования. Но почему в этом случае не был вызван конструктор перемещения для std::string? Дело в том, что даже если конструктор перемещения для Buffer был вызван с rvalue, внутри конструктора это все равно представляется как lvalue. Чтобы сделать его снова rvalue и нужно использовать std::move. Эта функция просто превращает ссылку lvalue в rvalue. 


Вместо заключения

 Есть много вещей в С++11, о которых можно и нужно рассказывать; эта статья была лишь одним из многих возможных начал. Эта статья представила серию функций языка и стандартной библиотеки, которую должен знать каждый разработчик С++. Однако, для более глубокого понимания всего сказанного, этой статьи недостаточно, поэтому тут не обойтись без дополнительной литературы.
 
 


	
	1) Align Technology
	To : Ekaterina Chumikova <echumikova@aligntech.com>
	Екатерина Чумикова
	Align Technology, Inc .
	9 / 1 B Варшавское шоссе, 117105
	электронная почта   echumikova@aligntech.com
	+ 7 - 495 - 995 - 88 - 54 (2309) | ячейка + 7 915 829 99 29

	2) ETHR
	Меня зовут Екатерина, я IT - рекрутер компании ETHR.Нашла Ваше резюме на HeadHunter.
	разработчика C++ (виндовый кластер, highload).Зарплатная вилка 150 - 200 т.р.
	С уважением,
	Екатерина Лавреха, агентство IT - рекрутмента ETHR
	skype : taiss.erinkite

	3) http://www.nfware.com/ активно ищем "C++ разработчика" (возможно, это Вы!?). 
	Анастасия Белая!
		nastya0612@gmail.com

		4) АББУ
		Рузаева Анастасия
		Специалист по работе с персоналом
		ABBYY International HQ
		Тел : +7 495 783 37 00
		Факс : +7 495 783 26 63
		E - mail : Anastasiya_R@abbyy.com
		http ://www.abbyy.ru


	5) Люксофт

	Elizaveta
		Deyneko

		Junior Recruitment Specialist

		T : +7(495)967 8030

		Ex.5042





		--) --ХЕЛЬСИНКИ
		Kind Regards,
		Ruslan Aktemirov

		+ 7 915 329 24 22
		skype: ruslan_aktemirov
		telegram : @aktemirov




# General questions

- OOP concepts - encapsulation, data abstraction, inheritance, polymorphism
- Data Types, Variables - const, static, readonly
- access specifier - private, protected, public
- Abstract class
- interface
- collection - hast table, map, vector, binary tree
- Multi threading
- Memory Management
- Pointers - void, far, near, wild
- virtual functions
- Marshaling
-  SDI, MDI
- TCP / IP client server connection
-  Message passing, delegation, IPC
-  File handling
-  Memory management
- Error handling, exception handling

# C++ general

- Classes and Objects
- Constructors and Destructors
- Template
- References and pointer
- STL
- RTTI

# SQL questions

- RDBMS
- Normalization - Different Normalization Forms(1NF, 2NF, 3NF, BCNF)
- SQL Stament(DML, DDL, DCL, TCL)
- Stored Procedure, Trigger and View
- Join - Different Types of Join(Cross Join, Inner Join, Outer Join, Self Join)
- Index - Clustered Index, Non Clustered Index
- Linked Server
- Cursor
- Collation
- Sub - query

# QT related interview questions

http://www.qtcentre.org/threads/38448-QT-related-interview-questions

- How qt differs from other mobile development platforms like android?
- If worked with GTK what is the difference between QT and GTK?
- What are the striking futures of QT?
- What is Qpointer?
- What is dpointer?
- What is MVC architecture? How it is organized?
- What is a signal? And how will it differ from event?
- What is a slot? And how it differs with callback Method?
- What is the difference between signal and slot mechanism and Callback mechanism of GTK?
- How many signals at maximum you can connect to a single slot? If more than one how you can do that?
- How many slots can you connect to a signal? If more than one how those slots will be executed? 
(The order of execution)
- What is QCast and how will it differ compared to c++’s dynamic cast?
- What is the use of Q_OBJECT macro?
- What is MOC and UIC? Explain how they will work for compilation in QT?
- What is qmake? (Explain the usage of it)
- How a QT Program/Application written for one platform (Symbian) can be ported/executed in another 
platform (Maemo)? (Explain If you need to make any changes or you need to recompile)
- What are all the platforms/OS currently QT supports?

# Threading stuff

https://books.google.ru/books?id=MEZdDgAAQBAJ&pg=PA846&lpg=PA846&dq=std+thread+if+fails+before+join&source=bl&ots=LbhCsUltf3&sig=Sd5LjAg9Fcw8pmH3_oQVyL-gmOQ&hl=ru&sa=X&ved=0ahUKEwjJqNSh2o7XAhUiMZoKHZJ1ASwQ6AEIZzAI#v=onepage&q=std%20thread%20if%20fails%20before%20join&f=false

# What if std::thread fails BEFORE join - program will shutdown

A std::thread is joinable if it contains a thread state that has not been joined or detatched.

A std::thread gains a thread state by being non default constructed, or having one moveed into it from another std::thread. It loses it when moveed from.

There is no delay in gaining the thread state after construction completes. And it does not go away when the threaded function finishes. So there is not that problem.

There is the problem that if code throws above, you will fail to join or detatch, leading to bad news at program shutdown. Always wrap std::thread in a RAII wrapper to avoid that, or just use std::async that returns void and wrap the resulting std::future similarly (because the standard says it blocks in the dtor, but microsofts implementation does not, so you cannot trust if it will or not).

--------------
- In VC std::futures from std::async don't block in dtor? – inf Nov 25 '13 at 12:14
- Yup, that's true. Tested it myself. 
--------------

-- if  JOIN()  Fails

libc++abi.dylib: terminating with uncaught exception of type std::__1::system_error: thread::join failed: No such process



# CreateThread <-> _beginthreadex
# Createthread разница _beginthreadex

Лучше использовать _beginthreadex, чем CreateThread().
СУТЬ: 
http://forum.vingrad.ru/forum/topic-47554.html

CreateThread - чисто Win32Api'шная функция, а вот
_beginthread - функция библиотеки CRT, НЕ кроссплатформенна, но приспособленна для работы с С, т.е. она делает дополнительные манипуляции, что бы стандартные библиотеки корректно работатли (+ вызывает CreateThread ) .
В общем если пишешь на С, то лучше пользоваться вторым.
Рихтер в статье CreateThread vs. _beginthread очень подробно описывает почему _beginthread предпочтительнее. Она создает Thread Local Storage (TLS), где переопределены, в частности, все глобальные константы, к-рые ф-ции CRT-библиотеки юзают. Например, такая как errno. 
Именно TLS - гарантия, что ф-ции CRT-библиотеки будут работать корректно. 

The C runtime library was delivered in a UNIX context, in which there is no distinction between processes and threads. In the Windows context, many threads can be executing in a single address space. 
Microsoft has provided an alternative function to CreateThread, called _beginthreadex, to be used with the programs that use multiple threads at the same time they use the C runtime library. The problem occurs with any globally accessible variable used by this library ( there are several of them ). The Microsoft solution is to have the C runtime library provide a copy of each of these variables for each thread. Then, when a thread interacts with the runtime library, variables are shared only between the runtime code and the thread, not among all threads. The _beginthreadex function creates the copy for a thread in conjunction with an embedded call to CreateThread.


# PATTERNS

- Синглтон
- Фассад
- Ресивер
- Листенер
- Фабрика


# SQL

GroupBy HAVING


# Вирт.функции в Конструкторах

	// 1-ый случай и ПРОБЛЕМА 1 ...
	class Transaction 
	{ public: // транзакций
	  Transaction() { logTransaction(); }
	  virtual void logTransaction() const = 0; // выполняет зависящую от типа
	};
	class BuyTransaction: public Transaction
	{ public: virtual void logTransaction() const = 0; };
	class SellTransaction: public Transaction
	{ public: virtual void logTransaction() const = 0; };

	// 2-ой случай и ПРОБЛЕМА 2 ....
	class Transaction
	{ public: // транзакций
	  Transaction() { logTransaction(); }
	  virtual void logTransaction() const = 0; // выполняет зависящую от типа
	};
	class BuyTransaction: public Transaction
	{ public: virtual void logTransaction() {print("Buy");} };
	class SellTransaction: public Transaction
	{ public: virtual void logTransaction() {print("Sell");} };

	BuyTransaction b;

Ясно, что будет вызван конструктор BuyTransaction, но сначала должен быть вызван конструктор Transaction, потому что части объекта, принадлежащие базовому классу, конструируются прежде, чем части, принадлежащие производному классу. В последней строке конструктора Transaction вызывается виртуальная функция logTransaction, тут-то и начинаются сюрпризы. Здесь вызывается та версия logTransaction, которая определена в классе Transaction, а не в BuyTransaction, несмотря на то что тип создаваемого объекта – BuyTransaction. Во время конструирования базового класса не вызываются виртуальные функции, определенные в производном классе. Объект ведет себя так, как будто он принадлежит базовому типу. Короче говоря, во время конструирования базового класса виртуальных функций не существует.


# Вирт.функции в Деструкторах



# Исключение в Конструкторах


# Исключение в деструкторах

1) Утечки ресурсов / некнтролируемое поведение
~B() {
    delete this->resource;  // throws
    close(this->socket);    // leaks
}

2) Предположим, что где-то в программе сгенерировано исключение. При этом начинается размотка стека и уничтожение автоматических объектов.
Если новое исключение генерируется в деструкторе уничтожаемого в процессе раскрутки объекта, то вызывается функция terminate(), которая по умолчанию вызывает abort(), т.е. приложение завершается.
Эту функцию можно подменить своей с помощью set_terminate(), но это уже другая история...
+ При разрушении статических объектов исключение в деструкторе также приведет к terminate().

3) vector<объектов> - если деструкторы сработали не в 1ом элеменете а множество раз, то вызовится ф-ция terminate(), которая по умолчанию вызывает abort(), т.е. приложение завершается.



# REFERENCE, NEW-DELETE, TEMPLATE, VIRTUALITY

	#include <iostream>

	class A
	{
	public:
		virtual void Printer()
		{
			std::cout << "A print" << std::endl;
		}
		virtual ~A()
		{
			std::cout << "~A" << std::endl;
		}
	};
	
	class B : public A
	{
	public:
		void Printer()
		{
			std::cout << "B" << std::endl;;
		}
		~B()
		{
			std::cout << "~B" << std::endl;
		}
	};
	
	template <typename T>
	class Temp
	{
	public:
		//void print(T t)	// ERROR - Incorrect by value
		void print(T* t)	// OK - because original is pointer pointer
		{
			t->Printer();
		};
	};
	
	int main()
	{
		B b;
		b.Printer();		// B
	
		A* a = &b;
		a->Printer();		// B
	
		Temp<A> printer;
		printer.print(a);	// B
		
		// ПАМЯТЬ НЕ ВЫДЕЛИЛИ ДИНАМИЧЕСКИ !!!
		// НЕЛЬЗЯ DELETE-ТИТЬ !!!!!
		delete a;	// DELETE WILL THROW EXEPTION !!!
	
		return 0;
	}



# Reverse a linked list - Iterative method

https://www.youtube.com/watch?v=sYcOK51hl-A
https://vichargrave.github.io/articles/2013-01/reversing-a-singly-linked-list

http://www.geeksforgeeks.org/reverse-a-linked-list/

Given pointer to the head node of a linked list, the task is to reverse the linked list. We need to reverse the list by changing links between nodes.

Examples:

	Input: Head of following linked list
	1->2->3->4->NULL
	Output : Linked list should be changed to,
	4->3->2->1->NULL

	Input : Head of following linked list
	1->2->3->4->5->NULL
	Output : Linked list should be changed to,
	5->4->3->2->1->NULL

	Input : NULL
	Output : NULL

	Input : 1->NULL
	Output : 1->NULL


Iterative Method
Iterate trough the linked list.In loop, change next to prev, prev to current and current to next.

Implementation of Iterative Method


	#include<stdio.h>
	#include<stdlib.h>
	
	/* Link list node */
	struct Node
	{
		int data;
		struct Node* next;
	};
	
	/* Function to reverse the linked list */
	static void reverse(struct Node** head_ref)
	{
		struct Node* prev = NULL;
		struct Node* current = *head_ref;
		struct Node* next;
		while (current != NULL)
		{
			next = current->next;
			current->next = prev;
			prev = current;
			current = next;
		}
		*head_ref = prev;
	}
	
	/* Function to push a node */
	void push(struct Node** head_ref, int new_data)
	{
		/* allocate node */
		struct Node* new_node =
			(struct Node*) malloc(sizeof(struct Node));
	
		/* put in the data  */
		new_node->data = new_data;
	
		/* link the old list off the new node */
		new_node->next = (*head_ref);
	
		/* move the head to point to the new node */
		(*head_ref) = new_node;
	}
	
	/* Function to print linked list */
	void printList(struct Node *head)
	{
		struct Node *temp = head;
		while (temp != NULL)
		{
			printf("%d  ", temp->data);
			temp = temp->next;
		}
	}
	
	/* Driver program to test above function*/
	int main()
	{
		/* Start with the empty list */
		struct Node* head = NULL;
	
		push(&head, 20);
		push(&head, 4);
		push(&head, 15);
		push(&head, 85);
	
		printf("Given linked list\n");
		printList(head);
		reverse(&head);
		printf("\nReversed Linked list \n");
		printList(head);
		getchar();
	}
	/ pre>

		Given linked list
		85 15 4 20
		Reversed Linked list
		20 4 15 85

		Time Complexity : O(n)
		Space Complexity : O(1)

Recursive Method :

- Divide the list in two parts - first node and rest of the linked list.
- Call reverse for the rest of the linked list.
- Link rest to first.
- Fix head pointer

	void recursiveReverse(struct Node** head_ref)
	{
	struct Node* first;
	struct Node* rest;

	/* empty list */
	if (*head_ref == NULL)
		return;

	/* suppose first = {1, 2, 3}, rest = {2, 3} */
	first = *head_ref;
	rest = first->next;

	/* List has only one node */
	if (rest == NULL)
		return;

	/* reverse the rest list and put the first element at the end */
	recursiveReverse(&rest);
	first->next->next = first;

	/* tricky step -- see the diagram */
	first->next = NULL;

	/* fix the head pointer */
	*head_ref = rest;
	}


A Simpler and Tail Recursive Method

	// A simple and tail recursive C++ program to reverse
	// a linked list
	#include<bits/stdc++.h>
	using namespace std;
	
	struct Node
	{
		int data;
		struct Node *next;
	};
	
	void reverseUtil(Node *curr, Node *prev, Node **head);
	
	// This function mainly calls reverseUtil()
	// with prev as NULL
	void reverse(Node **head)
	{
		if (!head)
			return;
		reverseUtil(*head, NULL, head);
	}
	
	// A simple and tail recursive function to reverse
	// a linked list.  prev is passed as NULL initially.
	void reverseUtil(Node *curr, Node *prev, Node **head)
	{
		/* If last node mark it head*/
		if (!curr->next)
		{
			*head = curr;
	
			/* Update next to prev node */
			curr->next = prev;
			return;
		}
	
		/* Save curr->next node for recursive call */
		node *next = curr->next;
	
		/* and update next ..*/
		curr->next = prev;
	
		reverseUtil(next, curr, head);
	}
	
	// A utility function to create a new node
	Node *newNode(int key)
	{
		Node *temp = new Node;
		temp->data = key;
		temp->next = NULL;
		return temp;
	}
	
	// A utility function to print a linked list
	void printlist(Node *head)
	{
		while (head != NULL)
		{
			cout << head->data << " ";
			head = head->next;
		}
		cout << endl;
	}
	
	// Driver program to test above functions
	int main()
	{
		Node *head1 = newNode(1);
		head1->next = newNode(2);
		head1->next->next = newNode(3);
		head1->next->next->next = newNode(4);
		head1->next->next->next->next = newNode(5);
		head1->next->next->next->next->next = newNode(6);
		head1->next->next->next->next->next->next = newNode(7);
		head1->next->next->next->next->next->next->next = newNode(8);
		cout << "Given linked list\n";
		printlist(head1);
		reverse(&head1);
		cout << "\nReversed linked list\n";
		printlist(head1);
		return 0;
	}





# File MAPPING / Map View of File

http://vsokovikov.narod.ru/New_MSDN_API/Menage_files/main_fl_map.htm

# Books

 LARGE_INTEGER union

- Скотт Майерс - Эффективное использование C++. 55 верных способов улучшить структуру и код ваших программ

ONLINE - https://www.e-reading.club/book.php?book=1002058


- Рихтер Дж., Назар К. - Windows via C C++. Программирование

RUS - https://studfiles.net/preview/397644/

ENG - https://ptgmedia.pearsoncmg.com/images/9780735663770/samplepages/9780735663770.pdf

Windows Internals

http://materias.fi.uba.ar/7508/WI6/Windows%20Internals%20Part%201%20(6th%20Edition).pdf

Application Programming - Interface for Windows

https://www.ecma-international.org/publications/files/ECMA-ST/Ecma-234-v3.pdf



https://msdn.microsoft.com/en-us/library/windows/desktop/ff485848(v=vs.85).aspx

- What Is a COM Interface?
- Initializing the COM Library
- Error Codes in COM
- Creating an Object in COM
- Example: The Open Dialog Box
- Managing the Lifetime of an Object
- Asking an Object for an Interface
- Memory Allocation in COM
- COM Coding Practices
- Error Handling in COM

# ПОЛИМОРФИЗМ - как реализован в Си++
https://ru.stackoverflow.com/questions/192522/%D0%9F%D0%BE%D0%BB%D0%B8%D0%BC%D0%BE%D1%80%D1%84%D0%B8%D0%B7%D0%BC-%D0%B2-%D0%BA%D0%BB%D0%B0%D1%81%D1%81%D0%B0%D1%85-c

Правильный полиморфизм заключается в том, что будет вызываться правильная функция по указателю на базовый класс, при этом не нужно знать, какой именно класс наследник скрывается за указателем.

	class A {
	public:
		virtual void f() = 0;
	}
	
	class B : A {
	public:
		void f() {};
	}
	
	class C : A {
	public:
		void f() {};
	}
	
	A * b = new B();
	A * c = new C();
	b->f(); // здесь будет вызываться метод класса B
	c->f(); // здесь будет вызываться метод класса C

Почему следует использовать полиморфимз:
- пример 1. Пусть есть игра (starcraft, козаки, и подобные). Создается класс "базовый юнит". От него наследуются все юниты. Все созданные юниты добавляются в один большой массив (вектор, список). Когда нужно отрисовать, то просто в цикле вызываем у всех функция draw и не думаем, а кто у нас там. Каждый объект и так знает, как ему рисоваться.
- привет 2. мессенджер типа миранда или квип. Есть куча различных сервисов (аська, жаббер, мейлру). У всех есть контакт лист. Сам мессенджер ничего не знает о сервисах, он просто вызывает функции, а за счет виртуальности и полиморфизма вызываются правильные функции. При этом, если был добавлен новый сервис, то не нужно переписывать весь код, что бы он был в курсе.


# rvalue и lvalue ссылки

https://www.youtube.com/watch?v=5AbTHsZl7LY


# MALLOCK
Возвращает указатель на выделенную память. или НОЛЬ, если память выделить не удалось.

# РЕКУРСИЯ - как работает
кладёт на стек, адреса возврата (чтобы произвести обратный вызов) в функции, в коорые циклически заходит - 
Но размер стека имеется ограничения, и если мы положим на стек слишком много адресов возврата, то мы получим
STACKOVERFLOW

# ПАТТЕРН ПРОЕКТИРОВАНИЯ "Виртуальный конструктор"

https://habrahabr.ru/post/64369/


# Виртуальные функции - как работают
https://habrahabr.ru/post/51229/

Связывание — это сопоставление вызова функции с вызовом. В C++ все функции по умолчанию имеют раннее связывание, то есть компилятор и компоновщик решают, какая именно функция должна быть вызвана, до запуска программы. Виртуальные функции имеют позднее связывание, то есть при вызове функции нужное тело выбирается на этапе выполнения программы.

Встретив ключевое слово virtual, компилятор помечает, что для этого метода должно использоваться позднее связывание: для начала он создает для класса таблицу виртуальных функций, а в класс добавляет новый скрытый для программиста член — указатель на эту таблицу. (На самом деле, насколько я знаю, стандарт языка не предписывает, как именно должен быть реализован механизм виртуальных функций, но реализация на основе виртуальной таблицы стала стандартом де факто.). 

Что можно понять из этого примера. Во-первых, размер «пустого» класса всегда больше нуля, потому что компилятор специально вставляет в него фиктивный член. Как пишет Эккель, «представьте процесс индексирования в массиве объектов нулевого размера, и все станет ясно» ;) Во-вторых, мы видим, что размер «непустого» класса NotEmptyVirt при добавлении в него виртуальной функции увеличился на стандартный размер указателя на void; а в «пустом» классе EmptyVirt фиктивный член, который компилятор ранее добавлял для приведения класса к ненулевому размеру, был заменен на указатель.

Что представляет собой таблица виртуальных функций и для чего она нужна? Таблица виртуальных функций хранит в себе адреса всех виртуальных методов класса (по сути, это массив указателей), а также всех виртуальных методов базовых классов этого класса.

Таблиц виртуальных функций у нас будет столько, сколько есть классов, содержащих виртуальные функции — по одной таблице на класс. Объекты каждого из классов содержат именно указатель на таблицу, а не саму таблицу! Вопросы на эту тему любят задавать преподаватели, а также те, кто проводит собеседования. 

ПРИМЕР КАВЕРЗНЫХ ВОПРОСОВ на которых можно подловить новичков: «если класс содержит таблицу виртуальных функций, то размер объекта класса будет зависеть от количества виртуальных функций, содержащихся в нем, верно?»; «имеем массив указателей на базовый класс, каждый из которых указывает на объект одного из производных классов — сколько у нас будет таблиц виртуальных функций?» и т.д.).



# Синглтон и МНОГОПОТОЧНОСТЬ
https://habrahabr.ru/post/147373/

Проблема. Нам нужно сделать LAZY-инициализацию (изначально объект не создан, а мы создаём при первом вызове getInstance)
НО проблема в том, что несколько потоков могут одновременно вызвать getInstance - Как это сделать Правильно ?

ОТВЕТ - Мы при создании - проверяем если он не создан, то делаем ЛОК, под локом ещё раз проверяем, если объект не создан, то
создаём, и делаем АНЛОК. - ДАБЛ-ЧЕК-ПАТТЕРН - Это принцип правильной LAZY-инициализации.

- DOUBLE-CHECK LOCKING. Microsoft советует записывать его вот так:


	using System;
	public sealed class Singleton
	{
		private static volatile Singleton instance;
		private static object syncRoot = new Object();
	
		private Singleton() {}
	
		public static Singleton Instance
		{
			get
		{
			if (instance == null)
			{
				lock(syncRoot)
				{
					if (instance == null)
						instance = new Singleton();
				}
			}
		return instance;
		}
		}
	}




# Процессы, Потоки, Приоритеты в Windows
http://www.netcode.ru/cpp/?artID=2763
# Потоки
http://club.shelek.ru/viewart.php?id=71


# Процессы

Процессом обычно называют экземпляр выполняемой программы.

Хотя на первый взгляд кажется, что программа и процесс понятия практически одинаковые, они фундаментально отличаются друг от друга. Программа представляет собой статический набор команд, а процесс это набор ресурсов и данных, использующихся при выполнении программы. 

Процесс в Windows состоит из следующих компонентов:

- Структура данных, содержащая всю информацию о процессе, в том числе список открытых дескрипторов различных системных ресурсов, уникальный идентификатор процесса, различную статистическую информацию и т.д.;
- Адресное пространство - диапазон адресов виртуальной памяти, которым может пользоваться процесс;
- Исполняемая программа и данные, проецируемые на виртуальное адресное пространство процесса.

https://moodle.kstu.ru/mod/page/view.php?id=49

С каждым процессом связывается его адресное пространство, из которого он может читать и в которое он может писать данные.

Адресное пространство содержит:

- саму программу
- данные к программе
- стек программы

С каждым процессом связывается набор регистров, например:
- счетчика команд (в процессоре) - регистр в котором содержится адрес следующей, стоящей в очереди на выполнение команды. После того как команда выбрана из памяти, счетчик команд корректируется и указатель переходит к следующей команде.


# Потоки

Процессы инертны. Отвечают же за исполнение кода, содержащегося в адресном пространстве процесса, потоки. Поток (thread) - некая сущность внутри процесса, получающая процессорное время для выполнения. В каждом процессе есть минимум один поток. Этот первичный поток создается системой автоматически при создании процесса. Далее этот поток может породить другие потоки, те в свою очередь новые и т.д. Таким образом, один процесс может владеть несколькими потоками, и тогда они одновременно исполняют код в адресном пространстве процесса. 

Каждый поток имеет:

- Уникальный идентификатор потока;
- Содержимое набора регистров процессора, отражающих состояние процессора;
- Два стека, один из которых используется потоком при выполнении в режиме ядра, а другой - в пользовательском режиме;
- (стека потока, который содержит параметры всех функций и локальные переменные, необходимые потоку для выполнения кода.)
- Закрытую область памяти, называемую локальной памятью потока (thread local storage, TLS) и используемую подсистемами, run-time библиотеками и DLL.


# Планирование потоков

Чтобы все потоки работали, операционная система отводит каждому из них определенное процессорное время. Тем самым создается иллюзия одновременного выполнения потоков (разумеется, для многопроцессорных компьютеров возможен истинный параллелизм). В Windows реализована система вытесняющего планирования на основе приоритетов, в которой всегда выполняется поток с наибольшим приоритетом, готовый к выполнению. Выбранный для выполнения поток работает в течение некоторого периода, называемого квантом. Квант определяет, сколько времени будет выполняться поток, пока операционная система не прервет его

# Приоритеты

В Windows существует 32 уровня приоритета, от 0 до 31. Они группируются так: 31 - 16 уровни реального времени; 15 - 1 динамические уровни; 0 - системный уровень, зарезервированный для потока обнуления страниц (zero-page thread).

При создании процесса, ему назначается один из шести классов приоритетов:

- Real time class (значение 24),
- High class (значение 13),
- Above normal class (значение 10),
- Normal class (значение 8),
- Below normal class (значение 6),
- и Idle class (значение 4).

# Создание процессов

Создание Win32 процесса осуществляется вызовом одной из таких функций, как CreateProcess, CreateProcessAsUser (для Win NT/2000) и CreateProcessWithLogonW (начиная с Win2000) и происходит в несколько этапов:

- Открывается файл образа (EXE), который будет выполняться в процессе. Если исполняемый файл не является Win32 приложением, то ищется образ поддержки (support image) для запуска этой программы. Например, если исполняется файл с расширением .bat, запускается cmd.exe и т.п.

В WinNT/2000 для отладки программ реализовано следующее. CreateProcess, найдя исполняемый Win32 файл, ищет в SOFTWARE\Microsoft\Windows NT\CurrentVersion\Image File Execution Option раздел с именем и расширением запускаемого файла, затем ищет в нем параметр Debugger, и если строка не пуста, запускает то, что в ней написано вместо данной программы.

- Создается объект Win32 "процесс".
- Создается первичный поток (стек, контекст и объект "поток").
- Подсистема Win32 уведомляется о создании нового процесса и потока.
- Начинается выполнение первичного потока.
- В контексте нового процесса и потока инициализируется адресное пространство (например, загружаются требуемые DLL) и начинается выполнение программы.

# Завершение процессов

Процесс завершается если:

- Входная функция первичного потока возвратила управление.
- Один из потоков процесса вызвал функцию ExitProcess.
- Поток другого процесса вызвал функцию TerminateProcess.


# Создание потоков

Первичный поток создается автоматически при создании процесса. Остальные потоки создаются функциями CreateThread и CreateRemoteThread (только в Win NT/2000/XP).

# Завершение потоков

Поток завершается если

- Функция потока возвращает управление.
- Поток самоуничтожается, вызвав ExitThread.
- Другой поток данного или стороннего процесса вызывает TerminateThread.
- Завершается процесс, содержащий данный поток.

# Объекты ядра (17)

- Module			Подгружаемый модуль(DLL)
- Process			Процесс
- Pipe (Named / Unnamed)	Канал (Именованые / Неименованые)
- Socket			Сокет
- Mailslot			Почтовый слот
- File				Файл
- File mapping			Проекция файла
- Job				Задание
- Thread			Поток
- Event				Событие
- Mutex				Мьютекс
- Semaphore			Семафор
- Access token			Маркер доступа
- Heap				Куча
- Change notification		Уведомление об изменениях на диске
- I / O completion ports	Порт завершения ввода - вывода
- Timer				Ожидаемый таймер


# Wait функции

- WaitForSingleObject
- WaitForMultipleObjects

# Синхронизация потоков

- События
- Мьютексы
- Семафоры
- Крит. секции

# Синхронизация процессов

- Пайпы, Сокеты
- Оконные сообщения
- МэйлСлоты
- ФайлМэппинги / разделяемая память


# Оконная функция
http://lavimidj.ru/860/

- SendMessage	(синхр.)
- PostMessage (асинхроння)
- GetMessage (while ((iGetOk = GetMessage(&msg, NULL, 0, 0 )) != 0) //цикл сообщений)
- TranslateMessage
- DispatchMessage
- PostQuitMessage

- WndProc - Обработка сообщений

СОВЕТ
Сообщение можно отослать функцией SendMessage или ее асинхронным аналогом PostMessage.
Для приема сообщений в программе должен находиться «цикл сообщений» («message loop») который обычно выглядит так:

	//цикл сообщений приложения
	MSG msg = {0};    //структура сообщения
	int iGetOk = 0;   //переменная состояния
	while ((iGetOk = GetMessage(&msg, NULL, 0, 0 )) != 0) //цикл сообщений
	{
		//если GetMessage вернул ошибку - выход
		if (iGetOk == -1) return 3;
		TranslateMessage(&msg);    
		DispatchMessage(&msg);
	}
	
Функция GetMessage принимает следующие параметры:

LPMSG lpMsg – указатель на структуру сообщения, в которую GetMessage вернет результат.
HWND hWnd – описатель окна, от которого GetMessage примет сообщение (NULL означает, что GetMessage принимает сообщения от всех окон, принадлежащих потоку).
UINT wMsgFilterMin – наименьший идентификатор сообщения, которое примет GetMessage.
UINT wMsgFilterMax – наибольший идентификатор сообщения, которое примет GetMessage (если в значениях параметров wMsgFilterMin и wMsgFilterMax передать 0, функция будет принимать ВСЕ сообщения).
Функция GetMessage не отдает управление программе, пока не придет какое-либо сообщение. Если пришедшее сообщение – WM_QUIT, функция GetMessage вернет 0. Тогда цикл прервется, и программа завершит свою работу. При любом другом сообщении функция GetMessage возвращает значение больше нуля, и начинатся выполнение тела цикла. При ошибке GetMessage возвращает -1.

СОВЕТ
Сообщение WM_QUIT лучше посылать с помощью специальной функции PostQuitMessage(int iExitCode). Эта функция отошлет сообщение WM_QUIT, а в параметре wParam передаст код завершения программы, указанный в iExitCode.
Функция DispatchMessage должна вызвать «функцию обработки сообщений». В простейшем варианте она выглядит так:

	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, 
	WPARAM wParam, LPARAM lParam)
	{
	// выборка и обработка сообщений
	switch (message)
	{
		case WM_LBUTTONUP:
		//реакция на сообщение
		MessageBox(hWnd,"Вы кликнули!","событие",0); 
		break;
		case WM_DESTROY:
		//реакция на сообщение
		PostQuitMessage(0);
		break;
		//все необработанные сообщения обработает сама Windows
		default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	// switch (message)
	}
	return 0;
	} // конец функции обработчика сообщений


# ЧТО ТАКОЕ ОКОННАЯ ФУНКЦИЯ:
http://detc.ls.urfu.ru/assets/acomp0091/lesson1/i3.html

Как Windows определяет адресата, ведь клавиатура и мышь являются разделяемыми устройствами, а значит, их сообщения могут предназначаться любому приложению? 

otvet.jpg - 2419 Bytes Windows допускает выполнение одновременно нескольких приложений, каждое из которых может иметь множество окон. Однако только одно окно в каждый момент времени может получать сообщения от клавиатуры. Принято говорить, что окно это имеет фокус ввода. Фокус ввода может быть изменен, например, с помощью мыши (для этого достаточно щелкнуть мышью в требуемом окне). Приложение, окно которого имеет фокус ввода, называется активным. Сообщения от клавиатуры помещаются в очередь активного приложения. Сообщения от мыши обрабатываются по-другому, они передаются тому приложению, в окне которого находится указатель мыши. 

Обработку прикладной очереди сообщений осуществляет уже само приложение. Для этого программа организует так называемый цикл обработки сообщений. В нем осуществляется выбор нового сообщения из очереди прикладной программы и вызов диспетчера для его обработки соответствующей функцией (в данном случае А илиВ). В связи с тем, что сообщения связаны с окнами, функции обработки сообщения называют 

!!! ОКОННЫМИ ФУНКЦИЯМИ !!! 


# COM-объекты:
https://www.youtube.com/watch?v=7yv3ue8kWBw

https://rsdn.org/article/com/introcom.xml#EHCAC

COM-позволяет делать 2 вещи / ответсвенности:

- Запросить Интерфейс
-- QueryInterface
- Подсчёт ссылок (счётчик ссылок)
-- AddRef, Release

- IUnknown::QueryInterface
- IUnknown::AddRef
- IUnknown::Release

https://www.e-reading.club/chapter.php/127274/101/Kidruk_-_KOMPAS-3D_V10_na_100__.html

Данный счетчик определяет, как долго интерфейс будет оставаться доступным, прежде чем он будет удален из памяти. Именно для этой цели существует специальный интерфейс, который называется ІUnknown. Он имеет настолько важное значение, что основной принцип спецификации СОМ требует, чтобы все СОМ-объекты кроме своих специализированных интерфейсов поддерживали интерфейс ІUnknown. Причем каждый определенный для объекта интерфейс должен происходить от ІUnknown или от интерфейса, который в свою очередь сам происходит от ІUnknown. Данный принцип называется наследованием интерфейсов. В интерфейсе ІUnknown реализовано лишь три метода: Queryіnterface(), AddRef() и Release(). Метод Queryіnterface() определяет, является ли полученный интерфейс нужным. Методы AddRef() и Release() используются для подсчета ссылок на данный интерфейс при его применении многими программами. Перед началом использования COM-объекта клиент вызывает метод СОМ, тем самым увеличивая количество ссылок на интерфейс на единицу.


Теперь вы поняли, что технология СОМ предусматривает наличие множества абстрактных классов, которые требуют реализации. При построении СОМ-компонента первым делом нужно реализовать интерфейс, который должны использовать все СОМ-компоненты: IUnknown. Компонент должен не только реализовать интерфейс IUnknown для себя самого, но и обеспечить его реализацию для каждого своего интерфейса. Вначале это может показаться вам слишком сложным, но именно так и обстоят дела. Большинство СОМ-компонентов предлагают несколько интерфейсов, и запомните: СОМ- интерфейс — это просто указатель на С++-интерфейс. Более подробно мы обсудим это чуть позже.

Интерфейс IUnknown выполняет две функции. Первая состоит в том, чтобы обеспечить стандартный способ запроса определенного интерфейса данного компонента его пользователем (клиентом). Эту возможность предоставляет метод QueryInterface. Вторая функция состоит в обеспечении способа управления временем жизни компонента извне. Интерфейс IUnknown предоставляет два метода (AddRef и Release), обеспечивающих управление временем жизни экземпляра компонента. Приведем определение IUnknown.

	class IUnknown
	{
	public:
	   virtual HRESULT QueryInterface(REFID riid, void** ppv)=0;
	   virtual ULONG AddRef () = 0;
	   virtual ULONG Release() = 0;
	};


# Интерфейс IDispatch

http://mf.grsu.by/UchProc/konspekt/com/ch05/ch01

Экспортирует объекты, методы и свойства программам и прочим приложениям, которые поддерживают "автоматизацию".
КОМ-компоненты содержат в себе реализованный IDispatch интерфейс, чтобы клиенты поддерживающшие "Автоматизацию" могли бы иметь доступ к ним.

Exposes objects, methods and properties to programming tools and other applications that support Automation.
COM components implement the IDispatch interface to enable access by Automation clients, such as Visual Basic.

Основной функцией интерфейса IDispatch является метод Invoke(). Когда клиент получает указатель IDispatch на сервер автоматизации, он может вызвать метод Invoke() для выполнения определенных методов на сервере. Параметр DispID этого метода содержит число, называемое идентификатор диспетчера (dispatch ID), который показывает, какой метод должен быть вызван на сервере. Параметр IID не используется. Параметр LocaleID содержит информацию о языке. Параметр Flags определяет, как этот метод будет вызван: как обычный либо для получения или установки свойств. Свойство Params содержит указатель на массив TDispParams, который содержит параметры, переданные этому методу. Параметр VarResult ? это указатель на OleVariant, который может содержать возвращаемое значение вызываемого метода. Параметр ExcepInfo является указателем на запись TExcepInfo, которая содержит информацию об ошибке, если метод Invoke() возвращает значение DISP_E_EXCEPTION. И наконец, если метод Invoke() возвращает значение DISP_E_TYPEMISMATCH или DISP_E_PARAMNOTFOUND, то параметр ArgError ? указатель на целое число ? будет содержать индекс некорректного параметра в массиве Params.

Метод GetIDsOfNames() интерфейса IDispatch вызывается для получения идентификатора диспетчера одного или нескольких методов по строкам имен этих методов. Параметр IID этого метода не используется, параметр Names указывает на массив имен методов типа PHideChar.

////////////////////////////////////////////////////////////////

https://all4study.ru/oot/interfejsy-avtomatizacii-dispinterfejsy.html

В блоке System Delphi объявлен также и IDispatch интерфейс, предназначенный для поддержки объектов автоматизации (Automation). Таким образом, любое приложение, предоставляющее свои внутренние методы другим приложениям, может осуществлять это через этот интерфейс.

Работает IDispatch интерфейс медленнее обычных. С его помощью можно обращаться

Диспинтерфейсы

IDispatch — это обычный интерфейс, реализованный с помощью VMT таблицы указателей на его методы. Его основной особенностью является наличие метода Invoke, используемого для вызова других методов интерфейса. Для обеспечения этого определяются специальные Dispatch интерфейсы, для реализации которых VMT таблица не используется. Их часто называют диспинтерфейсами (Dispinterface). Вызов их методов осуществляется с помощью уникального целочисленного идентификатора DispID, присваиваемого методам и свойствам диспинтерфейсов.

Таким образом, диспинтерфейс определяет методы и свойства, которые объект Automation выполняет через этот интерфейс, а вызов диспинтерфейса осуществляется с помощью метода IDispatch.Invoke — метода времени выполнения.
Объявление типа диспинтерфейса имеет следующий синтаксис:

Туре <имя интерфейса >=Dispinterface
[‘{GUID}’]	//Global Unique IDentifier
<Определение интерфейса> //Объявление методов и свойств
End;

Примечания:
• Объявление диспинтерфейсов похоже на объявления простых интерфейсов, но не может содержать предка в своем объявлении.
• Диспинтерфейсы имеют тот же GUID, что и IDispatch интерфейсы.
• Классы не реализуют диспинтерфейсы.
• Объявление методов и свойств должно сопровождаться командой DispID с указанием целочисленной константы, которая должна быть уникальной в пределах объявления интерфейса. При самостоятельном указании константы следует использовать положительные значения. Отрицательные значения зарезервированы Windows.
• Свойства, параметры и типы результатов методов должны быть: Byte, Currency, Real, Double, Longlnt, Integer, Single, Smalllnt, AnsiString, WideString, TDateTime, Variant, OleVariant, WordBool, интерфейсный тип.
• Свойства интерфейса Dispatch не включают команд доступа, но они могут быть объявлены как ReadOnly или WriteOnly. Свойства-массивы могут быть объявлены как Default. Все опции указываются через разделитель ;.
• Свойства и методы могут быть указаны в определении диспинтерфейса вперемежку друг с другом.

Туре IStringsDisp=Dispinterface
[‘{EE05DFE2-5549-11D0-9EA9-0020AF3D82DA}’]
Property ControlDefault[Index: Integer]: OleVariant DispID 0; Default;
Function Count: Integer; DispID 1;
Property Item [Index: Integer]: OleVariant DispID 2;
Procedure Remove(Index: Integer); DispID 3; End;

Вызов методов диспинтерфейса с помощью метода Invoke несколько быстрее, чем при использовании переменной типа Variant, поскольку не требуется выяснения имени нужного метода, вследствие использования DispID.



# ЦИКЛ СОБЫТИЙ / Главный Цикл обработки Сообщений в ОС Windows
https://ru.wikipedia.org/wiki/%D0%A6%D0%B8%D0%BA%D0%BB_%D1%81%D0%BE%D0%B1%D1%8B%D1%82%D0%B8%D0%B9

Помимо ввода-вывода в Windows реализован цикл событий для графических приложений. «Сердцем» таких приложений является функция WinMain(), которая вызывает GetMessage() в цикле. GetMessage() блокируется, пока не поступит какое-либо событие (также есть PeekMessage(), как неблокирующая альтернатива). Далее после небольшой обработки вызывается DispatchMessage(), которая передаёт сообщение о событии надлежащему обработчику, также известному как WindowProc. Сообщения, для которых не зарегистрирован обработчик передаются обработчику по-умолчанию (DefWindowProc)


# git / ГИТ: СТРАТЕГИИ СЛИЯНИЯ

https://habrahabr.ru/post/195674/

https://webhamster.ru/mytetrashare/index/mtb0/1403174393wno3ejl1g3





# МНОГОПОТОЧНОСТЬ В С++11:

BO QuaN -  https://www.youtube.com/watch?v=LL8wkskDlbs

https://habrahabr.ru/post/182610/



# QT - СИГНАЛЫ И СЛОТЫ:

В программировании графического интерфейса, когда мы меняем один виджет, мы часто хотим что бы другой виджет получил об этом уведомление. В общем случае, мы хотим что бы объекты любого типа могла общаться с другими. Например, если пользователь нажимает кнопку Закрыть, мы вероятно хотим что бы была вызвана функция окна close().
Другие библиотеки добиваются такого рода общения используя обратный вызов. Обратный вызов это указатель на функцию, таким образом, если мы хотим что бы функция уведомила нас о каких-нибудь событиях, мы передаем указатель на другую функцию (обратновызываемую) этой функции. Функция в таком случае делает обратный вызов когда необходимо. Обратный вызов имеет два основных недостатка. Во-первых, он не является типобезопасным. Мы никогда не можем быть уверены что функция делает обратный вызов с корректными аргументами. Во-вторых, обратный вызов жестко связан с вызывающей его функцией, так как эта функция должна точно знать какой обратный вызов надо делать.

Сигналы и слоты

В Qt используется другая техника — сигналы и слоты. Сигнал вырабатывается когда происходит определенное событие. Слот это функция, которая вызывается в ответ на определенный сигнал. Виджеты Qt имеют много предопределенных сигналов и слотов, но мы всегда можем сделать дочерний класс и добавить наши сигналы и слоты в нем.

Сигналы и слоты

Механизм сигналов и слотов типобезопасен. Сигнатура сигнала должна совпадать с сигнатурой слота-получателя. (Фактически слот может иметь более короткую сигнатуру чем сигнал который он получает, так как он может игнорировать дополнительные аргументы). Так как сигнатуры сравнимы, компилятор может помочь нам обнаружить несовпадение типов. Сигналы и слоты слабо связаны. Класс, который вырабатывает сигнал не знает и не заботится о том, какие слоты его получат. Механизм сигналов и слотов Qt гарантирует, что если мы подключим сигнал к слоту, слот будет вызван с параметрами сигнала в нужное время. Сигналы и слоты могут принимать любое число аргументов любого типа. Они полностью типобезопасны.
Все классы, наследуемые от QObject или его дочерних классов (например, QWidget) могут содержать сигналы и слоты. Сигналы вырабатываются объектами когда они изменяют свое состояние так, что это может заинтересовать другие объекты. При этом он на знает и не заботится о том что у его сигнала может не быть получателя. 
Слоты могут быть использованы для получения сигналов, но они так же нормальные функции-члены. Так же как объект не знает ничего о получателях своих сигналов, слот ничего не знает о сигналах, которые к нему подключены. Это гарантирует что полностью независимые компоненты могут быть созданы с помощью Qt.
Мы можем подключать к одному слоту столько сигналов, сколько захотим, также один сигнал может быть подключен к стольким слотам, сколько необходимо. Так же возможно подключать сигнал к другому сигналу (это вызовет выработку второго сигнала немедленно после появления первого).
Сигналы и слоты вместе составляют мощный механизм создания компонентов.


# DUMP - DMP dump analysis

-  Windows Debugging and Troubleshooting
-  HOW TO ANALYSE MINIDUMP INFO BY DEBUGGING TOOL.avi
	
https://www.youtube.com/watch?v=2rGS5fYGtJ4&t=1003s

https://www.youtube.com/watch?v=P1O9dg9CCS0


# My-Notes

Все, что вы хотели знать о сексе, но боялись спросить

http://gidonline.club/2016/02/vse-chto-vy-xoteli-znat-o-sekse-no-boyalis-sprosit/


Алан Пол - ОБЪЕКТНО-ОРИЕНТИРОВАННОЕ ПРОГРАММИРОВАНИЕ НА C++ 
  
http://fis.tntu.edu.ua/data/elibrary/3/oop_cpp.pdf


  С++ библиотеки ВСЕХ мастей и на ВСЕ случаи жизни
  
https://github.com/fffaraz/awesome-cpp#bittorrent


  Е. В. Пышкин - Структуры данных и алгоритмы: реализация на С/С++
  
http://kspt.icc.spbstu.ru/media/files/people/pyshkin/books/AlgDataStrA5_2009.pdf




My first Project on Github


Простой нагрузочный тест с Apache JMeter / Хабрахабр


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

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
	
	3) 
	class A {};
	
	void main()
	{
	  A a = new A();
	}
	
	// НЕ ХВАТАЕТ оператора   delete a;

	*/



//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

https://stackoverflow.com/questions/39383936/correctly-overload-assignment-operator-for-classes-with-pointer-members


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


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


	#include <iostream>
	
	struct Base
	{
		virtual int f() { return 1; }
	};
	
	struct Derived : Base
	{
		int f() { return 2; }
	};
	
	/* // ORIGINAL
	int main()
	{
		Derived d;
		Base* b = &d;
		std::cout << b->f() << std::endl;
		return 0;
	}
	*/
	
	/* ERROR
	int main()
	{
		Derived d;
		Base* b = &d;
		std::cout << b->f() << std::endl;
		delete b;
		return 0;
	}
	*/
	
	/*
	int main()
	{
		Base* b = new Derived();
		std::cout << b->f() << std::endl;
		delete b;
		return 0;
	}
	*/






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




