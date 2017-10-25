
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

# CreateThread <-> _beginthreadex

http://forum.vingrad.ru/forum/topic-47554.html

CreateThread - чисто Win32Api'шная функция, а вот
_beginthread - функция библиотеки CRT, НЕ кроссплатформенна, но приспособленна для работы с С, т.е. она делает дополнительные манипуляции, что бы стандартные библиотеки корректно работатли (+ вызывает CreateThread ) .
В общем если пишешь на С, то лучше пользоваться вторым.
Рихтер в статье CreateThread vs. _beginthread очень подробно описывает почему _beginthread предпочтительнее. Она создает Thread Local Storage (TLS), где переопределены, в частности, все глобальные константы, к-рые ф-ции CRT-библиотеки юзают. Например, такая как errno. 
Именно TLS - гарантия, что ф-ции CRT-библиотеки будут работать корректно. 

The C runtime library was delivered in a UNIX context, in which there is no distinction between processes and threads. In the Windows context, many threads can be executing in a single address space. 
Microsoft has provided an alternative function to CreateThread, called _beginthreadex, to be used with the programs that use multiple threads at the same time they use the C runtime library. The problem occurs with any globally accessible variable used by this library ( there are several of them ). The Microsoft solution is to have the C runtime library provide a copy of each of these variables for each thread. Then, when a thread interacts with the runtime library, variables are shared only between the runtime code and the thread, not among all threads. The _beginthreadex function creates the copy for a thread in conjunction with an embedded call to CreateThread.


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

Рихтер Дж., Назар К. - Windows via C C++. Программирование

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




