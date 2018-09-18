#  QT:

## 20 Qt Questions
https://www.wisdomjobs.com/e-university/qt-qml-interview-questions.html01

### QMAKE
утилита (Qt-шный аналог CMAKE) для генерации Make-файлов, которые нужны для описания процесса построения сполняемых программ из исходных кодов

### MOC
утилита, переводящая код, написанный на Qt, в код на чистом C++

### QML
Это Qt Meta Language или Qt Modelling Language язык для описания интерфейсов, с использованием toolkit-а QtQuick is a toolkit for QML, который и позвляет писать графические интерфейсы дя Qt на QML

### Q_GADGET 
https://habr.com/post/307816/

Макрос Q_GADGET позволяет
- (+) не требует наследования от QObject
- (+) боле легковестный
- (-) он БЕЗ поддержки механизма сигналов и слотов
- (-) можно использовать QMetaObject c некоторыми ограничениями, а именно:
###### Q_ENUM
###### Q_PROPERTY
###### Q_INVOKABLE - Как плохая, но всё же альтернатива сигналам и слотам


### SIGNALS AND SLOTS

http://blog.kislenko.net/show.php?id=1308

https://www.youtube.com/watch?v=sA2PX_79NkQ

# Особенности работы механизма сигналов и слотов следующие:
- сигналы и слоты не являются частью языка C++, поэтому требуется запуск дополнительного препроцессора перед компиляцией программы;
- отправка сигналов происходит медленнее, чем обычный вызов функции, который производится при использовании механизма функций обратного вызова;
- существует необходимость в наследовании класса QObject;
- в процессе компиляции не производится никаких проверок: имеется ли сигнал или слот в соответствующих классах или нет; совместимы ли сигнал и слот друг с другом и могут ли они быть соединены вместе. Об ошибке можно будет узнать лишь тогда, когда приложение будет запущено. Вся эта информация выводится на консоль, поэтому, для того чтобы увидеть ее в Windows, в проектном файле необходимо в секции CONFIG добавить опцию console.

#  Что такое Сигнал:
http://blog.kislenko.net/show.php?id=1308&s=0

Сигналы (signals)
- это методы, которые в состоянии осуществлять пересылку сообщений.
- Сигналы определяются в классе, как обычные методы, но без реализации.
- Выслать сигнал можно при помощи ключевого слова emit. 
- emit – пустой макрос. Он даже не парсится MOC. Другими словами, emit опционален и ничего не значит (подсказка для разработчика).

#  Что такое Слот:
http://blog.kislenko.net/show.php?id=1308&s=0

Слоты (slots) 
- это методы, которые присоединяются к сигналам. По сути, они являются обычными методами. 
- Основное их отличие состоит в возможности принимать сигналы. Они определяются в классе как <b>private slots:</b>, <b>protected slots:</b> или <b>public slots</b>: ПО УМОЛЧАНИЮ СЛОТЫ  <b>PRIVATE</b>
- В слотах нельзя использовать параметры по умолчанию, например slotMethod (int n = 8)
- и нельзя определять слоты как static.

# Важно
в этом случае код после ключевого слова emit продолжает выполнение немедленно, а слоты будут выполнены позже.
Если несколько слотов подключены к одному сигналу, слоты будут выполнены один за другим в произвольном порядке после выработки сигнала.

Connect (Метод соединения объектов)
Соединение объектов осуществляется при помощи статического метода connect(), который определен в классе QObject.

В общем виде, вызов метода connect() выглядит следующим образом:
```
QObject::connect(const QObject* sender, 
const char* signal,
const QObject* receiver,
const char* slot,
Qt::ConnectionType type = Qt::AutoConnection
);
```

Ему передаются пять следующих параметров:
- sender — указатель на объект, отправляющий сигнал;
- signal — это сигнал, с которым осуществляется соединение. Прототип (имя и аргументы) метода сигнала должен быть заключен в специальный макрос SIGNAL(method());
- receiver — указатель на объект, который имеет слот для обработки сигнала;
- slot — слот, который вызывается при получении сигнала. Прототип слота должен быть заключен в специальном макросе SLOT(method());
- type — управляет режимом обработки. Имеется три возможных значения:

### ConnectionType type, 3 возможных значения:


| Connections          | Description                                                             |
| -------------------- |:-----------------------------------------------------------------------:|
| Qt::DirectConnection | сигнал обрабатывается сразу вызовом соответствующего метода слота       |
| Qt::QueuedConnection | сигнал преобразуется в событие и ставится в общую очередь для обработки |
| Qt::AutoConnection   | это автоматический режим, который действует следующим образом           |


- если отсылающий сигнал объект находится в одном потоке с принимающим его объектом, то устанавливается режим Qt::DirectConnection - CИНХРОННЫЙ Вариант,
- в противном случае — режим Qt::QueuedConnection - АСИНХРОННЫЙ. Этот режим (Qt::AutoConnection) определен в методе connection() по умолчанию.


######  Наследование класса от QObject-а.
Нужно в иерархии наследования выставлять его первым.


#  QML + CPP:
https://habrahabr.ru/post/140899/

- Первый вариант:

cpp: QDeclarativeView -> SetSource(some.QML) -> RootObject -> RootContext()->SetContextProperty("QtFun", this);

qml: QtFun.function_name();

h: Q_INVOCABLE function_name(); 

- Второй Вариант

...

...

	class TestClass : public QObject
	{
		Q_OBJECT
			Q_PROPERTY(int someProperty READ getSomeProperty WRITE setSomeProperty NOTIFY somePropertyChanged)
	public:
		explicit TestClass(QObject *parent = 0);
		int getSomeProperty()const;
		void setSomeProperty(const int &);
	private:
		int someProperty;
	signals:
		void somePropertyChanged();
		public slots:
	};
	int TestClass::getSomeProperty()const
	{
		qDebug() << "I'm getter";
		return someProperty;
	}
	void TestClass::setSomeProperty(const int &i)
	{
		qDebug() << "I'm setter";
		someProperty = i;
	}
	

- emit - используется для высылки SIGNAL-а.
###### - SLOT (по умолчанию private)
могут быть объявлены как virtual, public и private
###### Соадинение СИГНАЛА с ВИРТ. Слотом МЕДЛЕННЕ, чем с Невритуальным.
- События могут обрабатываться лишь одним методом, а сигналы многими слотами

###### 2) Разница между Q_INVOCABLE и SLOT-ом ?

Q_INVOCABLE - привязывается как обычная колбэчная функция, с одним методом, вызываемом при "emite", для данной функции. Функции С++ вызывающиеся в QML.

SLOT - может быть любоче число сигналов, как и на любой сигнал можно повесить любое число слотов.


###### 3) QObject это базовый класс для всех Qt классов. 

###### 4) Для чего нужен макрос Q_OBJECT

Q_OBJECT макрос используется для включения мета объектных функций в классах и на этапе компиляции


###### 5) Что такое MOC

Мета-объектный компилятор, moc, - программа, которая обрабатывает расширения C++ от Qt.
moc работает как препроцессор который преобразует применения макроса Q_OBJECT в исходный код C++

Инструмент moc читает заголовочный файл C++. Если он находит одно или более объявлений классов, которые содержат макрос Q_OBJECT, то он порождает файл исходного кода C++, содержащий мета-объектный код для этих классов. Кроме всего прочего, мета-объектный код требуется механизму сигналов и слотов, информации о типе времени выполнения и системы динамических свойств.

Файл исходного кода C++, сгенерированный moc, должен компилироваться и компоноваться с помощью реализации класса.

Если вы используете qmake для создания своих make-файлов, в правила сборки будет включен вызов moc когда это необходимо, поэтому вам не нужно использовать moc непосредственно. Дополнительную информацию по moc смотрите в статье Почему Qt не использует шаблон для сигналов и слотов?



Клиент тсерверное приложение
- контроль целостности файлов / папок / ключей реестра
- Политики пользователей
- 

Qt сначала писалось на Виджетах

Осовременить графически:
Если нужен более интересный дизайн интерфейса, то идём в QML
Много динамики: Опасити менялось, что-то пропадало, на его месте что-то появлялось.
изменение цвета с одного на другой, вылетающие, двигающиеся элементы, почти анимация присуствовала.
Мы смотрели на решения от конкурентов думали как повотрить то или инове поведение, что 
хочется перенять из интерфейса того

Вёрстка на QML

Прямое соответсвие Виджетов и MFC-шных классов


# MFC
https://www.go4expert.com/forums/mfc-interview-questions-t724/


# Назовите 10 MFC-классов ?

# Назовите 10 QML-классов ?
CheckBox
DialogBox
 Slider
 Rectangle
 Column 
 Button 
 Text
 
 MouseArea
 Component

ListView
GridView
 
# Qt / QML:


# Как передавали данные в QML из C++ ?

# Чем отличается механизм Q_INVOCABLE и SLOT ?

Механизмы абсолютно разные !

# Зачем нужен макрос Q_OBJECT ?


Внутри Q_OBJECT:
- QMetaObject
- qt_metacall
- META_MACROS
- Q_MOC_RUN
- signals, slots, Q_PROPERTY, и прочее


	#define Q_OBJECT \
	public: \
		Q_OBJECT_CHECK \ QT_WARNING_PUSH \ Q_OBJECT_NO_OVERRIDE_WARNING \
		static const QMetaObject staticMetaObject; \
		virtual void *qt_metacast(const char *); \
		virtual int qt_metacall(QMetaObject::Call, int, void **); \
		QT_TR_FUNCTIONS \
	private: \
		Q_DECL_HIDDEN_STATIC_METACALL static void qt_static_metacall(QObject *, QMetaObject::Call, int, void **); \
		struct QPrivateSignal {}; \
		QT_ANNOTATE_CLASS(qt_qobject, "")
		
	#ifndef QT_NO_META_MACROS
	
	#else // Q_MOC_RUN
	#define slots slots
	#define signals signals
	#define Q_SLOTS Q_SLOTS
	#define Q_SIGNALS Q_SIGNALS
	#define Q_CLASSINFO(name, value) Q_CLASSINFO(name, value)
	#define Q_INTERFACES(x) Q_INTERFACES(x)
	#define Q_PROPERTY(text) Q_PROPERTY(text)
	#define Q_PRIVATE_PROPERTY(d, text) Q_PRIVATE_PROPERTY(d, text)
	#define Q_REVISION(v) Q_REVISION(v)
	#define Q_OVERRIDE(text) Q_OVERRIDE(text)
	#define Q_ENUMS(x) Q_ENUMS(x)


# Как работает класс QObject / Макрос Q_OBJECT ?

На первом шаге запускается  MOC-компилятор. Meta Object Compiler, он у всех классов берёт и смотрит ПЕРВЫЙ класс среди базовых это  QObject или НЕ_QObject и далее действует, и внутри класса уже он же смотрит чтобы в "шапке" класса стоял Q_OBJECT, иначе он не отработает и пойдут ошибки компиляции.

# Возможно ли МНОЖЕСТВЕННОЕ НАСЛЕДОВАНИЕ от класса QObject ?

Нельзя и никаким образом. MOC просто не понимает классов, наследованных дважды от QObject при любой глубине дерева наследования 

# Важен ли порядок при наследовании от QObject ?
https://www.linux.org.ru/forum/development/814529

Должен стоять ПЕРВЫМ наследником, среди списка наследников:

moc просто не понимает классов, в которых QObject стоит не на первом месте (в качестве базового класса)

	class classA : public QObject, classV, classC
	{
	  Q_OBJECT

	  classA();
	  ...
	};



# Какой 5-тый параметр у функции Connect(Object, SIGNAL, Object, SLOT, SynhroniousAsync) ? (по умолчанию стоит Auto Connection)
# После соединения SIGNAL-a и SLOT-а, Как будет вызвана SLOT(func) функция, которая вызовется через emit СИНХРОННО или АСИНХронно ?

- Зависит всё от следующего: Работает ли всё в одном потоке или нескольких.

А именно: Auto Connection - выставлен по умолчанию => в ОДНОМ потоке будет СИНХронный вызов.


# Два раза вызвали Connect с одинаковыми параметрами - Что будет после emit SIGNAL ?

Двойной вызов функции Слота. ПО УМОЛЧАНИЮ !!! 	А так этот момент и задаётся в функции Connect 5-тым параметром.


Direct / Queued

https://stackoverflow.com/questions/38376840/qt-signals-and-slots-direct-connection-behaviour-in-application-with-a-single-th

Let´s get this out of the way before diving into the basics.

- If it is a direct connection, your code is ALWAYS executed on a single thread, regardless as to whether or not the slot is running on a different thread. (In most cases a VERY BAD idea)
- If the connection is queued and the slot is running inside the same thread, it acts exactly like a direct connection. If the slot is running on a different thread, the slot will execute within its proper thread context that it is running in, so making the code execution multi-threaded.
- If the connection is auto which is the default, for a good reason, then it will chose the appropriate connection type.

- Now there is a way to force your code execution to jump into a slot in another thread, that is by invoking a method:

QMetaObject::invokeMethod( pointerToObject*, "functionName", Qt::QueuedConnection);

https://stackoverflow.com/questions/41299480/qt-4-8-connection-behavior-between-two-signals-and-one-slot-from-different-thr

- If the type is Qt::DirectConnection, the second signal is always emitted from the thread that emitted the first signal.
- if the type is Qt::QueuedConnection, the second signal is always queued to be invoked when control returns to the event loop of the receiver object's thread.
- If the type is Qt::AutoConnection, the connection type is resolved when the signal is emitted and the thread of the sending object is ignored.

###### If the receiver object lives in the same thread where the first signal is emitted, this will be the same as using Qt::DirectConnection.
###### Otherwise, this will be the same as using Qt::QueuedConnection.

http://www.doc.crossplatform.ru/qt/4.6.x/threads-qobject.html

Соединение сигналов и слотов между потоками

Qt поддерживает следующие типы соединений сигнал-слот:

- Автоматическое соединение (Auto Connection) (по умолчанию) Поведение такое же, как и при прямом соединении, если источник и получатель находятся в одном и том же потоке. Поведение такое же, как и при соединении через очередь, если источник и получатель находятся в разных потоках.
- Прямое соединение (Direct Connection) Слот вызывается немедленно при отправке сигнала. Слот выполняется в потоке отправителя, который не обязательно является потоком-получателем.
- Соединение через очередь (Queued Connection) Слот вызывается, когда управление возвращается в цикл обработки событий в потоке получателя. Слот выполняется в потоке получателя.
- Блокирующее соединение через очередь (Blocking Queued Connection) Слот вызывается так же, как и при соединении через очередь, за исключением того, что текущий поток блокируется до тех пор, пока слот не возвратит управление. Замечание: Использование этого типа подключения объектов в одном потоке приведет к взаимной блокировке.
- Уникальное соединение (Unique Connection) Поведение такое же, что и при автоматическом соединении, но соединение устанавливается только если оно не дублирует уже существующее соединение. т.е., если тот же сигнал уже соединён с тем же самым слотом для той же пары объектов, то соединение не будет установлено и connect() вернет false.

Это можно изменить, передав дополнительный аргумент в connect(). Помните, что использование прямых соединений, когда отправитель и получатель "живут" в разных потоках, опасно в случае, если цикл обработки событий выполняется в потоке, где "живет" приемник, по той же самой причине, по которой небезопасен вызов функций объекта, принадлежащего другому потоку.

QObject::connect() сама по себе потокобезопасна.




```
new [нью] - новый
old [олд] - старый
size [сайз] - размер
next [некст] - следующий / Далее
back [бэк] - назад / спина
previous [привэос] - предыдущий
data [дэйта] - данные
add [эд] - добавить
delete [делит] - удалить
step [стэп] - шаг
open [оупэн] - открыть
close [клоуз] - закрыть
save [сейв] - сохранить
load [лоад] - загрузить
option [опшн] - настройка, опция, вариант
propertie [проперти] - свойство
download [даунлоад] - скачать
upload [аплоад] - загрузить

who ? [ху] - кто
what ? [уот] - что
when ? [уэн] - когда
why ? [уай] - полчему
how ? [хау] - как
whom ? [хум] - кому
about [эбаут] - о (чём-то / ком-то)

and [энд] - и
bool [бул] - булева
break [брэйк] - разбить
case [кейс] - случай
catch [кеч] - поймать / ловить
character [чарактэр] - символ, персонаж
cast [каст] - перевести (выполнить перевод из одного сосот. в другое)
continue [континью] - продолжить
default [дефолт] - стандартный / по умолчанию
delete [делит] - удалить
do [ду] - делать
double [дабл] - двойной / удвоенный
dynamic [дайнэмик] - динамический
else [элс] - иначе
export [экспорт] - экспортировать
extern [экстерн] - внешний
false [фолс] - ЛОЖЬ
float [флоат] - 
for [фор] - для
go to [гоу ту] - идити в
if [иф] - если
integer [интеджер] - целое (всмысле не дробное, про число)
name [нейм] - имя
space [спейс] - пробел, пространство
new [нью] - новый
pointer [поинтер] - указатель
private [прайвет] - приватный
protected [протектед] - защищённый
public [паблик] - публичный
return [ретёрн] - вернуть
short [шорт] - короткий
sign [сайн] - знак
signed [сайнт] - знаковый
size of [сайз оф] - размер (чего-то)
structure [страчер] - структура
switch [свич] - переключиться
template [темплейт] - шаблон
this [Зис] - это
thread [тред] - поток
local [локал] - локал
throw [фроу] - бросать
true [тру] - ИСТИНА
try [трай] - попытаться
type [тайп] - тип
union [юнион] - объединение
unsigned [ансайнт] - беззнаковый
use [юз] - использовать
using [юзинг] - используя
while [уайл] - во то время как

function [фанкшн] - функция
jump [джамп] - прыгать
big [биг] - большой
small [смол] - маленький
little [литл] - маленький
edit [эдит] - менять
deny [денай] - отменить
enable [энейбл] - задействовать
deprecated [деприкэйтед] - 
call [кол] - вызвать, вызов
substract [сабстракт] - 
multiply [мультиплай] - 
erase [ирэйз] - 

add [эд] - 
insert [инсерт] - вставить
select [селект] - выбирать
new [нью] - создать

complete [комплит] - 
incomplete [инкомплит] - 
different [дифферент] - 
difference [дифференс] - 
algorythm [элгоритм] - 
compare [кмпэар] - 
read [рид] - 
write [райт] - 
access [эксэс] - 
word [ворд] - 
last [лэст] - 
first [фёрст] - 
begin [бегин] - 
end [энд] - 
create [криэйт] - 
destroy [дестрой] - 
total [тотал] - 
location [локэйшн] - 
recent[рисэнт] - 
print [принт] - 
all [ол] - 
both [боуф] - 
side [сайд] - 
letter [лэттэр] - 
preview [привью] - 
attach [эттач] - вложение
share [шэр] - 
Save [сэйв] - 
load [лоад] - 
change [чейндж] - 
support [сапорт] - 
tool [тул] Инструмент - 
Check [чек] - 
Paste [пэйст] - Вставить
Cut [кат] - Вырезать
Font [фонт] - Шрифт
Color [колор] - Цвет 
Show [шоу] - 
Increase [инкриз] - 
Decrease [дериз] - 
Change [чейндж] - 
Find [файнд] - 
Replace [реплэйс] - 
Select [селект] - 
Shape [шэйп] - 
Blank [блэнк] - Пустая 
Link [линк] - Ссылки
Header [хэдэр] - заголовок
Equation [экуэйжн] - 

Margin [маргин] - Поле
Page [пэйдж] - Страница
Line [лайн] - строка
Column [колам] - столбец
Column [колам] - Колонка
Even [ивэн] - Четная
Odd [од] - Нечетная
Left [лэфт] - Слева
Right [рфйт] - Справа
Before [бефор] - До
After [афтэр] - После 
Position [позишн] - Положение
Bring [бринг] - принести
Forward [форворд] - вперед
Backward [бэкворд] - назад 
Send [сэнд] - отправить 
Pane [пээн] - Область
Align [элайн] - Выровнять
Rotate [ротэйт] - Повернуть
angle [энгл] - угол
Mark [марк] - Пометить
Entry [энтри] - элемент
Note [ноут] - Показать сноски
Style [стайл] - Стиль
List [лист] - 
Rule [рул] - Правила
Field [фиилд] -  поле
Merge [мёрдж] - объединить
Split [сплит] - Разделить 

help [хэлп] - помогите, помогать, помощь
tab [тэб] - вкладка
home [хоум] - дом
push [пуш] - нажать, давить
page [пэйдж] - страница
reference [референс] - ссылка
mail [мэйл] - почта
view [вью] - вид, представление
review [ревью] - обзор
title [тайтл] - надпись
point [поинт] - точка
button [баттон] - кнопка
box [бокс] - 
scroll [скрол] - Ползунок
scroll box [скрол бокс] - Ползунок прокрутки
zoom [зум] - прибилжать
send [сэнд] - отправлять
recieve [ресив] - получать
layout [лэйаут] - 
label [лэйбл] - надпись
save [сэйв] - сохранить
save as [сэйв эз] - сохранить как
open [оупен] - открыть
close [клоуз] - закрыть
info [инфо] - сведения
recent [рисэнт] - последние
print [принт] - печать
options [опшн] - параметры
exit [экзит] - Выход

Window [уиндоу] - окно
Comment [коммент] - Примечание, Комментарии
Change [чейндж] - 
Accept [эксэпт] - 
Protect [протэкт] - 
Block [блок] - 
Restrict [рестрикт] - 
Record [рекорд] - 
Security [секьюрити] - 
Drop [дроп] - 
Pick [пик] - 
Frame [фрэйм] - рамку 
Reset [рисэт] - 
Image [имэйдж] - 
Mode [моуд] - Режим 
Group [груп] - Группи
Schema [шэма] - Схема
Template [тэмплейт] - Шаблоны
Border [бордэр] - Границы
Pen [пэн] - перо
Style [стайл] - Стиль 
Weight [вэйт] - Толщина 
Height [хэйт] - Высота 
Widht [уидт] - Ширина 
Draw [дроу] - 
Table [тэйбл] - Нарисовать таблицуэ
Eraser [эрэйзр] - Ластик
Fit [фит] - Автоподбор
Align [элайн] - Выровнять 
Repeat [рипит] - Повторить 
Convert [ковёрт] - Преобразовать 
Adjust [эджаст] - 
Background [бэкграунд] - 
Reset [рисэт] - 
Compress [компрэс] - 
Wrap [урэп] - 
Arrange [эррэйндж] - 

Layout [лэйаут] -  Макет 
Crop [кроп] - Обрезка

Forward [форвуард] - 
Backward [бэквуард] - 
Fill [фил] - 
Outline [аутлайн] - 
Direction [дайрекшн] - 
Shape [шэйп] - Фигуры
Picture [пикчэр] - Рисунок
Axe [экс] - Оси
Wall [уол] - Стенка
Area [эриа] - Область
Background [бэкграунд] - Фон
Up [ап] - 
Down [даун] - 
under [андэр] - 
over [оувэр] - 
Error [эррор] - 
exception [эксэпшн] - 

point [поинт] - 
line [лайн] - 
polyline [полилайн] - 
ellipse [эллипс] - 
circle [сиркл] - 
rectangle [рэктэнгл] - 
square [скуэар] - 
triangle [трайэнгл] - 
angle [энгл] - 
side [сайд] - 
polygon [полигон] - 

select [селект] - 
insert [инсерт] - 
update [апдейт] - 
delete [делит] - 

include [инклуд] - 
import [импорт] - 
return [ретёрн] - 

memory [мэмори] - 
drie [драйв] - 
sound [саунд] -
unique [юник] - 
description [дескрипшн] - 
display [дисплэй] - 
launch [лаунч] - 
crash [скэр] - 
fall [фол] - 
settings [сэттингз] - 
amount [эмаунт] - 
must [маст] - 
disable [дисэйбл] - 
prefear [прифэар] - 
count [каунт] - 
engine [энджин] - 
core [кор]
current [каррэнт]
device [девайс]
brows [брауз]
advanced [эдвансд] - дополнительно
direct [дайрект]
custom [кастом] - определённая
сompatibillity [компатибилити] - 
show [шоу] - 
with [уизтх] -
specify [специфити] - 
present [презент]
allow [эллау]
any [эни]


```



FREE ICONS

https://www.1001freedownloads.com/free-clipart/icon-set-player


ENGLISH IN IT-WEB-DEVELOPMENT-APPS-GRAFICAL-INTERFACE:

http://wordexpert.ru/forum/viewtopic.php?id=1526


	bool isRequestWithNewDogInfoCorrect = sendReqWith_New_DogovorInfoToService();
	

2.3. Исполнитель направляет Заказчику по два экземпляра Акта в срок до 5 (Пяти) рабочих дней, следующих за днем окончания оказания
услуг. К Акту прилагаются Отчет об оказанных услугах и счет на оплату. До предоставления указанных документов Заказчик вправе не производить окончательный расчет с Исполнителем.

ВОПРОС: КАК ЭТО РЕШАЕТСЯ НА ПРАКТИКЕ. ЧЕЛОВЕК РАБОТАЕТ ПО ТЕКУЧКЕ. 
НЕ ВСЕГДА РЕШАЕТСЯ ТО, ЧТО СДЕЛАНО, И Т.Д. КАК СОСТАВЛЯЮТСЯ АКТЫ ПРИЁМКИ ?


перечнем объема и срока необходимых доработок. Устранение недостатков результатов оказанных услуг осуществляется силами Исполнителя и за его счет.

НА СКОЛЬКО НА ЭТО МОЖНО ОРИЕНТИРОВАТЬСЯ В СЛУЧАЕ РАБОТЫ РЕАЛЬНОГО РАЮОТКНИКА
ИЛИ ЭТО УКАЗАНО В ДОГОВОРЕ ЧИСТО ДЛЯ ФОРМЫ ?

3.2. Стоимость каждого вида Услуг по настоящему Договору указывается Сторонами в соответствующей спецификации к настоящему Договору. Стоимость Услуг является твердой и

КОГДА БУДЕТ СПЕЦИФИКАЦИЯ ? ПРЕДЛОЖЕНИЕ ?


3.4. Оплата производится в порядке, указанном в соответствующей спецификации к настоящему Договору.

СПЕЦИФИКАЦИЯ КАК ВЫГЛЯДИТ ?

4
− Назначает Менеджера проекта, который является ответственным представителем Исполнителя по вопросам, связанным с оказанием Услуг по настоящему Договору.

ИСПОЛНИТЕЛЬ ЭТО МЫ , ПОЧЕМУ МЫ КОГОТО НАЗНАЧАЕМ ?



	AnsiString UserCode = "24365";
	AnsiString sqlSelect =
		"select  USER_CODE, FIO"
		" from   USERS_INFORMATION"
		" where  USER_CODE = '" + UserCode + "'";
	TADOQuery *qw = BranchApi->dbGetCursor(res, sqlSelect);



	sommer_type.is_light = summer.type_id == 1;

	err = "";
	if (ser == "")
	  err += "Ошибка_1\n";
	if (num == "")
	  err += "Ошибка_2\n";


	st = st.IsEmpty() ? "0" : st; // error
	st = st.IsEmpty() ? AnsiString("0") : st; // no_error

	int count = sl->Count;
	if (count > 100)
		for (int i = count - 1; i >= 0; i--)
			Name = Name + " " + sl->Strings[i] + Separator;
	else
		for (int i = 0; i <= count - 1; i++)
			Name = Name + " " + sl->Strings[i] + Separator;
	

	#ifndef __FUNCTION_NAME__
	    #ifdef WIN32   //WINDOWS
	        #ifdef __BORLANDC__
	            #define __FUNCTION_NAME__   __FUNC__ // CPPBulder version
	        #endif
	        #ifdef _MSC_FULL_VER
	            #define __FUNCTION_NAME__   __FUNCTION__ // MSVS version
	        #endif
	    #else          //*NIX
	        #define __FUNCTION_NAME__   __func__
	    #endif
	#endif

	#define cb_get(cb)  (cb->ItemIndex != -1) ? (int)cb->Items->Objects[cb->ItemIndex] : -1
	#define cb_save(cb) (cb->ItemIndex != -1) ? (int)cb->Items->Objects[cb->ItemIndex] : -1
	#define cb_load(cb,idx) cb->ItemIndex = cb->Items->IndexOfObject((TObject*)idx)



https://i.snag.gy/nTPI3R.jpg

http://www.cyberforum.ru/cpp-beginners/thread2166498.html#post11986843


- Спроси про использование const в разных частях объявления функции.
- Чисто так, можешь спросить на тему того, что быстрее работает в Unix: потоки или процессы. Вопрос чуть спорный, но можешь сделать немного выводов.
- Спроси как человек относится к препроцессору, дай пару опасных макросов вроде a+b (ведь верным будет именно (a+b) ), попроси найти проблему.
- Да, попроси рассказать о ++, --, о результатах выполнения кода int i = 5; ++i + ++i;. Верным ответом будет: как компилятор захочет, какая будет фаза луны, 13, 14.
- Помучай по темплейтам, если З/П от 60к, то он должен хорошо их знать.
- Спроси про Boost, как он к нему относится, попроси не лукавить (скажет что-нибудь про 2-страничные ошибки — всё ок).
- Спроси как он относится к Qt.
- Вообще, на C++ столько ловушек, что ужас. У Страуструпа их не мало описано, поэтому можешь оттуда брать примеры и давать их. Даже если человек вспомнит ответы, это уже будет значить что он читал Страуструпа и понял всё, что там есть, а это огромный плюс.


# Temaplates:

	template<class T>
	void f(T arg)
	{
		printf("general call");
	}

	template<class T>
	void f(long arg)
	{
		printf("explicit call");
	}



	void main()
	{
	  int i = 0;
	  f(i); // "general call"
	}

# Как считать два байта числа?
https://toster.ru/q/489059

# Как выделяется память в классах?
https://toster.ru/q/488126

# Что означает конструкция float(&)() в параметре аргумента функции?
https://toster.ru/q/486095

Ссылка на функцию:

	#include <iostream>

	float testFunction1()
	{
	  std::cout << "testFunction1 is doing something" << std::endl;
	  return 1.49;
	}

	float test(float(&func)()) 
	{
	  return func();
	}

	int main() 
	{
	  std::cout << test(testFunction1) << std::endl;
	  return 0;
	}

# UML Design Patterns

https://www.researchgate.net/profile/William_Frakes/publication/235625572/figure/fig5/AS:299891864686597@1448511200888/Figure-5-A-UML-class-diagram-of-the-code-produced-by-the-ad-hoc-method.png

# COPY and SWAP Ideom (Deep Copy)

Если в классе имеется Указатель, то ПРАВИЛО трёх диктует нам, что
нам стоит переопределить оператор равно, копирующий конструктор и дестуркутор
для корректной реализации менеджмента динамически выделяемой памяти

- Основная Гарантия - ПАМЯТЬ НЕ УТЕЧЁТ !

operator= и контр_копии  отработают через std::copy Успешно

ПРОБЛЕМА:  new char; - дошли сюда и NEW бросило исключение:

Хоть утечки памяти и не произойдёт, НО this которое было на входе
в оператор присваивания и то, что стало на момент исключения изменено
(Есть способ просто  new (nothrow) char, НО он не сильно поможет)  


	class DynArray
	{
	private:
	  int m_size;
	  char* m_data;
	  
	public:
	  DynArray(int size = 0)
	  : m_size(size), m_data(m_size ? new char[m_size]() : 0)
	  {}

	  ~DynArray()
	  {
	    delete [] m_data;
	    m_data = 0;
	  }
	  
	  DynArray(const DynArray& that)
	  : m_size(that.m_size), m_data(m_size ? new char[m_size]() : 0)
	  {
	    std::copy(that.m_data, that.m_data + m_size, m_data);
	  }

	  DynArray& operator=(const DynArray& that)
	  {
	    if(this != &that)
	    {
	      delete[] m_data;
	      m_data = 0;
	      
	      m_size = that.m_size;
	      m_data = m_size ? new char[m_size] : 0;
	      std::copy(that.m_data, that.m_data + m_size, m_data);
	    }
	    
	    return *this;
	  }
	}

ОДНАКО, ИДЕОМА  COPY and SWAP предлагает более Лучшее решение
с точки зрения Exception-Safety. 

- Строгая Гарантия - Exception-Safety

СУТЬ: Мы создаём временные отдельные объекты size и data, в которые перемещаем
всё из this, чтобы работать с его копией, и не менять состояние this напрямую,
как делалось в примере выше. В итоге, если произойдёт исключение, всё, что
внутри this останется и НЕТРОНУТЫМ (exeption-safe) и не утечёт (leak-safe)

Мелочи: //if(this != &that) Можно так же убрать из кода проверку на копирование
самого себя, ибо, эта проверка в реальной жизни будет почти никогда не нужна, 
ибо в реальности оператор само собой будет работать по своему основному назначению,
так что оставлять или нет эту проверку остаётся на усмотрение прораммисту.

	class DynArray
	{
	private:
	  int m_size;
	  char* m_data;

	public:
	  DynArray(int size = 0)
	  : m_size(size), m_data(m_size ? new char[m_size]() : 0)
	  {}

	  ~DynArray()
	  {
	    delete [] m_data;
	    m_data = 0;
	  }

	  DynArray(const DynArray& that)
	  : m_size(that.m_size), m_data(m_size ? new char[m_size]() : 0)
	  {
	    std::copy(that.m_data, that.m_data + m_size, m_data);
	  }

	  DynArray& operator=(const DynArray& that)
	  {
	    //if(this != &that)
	    //{
	      int size = that.m_size;
	      char* data = size ? new char[size] : 0;
	      std::copy(that.m_data, that.m_data + size, data);
	      
	      delete[] m_data;
	      m_size = size;
	      m_data = data;
	    //}
	    
	    return *this;
	  }	   
	}


# ИДЕОМА COPY and SWAP решение БЕЗ Move-семантики:

	class DynArray
	{
	private:
	  int m_size;
	  char* m_data;

	public:
	  DynArray(int size = 0)
	  : m_size(size), m_data(m_size ? new char[m_size]() : 0)
	  {}

	  ~DynArray()
	  {
	    delete [] m_data;
	    m_data = 0;
	  }

	  DynArray(const DynArray& that)
	  : m_size(that.m_size), m_data(m_size ? new char[m_size]() : 0)
	  {
	    std::copy(that.m_data, that.m_data + m_size, m_data);
	  }

	  friend void swap(DynArray& a, DynArray& b)
	  {
	    using std::swap;
	    swap(a.m_size, b.m_size);
	    swap(a.m_data, b.m_data);
	  }
	  
	  // 1-ый вариант хороший
	  //DynArray& operator=(const DynArray& that)
	  //{
	  //  DynArray copy(that);
	  //  swap(*this, copy);
	  //  return *this;
	  //}
	
	  // 2-ой вариант ИДЕАЛЬНЫЙ
	  DynArray& operator=(DynArray copy)
	  {
	    swap(*this, copy);
	    return *this;
	  }
	   
	}


# COPY and SWAP Ideom + MOVE Semantiks

	class DynArray
	{
	private:
	  int m_size;
	  char* m_data;
	  
	public:
	  DynArray(int size = 0)
	  : m_size(size), m_data(m_size ? new char[m_size]() : 0)
	  {}

	  ~DynArray()
	  {
	    delete [] m_data;
	    m_data = 0;
	  }

	  // Спец конструктор
	  //DynArray("abc"); // how we will use the constructor
	  DynArray(const char* that)
	  {
	    m_size = strlen(that) + 1;
	    m_data = new char[m_size];

	    // 1 option
	    memcpy(m_data, that, m_size);

	    // 2 option
	    for (int i = 0; i < m_size; i++)
	    {
	      m_data[i] = that[i];
	    }
	  }

	  DynArray(const DynArray& that)
	  : m_size(that.m_size), m_data(m_size ? new char[m_size]() : 0)
	  {
	    std::copy(that.m_data, that.m_data + m_size, m_data);
	  }

	  friend void swap(DynArray& a, DynArray& b)
	  {
	    using std::swap;
	    swap(a.m_size, b.m_size);
	    swap(a.m_data, b.m_data);
	  }
	  
	  // 1-ый вариант хороший
	  //DynArray& operator=(const DynArray& that)
	  //{
	  //  DynArray copy(that);
	  //  swap(*this, copy);
	  //  return *this;
	  //}
	
	  // 2-ой вариант ИДЕАЛЬНЫЙ
	  DynArray& operator=(DynArray copy)
	  {
	    swap(*this, copy);
	    return *this;
	  }
	   
	  DynArray( /*const*/ DynArray&& that) // НЕ НУЖЕН CONST (!!!) -  MyString&& is an rvalue reference to a MyString
	  : m_data(that.m_data)
	  {
	    // 1-nd option
	    this->m_data = that.m_data;
	    this->m_size = that.m_size;

	    that.m_data = nullptr;
	    that.m_size = 0;

	    // 2-st option
	    std::swap(this->m_size, that.m_size);
	    std::swap(this->m_data, that.m_data);
	    // or
	    std::swap(*this, that); // with c++11
	  }
	  
	  DynArray& operator=(DynArray&& that)
	  {
	    if (this != &that)
	    {
	      // 1-nd option
	      this->m_data = that.m_data;
	      this->m_size = that.m_size;
        
	      that.m_data = nullptr;
	      that.m_size = 0;
        
	      // 2-st option
	      std::swap(this->m_size, that.m_size);
	      std::swap(this->m_data, that.m_data);
	      // or
	      std::swap(*this, that); // with c++11
	    }
	    return *this;
	  }
	}



# Socket Programming TCP
https://www.youtube.com/watch?v=eVYsIolL2gE&list=PL0JmC-T2nhdgJ2Lw5YdufR8MffaQdAvEf

# Socket Programming UDP
https://www.youtube.com/watch?v=xfRdYrQUQeQ&list=PL0JmC-T2nhdgJ2Lw5YdufR8MffaQdAvEf&index=2

Nicolai Josuttis “The Nightmare of Move Semantics for Trivial Classes”
# https://www.youtube.com/watch?v=PNRju6_yn3o


	#include <array>
	#include <vector>
	#include <string>
	#include <algorithm>
	
	
	//template <class T>
	//void remove_(std::vector<T> v, T n)
	void remove_(std::vector<int>& _v, int _n)
	{
	  bool found = false;
	  size_t pos = 0;
	  for (size_t i = 0, ilen = _v.size(), iv=0; i<ilen; i++)
	  {
	    iv = _v[i];
			
	    if (_v[i] == _n && !found)
	    {
	      pos = i;
	      found = true;
	    }
	    else
	    {
	      if(_v[i] != _n)
	      {
	        found = false;
	        _v[i - pos] = _v[i];
	      }
	    }
	  }
	}
	
	void print_v(std::vector<int>& _v)
	{
	  for (auto i : _v)
	  {
	    std::cout << i;
	  }
	}
	
	void remove_(int _v[], int vsz, int _n)
	{
		bool found = false;
		size_t pos = 0;
		for (size_t i = 0, ilen = vsz, iv = 0; i<ilen; i++)
		{
			iv = _v[i];
	
			if (_v[i] == _n && !found)
			{
				pos = i;
				found = true;
			}
			else
			{
				if (_v[i] != _n)
				{
					found = false;
					_v[i - pos] = _v[i];
				}
			}
		}
	}
	
	void main()
	{
		const int n  = 3;
		const int sz = 6;
		const int sz2 = 20;
	
		/*
		std::array<int, 3> a = { 1,2,3 };
		//std::vector<int> v = { 1,2,n,n,4,5,n,6,7,8,n,n,n,9,10,n,n,n,n,n };
		//std::vector<int> v = { 1,2,3,3,4,5,3,6,7,8,3,3,3,9,10,3,3,3,3,3 };
	
		std::vector<int> v;
		v.push_back(0);
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
	
		//remove_<int>(v, n);
		remove_(v, n);
	
		print_v(v);
	
		*/
	
		//int m[sz] = { 1,2,3,3,4,5 };
		int m[sz2] = { 1,2,n,n,4,5,n,6,7,8,n,n,n,9,10,n,n,n,n,n };
	
		remove_(m, sz2, n);
	
	}




# MFC: AFX_MANAGE_STATE (1)

https://msdn.microsoft.com/ru-ru/library/30c674tx.aspx


Обычная библиотека DLL, динамически связываемая с MFC — это библиотека DLL, внутренне использующая MFC. Экспортируемые функции этой библиотеки могут вызываться исполняемыми приложения MFC и другими приложениями. Как понятно из названия, этот вид библиотек DLL построен с использованием версии библиотеки динамической компоновки MFC (также называемой общей версией MFC). Функции экспортируются из обычной библиотеки DLL, используя, как правило, стандартный интерфейс языка C.
Чтобы установить для текущего состояния модуля одну из библиотек DLL, необходимо добавить макрос AFX_MANAGE_STATE в начало всех экспортируемых функций в обычных библиотеках DLL, которые динамически связываются с MFC. Для этого следует добавить следующий код в начало функций, экспортируемых из библиотеки DLL:

AFX_MANAGE_STATE(AfxGetStaticModuleState( ))  

Обычная библиотека DLL, динамически связываемая с MFC, обладает следующими возможностями.

- Это новый тип библиотеки DLL, впервые представленный в Visual C++ 4.0.
- Клиентский исполняемый модуль может быть создан на любом языке, поддерживающим использование библиотек DLL (C, C++, Pascal, Visual Basic и т. д.); ему не обязательно быть приложением MFC.
- В отличие от статически связываемых обычных DLL, этот вид библиотек DLL динамически связывается с DLL-библиотекой MFC (также называемой общей DLL-библиотекой MFC).
- С этим типом библиотеки DLL связана та же библиотека импорта MFC, которая используется для DLL-библиотек расширения или приложений, использующих DLL-библиотеки MFC: MFCxx(D).lib.


# MFC: AFX_MANAGE_STATE (2)

http://www.firststeps.ru/mfc/steps/r.php?325

Этот макрос управляет состоянием модуля. Под состоянием модуля понимается информация о приложении. В это состояние входят дескрипторы окон, таблицы связей MFC объектов и так далее.
```
AFX_MANAGE_STATE( AFX_MODULE_STATE* pModuleState )
```
При выполнении обычного модуля есть только одна таблица состояния:

Я не зря написал MFC модуль, это может быть как MFC EXE, так и MFC DLL. У каждого модуля своя таблица состояния. Раз так, то при выполнении другого модуля, который использует MFC, например, DLL, которая использует MFC или объектов OLE нужно переключаться на таблицу состояния этого модуля. Именно это и делает данный макрос.

-------------------------------------------------------


# Как устроена строка CString ? Чем она отличается от basic_string (std::string) ?

- Есть ОДНА особенность у CString (Конструктор копии). 
Конструктор копии делает так, что фактической копии объекта он не создаёт СНАЧАЛА.
Сначала он делает так, что старая и новая строка просто указывают на один и тот же буфер памяти.
А в тот момет, когда другой объект захотел поменять исходную строку (выпоолнить WRITE),
именно в момент изменения, и начинает (COPY) формироваться "копия" + и к копии приписывается "вносимое изменение".

- Конструктор копирования как следствие ОЧЕНЬ "Дешёвый" в плане расходования памяти.
- До вносимых изменений они все обычно указывают на одну ссылку.
- Мало памяти потребляет => Это очень сильно повышает эффективность в многопроцессорных системах

# Что такое Copy on write / Copy-on-write (CoW or COW) ? Что такое Копирование при записи ?
https://ru.wikipedia.org/wiki/%D0%9A%D0%BE%D0%BF%D0%B8%D1%80%D0%BE%D0%B2%D0%B0%D0%BD%D0%B8%D0%B5_%D0%BF%D1%80%D0%B8_%D0%B7%D0%B0%D0%BF%D0%B8%D1%81%D0%B8

Идея подхода copy-on-write заключается в том, что при чтении области данных используется общая копия, в случае изменения данных - создается новая копия.

Класс string имеющийся в C++ STL в рамках C++98, применял концепцию copy-on-write, но ушёл от неё с приходом стандарта C++11:

	// ПРИМЕР для C++98
	std::string x("Hello");
	
	std::string y = x;  // x и y используют один и тот же буфер
	
	y += ", World!";    // теперь y использует отдельный буфер
						// x продолжает использовать свой старый

# COW (Copy on write) and QT

In the Qt framework, many types are copy-on-write ("implicitly shared" in Qt's terms). Qt uses atomic compare-and-swap operations to increment or decrement the internal reference counter. Since the copies are cheap, Qt types can often be safely used by multiple threads without the need of locking mechanisms such as mutexes. The benefits of CoW are thus valid in both single- and multithreaded systems.



#  Совместное написание кода / Коллективное редактирование кода
collabedit.com/

#  Функции со смыслом:

	1 - 2^8 = 256
	
	2 - диапазон 4ё-х байтового числа = -(2^31)-1 - +(2^31)-1 
	
	3 - Чтобы число умножить на 2 - Логическая операция побитовая какую операцию можно применить 
	Ответ: ПОБИТОВЫЙ СДВИГ Влево

	0000 0011 = 3
	0000 0110 = 6

	0000 0001 = 2^0 = 1
	0000 0010 = 2^1 = 2
	0000 0100 = 2^2 = 4
	0000 1000 = 2^3 = 8
	0001 0000 = 2^4 = 16
	0010 0000 = 2^5 = 32
	0100 0000 = 2^6 = 64
	1000 0000 = 2^7 = 128
	
# Функция ВЫРАВНИВАНИЯ до нужного числа бит 


	int numParts = getNumOfParts(); // Parts of some class Object
	int offset = sizeof(Object) + sizeof(int) * numParts;
	if((offset % 8) != 0 )
	  offset += 8 - (offset % 8);
	PPOINT* start = (PPOINT*) (((char*) (&cur_object)) + offset);
	
# Функция проверки является ли число степенью двойки


	(N & (N-1) ) == 0
	
	например
	
	(0x1000 & 0x0fff) == 0
	(0x1234 & 0x1233) == 0x1230 != 0

	проверяет, является ли число степенью двойки
	т.е. то, что выставлен только самый старший бит и больше никаких


# Эффективное удаление для map:

# Самописный erase для map

# Самописный erase для list

# Самописный remove для вектора



# Дополнить число хранящееся как строка нулями справа:

- НЕЭФФЕКТИВНОЕ РЕШЕНИЕ

```

	//меньше 8-ми - дополняем нулями справа
	int i = NUM.Length();
	while(i != 8  &&  i < 8)
	{
	  NUM += "0";
	  i++;
	}
```

- ЭФФЕКТИВНОЕ РЕШЕНИЕ

```
	//меньше 8-ми - дополняем нулями справа
	while(NUM.Length() < 8)
	  NUM += "0";
```

# Чему равен размер указателя ? 
	
	Ответ: В зависимости от платформы. 4ём байтам какой максиманый размер оперативки можно адресовать ?
	К какому верхнему адресу можно обратиться, если иметь доступ ко всему адресному пространству ?
	- Указатель в зависимости от платформы - 64битный платформе он 8 байт занимает, на 32 битной 4 байта.

# Бросать исключения в Конструкторе это НОРМАЛЬНО ?

	Да это НОМРАЛЬНО - и память НЕ утечёр ибо объект ещё не создался, ибо конструктор полностью не отработал

# GIT - Чем отличается Merge от Rebase ?

	ДОПИСАТЬ

# ПРО ГИТ : About GIT

	Рассказать как было на предыдущих местах работы.
	Дев ветка, Мастер Ветка, Прод ветка
	Пишем -> делаем коммиты -> пушим в бранч
	Раз в неделю Делаем МЁРДЖ дева с Мастером.
	Выпускаем релиз -> Мёрджим Мастер с Продуктивом (через неделю после того как функционал поработал у заказчика)
	В течение недели в мастер не мерджим ничего, и мастер более новый чем продуктив. Если мастер последний показал себя у заказчика хорошо, мёрджим Мастер с Продуктивом.


# Оценка сложности
https://tproger.ru/articles/computational-complexity-explained/

Сложность алгоритмов обычно оценивают по времени выполнения или по используемой памяти. В обоих случаях сложность зависит от размеров входных данных: массив из 100 элементов будет обработан быстрее, чем аналогичный из 1000. При этом точное время мало кого интересует: оно зависит от процессора, типа данных, языка программирования и множества других параметров. Важна лишь асимптотическая сложность, т. е. сложность при стремлении размера входных данных к бесконечности.

Допустим, некоторому алгоритму нужно выполнить 4n3 + 7n условных операций, чтобы обработать n элементов входных данных. При увеличении n на итоговое время работы будет значительно больше влиять возведение n в куб, чем умножение его на 4 или же прибавление 7n. Тогда говорят, что временная сложность этого алгоритма равна О(n3), т. е. зависит от размера входных данных кубически.

Использование заглавной буквы О (или так называемая О-нотация) пришло из математики, где её применяют для сравнения асимптотического поведения функций. Формально O(f(n)) означает, что время работы алгоритма (или объём занимаемой памяти) растёт в зависимости от объёма входных данных не быстрее, чем некоторая константа, умноженная на f(n).

# Примеры алгоримов O(n), O(log n), O(n^2)

- O(n) — линейная сложность

Такой сложностью обладает, например, алгоритм поиска наибольшего элемента в не отсортированном массиве. Нам придётся пройтись по всем n элементам массива, чтобы понять, какой из них максимальный.

- O(log n) — логарифмическая сложность

Простейший пример — бинарный поиск. Если массив отсортирован, мы можем проверить, есть ли в нём какое-то конкретное значение, методом деления пополам. Проверим средний элемент, если он больше искомого, то отбросим вторую половину массива — там его точно нет. Если же меньше, то наоборот — отбросим начальную половину. И так будем продолжать делить пополам, в итоге проверим log n элементов.

- O(n^2) — квадратичная сложность

Такую сложность имеет, например, алгоритм сортировки вставками. В канонической реализации он представляет из себя два вложенных цикла: один, чтобы проходить по всему массиву, а второй, чтобы находить место очередному элементу в уже отсортированной части. Таким образом, количество операций будет зависеть от размера массива как n * n, т. е. n2.


 
 

#  Sample


	using MyUint32 = uint32_t; 
	using Range = std::pair<uint32_t, uint32_t>;


#  Sample


	#include <iostream> 

	template <typename U, typename V> 
	bool isSameType() 
	{ 
	  return typeid(U) == typeid(V); 
	} 

	int _tmain(int argc, _TCHAR* argv[]) 
	{ 
	  printf("%s\n\n", isSameType<char, int>() ? "same" : "not the same"); 

	  getchar(); 
	  return 0; 
	}


#  Sample Cycles test for Node in a List

	#include <iostream>
	#include <set>
	
	struct Node
	{
		int data;
		Node* next;
	};
	
	bool hasCycle(Node* head)
	{
		Node* entry = head;
	
		for (;;)
		{
			if (entry->next == head)
			{
				return true;
			} else if (entry->next == nullptr)
			{
				break;
			}
	
			entry = entry->next;
		}
	
		return false;
	}
	
	bool hasCycle2(Node* head)
	{
		Node* entry = head;
		std::set<Node*> marked;
		marked.insert(head);
	
		for (; entry != nullptr; entry = entry->next)
		{
			if (marked.count(entry->next) != 0)
			{
				return true;
			}
			
			marked.insert(entry); 
		}
	
		return false;
	}
	
	int _tmain(int argc, _TCHAR* argv[])
	{
		Node nodes[4];
		nodes[0].next = &nodes[1];
		nodes[1].next = &nodes[2];
		nodes[2].next = &nodes[3];
		//nodes[3].next = nullptr;
		nodes[3].next = &nodes[1];
	
		printf("Has a cicle? - %s\n\n\n", hasCycle2(nodes) ? "yes" : "no");
	
		getchar();
		return 0;
	}


#  Высоконагруженные системы (сокет-сервер и 5к~10к клиентов) Решения

- libev
- livevent
- libux
- исходные тексты Node.JS. Или просто писать на Node.JS, скорость удивит.
- Попробуйте посмотреть исходники проекта raknet ( http://www.jenkinssoftware.com/ ). Это опенсорсный движок для сетевых игр. 
- ERLANG ( https://github.com/goertzenator/nifpp ,  https://github.com/saleyn/eixx)

RSDN

http://rsdn.org/forum/network/4634983.hot

QT-Solution

http://www.prog.org.ru/topic_16415_0.html

https://habrahabr.ru/post/131585/


#  Высоконагруженные системы (сокет-сервер и 5к~10к клиентов)

https://toster.ru/q/11203

http://www.sql.ru/forum/1070722/vysoko-nagruzhennyy-server-na-ubuntu-s-pod-linux

http://www.programmersforum.ru/showthread.php?t=284261

в ОС штатно только один из нескольких механизмов (что бы вы не выбрали, будет использовать их (особо кривые что то одно))

- message queue - рекомендую не передавать данные в очереди, она быстро кончается
- shared memory - максимум идентификаторы и подробности через shared memory или другие механизмы.
- semaphore - Возможно, не стоит создавать один семафор на все, лучше под напрячься и по семафору на объект или хотя бы группу (чтобы блокировать только на доступ к группе а не всех ко всему) — этот подход может дать наверное максимально возможный прирост, когда упретесь в потолок (особенно грустно когда процессоры еще не нагружен и демоны чего то ждут), это в смысле организации многопроцессорного демона (или демон на ядро, так удобнее).

(+) высокопроиводительный сокет-сервер — лучше не писать многопоточное приложение, а обрабатывать все операции с сокетами в одном потоке,




1. Забудьте про треды и тем более процессы, 5-10к тредов не выдержит никакая ось.
2. Соответственно только неблокирующий ввод-вывод. Один поток занимается только i/o и сбрасывает полученные данные другим потокам… Вы бы сказали всё же какая у вас задача, а то это пальцем в небо.
3. Нормально реализовать неблокирующий и/о с первого раза сложно, со второго тоже… Там внутрях каждой оси много «трюков», которые нет-нет да заблокируют ваш поток. Очень советую использовать libevent или что-то вроде того. 
4. Если уж собираете статистику и всё такое, не изобретайте велосипед и возьмите хотя бы SQLite. Иначе опять же соберете кучу граблей и косяков с конкурентностью, взаимными блокировками потоков, крахом базы при падении сервера, рейсами и прочими прелестями многопоточки. SQLite можно встроить прямо в вашу прогу, для внешнего наблюдателя её как бы и не будет.




http://www.cyberforum.ru/cpp-beginners/thread2150113.html#post11914363


684 231
75 000


760 282 р


331 600
--- --- ---



#  C++ 99,03,11,14,17
http://glebradchenko.susu.ru/courses/bachelor/oop/201..

https://ru.wikipedia.org/wiki/C%2B%2B11#Ссылки_на_временные_объекты_и_семантика_переноса_(Rvalue_Reference/Move_semantics)

# C++11 + STL:

- Хеш-таблицы

std::hash_set и std::hash_map давно были нестандартным расширением STL, по факту реализованным в большинстве компиляторов.
В C++11 они стали стандартом, под именами std::unordered_set и std::unordered_map

- Регулярные выражения (std::regex, std::match_results)

Новая библиотека, объявленная в заголовочном файле <regex>, содержит в себе несколько новых классов:

Регулярные выражения представлены в виде экземпляров класса std::regex;
результаты поиска представлены в виде экземпляров шаблона std::match_results.

# C++11:

Произошло Расширение ядра языка:

- Ссылки на временные объекты и семантика переноса (Rvalue Reference / Move semantics)

В C++11 появился новый тип ссылки — rvalue-ссылка (англ. rvalue reference). Его объявление следующее: type &&. Новые правила разрешения 

- auto новое ключевое слово 

C++11 появилась ДИНАМИЧЕСКАЯ ТИПИЗАЦИЯ, при условии что ранее была только Строгая типизация, это привнесло в язык больше гибкости и удобств. 

- Обобщённые константные выражения 

C++11 вводит ключевое слово constexpr, которое позволяет пользователю гарантировать, что или функция или конструктор объекта возвращает константу времени компиляции. Код выше может быть переписан следующим образом:

- Изменения в определении простых данных

C++11 ослабит несколько правил, касающихся определения типов простых данных.

Класс рассматривается как тип простых данных, если он тривиальный (trivial), со стандартным размещением (standard-layout) и если типы всех его нестатических членов-данных также являются типами простых данных.

- Внешние шаблоны

В C++11 введена идея внешних шаблонов. В С++ уже есть синтаксис для указания компилятору того, что шаблон должен быть инстанцирован в определённой точке:

	extern template class std::vector<MyClass>;

- For-цикл по коллекции

Пример кода:
	
	int my_array[5] = {1, 2, 3, 4, 5};
	for(int &x : my_array)
	{
	  x *= 2;
	}


- Списки инициализации

...

	struct Object
	{
	    float first;
	    int second;
	};

	Object scalar = {0.43f, 10}; // один объект, с first=0.43f и second=10
	Object anArray[] = {{13.4f, 3}, {43.28f, 29}, {5.934f, 17}}; // массив из трёх объектов


	SequenceClass someVar = {1, 4, 5, 6};

- Спецификаторы default и delete

Спецификатор default означает реализацию по умолчанию и может применяться только к специальным функциям-членам:
(конструктор по-умолчанию; конструктор копий; конструктор перемещения; оператор присваивания; оператор перемещения; деструктор.)

Спецификатор delete помечают те методы, работать с которыми нельзя. Раньше приходилось объявлять такие конструкторы в приватной области класса.

	class Foo
	{
	public:
	    Foo() = default;
	    Foo(int x) {/* ... */}
	};

- override и final - Явное замещение виртуальных функций и финальность

1) В C++11 будет добавлена возможность отследить подобные проблемы на этапе компиляции (а не на этапе выполнения). Для обратной совместимости данная возможность является опциональной. Новый синтаксис представлен ниже:
2) Наличие у виртуальной функции спецификатора final означает, что её дальнейшее замещение невозможно. Кроме того, класс, определённый со спецификатором final, не может использоваться в качестве базового класса:

- Перечисления со строгой типизацией

Такое перечисление является типобезопасным. Элементы классового перечисления невозможно неявно преобразовать в целые числа. Как следствие, сравнение с целыми числами также невозможно (выражение Enumeration::Val4 == 101 приводит к ошибке компиляции).

	enum class Enumeration {
	    Val1,
	    Val2,
	    Val3 = 100,
	    Val4, /* = 101 */
	};

- Шаблонный typedef

В C++11 директива using также может использоваться для создания псевдонима типа данных.

	typedef void (*OtherType)(double);	// Старый стиль
	using OtherType = void (*)(double);	// Новый синтаксис

- Шаблоны с переменным числом аргументов (Вариативный шаблон)

До появления C++11 шаблоны (классов или функций) могли принимать только заданное число аргументов, определяемых при первоначальном объявлении шаблона. C++11 позволяет определять шаблоны с переменным числом аргументов любого типа.

	template<typename... Values> class tuple;


- Лямбда-функции и выражения


- (ПОДРОБНЕЕ) Ссылки на временные объекты и семантика переноса (Rvalue Reference / Move semantics)

В C++11 появился новый тип ссылки — rvalue-ссылка (англ. rvalue reference). Его объявление следующее: type &&. Новые правила разрешения перегрузки позволяют использовать разные перегруженные функции для неконстантных временных объектов, обозначаемых посредством rvalues, и для всех остальных объектов. Данное нововведение позволяет реализовывать семантику переноса (Move semantics).

Например, std::vector — это простая обёртка вокруг Си-массива и переменной, хранящей его размер. Конструктор копирования std::vector::vector(const vector &x) создаст новый массив и скопирует информацию; конструктор переноса std::vector::vector(vector &&x) может просто обменяться указателями и переменными, содержащими длину.

Пример объявления.

	template<class T> class vector
	{
	   vector (const vector &);              // Конструктор копирования (медленный)
	   vector (vector &&);                   // Конструктор переноса из временного объекта (быстрый)
	   vector & operator = (const vector &); // Обычное присваивание (медленное)
	   vector & operator = (vector &&);      // Перенос временного объекта (быстрый)
	};
	
	
- Семантика пепемещения


# ЛЯМБДЫ:

Чтобы решить эту проблему, можно вручную указать возвращаемый тип лямбда-функии, используя синтаксис "-> тип":

 В общем случае его можно записать так:
[captures](arg1, arg2) -> result_type { /* code */ }

[](double d) -> double {}

[] - Название функции
Запись "[]" означает, что у функции нет имени, она безымянная, или, говоря по-другому, анонимная.
Вместо "[]" можно мысленно подставлять имя "безымяннаяФункция",

() - параметры лямбда функции (работают внутри ЗАМЫАНИЯ)
arg1, arg2
это аргументы.То, что передается алгоритмом в функтор(лямбду).
Парметры ЗАМКНУТЫ или находятся внутри ЗАМЫКАНИЕ / ЗАМЫКАНИЯ -
доступ измне к ним более невозможен, они доступны только в рамках теля лямбда выражения

-> - тип возвращаемого значения
result_type
это тип возвращаемого значения.Это может показаться несколько непривычно, так как раньше тип всегда писали перед сущностью(переменной, функцией).Но к этом быстро привыкаешь.

{ } - тело ЛЯМБДА выражения

# Лямбды и Замыкания

... ДОПИСАТЬ


# Умный указатель или Smart Pointer своими руками:
https://tproger.ru/problems/write-a-class-for-smart-pointer/

	/* Класс интеллектуального указателя нуждается в указателях на собственно
	 * себя и на счетчик ссылок. Оба они должны быть указателями, а не реальным
	 * объектом или значением счетчика ссылок, так как цель интеллектуального
	 * указателя - в подсчете количества ссылок через множество интеллектуальных
	 * указателей н один объект */

	template 
	class SmartPointer {
		T * obj;
		unsigned * ref_count;
	}



	template <class T>
	class SmartPointer
	{
	public:
		SmartPointer(T * ptr)
		{
			ref = ptr;
			ref_count = (unsigned*)malloc(sizeof(unsigned));
			*ref_count = 1;
		}
	
		SmartPointer(SmartPointer & sptr)
		{
			ref = sptr.ref;
			ref_count = sptr.ref_count;
			++(*ref_count);
		}
	
		/* Перезаписываем оператор равенства (eqal), поэтому когда вы установите
		* один интеллектуальный указатель в другой, количество ссылок старого указателя
		* будет уменьшено, а нового - увеличено.
		*/
		SmartPointer & operator=(SmartPointer & sptr)
		{
			/* Если уже присвоено объекту, удаляем одну ссылку. */
			if (*ref_count > 0)
			{
				remove();
			}
			if (this != &sptr)
			{
				ref = sptr.ref;
				ref_count = sptr.ref_count;
				++(*ref_count);
			}
			return *this;
		}
	
		~SmartPointer()
		{
			remove(); // удаляем одну ссылку на объект.
		}
	
		T operator*()
		{
			return *ref;
		}
	
	protected:
		void remove()
		{
			--(*ref_count);
			if (ref_count == 0)
			{
				delete ref;
				free(ref_count);
				ref = NULL;
				ref_count = NULL;
			}
		}
	
		T * ref;
		unsigned * ref_count;
	}






# RValues + LValues + Move Semantic in a C++11 Class

	// RValues + LValues + Move Semantic

	// https://www.youtube.com/watch?v=ruHw7E71zBw
	// https://www.youtube.com/watch?v=cO1lb2MiDr8
	
	#include <cstring>
	#include <string>
	#include <algorithm>
	
	class MyString
	{
		char* m_data;
		size_t m_size;
	
	public:
	
		MyString() : m_data(0), m_size(0)
		{
		}
	
		~MyString()
		{
			delete[] m_data;
			m_data = 0; // установка указателя в 0 позволяет проверять его недопустимость
		}
	
		// Спец конструктор
		//MyString("abc"); // how we will use the constructor
		MyString(const char* other)
		{
			m_size = strlen(other) + 1;
			m_data = new char[m_size];
	
			// 1 option
			memcpy(m_data, other, m_size);
	
			// 2 option
			for (int i = 0; i < m_size; i++)
			{
				m_data[i] = other[i];
			}
		}
	
		// Конструктор копий.
		//MyString(const MyString& that)
	
		// default  copy constructor  // буквальное (shallow copy)
		MyString(const MyString& that) // Конструктор копий.
		{
			m_data = that.m_data;
			m_size = that.m_size;
		}
	
		// развернутое / глубокое копирование (deep copy)
		// 1 option = BETTER
		MyString(const MyString& that)
			: m_size(that.m_size)
			, m_data = new char[m_size]
		{
			memcpy(m_data, that.m_data, m_size); // memcpy(m_data, that.m_data, sizeof(char) * m_size);
		}
	
			// 2-nd option
			MyString(const MyString& that)
		{
			m_size = that.m_size; //m_size = strlen(that.m_data) + 1;
			m_data = new char[m_size];
			memcpy(m_data, that.m_data, size);	// memcpy(m_data, that.m_data, sizeof(char) * m_size);
		}
	
		// Оператор присваивания.
		//MyString& operator=(const MyString& that)
	
		// default  operator=  // буквальное (shallow copy)
		MyString& operator=(const MyString& that) // нужен ли const ?
		{
			m_data = that.m_data;
			return *this;
		}
	
		// развернутое / глубокое копирование (deep copy)
		MyString& operator=(const MyString& that) // нужен ли const ?
		{
			if (this == &that)
				return *this;
	
			// 1 option
			m_size = that.m_size; //m_size = strlen(that.m_data) + 1;
			m_data = new char[m_size];
			memcpy(m_data, that.m_data, m_size);	// memcpy(m_data, that.m_data, sizeof(char) * m_size);
	
			// 2 option
			//m_size = that.m_size; //m_size = strlen(that.m_data) + 1;
	
			// not here						// COPY !!!
			// not here						// AND
			//std::swap(m_data, that.m_data); // SWAP !!!	// Если с  (CONST MyString that), то swap ругнётся can not convert!!!  char*, char* const
	
			return *this;
		}
	
		// Семантика перемещения.
	
		// Перемещающий Конструктор копий.
		//MyString(const MyString&& that)
	
		// default  move copy constructor  // буквальное (shallow copy)
		//	MyString(const MyString&& that)
		//	{
		//		this = that;
		//	}
	
		// развернутое / глубокое копирование (deep copy)
		MyString( /*const*/ MyString&& that) // НЕ НУЖЕН CONST (!!!) -  MyString&& is an rvalue reference to a MyString
			: m_data(that.m_data)
		{
			// 1-nd option
			this->m_data = that.m_data;
			this->m_size = that.m_size;
	
			that.m_data = nullptr;
			that.m_size = 0;
	
			// 2-st option
			std::swap(this->m_size, that.m_size);
			std::swap(this->m_data, that.m_data);
			// or
			std::swap(*this, that); // with c++11
		}
	
		// Перемещающий Оператор присваивания.
		//MyString& operator=(const MyString&& that)
	
		MyString& operator=(MyString&& that)
		{
			if (this != &that)
			{
				// 1-nd option
				this->m_data = that.m_data;
				this->m_size = that.m_size;
	
				that.m_data = nullptr;
				that.m_size = 0;
	
				// 2-st option
				std::swap(this->m_size, that.m_size);
				std::swap(this->m_data, that.m_data);
				// or
				std::swap(*this, that); // with c++11
			}
			return *this;
		}
	
	};
	
	
	void main()
	{
		int z = 0;
	}




# OpenGL

# РЕГУЛЯРНЫЕ ВЫРАЖЕНИЯ <regex>

# XSLT - трансформация XML

# XSD

# INNER JOIN / OUTER JOIN


# MEMORY MAPPED FILES Cуть:

Это механизм, который позволяет отображать файлы на участок памяти. Таким образом, при чтении данных из неё, производится считывание соответствующих байт из файла. С записью аналогично. 

Допустим, перед нами стоит задача обработки большого файла(несколько десятков или даже сотен мегабайт). Казалось бы, задача тривиальна — открываем файл, поблочно копируем из него в память, обрабатываем. Что при этом происходит. Каждый блок копируется во временный кэш, затем из него в нашу память. И так с каждым блоком. Налицо неоптимальное расходование памяти под кэш + куча операций копирования. Что же делать?

Тут-то нам на помощь и приходит механизм MMF. Когда мы обращаемся к памяти, в которую отображен файл, данные загружаются с диска в кэш(если их там ещё нет), затем делается отображение кэша в адресное пространство нашей программы. Если эти данные удаляются — отображение отменяется. Таким образом, мы избавляемся от операции копирования из кэша в буфер. Кроме того, нам не нужно париться по поводу оптимизации работы с диском — всю грязную работу берёт на себя ядро ОС.

С отображением далее можно работать как и с обычным файлом:
- Писать / WRITE
- Читать / READ
- Шарить отображение / делать Нешаренным / MAP_SHARED
- Применять результат того, что мы сделали с отображением, Не применять изменения в отображении.


# Преимущества Хэш таблицы перед Деревом ? Преимущество unordnered_map перед просто map ?

- MAP сложнорсть операций O(log(n)), UNORDNERED_MAP сложнорсть, если рассматривать амортизированное O-большое = O(1). Амртизированность заключается в том, что мы предполагаем, что у нас будет мало или почти не будет коллизий. И тогда Хэш-таблица получается выйгрышней, производительней, быстрее.

# Имеется массив из 10 Гигабайт миллиона элементов, и его нужно отсортировать, при этом вам дано очень много процессоров (несколько Google-Кластеров) ?
https://ru.wikipedia.org/wiki/MapReduce

МЬЮТЕКСЫ: Если использовать мьютексы, то решение будет слишком медленным и неэффективным.

ВЕРНЫЙ ОТВЕТ: Использовать подход MAPREDUCE, то есть:
1) На первом MAP шаге смотрим сколько у нас процессоров допустим 28. Делим массив на 28 блоков, каждый блок отдаём на сортировку каждому процессору
2) На втором REDUCE шаге происходит свёртка предварительно обработанных данных. Мы производим слияние отсортированных массивов.

О MapReduce — модель распределённых вычислений, представленная компанией Google, используемая для параллельных вычислений над очень большими, вплоть до нескольких петабайт, наборами данных в компьютерных кластерах.

Канонический пример приложения, написанного с помощью MapReduce, — это процесс, подсчитывающий, сколько раз различные слова встречаются в наборе документов:

	// Функция, используемая рабочими нодами на Map-шаге
	// для обработки пар ключ-значение из входного потока
	void map(String name, String document):
      // Входные данные:
      //   name - название документа
      //   document - содержимое документа
      for each word w in document:
          EmitIntermediate(w, "1");
 
	// Функция, используемая рабочими нодами на Reduce-шаге
	// для обработки пар ключ-значение, полученных на Map-шаге
	void reduce(String word, Iterator partialCounts):
      // Входные данные:
      //   word - слово
      //   partialCounts - список группированных промежуточных результатов. Количество записей в partialCounts и есть 
      //     требуемое значение
      int result = 0;
      for each v in partialCounts:
          result += parseInt(v);
      Emit(AsString(result));


	  
В качестве домашнего задания можете попробовать модифицировать код так, чтобы через отображение файл можно было не только читать, но и писать в него.
	  


#  RAII - СУТЬ:

Концепция RAII (Запрос ресурса при инициализации) = ресурс запрашивается в конструкторе и освобождается в декструкторе:
- СТАНДАРТ !!! C++ гарантирует вызов деструктора при выходе из области видимости (за текущий блок выполнения программы)
  в независимости от того, будет ли это изза сгенерированного исключения, вызов return, конец блока.
- RAII концепция работает, только в том случае, если наш RAII-объект создаётся на стеке, а не на куче.


Как уже было сказано ранее в языке С++ (в отличие от языка C#), при генерации исключения в конструкторе класса деструкторы уже сконструированных полей (т.е. подобъектов) будут вызваны автоматически. Это значит, что в данном случае вызов деструктора объекта Resource1 произойдет автоматически и никаких утечек ресурсов не будет. 


	{
		File f("file.txt");
		// исключение, ретёрн, выход за пределы блока, деструктор ВЫЗОВЕТСЯ !
	}
	
	{
		File* f = new File("file.txt");
		// Деструктор НЕ вызовется, до тех пор пока не появится delete f;
		// при исключении, ретёрне, выходе за пределы блока, получим УТЕЧКУ
	}
	
	- требуется реализовать для специфических типов ресурсов и сценариев использования
	
	// 1 //
	A* p = new A();
	// код 
	// бросается исключение // утечка памяти, не будет вызван оператор  делит  для указателя на динам. выделенную память. 
	// код
	SomeFunc();
	delete p;
	
	// 2 //
	std::mutex m;
	m.lock();
	// код 
	// бросается исключение // будет ЗАВИСАНИЕ , ибо многопоточка и не отработает синхронизация !!!
	// код
	SomeFunc();
	m.unlock();
	

#  RAII
https://habrahabr.ru/post/150069/

Идиома RAII (Resource Acquisition Is Initialization) берет свое начало в языке С++ и заключается в том, что некоторый ресурс захватывается в конструкторе объекта, и освобождается в его деструкторе. А поскольку деструктор локальных объектов вызывается автоматически при выходе из метода (или просто из области видимости) не зависимо от причины (нормальное завершение метода или при генерации исключения), то использование этой идиомы является самым простым и эффективным способом написания сопровождаемого C++ кода, безопасного с точки зрения исключений. 

При переходе к «управляемым» платформам, таким как .NET или Java, эта идиома в некотором роде теряет свою актуальность, поскольку освобождением памяти занимается сборщик мусора, а именно память была самым популярным ресурсом, о котором приходилось заботиться в языке С++. Однако поскольку сборщик мусора занимается лишь памятью и никак не способствует детерминированному освобождению ресурсов (таких как дискрипторы операционной системы), то идиома RAII все еще применяется и в .NET, и в Java, пусть мало кто из разработчиков знает об этом замысловатом названии. 


- Базовая гарантия


Исходное определение: “в случае возникновения исключений не должно быть никаких утечек ресурсов”.

Современное определение: “при возникновении любого исключения в некотором методе, состояние программы должно оставаться согласованным”. Это означает, не только отсутствие утечек ресурсов, но и сохранение инвариантов класса, что является более общим критерием, по сравнению с базовым определением.

Разница между этими двумя формулировками обусловлена тем, что изначально эта гарантия были предложена для реализации библиотеки на языке С++ и не имела никакого отношения к прикладным приложениями. Но если говорить о более общем случае (т.е. о приложении, а не только о библиотеке), то можно сказать, что утечки ресурсов является лишь одним из источников багов, но далеко не единственным. Сохранение инварианта в любой устойчивый момент времени (**) является залогом того, что никакой внешний код не сможет «увидеть» рассогласованного состояния приложения, что, согласитесь, не менее важно, чем отсутствие утечек ресурсов. Мало какого пользователя банковского приложения будут интересовать утечки памяти, если при переводе денег с одного счета на другой, деньги могут «уйти» с одного счета, но «не дойти» до другого.

- Строгая гарантия


Что касается определения строгой гарантии исключений, то исходное и современные определения являются аналогичными и сводятся к следующему: “если при выполнении операции возникает исключение, то это не должно оказать какого-либо влияния на состояние приложения ”.

Другими словами, строгая гарантия исключений обеспечивает транзакционность операций, когда мы получаем либо все, либо ничего. В этом случае, при возникновении исключения мы должны откатиться к состоянию приложения, которое было перед выполнением операции, и переходить в новое состояние только в случае удачного завершения всей операции.

- Гарантия отсутствия исключений


Гарантия отсутствия исключений сводится к следующему: “ни при каких обстоятельствах функция не будет генерировать исключения”.

Эта гарантия наиболее простая с точки зрения определения, однако, она не так проста, как кажется. Во-первых, ее практически невозможно обеспечить в общем случае, особенно в среде .Net, когда исключение может произойти практически в любой точке приложения. На практике, лишь единицы операций следуют этой гарантии, и именно на основании таких операций строятся гарантии предыдущих уровней. В языке C#, то одной из немногих операций, обеспечивающих эту гарантию, является присваивание ссылок, а в языке C++ — функция swap, реализующая обмен значений. Именно на основании этих функций зачастую и реализуется строгая гарантия исключений, когда вся «грязная работа» выполняется во временном объекте, который затем присваивается результирующему значению.


#  RAII
https://habrahabr.ru/post/253749/

Пример кода использующего RAII:

Допустим, есть какой-то класс, инкапсулирующий доступ к сети:

	class Network {
	public:
		Network(const URL &url) : m_url(url)
		{
		}
	
	private:
		Url m_url;
	
	};
	
	Создаём класс, который будет реализовывать RAII :
	
	class LockNet {
	public:
		LockNet(const Url &url) {
			m_net = new Network(url);
		}
		~LockNet() {
			delete m_net;
		}
	
		operator Network * () {
			return network;
		}
	
	private:
	
		Network *m_net;
	};

Теперь в функции main мы можем безопасно использовать этот ресурс:

	int main(int argc, char *argv[])
	{
		LockNet net("http://habrahabr.ru")
		//здесь какие-то другие функции, 
		//которые могут генерировать исключения
		return 0;	
	}

Вроде бы всё нормально, как обещает RAII, даже если будет сгенерировано исключение, указатель m_net в классе LockNet будет корректно удалён. Правильно?

Увы, нет.

Почему-то в описании RAII обычно забывают написать, что для работы этой техники исключение ОБЯЗАНО быть перехвачено обработчиком исключений этого типа, иначе, если обработчик не будет найден, будет вызвана std::terminate(), которая аварийно завершит выполнение программы. Страуструп описывает это в книге «Язык программирования С++ (03)», глава 14.7.

Удаление локальных объектов зависит от реализации, где-то они будут удалены, где-то наоборот, чтобы разработчик мог увидеть состояние локальных объектов на момент исключения, в дебагере когда загрузит coredump. И рекомендует если вам нужно гарантированное удаление локальных объектов оборачивать код в функции main блоком try — catch (...), который перехватывает любые исключения.

Т.ч. в коде функции main, если будет исключение до оператора return 0;, мы получаем обычную утечку ресурсов.
Она не фатальная, так как ОС сохранит coredump и освободит ресурсы, занятые программой.

Как в этом убедиться? Пишем проверочный код!

В данном коде мы используем умные указатели, которые реализовывают технику RAII:





# Сортировки:
http://www.cyberforum.ru/cpp-beginners/thread27084.html

- 1. Сортировка выбором / Selection sort

Идея метода состоит в том, чтобы создавать отсортированную последовательность путем присоединения к ней одного элемента за другим в правильном порядке. Если входная последовательность почти упорядочена, то сравнений будет столько же, значит алгоритм ведет себя неестественно.

- 2. Сортировка пузырьком (обменом) / Bubble Sort

Идея метода: шаг сортировки состоит в проходе снизу вверх по массиву. По пути просматриваются пары соседних элементов. Если элементы некоторой пары находятся в неправильном порядке, то меняем их местами.

- 3. Сортировка вставками / Insertion sort

Аналогично сортировке выбором, среднее, а также худшее число сравнений и пересылок оцениваются как O(n^2), дополнительная память при этом не используется.
Хорошим показателем сортировки является весьма естественное поведение: почти отсортированный массив будет досортирован очень быстро. Это, вкупе с устойчивостью алгоритма, делает метод хорошим выбором в соответствующих ситуациях.

- 4. Сортировка Шелла

Сортировка Шелла является довольно интересной модификацией алгоритма сортировки простыми вставками.
Часто вместо вычисления последовательности во время каждого запуска процедуры, ее значения рассчитывают заранее и записывают в таблицу, которой пользуются, выбирая начальное приращение по тому же правилу: начинаем с inc[s-1], если 3*inc[s] > size.

- 5. Пирамидальная сортировка / Heapsort

Пирамидальная сортировка является первым из рассматриваемых методов, быстродействие которых оценивается как O(n log n).
Построение пирамиды занимает O(n log n) операций, причем более точная оценка дает даже O(n) за счет того, что реальное время выполнения downheap зависит от высоты уже созданной части пирамиды.
Вторая фаза занимает O(n log n) времени: O(n) раз берется максимум и происходит просеивание бывшего последнего элемента. Плюсом является стабильность метода: среднее число пересылок (n log n)/2, и отклонения от этого значения сравнительно малы.
Метод не является устойчивым: по ходу работы массив так "перетряхивается", что исходный порядок элементов может измениться случайным образом.

- 6. Быстрая сортировка (сортировка Хоара) / Quick sort

"Быстрая сортировка", хоть и была разработана более 40 лет назад, является наиболее широко применяемым и одним их самых эффективных алгоритмов.
Каждое разделение требует, очевидно, O(n) операций. Количество шагов деления(глубина рекурсии) составляет приблизительно log n, если массив делится на более-менее равные части. Таким образом, общее быстродействие: O(n log n), что и имеет место на практике.
Итеративный алгоритм быстрой сортировки.

- 7. Поразрядная сортировка / Radix sort

Рассматриваемый ниже алгоритм существенно отличается от описанных ранее.
Во-первых, он совсем не использует сравнений сортируемых элементов.
Во-вторых, ключ, по которому происходит сортировка, необходимо разделить на части, разряды ключа. Например, слово можно разделить по буквам, число - по цифрам..


# Сортировки время работы в ЛУЧшем / СРЕДнем / ХУДшем случае:
https://habrahabr.ru/post/188010/

- 1) Сортировка выбором / Selection sort

ВСЕ СЛУЧАИ: O(n^2)

- 2. Сортировка пузырьком (обменом) / Bubble Sort

Луч: O(n)	Сред: O(n^2)	Худ: O(n^2)

- 3. Сортировка вставками / Insertion sort

Луч: O(n)	Сред: O(n^2)	Худ: O(n^2)

- 4. Сортировка Шелла 

Луч: До O(n)	Сред: плавает*	Худ: O(n^2)    (*) плавает в зависимости от вида входной последовательности.

- 5.1 Пирамидальная сортировка / Heapsort

ВСЕ СЛУЧАИ: O(n*log(n))

- 5.2 Сортировка деревом / Tree sort

ВСЕ СЛУЧАИ: O(n*log(n))

- 6. Быстрая сортировка / Quick sort

Луч: O(n*log(n))  Сред: O(n*log(n))  Худ: O(n^2)

- 7. Поразрядная сортировка / Radix sort ( http://algolist.manual.ru/sort/radix_sort.php )

Луч: O(n)       ВСЕ СЛУЧАИ: O(n*k), n - разрядность данных: количество возможных значений разряда ключа; k - количество разрядов в самом длинном ключе


# Сортировки / Гарантированно работающая за O(n(log(n))) это Пирамидальная сортировка (HeapSort)
https://habrahabr.ru/post/335920/

Пирамидальная сортировка / Heapsort

Развитие идеи сортировки выбором. Воспользуемся структурой данных «куча» (или «пирамида», откуда и название алгоритма). Она позволяет получать минимум за O(1), добавляя элементы и извлекая минимум за O(logn). 

Таким образом, асимптотика O(n(log(n))) в ХУДШЕМ, СРЕДНЕМ и ЛУЧШЕМ случае. Реализовывал кучу я сам, хотя в С++ и есть контейнер priority_queue, поскольку этот контейнер довольно медленный.


# Виртуальный конструктор / Может ли быть конструктор виртуальным:

Конструктор без парматров (по умолчанию):
- (1) ищем блок памяти куда проинициализщировать объект, на случай если он пустой. (поэтому пустой класс разхмера не ноль)
- (2) считает размер всех полей, выполонил выравнивание (дефолтное или нами задланние через #pragma)
- (3) смотит есть ли виртуальные функции, если есть, то инициализирует указатель на таблицу виртуцальных функций
- (3.5) - (*) где-то тут выховутся конструкторы предков
- (4) смотрит есть ли виртуальные предки, под них выделяет и инициализирует указатели.
- (4.5) - (*) где-то тут выховутся конструкторы предков
- (5) и в самом конце то, что он посчитал на этапе (2) под это наконец выделяется памятяь на стеке / или в куче
- (6) завершается выполнение конструтора. ОБЪЕКТ СОЗДАН.

Конструктор без парматров (по умолчанию) должен проинициализировать указатель на таблицу виртуальных функций, чего он не сможет сделать, если сам будет виртуальным.
Вопрос связан с терминами - раннее и поднее связывание - 

Более того. Пойдём от противного. В чём суть виртуальности - В том, чтобы опеределить виртуальную функцию в БАЗОВОМ классе, чтобы через указатель на базовый класс мы могли бы вызывать функции классов потомков. В чём получается суть виртуального контсрутора, тоесть мы с однорй стороны ходим по идее вызвать контруктор, но допустим, что он у нас виртуальный, значит, мы вызовим контруктор не базовый, а класса ниже по иерархии .... В чём смысл ?

Идеологическая сторона вопроса - Суть виртуальности описана выше. Есть базовый объект и объект дочерний. вирт. функция чтобы через ук. на обхект баз. вызвать объект кружка, НО т.к. объект наследник не может быть вызван, ибо ещё не создан, а вирт. функции вызываются для уже созданных объектов. 
(Вопрос на подумать - Могут ли всё сломать статический конструтор .... )

СОЛЬ: Виртуальная функци вызывается примениткльно к функции уже созданного объекта, а конструктор нужен для создания обхъекта, и пока объекьт не созхдакн, мы ничего и не сможем вызвать.



# Порядок уничтожения объектов в классе:

https://habrahabr.ru/post/58818/

# Гарантии RAII:

https://habrahabr.ru/post/253749/

https://habrahabr.ru/post/126374/

https://habrahabr.ru/post/150069/



# Виртуальное наследование / Ромбовидное наследование / Виртуальный базовый класс
https://ru.stackoverflow.com/questions/163041/%D0%9D%D0%B5%D0%BE%D0%B4%D0%BD%D0%BE%D0%B7%D0%BD%D0%B0%D1%87%D0%BD%D0%BE%D0%B5-%D1%80%D0%BE%D0%BC%D0%B1%D0%BE%D0%B2%D0%B8%D0%B4%D0%BD%D0%BE%D0%B5-%D0%BD%D0%B0%D1%81%D0%BB%D0%B5%D0%B4%D0%BE%D0%B2%D0%B0%D0%BD%D0%B8%D0%B5

- СУТЬ:

При РОМБОВИДНОМ наследовании класс D / Multi будет иметь ДВЕ копии A / Base.

Но если сделать наследование ВИРТУАЛЬНЫМ, то копия A / Base внутри D / Multi будет ОДНА.

Проблема ромбовидного наследования надуманная, ибо решение всегда имеется через явное указание того класса откуда что брать:

	class A { public: int a };
	class B: public A {};
	class C: public A {};
	class D: public B, C {};

	D d;
	d.a = 2;	// 1 Есть проблема ... не знаем откуда брать a из  B  или из  C
	d::B.a = 2;	// 1 НЕТ проблемы ... Указали явно, что из B

- Ромбовидное наследование:
...
	
	
		class Base{ public: Base(){ std::cout<<"Create!"<<endl; } };
		class Sub1 : public virtual Base{};
		class Sub2 : public Base{};
		class Multi : public Sub1, public Sub2{} ;
	

Далее вызываем конструктор класса Multi:

	int main()
	{
	    Multi m;
	    return 0;
	}
	
Вывод:

Create!

Create!


- Виртуальное наследование:
(помогает решить проблему ромбовидного наследования)

Специфицируем класс Sub2, как виртуальный, то вывод будет иным, а именно:

Create!



# Docker

https://habrahabr.ru/post/343572/


	class AA
	{
	public:
		AA() { std::cout << "AA"; }
		~AA()
		{
			std::cout << "~AA";
			throw 5;
		}
	};
	
	class BB
	{
	public:
		BB() { std::cout << "BB"; }
		~BB()
		{
			std::cout << "~BB";
			throw 55;
		}
	};
	
	class Ok
	{
	public:
		Ok() { std::cout << "Ok"; }
		~Ok()
		{
			std::cout << "~Ok";
		}
	};
	
	
	void main()
	{
		try
		{
			std::cout << "try";
			BB b;
			AA a;
			Ok k;
			throw 6;
		}
		catch (int n)
		{
			std::cout << "catch";
		}
	}

# Корректность копирования

	#include <cstring>
	#include <algorithm>
	
	class string
	{
		char* data;
		int size;
	
	public:
	
		string(const char* p)
		{
			size_t size = strlen(p) + 1;
			data = new char[size];
			memcpy(data, p, size);
		}
	
		~string()
		{
			delete[] data;
		}
	
		string(const string& that)
		{
			size_t size = strlen(that.data) + 1;
			data = new char[size];
			memcpy(data, that.data, size);
		}
	
	
		string& operator=(string that)
		{
			std::swap(data, that.data);
			return *this;
		}
	
	
		string& operator=(const string& other)
		{
			name = other.name;
			return *this;
		}
	
		string(const string& _foo) // Конструктор копий.
		{
			this->m_name = _foo.m_name;
		}
	
		string& operator=(const string& _other) // Оператор присваивания.
		{
			if (this != &_other)
			{
				this->m_name += "_copied_" + _other.m_name;
			}
			return *this;
		}
	
		// Семантика перемещения.
		string(string&& that)   // string&& is an rvalue reference to a string
		{
			// 1-st option
			// this->swap(other);
	
			// 2-nd option
			this->data = that.data;
			that.data = nullptr; // ???
		}
	
		string& operator=(string&& _that)
		{
			if (this != &_that)
			{
				this->data = std::move(_that.data);
			}
			return *this;
		}
	};
	
	
	


# QT - РАЗНИЦА между СИГНАЛЫ и СОБЫТИЯ.

События могут обрабатываться лишь одним методом, а сигналы многими слотами



http://aristeia.com/TalkNotes/C++_Embedded_Deutsch.pdf

https://www.aristeia.com/

https://stepik.org/course/363/

http://spiskicpp.blogspot.ru/p/blog-page_5191.html

http://abkov.ru/rvsn/pgm/examena-2014-vo1-x10.pdf

http://cppstudio.com/cat/285/


# 18.02.2012. Источник: С. Мейерс — Эффективное использование C++.
Тонкость не совсем олимпиадная, но очень интересная. Рассмотрим следующий код:

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
    
А теперь результат его исполнения: http://ideone.com/DcY4o.
При вызове виртуальной функции, функция выбирается в зависимости от динамического типа (то есть от типа объекта на который в данный момент указывает указатель), а параметры по-умолчанию — от статического типа (то есть определенного в момент объявления). По-этому, когда мы пишем A* b = new B(); b->print();, мы вызываем функцию класса B(динамический тип), но с параметром по-умолчанию класса А (статический тип).

# Семантика перемещения:

https://stackoverflow.com/questions/3106110/what-are-move-semantics


http://qaru.site/questions/2259/c-unified-assignment-operator-move-semantics

http://www.cplusplus.com/forum/general/63416/

http://www.geeksforgeeks.org/copy-constructor-in-cpp/

https://codereview.stackexchange.com/questions/103744/deepptr-a-deep-copying-unique-ptr-wrapper-in-c

http://www.cplusplus.com/forum/general/163948/


# Семантика перемещения и EXEPTION-Safety:

https://akrzemi1.wordpress.com/2011/08/11/move-constructor/

http://modernescpp.com/index.php/component/jaggyblog/c-core-guidelines-copy-and-move-rules


vector& operator=( vector&& other ) noexcept  // since C++17)


# о RVALUE и LVALUE:

http://www.bogotobogo.com/cplusplus/C11/5_C11_Move_Semantics_Rvalue_Reference.php


# Как правильно завести ostream& operator<< в класс через friend:
http://www.learncpp.com/cpp-tutorial/915-shallow-vs-deep-copying/

Ответ:

std::ostream& operator<<(std::ostream& out, const Fraction &f1)

Пример:

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



# Составить частотный словарь вводимого текста. Распечатать его по алфавиту.

http://www.cyberforum.ru/cpp-beginners/thread410311.html

	
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
	

http://forum.codenet.ru/q39184/

Липпман.Язык программирвания С++

	#include "stdafx.h"
	#include <iostream>
	#include <vector>
	#include <map>
	#include <string>
	#include <algorithm>
	
	using namespace std;
	
	int _tmain(int argc, _TCHAR* argv[])
	{
		wcout.imbue(locale(".866"));
		wcout << L"Вводите текст" << endl;
		string s;
		vector<string> vec;
		while (cin >> s)
			vec.push_back(s);
		wcout << L"Частота с какой встречаются слова" << endl;
		vector<int> v;
		for (size_t i = 0; i<vec.size(); ++i) {
			int count = 0;
			vector<string>::iterator it = find(vec.begin(), vec.end(), vec);
			for (vector<string>::iterator iter = vec.begin();
				iter != vec.end(); ++iter) {
				if (*iter == *it) ++count;
			}
			v.push_back(count);
		}
		map<string, int> m_map;
		for (size_t i = 0; i<vec.size(); ++i)
			m_map[vec] = v;
		for (map<string, int>::iterator iter = m_map.begin(); iter !=
			m_map.end(); ++iter) {
			cout << iter->first << ' ' << iter->second << endl;
		}
		return 0;
	}

# РАЗВЁРНУТОЕ ГЛУБОКОЕ КОПИРОВАНИЕ

	class A {
	private:
	 	unsigned int max;
	 	unsigned int dummy;
	 	int *data;
	};
	
	// Конструктор копий с развернутым копированием
	INT_ARRAY::INT_ARRAY(const INT_ARRAY& rhs)
	{
		delete[] data; //освобождаем память
		max = rhs.max;
		dummy = rhs.dummy;
		data = new int[dummy]; //выделяем новый блок
		for (unsigned int j = 0; j<duinmy; j++)
			data[j] = rhs.data[j]; //копируем данные
	}
	// Операция присваивания с развернутым копированием
	INT_ARRAY& INT_ARRAY::operator=(const INT_ARRAY&rhs)
	{
		if (this == &rhs) return *this;
		// Обратите внимание, что код идентичен тому, 
		// что используется в конструкторе копий
		delete[] data;
		max = rhs.max;
		dummy = rhs.dummy;
		data = new int[dummy];
		for (unsigned int j = 0; j<dummy; j++)
			data[j] = rhs.data[j];
		return *this;
	}


# STATIC

(!)  обнулить массив простых типоа (к примеру int, char) можно не через вызов ZeroMemory, и т.п., а через 
	 char buffer[256] = { 0 };

(!)  Для массива объектов С++ вызывается конструктор по умолчанию, если не задан явный вызов конструктора
	 Если явный вызов конструктора задан, ТО для классов наследников !!! ???

(!)  Функтор в С++ это объект у которого перегружен operator()
	 т.е. внешне эксземпляр класса может быть похож на функцию и использоваться как функция

(!)  Функтор это функция с состоянием

(!)  const-антный метод класса не имеет права изменять состояние экземпляра класса
	 (элементов, членов класса) ЗА ИСКЛЮЧНИЕМ те, которые помечены ключевым словом
	 mutable

(!)  static-методы класса имеют доступ только к статическим полям класса, т.к.
	 static-методы не имеют прямой связи с конкретным экземпляром класса

(!)  преобразование:
func(char* ptr) : // read / write
	...
	char buf[256]; const char* const ptr;
	const char* ptr2 = "MyName"; // READ ONLY !

	func(buf);
	func(ptr2); // ERROR
	
# CONST

    int i = 1, ii=2, iii=3;
    int k = 10;

	// ВАЖНО ТОЛЬКО ОДНО: CONST стоит ДО звёздочки или ПОСЛЕ
	// ЕСЛИ  const  стоит рядом с ПЕРЕМЕННОЙ(переменная сразу справа от конст), то константна именно переменная а не содержимое
	// ЕСЛИ  const  cтоит перед ЗВЁЗДОЧКОЙ, значит константна "операция звёздочка", и НЕЛЬЗЯ обращаться по *p !!!

    int* const p1(&i); // Позволяет задать константность указателя
    // идентичные записи // Указатель на целое, которое нельзя менять
    int const* p2(&ii);
    const int* p3(&iii);

    // Данные на которые ссылается указатель менять можно. Сам Указатель НЕЛЬЗЯ
    *p1 = k;	// Ok 
    //p1 = &k;	// error C3892: 'p1' : you cannot assign to a variable that is const 

    //*p2 = k;	// error C3892: 'p2' : you cannot assign to a variable that is const 
    p2 = &k;	// Ok 
    //*p3 = k;	// error C3892: 'p3' : you cannot assign to a variable that is const 
    p3 = &k;	// Ok 

    return 0;

# Оператор сравненя (0) Нужно ли дополнительно определять operator== ?

	Равенство не нужно доопределять, оно выводится из "меньше" путём:
	!(a < b) && !(b < a)
 
#  Правильное примнение оператора сравненя (1)
// Что ели нужно "упорядочить" / "отсортировать" SET из структур такого типа:

	struct MyStruct
	{
		int i;
		std::string str;
	}

// ОТВЕТ:

	inline bool operator<(const DescriptionOfFsObject& _first, const DescriptionOfFsObject& _second)
	{

		if (_first.path < _second.path)
		{
			return true;
		}	
		else if (_first.path == _second.path)
		{
			return _first.type < _second.type;
		}

		return false;
	}



#  Правильное примнение оператора сравненя (2)
// Что ели нужно "упорядочить" / "отсортировать" SET из уже имеющихся структур Операционной системы:

// Что если мы хотим положить в  std::set  какую-нибудь системную структуру,
  не созданную нами, но уже готовую и присуствующую в системе, например WNDCLASSEXW:

https://msdn.microsoft.com/en-us/library/windows/desktop/ms633576(v=vs.85).aspx

Решение: переопределить орператор сравнения / оператор меньше

	bool operator <(WNDCLASSEXW const & a, WNDCLASSEXW const & b)
	{
	  return a.cbSize < b.cbSize;
	}
	
Описание структуры:

	/*
	typedef struct tagWNDCLASSEXW
	{
		UINT        cbSize;
		// Win 3.x
		UINT        style;
		WNDPROC     lpfnWndProc;
		int         cbClsExtra;
		int         cbWndExtra;
		HINSTANCE   hInstance;
		HICON       hIcon;
		HCURSOR     hCursor;
		HBRUSH      hbrBackground;
		LPCWSTR     lpszMenuName;
		LPCWSTR     lpszClassName;
		// Win 4.0
		HICON       hIconSm;
	} WNDCLASSEXW, *PWNDCLASSEXW, NEAR *NPWNDCLASSEXW, FAR *LPWNDCLASSEXW;
	*/
	
	//* ----------------------------------------------------------------------- QUESTION 2
	#include <windows.h>
	
	#include <set>
	#include <iostream>
	
	int main()
	{
		//WNDCLASSEX;
		std::set<WNDCLASSEX> st;
		WNDCLASSEX w_1;
		w_1.style = 3;
		WNDCLASSEX w_2;
		w_1.style = 2;
		WNDCLASSEX w_3;
		w_1.style = 1;
	
		st.insert(w_1);
		st.insert(w_2);
		st.insert(w_3);
	
		for (auto it : st)
		{
			std::cout << it.style << std::endl;
		}
	
		return 0;
	}
	//*/

# [Q] ЧТО БУДЕТ ?
// Данный вопрос примерно о том же что и предыдущий

	void DoPrint(std::string& str)  { std::cout << str.c_str(); }
	void DoPrint2(const std::string& str) { std::cout << str.c_str(); }
	void main(void)
	{
	    char* str = "abc";
	    DoPrint(str); // ERROR // NON CONST  can not be initialized with a value of type char*
	    DoPrint2(str);
	}


# Класс:

	class A
	{
	  public:
	  A();
	  ~A();
	  A(const& A _obj);
	  const& A operator=(const& A _obj);
	  A(const&& A _obj);
	  const& A operator=(const&& A _obj);  
	}

# Типы контейнеров:

- bitset	Битовое множество	<bitset>
- deque	Дек (двусторонняя очередь, очередь с двусторонним доступом)	<deque>
- list	Линейный список	<list>
- map	Отображение. Хранит пары "ключ-значение", в которых каждый ключ связан только с одним значением	<map>
- multimap	Мультиотображение. Хранит пары "ключ-значение", в которых каждый ключ может быть связан с двумя или более значениями	<map>
- multiset	Множество, в котором каждый элемент необязательно уникален	<set>
- priority_queue	Приоритетная очередь	<queue>
- queue	Очередь	<queue>
- set	Множество, в котором каждый элемент уникален	<set>
- stack	Стек	<stack>
- vector	Динамический массив	<vector>

# Vector
- Вставка и удаление возможно только с конца вектора. Вставка, удаление при использовании insert, erase занимает линейное время, пропорциональное длине последовательности, хранящейся в контейнере.
- Доступ к элементам произвольный. Занимает постоянное время.
- Сортировка возможна с применением функции sort.
- Вставка в конец требует постоянного времени, но если требуется перераспределение, то требуется линейное время.
- Из всех функций получения элемента вектора наиболее безопасной считается at()  т.к. в случае неверного индекса она выбрасывает исключение out_of_range . Все остальные ([], front, back) обладают неопределённым поведением.
- Итератор остается действительным до момента вставки или удаления элемента с меньшим индексом или перераспределения памяти с изменением ёмкости.
- Вставка и удаление элементов выполняется быстрее, если группа элементов обрабатывается одним вызовом вместо нескольких последовательных вызовов.
- Для любого действительного индекса i в векторе v заведомо истинно следующее условие: &v[i] == &v[0] + i;
- Если используемые элементы не генерируют исключений (в операторе присваивания, копирующем конструкторе, конструкторе), то любая операция  либо выполняется успешно, либо не вносит изменений в контейнер.
- Vector<bool> является особым типом вектора, он не удовлетворяет всем требованиям других векторов. Его итератор не является итератором произвольного доступа. Один элемент вектора занимает один бит памяти.

# Dequeue
- Вставка и удаление возможна в конец и начало. Вставка, удаление при использовании insert, erase занимает линейное время, пропорциональное длине последовательности, хранящейся в контейнере.
- Доступ к элементам произвольный. Занимает постоянное время.
- Внутренняя структура содержит ряд ссылок связывающих между собой блоки выделенной памяти, поэтому обращение к элементам и перемещение итератора выполняется медленнее, чем в векторах.
- Деки не позволяют управлять ёмкостью и моментом перераспределения памяти. При вставке элемента в конец, середину или начало, становятся недействительными все итераторы, ссылающиеся на элементы дека. Однако перераспределение памяти выполняется быстрее, чем в векторах из-за особенностей реализации (блочной).
- Вставка или удаление может привести к перераспределению памяти, в результате чего могут стать недействительными все указатели, ссылки и итераторы, ссылающиеся на другие элементы дека. Сюда не относится вставка, удаление   с конца, начала дека – в этом случае ссылки и указатели на элементы (но не итераторы) остаются действительными.
- Сортировка возможна с применением функции sort.

# List
- Вставка и удаление возможна в произвольном месте, выполняется за постоянное время.
- Нет произвольного доступа.
- В результате вставки и удаления элементов указатели, ссылки и итераторы, относящиеся к другим элементам, остаются действительными.
- Список реализован таким образом, что любая операция над ним либо совершается, либо нет. Список не может находиться в промежуточном состоянии.
- Возможна сортировка функцией членом sort.
- Функция-член list<T>::remove – это единственная функция, которая действительно удаляет элементы (выполняет фактическое удаление, т.е. erase вызывать после нее не требуется). Другая же одноименная функция-алгоритм remove занимается уплотнением элементов коллекции, после работы, которой требуется вызывать erase для удаления элементов и изменения размера контейнера.

# Set
- Не содержат дубликатов, элементы автоматически сортируются, из-за чего накладываются ограничения – значения элементов нельзя изменять напрямую, так как это нарушит порядок сортировки.
- Не поддерживают прямое обращение к элементам.
- Элемента двух множеств будут равны только в том случае, если будут равны их критерии сортировки.
- Реализовано с использованием красно-чёрного дерева.

#  Map, Multimap (отображения, мультиотображения)
- Элементы представляются в виде пары – ключ/значение.
- Сортировка элементов производится автоматически на основании критерия сортировки, применяемого к ключу. Отличие в том, что мультимапы могут содержать дубликаты.
- Ключ элемента нельзя удалять напрямую, так как это нарушает порядок сортировки. Для этого нужно удалить старый ключ и вставить новый.
- Модификация значения разрешена, если только значение не константное.
- Отображения поддерживают операцию индексирования [key] для прямого обращения к элементам. В случае если элемент с заданным ключом отсутствует в отображении, он автоматически создается и инициализируется значением по умолчанию, базовым конструктором. Таким образом, с помощью оператора индексирования можно добавлять элементы в отображение, однако эффективнее воспользоваться операцией вставки (insert).

# unordered_set (хеш-контейнер)
- Операция вставки и поиска выполняется за постоянное время O(1). Однако в случае, если потребуется перестройка хеш-таблицы время вставки будет линейным O(n).
- Данный контейнер разумно использовать при частых операциях вставки, удаления и поиска.
- Отличается от hash_set, тем что первый не входит в стандарт библиотеки.


# Типы итераторов:

- Произвольного доступа (random access)	Сохраняют и считывают значения; позволяют организовать произвольный доступ к элементам контейнера
- Двунаправленные (bidirectional)	Сохраняют и считывают значения; обеспечивают инкрементно-декрементное перемещение
- Однонаправленные (forward)	Сохраняют и считывают значения; обеспечивают только инкрементное перемещение
- Входные (input)	Считывают, но не записывают значения; обеспечивают только инкрементное перемещение
- Выходные (output)	Записывают, но не считывают значения; обеспечивают только инкрементное перемещение

# Проблема увеличения и уменьшения итераторов в векторах 
– При применении к итераторам векторов операций инкремента и декремента – и ++ могут возникать ошибки компиляции. Это обусловлено тем, что итераторы в векторах зачастую реализуются как обыкновенные указатели, а для них, как для всех базовых типов запрещена модификация временных объектов. Данный вызов будет считаться ошибочным sort(++vec.begin(), vec.end()) т.к. begin() вернёт временный объект базового типа.

# Алгоритмы НЕ могут использоваться со СПИСКАМИ, потому что списки не поддерживают итераторы ПРОИЗВ. доступа.


# Что такое дружественная функция? friend функция, класс друг, классы друзья. Приведите пример.
Дружественная функция — это функция, не являющаяся членом класса, имеющая доступ к закрытым членам класса, для которого она объявляется другом. Объявляется с ключевым словом friend с модификатором доступа public. Может быть как членом класса, так и нет.
Пример: 

	class Sample {
	private: int a,b;
	public:  friend int Min(Sample s);
	};

	int Min(Sample s){
		return s.a<s.b? s.a: s.b;
	}

#   Умные указатели смысл их появления:
- чтобы не очистить память дважды одну и туже
- чтобы единожды, но гарантированно удалить то что нужно
-- как следтсвие, чтобы избежать утечек памяти и прочих ресурсов




1) переслушать про reserve и resize

2)


# POSIX 7

https://unix.stackexchange.com/questions/11983/what-exactly-is-posix/220877




	NO C++ in Vacancy Name but C++
	https://kirov.hh.ru/vacancy/23144646?query=c%2B%2B

	С++
	https://kirov.hh.ru/vacancy/23270054?query=c%2B%2B - Уже вышло на меня по ходу
	Wind:
	https://kirov.hh.ru/vacancy/23181785?query=c%2B%2B
	https://kirov.hh.ru/vacancy/23237800?query=c%2B%2B
	https://kirov.hh.ru/vacancy/21891258?query=c%2B%2B
	https://kirov.hh.ru/vacancy/23236640?query=c%2B%2B
	https://kirov.hh.ru/vacancy/23151665?query=c%2B%2B
	https://kirov.hh.ru/vacancy/22016378?query=c%2B%2B
	https://kirov.hh.ru/vacancy/23417107?query=c%2B%2B
	https://kirov.hh.ru/vacancy/23376142?query=c%2B%2B
	Linx:
	https://kirov.hh.ru/vacancy/23206905?query=c%2B%2B
	https://kirov.hh.ru/vacancy/22599145?query=c%2B%2B
	https://kirov.hh.ru/vacancy/20893162?query=c%2B%2B
	https://kirov.hh.ru/vacancy/23330633?query=c%2B%2B
	https://kirov.hh.ru/vacancy/22812098?query=c%2B%2B
	https://kirov.hh.ru/vacancy/23097871?query=c%2B%2B
	https://kirov.hh.ru/vacancy/22469683?query=c%2B%2B
	https://kirov.hh.ru/vacancy/23100251?query=c%2B%2B
	https://kirov.hh.ru/vacancy/23079292?query=c%2B%2B
	
	TEAM_LEADING
	https://kirov.hh.ru/vacancy/23372477?query=c%2B%2B
	https://kirov.hh.ru/vacancy/23095234?query=c%2B%2B
	
	NOT C++ but includes C++
	https://kirov.hh.ru/vacancy/22677653?query=c%2B%2B
	https://kirov.hh.ru/vacancy/22812104?query=c%2B%2B
	https://kirov.hh.ru/vacancy/22391805?query=c%2B%2B
	https://kirov.hh.ru/vacancy/23091244?query=c%2B%2B
	https://kirov.hh.ru/vacancy/23158654?query=c%2B%2B
	https://kirov.hh.ru/vacancy/22689520?query=c%2B%2B
	https://kirov.hh.ru/vacancy/23355290?query=c%2B%2B
	
	NOT A CODER
	https://kirov.hh.ru/vacancy/23389918?query=c%2B%2B
	


Методология - писать вообще без классов


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

_beginthreadex

RunTime-функция: она запустится - и будет задействоват Thread Local Storage.

Она запустится - выделит память и будет ею пользоваться, а когда процесс будет умирать.

CreateThread  (не создаёт такого окружения для работы с рантаймовскими библами и объектами) не запускается таким образом, чтобы создать рантайм-обхекты и как следствие он не вызывает и деструкторов этих объектов.

А _beginthreadEx - Удалить так же ещё и вспомогательную информацию, что хранится в этих самых объектах рантаймовских (бибоиотечных).
Если их не удалить, то произойти своеобразная утечка памяти может.



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
# Шаблоны проектирования:

- Синглтон
- Фассад
- Ресивер
- Обзёрвер
- Листенер
- Фабрика
- Декоратор

- Док - Вью




# SQL

GroupBy HAVING


# Ошибки в программе под ОС Windows

Информация об ошибках
0. Логирование в файл событий  
+ рабочее решение
- замедляет работу программы
- нужно вовремя включить
- не всегда есть гарантия записи в файл

Две категории ошибок:
- 1) Падение
- 2) Зависание

 Дедлок / Поток / Процесс завис / зацикливание  
Если зависло у нас - то на этапе дебага, можем использовать WinDbg -> Attach to process
Если процесс завис у пользователя можем попробовать сделать то же самое, НО есть его у него нет
Через диспетчер задач он может сказать какой у него процесс завис (имя),
Process Explorer может выдать нам выдать про процесс более подробную инфу.
Пользователь не имеет прав на УСТАНОВКУ, так что без установки стороннего ПО и нельзя через TeamViewer получить доступ на ПК, у него ЕСТЬ права на Запуск.

Девочка / Мальчик из тех поддержки:

------------------------------------------------------------------
111]  ЗАВИСАНИЯ

1) Без подключения и без запуска:

- EventLog виндовый посмотреть
- Создать файл дампа через Диспетчер задач - на рабочем зависшем или независшем короче ещё работающем процессе.
Снять несколько "отпечатков/слепков"файлов дампа процесса. По ним (10 штук) можно примерно понять что происходит.

2) С запуском чего-то от нас:
- ProcessExplorer - Дампы + общая миниинфа
- ProcessMonitor - Полный лог работы этого процесса
-- куда лезет
-- какие мьютексы открывает
-- call стеки какие вызывает
Полное логирование в общем + дамп => отсюда можно практически всё понять в чём проблема.

ProcessMonitor - профилировщик удалённый, который аттачится к процессу.

МИНУС: Нудны права на установку этого софта.

------------------------------------------------------------------
222]  ПАДЕНИЯ

222.1] В режиме ОС:
- PageFault
- AccesVialation

http://citforum.ru/programming/delphi/delphi_bugs.shtml

AccesVialation
- имя библиотеки / имя dll - где оно произошло ПО такому-то Адресу:
0х123... Как найти процедуру функции, в которой произошло это падение - 

	Access violation at address <HEX_value>
	in module <Application.Exe>.
	Read of address <HEX_value_2>

- 1. Статический анализ ситуации - чтобы понять ГДЕ - ТОЧКА
- 2. А по ТОЧКЕ делать какие-то выводы.

Если второй адрес при выдачи ошибки - FFFFFFF (или 0000000) Вы можете почти утверждать, что было обращение к объекту, который еще не был создан. Например, вызов метода формы, которая не была создана.

	procedure TfrMain.OnCreate(Sender: TObject);
	var BadForm: TBadForm;
	begin
		BadForm.Refresh; // причина  ошибки
	end;

	
DLL: Во время сборки проекта так же 
- lib
- idl
- map

- PDB - Programm Data Base - инфа о скомпилиоованной программе.
-- вызовы функций
-- параметры
-- смещеня 

В случае анализа ДАМПА + PDB файл становится очень информативен.
- map - Файл текстовый со всемми точками входа для всех функций, сгенерированных в рамках данной библиотеки
  У каждой точки входа есть своё смещение 

ИТАК Получив Адрес из Исключения - Мы открывваем МЭП файл, там написано с какого смещения начинается какая функция
мы берём этот адрес смотим в какой диапазон / функцию он попадает  => получаем имя функуции и смещение относительно этой функции
открываем дизасемблер смотрим по кодам и получаем кокнретную точку, где и что происзошло, с какими ПАРАМЕТРАМИ.

Это СТАТИЧЕСКИЙ анализ - можем попробовать повторить ситуацию, повызывать функцию именно с такими параметрами и попытка воспросизвести ошибку.


222.2] Внутренние ошибки:
- Exeptions
- Некорректное поведение (внутренняя логика ПО)

Кокнретный шаг - Exception 
- имя библиотеки / имя dll - где оно произошло 
- Адрес, который нам это исключение выдало 



# УТЕЧКИ ПАМЯТИ - РАЗРАСТАНИЕ ПАМЯТИ ПРОЦЕССА ВО ВРЕМЯ РАБОТЫ

# MEMORY LEAKS DETECTION - Утечки памяти (диагностика)

https://habrahabr.ru/post/82514/

CRT

https://rsdn.org/article/vcpp/leaks.xml

Активизация режима обнаружения утечек памяти

Самые главные ваши помощники в борьбе с утечками памяти - отладчик и функции отладочной "кучи" из CRT. Чтобы активизировать эти функции, нужно включить в программу следующие строки:


	#define _CRTDBG_MAP_ALLOC
	#include <stdlib.h>
	#include <crtdbg.h>

После того, как вы добавили в вашу программу указанные строчки, вы можете получить информацию об утечках памяти, обратившись к функции
	
	_CrtDumpMemoryLeaks();

Когда программа выполняется под управлением отладчика, _CrtDumpMemoryLeaks отображает информацию об утечках памяти на вкладке Debug окна Output. Эта информация выглядит примерно так:

	Detected memory leaks!
	Dumping objects ->
	C:\PROGRAM FILES\VISUAL STUDIO\MyProjects\leaktest\leaktest.cpp(20) : {18} normal block at 0x00780E80, 64 bytes long.
	 Data: <                > CD CD CD CD CD CD CD CD CD CD CD CD CD CD CD CD 
	Object dump complete.

Если бы вы не включили в программу директиву #define _CRTDBG_MAP_ALLOC, отчёт выглядел бы так:

	Detected memory leaks!
	Dumping objects ->
	{18} normal block at 0x00780E80, 64 bytes long.
	 Data: <                > CD CD CD CD CD CD CD CD CD CD CD CD CD CD CD CD 
	Object dump complete.
	
Как видите, _CrtDumpMemoryLeaks выдаёт гораздо более полезную информацию, когда символ _CRTDBG_MAP_ALLOC определён. Без него вам выдаются следующие данные:

- порядковый номер распределения памяти (в фигурных скобках).
- тип блока (нормальный, клиентский или CRT-блок).
- адрес блока (в шестнадцатеричном представлении).
- размер блока в байтах.
- содержимое первых 16 байт этого блока (также в шестнадцатеричном представлении).

Если _CRTDBG_MAP_ALLOC определён, вам дополнительно показывается имя файла, в котором произошло распределение памяти. После имени файла в скобках содержится номер строки (20 в нашем примере). Если сделать двойной щелчок на строчке, содержащей имя файла и номер строки в нём:

	C:\PROGRAM FILES\VISUAL STUDIO\MyProjects\leaktest\leaktest.cpp(20) : {18} normal block at 0x00780E80, 64 bytes long.
	
то курсор переместится на строку в файле с исходным кодом программы (в нашем примере строку 20 в файле leaktest.cpp), где произошло распределение памяти. Аналогичного эффекта можно добиться, выделив строчку и нажав F4.

Использование _CrtSetDbgFlag

Если ваша программа всегда завершается в одном и том же месте, использовать _CrtDumpMemoryLeaks достаточно просто. А что делать, если программа может завершаться в различных местах? Вместо того, чтобы расставлять по всей программе вызовы _CrtDumpMemoryLeaks, вы можете разместить в начале программы следующий код:

	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
После этого функция _CrtDumpMemoryLeaks будет автоматически вызываться перед завершением работы вашей программы. Вы должны задать оба флага (_CRTDBG_ALLOC_MEM_DF и _CRTDBG_LEAK_CHECK_DF), как это показано выше.

- Установка режима сообщений CRT
- Установка точки останова на нужном распределении памяти
- Сравнение состояний памяти

Чтобы определить, не было ли утечек памяти на каком-то участке вашей программы, вы можете сделать "снимки" памяти до и после этого участка, а затем вызвать _CrtMemDifference, чтобы сравнить два состояния:

	_CrtMemCheckpoint( &s1 );
	// memory allocations take place here
	_CrtMemCheckpoint( &s2 );

	if ( _CrtMemDifference( &s3, &s1, &s2) ) 
	   _CrtMemDumpStatistics( &s3 );




# Deadlock

# Race conditions

# Allocator
https://habrahabr.ru/post/270009/

http://www.quizful.net/interview/cpp/allocator-in-cpp

Аллокатор это шаблонный класс, который отвечает за выделение памяти и создание объектов. По умолчанию все контейнера используют std::allocator<T>. 
В языке c++ имеется так же возможность написать свой аллокатор. У своего алокатора должно быть такое объявление:


	template <class T>
	class my_allocator
	{
		typedef size_t    size_type;
		typedef ptrdiff_t difference_type;
		typedef T*        pointer;
		typedef const T*  const_pointer;
		typedef T&        reference;
		typedef const T&  const_reference;
		typedef T         value_type;
	
		pointer allocate(size_type st, const void* hint = 0);
		void deallocate(pointer p, size_type st);
		void construct(pointer p, const_reference val);
		void destroy(pointer p);
		template <class U>
		struct rebind { typedef allocator<U> other; };
	};

# memory map files (mmap - Linux-version, CreateFileMapping and MapViewOfFile - WindowsVersion)
https://habrahabr.ru/post/55716/


Файлы, отображаемые в память
Программирование
В этой статье я хотел бы рассказать о такой замечательной штуке, как файлы, отображаемые в память(memory-mapped files, далее — MMF).
Иногда их использование может дать довольно таки существенный прирост производительности по сравнению с обычной буферизированной работой с файлами.

Это механизм, который позволяет отображать файлы на участок памяти. Таким образом, при чтении данных из неё, производится считывание соответствующих байт из файла. С записью аналогично. 
«Клёво, конечно, но что это даёт?» — спросите вы. Поясню на примере.
Допустим, перед нами стоит задача обработки большого файла(несколько десятков или даже сотен мегабайт). Казалось бы, задача тривиальна — открываем файл, поблочно копируем из него в память, обрабатываем. Что при этом происходит. Каждый блок копируется во временный кэш, затем из него в нашу память. И так с каждым блоком. Налицо неоптимальное расходование памяти под кэш + куча операций копирования. Что же делать?

///////////////////////////////////////////////////////

mmap:mmap() (или “memory map”) аналогичен brk(), но является более гибким инструментом. Во-первых, он может разметить память в любом месте адресного пространства, а не только в конце процесса. Во-вторых, он может не просто разметить память (виртуальную) как проекцию к физической или свопу (swap), он может привязать память к конкретным файлам так, что чтение и запись будут оперировать непосредственно с файлом. Антиподом mmap() является munmap().

Как вы можете видеть, простые вызовы brk() или mmap() могут быть использованы для расширения памяти процесса. Дальше по тексту будут использоваться brk() т.к. он является наиболее простым и распространённым инструментом.

# boost::aiso

http://alexott.net/ru/cpp/BoostAsioNotes.html

https://www.google.ru/url?sa=t&rct=j&q=&esrc=s&source=web&cd=10&cad=rja&uact=8&ved=0ahUKEwje09m7ja_XAhUoJJoKHfDUCbsQtwIIbjAJ&url=https%3A%2F%2Fwww.youtube.com%2Fwatch%3Fv%3DFotwf6qVXcI&usg=AOvVaw1nvr9NsKW6Fpe_bUouZo0p

# boost::bind

https://habrahabr.ru/post/310270/

https://habrahabr.ru/post/149056/

# std::ref()

Если в функцию необходимо передать параметры по ссылке, они должны быть обернуты в std::ref или std::cref, как в примере:

	void threadFunction(int &a)
	{ a++; }
 	
	int main()
	{
	     int a = 1;
	     std::thread thr(threadFunction, std::ref(a));
	     thr.join();
	     std::cout << a << std::endl; 
	     return 0;
	}

Программа напечатает в консоль 2. Если не использовать std::ref, то результатом работы программы будет 1.

# mutable

Ключевое слово - означает что член, объявленный с наличием mutable можно будет менять для константного полного объекта.

	class A{
	public:
 	  mutable int i;
	};
	
	void g()
	{
	   const A a;
	   a.i = 10;  //без mutable ERROR
	}


# STATIC + CLASSES

	int fun()
	{
		static int var = 0;
		var++;
		return var;
	}
	
	class A
	{
		public:
		int m_q;
		int m_b;
		A() : m_b(fun()), m_q(fun())
		{}
	
		int getQ() { return m_q; }
		int getB() { return m_b; }
	};
	
	int main()
	{
		A a;
		int r = a.getQ(); // = 1  ИБО инициализация будет в порядке объявления переменных внутри класса, т.е. сначала  
				  // m_q и потом m_b, а не в порядке следования в списке инициализации в рамках конструктора клсса.
		r = a.getB();	  // = 2
		return 0;
	}





# Interface in C++


https://habrahabr.ru/post/82514/


	class IDemo
	{
	    public:
	        virtual ~IDemo() {}
	        virtual void OverrideMe() = 0;
	};
	
	class Parent
	{
	    public:
	        virtual ~Parent();
	};
	
	class Child : public Parent, public IDemo
	{
	    public:
	        virtual void OverrideMe()
	        {
	            //do stuff
	        }
	};




# INVERT STRING:

	// Функция переворота строки / функция переворачивающая строку / функция для переворачивания строки
	// Функция разворота строки / функция разворачивающая строку / функция для разворачивания строки
	//*

	template <typename T >
	void invert_string(T &a)
	{
		T::size_type length = a.size();
		for (T::size_type i = 0; i < (length / 2); ++i)
		{
			std::swap(a[i], a[length - i - 1]);
		}
	}

	std::string str = "abcdefg";
	invert_string(str);


	void reverse(string &s)
	{
		int j = s.size() - 1;

		for (int i = 0; i < s.size() / 2; i++)
		{
			swap(s[i], s[j]);
			j--;
		}
	}



# bubble_sort

	// 2. Сортировка пузырьком (обменом)
	// Идея метода: шаг сортировки состоит в проходе снизу вверх по массиву. По пути просматриваются пары соседних элементов. Если элементы некоторой пары находятся в неправильном порядке, то меняем их местами.


	//*
	template< class T >
	void bubbleSort(T* arr, int size)
	{
		T tmp;

		for (int i = 0; i < size - 1; ++i) // i - номер прохода
		{
			for (int j = 0; j < size - 1; ++j) // внутренний цикл прохода
			{
				if (arr[j + 1] < arr[j])
				{
					tmp = arr[j + 1];
					arr[j + 1] = arr[j];
					arr[j] = tmp;
				}
			}
		}
	}
	//*/
	//*
	template <class T>
	void bubble_sort(T* a, int size)
	{
		T tmp;
		for (int i = 0; i < size - 1; ++i)
		{
			for (int j = 0; j < size - 1; ++j)
			{
				if (a[j + 1] < a[j])
				{
					tmp = a[j];
					a[j] = a[j + 1];
					a[j - 1] = tmp;
				}
			}
		}
	}

	// modified bubble_sort
	void bubble_sort_mod_1(int* a, int len)
	{
		int tmp = 0;
		bool sorted = true;
		while (!sorted)
		{
			sorted = true;
			for (int i = 0; i < n - 1; i++)
			{
				if (a[i] > a[i + 1])
				{
					tmp = a[i];
					a[i] = a[i + 1];
					a[i + 1] = tmp;
					sorted = false;
				}
			}
		}
	}


	// modified bubble_sort
	void bubble_sort_mod_2(int* a, int len)
	{
		int j = 1;
		int tmp = 0;
		bool sorted = true;
		while (!sorted)
		{
			sorted = true;
			for (int i = 0; i < n - j; i++)
			{
				if (a[i] > a[i + 1])
				{
					tmp = a[i];
					a[i] = a[i + 1];
					a[i + 1] = tmp;
					sorted = false;
				}
			}
			j++;
		}
	}



# Quick_sort


	quickSort(массив a, верхняя граница N) {
		Выбрать опорный элемент p - середину массива
			Разделить массив по этому элементу
			Если подмассив слева от p содержит более одного элемента,
			вызвать quickSort для него.
			Если подмассив справа от p содержит более одного элемента,
			вызвать quickSort для него.
	}



	template<class T>
	void quickSortR(T* a, long N) {
		// На входе - массив a[], a[N] - его последний элемент.

		long i = 0, j = N;      // поставить указатели на исходные места
		T temp, p;

		p = a[N >> 1];      // центральный элемент

					// процедура разделения
		do {
			while (a[i] < p) i++;
			while (a[j] > p) j--;

			if (i <= j) {
				temp = a[i]; a[i] = a[j]; a[j] = temp;
				i++; j--;
			}
		} while (i <= j);

		// рекурсивные вызовы, если есть, что сортировать 
		if (j > 0) quickSortR(a, j);
		if (N > i) quickSortR(a + i, N - i);
	}




# IMPORTANT LINKS:

http://job-interview.ru/questions/cpp/

https://tproger.ru/articles/problems/

https://rsdn.org/forum/job/2316994.flat

https://habrahabr.ru/post/200190/

http://www.devexp.ru/2010/03/o-kopirovanii-obektov-v-c/

http://www.quizful.net/post/neobhodimost-konstruktora-kopirovaniya-cpp

Алгоритмы

https://ru.stackoverflow.com/questions/307629/%D0%A1%D0%BE%D0%B1%D0%B5%D1%81%D0%B5%D0%B4%D0%BE%D0%B2%D0%B0%D0%BD%D0%B8%D0%B5-%D0%BF%D0%BE-%D0%B0%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC%D0%B0%D0%BC-%D0%BA%D0%B0%D0%BA-%D0%BF%D0%BE%D0%B4%D0%B3%D0%BE%D1%82%D0%BE%D0%B2%D0%B8%D1%82%D1%8C%D1%81%D1%8F-%D0%BA-%D0%BD%D0%B5%D0%BC%D1%83-%D0%B7%D0%B0-%D0%BE%D0%B4%D0%BD%D1%83-%D0%BD%D0%B5%D0%B4%D0%B5%D0%BB%D1%8E

Алгоритмическая “база” хорошего программиста:

https://ru.stackoverflow.com/questions/262661/%D0%90%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B0%D1%8F-%D0%B1%D0%B0%D0%B7%D0%B0-%D1%85%D0%BE%D1%80%D0%BE%D1%88%D0%B5%D0%B3%D0%BE-%D0%BF%D1%80%D0%BE%D0%B3%D1%80%D0%B0%D0%BC%D0%BC%D0%B8%D1%81%D1%82%D0%B0-%D0%92%D0%BE%D0%BF%D1%80%D0%BE%D1%81-%D0%BF%D0%BE-%D1%81%D0%B0%D0%BC%D0%BE%D1%80%D0%B0%D0%B7%D0%B2%D0%B8%D1%82%D0%B8%D1%8E

15 вопросов на собезах по Алгоритмам:

https://proglib.io/p/15-questions-for-programmers/


# CORRECT / буквальное (shallow copy) развернутое / глубокое копирование (deep copy) /  RValues + LValues + Move Semantic

	// https://www.youtube.com/watch?v=ruHw7E71zBw
	// https://www.youtube.com/watch?v=cO1lb2MiDr8
	
	#include <cstring>
	#include <string>
	#include <algorithm>
	
	class MyString
	{
		char* m_data;
		size_t m_size;
	
	public:
	
		MyString() : m_data(0), m_size(0)
		{
		}
	
		~MyString()
		{
			delete[] m_data;
			m_data = 0; // установка указателя в 0 позволяет проверять его недопустимость
		}
	
		// Спец конструктор
		//MyString("abc"); // how we will use the constructor
		MyString(const char* other)
		{
			m_size = strlen(other) + 1;
			m_data = new char[m_size];
	
			// 1 option
			memcpy(m_data, other, m_size);
	
			// 2 option
			for (int i = 0; i < m_size; i++)
			{
				m_data[i] = other[i];
			}
		}
	
		// Конструктор копий.
		//MyString(const MyString& that)
	
		// default  copy constructor  // буквальное (shallow copy)
		MyString(const MyString& that) // Конструктор копий.
		{
			m_data = that.m_data;
			m_size = that.m_size;
		}
	
		// развернутое / глубокое копирование (deep copy)
		// 1 option = BETTER
		MyString(const MyString& that)
			: m_size(that.m_size)
			, m_data(new char[m_size])
		{
			memcpy(m_data, that.m_data, m_size); // memcpy(m_data, that.m_data, sizeof(char) * m_size);
		}
	
			// 2-nd option
			MyString(const MyString& that)
		{
			m_size = that.m_size; //m_size = strlen(that.m_data) + 1;
			m_data = new char[m_size];
			memcpy(m_data, that.m_data, m_size);	// memcpy(m_data, that.m_data, sizeof(char) * m_size);
		}
	
		// Оператор присваивания.
		//MyString& operator=(const MyString& that)
	
		// default  operator=  // буквальное (shallow copy)
		MyString& operator=(const MyString& that) // нужен ли const ?
		{
			m_data = that.m_data;
			return *this;
		}
	
		// развернутое / глубокое копирование (deep copy)
		MyString& operator=(const MyString& that) // нужен ли const ?
		{
			if (this == &that)
				return *this;
	
			// 1 option
			m_size = that.m_size; //m_size = strlen(that.m_data) + 1;
			m_data = new char[m_size];
			memcpy(m_data, that.m_data, m_size);	// memcpy(m_data, that.m_data, sizeof(char) * m_size);
	
			// 2 option
			//m_size = that.m_size; //m_size = strlen(that.m_data) + 1;
	
			// not here						// COPY !!!
			// not here						// AND
			//std::swap(m_data, that.m_data); // SWAP !!!	// Если с  (CONST MyString that), то swap ругнётся can not convert!!!  char*, char* const
	
			return *this;
		}
	
		// Семантика перемещения.
	
		// Перемещающий Конструктор копий.
		//MyString(const MyString&& that)
	
		// default  move copy constructor  // буквальное (shallow copy)
		//	MyString(const MyString&& that)
		//	{
		//		this = that;
		//	}
	
		// развернутое / глубокое копирование (deep copy)
		MyString( /*const*/ MyString&& that) // НЕ НУЖЕН CONST (!!!) -  MyString&& is an rvalue reference to a MyString
			: m_data(that.m_data)
		{
			// 1-nd option
			this->m_data = that.m_data;
			this->m_size = that.m_size;
	
			that.m_data = nullptr;
			that.m_size = 0;
	
			// 2-st option
			std::swap(this->m_size, that.m_size);
			std::swap(this->m_data, that.m_data);
			// or
			std::swap(*this, that); // with c++11
		}
	
		// Перемещающий Оператор присваивания.
		//MyString& operator=(const MyString&& that)
	
		MyString& operator=(MyString&& that)
		{
			if (this != &that)
			{
				// 1-nd option
				this->m_data = that.m_data;
				this->m_size = that.m_size;
	
				that.m_data = nullptr;
				that.m_size = 0;
	
				// 2-st option
				std::swap(this->m_size, that.m_size);
				std::swap(this->m_data, that.m_data);
				// or
				std::swap(*this, that); // with c++11
			}
			return *this;
		}
	
	};
	
	
	void main()
	{
		int z = 0;
	}
	

# буквальное (shallow copy) развернутое / глубокое копирование (deep copy)

https://club.shelek.ru/viewart.php?id=247


Однако, именно с этой целью этот пример и приведен.

	
	// SMARRAY2.H - интерфейс интеллектуального массива
	#ifndef _SMARRAY2_H
	#define _SMARRAY2_H
	class INT_ARRAY
	{
	public:
		INT_ARRAY(unsigned int sz = 100);
		~INT_ARRAY();
		INT_ARRAY(const INT_ARRAY&); // Объявление конструктора копий
		INT_ARRAY& operator=(const INT_ARRAY&);// Объявление операции присваивания
							// Использование беззнаковых целых снимает необходимость
							// проверки на отрицательные индексы
		int& operator[](unsigned int index);
	
	private:
		unsigned int max;
		unsigned int dummy;
		int *data;
	};
	#endif


БУКВАЛЬНОЕ КОПИРОВАНИЕ

	
	// SMARRAY2.CPP - реализация интеллектуального массива
	#include <mem.h>
	#include [i]
	#include "smarray2.h"

	// Конструктор - Добавляет единицу к размеру массива для хранения
	// фиктивного значения на случай использования недопустимого индекса.
	INT_ARRAY::INT_ARRAY(unsigned int sz)
	{
		max = sz;
		dummy = sz + 1;
		data = new int[sz + 1];
		// Если  new возвращает допустимый блок памяти,
		// тогда data не нуль. Функция memset инициализирует
		// этот блок памяти значением 0.
		if (data) memset(data, 0, dummy);
		else max = -1;
	}


	// деструктор
	INT_ARRAY::~INT_ARRAY()
	{
		delete[] data; // освобождение массива
		data = 0; // установка указателя в 0 позволяет проверять 
				  // его недопустимость
	}

	// - Предупреждение -
	// Этот класс использует буквальное копирование.
	// Не пользуйтесь им в реальных программах.
	// Этот конструктор копий демонстрирует вариант
	// "буквального" конструктора, генерируемого компилятором.
	// Здесь не только два указателя ссылаются на один и тот же
	// блок памяти, но и, кроме того, не освобождается
	// старый блок.

	//конструктор копий
	INT_ARRAY::INT_ARRAY(const INT_ARRAY& rhs)
	{
		this->max = rhs.max;
		this->dummy = rhs.dummy;
		this->data = rhs.data;  // ОШИБКА: буквальное копирование
	}

	//оператор присваивания
	// Предупреждение - И здесь та же ошибка
	INT_ARRAY& INT_ARRAY::operator=(const INT_ARRAY& rhs)
	{
		if (this == &rhs) return *this;
		this->max = rhs.max;
		this->dummy = rhs.dummy;
		this->data = rhs.data;
		return *this;
	}

	// Очень кратко, но допустимость индекса проверяется.
	// Этот вид проблем - превосходный кандидат для
	// обработки исключительных ситуаций.
	int& INT_ARRAY::operator[](unsigned int index)
	{
		return index < max ? data[index] : data[dummy];
	}


	void main(void)
	{
		INT_ARRAY ouch;

		// Создается искусственная область видимости,
		// чтобы деструктор startMeUp был вызван первым
		{
			INT_ARRAY StartMeUp(10);
			for (unsigned int k = 0; k<10; k++)
				StartMeUp[k] = k;  // здесь работает operator[]
			ouch = StartMeUp;  // Вызов "ПЛОХОЙ" операции присваивания
							   // Демострация того факта, что 'ouch' и
							   // 'startMeUp' указывают на один и тот же блок памяти
			for (unsigned int k = 0; k<10; k++) cout << ouch[k] << endl;
		}
	}
	

РАЗВЁРНУТОЕ КОПИРОВАНИЕ

	
	// Конструктор копий с развернутым копированием
	INT_ARRAY::INT_ARRAY(const INT_ARRAY& rhs)
	{
		delete[] data; //освобождаем память
		max = rhs.max;
		dummy = rhs.dummy;
		data = new int[dummy]; //выделяем новый блок
		for (unsigned int j = 0; j<duinmy; j++)
			data[j] = rhs.data[j]; //копируем данные
	}
	// Операция присваивания с развернутым копированием
	INT_ARRAY& INT_ARRAY::operator=(const INT_ARRAY&rhs)
	{
		if (this == &rhs) return *this;
		// Обратите внимание, что код идентичен тому, 
		// что используется в конструкторе копий
		delete[] data;
		max = rhs.max;
		dummy = rhs.dummy;
		data = new int[dummy];
		for (unsigned int j = 0; j<dummy; j++)
			data[j] = rhs.data[j];
		return *this;
	}



# SAMPLE 

	#include <string>
	#include <iostream>
	using namespace std;
	
	
	void Func()
	{
		string s1("FIRST");
		string* s2 = new string("SECOND");
		string* s0 = &s1;
		cout << s0 << endl;
		s0 = s2;
		cout << s0 << endl;
		delete s0;
	}
	
	
	class A
	{
	public:
		A()			 {
			std::cout << "A" << std::endl;  }
		virtual ~A() {
			if (!this) return;
			std::cout << "~A" << std::endl; }
		virtual void Printer() { std::cout << "A print" << std::endl; }
	};
	
	class B : public A
	{
	public:
		B()  {
			std::cout << "B" << std::endl;  }
		~B() {
			if (!this) return;
			std::cout << "~B" << std::endl; }
		void Printer()	{ std::cout << "B print" << std::endl;	}
	};
	
	
	void test_0()
	{
		B b;
		B* bb = &b;
	}
	
	void test_1()
	{
		B b;
		A* ab = &b;
	}
	
	void test_1_del()
	{
		B b;
		A* ab = &b;
		delete ab;
	}
	
	void test_2()
	{
		A s1;
		A* s2 = new A();
		A* s0 = &s1;
		A* s3 = &s1;
		s0 = s2;
		delete s0;
		delete s3;
		// doiuble destructor CALL !!!!
		// 1-st call - delete s3 that points to s1
		// 2-nd call - exit from scope {}
	}
	
	
	void main()
	{
		//test_0();
		//test_1();
		//test_1_del();
		test_2();
		cout << "THIRD." << endl;
	}




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
К счастью, теперь есть способ избавиться от этих ошибок. Были добавлены два новых идентификатора (не ключевые слова): 

# override, 

для указания того, что метод является переопределением виртуального метода в базовом классе и final, указывающий что производный класс не должен переопределять виртуальный метод. Первый пример теперь выглядит так:

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




# 6 — Умные указатели / интеллектуальные указатели / smart pointer 

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



# 7 — лямбды / лямбда выражения

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

# Конструктор перемещения 

и

# перемещающий оператор присваивания 

— эти две специальные функции принимают параметр T&&, который является rvalue. Фактически, они могут изменять объект. 

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

По аналогии с Вирт.функциями в Конструкторах, только в обратном порядке всё

# Исключение в Конструкторах


	class static_Part_A
	{
	public:
		static_Part_A() {
			std::cout << "static_Part_A" << std::endl;
		}
		virtual ~static_Part_A() {
			std::cout << "~static_Part_A" << std::endl;
		}
	};
	
	class static_Inside_A
	{
	public:
		static_Inside_A() {
			std::cout << "static_Inside_A" << std::endl;
		}
		virtual ~static_Inside_A() {
			std::cout << "~static_Inside_A" << std::endl;
		}
	};
	
	class dynm_Part_A
	{
	public:
		dynm_Part_A() {
			std::cout << "dynm_Part_A" << std::endl;
		}
		virtual ~dynm_Part_A() {
			std::cout << "~dynm_Part_A" << std::endl;
		}
	};
	
	class dynm_Inside_A
	{
	public:
		dynm_Inside_A() {
			std::cout << "dynm_Inside_A" << std::endl;
		}
		virtual ~dynm_Inside_A() {
			std::cout << "~dynm_Inside_A" << std::endl;
		}
	};
	
	
	class A
	{
		dynm_Part_A* _dynm_Part_A;	// !!! ~ will NOT be called
		static_Part_A  _stat_Part_A; // ~ will be called
	public:
		A(): _dynm_Part_A(0) {
			std::cout << "A" << std::endl;
			static_Inside_A _static_Inside_A; // ~ will be called
			_dynm_Part_A = new dynm_Part_A();
			dynm_Inside_A* _dynm_Inside_A = new dynm_Inside_A(); // ~ !!! will NOT be called
			throw(1);
		}
		virtual ~A() {
			std::cout << "~A" << std::endl;
		}
	};
	
	void tstNew()
	{
		try {
			A a;
		}
		catch (...)	{
			std::cout << "catch" << std::endl;
		}
	
	}
	
	void main()
	{
		tstNew();
	}


https://pro-prof.com/forums/topic/constructor_destructor_exceptions

1) Программа не должна вырабатывать исключения во время обработки другого исключения (когда происходит раскрутка стека) – это приведет к аварийному завершению работы программы (фактически вызову abort()). (т.е. > 1 раза), то вызовится ф-ция terminate(), которая по умолчанию вызывает abort(), т.е. приложение завершается.

2) Если конструктор класса завершает работу исключением, значит он не завершает свою работу – следовательно объект не будет создан. Из-за этого могут возникать утечки памяти, т.к. для не полностью сконструированных объектов не будет вызван деструктор. Из-за этого распространено мнение, что конструктор никогда не должен вырабатывать исключения, однако это не так – утечки памяти возникнут не во всех случаях.

Стандарт языка С++ гарантирует, что если исключение возникнет в конструкторе, то памяти из под членов-данных класса будет освобождена корректно вызовом деструктора – т.е. если вы используете идиому RAII [2], то проблем не будет. Часто для этого достаточно использовать std::vector/std::string вместо старых массивов и строк, и умные указатели вместо обычных [3]. Если же вы продолжите использовать сырые указатели и динамически выделять память – нужно будет очень тщательно следить за ней, например в следующем фрагменте кода нет утечки, т.к. исключение будет выработано только если память не будет выделена [4]:

	template <class ElementType>
	Array<ElementType>::Array() : m_realSize(Step), m_size(0), m_array(0) { 
	  m_array = (ElementType*)malloc(sizeof(ElementType)*m_realSize);
	  if (0 == m_array) {
		throw bad_allocation();
	  }
	} 



# Исключение в деструкторах

1) Утечки ресурсов / некнтролируемое поведение
код код
	
	~B()
	{
	    delete this->resource;  // throws
	    close(this->socket);    // leaks
	}
	
код
2) Тем более очевидно, что если деструктор завершает работу исключением, то может возникать утечка памяти – в памяти могут остаться как части текущего класса, так и базовых классов. Из этого ясно, что деструктор никогда не должен вырабатывать исключения, а также обрабатывать все возможные исключения функций, которые вызывает – они могут приводить как к утечкам, так и к очень трудноуловимым ошибкам.

3) Предположим, что где-то в программе сгенерировано исключение. При этом начинается размотка стека и уничтожение автоматических объектов.

Если новое исключение генерируется в деструкторе уничтожаемого в процессе раскрутки объекта, то вызывается функция terminate(), которая по умолчанию вызывает abort(), т.е. приложение завершается.
Эту функцию можно подменить своей с помощью set_terminate(), но это уже другая история...
+ При разрушении статических объектов исключение в деструкторе также приведет к terminate().

Программа не должна вырабатывать исключения во время обработки другого исключения (когда происходит раскрутка стека) – это приведет к аварийному завершению работы программы (фактически вызову abort()).

4) vector<объектов> - если исключение в деструкторе сработало не в одномом элеменете а в нескольких (т.е. > 1 раза), то вызовится ф-ция terminate(), которая по умолчанию вызывает abort(), т.е. приложение завершается.



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
код

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
код

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



# ///  РАБОТА  ///

	CONNECT
	Законектились - Сервер начинает нас слушать RECIEVE
	Мы отправили эти данные SEND-ом.
	Сервер проситал эти данные.
	Прокол определён, сервер распарсил эту структуру.
	Определил -> Что это запрос такого-то метода.
	=> Выполнить этот метод на сервере.
	И вернули ответ. SEND.

	Пул Потоков - создали  Поток и внутри него 1 коннект между клиентом и счервером, и очередь сообщений / коннектов.
	По одному потоку на 1 подсистему (1-го клиента) на 1 КОННЕКТ 
	- в рамках коннекта делаем что нужно открыли соединение, закрыли соединение.
	Все потоки ПАРАЛЛЕЛЬНО.

# ////  ОТ СТАСА ПРО WINDOWS  ///

# Процесс:
- контейнер для потоков
- то чему принадлежит память

	Даже когда поток выделяет какую-то память, то это на самом деле память расположенное в адресном пространстве процесса, и эта память доступна ВСЕМ потокам

Объект Процесс - в Windows это объект ЯДРА.

Суть в том, что На ЛЮБОМ обекте ЯДРА можно ОЖИДАТЬ. ибо они ВСЕ могут находится в 2-ух состояниях - СИГНАЛЬНОЕ = Занят. НЕСИГНАЛЬНОЕ = Свободен.

Пример: Процесс - автообнолвения. Ждём и жержим ресурсы, пока не обновимся.

	Поток, Мьютекс, Евент, Семафор:
		СИГНАЛЬНОЕ = Занят. НЕСИГНАЛЬНОЕ = Свободен.

# 	Все потоки в процессе разделяют одно и тоже адресное пространство.

	Память: У каждого процесса его адресное пространство ИЗОЛИРОВАННО
	Адрес виртуальный один и тот же, а по факту в физической памяти они РАЗНЫЕ
	Указатель в одном процессе  - адрес память в 1-ом процессе -> физич. память Ячейка_1
	Указатель в другом процессе - адрес память в 2-ом процессе -> физич. память Ячейка_2
	
	На 1 виртуальный адрес  есть таблица Связи Виртуальныхи Физических адресов. 
	
	На 1 ВИРТУАЛЬНЫЙ адрес в виртуальном адресном пространстве -> ссылка на Страницу физической памяти.

	ВСЯ ПАМЯТЬ ПРОЦЕССА - Его виртуальое Адресное простраснство - ИЗОЛИРОВАНО от Адресных пространств всех Других процессов.


	В Заголовке Файла: У него есть несколько СЕКЦИЙ - read/write read_only Execute_image ... 
				Смотрится эта секция, и сколько памяти нужно



# (???) Можно ли себе выделить ЕЩЁ Больше Виртуальной памяти ?
Ответ: ДА !

WIRTUAL_ALLOC - выделяем предварително ДИАВПАЗОН Виртуальных адресов в адресном пространстве.
				(НА этом этапе только выделились адреса, НО НЕТ соответсвия с Физ.адресами на Диске)
				А потом MEM_COMMIT - Привязываем и работаем с этими адресами полноценно.

# ПРОЦЕСС имеет 2 СТЕКА:
- Ядерный - 16 Килобайт
- Юзермодный - Большой ~1Мб (Или задаём параметром в фции CreateThread() )

Когда мы делаем ситемный вызов какого-то API - CreateEvent() = СИСТЕМНЫЙ ВЫЗОВ - происходит переключение в Режим Ядра

А это означает, что ECX, EAX, ESP .... что эти регистры, STACK_POINTER - Мы эту информацию в (?) частности передаём через Стек Ядерный.

Подгрузка регистров произойдёт по очереди

Плюс перейдя в режим Ядра, мы используем только этот стек для вызовов Функции, работает ядро со своими внутренними вызовами 

+нам нужен этот стек чтобы когда раскрутка стека началсь бы ОБРАТНО, у нас был бы обратный вызов в нашу функцию юзермодную, к тому кто вызывал.

call - достаёт из стека адрес возврата и передаёт управление на этот адрес возврата. В какой-то момент ПЕРЕКЛЮЧАЕТСЯ "КОНТЕКСТ"
Для этого есть структура CONTEXT - она загружает регистры изменённые в ядре, на значения регистров Юзермодные.

	СТАРЫЙ СТЕK Ядерный с регистрами - зафиксировался.
	// вызвали Ядерную функцию = СИСТЕМЕНЫЙ ВЫЗОВ
	СЛЕПОК Стека изменённого после системного вызова возвращается обратно
	// Продолжаем работать в Юзермодном Режимею.

Юзермодный Стек - страницы памяти - 20 Мегабайт задали, зарезевировалось адресное пространство, но страниц зарезервировалось 2 страницы, а не всё, что мы запросили.
Следовательно: Например, когда мы начали использовать Серьёзную Рекрсию. Что может выявить собой то, что Стек по виртуальным Адресам растёт и мы движемся всё дальше и выше.
НАшей виральыной памяти не поставлена в соответсвии Физическая память. => ОС дополниетльно начинает подгркжать страницы физич. памяти на это Виртуальное Адресное пространство.

В каждом приложении много потоков. И всем запросам передаётся не вся память, ибо они итак не расходуют ВСЁ за РАЗ.


#  Мьютекс - свободен мьютекс - переводим в СИГНАЛЬНОЕ состояние = НЕ ЗАНЯТ / СИГНАЛЬНОЕ - ЗАНЯТ.

Неэффективность Мьютексов - переключение контекста из Пользоват. в режим Ядра это ценно по врмеени слишком.
Эффектвиность Мьютексов - только то,что его можно использовать в рамках ОДНОГО Процесса.

Ядро это всегда посредник, и в рамках одного процесса, нет смылса задействовать ядро (ибо ЗАТРАТНО), если на то нет необходимости.


# События - С Автосбросом / Без Автосброса.
Waitфункция - Евент сделали Ресет - Евента НЕТ. 
10 потоков сделали WaitForSingleObkect() и в ещё одном потоке мы делаем 

- AUTORESET_EVENT
- SetEvent() -> просыпается ОДИН поток , которые выполнил WaitForSinlgeObject()
	Просыпается и этот Евент переводится в Несигнальное состояние Автоматически.

- MANUALRESET_EVENT
- SetEvent() -> просыпаются ВСЕ потоки , и в  Несигнальное состояние 
	событие надо было бы перевести ЯВНО вызвав ResetEvent().


# (?) ПАМЯТЬ WINDOWS: Одному процессу Можно или нельзя писать в память Другого процесса ?

	МОЖНО - НО - Чтобы прочитать/записать что-то в другой процесс, нужно вызвать ЯВНО ReadProcessMemory() / WriteProcessMemory()
		передаём в функции ХЭНДЛ процесса, к которому у нас есть право доступа и 
		указатель на участок адресного пространства в которое нам нужно пичать/читать.


# (?) Есть HANDLE. Есть объект Ядра - Именованый Event. 
HANDLE = CreateEvent("Event_name"); // HANDLE - Дескриптор этого объекта Ядра. У каждого процесса есть таблица Дескрипторов.

Но получить доступ к этому объекту по ИМЕНИ евента ДРУГОЙ Процесс может открыть его по имени через OpenEvent();

Handle_1 = фактически актуальлен будет только в рамках одного нашего процесса (в которм мы его СОЗДАЛИ)

Handle_2 = фактически актуальлен будет только в рамках одного нашего процесса (в которм мы его ОТКРЫЛИ)

Мы не получили КОПИЮ Объекта. Мы просто получили Handle_2 - ИДЕКС в таблице Дескрипторов в рамках нашего процесса и более ничего, 
и только через дескриптор мы получаем доступ к самосу объекту, работая через системыне вызовы.


# (?) Как Получить доступ к Объекту Ядра Из Двух процессов:

- 1) Можно получить доступ - ОТКРЫТЬ объект по ИМЕНИ.
- 2) можно получить доступ - по РОДИТЕЛЬСКОЙ связи.
- 3) Явный вызов функции	 - DUPLICATE_HANDLE()


# (2)
В CreateProcess() - мы имеем такую штуку, как INHERITABLE - параметр - можно ли этот объект НАСЛЕДОВАТЬ, тоесть Процесс может передать Чайлду Те Индексы в твблице дескрипторов,
	у которых при создании самих объектов мы выставили параметр INHERITABLE.

	CreateProcess() // Paren
	{
	  // .. create some Kernel-Objects
	  CreateProcess(INHERITABLE) // Child
	  {
	    // get all the HANDLE-s of created Inheritable Parent Handles
	  }
	}


# (?) Что за параметр  ALTERABLE

Имеется в  WaitForSingleObjectEX(); EX !!!

ALTERABLE  - Для IPC процедур, она просыпается в тот момент, когда ты ожидаешь на каком-то фале и операция для записи - Когда асинхронная функуия выполнлось. и просыпается, если она выполняется.
	Просыпается поток, которые ждёт на файле на каком-то
	АСИНХРОННЫЙ вызов когда происходит - в тот момент, когда кто-то пишет или читает из Этого файла.

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
#  СТРАНИЦЫ ПАМЯТИ - ДСЛШТ


////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
#  64-БИТНАЯ СРЕДА

- Всё больше весит за исключением типа chsr = 1 байту всегда и во всех версиях.
- Переадресация Реестра и Файловой системы - SysWOW64
- Для работы в ней, есть специальные версии всех СИСТЕМНЫХ ВЫЗОВОВ / Функций
- Адресное Пространство Выделяемое под процесс - есть указатель, который ограницен определённым числом
  32 битная машина исаользует указатель = 4  Гигабайта = 2^32 байт
  64 битная машина исаользует указатель = 16 Экзобайт = 2^64 байт = 64 ТЕРАБАЙТА (гига, тера, пета, экзо)
//	гигабайт	Гбайт	109	
//	терабайт	Тбайт	1012
//	петабайт	Пбайт	1015
//	эксабайт	Эбайт	1018

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
# WINDBG - DMP - Дампы - Анализ Дампов

UserMode отладчик   - OlieDBG 
KernelMode отладчик - WinDBG - можно смотреть регистры, отадчивать, переменные, 
								можно отлаживать как Юзер Мод программы, так и Кернел мод программы.


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

В Windows существует 32 уровня приоритета, от 0 до 31. Они группируются так:
- 31 - 16 уровни реального времени; 
- 15 - 1 динамические уровни;
- 0 - системный уровень, зарезервированный для потока обнуления страниц (zero-page thread).

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


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

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











Оценки сложности операций для STL контейнеров

Контейнер	Контейнер	Вставка	Удаление	Произв.Доступ	Поиск	Валидность Итератора
array	массив					
vector / string	Вектор	В Конец:               O(1)
В Начало:             O(n)
В Произв. позиц.: O(n)	Конец:                     O(1)
Произв. позиц.:       O(n)
Сорт.(надо искать): O(n)	O(1)	Несорт.: O(n)

Сорт.:    O(log n)	Нет
deque	Двусторонняя очередь (Дек)	В Конец/Начало:  O(1)
В Произв. позиц.: O(n)	Конец/Начало:        O(1)
Произв. позиц.:       O(n)
Сорт.(надо искать): O(n)	O(1)	Несорт.: O(n)

Сорт.:    O(log n)	Указатели только
list / forward_list	Список	В Конец   O(n) [до него надо дойти]
Начало:   O(1)
По итератору:     O(1)
В Произв.поз.(По индексу):O(n)	Конец/Начало:    O(1)
По итератору:     O(1)
По индексу:         O(n)	НЕТ !!!

только ПО Итертору!	O(n)	Да
set / map	Сэт / Мэп
Ассоциативный массив	O(log n)	O(log n)	Set / Map - Работает по принципу хэш-таблицы и НЕ умеет получать элемент по номеру. (-)	O(log n)	Да
unordered_set / unordered_map	Несортированный мэп / сэт	Амортизированое О(1)
O(1) или O(n)	Амортизированое О(1)
O(1) или O(n)	Амортизированое О(1)
O(1) или O(n)	Аморт. О(1)
O(1) или O(n)	Указатели только
priority_queue	Приоритетная очередь	O(log n)	O(log n)	O(1)	В общем случае O(n), хотя поиск в контейнере не реализован (-)	-

ВСЕГДА O(1), если есть: begin(), end(), empty(), size(), push_back()

vector - вставка в Конец:   O(1)
vector - вставка в Произв: O(n)
vector - удален. Конец:      O(1)
vector - удален. Произв:    O(n)
vector - произв. Доступ:     O(1)
vector - поиск по сорт.:      O(log n)
vector - поиск несорт. :      O(n)
vector - валидность итер.: нет

deque - вставка в Конец:   O(1)
deque - вставка в Произв: O(n)
deque - удален. Конец:      O(1)
deque - удален. Произв:    O(n)
deque - произв. Доступ:     O(1)
deque - поиск по сорт.:      O(log n)
deque - поиск несорт. :      O(n)
deque - валидность итер.: Указатели только

list - вставка:             O(1)
list - удален.:             O(1)
list - произв. Доступ: O(1)
list - поиск:                 O(n)
list - валидность итер.: ДА

set / map - вставка  O(log n)
set / map - удален   O(log n)
set / map - произв. Доступ НЕТ (хэш таблица)
set / map - поиск    O(log n)
set / map - валидность итер.: ДА

unordered_set - вставка  O(1) или O(n)
unordered_set - удален   O(1) или O(n)
unordered_set - произв. Доступ O(1) или O(n)
unordered_set - поиск    O(1) или O(n)
unordered_set - валидность итер.: Указатели только

priority_queue - вставка             O(log n)
priority_queue - удален              O(log n)
priority_queue - произв. Доступ O(1)
priority_queue - поиск                 НЕТ (O(n))
priority_queue - валидность итер.: хз




какими технологиями было бы интересно развиваться
- стандарт новый 11-тый алгоритмы
- ХОЧУ УЧИТЬСЯ И РАЗВИВАТЬСЯ, глубже и глубже копать и познавать язык, алгоритмы, я очень этим делом увлечён )
- 



верси компилятора 11-тый

си++11-тый
Смарт поинтеры какие есть для чего используются какие есть

Суть смарт поинтеров - реализация койепции RAII
-- безопасность с точки зрения утечки памяти


auto_ptr - какие были с ним проблемы ?
мув семантика / семантика перемещения не была реализована в 11-том стандарте

nullptr - 

unique_ptr - 
shared_ptr - 
weak_ptr - 

-----------------------------------------------------------

сьруктуры данных:

какие есть в стл-е
аррей
вектор
лист
дек
мэп
мультмэп
мультисэт

анорднеред мэп
анодеред сэт


реализованы как красно чёрное дерево

Если мы знаем, что 

В каких случаях одно лучше использовать, в каких другое ?

В случае с аноррднеред:
в общем случае мы рассматриваем случаи 

мэп - сэт: одна особенность:

коллекции: словарь 0


Фича что у анорднеред мэпа нет, а у мэпа есть

АНОРДНЕРЕД - Неупорядоченность
изза неупорядоченности проход по эелемнтам возможен ТОЛЬКО через ИТЕРАТОР !!!!!

фамилии - 
сортировать придётся 
АППЕР БАУНД
ЛОВЕР БАУНД 


///////////////////////////////// 17

Эррэй - СТЛьная обёртка обычного нединамического массива

Эррэи	 - НЕДИНАМИЧЕСКИЙ МАССИВ
Векторы	 - ДИНАМИЧЕСКИЙ МАССИВ
		 Вектор смежный кусок памяти, и у него есть .data() - Получение указателя на него
		 Как долго указатель на дату валиден, до тех пор пока мы не добавим ещё один элемент и они будет перекопирован 
Листы	 - 
дек		 - пушбэк попбэк


При любой операции в середине вектора выделение памяти ?
УДАЛЕНИЕ ...

При расширении Капасити только при добавлении в вектор
При удалении элемента вектор не перераспределяется не перекопируется полностью

Вектор 2^n зависит от версии компилятора.


Если капасити не равен сайзу, то

100.0000 элементов капасити 100.0000 
Добавление в конец
и тут
1) выделение 200.000 элеипентов
2) копирование с одного места на другое

Как же быть с операциями за О(1) времени 


ПОНЯТИЕ АМОРТИЗИРОВАННОГО   О ибо когда-то О от 1 и до О от n

анордеред мэп 
мэп в любой момент может расшириться, и ко

В зависимости от задачи можно понять какой сделать
РЕСАЙЗ, РЕСЕТ

///////////////////////////////// 34

СПИСОК
как отличаются операции, 
поиск - О(n)

удаление добавление О(1)
РЕМАРКА !!!
НО чтобы было О(1) НУЖНО чтобы, нам нужно дойти до элемента 500-го который мы хотим удалить ... и в итоге 
ЕСЛИ есть ИТЕРАТОР в нужном месте, тогда O(1)
если мы хотим удалить элемент и делаем это без итератора, то результат будет O(n)

///////////////////////////////// 41

ШАБЛОНЫ: 

Зачем нужны , для чего использовали:

- Чтобы сократить количество кода
- Для использования одного метода работающего с разными объектами / типами

- стандартные решение
-- на этапе предкомпиляции
--- фактореал на шаблонах

Александреского

-- код должен быть читаемый
-- шаблоны сильно усложняют

ИЛИ если вывалится Оштбка на этапе компиляции .....
с БОЛЬшими сложными выводами в лог

///////////////////////////////// 45

ИСКЛЮЧЕНИЯ: 

RAII - ресурсы .... контекнты файлов потоков и 


трай
 
 кетч
 
 бэдаллок
 
 НЬЮНОУФРОУ

/////////////////////////////////

 стд-шные эксепшены ...

 
///////////////////////////////// 45

ШАБЛОНЫ ПРОЕКТИРОВАНИЯ

Синглтон - Мейерса
 в Си++11 есть готовый Синглтон

Клинет - Серверные задачи

Обзёрвер
Листенер

Фассад
Билдер


Фабрика - Для СОЗДАЕНИЯ объектов

///////////////////////////////// 51

МНОГОПОТОЧНОСТЬ 

ПРИМИТИВЫ СИНХРОНИЗАЦИИ И ПРОБЛЕМЫ:

тред
 создал он объект и мы можем 
 
 аттач 
 детач
 

Создали несколько тредов:
Мы хотим сделать из потоков к некско



стд-мьютекс
рекурсивный мьютекс
мьютекс-гуард


стд мьютекс:
лок 

лочим другим тредам доступ к общему ресурсу

анлок

ВНУТРИ СЕКЦИИ ЛОК АНЛОК Только одному потоку будет доступен ресурс
//////////////////////////////

лок/анлок НЕ ЛУЧШАЯ ПРАКТИКА, ибо можно сделать так:

лок 

- ретурн и ВСЁ
- бросился эксепшн

анлок

//////////////////////////////

Объект синхронизации 2

RAII-решение:

ЛОК-гуард

ЮНИК-ЛОК


Объект синхронизации 3

Проблема

функция фу
 в ней захватили тот же мьютекс
есть функция бар
 в ней захватили тот же мьютекс

 В ЭТОМ СЛУЧАЕ БУДЕТ У ОБЫЧНОГО МЬЮТЕКСА ДЕДЛОК
 
бар может вызываться как 


recursive-mutex

///////////////////////////// час +02

Два потока в один под мьютексои чтото долго делаем

и из другой функции мы использовать хоть

timed_mutes
.try_lock()






















































//[Q]///////////////////////////////////////////////////////////////////////////////
/*
Вы разрабатываете графический редактор для рисования простых геометрических фигур.
Пользователь через UI может добавлять фигуры на холст (UI предоставляет точку на палитре и тип фигуры )
Допишите реализацию класса Canvas (Внешняя бибилиотека предоставляет Вам объект Graphics)
Реализацию отрисовки примитивов (квадрат, треуг, прямоуг) писат не надо
*/

#if question

class Graphics
{
public:
    void DrawLine (int x, int y, int x2, int y2);
};

enum FigureType
{
    Square,
    Triangle,
    Rectangle
};

class Canvas
{
	private int _x;
	private int _y;
	FigureType _ft;

public:
    void AddFigure(int x, int y, FigureType ft);
    void DoPaint(Graphics& gr);
}


void Canvas::DoPaint(Graphics& gr) {

	switch (ft)
	{
	case Square: 
		//
		break;
	}
}

void Canvas::AddFigure(int x, int y, FigureType ft) {
	this->_x = x;
	this->_y = y;
	this->_ft = ft;
}

void main()
{
	Canvas* c = new Canvas();
	c->AddFigure(2, 4, FigureType::Triangle);
	c->DoPaint(new Graphics());

}

#endif

//[Q]///////////////////////////////////////////////////////////////////////////////
// Можно ли обойтись без виртаульного деструтора используя вот такой способ ?
// Можно ли воспользоваться конструкцией ниже или нет и почему ?

#if question
#include <stdio.h>

class A
{
public:
    A()  { printf("A"); }
    ~A()
    {
        this->deinit(); // вызовет деструктор В
        printf("~A");
    }
    virtual void deinit()
	{
		printf("delete this A");
		delete this;
	}
};

class B : public A
{
public:
    B()  { printf("B"); }
    ~B() { printf("~B"); }
    virtual void deinit()
	{
		printf("delete this B");
		delete this;
	}
};

void main()
{
    A* pA = new B;
    //pA->deinit(); // вызовет деструктор В
    delete pA;	  // вызовет деструтор А
}

#endif

//[Q]///////////////////////////////////////////////////////////////////////////////
// [Q] Перечислите все проблемы, которые вы видите в данном коде :

// Хотелось бы разрисовать как память выделяется под все объекты, почему происходит утечка памяти,
// и нарисовать всё визуально, чтобы понимать всё, что происходит в коде максимально наглядно

#if question 

class Foo
{
public:
    Foo(int j) { i = new int[j]; }
    ~Foo() { delete i; }
private:
    int* i;
};

class Bar : Foo
{
public:
    Bar(int j) { i = new char[j]; }
    ~Bar() { delete i; }
private:
    char* i;
};

void main()
{
    Foo* f = new Foo(100);
    Foo* b = new Bar(200);

	*f = *b;

    delete f;
    delete b;
}

#endif

///////// пример ответа
//	У Foo нет конструктора по умолчанию.А в конструкторе Bar базовый класс Foo никак не инициализируется существующим конструктором Foo::Foo(int j)
// В строчке Foo* b = new Bar(200) будет ошибка из - за того, что наследование по умолчанию "private".Нужно поставить ключевое слово public перед Foo в строчке class Bar : Foo.
//	Массивы нужно удалять оператором delete[].
//	Деструктор в Foo нужно сделать виртуальным, иначе в данном случае не вызывается Bar::~Bar()
// char* i; поле i определено в классе Foo.С точки зрения компилятора всё правильно, т.к. char* i и int* i находятся в разных пространствах имен.Но это может запутать программиста
// В конструкторах, желательно, сделать отдельную инициализацию, если j не положительное или нулевое.
// Строка *f = *b; -утечка памяти.


//[Q]///////////////////////////////////////////////////////////////////////////////
// Правильно ли я понимаю, что происходит в коде ?

#if question

struct Point {
    Point(int x, int y)
    : X(x)
    , Y(y)
    {}

    bool operator<(const Point& p) const {
        return ((X < p.X) && (Y < p.Y));
    }

	// https://www.linux.org.ru/forum/development/13246470
	//..операторы «больше» и «равно» выводятся из одного оператора «меньше»
	// Чтобы поддерживать SORT, FIND и т.д. НЕ нужен оператор equality (a == b)
	// А НУЖЕН  equivalence  это когда первое значение не меньше второго, ни второе значение не меньше первого => (!(a < b) && !(b < a))
	
	// оператор БОЛЬШЕ > выражается через меньше => возвращает тру, когда не меньше и не равно => ()
	// оператор РАВНО ==  =>  
	//операторы «больше» и «равно» выводятся из одного оператора «меньше»
	//по теме : определи оператор «меньше», либо определи функтор «меньше» и передай в качестве параметра шаблона.


private:
    int X, Y;
};

int main()
{
    std::map<Point, int> x;
    Point p1(0, 1);
    Point p2(1, 0);
    x[p1] = 1;
    x[p2] = 2;

	if (p1<p2)  std::cout << "p1 < p2";
	//if (p1>p2)  std::cout << "p1 > p2";
	//if (p1==p2) std::cout << "p1 = p2";

    std::cout << x[p1] << x[p2];
    return 0;
}

#endif

//[Q]///////////////////////////////////////////////////////////////////////////////
// Будет ли или при каких условиях возможно "падение" в данном участке кода ?
// Как будут переданы параметры в функцию f (согласно конвенциям вызовов ф-ции)
// Что будет, если мы метод  f  сделаем виртуальным ?

#if done

#include <stdio.h>

class A
{
	public:
    void f() { printf("A"); }
};

int main()
{
    A* a = 0;
    a->f(); // по умолчанию в классе все члены PRIVATE !!!

    return 0;
}

#endif

//[Q]///////////////////////////////////////////////////////////////////////////////
// [Q] В чём проблема ? Как произойдёт утечка памяти ? Будет ли создан экзепляр класса А ?
//Что будет после блока try, вызовется ли деструктор для объекта класса A ? а для объекта класса В ? 
//Как поправить такой код ? Как можно воспользоваться тут умными указателями ?

#if question

class A;

class B {};

class C
{
public:
	C() //{ throw 1; } // (*)
	{
		throw new B;
	}
};

class A
{
public:
	A() : m_b(new B), m_c(new C)
    {}


	//[1]
	~A()
	{
		delete m_b;
		delete m_c;
	}
	//[2] // Констурктор копирования

	B* m_b;
    C* m_c;

	//std::auto_ptr<B> m_b;
	//std::auto_ptr<C> m_c;
};


int main()
{
    try
    {
        A a;
    }
	// catch (int) // или catch(...) // (*) чтобы была возможность поймать исключение того типа, что бросает throw
    //catch (A a)
	catch (B b)
	{
        printf("catch (A a)");
    }

    return 0;
}

#endif

//[Q]///////////////////////////////////////////////////////////////////////////////
// [COMMENT] Почитать про РАСКРУТКУ СТЕКА
// Как происходит раскрутка стека


//[Q]///////////////////////////////////////////////////////////////////////////////
// ПРОБЛЕМА РОМБОВИДНОГО НАСЛЕДОВАНИЯ

// ЧТО БУДЕТ ЕСЛИ УБРАТЬ ВТОРОЙ VIRTUAL ?
// Рассмотрим следующий пример :

#if 0
#include <stdio.h>

class Parent
{
public:
	Parent()
	{
		printf("Parent\n");
	}

	void fun()
	{
		printf("Paren methodt\n");
	}

};
class Child1 : virtual public Parent
//class Child1 : public Parent
{
public:
	Child1()
	{
		printf("Child1\n");
	}

};
class Child2 : virtual public Parent
{
public:
	Child2()
	{
		printf("Child2\n");
	}

};
class GrandChild : public Child1, public Child2
{
public:
	GrandChild()
	{
		printf("GrandChild\n");
	}
};


// Использование ключевого слова virtual в классах Child1, Child2 приводит к тому что они наследуют 
// единый общий подобъект базового класса Parent, а не каждый свою!Таким образом решается 
// неоднозначность для компилятора по отношению к GrandChild

int main()
{
	GrandChild gr;
	gr.fun();

	return 0;
}

#endif


//[Q]///////////////////////////////////////////////////////////////////////////////
// КАКИЕ ПРОБЛЕМЫ ВЫ ВИДЕТЕ В ЭТОМ КОДЕ
#if question

#include <iostream> 

class A {
public:
	A(int a) {}
	int max() { return 1; }
};
class B {
public:
	B(int b) {}
	int max() { return 2; }
};

class foo
{
    A* a;
    B* b;
public:
    foo(int x, int y) :a(0), b(0){
        a = new A(x);
        b = new B(y);
    }

    int multiply(){
        return a->max() * b->max();
    }

    ~foo(){
        delete a;
		delete b;
    }
};

void main()
{
	foo f(2, 3);
	int m = f.multiply();
	std::cout << m << std::endl;
}
#endif

//[Q]///////////////////////////////////////////////////////////////////////////////
// Для чего используется паттерн Синглтон ?
// [Q] Как объявить Класс-Singleton ?


//[Q]///////////////////////////////////////////////////////////////////////////////
// Зачем вообще нужен формат DLL, почему не хранить функции в любом другой бинарном файле, в чём суть DLL-фвйла ?

//[Q]///////////////////////////////////////////////////////////////////////////////
// На уровне ассемблерного кода, и вызовов как работают DLL-ки ? Как работеют выховы функций ?
// Как работает стек ? Как работает куча ?
// Как работают регистры с различных конвенций вызова функций?
// и функция printf (примеры с этой функцией, когда она печатает то, что остаётся на стеке) ?




#if question
// [Q]	Как надо переопределить оператор присваивания, чтобы он работал правильно
//		Скрытая задача на ПРАВИЛО ТРЁХ 
// https://stackoverflow.com/questions/39383936/correctly-overload-assignment-operator-for-classes-with-pointer-members

#include <iostream>

class Object 
{
public:
	char mas[32];
	char* arr;


	Object() {}
	Object(int _n)
	{
		size = _n;
		arr = new char[_n];
	}

	~Object()
	{
		if(arr)
		delete arr;
	}

	// оператор присваивания
	Object& operator=(const Object& _obj)
	{
		// ТО КАК БЫЛО ИЗНАЧАЛЬНО
		// memcpy(this, _obj, sizeof(_obj));

		// ОШИБКИ:
		this->mas = _obj.mas; // 1 // ОШИБКА must be a modified lvalue
		if (_obj.arr)
		{ this->arr = _obj.arr;} // 2 //  ОШИБКА - Два объекта будут указывать на одну и ту же память
									  //  когда вызовется  delete(), то оба указателя станут НЕВАЛИДНЫМИ
		// 1 // РЕШЕНИЕ:
		std::memcpy(this->mas, _obj.mas, sizeof(_obj.mas));

		// 2 // РЕШЕНИЕ:
		if (this == &_obj)
			return *this; //равенство самому себе // self assignment
		if (arr != NULL)
			delete[] arr; //очищаем ранее использованную память //clean up already allocated memory

		size = _obj.size;
		arr = new char[size];
		std::memcpy(arr, _obj.arr, size);
		return *this;
	}

	//Конструктор копирования
	Object(const Object& _obj)
	{
		size = _obj.size;
		arr = new char[size];
		std::memcpy(arr, _obj.arr, size);
	}


private:
	int size; //array elements int *arr; //arr - dynamic array pointer
};

#endif

//[Q]///////////////////////////////////////////////////////////////////////////////


//[PAGE]///////////////////////////////////////////////////////////////////////////////

объект std::tread [фактически есть ссылка] -> [на привязанный к нему Thread объект из ОС]
						 OS Thread-object
						 --------------------
std::thread ---linkk---> | mov eax, ecx		| <- void func()
						 | pop eax			|	 {
						 |					|	 }
						 --------------------

0. native_handle = HANDLE inside the Operation System
1. joinable()
2. join() -> wait
3. detach

						 OS Thread-object
						 --------------------
std::thread -X-linkk-X-> | ...       		| 
						 | mov eax, ecx		|
						 | ...				|
						 --------------------

4. joinable - говорит о возможности ожидания на потоке
			  ( возможность выполнить на нём join() )
std::thread t1 = t2: -> std::thread O --> связь с потоком ОС

//[PAGE]///////////////////////////////////////////////////////////////////////////////

VECTOR

O(1) - Вставка в конец (за исключением тех случаев, когда расширяется capacity)
O(N) - Вставка в любое другое место, ибо вектор пересобирается заново


| 1 | 4 | 6 | 10 | | | | |
[....size = 4....]		   = текущий размер заполненнного вектора
[......capacity = 8......] = 2^n

DEQUE

 array
------- <- -------  <- ------- 
|     |	   |     | 	   |     |
-------	   ------- 	   -------
|     |	   |     | 	   |     |  -> end()
-------	   ------- 	   -------
|     |	   |     | 	   |     |
------- -> -------  -> ------- 

LIST

Поиск O(N) - ИБО нам нужно по ссылкам пробежаться по всем элементам чтобы найти нужный
Вставка / Удаление О(1) - нужно сделать ссылкам переуказание. удаляемый более не указывает ниуда, а тот что после него указывает теперь на тот что был перед удаляемым.

-------     -------     ------- 
|     | <-> |     | <-> |     | <-> endl()
-------	    ------- 	-------

MAP = SET

Вставка / Удаление / Поиск O(log_2(N)), где N - размер дерева, т.е. количество элементов дерева
Основание логарифма = 2 - число Листьеа (детей) у одного Ветки / УЗЛА (родителя)
MAP - Красно-чёрное дерево

      O
    /  \
   O    O
  / \  / \
 0   0 0  0

SET - это MAP без VALUE
MAP [key, value]
SET [keys]

std::pair<first, second> pr; после определения можно обращаться к парным элементам вот так: pr.first, pr.second

UNORDERED SET / MAP - Хеш Таблицы

Вставка / Удаление / Поиск O(1)

Внутри Элементов хэш таблицы расположены Бакеты, которые как правило являются расширяющимися списками типа LIST

hash
-------  
|     |	   bucket = list
-------	   --- 	  ---    ---
|     | -> | | -> | | -> | | -> end()
-------	   ---    ---    ---
|     |	 
------- 

//[PAGE]///////////////////////////////////////////////////////////////////////////////

atomic


//[PAGE]///////////////////////////////////////////////////////////////////////////////

100
110
1FD bool foo()
1FE {
1FF   int i - 0;
...
	  return smth;
2F1 }

0x1FE : foo - адрес функции - "foo" = 0x1FE
foo(); -вызов функции по адресу


std::mutex.lock();
counter++;
std::mutex.unlock();

counter++:
	      ------------------
		  |  asm
		  |  push eax
	     /  mov eax, ecx
atomic <-	   inc eax
	     \  mov ecx, eax
		  |  pop eax
		  | mov 0x4F1FE, ecx
	      ------------------

		push eax
		mov eax, ecx
		INTERUPT

mov 0x4F1E, eax
mov eax, 0x4F1E
- inc eax (=5)
- eax = 2
mov 0x4F1E, eax
 counter = 5
 counter = 8
 counter = 2


//[PAGE]///////////////////////////////////////////////////////////////////////////////

int foo(int x, int y)

cnak --
shap -- foo(int x, int y)


sqrt((float)8.8)

//[PAGE]///////////////////////////////////////////////////////////////////////////////

// СЛОЖНОСТИ

* Если требуется пробежаться по одному и тому же массиву дважды 
  (к примеру с начала до конца, с конца до начала),
  то сложность будет О(2*N) = О(N) ибо константы опускаются

* О(log_2(N)) - бинарный поиск

* std::vector<bool> - необычный вектор


//[PAGE]///////////////////////////////////////////////////////////////////////////////

!!!___VECTOR___!!!

std::vector<int> vec;
vec.push_back(30);
vec.push_back(23);
-----------
| 30 | 23 | size = capacity = 2
-----------

vec.push_back(48);

---------------------
| 30 | 23 | 48 |    | 
---------------------  
size = 3; capacity = 4
capacity рассчитывается по формуле: new_capacity = current_capacity * 2

vec.push_back(54);

---------------------
| 30 | 23 | 48 | 54 | size = 4; capacity = 4
---------------------  

vec.push_back(7);

-------------------------------------
| 30 | 23 | 48 | 54 | 7 |   |   |   | size = 5; capacity = 8
-------------------------------------

vec.push_back(9);
vec.push_back(12);

--------------------------------------
| 30 | 23 | 48 | 54 | 7 | 9 | 12 |   |
--------------------------------------

!!!___ERASE___!!!

vec.erase(2) // erase element with index [2]

 [0] [1] [2] [3]  [4]  [5] [6] [7] [8]
---------------------------------------
| 1 | 4 | 7 | 10 | 11 | 2 |   |   |   |  size = 6
---------------------------------------

после выполнения erase:
---------------------------------------- -
| 1 | 4 | 10 | 11 | 2 |//2//|///|///|///|  size = 5 
---------------------------------------- -
всё что после двойки стало невалидным


!!!___RESIZE___!!!

vec.resize(2)
------------------
| 1 | 4 | | | size = 2  capacity = 4
------------------

!!!___RESERVE___!!!

vec.reserve(8)
-------------------------------- -
| 1 | 4 | | | | | | | size = 2  capacity = 8
-------------------------------- -


(!) В случае, если надо приравнять вектор к вектору.
НУЖНО использовать метод перемещения.SWAP() !!!
Но у нас вектор имеет 10.000 значений.

vec_1 = vec_2
vec_1.size() = 10.000
vec_2.size() = 10.000
vec_1.swap(vec_2)
Для более быстрого и более эффективного перемещения содержимого

(!) std::vector<bool> -необычный вектор

136 бит для 17 bool
24 бита  vector<char>

!!!___BINARY SEARCH___!!!

Binary search works only with SORTed Arrays
------------------------------------------------------------ -
| 10 | 20 | 30 | 41 | 44 | 56 | 100 | 101 | 109 | 140 | 250 | length = 11
------------------------------------------------------------ -

0) searching for the number  n = 30
1) length / 2 = [5] = 56 : n > 56; n==56
2) (10 ; 56] : [2] = 30

//[PAGE]///////////////////////////////////////////////////////////////////////////////

foo()
calc(3, 5, plus);
...
{
  calc(...)
  {
    ...
    plus(...)
    {
    }
  }
}

plus(...)
{
	throw(excp);
}

     asm:
   --call function;
   |
   --> код

     стек:
   адрес
   unhandled() -> terminate()

///////////////////////////////////////  ??? !!!!!

  cхема в памяти: 
|                |
|   переменные   |
|    локальные   |
------------------
| адрес возврата |
------------------

  jmp  function() ->   
                   -> function() { return; }
--call function() ->
|
--> push ecp, ecx; 

//[PAGE]///////////////////////////////////////////////////////////////////////////////

bool fun(); // пртотип функции

fun; // адрес функции
fun(); // вызов функции


адрес_функции(); // вызов функции



//[PAGE]///////////////////////////////////////////////////////////////////////////////

(!)  обнулить массив простых типоа (к примеру int, char) можно не через вызов ZeroMemory, и т.п., а через 
	 char buffer[256] = { 0 };

(!)  Для массива объектов С++ вызывается конструктор по умолчанию, если не задан явный вызов конструктора
	 Если явный вызов конструктора задан, ТО для классов наследников !!! ???

(!)  Функтор в С++ это объект у которого перегружен operator()
	 т.е. внешне эксземпляр класса может быть похож на функцию и использоваться как функция

(!)  Функтор это функция с состоянием

(!)  const-антный метод класса не имеет права изменять состояние экземпляра класса
	 (элементов, членов класса) ЗА ИСКЛЮЧНИЕМ те, которые помечены ключевым словом
	 mutable

(!)  static-методы класса имеют доступ только к статическим полям класса, т.к.
	 static-методы не имеют прямой связи с конкретным экземпляром класса

(!)  преобразование:
func(char* ptr) : // read / write
	...
	char buf[256]; const char* const ptr;
	const char* ptr2 = "MyName"; // READ ONLY !

	func(buf);
	func(ptr2); // ERROR

//[PAGE]///////////////////////////////////////////////////////////////////////////////
TEMPLATES

template <внутренний_тип>

(!) Каждый шаблон (template) накладывает некоторые
    ограниченя или обязательства на используемый внутренний тип

template <class T>
class MyTemplate
{
	public:
	int calc(T _k)
	{
		T k1 = _k + 1;
		_k1.divide();
		return _k;
	}
};

В вышеописанном примере на тип накладываются обязательства:
- Должен быть определён operator(int)
- Должен быть реализован метод .divide()
- Должен быть определён operator int()

(!!!) Описание и реализация шаблона должна
      содержаться в заголовочном файле *.H (Header)

//[PAGE]///////////////////////////////////////////////////////////////////////////////
EXEPTIONS = ИСКЛЮЧЕНИЯ В С++

1. Генерируются ключевым словом throw
2. Перехватываются в catch()

class BaseExeption
{};

class DerivedExeption : public BaseExeption
{};

class SubDerivedExeption : public DerivedExeption
{};


throw DerivedExeption()
...

catch (BaseExeption)
{
	<- обработчик зайдёт сюда
}
catch (DerivedExeption)
{
	// А СЮДА НЕ ЗАЙДЁТ
	// ХОТЬ МЫ И БРОСАЛИ 
	// ИМЕННО throw DerivedExeption()
}

    -----------------
/\  |               |
 |  |     Base      |
 |  |               |
 |  |     ----------|
 |  |     |         |
 |  |     | Derived |
 |  |     |         |
    -----------------

//[PAGE]///////////////////////////////////////////////////////////////////////////////
LVALUE AND RVALUE [1]

LValue = RValue
Left = Right;

Left  - то, что можем изменять
Right - то, что не можем менять

 ----------------	| 			|
 | "Any" | 1234 |	| <-		|
 ----------------	| без		|
 T Dan = Any;		| <-		|	T Dan = std::move(Any);
					| семантики	|
---------			| <-		|	----------------	---------
| "Dan" |			| move		|	| "Dan" | 1234 |	| "Any" |
---------			| <-		|	----------------	---------
					|			|
----------------	|			|
| "Dan" | 1234 |	|			|
----------------	|			|

{
  Foo foo;
  ...
  return foo;
}

[unordnered obj] = foo;
	*move*

//[PAGE]///////////////////////////////////////////////////////////////////////////////
LVALUE AND RVALUE [2]

lvalue = rvalue

  Семантика перемещения (MOVE)

* Foo( Foo && _foo) { } <- Конструктор перемещения

* Foo& operator=( Foo && _foo) { } <- Оператор перемещения

    Суть перемещения состоит в том, 
    чтобы забрать у одного объекта данные
    и присвоить из себе (ЗАВЛАДЕТЬ).
(!) НЕ ОСТАВИВ этих данных Прежнему Владельцу

	Это помогает оптимизировать работу
	с временными объектами, RVALUES

 std::move - спецификатор для явного
			 использования семантики move

//[PAGE]///////////////////////////////////////////////////////////////////////////////
КОНСТРУКТОР КОПИЙ

 (!) Конутркутор копии вызывается в
	 ТРЁХ случаях:

	1)	Инициализация класса :
		MyClass mc = mcz;

	2)	Во время ВОЗВРАТА значения из функции :
		MyClass doSmth(...);
		...
		mc = doSmth();

	3) При передаче в качестве АРГУМЕНТА в функцию :
		void doSmth(MyClass _my);
		...
		doSomething(mc);

	Сигнатура конструктора копий:

	class Foo {
		public:
			Foo(const Foo& _foo);
	};


	return foo();
	[ ] = foo;

//[PAGE]///////////////////////////////////////////////////////////////////////////////
ВИРТУАЛЬНОСТЬ 

- Функции (методы)
- Деструктор

(!) Конутркутор НЕ МОЖЕТ БЫТЬ виртуальным

В C++11 появилось ключевое слово override

OVERRIDE -	говорит о том, что мы перекрываем какой-то 
			из виртуальных методов в базовом классе

	class ... {
	virtual void reproduce() = 0;
};

(!) ЧИСТАЯ Виртуальная функция (метод) - метод, не имеющий реализации в телле класса,
										 а имеющий только Сигнатуру.
	
(!) Абстрактный класс - класс имеющий хотя бы одну чисто виртуальную функцию,
						без её реализации в потомке

(!) Экземпляры Абстрактного класса создавать НЕЛЬЗЯ !

(!!!) Для чистой виртуальной функции можно предоставлять базовую реализацию,
	  обращаться к которой может класс наследник Base_class::pure_virtual_func();

  Base()
   |
  \ /
 Derived()
------------
~Derived
   |
  \ /
 ~Base

in memory:
    --------------
  0 | Base class |
 10 | ...        |
  n | Derived    |
    --------------

При создании объекта конструкторы вызываются
в порядке Сверху-Вниз, т.е. от Базового к Наследнику.
А Декструкторы вызываются в обратном порядке, от наследника к Базовому.

(!) ВИРТУАЛЬНЫЙ ДЕСТРУКТОР - если он не указан вызываются лишь те дееструкторы,
    которые можно определить из иерархии наследования из типа указателя, к которому
	применяется оператор delete

class Base {};
class Between : public Base() {};
class Derived : public Between() {};

Between* betwPtr = new Derived();
delete betwPtr; 
= >
~Between
~Base

//[PAGE]///////////////////////////////////////////////////////////////////////////////
НАСЛЕДОВАНИЕ	PUBLIC, PRIVATE, PROTECTED

1) public:	  public	-> public
			  protected -> protected
			  private	-> private

2) protected: public	-> protected
			  protected -> protected
			  private	-> private

3) private:	  так же как и в protected

(!) В конструкторах и деструкторах не рекомендуется вызывать виртуальные функции.
	
/////////////////////////////////////////////////////////////////////////////////
ВИРТУАЛЬНОЕ НАСЛЕДОВАНИЕ

[Q] Что такое ВИРТУАЛЬНЫЙ БАЗОВЫЙ КЛАСС ?
[A] Это такой класс, который ??? !!!


[Q] Проблема Ромбовидного наследования:

class A_
{ int fa() { return 1; } };

class B: public A_  
{ int fb() { return 2; } };

class C: public A_  
{ int fc() { return 3; } };

class D : public B, C
{ int fd() { return 4; } };

void main()
{
	D _d;
	_d.fa(); // непонятно какое fa из B  или из  C надо вызвать
}

/////////////////////////////////
[A] Решением будет использовать виртуальное наследование

class A_
{ int fa() { return 1; } };

class B: virtual public A_  
{ int fb() { return 2; } };

class C: virtual public A_  
{ int fc() { return 3; } };

class D : public B, C
{ int fd() { return 4; } };

void main()
{
	D _d;
	_d.fa(); // непонятно какое fa из B  или из  C надо вызвать
}

/////////////////////////////////////////////////////////////////////////////////

 HEвиртуальные
----------------
A A A A A
| | | | |
B C D-F-G
  |/
  W   - W-instance

	 A <------
    / \      |
	C  D --> F -> G -> A
   ^   ^
    \ /
	 W
	   
/////////////////////////////////////////////////////////////////////////////////
DYNAMIC CAST

использует парадигму RTTI
auto  val  = dynamic_cast<T*> ptr; // null_ptr
auto& val1 = dynamic_cast<T>  refference; // throw bad_cast();

Динамическое преобразование типа,
работает только с объектами, которые имеют
таблицу виртуальных функций

/////////////////////////////////////////////////////////////////////////////////
Из чего складывается размер объекта =
1) сумма размеров всех полейкласса
2) размер указателя на табл.вирт.функций
3) выравнивание всего объекта до размера кратного 4 - ём байтам
4) указатель на классы потомки






















//[PAGE]///////////////////////////////////////////////////////////////////////////////
m_sh1; m_sh2;
local: std::shared a1 = new ...
local: shared_ptr  a2 = new ...

m_sh1 = a1;
m_sh2 = a2;

shared_ptr a1(new A());
shared_ptr a2(new A());

class Foo {
	shared_ptr m_a1;
	shared_ptr m_a2;
public:
	foo()
	{
		shared_ptr a1(new A());
		shared_ptr a2(new A()); <- EXCEPTION !!!

		m_a1 = a1;
		m_a2 = a2;
	}
};


try
{
	int i = doSmth(foo(), 5);
	k = i + i + 1;
}
catch (...)
{
}




































































// АЛГОРИТМЫ СОРТИРОВОК

// 1. Сортировка выбором
// Идея метода состоит в том, чтобы создавать отсортированную последовательность путем присоединения к ней одного элемента за другим в правильном порядке. Если входная последовательность почти упорядочена, то сравнений будет столько же, значит алгоритм ведет себя неестественно.

/*
template< class T >
void selectSort(T* arr, int size) 
{
    T tmp;
    for(int i = 0; i < size; ++i) // i - номер текущего шага
    { 
        int pos = i; 
        tmp = arr[i];
        for(int j = i + 1; j < size; ++j) // цикл выбора наименьшего элемента
        {
            if (arr[j] < tmp) 
           {
               pos = j; 
               tmp = arr[j]; 
           }
        }
        arr[pos] = arr[i]; 
        arr[i] = tmp; // меняем местами наименьший с a[i]
    }
}
*/

// 2. Сортировка пузырьком (обменом)
// Идея метода: шаг сортировки состоит в проходе снизу вверх по массиву. По пути просматриваются пары соседних элементов. Если элементы некоторой пары находятся в неправильном порядке, то меняем их местами.


//*
template< class T >
void bubbleSort(T* arr, int size)
{
    T tmp;
 
    for(int i = 0; i < size - 1; ++i) // i - номер прохода
    {            
        for(int j = 0; j < size - 1; ++j) // внутренний цикл прохода
        {     
            if (arr[j + 1] < arr[j]) 
            {
                tmp = arr[j + 1]; 
                arr[j + 1] = arr[j]; 
                arr[j] = tmp;
            }
        }
    }
}
//*/








/*
template< class T >
void bubbleSort(T* arr, int size)
{
    T tmp;
 
    for(int i = 0; i < size - 1; ++i) // i - номер прохода
    {            
        for(int j = 0; j < size - 1; ++j) // внутренний цикл прохода
        {     
            if (arr[j + 1] < arr[j]) 
            {
                tmp = arr[j + 1]; 
                arr[j + 1] = arr[j]; 
                arr[j] = tmp;
            }
        }
    }
}
//*/
//*
template <class T>
void bubble_sort(T* a, int size)
{
	T tmp;
	for (int i = 0; i < size - 1; ++i)
	{
		for (int j = 0; j < size - 1; ++j)
		{
			if(a[j+1] < a[j])
			{
				tmp = a[j];
				a[j] = a[j + 1];
				a[j - 1] = tmp;
			}
		}
	}
}

// modified bubble_sort
void bubble_sort_mod_1(int* a, int len)
{
	int tmp = 0;
	bool sorted = true;
	while(!sorted)
	{
		sorted = true;
		for(int i=0; i < n-1; i++)
		{
			if(a[i] > a[i+1])
			{
				tmp    = a[i];
				a[i]   = a[i+1];
				a[i+1] = tmp;
				sorted = false;
			}
		}
	}
}







// modified bubble_sort
void bubble_sort_mod_2(int* a, int len)
{
	int j = 1;
	int tmp = 0;
	bool sorted = true;
	while(!sorted)
	{
		sorted = true;
		for(int i=0; i < n-j; i++)
		{
			if(a[i] > a[i+1])
			{
				tmp    = a[i];
				a[i]   = a[i+1];
				a[i+1] = tmp;
				sorted = false;
			}
		}
		j++;
	}
}*/
// Дополнительная память, очевидно, не требуется. Поведение усовершенствованного (но не начального) метода довольно естественное, почти отсортированный массив будет отсортирован намного быстрее случайного. Сортировка пузырьком устойчива, однако шейкер-сортировка утрачивает это качество.
// На практике метод пузырька, даже с улучшениями, работает слишком медленно.А потому - почти не применяется.

// 3. Сортировка вставками
//Сортировка простыми вставками в чем-то похожа на вышеизложенные методы.

template< class T >
void insertSort(T* a, int size)
{
	T tmp;
	for (int i = 1, j; i < size; ++i) // цикл проходов, i - номер прохода
	{
		tmp = a[i];
		for (j = i - 1; j >= 0 && a[j] > tmp; --j) // поиск места элемента в готовой последовательности 
			a[j + 1] = a[j];    // сдвигаем элемент направо, пока не дошли
		a[j + 1] = tmp; // место найдено, вставить элемент    
	}
}

// Аналогично сортировке выбором, среднее, а также худшее число сравнений и пересылок оцениваются как O(n^2), дополнительная память при этом не используется.
// Хорошим показателем сортировки является весьма естественное поведение : почти отсортированный массив будет досортирован очень быстро.Это, вкупе с устойчивостью алгоритма, делает метод хорошим выбором в соответствующих ситуациях.
// Алгоритм можно слегка улучшить.Заметим, что на каждом шаге внутреннего цикла проверяются 2 условия.Можно объединить из в одно, поставив в начало массива специальный сторожевой элемент.Он должен быть заведомо меньше всех остальных элементов массива.


Timsort

СОСТОИТ ИЗ 3-ёх шагов:
1) Специальный алгоритм разделяет входной массив на подмассивы
2) Каждый подмассив сортируется обычной сортировкой вставками
3) Отсортированные подмассивы собираются в единый массив с помощью модифицированной сортировки слиянием



// 4. Сортировка Шелла
// Сортировка Шелла является довольно интересной модификацией алгоритма сортировки простыми вставками.

int increment(long inc[], long size)
{
	int p1, p2, p3, s;
	p1 = p2 = p3 = 1;
	s = -1;
	do
	{
		if (++s % 2)
		{
			inc[s] = 8 * p1 - 6 * p2 + 1;
		}
		else
		{
			inc[s] = 9 * p1 - 9 * p3 + 1;
			p2 *= 2;
			p3 *= 2;
		}
		p1 *= 2;
	} while (3 * inc[s] < size);

	return s > 0 ? --s : 0;
}


template< class T >
void shellSort(T a[], long size)
{
	long inc, i, j, seq[40];
	int s;

	s = increment(seq, size); // вычисление последовательности приращений
	while (s >= 0)  // сортировка вставками с инкрементами inc[] 
	{
		inc = seq[s--];
		for (i = inc; i < size; ++i)
		{
			T temp = a[i];
			for (j = i; (j >= inc) && (temp < a[j - inc]); j -= inc) {
				a[j] = a[j - inc];
			}
			a[j] = temp;
		}
	}
}

// Часто вместо вычисления последовательности во время каждого запуска процедуры, ее значения рассчитывают заранее и записывают в таблицу, которой пользуются, выбирая начальное приращение по тому же правилу: начинаем с inc[s-1], если 3*inc[s] > size.













// 5. Пирамидальная сортировка
// Пирамидальная сортировка является первым из рассматриваемых методов, быстродействие которых оценивается как O(n log n).

template< class T >
void downHeap(T a[], long k, long n)
{
	//  процедура просеивания следующего элемента 
	//  До процедуры: a[k+1]...a[n]  - пирамида 
	//  После:  a[k]...a[n]  - пирамида 
	T new_elem;
	long child;
	new_elem = a[k];

	while (k <= n / 2) // пока у a[k] есть дети 
	{
		child = 2 * k;

		if (child < n && a[child] < a[child + 1]) //  выбираем большего сына 
			child++;
		if (new_elem >= a[child])
			break;
		// иначе 
		a[k] = a[child];    // переносим сына наверх 
		k = child;
	}
	a[k] = new_elem;
}

template< class T >
void heapSort(T a[], long size)
{
	long i;
	T temp;

	// строим пирамиду 
	for (i = size / 2 - 1; i >= 0; --i)
		downHeap(a, i, size - 1);

	// теперь a[0]...a[size-1] пирамида 

	for (i = size - 1; i > 0; --i)
	{
		// меняем первый с последним 
		temp = a[i];
		a[i] = a[0];
		a[0] = temp;
		// восстанавливаем пирамидальность a[0]...a[i-1] 
		downHeap(a, 0, i - 1);
	}
}

// Построение пирамиды занимает O(n log n) операций, причем более точная оценка дает даже O(n) за счет того, что реальное время выполнения downheap зависит от высоты уже созданной части пирамиды.
// Вторая фаза занимает O(n log n) времени: O(n) раз берется максимум и происходит просеивание бывшего последнего элемента.Плюсом является стабильность метода : среднее число пересылок(n log n) / 2, и отклонения от этого значения сравнительно малы.
// Метод не является устойчивым : по ходу работы массив так "перетряхивается", что исходный порядок элементов может измениться случайным образом.







// 6. Быстрая сортировка (сортировка Хоара)
// "Быстрая сортировка", хоть и была разработана более 40 лет назад, является наиболее широко применяемым и одним их самых эффективных алгоритмов.

/*quickSort ( массив a, верхняя граница N ) {
    Выбрать опорный элемент p - середину массива
    Разделить массив по этому элементу
    Если подмассив слева от p содержит более одного элемента,
    вызвать quickSort для него.
    Если подмассив справа от p содержит более одного элемента,
    вызвать quickSort для него.
}
*/



template<class T>
void quickSortR(T* a, long N) {
	// На входе - массив a[], a[N] - его последний элемент.

	long i = 0, j = N;      // поставить указатели на исходные места
	T temp, p;

	p = a[N >> 1];      // центральный элемент

						// процедура разделения
	do {
		while (a[i] < p) i++;
		while (a[j] > p) j--;

		if (i <= j) {
			temp = a[i]; a[i] = a[j]; a[j] = temp;
			i++; j--;
		}
	} while (i <= j);

	// рекурсивные вызовы, если есть, что сортировать 
	if (j > 0) quickSortR(a, j);
	if (N > i) quickSortR(a + i, N - i);
}

// Каждое разделение требует, очевидно, O(n) операций. Количество шагов деления(глубина рекурсии) составляет приблизительно log n, если массив делится на более-менее равные части. Таким образом, общее быстродействие: O(n log n), что и имеет место на практике.

// Итеративный алгоритм быстрой сортировки.
/*
Итеративная QuickSort (массив a, размер size) {
    Положить в стек запрос на сортировку массива от 0 до size-1.
    do {
        Взять границы lb и ub текущего массива из стека.
        do {
            1. Произвести операцию разделения над текущим массивом a[lb..ub].
            2. Отправить границы большей из получившихся частей в стек.
            3. Передвинуть границы ub, lb чтобы они указывали на меньшую часть.
        } пока меньшая часть состоит из двух или более элементов
    } пока в стеке есть запросы
}
*/






// Максимальное значение для переменной типа int.
// INT_MAX   2 147 483 647
// ОТВЕТ: (2^31) - 1
// Максимальное значение для переменной типа unsigned int.
// UINT_MAX  4 294 967 295 (0xffffffff)
// ОТВЕТ: (2^32) - 1

// [Q] Как выглядит -1 в Hex-е. 16-ти ричном представлении
// В зависимости от числа байт:
// 1 байт  = 8  бит => 1111 1111 => ответ: FF
// 2 байта = 16 бит => 1111 1111 1111 1111  => ответ: FFFF
// 4 байта = 32 бит => 1111[1] ... 1111[8]  => ответ: FFFF FFFF
// 8 байт  = 64 бит => 1111[1] ... 1111[16] => ответ: FFFF FFFF FFFF FFFF


// ТИП FLOAT
//
// [Q] Как сравнить неравенство. ДВА  float  числа ? Как сравнить ДВА  float  числа ?
// float z = 0.0;
// float a, b;
// if(a == b) // ? на сколько этот код правильный.
// if(z == 0) // ? на сколько этот код правильный.
// Так писать НЕЛЬЗЯ. Причина в погрешности таких переменных.
// 
// float c = 0;
// auto m = a / c;
// Сама переменная хранится как 

// http://programmersforum.ru/showthread.php?t=174062
// В чём разница между виртуальной и чисто виртуальной функцией / между виртуальным и чисто виртуальным методом ?




// УКАЗАТЕЛЬ — Переменная, в котой хранится адрес на какой-то объект.
// ССЫЛКА — это указатель, с которым можно работать, как с обычной переменной.

// ПУТАНИЦА И ЕЁ СУТЬ:
//   Есть "&" - ССЫЛКА    - ханит указатель на объект // Есть Оператор "&" - ВЗЯТИЕ АДРЕСА переменной по которому она расположена
// И есть "*" - УКАЗАТЕЛЬ - хранит адрес на объект    // Есть Оператор "*" - РАЗЫМЕНОВАНИЕ Указатля т.е. взятия значения по адресу который хранится в указателе
// CУТЬ - для одних и тех же вещей ввели одинаковые символы.

// int x;
// int *y; // Объявили указатель  у  
// y = &x; // От любой переменной можно взять адрес при помощи операции взятия адреса "&". Эта операция возвращает указатель
// int z = *y; // Указатель можно разыменовать при помощи операции разыменовывания "*". Это операция возвращает тот объект, на который указывает указатель

// int x;
// int &y; // просто так объявить ссылку НЕЛЬЗЯ, нужно сразу же её проинициализировать, т.е. присвоить ей тут же значние (к чему-то приравнять)
// int &y = x; // проинициализировали ссылку  у
// int z = y;






// [Q] КАКОВ РАЗМЕР УКАЗАТЕЛЯ на int ? Т.е. int* n = new (5); sizeof(n)
// В зависимости от платформы: на 32-бит машине 4 Байта. На 64-битной машине 8 байт.
// Каков размер ССЫЛКИ = Такой же как и размер указателя

// Разница между Указателем и ссылкой: Принципиальных отличий два :
// 0) ссылка не может быть равна NULL. Указатель может.
// 1) ссылка, в отличии от указателя, не может быть неинициализированной;
// 2) ссылка не может быть изменена после инициализации. ТОЛЬКО Значение ПО ССЫЛКЕ Ссылка это как бы неизменяемый указатель.
// 3) Нельзя объявить массив ссылок.
// 4) У ссылки нет адреса.
// 5) Существует арифметика указателей, но нет арифметики ссылок.
// 6) Не может быть константной ссылки, только ссылка на константу. А констатный указатель может быть.
//
// Отсюда и получаем плюсы и минусы использования того и другого :
// - Ссылки лучше использовать когда нежелательно или не планируется изменение связи ссылка → объект;
// - Указатель лучше использовать, когда возможны следующие моменты в течении жизни ссылки :
//   -- ссылка не указывает ни на какой объект;
//   -- ссылка указаывает на разные объекты в течении своего времени жизни.

// ПЛЮС ССЫЛКИ:
// Ссылка - Всегда чем-то заполненный объект. Живой объект, который не надо проверять на равенство нулю, или что она "освбождена" как память в указателе.
// Указатель - можно непроиниализировать, можно приравнять к нулю, в течение жизнт может указывать на разные объекты, он может ссылаться на освобождённую память после применения к нему "delete".


// Разница между Указателем и ссылкой: Принципиальных отличий два :
// 0) ссылка не может быть равна NULL. Указатель может.
// 1) ссылка, в отличии от указателя, не может быть неинициализированной;
// 2) ссылка не может быть изменена после инициализации. ТОЛЬКО Значение ПО ССЫЛКЕ Ссылка это как бы неизменяемый указатель.
// 3) Нельзя объявить массив ссылок.
// 4) У ссылки нет адреса.
// 5) Существует арифметика указателей, но нет арифметики ссылок.
// 6) Не может быть константной ссылки, только ссылка на константу. А констатный указатель может быть.
//
// Отсюда и получаем плюсы и минусы использования того и другого :
// - Ссылки лучше использовать когда нежелательно или не планируется изменение связи ссылка → объект;
// - Указатель лучше использовать, когда возможны следующие моменты в течении жизни ссылки :
//   -- ссылка не указывает ни на какой объект;
//   -- ссылка указаывает на разные объекты в течении своего времени жизни.

// ПЛЮС ССЫЛКИ:
// Ссылка - Всегда чем-то заполненный объект. Живой объект, который не надо проверять на равенство нулю, или что она "освбождена" как память в указателе.
// Указатель - можно непроиниализировать, можно приравнять к нулю, в течение жизнт может указывать на разные объекты, он может ссылаться на освобождённую память после применения к нему "delete".


















// Почему в Си++ нельзя организовать полноценную сборку мусора:
// - Из-за УКАЗАТЕЛЕЙ. И из-за адресной арифметики / тоесть арифметических операций с указателями.
// Мы выделили облать памяти, после произошло какое-нибудь смещение, а указатель нужно передать дальше в функцию сборщика, и собрать после смещений 
// или тех операций, что происходили с указателем, будет невозможно, ибо сборщик всех операций учесть не сможет. 
// ПРИМЕР - Под строку выделяем один (буфер =) блок памяти 1024 байта, и разделяя нулём несколько строк туда засунуть,
// и в разные функции передаём разные указатели на разные строки из этого буфера. и когда всё это освобождать, не понятно, ибо не понятно время жизни этих объектов.
// - ИХ можно приравнять к нулю.
//
// чем пользуются многие программы парсеры XML, JSON
// Приходит буфер с даными, со строкой и они под каждый отдельный нод не аллоцируют новый буфер. А все или минимум несколько нодов в один буфер
// имена нодов в одной строке, и между ними просто нули.
// ПРИЧИНА: ОДИН раз, выделенная (аллокации) память. А не по нескольку раз. Экономя времни на выделение памяти.
// Mamory Manager медленно работает, по этой причине Выделить память желательно ЕДИНОЖДЫ.





































ВНУТРИ БЛОКА. 
16.	Область видимости глобальных static переменных?
Глобальная статическая переменная имеет область видимости в пределах файла в котором она объявлена.


0. Какие книги по Си вы знаете / читали ?
Шилд Герберт - Справочники по Си/Си++
Рихтер Джефри - Программирование на Си/Си++ под Виндоус
Джосьютис. - C++ Стандартная библиотека. Питер.2004
Мейерс Скот. - Эффективное использование C++. 55 верных советов улучшить структуру и код ваших програм
Страуструп - Язык программирования С++
Кнут - Алгоритмы - Искусство программирования
Таненбаум - Операционные системы. Разработка и реализация
Qt 4.8. - Шлее М. - Профессиональное программирование на C++. (В подлиннике) - 2012

1. Что будет выведено на экран printf(“%d”, (int*)5 + 3)?  //ответ 5+(3*sizeof(int))
Смещаемся относительно адреса "5" на 3 позиции типа int, а размер int = 4 байта => 5 + (3 * 4) = 5 + 12 = 17

1.	Какой тип по умолчанию присваивается числу  с плавающей точкой 2.0?
В случае если тип не указан явно, присваивается double.


2. Что вернёт операция sizeof для login, password, object?
1) char* password = "pass12";
2) char login[] = "ivanov_oleg";
3) class object; sizeof(object);

1) Для password вернёт 4 или 8 в зависимости от платформы (для x86 вернёт 4, а для x64 вернёт 8)
ИБО password есть указатель. 
2) Для login вернёт 12
ИБО массив символов инициализируется строкой, в которой на первый взгляд 11 символов, НО в конце строки есть "/0" так называемый "закрывающий ноль" он не видим. (все строки в Сях инициализируются как нультерминируемые строки)
3) Для object вернёт 1
ИБО в С++ размер всех объектов больше 0. Размер любого объекта (даже пустого класса) по стандарту не может быть меньше 1го байта. Это реализовано затем, чтобы адрес каждого объекта был отличным от адреса любого другого объекта.
Поэтому в нашем размер объекта пустого класса равен 1-му байту.

3. Какой порядок вычисления аргументов для передачи функции? Пример
int i = 1; doSomething(++i, i++);
Слева направо.
Причём ++i, будет учитывать все операции над i, вплоть до последнего операнда функции и отправит результат от всех инкрементов в неё. А i++ отправит лишь исходное i=1 результат вычислений от себя в функцию он не отправит.

void doSomething(int a, int b)
{a = 0; b = 0;}
void main(void)
{
	int i = 1;
	doSomething(++i, i++); В функцию отправятся // 3 и 1 // Сначала выполняются все операции 					    внутри скобок, через запятую и i увеличивается до 2-ух далее передача
	int j = 2, k = 2;
	doSomething(++j, k++); В функцию отправятся // 3 и 2
}

4.1. В чём разница между malloc и new?
malloc() выделяет блок памяти (в LocalHeap) и возвращает этот блок программисту.
new выделяет память (в GlobalHeap) и вызывает конструктор объекта.
Соответ-нно delete (для new) вызывает деструктор и освобождает память. free() (для malloc()) просто освобождает память. 

4.2. В чём разница между парами операторв  new / delete  и  new[] / delete[] ?
Пара new / delete:  new выделяет память для одного элемента и вызывает конструктор для него. delete, вызывающий деструктор объекта и освобождающий память должен вызываться для объекта выделенного с помощью new.

Пара new[] / delete[]:  new[число_объектов] выделяет память для массива объектов и вызывает конструктор для каждого из них. delete[] вызывается для массива, выделенного с помощью new[] .

СИНТАКСИС:
int *p_var = new int(5); // Инициализация указателя 
delete p_var;

int *p_arr = new int[10];  //указатель на выделенную память под 10 элементов типа int
delete [] p_arr;



БЛИЦ ВОПРОСЫ

[Q] Сколько будет 2 в какой-нибудь степени (случайное число для степени от 6 до 16).
ОТВЕТ: Посчитать в уме

[Q] Максимальное значение для переменной типа int.
INT_MAX   2 147 483 647
ОТВЕТ: (231) - 1
Максимальное значение для переменной типа unsigned int.
UINT_MAX  4 294 967 295 (0xFFFF FFFF)  4 байта = 32 бита
ОТВЕТ: (232) - 1

[Q] Как выглядит -1 в Hex-е. 16-тиричном представлении
 В зависимости от числа байт:
 1 байт  = 8  бит => 1111 1111 => ответ: FF
 2 байта = 16 бит => 1111 1111 1111 1111  => ответ: FFFF
 4 байта = 32 бит => 1111[1] ... 1111[8]  => ответ: FFFF FFFF
 8 байт  = 64 бит => 1111[1] ... 1111[16] => ответ: FFFF FFFF FFFF FFFF




ТЕОРИЯ ПРОГРАММИРОВАНИЯ

[Q] Что такое Инкапсуляция, Наследование, Полиморфизм ?

Инкапсуляция — это свойство, позволяющее объединить в классе и данные, и методы, работающие с ними и скрыть детали реализации от пользователя
Verkapselung — Eigenschaft die es ermöglicht, in einer Klasse  Daten und Methoden die mit diesen Daten arbeiten zu verbinden und die Implementierungsdetails vor dem Benutzer zu verbergen
Наследование — это свойство, позволяющее создать новый класс-потомок на основе уже существующего, при этом все характеристики класса родителя присваиваются классу-потомку
Vererbung — Eigenschaft die es ermöglicht, eine neue abgeleitete Kinderklasse auf der Basis einer Elternklasse zu erstellen.
Dabei werden der Linderklasse alle Eigenschaften der Elternklasse übergeben / zugewiesen.
Полиморфизм — свойство классов, позволяющее использовать объекты классов с одинаковым интерфейсом без информации о типе и внутренней структуре объекта 

Abgeleitete Klassen erben die Funktionen ihrer Basisklasse. Sollte eine Funktion der Basisklasse nicht die gewünschte Funktionalität für die abgeleitete Klasse liefern, können Sie sie überschreiben. Dann wird die Funktion der Basisklasse für alle Instanzen der abgeleiteten Klasse überdeckt.
Er bezeichnet die Tatsache, das eine Methode in verschiedenen abgeleiteten Klassen einer Hierarchie unterschiedlich implementiert werden kann.  So ist es möglich, dass verschiedene Klassen gleichlautende Methoden enthalten, die aber nicht den gleichen Inhalt haben. Verschiedene Objekte werden gleich behandelt, reagieren aber unterschiedlich.


[Q] Чем отличаются Постфиксный инкремент i++ от Префиксного ++i 

1. Результатом вычислений и порядком присваивания:
int x = 5, y = 0;

y = ++x;	// y = 6, x = 6:  сначала увеличивается x на 1, потом y = x.
y = --x;	// y = 5, x = 5: сначала уменьшается x на 1, потом y = x.
y = x++;	// y = 5, x = 6: сначала присваивается значение y = x, потом x увеличивается на 1.


(!) ПОДРОБНО:

x++ - ПОСТИНКРЕМЕНТ, x--  - ПОСТДЕКРЕМЕНТ.

++x - ПРЕИНКРЕМЕНТ, --x - ПРЕДЕКРЕМЕНТ. Оба 


10.	Что такое inline функция, опишите inline функцию?
Inline функция это автоматически подставляемая функция, при  обращении к которой не происходит перехода на саму функцию, потому как код inline функции автоматически вставляется в код использующей её функции на этапе компиляции, что зачастую оптимизирует скорость выполнения программы, но увеличивает размер программы.
Объявление: inline int add(int t1, int t2);
11.	Какие ограничения накладываются на inline функции?
1)	Некоторые компиляторы не могут компилировать встроенный код для функции, содержащей циклы, а также предложения switch и goto.
2)	Зачастую бывает нельзя создать рекурсивную inline функцию.
3)	Запрещается использование статических членов функции.

КЛАССЫ И СТРУКТУРЫ

14. В каком порядке инициализируются члены класса?
Члены класса создаются в порядке их объявления в классе.   Уничтожаются они в обратном порядке. 

(!) ПОДРОБНО:


15. Какие методы класса генерируются компилятором автоматически (неявно)?
 1. Конструктор по умолчанию (без параметров)
 2. Конструктор КОПИИ по умолчанию
 3. Деструктор класса
 4. Оператор присваивания =
 + С 11 стандарта добавились:
 5. Конструктор перемещения
 6. Оператор получения адреса

(!) ПОДРОБНО:
Итак, если вы написали
class Empty {};

То, знайте, что на самом деле вы создали примерно вот такой класс:
class Empty 
{
public:
  Empty();  // Конструктор без параметров
  Empty(const Empty &);  // Копирующий конструктор
  ~Empty();  // Деструктор
  Empty& operator=(const Empty &);  // Оператор присвоения
  Empty * operator&();  // Оператор получения адреса
  const Empty * operator&() const;  // Оператор получения адреса константного объекта
};

16.1 В каких случаях вызывается деструктор класса?
1) явным образом - при вызове оператора delete; 
2.1) неявным образом при выходе из блока в котором определена переменная
2.2) неявным образом - или при раскрутке стека при отработке исключения; 

75.	В процессе обработки исключения, исключение не может исходить из самого деструктора, так как это считается ошибкой в работе механизма обработки исключений, приводящей к вызову std::terminate(); Однако деструктор может обрабатывать исключения, которые генерируются вызываемыми им функциями, сам же деструктор  не должен возбуждать исключений.

16.2 Назовите ситуацию, когда деструктор может быть никогда не вызван?
В случае (аварийного) завершения потока без вызова деструкторов объектов что были созданы внутри этого потока, что может привести к утечкам памяти.

(!) ПОДРОБНО:
Вопрос имеет отношение не совсем к С++, а к многопоточному программированию.
Этот механизм может быть нарушен, если поток выполнения прерван извне (например функцией операционной системы "завершить поток" или "завершить процесс"). И если завершение процесса не особо критично (при этом все ресурсы освобождаются), то завершение потока без вызова деструкторов может привести к утечкам памяти, или ресурсов (например не разлоченные объекты синхронизации, которые могут привести к дедлокам). По этой причине в коде С++ настоятельно не рекомендуется пользоваться "сырым" API для работы с потоками, а использовать С++ библиотеки гарантирующие корректную очистку ресурсов, например Boost threads
17. Когда имеет смысл делать деструктор виртуальным?
Зачем нужен виртуальный деструктор?

Ответ: Чтобы избежать возможной утечки ресурсов или другого неконтролируемого поведения объекта, в логику работы которого включен вызов деструктора.

Пример:
class Base
{
public:
    virtual ~Base() { std::cout << "Hello from ~Base()" << std::endl; }
};

class Derived : public Base
{
public:
    virtual ~Derived() 
    {
        // Здесь могла бы быть очистка ресурсов
        std::cout << "Hello from ~Derived()" << std::endl;
    }
};

Base *obj = new Derived();
delete obj;

Output:
Hello from ~Derived()
Hello from ~Base()

Без ключевого слова virtual у родительского класса Base деструктор порожденного класса не был бы вызван. Т.е. вызвался бы только ~Base():


19. В каких случаях вызывается конструктор копий?
Конструктор вызывается при создании копии объекта некоторого класса, что инициализирует новый объект того же типа. Но конструктор вызывается и в менее очевидных случаях, когда происходит создание временной копии некоторого объекта.

1) Инициализация нового объекта другим объектом того же типа
К примеру, при инициализации некоторого объекта А типа MyClassобъектом В того же типа происходит создание побитовой копии объекта B, с последующей ее присваиванием объекту А.
      MyClass old_obj;  
      MyClass new_obj = old_obj; 
2) Передача объекта в качестве аргументов в функцию
Как известно, в языках С и С++ по умолчанию аргументы в функцию передаются по значению. При этом происходит создание копии аргумента, которая и участвует во всех выражениях внутри функции, 
func(my_class); - Будет вызван конструктор копий для параметра функции

3) Возврат объекта из функции - также создает побитовую временную копию возвращаемого объекта. MyClass func();
my_obj_class = func();



	1. Чем отличается Структура от Класса ?
У Структуры все поля по умолчанию public, у Класса все поля по умолчанию private
БОЛЬШЕ Они ни чем не отличаются. По сути структура как объект является классом и наоборот.
Более того. На вопрос, "Какие ключевые слова означают класс ?" верный ответ: class и struct

	2. Для чего используются ключевые слова public и private?
Для определения области видимости.

	14. Что такое метод? Как вызывается метод?
Метод - это функция, определённая в классе.
Если статический, то вызывается для класса, если обычный - то для объекта класса.

	20.	Может ли константный метод вызываться для объектов-переменных?
		А обычный метод — для объектов-констант?
Ответы: Да (на первый вопрос). Нет (на второй вопрос).   (ПРОВЕРИТЬ!!!)

	2. Как можно передать объекты в качестве параметров в функции или классы ?
1) По указателю
2) По ссылке 
3) По значению (!) По значению передаётся КОПИЯ объекта (вызывается конструктор копирования !)
Возвращается при этом:
1) тот же указатель
2) та же ссылка на объект 
3) копия созданная при передаче по значению внутри функции по выходу из функции будет разрушена (???)

	2. Из чего складывается размер объекта в памяти ?
	Сколько в памяти занимает произвольный объект (структура / класс) ?

0) МЕТОДЫ НЕ ВЛИЯЮТ НА РАЗМЕР ОБЪЕКТА !!!





Ответ: Размер объекта в общем случае равен = (1) + (2) + (3) + (4)
(1) + sizeof всех членов класса
(2) + остаток для выравнивания (по умолчанию выравнивание 4 байта) 
(3) + vtblptr = sizeof указателя на vtable (если есть виртуальные функции, который находится вскгда ПЕРВЫМ в памяти объетка, чтобы имея указатель на базовый класс ты в любом случае мог бы обратиться ко всем функциям (любой из на любой ступни наследования) ) 
(4) + указатели на классы предков, от которых было сделано виртуальное наследование (=размер указателя * количество классов, есть множ.насл. от двух классов, значит и будет 2 указат. на них)
(0)  - методы внутри объекта не влияют на размер объекта
(static) - static-поля НЕ ЯВЛЯЮТСЯ ЧАСТЬЮ КЛАССА

1 class A {
2 private:
3   float f;
4   const int i;
5   static char j;
6   double c;
7 };
Рамер объекта класса A будет равен равен сумме размеров типов float, int, double. Статическое поле не является частью класса.
1 bool b = sizeof( A ) == sizeof( float ) + sizeof( int ) + sizeof( double ); // b == true;


Пример:
struct Foo
{
    int i;
    char a;
};

int size = sizeof(Foo);
// 8 байт, хотя int (4) + char (1) = 5. Все дело в дефолтном выравнивании равном 4, т.е. размер должен быть кратен блоку в 4 байта.


	56. Что такое выравнивание и от чего оно зависит? Влияет ли выравнивание на размер класса?
Расположение данных в памяти поблочно, так как процессор читает машинными словами. Зависит от реализации компилятора, ОЗУ и процессора. Влияет.


	2. Каков размер пустого объекта - Класса или Структуры ?
ОТВЕТ: 1 Байт.

(!) ПОДРОБНО:
	Размер любого объекта программы на С++ по стандарту не может быть меньше 1 байта
(точнее одного идентифицируемого на данной платформе элемента памяти). Это 
связано с тем, что никакие два разных объекта не могут иметь одинаковые адреса.
Если размер объекта был бы 0, то в массиве таких объектов все элементы имели
бы одинаковый адрес, а это недопустимо.

	25. Одинаков ли размер класса и аналогичной структуры?
Да.

	24. Влияют ли методы на размер объекта?
Нет.

	18. Что обозначается ключевым словом this ?
Указатель на объект, который вызвал метод.

	19. Зачем нужны константные методы? Чем отличается определение константного метода от обычного?
1) Чтобы предотвратить случайное изменение данных внутри метода и показать, что метод не меняет состояние класса.
2) После названия методов и скобок с параметрами указывается ключевое слово CONST:

( !!! ПРИМЕР !!! ) 



52. Разрешается ли объявлять массив в качестве поля класса. Как присвоить элементам массива начальные значения?
Да.
В классе - только в конструкторе.
Если статический константый, то вне пределов класса.

55. Как объявить в классе и проинициализировать статический константный массив?
class A { static const int I[3]; } A::I[3] = {1, 2};


62.	При наличии нескольких базовых классов становится возможной ситуация, когда какой-то класс дважды становится базовым(реплецированным) для другого класса.  В таком случае два объекта типа Base будут сосуществовать вполне нормально.  В таком случае возможны неоднозначности, которые должны разрешаться при помощи оператора разрешения области видения.
Пример: 
		class Base{ public: void something(); };
		class A: public Base{};
		class B: public Base{};
		class AB: public A, public B {};
		void f(AB* ab){
			ab->A::something();
		}


















ПОЛИМОРФИЗМ

	21. Объясните принцип полиморфизма.
Возможность работать с объектами разных классов одинаковым образом.
Поддержка различного поведения родственных классов, предоставляемого через единый интерфейс базового класса.
Есть статический - на этапе компиляции. Шаблоны, перегрузка функций и операторов.
Есть динамический - виртуальные функции. Точное значение операции определяется объектом для которого она вызывается.



ССЫЛКИ И УКАЗАТЕЛИ

УКАЗАТЕЛЬ — переменная, в которой хранится адрес на какой-то объект.
СЫЛКА — это указатель, с которым можно работать, как с обычной переменной.

ПУТАНИЦА И ЕЁ СУТЬ:
  Есть "&" - ССЫЛКА    - хранит указатель на объект 
// Есть Оператор "&" - ВЗЯТИЕ АДРЕСА переменной по которому она расположена

И есть "*" - УКАЗАТЕЛЬ - хранит адрес на объект    
// Есть Оператор "*" - РАЗЫМЕНОВАНИЕ Указателя т.е. взятия значения по адресу который хранится в указателе
CУТЬ - для одних и тех же вещей ввели одинаковые символы.

int x;
int *y; // Объявили указатель  у  
y = &x; // От любой переменной можно взять адрес при помощи операции взятия адреса "&". Эта операция возвращает указатель
int z = *y; // Указатель можно разыменовать при помощи операции разыменовывания "*". Это операция возвращает тот объект, на который указывает указатель

int x;
int &y; // просто так объявить ссылку НЕЛЬЗЯ, нужно сразу же её проинициализировать, т.е. присвоить ей тут же значение (к чему-то приравнять)
int &y = x; // проинициализировали ссылку  у
int z = y;


[Q] КАКОВ РАЗМЕР УКАЗАТЕЛЯ ? Т.е. int* n = new (5); sizeof(n)
В зависимости от платформы: на 32-бит машине 4 Байта. На 64-битной машине 8 байт.

[Q] Каков размер ССЫЛКИ ?
Такой же как и размер указателя
	
[Q] Разница между Указателем и ссылкой ?
Принципиальных отличий два 0), 1), 2) :
 0) ссылка не может быть равна NULL. Указатель может.
 1) ссылка, в отличии от указателя, не может быть неинициализированной;
 2) ссылка не может быть изменена после инициализации. ТОЛЬКО Значение ПО ССЫЛКЕ Ссылка это как бы неизменяемый указатель.
 3) Нельзя объявить массив ссылок.
 4) У ссылки нет адреса.
 5) Существует арифметика указателей, но нет арифметики ссылок.
 6) Не может быть константной ссылки, только ссылка на константу. А констатный указатель может быть.

[Q] Плюсы и минусы использования того и другого :
 - Ссылки лучше использовать когда нежелательно
или не планируется изменение связи ссылка → объект;
 - Указатель лучше использовать, когда возможны следующие моменты в течении жизни ссылки :
   -- ссылка не указывает ни на какой объект;
   -- ссылка указывает на разные объекты в течении своего времени жизни.

 ПЛЮСЫ И МИНУСЫ:
 Ссылка - (+)Всегда чем-то заполненный объект. (+)Живой объект, который не надо проверять на равенство нулю, или что она "освобождена" как память в указателе.
 Указатель - (+)можно не проинициализировать, (+)можно приравнять к нулю, (+)в течение жизни может указывать на разные объекты, (-)НО может ссылаться на освобождённую память после применения к нему "delete".

	[Q] Почему в Си++ нельзя организовать полноценную сборку мусора ?
ОТВЕТ: Из-за УКАЗАТЕЛЕЙ. И из-за адресной арифметики / то есть арифметических операций с указателями.
	Мы выделили область памяти, после произошло какое-нибудь смещение, а указатель нужно передать дальше в функцию сборщика, и собрать после смещений или тех операций, что происходили с указателем, будет невозможно, ибо сборщик всех операций учесть не сможет.

УМНЫЕ УКАЗАТЕЛИ

[Q] Что такое "умные" указатели, чем они отличаются от обычных? Зачем они нужны? Какие реализации вам известны?
ОТВЕТ
Как правило шаблонный класс, имитирующий интерфейс обычного указателя и добавляющий некую новую функциональность, например проверку границ при доступе или очистку памяти.
Обычные указатели по сравнению с умными имеют ряд недостатков:
Указатель не управляет временем жизни объекта, ответственность за удаление объекта целиком лежит на программисте. Проще говоря, указатель не «владеет» объектом.
Указатели, ссылающиеся на один и тот же объект, никак не связаны между собой. Это создаёт проблему «битых» указателей – указателей, ссылающихся на освобождённые или перемещенные объекты.
Нет никакой возможности проверить, указывает ли указатель на корректные данные, либо «в никуда».
Указатель на единичный объект и указатель на массив объектов никак не отличаются друг от друга.
Из этих недостатков вытекает преимущество использования умных указателей.

Бывают нескольких видов, например
Простые владеющие указатели, которые при присвоении нового значения или удалении сами удаляют объект.
Еще пример - Указатели с подсчётом ссылок
Различные реализации доступны в stl и boost.
std::auto_ptr<>
std::tr1::shared_ptr<>
std::tr1::weak_ptr<>
boost::intrusive_ptr<>
boost::scoped_ptr<>
boost::scoped_array<>, boost::shared_array<>




[Q]  Разница между оператором присваивания и копирующим конструктором +их реализации ? 

1)  Копирующий конструктор a(b); - инициализирует ранее неинициализированный (не существующий) объект из данных другого объекта (в момент создания объекта он сразу же инициализирует память.)
// A copy constructor is used to initialize a previously uninitialized object from some other object's data.	Реализация:	A(const A& rhs) : data_(rhs.data_) {}
2) Оператор присваивания a = b;  - заменяет данные в ранее проинициализированном (созданном) объекте, данными из другого объекта. (сначала создаёт объект, и потом перезатирает то, что он проинициализировал новым значением)
// An assignment operator is used to replace the data of a previously initialized object with some other object's data.
	Реализация:	A& operator=(const A& rhs) { data_ = rhs.data_; return *this; }

ПРИМЕР вызова Копирующего конструктора:
Example for copy constructor :
Base obj1(5);
Base obj2 = obj1; //calls copy constructor (ИБО новый объект obj2 только создался +не был ранее 												проинициализирован)
ПРИМЕР вызова Оператора присваивания: Example for assignment operator:
Base obj1(5); //calls Base class constructor
Base obj2; //calls Base class default constructor // вызывается конструктор по умолчанию
obj2 = obj1; //calls assignment operator (ИБО оба объекта уже были созданы ранее(проинициализированны)



[Q]   Как защитить объект от копирования?

Ответ: Сделать private конструктор копирования и оператор присваивания "="

Пример:
class NonCopyable
{
// какой-то код
private:
    NonCopyable(NonCopyable&)
    void operator=(const NonCopyable&)
};

NonCopyable a; 
NonCopyable b = a; // error C2248: 'NonCopyable::NonCopyable' : cannot access private member
a = b; // error C2248: 'NonCopyable::operator =' : cannot access private member

подробнее тут - https://habrahabr.ru/company/abbyy/blog/142595/


КОНСТАНТНОСТЬ

[Q]  Для каких целей применяется ключевое слово const?

Ответ: 
1) Позволяет задать константность объекта  (Чтобы не было возможности изменить ОБЪЕКТ)
2) Позволяет задать константность указателя (Чтобы не было возможности изменить указатель)
3) Позволяет указать, что данный метод не модифицирует члены класса, т.е. сохраняет состояние объекта. Чтобы метод не мог изменять члены класса, ЗА Исключением членов mutable. 

1. Позволяет задать константность объекта
const int i = 8; 
i = 125; // error C3892: 'i' : you cannot assign to a variable that is const 
2. Позволяет указать, что данный метод не модифицирует члены класса, т.е. сохраняет состояние объекта. Константный метод может изменять члены класса, если они объявлены как mutable.
class Foo 
{ 
private: 
    int i; 
public: 
    void func() const 
    { 
        i = 3; // error C3490: 'i' cannot be modified because it is being accessed through a const object 
    } 
}; 
3. Позволяет задать константность указателя
int i = 4; 
int* const j(&i); 
int k = 6; 
*j = k; // Ok 
j = &k; // error C3892: 'j' : you cannot assign to a variable that is const 
4. const можно использовать со ссылками, чтобы через ссылку нельзя было поменять значение переменной.
int p = 4; 
const int& x=p; //нельзя через x поменять значение p 
x=5; //ошибка 
5. const удобен, если нужно передать параметры в функцию, но при этом надо обязательно знать, что переданный параметр не будет изменен.
void f1(const std::string& s); 
void f2(const std::string* sptr); 
В первой и второй функции попытки изменить строку будут пойманы на этапе компиляции. 
6. Объявления
int const* p2 
const int* p3 
это по разному записанное одно и то же объявление. Указатель на целое, которое нельзя менять. 
7. Для предотвращения нечаянной модификации возвращенного объекта можно объявить тип возврата как const:
const int &get_val( ... ) 



Пример 1. Не можем изменить значение объекта:
const int i = 1;
i = 2; // error C3892: 'i' : you cannot assign to a variable that is const

Пример 2. Не можем изменить указатель на объект:
int i = 1;
int* const j(&i);
int k = 2;
*j = k; // Ok
j = &k; // error C3892: 'j' : you cannot assign to a variable that is const

Пример 3. Не можем изменить члены класса:
class Foo
{
private:
    int i;
public:
    void func() const
    {
        i = 1; // error C3490: 'i' cannot be modified because it is being accessed through a const object
    }
};

Дополнение: константный метод может изменять члены класса, если они объявлены как mutable. 


    int i = 1, ii=2, iii=3;
    int k = 10;

    int* const p1(&i); // Позволяет задать константность указателя
    // идентичные записи // Указатель на целое, которое нельзя менять
    int const* p2(&ii);
    const int* p3(&iii);

    // Данные на которые ссылается указатель менять можно. Сам Указатель НЕЛЬЗЯ
    *p1 = k;	// Ok 
    //p1 = &k;	// error C3892: 'p1' : you cannot assign to a variable that is const 

    //*p2 = k;	// error C3892: 'p2' : you cannot assign to a variable that is const 
    p2 = &k;	// Ok 
    //*p3 = k;	// error C3892: 'p3' : you cannot assign to a variable that is const 
    p3 = &k;	// Ok 


	[Q]  Через что можно выразить оператор РАВНО и оператор БОЛЬШЕ ?
ОТВЕТ: Операторы «больше» и «равно» выводятся из одного оператора «меньше»
Чтобы поддерживать SORT, FIND и т.д. НЕ нужен оператор equality (a == b)
А НУЖЕН  equivalence  это когда первое значение не меньше второго, ни второе значение не меньше первого => (!(a < b) && !(b < a))

оператор БОЛЬШЕ > выражается через меньше => возвращает тру, когда не меньше и не равно => ()
оператор РАВНО ==  =>  


	[Q]  Какие операторы НЕЛЬЗЯ перегружать ? 
ПЕРЕГРУЖАТЬ НЕЛЬЗЯ

 :: (разрешение области видимости)
 . (выбор члена)
 .* (выбор члена через указатель на член)
 ?: тернарный оператор
 sizeof, typeid

У первых трех в правой части имя, а не значение.
У тернарного оператора аж 3 параметра, к тому же его возвращаемое значение является l-value.
Переопределять sizeof, typeid, думаю, просто нет смысла.
Для ВСТРОЕННЫХ ТИПОВ данных перегружать операции НЕЛЬЗЯ, потому что тип — это набор данных и операций над ними. Изменяя операции, выполняемые над данными типа, мы меняем само определение типа. Также, НЕЛЬЗЯ изменить ПРИОРИТЕТ Операции и определить новую операцию.


	[Q]  Привести пример перегрузки оператора (операции как метода):
13.	Что такое перегрузка операторов?
Один из способов реализации полиморфизма, заключающийся в возможности одновременного существования в одной области видимости нескольких различных вариантов применения оператора, имеющих одно и то же имя, но различающихся типами параметров, к которым они применяются.

	пример


	[Q]  Какой результат возвращают операторы с присваиванием:
Отавет: Ссылку

	[Q]  32. Как различаются перегруженная префиксная и постфиксная операции инкремента и декремента?
Отавет: Постфикс имеет фиктивный параметр.

	[Q]  33. Что означает выражение *this? В каких случаях оно используется?
Отавет:  Ссылка на объект.  Для разрешения неоднозначности, для определения размера.

	[Q]  34. Какие операции не рекомендуется перегружать как методы класса? Почему?
Отавет:  Те, которым не нужен доступ к внутренним переменным класса. Чтобы не нарушать инкапсуляции.

	[Q]  35. Какие операции разрешается перегружать только как методы класса?
Отавет:  Те, для которых нужна гарантия, что их первый операнд lvalue.
1) =  (равно)   2) [ ]  (квадратные скобки)   3) ->  (стрелочка)



	[Q] Какая разница между определёнными операторами внутри класса, и (перегрузка внешним образом) вне класса, заведённые как friend-ы в класс?
	Ответ: Внешняя перегрузка через заведение функции как  friend  функции имеет 2 параметра, а внутренняя перегрузка функции требует указания только одного входного параметра.
	Ответ: Если операторы определены внутри класса, то они полноценно наследуются классами потомками. ЕСЛИ же операторы заведены / объявлены как друзья класса, то наследования их классами потомками фактически не происходит.	

	(!!! ПРИМЕР !!!)


	[Q] Для чего нужны функции-друзья ?
Что такое дружественная функция? Приведите пример.

Дружественная функция — это функция, не являющаяся членом класса, имеющая доступ к закрытым членам класса, для которого она объявляется другом. Объявляется с ключевым словом friend с модификатором доступа public. Может быть как членом класса, так и нет.

Пример:
class Sample
{
  private: int a,b;
  public:  friend int Min(Sample s);
};

int Min(Sample s)
{ return s.a<s.b? s.a: s.b; }


	[Q] Для чего нужны классы-друзья ?
Для фактически определения одного класса внутри другого

	[Q]  




КОНУСТРУТОРЫ И ДЕСТРУКТОРЫ

[Q]  37. Дайте определение конструктора. Каково назначение конструктора? Перечислите отличия конструктора от метода ?
ОТВЕТ: Специальный метод для инициализации объекта.
Не имеет возвращаемого значения. Не может быть статическим, виртуальным. Внутри не работает механизм виртуальных функций, потому что ещё не инициализирована таблица виртуальных функций.

[Q]  38. Сколько конструкторов может быть в классе? Допускается ли перегрузка конструкторов? Какие виды конструкторов создаются по умолчанию?
ОТВЕТ: 
1) Сколько угодно. 
2) Да. 
3) default constructor = конструктор по умолчанию, copy constructor = копирующий конструктор.

[Q]  39. Может ли конструктор быть приватным? Какие последствия влечет за собой объявление конструктора приватным?
ОТВЕТ: 
1) Да. КОНСТРУКТОР МОЖЕТ БЫТЬ ПРИВАТНЫМ (пример Singleton) 
2) Невозможность конструирования объекта класса.

[Q]  40. Может ли Деструктор быть приватным? Какие последствия влечет за собой объявление Деструктора приватным?
ОТВЕТ: 
1) Да. ДЕСТРКУКТОР МОЖЕТ БЫТЬ ПРИВАТНЫМ (пример Singleton) 
2) Невозможность конструирования объекта класса.

[Q]  40. Приведите несколько случаев, когда конструктор вызывается неявно?
ОТВЕТ: 
Копирование, конструирование внутренних объектов, передача по значению, приведение типа..



ОПЕРАТОРЫ  NEW  И   DELETE

[Q]  40. Сколько операторов NEW вам известно?
ОТВЕТ: 
1) new
2) placement new
3) new(nothrow)

[Q]  41. Как проинициализировать динамическую переменную?
ОТВЕТ: 
в списке инициализаторов
new
placement new
new(nothrow)

[Q]  43. Каким образом разрешается инициализировать константные поля в классе?
ОТВЕТ: 
статические интегральные прямо на месте, остальные в инициализаторе или вне класса, или в конструкторе


[Q]  45. Какие конструкции С++ разрешается использовать в списке инициализации качестве инициализирующих выражений?
ОТВЕТ: 
rvalue, инициализированные lvalue




ВИРТУАЛЬНЫЕ ФУНКЦИИ

[Q]  Зачем нужна виртуальная функция ?
ОТВЕТ: Чтобы иметь возможность использовать механизм Полиморфизма. Определяя в базовом классе функцию, которая будет присутствовать в классах наследниках, и по сигнатуре она будет одна и та же или с какими-то изменениями, НО главное, что работать в каждом классе наследнике она сможет по разному. При этом вызывать эту функцию можно будет через указатель на базовый класс. 
 
[Q]  Что такое виртуальный метод ?
Функция объявленная в базовом классе с использованием ключевого слова virtual, переопределенная в одном или в нескольких классах наследниках (производных классах).

[Q]  В чём разница между виртуальной и чисто виртуальной функцией / между виртуальным и чисто виртуальным методом  / Отличие виртуального метода от чисто-виртуального метода ?
1) Чисто виртуальная функция имеет визуальное различие, а именно "= 0" приписанный в конец.
2) Чисто виртуальная функция в отличие от обычной виртуальной функции не может иметь определения в базовом классе (а просто вирт. функция МОЖЕТ), она может быть только переопределена в классах наследниках. 

[Q] Самый часто используемый способ использования виртуальной функции
ОТВЕТ: Использование через указатель базового класса вызова функций, переопределённых в классах наследниках



8.2 Что такое абстрактный класс?
Абстрактный класс - это такой класс, который имеет хотя бы одну чисто виртуальную функцию.
Для такого класса невозможно создать объект класса. Его используют исключительно для дальнейшего наследования.

9. Где стоит избегать вызовов виртуальных функций?
В Конструкторе и Деструкторе класса ! 
Пример ТУТ https://habrahabr.ru/post/64280/



[Q] Какая самая простая функция хэширования для Целых чисел ?
ОТВЕТ 1: Операция взятия по модулю "%"
ОТВЕТ 2: 
ОТВЕТ 3:




















ПРИВЕДЕНИЕ ТИПОВ

[Q] 50. Для чего служит ключевое слово explicit?
Это модификатор для запрещения неявного преобразования типов объектов аргументов конструктора

[Q] 48. Как запретить неявное преобразование типа, выполняемое конструктором инициализации?
explicit

(!!! ПРИМЕР !!!)


[Q] 59.	Для чего объявлять конструктор с ключевым словом explicit?
Таким образом происходит подавление неявное приведение типа. Такой конструктор можно вызывать только явно.

(!!! ПРИМЕР !!!)


[Q] Назовите четыре варианта приведения типов?
1) const_cast - аннулирует const и volatile -  убирает константность объекта. Никакие другие приведения в С++ стиле не позволяют такое сделать.
2) static_cast – иерархическое преобразование с проверкой на этапе компиляции - явное приведение типов, например, и в основном 1) для встроенных типов (Int к double), то будут использованы встроенные в C++ правила их приведения. 2) Если это типы, определенные программистом, то будут использованы правила приведения, определенные программистом.
static_cast - ещё варианты: приведение неконстантных объектов к константным. между указателями корректен, только если один из указателей - это указатель на void или если это приведение между объектами классов, указателей на базовый класс к указателю на производный.
3) dynamic_cast — проверяется на этапе выполнения RTTI -  применяется для выполнения безопасного понижающего приведения. Позволяет определить, принадлежит ли объект данного типа некоторой иерархии наследования. Единственное приведение, которое не может быть выполнено с использованием старого синтаксиса в Си-стиле. Требует определённых временных затрат.
4) reinterpret_cast — несвязанное преобразование с проверкой на этапе компиляции -  Обычно используется, чтобы привести указатель к указателю, указатель к целому, целое к указателю. Умеет также работать со ссылками. Результат может быть некорректным, никаких проверок не делается. Считается, что вы лучше компилятора знаете как на самом деле обстоят дела, а он тихо подчиняется. Не может быть приведено одно значение к другому значению. 
 	Предназначен для низкоуровневых приведений, которые порождают зависимые от реализации (непереносимые) результаты, например приведение указателя к int. Вне низкоуровневого кода такое приведение должно использоваться редко.



10.2 Почему стоит использовать преобразования типов в C++ стиле?
Потому что оно более безопасное. Си-стиль позволяет привести почти всё что угодно ко всему, без проверок от компилятора! C++-стиль приведения более заметен, чем Си-стиль.


11.1 Чем отличается dynamic_cast от других вариантов приведения типов?
Безопасное приведение по иерархии наследования, в том числе и для виртуального наследования.
dynamic_cast<derv_class *>(base_class_ptr_expr)
Используется RTTI (Runtime Type Information), чтобы привести один указатель на объект класса к другому указателю на объект класса. Классы должны быть полиморфными, то есть в базовом классе должна быть хотя бы одна виртуальная функция. Если эти условие не соблюдено, ошибка возникнет на этапе компиляции. Если приведение невозможно, то об этом станет ясно только на этапе выполнения программы и будет возвращен NULL.
dynamic_cast<derv_class &>(base_class_ref_expr)

11.2 Каковы особенности использования данной операции для указателей и ссылок?
Работа со ссылками происходит почти как с указателями, но в случае ошибки во время исполнения будет выброшено исключение bad_cast.

66.	Операция dynamic_cast при применении к указателю, в случае не возможности привести к необходимому типу, вернёт нуль. В случае применения к ссылкам, при неудачи будет выброшено исключение типа bad_cast.

ИСКЛЮЧЕНИЯ

[Q] Что такое исключение?
1. И Событие отлавливаемое операторами
try {} - "секция попытка" - попробовать выполнить код с потенциальным исключением внутри
catch( ) {} - "секция ловушка" - поймать исключение, если оно произошло в блоке try
throw {} -  "передать исключение дальше", если необходимо
2. И Объект - если исключение ПОЙМАННО в блоке catch() {} и его нужно обработать, или получить о нём / из него информацию.
3. Исключение может быть ЛЮБОГО ТИПА, ибо по факту оно есть КЛАСС.

[Q] Что стоит помнить при использовании исключений в конструкторе объекта?
ОТВЕТ: Если исключение не обработано, то c логической точки зрения разрушается объект, который еще не создан, а с технической, так как он еще не создан, то и деструктор этого объекта не будет вызван.


[Q]  .Для чего используется throw без аргументов?

Ответ: Для повторного возбуждения предыдущего исключения и направления его следующему обработчику.
Пример:

try
{
    //....
    try
    {
        // Call something
    }
    catch(const std::exception& )
    {
        // Make/Check something..
        throw; // Пересылаем исключение следующему обработчику
    }
    //...
}
catch(const std::exception& e)
{
    std::cout << e.what() << std::endl;
}



72.	Пример спецификации исключений:
void f(int a) throw(ExceptA, ExceptB);
Функция f может выбрасывать исключения типа ExceptA, ExceptB и производных от них.
Попытка выбросить любое другое исключение приведёт к вызову std::unexpected.
void g() throw(); // Функция g не генерирует исключений.
void h(); // h может генерировать любые исключения. 

73.	Спецификация исключений не является частью типа функции и в операторе typedef она не допускается.

STL - КОНТЕЙНЕРЫ

[Q] ОПРЕДЕЛЕНИЕ - STD::MAP - Отображение / Ассоциативный массив ?
Отсортированный ассоциативный контейнер, который содержит пары ключ-значение с неповторяющимися ключами.

[Q]  STD::MAP - Как организованны данные внутри Отображения / Ассоциативного массива ?
Данные внутри организованы в виде красно-чёрного дерева

[Q] ОПРЕДЕЛЕНИЕ - STD:: UNORDERED_MAP 
Хэш таблица, с внутренними ячейками, внутри которых расположены списки коллизий.

[Q] Что нужно сделать, чтобы положить свой класс в, unordered_map (и ДРУГИЕ unordered контейнеры) ?
В нашем классе мы должны определить хэш-функцию !

Если положить свой класс без определённой хеш-функци, то мы получим сообщение об ошибке:
cannot convert from 'const Name' to 'size_t'

[Q] Как устроена хэш таблица в STD:: UNORDERED_MAP:
 Берём значение которое хотим положить в хэш таблицу, его называем КЛЮЧ. Считаем от Ключа хэш = этот хэш является индексом элемента для данного ключа в таблице.
 Может случиться  КОЛЛИЗИЯ - причём даже не в силу повторений выходных хешей, а в силу ограниченности длины контейнера 
 От двух разных значений может получится одинаковый хэш, что может привести к Колизиям => это разрешается так:
 На месте элемента, где происзошла коллизия начнёт формироваться список "одинаковых" элементов.
(!) для  UNORDERED_MAP  на каждой позиции хранятся БАКЕТЫ (bucket) - это линки на контейнеры, типа list (список) в которые уже складываться коллизии
И так мы получаем UNORDERE_MAP который представит из себя - таблицу из списков или хэш таблицу с бакетами (указателями на список в каждой хэш-позиции).
 В случае, если для всех элементов, ВСЕ хэшы совпали, то именно в этом случае мы получим максимальную сложность О(n).
 Некоторые контейнеры могут из коллизионных элементов формировать деревья, чтобы улучшить сложность поиска элементов до О(ln(n))
 + на качество контейнера так же влияет выбранная хэш функция и в первую очередь то на сколько равномерно она выделяет выходные хеши.


ШАБЛОНЫ ПРОЕКТИРОВАНИЯ

[Q] Как объявить Класс-Singleton ?



ВСЯКАЯ ХУЕРГА

2.	Термин <<Срезка>> означает следующее — 
119. Объясните, что такое «срезка» или «расщепление».
Случай, когда в присваивании участвует два объекта из разных уровней одной иерархии. Одному из объектов присваивается только базовая часть (то, что он знает) от другого объекта.
Или, например, передача по значению в функцию класса наследника.





































































using namespace std;
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

Теоретический минимум для программиста [Кросспост]

http://codeforces.com/blog/entry/1594?locale=ru

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

СТРУКТУРЫ ДАННЫХ !!!

http://itedu.ru/courses/cpp/oop-in-cpp

 !!!!!!!!!!!!!!!!!
http://scrutator.me/post/2014/06/02/objects_memory_layout_p2.aspx

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

ЛЯМБДЫ:
Чтобы решить эту проблему, можно вручную указать возвращаемый тип лямбда-функии, используя синтаксис "-> тип":

 В общем случае его можно записать так:
[captures](arg1, arg2) -> result_type { /* code */ }
arg1, arg2
это аргументы. То, что передается алгоритмом в функтор (лямбду).
result_type
это тип возвращаемого значения. Это может показаться несколько непривычно, так как раньше тип всегда писали перед сущностью (переменной, функцией). Но к этом быстро привыкаешь.

[] - Название функции
() - 

[](double d) -> double { }

void func4(std::vector<double>& v) {
  std::transform(v.begin(), v.end(), v.begin(),
                 [](double d) -> double {
                   if (d < 0.0001) {
                     return 0;
                   }
                   else {
                     return d;
                   }
                 });
} 

Запись "[]" означает, что у функции нет имени, она безымянная, или, говоря по-другому, анонимная. Вместо "[]" можно мысленно подставлять имя "безымяннаяФункция",

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
//////////////////  РАБОТА  ///////////////////////////////

CONNECT
Законектились - Сервер начинает нас слушать RECIEVE
Мы отправили эти данные SEND-ом.
Сервер проситал эти данные.
Прокол определён, сервер распарсил эту структуру.
Определил -> Что это запрос такого-то метода.
=> Выполнить этот метод на сервере.
И вернули ответ. SEND.

Пул Потоков - создали  Поток и внутри него 1 коннект между клиентом и счервером, и очередь сообщений / коннектов.
По одному потоку на 1 подсистему (1-го клиента) на 1 КОННЕКТ 
- в рамках коннекта делаем что нужно открыли соединение, закрыли соединение.
Все потоки ПАРАЛЛЕЛЬНО.

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
//////////////////  ОТ СТАСА ПРО WINDOWS  ///////////////////////////////

Процесс:
- контейнер для потоков
- то чему принадлежит память 
	Даже когда поток выделяет какую-то память, то это на самом деле память расположенное в адресном пространстве процесса, и эта память доступна ВСЕМ потокам

Объект Процесс - в Windows это объект ЯДРА.
Суть в том, что На ЛЮБОМ обекте ЯДРА можно ОЖИДАТЬ. ибо они ВСЕ могут находится в 2-ух состояниях - СИГНАЛЬНОЕ = Занят. НЕСИГНАЛЬНОЕ = Свободен.
Пример: Процесс - автообнолвения. Ждём и жержим ресурсы, пока не обновимся.

Поток, Мьютекс, Евент, Семафор:
	СИГНАЛЬНОЕ = Занят. НЕСИГНАЛЬНОЕ = Свободен.

Все потоки в процессе разделяют одно и тоже адресное пространство.
Память: У каждого процесса его адресное пространство ИЗОЛИРОВАННО
	Адрес виртуальный один и тот же, а по факту в физической памяти они РАЗНЫЕ
	Указатель в одном процессе  - адрес память в 1-ом процессе -> физич. память Ячейка_1
	Указатель в другом процессе - адрес память в 2-ом процессе -> физич. память Ячейка_2
На 1 виртуальный адрес  есть таблица Связи Виртуальныхи Физических адресов. 
На 1 ВИРТУАЛЬНЫЙ адрес в виртуальном адресном пространстве -> ссылка на Страницу физической памяти.

ВСЯ ПАМЯТЬ ПРОЦЕССА - Его виртуальое Адресное простраснство - ИЗОЛИРОВАНО от Адресных пространств всех Других процессов.


В Заголовке Файла: У него есть несколько СЕКЦИЙ - read/write read_only Execute_image ... 
				Смотрится эта секция, и сколько памяти нужно



(???) Можно ли себе выделить ЕЩЁ Больше Виртуальной памяти ?
Ответ: ДА !

WIRTUAL_ALLOC - выделяем предварително ДИАВПАЗОН Виртуальных адресов в адресном пространстве.
				(НА этом этапе только выделились адреса, НО НЕТ соответсвия с Физ.адресами на Диске)
				А потом MEM_COMMIT - Привязываем и работаем с этими адресами полноценно.

ПРОЦЕСС имеет 2 СТЕКА:
- Ядерный - 16 Килобайт
- Юзермодный - Большой ~1Мб (Или задаём параметром в фции CreateThread() )

Когда мы делаем ситемный вызов какого-то API - CreateEvent() = СИСТЕМНЫЙ ВЫЗОВ - происходит переключение в Режим Ядра
А это означает, что ECX, EAX, ESP .... что эти регистры, STACK_POINTER - Мы эту информацию в (?) частности передаём через Стек Ядерный.
Подгрузка регистров произойдёт по очереди
Плюс перейдя в режим Ядра, мы используем только этот стек для вызовов Функции, работает ядро со своими внутренними вызовами 
+нам нужен этот стек чтобы когда раскрутка стека началсь бы ОБРАТНО, у нас был бы обратный вызов в нашу функцию юзермодную, к тому кто вызывал.
call - достаёт из стека адрес возврата и передаёт управление на этот адрес возврата. В какой-то момент ПЕРЕКЛЮЧАЕТСЯ "КОНТЕКСТ"
Для этого есть структура CONTEXT - она загружает регистры изменённые в ядре, на значения регистров Юзермодные.
СТАРЫЙ СТЕН Ядерный с регистрами - зафиксировался.
// вызвали Ядерную функцию = СИСТЕМЕНЫЙ ВЫЗОВ
СЛЕПОК Стека изменённого после системного вызова возвращается обратно
// Продолжаем работать в Юзермодном Режимею.

Юзермодный Стек - страницы памяти - 20 Мегабайт задали, зарезевировалось адресное пространство, но страниц зарезервировалось 2 страницы, а не всё, что мы запросили.
Следовательно: Например, когда мы начали использовать Серьёзную Рекрсию. Что может выявить собой то, что Стек по виртуальным Адресам растёт и мы движемся всё дальше и выше.
НАшей виральыной памяти не поставлена в соответсвии Физическая память. => ОС дополниетльно начинает подгркжать страницы физич. памяти на это Виртуальное Адресное пространство.

В каждом приложении много потоков. И всем запросам передаётся не вся память, ибо они итак не расходуют ВСЁ за РАЗ.


Мьютекс - свободен мьютекс - переводим в СИГНАЛЬНОЕ состояние = НЕ ЗАНЯТ / СИГНАЛЬНОЕ - ЗАНЯТ.

Неэффективность Мьютексов - переключение контекста из Пользоват. в режим Ядра это ценно по врмеени слишком.
Эффектвиность Мьютексов - только то,что его можно использовать в рамках ОДНОГО Процесса.

Ядро это всегда посредник, и в рамках одного процесса, нет смылса задействовать ядро (ибо ЗАТРАТНО), если на то нет необходимости.


События - С Автосбросом / Без Автосброса.
Waitфункция - Евент сделали Ресет - Евента НЕТ. 
10 потоков сделали WaitForSingleObkect() и в ещё одном потоке мы делаем 

AUTORESET_EVENT
- SetEvent() -> просыпается ОДИН поток , которые выполнил WaitForSinlgeObject()
	Просыпается и этот Евент переводится в Несигнальное состояние Автоматически.

MANUALRESET_EVENT
- SetEvent() -> просыпаются ВСЕ потоки , и в  Несигнальное состояние 
	событие надо было бы перевести ЯВНО вызвав ResetEvent().


(?) ПАМЯТЬ WINDOWS: Одному процессу Можно или нельзя писать в память Другого процесса ?

МОЖНО - НО - Чтобы прочитать/записать что-то в другой процесс, нужно вызвать ЯВНО ReadProcessMemory() / WriteProcessMemory()
	передаём в функции ХЭНДЛ процесса, к которому у нас есть право доступа и указатель на участок адресного пространства в которое нам нужно пичать/читать.


(?) Есть HANDLE. Есть объект Ядра - Именованый Event. 
HANDLE = CreateEvent("Event_name"); // HANDLE - Дескриптор этого объекта Ядра. У каждого процесса есть таблица Дескрипторов.

Но получить доступ к этому объекту по ИМЕНИ евента ДРУГОЙ Процесс может открыть его по имени через OpenEvent();
Handle_1 = фактически актуальлен будет только в рамках одного нашего процесса (в которм мы его СОЗДАЛИ)
Handle_2 = фактически актуальлен будет только в рамках одного нашего процесса (в которм мы его ОТКРЫЛИ)

Мы не получили КОПИЮ Объекта. Мы просто получили Handle_2 - ИДЕКС в таблице Дескрипторов в рамках нашего процесса и более ничего, 
и только через дескриптор мы получаем доступ к самосу объекту, работая через системыне вызовы.


(?) Как Получить доступ к Объекту Ядра Из Двух процессов:

1) Можно получить доступ - ОТКРЫТЬ обхект по ИМЕНИ.
2) можно получить доступ - по РОДИТЕЛЬСКОЙ связи.
3) Явный вызов функции	 - DUPLICATE_HANDLE()


(2)
В CreateProcess() - мы имеем такую штуку, как INHERITABLE - параметр - можно ли этот объект НАСЛЕДОВАТЬ, тоесть Процесс может передать Чайлду Те Индексы в твблице дескрипторов,
	у которых при создании самих объектов мы выставили параметр INHERITABLE.

	CreateProcess() // Paren
{
	// .. create some Kernel-Objects
	CreateProcess(INHERITABLE) // Child
	{
		// get all the HANDLE-s of created Inheritable Parent Handles
	}
}


(?) Что за параметр  ALTERABLE

Имеется в  WaitForSingleObjectEX(); EX !!!

ALTERABLE  - Для IPC процедур, она просыпается в тот момент, когда ты ожидаешь на каком-то фале и операция для записи - Когда асинхронная функуия выполнлось. и просыпается, если она выполняется.
	Просыпается поток, которые ждёт на файле на каком-то
	АСИНХРОННЫЙ вызов когда происходит - в тот момент, когда кто-то пишет или читает из Этого файла.

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
СТРАНИЦЫ ПАМЯТИ - ДОСЛУШАТЬ


////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
64-БИТНАЯ СРЕДА

- Всё больше весит за исключением типа chsr = 1 байту всегда и во всех версиях.
- Переадресация Реестра и Файловой системы - SysWOW64
- Для работы в ней, есть специальные версии всех СИСТЕМНЫХ ВЫЗОВОВ / Функций
- Адресное Пространство Выделяемое под процесс - есть указатель, который ограницен определённым числом
  32 битная машина исаользует указатель = 4  Гигабайта = 2^32 байт
  64 битная машина исаользует указатель = 16 Экзобайт = 2^64 байт = 64 ТЕРАБАЙТА (гига, тера, пета, экзо)
//	гигабайт	Гбайт	109	
//	терабайт	Тбайт	1012
//	петабайт	Пбайт	1015
//	эксабайт	Эбайт	1018

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
WINDBG - DMP - Дампы - Анализ Дампов

UserMode отладчик   - OlieDBG 
KernelMode отладчик - WinDBG - можно ммотреть регистры, отадчивать, переменные, можно отлаживать как Юзер Мод программы, так и Кернел мод программы.

Суть - это всё равно что, самому себе делать операцию на мозгу.



////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
СУРРОГАТНЫЙ ПРОЦЕСС в СОМ

http ://www.k-press.ru/cs/2002/1/surrogat/surrogat.asp
https://www.osp.ru/winitpro/2001/03/174740/
https://rsdn.org/article/com/introcom.xml

Суррогатные процессы в COM**

Василий Кораблев
Вступление

Реализация COM - сервера в виде in - process(DLL) сервера дает значительные преимущества, например, лучшую структуризацию проекта, раздельную компиляцию модулей, возможность повторного использования модулей и т.п.Но в использовании внутрипроцессного(in - process) сервера есть одно небольшое, но порой критичное неудобство.Их невозможно создавать и вызывать по сети.Решить эту проблему помогают суррогатные процессы.

Формально, суррогатный процесс – это процесс, который порождается специальным EXE - модулем.Отличительной особенностью суррогатный процесса является то, что в него можно загрузить внутрипроцессный COM - сервер.Что же дает использование суррогатных процессов ?

Суррогатный процесс позволяет превратить внутрипроцессный сервер в полноценное DCOM - приложение, давая возможность вызывать компоненты этого сервера удаленно.

Суррогатные процессы позволяют изолировать компонент от клиента, тем самым исключая влияние на него таких критических ошибок, как проходы по памяти или утечки памяти во внутрипроцессном сервере.Таким образом, запуская компоненты в суррогатном процессе, клиент может защитить себя от возможно сбойного серверного кода при доступе к сервисам, предоставляемым сервером.

Один суррогатный процесс может обслуживать нескольких клиентов одновременно.

DLL внутрипроцессного сервера, запущенная в суррогатном процессе, получает все настройки контекста безопасности, установленные для суррогатного процесса.

Возможность использования так называемых системных суррогатных процессов, а также создания пользовательских суррогатных процессов появилась в Windows NT 4.0 SP2 и Windows 95 (с установленным DCOM).

Системный суррогатный процесс.

Идея, стоящая за суррогатными процессами COM – независимость способа реализации сервера от способа его активации.Суррогатные объекты реализуются в формате DLL, но могут быть активированы как внепроцессные серверы.Чтобы разрешить DLL активироваться внутри суррогатного процесса, нужно всего лишь добавить в реестр несколько дополнительных ключей, которые COM SCM(Service Control Manager COM, читается как «скам») просматривает при обслуживании запроса на активацию сервера.Эти ключи могут быть добавлены авторами клиентского кода для недопущения загрузки объекта с потенциально опасным кодом внутрь своего процесса или для удаленного запуска внутрипроцессных серверов через сеть...

**полностью статью можно прочитать в печатной версии журнала


////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////

(???) PRIVATE наследование Классов:
1) public:	  public	-> public
			  protected -> protected
			  private	-> private

2) protected: public	-> protected
			  protected -> protected
			  private	-> private

3) private:	  так же как и в protected

(???)
Каков размер объекта Foo: 
Каков размер объекта Bar: 

Для 32-битной платформы:
Foo: размер указателя int* = 4 байта 
	 (базовый класс указателя на наследников нет) 
	 + выравнивание кратное 4-ём
Bar: размер указателя char* = 4 байта 
	 + (указатель на класс наследник НЕ БУДЕТ УЧТЁН, ибо наследование было НЕВИРТУАЛЬНОЕ!!!)
	 + выравнивание кратное 4-ём

class Foo
{
public:
    Foo(int j) { i = new int[j]; }
    ~Foo() { delete i; }
private:
    int* i;
};

class Bar : Foo
{
public:
    Bar(int j) { i = new char[j]; }
    ~Bar() { delete i; }
private:
    char* i;
};

void main()
{
    Foo* f = new Foo(100);
    Foo* b = new Bar(200);

	*f = *b;

    delete f;
    delete b;
}

////////////////////////////////////////
Размер базового класса.
Размер класса также включает размер непосредственного родительского класа.

class D
{
 private:
   int i1;      // 4 байта
   int i2;      // 4 байта
};
 
class E : public D
{
 private:
   int k;       // 4 байта
};
В этом случае класс размер класса E будет равен 12 байтам.



////////////////////////////////////////
(???) СТАС - Чтобы число умножить на 2 - Логическая операция побитовая какую операцию можно применить 

http://informatics.mccme.ru/mod/book/view.php?id=5510&chapterid=496


////////////////////////////////////////
(???) Бросать исключения в Конструкторе это НОРМАЛЬНО ?

Так как конструктор полностью не выполнился. Объект полностью не сформировался 
=> утечки памяти, если не отработал конструктор НЕ БУДЕТ. Следовательно можно не вызывать delete.
(*) Если мы до того не понаделали всяких MALLOC-ов внутри конструктора или до него в переменной / конструкторе

(!!!) Относится ко ВСЕМ объектам Ядра:
В случае если семафор используется внутри одного процесса, можно создать его без имени,
передав в качестве lpName значение NIL. Имя семафора не должно совпадать с именем уже существующего
объекта типов event, mutex, waitable timer, job или file-mapping.


(?) Мьютекс - что это и для чего нужен.

Нужен для блокировки доступа стороннего потока к защищаемому от доступа семафором участка кода /
того участка кода как правило, внутри которго происходит обращение к какому-то общему ресурсу, который нужен Множеству потоков

(?) Как происходит "БЛОКИРОВКА" стороннего потока мьютексом ? на вечно ли ? Ставятся ли потоки в очередь ?

(?) Что делать, если поток заблокировал Мьютекс, началось на нём ожидание, и "забыл" выполнить его UNLOCK
или поток вообще УПАЛ (из-за ошибки / необработанного исключ.) / другой поток его прибил TerminateThread-ом ?
Что тогда будет с рассматриваемым (залоченным) Мьютексом ?

Ответ: Так как поток, в котором был создан / залочен Мьютекс перестал существовать, то и мьтекс освободится.
	Поток - объект ядра. И само же ядро следит за тем, чтобы освободить (отпустится) внутри умершего потока все прочие объекты ядра.

Верно ли:
НЕСИГНАЛЬНОЕ СОСТОЯНИЕ Мьютекса - Мьютекс залочен потоком
  СИГНАЛЬНОЕ СОСТОЯНИЕ Мьютекса - Мьютекс освобождён потоком

(?) Если мы Перевели Мьютекс в НЕсигнальное состояния внутри нашего потока, ТО разлочить этот мьютекс, 
тоесть перевести его в Сигнальное состояние извне (то есть из какого-либо другого потока) нельзя, это верно ?

Вопрос: Тоесть Стас, можно ли из другого потока сделать вызов OpenMutex() и выполнить в другом потоке ReleaseMutex ?
ОТВЕТ: НЕЛЬЗЯ - ReleaseMutex выбросит Ошибку, если вызывающий её поток не является Владельцем Мьютекса!!!!!
Поток становится его хозяином до тех пор, пока явно не освободит мьютекс функцией ReleaseMutex, или же не завершится.

Замечение: Запрет запуска второго экземпляра программы - вызываем CreateMutex, смотрим ERROR_ALREADY_EXISTS
если GetLastError вернул нам именно такой флаг, значит программа уже запущена.

5) Lock Free - ???

6) Spin Lock - ???
Спин-локи в ЯДРЕ, спин это бесконечный цикл for() / while() он в очень высокой частостотой запрашивает состояние
разделяемого ресурса, и постоянно запрашивает. Он не засыпает, он использует процессорное время постоянно, не
заплатив никапельки. Их использовать нужно на очень коротких учасках кода - ибо остальные из-за того, что спинлок
будет отбирать на себя всё процессорное время они протсо будут ждать.

7) InterLocked функции - ???

8) Семафор  представляет собой объект, позволяющий синхронизировать работу двух или нескольких процессов или потоков.
Для программиста семафор - это просто счетчик. Если счетчик равен N, это означает, что к ресурсу имеют доступ N процессов. 
Счетчик текущего числа ресурсов, максимальное , сколько потоков/процессов могут получить доступ к ресурсу одновременно.
- когда счетчик текущего числа ресурсов становится больше 0, семафор - в СВОБОДНОМ СОТОЯНИИ
- если этот счетчик равен 0, семафор ЗАНЯТ

// Уменьшаем счетчик семафора. Если к этому моменту уже запущено
// MAX_THREAD_COUNT потоков — счетчик равен 0 и семафор в
// несигнальном состоянии. Ожидаюшие потоки будут заморожены до завершения
// одного из запущенных ранее.
   WaitForSingleObject(Semaphore, INFINITE);
  
// Здесь располагается код, отвечающий за функциональность потока - загрузка файла
 
// Поток завершил работу, увеличиваем счетчик семафора и позволяем
// начать обработку другим потокам.
   ReleaseSemaphore(Semaphore, 1, NIL);

ПРИМЕР: SEMAPHORE - WaitForSingleObject   
   http://www.firststeps.ru/mfc/winapi/r.php?117
   
9) Критическая секция - Крит секция это объект ПОЛЬЗОВАТЕЛЬСКОГО режима. А Мьютекс это объект ЯДРА.
Особенности: Каждая операция с Мьютексом - захват, освобождение - требует переключение конткестного режима из пользовательского режима в контекст ядра.
Тоесть тратися время на сохраненеие регистров потока пользовательского режима, что-то свопается, что-то сохраняется. ЭТО ДОРОГО.
У КРИТ.СЕКЦИИ - всё находится и происходит в рамках пользовательского процесса / режима, тоесть в ядро перехода напрямую не происходит.
ОСОБЕННОСТЬ: - Так как Мьютекс объект ядра, а значит доступен всем процессам, что означает, что шарить мьютекс между процессами можно по имени.
- А Критическая Секция доступна в рамках ТОЛЬКО ОДНОГО Процесса. (Мьютекс тоже можно использовать так, но он более "мобильный")
ОГОВОРКА: ЕСЛИ есть Критическая Секция - множество потоков пытаются в неё войти, а кто-то один её залочил и потоки ждут ДОЛГО.
Так как "ПОД КАПОТОМ" этой Крит.Секции спрятан Мьютекс - Который ЗАХВАТЫВАЕТСЯ тогда, когда уровень критического ожидания входа в Крит.Секцию является Достаточно большим.

(??? СТАС) Кто определяет, на сколько Долгий интервал ожидания и когда будет задействован "подкапотный" Мьютекс

10) Wait-функции WaitForMultipleObjects:
Как вы помните, для синхронизации потоков, обычно требуется временно приостановить выполнение одного из потоков.
- При переводе средствами операционной системы в состояние ожидания, "ожидающий" поток НЕ ЗАНИМАЕТ процессорное время.
- Если флаг bWaitAll равен FALSE, функция вернет управление, как только хотя бы один из объектов подаст сигнал.
А если флаг равен TRUE, это произойдет только тогда, когда сразу все объекты начнут сигнализировать
(как мы увидим, это важнейшее свойство этой функции).


////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
 
https://www.youtube.com/watch?v=7KIIKrN9Pf8 
ЗАДАЧА: Реализовать очередь с приоритетом (последовательно)

Взять массив - долгие операции О(n)
Дерево, Куча или stack_list - О(log(n)) логарифмическое время для выполнения этих операция 
linked_list - связный список (вставка = О(n/2), а удаление О(1))

Вопрос будет таков: Принципиально ли нам иметь время вставки О(log(n)), или мы
можем пожертвовать в пользу более быстрого удаления элемента, чтобы удалять за О(1)
ЕСЛИ НАМ важно часто удалять из очереди приоритетов ?




////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
Ожидание
Нехватка опыта была, 

Аутентификация - клиент-серверная часть.
gina-dll / credential_provider / security provider
На JAVA разрабатывался и дорабатывался сервер.
через библиотеку Tshrift <-> С Джава-Сервером
Контролер домена свой.

Т.е. человек И именно в Windows встраивались механизмы
- аутентификации
- заведения новой пользовательской учётной записи
- вывод различных кастомизироыванных сообщений, разновго вида / ошибка / предупреждение / справка
- защита от перехвата, организовывалась через подппись и шифрование base64

(??? СТАС) Защита от перехвата вводимых логина и пароля
(??? СТАС) Защита от подделки отклика (перехват отправленного до сервера) - подпись 

STL / Boost:

STL: контейнеры, алгоритмы.
Boost: 
- split, is_any_of, toupper, tolower, shared_ptr, noncopyable, property_tree::ptree, RNGs, circular_buffer

3. из boost - а использовал, от того, что чаще всего, к тому, что реже всего :
3.1 некоторые вещи для удобства работы со строками - boost::algorithm::split, boost::is_any_of, boost::toupper
3.2 boost::shared_ptr, boost::noncopyable // shared_ptr -> 11 стандарт.
3.3 boost::property_tree::ptree - xml-ный тамошний парсер
3.4 И использовал тамошние генераторы случайных чисел. Исследовал их свойства в своей дипломной работе в институте.
3.5 И однажды поигрался с циркулярным буфером

MFC - разработка интерфейса. GUI-приложение.

COM / DCOM:
- написание COM-сервера
- взаимодействие с БД через OLEDB


////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
КАСПЕР

Блиц:
1 - 2^8 = 256
2 - диапазон 4ё-х байтового числа = -(2^31)-1 - +(2^31)-1 
(???) СТАС - Чтобы число умножить на 2 - Логическая операция побитовая какую операцию можно применить 
Ответ: ПОБИТОВЫЙ СДВИГ Влево

0000 0011 = 3
0000 0110 = 6

0000 0001 = 2^0 = 1
0000 0010 = 2^1 = 2
0000 0100 = 2^2 = 4
0000 1000 = 2^3 = 8
0001 0000 = 2^4 = 16
0010 0000 = 2^5 = 32
0100 0000 = 2^6 = 64
1000 0000 = 2^7 = 128


Чему равен размер указателя ? - В зависимости от платформы. 4ём байтам какой максиманый размер оперативки можно адресовать ?
К какому верхнему адресу можно обратиться, если иметь доступ ко всему адресному пространству ?
- Указатель в зависимости от платформы - 64битный платформе он 8 байт занимает, на 32 битной 4 байта.

(???) Бросать исключения в Конструкторе это НОРМАЛЬНО ?
Да это НОМРАЛЬНО - и память НЕ утечёр ибо объект ещё не создался, ибо конструктор полностью не отработал

https://habrahabr.ru/post/59349/

class Cnt {
private:
  X *xa;
  X *xb;
public:
  Cnt(int a, int b) {
    cout << "Cnt::Cnt" << endl;
    xa = new X(a);
    xb = new X(b);
  }
  ~Cnt() {
    cout << "Cnt::~Cnt" << endl;
    delete xa;
    delete xb;
  }
};

Казалось бы, ничего не забыли. (Хотя, строго говоря, конечно забыли как минимум конструктор копирования и операцию присвоения, которые бы корректно работали с нашими указателями; ну да ладно.)

Воспользуемся этим классом:

try {
  Cnt c(1, 0);
} catch (...) {
  cout << "error" << endl;
}

И разберёмся, что и когда будет конструиваться и уничтожаться.

Сперва запустится процесс создания объекта Cnt.
В нём будет создан объект *xa
Начнёт создание объекта *xb...
… и тут произойдёт исключение

Всё. Конструктор прекратит свою работу, а деструктор объекта Cnt вызван не будет (и это правильно, объект-то не создался). Итого, что мы имеем? Один объект X, указатель на который (xa) навсегда потерян. В этом месте мы сразу получаем утечку памяти, а возможно, получаем утечку и более ценных ресурсов, соктов, курсоров...

Обратите внимание, что это одна из самых неприятных ситуаций, утечка возникает не всегда, а только при определённых аргументах (первый — не ноль, а второй — ноль). Отыскать такие утечки бывает очень сложно.

Очевидно, такое решение годится только для очень простеньких программок, которые в случае любого исключения просто беспомощно валятся и всё.

Самое простое, надёжное и естественное решение — хранить объект по значению

Пример:

class Cnt {
private:
  X xa;
  X xb;
  
  
//////////////////////////////////////////////////////////////////////////
// Что выведется на экран:


struct A0
{
	A0()
	{
		printf("A0");
	}
	virtual ~A0()
	{
		printf("~A0");
	}
};

struct A
{
	A()
	{
		printf("A");
	}
	virtual ~A()
	{
		printf("~A");
	}
};

struct B : public A
{
	B() 
	{
		printf("B");
		throw 1;
	}
	~B()
	{
		printf("~B");
	}
};


int main()
{
/* // ERROR OPTION:
	try
	{
		A0* a0 = new A0;
		A*  aa = new A;
		A*  ab = new B;
	}
	catch (...)
	{
		return 1;
	}

	// A0 A A B ~A(от B) и ВСЁ !!!
//*/

//* // SOLUTION_1
	try
	{
		std::unique_ptr<A0> a0(new A0());
		std::unique_ptr<A> aa(new A());
		std::unique_ptr<B> ab(new B());
	}
	catch (...)
	{
		return 1;
	}

	// A0 A A B ~A(от B) ~A ~A0
//*/


ЯВНО ЧТО-ТО Стасовское, из того, что разбирали со Стасом.



////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
КАСПЕР
СИНХРОНИЗАЦИЯ

class A;
A* p = new A();
можео ли применять адресную арифметику к подобному указателю ?
МОЖЕМ !

p - не объект ядра


(???) ЧТО ТАКОЕ ОБЪЕКТ ЯДРА ?
http://novostynauki.com/e-ntsiklopediya/lektsii/sistemnoe-programmnoe-obespechenie/yadro-operatsionnoj-sistemy-funktsii-yadra-ob-ekty-yadra-ob-ekty-yadra-na-primere-os-windows-mikroyadro/

Для работы с важными системными ресурсами ОС Windows создает объекты:
- Объекты ядра. Объект – блок памяти, выделенный ядром для своих целей и доступный только ядру.
- Объект ядра содержит имя объекта
- класс защиты объекта 
- счётчик количества пользователей и другую информацию (смещение при открытии файла и т.д.)
- Все объекты имеют описатели (Handle). Большинство объектов обладают свойством наследования.
Таблица Хэндлов.
 

- управление которыми осуществляет менеджер объектов.
(Когда приложение открывает файл, создает поток или семафор, оно получает описатель ( handle ) 
соответствующего объекта (см. рис. 4.1). Например, после выполнения программного оператора)
- Объекты ядра принадлежат ядру, а не процессу. 
- если Ваш процесс вызывает функцию, создающую объект ядра, а затем завершается, объект ядра может быть не разрушен
- если созданный Вами объект ядра используется другим процессом, ядро запретит разрушение объекта до тех пор, пока от него не откажется и тот процесс.
- Ядру известно, сколько процессов использует конкретный объект ядра, посколь ку в каждом объекте есть счетчик числа его пользователей.


ГДЕ ХРАНЯТСЯ и НАХОДЯТСЯ Физически Уже созданные объекты ядра?
Мьютекс создали. Можем ли мы его переложить куда-нибудь ?
Обращение к ним возможно через HANDLE = Уникальный идентификатор.
Ядро возвращает нам 

Мы создали Мьютекс.
Мы работаем с Хэндлами через специальные Wait-функции и т.д.
НЕ забываем ЗАКРЫТЬ ХЭНДЛ

(?) Мьютекс - что это и для чего нужен.

Нужен для блокировки доступа стороннего потока к защищаемому от доступа семафором участка кода /
того участка кода как правило, внутри которго происходит обращение к какому-то общему ресурсу, который нужен Множеству потоков

Мьютексы — это простейшие двоичные семафоры, которые могут находиться в одном из двух состояний — отмеченном или неотмеченном (открыт и закрыт соответственно). Когда какой-либо поток, принадлежащий любому процессу, становится владельцем объекта mutex, последний переводится в неотмеченное состояние. Если задача освобождает мьютекс, его состояние становится отмеченным.
Задача мьютекса — защита объекта от доступа к нему других потоков, отличных от того, который завладел мьютексом. В каждый конкретный момент только один поток может владеть объектом, защищённым мьютексом. Если другому потоку будет нужен доступ к переменной, защищённой мьютексом, то этот поток блокируется до тех пор, пока мьютекс не будет освобождён.

Если другому потоку будет нужен доступ к переменной, защищённой мьютексом, 
то этот поток БЛОКИРУЕТСЯ до тех пор, пока мьютекс не будет освобождён.

(?) Как происходит "БЛОКИРОВКА" стороннего потока мьютексом ? на вечно ли ? Ставятся ли потоки в очередь ?

(?) Что делать, если поток заблокировал Мьютекс, началось на нём ожидание, и "забыл" выполнить его UNLOCK
или поток вообще УПАЛ (из-за ошибки / необработанного исключ.) / другой поток его прибил TerminateThread-ом ?
Что тогда будет с рассматриваемым (залоченным) Мьютексом ?

Ответ: Так как поток, в котором был создан / залочен Мьютекс перестал существовать, то и мьтекс освободится.

Верно СЛЕДУЮЩЕЕ:
•	Свободном состоянии (signaled) - СИГНАЛЬНОЕ СОСТОЯНИЕ Мьютекса - Мьютекс освобождён потоком
•	Занятом (not signaled) - НЕСИГНАЛЬНОЕ СОСТОЯНИЕ Мьютекса - Мьютекс залочен потоком  

(?) Если мы Перевели Мьютекс в НЕсигнального состояния внутри нашего потока, ТО разлочить этот мьютекс, 
тоесть перевести его в Сигнальное состояние извне (то есть из какого-либо другого потока) нельзя, это верно ?


Мьютекс - mutual exclusion - взаимное исключение
Смысл: Не допустить более одного потока к использованию какого-то ресурса (файл/переменная/сокет)


Семафоры – объекты ядра, использующиеся для учета ресурсов. Семафор имеет внутри счетчик.
Этот счетчик снизу ограничен значением 0 (семафор занят) и некоторым верхним значением N.
 В диапазоне 1..N семафор является свободным. Семафоры можно считать обобщением Mutex на несколько ресурсов

 
Семейство Interlocked-функций

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
Interlocked-функции не переводят процесс в режим ожидания, работают в пользовательском режиме, и поэтому обладают довольно большим быстродействием,
так что если необходима синхронизация для доступа к одной переменной, следует использовать именно их.
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

Используются в случае, если разным потокам необходимо изменять одну и ту же переменную. Например, увеличивать счетчик числа операций. 
Код вида var++; компилятором генерируется в что-то вроде

MOV EAX, [var]; 1
INC EAX; 2
MOV [var], EAX; 3


Соответственно, если будут два потока с таким кодом, то нельзя гарантировать, что выполняться строки 1,2,3 первого потока, а потом 1,2,3 второго, 
первая строчка второго потока может выполнится до того, как первый запишет новое значение в переменную, и тогда второй поток изменит старое значение 
и перетрет изменения первого. Использование Interlocked-функций гарантирует, что операция будет выполнена атомарно, и описанная выше проблема отпадает.
 При использование процессоров х86 они выдают по шине аппаратный сигнал, не давая другим процессорам процессорам обратится по тому же адресу памяти 
 на время работы функции.
 
В примере с инкрементом желанного результат можно достичь двумя функциями – InterlockedExchangeAdd(&var, 1), которая возвратит начальное значение var,
 либо InterlockedIncrement(&var), которая возвращает уже инкрементированое значение переменной. Также существуют их 64-разрядные версии 
 — InterlockedIncrement64 и InterlockedExchangeAdd64.
 
Существуют ещё функции, которые реализуют: 
- декремент: LONG InterlockedDecrement(LONG volatile *Addend), возвращает значение декрементированной переменной и 64-битная версия — InterlockedDecrement64
- монопольную замены текущего значения: LONG InterlockedExchange(LONG volatile *Target, LONG Value),
- логические операции: логическое «И» LONG InterlockedAnd(LONG volatile *Destination, LONG Value), логическое «ИЛИ» InterlockedOr и сумму по модулю два InterlockedXor. 
- выполнение сравнения и присвоения как атомарной операции: LONG InterlockedCompareExchange(LONG volatile *Destination, LONG Exchange, LONG Comparand)
 
 
Большая часть синхронизации потоков связана с атомарным доступом (atomic access) — монопольным захватом ресурса обращающимся к нему потоком. Возьмем простой пример

// определяем глобальную переменную lorig g_x = 0;

DWORD WINAPI ThreadFunc1(PVOID pvParam) { 
g_x++; 
return(0); }

DWORD WINAPI ThreadFunc2(PVOID pvParam} { 
g_x++; 
return(0); }

Я объявил глобальную переменную g_n и инициализировал ее нулевым значени ем. Теперь представьте, что я создал два потока: один выполняет ThreadFunc1, дру гой — ThreadFunc2 Код этих функций идентичен: обе увеличивают значение глобаль ной переменной g_x па 1. Поэтому Вы, наверное, подумали: когда оба потока завер шат свою работу, значение g_x будет равно 2. Так ли это? Может быть. При таком коде заранее сказать, каким будет конечное значенис g_x, нельзя. И вот почему. Допустим, компилятор сгенерировал для строки, увеличивающей g_x на 1, следующий код:

MOV EAX, [g_x] , значение из g_x помещается в регистр

INC EAX ; значение регистра увеличивается на 1

MOV [g_x], EAX ; значение из регистра помещается обратно в g_x

Вряд ли оба потока будут выполнять этот код в одно и то же время. Если они бу дут делать это по очереди — сначала один, потом другой, тогда мы получим такую картину:

MOV EAX, [g_x] ; поток 1 в регистр помещается 0

INC EAX ; поток V значение регистра увеличивается на 1

MOV [g_x], EAX , поток 1. значение 1 помещается в g_x

MOV EAX, [g_x] ; поток 2 в регистр помещается 1

INC EAX ; поток 2. значение регистра увеличивается до 2

MOV [g_x], EAX , поток 2. значение 2 помещается в g_x

После выполнения обоих потооков значение g_x будет равно 2 Это просто заме чательно и как раз то, что мы ожидали: взяв переменную с нулевым значением, дваж ды увеличили ее на 1 и получили в результате 2. Прекрасно. Но постойте-ка, ведь Windows — это среда, которая поддерживает многопоточность и вытесняющую мно гозадачность. Значит, процессорное время в любой момент может быть отнято у од ного потока и передано другому. Тогда код, приведенный мной выше, может выпол няться и таким образом:

MOV EAX, [g_x] ; лоток V в регистр помещается 0
INC EAX ; поток 1. значение регистра увеличивается на 1

MOV EAX, [g_x] ; поток 2 в регистр помещается 0 
INC EAX ; поток 2. значение регистра увеличивается на 1 
MOV [g_x], EAX , поток 2. значение 1 помещается в g_x

MOV [g_x], EAX , поток V значение 1 помещается в g_x

А если код будет выполняться именно так, конечное значение g_x окажется рав ным 1, а не 2, как мы думали! Д






 
 
 
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

ПОДХОДЫ СИНХРОНИЗАЦИИ ПОТОКОВ


(?) 4 подхода, для организации Синхронизания потоков:

https://www.youtube.com/watch?v=MU6AeNsZ6MM

0) Критические Секции, Мьютексы, События, Семафоры

1) МОНИТОР - Объект умеющий в Критической Секции "Приотпускать" замок.
Чтобы после наступления какого-то события (await for condition)
возобносить свою работу (конкурируют за замок на общих началах)
ПРИМЕР: поток deque(), ждёт пока в очереди не появится элемент.
Проблема мониторов Lost wake-up - ненаступление условия - лечится установкой timeout-ов.

2) Read-Write Locks - замки устанавливающие уровень доступа к данным.
Возможен захват Reader-замка несколькими потоками.
НЕВОЗМОЖЕН при захваченом Writer-замке.
Пример: SELECT/UPDATE в БД, Доступ к файлу.

3) Reentrant lock - замок, который можно повторно захватить, если он уже принадлежит исполняющемуся потоку.

4) СЕМАФОР - примитив пускающий в "критическую секцию", не более N потоков.
Пример: Распределение ограниченного числа (счтёных) ресурсов - сокетов, ядер, IO-операций, подключений к БД, лицензий. 

(??? СТАС ) как тогда эти потоки умудряются пользоваться общим ресурсом в рамках Семафорного взаимодействия ???


(1) Пример: наш объект заблокирован потоком, но этот поток должен выполнить какую-то операцию, для которой у него не хватает ресурсов.
К примеру_1 - в него есть вложенная блокировка. Он захватил объект_1, и после этого же он хочет захватиь объект_2, но объект_2 для него недосупен.
К примеру_2 - Он захватил объект_1, и он дожидается определённого времени, для того, чтобы исполнить свои действия, и не даёт другим в дуоступ объект_1.
Если он будет просто ждать - это неэффективно

Было бы эффективнее, если бы ПОКА наш поток ожидает освобождения объекта_2, он бы отпустил временно объект_1.

МОНИТОР - отпускает замок над нашим объектом, до наступления какого-то события. Монитору должно быть чётко поисано само событие.
Пример МОНИТОРА в жизни - Поток ждёт Момент, когда надо взять элемент из очереди. В случае, если в очереди Элементов НЕТ, он будет ждать очень долго,
а очеред при этом будет удерживаться. Но мы можем и ДОЛЖНЫ дать другому потоку возможность дать отпущеную очередь, чтобы он положил в неё элемент.
МИНУСЫ МОНИТОРОВ - Проблема Пропущенного события - Монитор пропустил событие, по которому он должен проснуться, потомучто оно наступило, и монитор этого не заметил.
Решение тут - выставлять таймеры на процесс ожидания/СНА, чтобы он Подержал объект, отпустил его ушёл спать, и если событие
которого он ожидает так и не наступило, в течение 30 секунд, он просыпается автоматически и пытается сново получить доступ к объекту.

(2) Если мы открываем файл на ЧТЕНИЕ, то это не мешает открыть и ЧИТАТЬ файл кому-то другому.
У них имеется РАЗНЫЙ УРОВЕНЬ доступа к данным, т.е. замок может 2 Уровня
- Захват объекта на ЧТЕНИЕ - Он НЕ МЕШАЕТ другим потокам так же захватывать это объект на чтение
	НО, тогда он заблокирован на ЗАПИСЬ и изменение такого объекта
- захват объект на ЗАПИСЬ - будет доступен другим потокам и на чтение и на запись.

ПРИМЕР: Запросы в БД SELECT / UPDATE:
	SELECT может быть множественным, и не блокирует табоицу.
	UPDATE - сначала будет исполнено изменение, а потом передатся управление для SELECT-a

(3) Дважды залочить один и тот же замок. Используем чужой код, и в нашей внешней части кода нам
	нужно заблокировать что-то, что находится и заблокированно ещё и внтури.
	
(4) Семафор это организующий примитив, который позволяет некоторому колчиеству потоков ожновреиенно 
	заходить в критическую секцию, но не более чем обозначенному количеству.

	Система БД, которая способна обеспечить по лицензии не более чем 5 подключений.
	Мы делаем ПУЛ подключений, ограничиваем этот Пул Семафором, и использовать то число подключений / потоков,
	солько нужно, согласно ограничению

МЬЮТЕКС:
- Крупнозернистая синхронизация.	

	
АБСТРАКТНЫЕ ЗАДАЧИ МНОГОПОТОЧНОСТИ / СИНХРОНИЗАЦИИ:
- Обедающие философы	
- Дилемма заключённого
- Людоед и шапки 2-ух цветов

	
5) Lock Free - ???

6) InterLocked функции - ???













////////////////////////////////////////////////////////////
BO QUAN

Многопроцессность:	процесс_1 <-> Межпроцессное взаимодействие (каналы) <-> процесс_2
файлы, пайпы, сообщения
Многопоточность:	поток_1 <-> разделяемая память <-> поток_2
 + Многопоточность - поток проще и быстрее запустить
					Чтобы запустить процесс, ОС необходимо выделить под него гораздо больше ресурсов.

						Процессу нужно больше безоаснсоти, чтобы они не наступали друг на друга в ОС (процессы же работают через посредников)
						Потоки же существуя в рамках процессов живут более раздельно друг от друга (встречаясь и работая только с разделяемой памятью/ресурсами)

						Межпотоковое взаимодействие сильно более быстрое, чем
						Межпроцессное

						
						Треды:
						Джойн.
						Можно проверить джоинабл он или нет

////////////////////////////////////////////////////////////
THIS_THREAD

std::this_thread::sleep_for(chrono::second(1));
Всегда позволяет нам узнать НАШ поток, или выполнить именно в ТЕКУЩЕМ потоке что-то
	
////////////////////////////////////////////////////////////
JOIN

В этом примере, thr — это объект, представляющий поток, в котором будет выполняться функция threadFunction().
join() -  блокирует вызывающий поток (в нашем случае — поток main) до тех пор, пока thr 
(а точнее threadFunction()) не выполнит свою работу. Если функция потока возвращает значение 
— оно будет проигнорировано. Однако принять функция может любое количество параметров.
						

////////////////////////////////////////////////////////////
  ПРОБЛЕМЫ СИНХРОНИЗАЦИИ:
- Гонки (Data Race)
- Взаимные блокировки (DeadLock)

////////////////////////////////////////////////////////////
						
Параметры в функцию потока всегда передаются по значению (копия объекта), а не по ссылке.
Чтобы передача происходила по ссылке нужно:

fun(string& msg) {}

main
{
  string s = "1";
  thread t1(fun, ref(s)); 
  thread t1(fun, move(s)); // второй вариант передачи параметра в поток 
}

thread tr2 = tr1; // ERROR will NOT work
tr2 = move(tr1); // перенесём содержимое потока в поток tr2
 
////////////////////////////////////////////////////////////

Гонки ... 

Мы можем разграничить доступ к общему используемому ресурсу в нашем случае это cout::  стандартнй вывод:

////////////////////////////////////////////////////////////
обычный мьютекс:
mutex mu;

МНОЖЕСТВО ПОТОКОВ Обращаются именно к этой функции и к общему для всех обхекту  cout
fun(int i)
{
	mu.lock();
	cout << i;
	mu.umlock();
}

лок - один поток
один поток сделал своё дело
анлок - один поток

и сразу после
лок - второй поток
второй поток сделал своё дело
анлок - второй поток

и так каждый поток гарантированно, не задев объект синхронизации одноврмеенно.
или в нужной, прогеру последовательности

////////////////////////////////////////////////////////////
mutex mu;
lock_guard<mutex> guard(mu);

lock_guard - Реализует RAII:
Автоматически выполнит лок и анлок в рамках заданной единицы трансляции
fun()
{ // начало блока
  lock_guard<mutex> guard(mu); // от момента инициализации, до конца  БЛОКА  функции
} // конец блока

// это работает, только если множество потоков будет вызывать именно эту 

////////////////////////////////////////////////////////////
ПРОБЛЕМА.
любой другой поток, тоесть новая функция которую мы введём и которая будет юзать  cout
и если в ней не будет того же самого мутекса с лок/анлок или мутекс_гуарда с этим мутексом, то Ж 

Тогда просто создаём класс, с мьютексом, лочим функцию которую будем шарить между потоками
с использованием лок-гарда и используем объект класса в потоках по ссылке, и в основном потоке просто инстанс.

Никогда не должен возвращаться сам объект, разделяемый между потоками.


////////////////////////////////////////////////////////////
ДЕДЛОК - взаимная блокировка

mutex m_1
mutex m_2

fun_1()
{
  lock_guard<mutex> locker(m_1);
  lock_guard<mutex> locker2(m_2);
  // защищаемый объект_1 1-ым мьютексом
  // защищаемый объект_2 2-ым мьютексом
}

fun_2()
{
  lock_guard<mutex> locker2(m_2);
  lock_guard<mutex> locker(m_1);
  // защищаемый объект_1 1-ым мьютексом
  // защищаемый объект_2 2-ым мьютексом
}

Синхронно выполняем обе функции:
1 шаг - 1поток в fun - lock_guard<mutex> locker (m_1); залочили m_1
2 шаг - 2поток - lock_guard<mutex> locker2(m_2); залочили m_2
3 шаг - 1поток - lock_guard<mutex> locker2 (m_2); ХОЧЕТ ЗАЛОЧИТЬ m_2, Но он уже залочен в первой строчке второй функции во втором потоке
4 шаг - 2поток - lock_guard<mutex> locker1 (m_1); ХОЧЕТ ЗАЛОЧИТЬ m_1, Но он уже залочен в первой строчке первой функции в  первом потоке
ДЕДЛОК !

РЕШЕНИЕ_0:
Использовать по ОДНОМУ локу анлоку в ОДНОЙ области видмости

fun_1()
{
	part_1
	{
		lock_guard<mutex> locker(m_1);
		// защищаемый объект_1 1-ым мьютексом
	}
	part_2
	{
		lock_guard<mutex> locker2(m_2);
		// защищаемый объект_2 2-ым мьютексом
	}
}

fun_2()
{
  lock_guard<mutex> locker(m_1);
  lock_guard<mutex> locker2(m_2);
  // защищаемый объект_1 1-ым мьютексом
  // защищаемый объект_2 2-ым мьютексом
}

РЕШЕНИЕ_1:
Лочить мьютексы ПОСЛЕДОВАТЕЛЬНО, в каждой из функций в ОДИНАКОВОЙ последоваткельности

fun_1()
{
  lock_guard<mutex> locker(m_1);
  lock_guard<mutex> locker2(m_2);
  // защищаемый объект_1 1-ым мьютексом
  // защищаемый объект_2 2-ым мьютексом
}

fun_2()
{
  lock_guard<mutex> locker(m_1);
  lock_guard<mutex> locker2(m_2);
  // защищаемый объект_1 1-ым мьютексом
  // защищаемый объект_2 2-ым мьютексом
}

РЕШЕНИЕ_2 STL:

fun_1()
{
  std::lock(m_1, m2);
  lock_guard<mutex> locker(m_1, std::adopt_lock);	// adopt_lock - говорит locker-у, что мьютекс m_1 уже залочен, так что достаточно просто 
  lock_guard<mutex> locker2(m_2, std::adopt_lock);	// "получить владение" этим мьютексом, чтобы удалить его как выйдем за пределы области видимости (out of scope), надо просто не забыть освободить мутекс
  // защищаемый объект_1 1-ым мьютексом
  // защищаемый объект_2 2-ым мьютексом
}

fun_2()
{
  lock_guard<mutex> locker(m_1);
  lock_guard<mutex> locker2(m_2);
  // защищаемый объект_1 1-ым мьютексом
  // защищаемый объект_2 2-ым мьютексом
}

НЮАНС:
- стоит избегать вызова функцции определённой пользователем на том промежутке кода, где вы используете lock_guard<mutex>
fun()
{
	lock_guard<mutex> locker(m);
	user_function();
}

- задать приоритетность мьютексам.
Чтобы пока поток залочил низкоуровневый мьютекс, он не может залочить Высокоуровневый мьютекс

- С защитой объектов от захвата нужно поступать очень аккуратно и с ВЫСОКОЙ ГРАНУЛЯРНОСТЬЮ
"Хороший" Лок - лочит маленький участок кода. Однако это может породить дедлоки
"Плохой" - большие участки кода от исполнения. Однако треды могут долго ждать освобождения ресурсов
"Золотая середина" - которой нет ...


////////////////////////////////////////////////////////////

https://habrahabr.ru/post/182610/

- lock_guard: когда объект создан, он пытается получить мьютекс (вызывая lock()), 
	а когда объект уничтожен, он автоматически освобождает мьютекс (вызывая unlock())

- unique_lock: в отличие от lock_guard, также поддерживает отложенную блокировку,
	временную блокировку, рекурсивную блокировку и использование условных переменных	


Конструкторы классов «оберток» могут принимать параметр, определяющий политику блокировки:
- defer_lock типа defer_lock_t: не получать мьютекс
- try_to_lock типа try_to_lock_t: попытаться получить мьютекс без блокировки
- adopt_lock типа adopt_lock_t: предполагается, что у вызывающего потока уже есть мьютекс

Для решения этой проблемы можно использовать 
- std::lock, который гарантирует блокировку безопасным (с точки зрения взаимоблокировки) способом:

     std::lock(c1._lock, c2._lock); 
     c1.remove(value);
     c2.add(value);
     c1._lock.unlock();
     c2._lock.unlock();

- lock: блокирует мьютекс, используя алгоритм избегания deadlock'ов (используя lock(), try_lock() и unlock())
- try_lock: пытается блокировать мьютексы в порядке, в котором они были указаны	 

////////////////////////////////////////////////////////////
ЮНИКЛОК - взаимная блокировка

1) позволяет сделать отложенную РАЗблокировку:
void shared_print()
{
	unique_lock<mutex> locker(m);
	// то, что требует синхронизации через мьютекс m
	locker.unlock(); // позволяет сделать это раньше, чем конец области видимости
	// от этого момента нам залоченный мьютекс не нужен
}

2.1) Можно создать объект locker, но при этом НЕ ЗАЛОЧИТЬ мьютекс
     Реализует механизм "ОТЛОЖЕННАЯ БЛОКИРОВКА"
2.2) МНОЖЕСТВО РАЗ делать ЛОК / АЛОК в рамках одной области видимости / одного блока { }
	 lock_guard так не умеет
2.3) Может  std::move() - быть ПЕРЕМЕЩЁН - функцией ПЕРЕМЕЩЕНИЯ, и при перемещении ВЛАДЕНИЕ Мьютексом переходит от одного unique_lock_1 к unique_lock_2
	 std::unique_lock<mutex> locker_1(mutex);
	 ...
	 std::unique_lock<mutex> locker_2 = std::move(locker_1);
	 
НЮАНС - Он БОЛЕЕ ТЯЖЁЛЫЙ, чем lock_guard (который более ЛЕГКОВЕСНЫЙ) 
	 
void shared_print()
{
	unique_lock<mutex> locker(m, std::defer_lock); // m - будет не залочен при создании locker. его нужно будет залочить вручную
	//сначала делаем то, что не требует синхронизации
	locker.lock(); // 1-ЫЙ РАЗ
	// то, что требует синхронизации через мьютекс m
	locker.unlock(); // позволяет сделать это раньше, чем конец области видимости

	// от этого момента нам залоченный мьютекс не нужен
	locker.lock(); // 2-ОЙ РАЗ
	// то, что требует ПОВТОРНОЙ синхронизации через мьютекс m
	locker.unlock();	
}

////////////////////////////////////////////////////////////
ЛЕНИВАЯ ИНИЦИАЛИЗАЦИЯ - lazy initialisation

class LogFile
{
	std::mutex m_mtx;
	std::ofstream m_f;
public:
	LogFile()
	{
		m_f.open("file.txt");
	}
	
	void shared_print(std::string _s)
	{
		unique_lock<mutex> locker(m_mtx);
		m_f << "PRINT: " << _s << std::endl;
	}
};

Тут в конструкторе мы открываем файл.
НО Что если в коде, разраб, пользующийся
нашим классом никогда не вызовет shared_print
И зачем нам тогда открытый файл вприцнципе ?

Для этого Инициализируем и откроем Файл ТОЛЬКО
внутри самой функци, единожды, кода она вызовется

class LogFile
{
	std::mutex m_mtx;
	std::ofstream m_f;
public:
	LogFile() { }
	
	void shared_print(std::string _s)
	{
		if(!m_f.is_open())			// Lazy initialisation
		{ m_f.open("file.txt"); } 	// ИДЕОМА - инициализация до первого использования

		unique_lock<mutex> locker(m_mtx);
		m_f << "PRINT: " << _s << std::endl;
	}
};

////////////////////////////////////////////////////////////
ПОТОКО  НЕ  БЕЗОПАСНЫЙ КОД

class LogFile
{
	std::mutex m_mtx_1;
	std::mutex m_mtx_2;
	std::ofstream m_f;
public:
	LogFile() { }
	
	void shared_print(std::string _s)
	{
		if(!f.is_open()) {						// cтр.1
		  unique_lock<mutex> locker_2(m_mtx_2);	// cтр.2
		  m_f.open("file.txt");					// cтр.3
		}
												// cтр.4
		unique_lock<mutex> locker_1(m_mtx_1);
		m_f << "PRINT: " << _s << std::endl;
	}
};

НЕБЕЗОПАСНОСТЬ: Имеем 2 потока (В рамках 1 шага 2 потока могут выполнить параллельно по одной операции в рамках одной строки):
-- шаг 1
поток 1 (стр.1): зашёл, увидел, что файл НЕ открыт, заходит в функ.
-- шаг 2
поток 1 (стр.2): лочит мьютекс, собирается перейти к строчке 3 и открыть файл
поток 2 (стр.1): зашёл, увидел, что файл ЕЩЁ НЕ открыт (поток 1 в это же время только залочил мьютекс, но ещё не перешёл на строчку 3)
-- шаг 3
поток 1 (стр.3): открывает файл		-- ФАЙЛ ОТКРЫТ (в потоке 1) --
поток 2 (стр.2): лочит мьютекс
-- шаг 4
поток 1 (стр.3): выходит из функции
поток 2 (стр.2): открывает файл		-- ФАЙЛ ОТКРЫТ (в потоке 2) --
--- РЕЗУЛЬТАТ: Файл одновременно открыт в Двух потоках.... Плохо просинхронизировали ....


// РЕШЕНИЕ  НЕправильное:

class LogFile
{
	std::mutex m_mtx_1;
	std::mutex m_mtx_2;
	std::ofstream m_f;
public:
	LogFile() { }
	
	void shared_print(std::string _s)
	{
		{
	 	  unique_lock<mutex> locker_2(m_mtx_2);	// cтр.1
		  if(!f.is_open()) 						// cтр.2
		  { m_f.open("file.txt"); }				// cтр.3
		}
												// cтр.4
		unique_lock<mutex> locker_1(m_mtx_1);
		m_f << "PRINT: " << _s << std::endl;
	}
};
	
ТАКОЕ решение плохое, ибо оно требует захвата мутекса КАЖДЫЙ РАЗ,
в каком-то смысле теряется как таковая "многопоточность" +нагрузка процессора и потеря процессорного времени
ПРИ том, что файл нам вообще говоря нужно открыть ЕДИНОЖДЫ


////////////////////////////////////////////////////////////
// РЕШЕНИЕ  ПРАВИЛЬНОЕ:

- ЕСЛИ нужно сделать что-то ЕДИНОЖДЫ в одном из потоков

ONCE_FLAG - позволяет чему-то выполниться в одном из потоков ЕДИНОЖДЫ

class LogFile
{
	std::mutex m_mtx_1;
	std::once_flag flag;
	std::ofstream m_f;
public:
	LogFile() { }
	
	void shared_print(std::string _s)
	{
		call_once(_flag, [&]() { m_f.open("log.txt"); }); // Файл будет открыть ЕДИНОЖДЫ Одним из потоков
		unique_lock<mutex> locker_1(m_mtx_1);
		m_f << "PRINT: " << _s << std::endl;
	}
};



////////////////////////////////////////////////////////////
// Condition Variable - УСЛОВНЫЕ ПЕРЕМЕННЫЕ

std::deque<int> q; // доступ к очереди - ГОНКИ потоков! (кто быстрее запихнёт/удалит)
std::mutex mu;

void fun_1() // producer
{
  int count =10;
  while(count > 0)
  {
    unique_lock<mutex> locker(mu);
	q.push_front(count);
	locker.unlock();
	sleep_for(chrono::seconds(1));
	count--;
  }
}

void fun_2() // consumer
{
  int data = 0;
  while(data != 1)
  {
    unique_lock<mutex> locker(mu);
	if(! q.empty())
	{
	  data = q.back();
	  q.pop_back();
	  locker.unlock();					UNLOCK_1
	  cout << "DATA:" << data << endl;
	}
	else
	{
	  locker.unlock();					UNLOCK_2
	}
  }
}

int main()
{
  thread t_1(fun_1);
  thread t_2(fun_2);
  t_1.join();
  t_2.join();
  // ожидаем в основном потоке завершение двух созданных потоков
  return 1;
}

FUN_2  исполняет BUSY WAITING - Ожидание ВХОЛОСТУЮ или - ПРОСТОЙ - многократный непрерывный заход в цикл while() loop
Происходит МНОГОКРЫТНЫЙ выхов РАЗБЛОКИРОВКИ в fun_2, так как разблокировка за пределами цикла

// РЕШЕНИЕ Плохое:

void fun_2() // consumer
{
...
	else
	{
	  std::this_thread::sleep_for(chrono::second(1));
	  locker.unlock();
	}
}

НЮАНС:  Да мы СОКРАТИМ число заходов в Цикл на единицу времени
	НО: Как как понять СКОЛЬКО нужно спать потоку ?
		1. если выставим слишком мало  - поток будет входить в цикл слишком часто и Ожидать вхолостую
		2. если выставим слишком много - Мы можем таки НЕ получить данные во время

////////////////////////////////////////
// РЕШЕНИЕ ПРАВИЛЬНОЕ:

std::deque<int> q; // доступ к очереди - ГОНКИ потоков! (кто быстрее запихнёт/удалит)
std::mutex mu;
std::condition_variable cond;

void fun_1() // producer
{
  int count =10;
  while(count > 0)
  {
    unique_lock<mutex> locker(mu);
	q.push_front(count);
	locker.unlock();
	cond.notify_one(); // Оповестить один ждущий поток, если есть таковой, с данной Условной переменой cond
	//cond.notify_all(); // Разбудит ВСЕ потоки, что ждут на данной условной переменной.
	sleep_for(chrono::seconds(1));
	count--;
  }
}

void fun_2() // consumer
{
  int data = 0;
  while(data != 1)
  {
    unique_lock<mutex> locker(mu);
	cond.wait(locker);	// Дойдёт до сюда и будет ждать, пока у данной переменной в другом потоке не будет выствлен ОПОВЕЩАЮЩИЙ ФЛАГ через метод notify_one
						// и ждать она будет того, чтобы залочить соответсвенно мьютекс
	  data = q.back();
	  q.pop_back();
	  locker.unlock();
	  cout << "DATA:" << data << endl;
  }
}

int main()
{
  thread t_1(fun_1);
  thread t_2(fun_2);
  t_1.join();
  t_2.join();
  // ожидаем в основном потоке завершение двух созданных потоков
  return 1;
}

ВЫВОД: С помощью Условных переменных мы можем Управлять последовательностью остановки и возобновления потоков,
и реализовывать ОТЛОЖЕННЫЙ Запуск и Возобновление потока, определяемый нами.

НЮАНС: Почему cond.wait(locker);  wait-функции нужен locker в качесве параметра
		на предыдущем шаге мьютекс захвачивается потоком_2
		и поток не должен ожидать "засыпать" при удержании мьютекса, ибо
		зачем задерживать мьютекс, когда ты собираешся заснуть (ведь если заснёшь .... то когда и как освободишь его ... не понятно)
		На время Засыпания потока нам не хочется блокать всех остальных, кто может поспользоваться мьютексом
		ИТАК перед wait-функцией мы посылаем поток_2 в СПЯЧКУ и это сделает НЕЯВНЫЙ UNLOCK locker-a, который передаётся в wait-функцию
		и только после этого поток_2 отправится в СПЯЧКУ.
		ААА КАК ТОЛЬКО поток_2 будет РАЗБУЖЕН через вызов функции notify_one(), это ЗАЛОЧИТ locker обратно, и только после этого
		в рамках потока_1 мы сможем МНОПОЛЬНО владеть ресурсом  q  , и после чего дойдя до locker.unlock(); мы и разлочим залоченый locker.

	Так как в данной ситуации надо много много раз вызывать lock() / unlock(), то тут нам ЯВНО нужен именно unique_lock,
	в комбинации с condition_variable

////////////////////////////////////////////////////////////
// Condition Variable
// ФОРСМАЖОРНОЕ_ПРОСЫПАНИЕ (САМОПРОСЫПАНИЕ) из режима wait-функции - SPURIOUS WAKE.

Суть: Запустили wait(), поток заснул, есть 2 варианта ПРОСНУТЬСЯ:
	(1) condition_variable вызовет  notify_one()
	(2) поток может проснуться САМОСОТОЯТЕЛЬНО (spurious wake)

	(2) В случае  spurious wake  может возникнуть ситуация, КОГДА поток проснулся не по нашему желанию / незапланированно / ФОРСМАЖОРНОЕ_ПРОСЫПАНИЕ ,
		в этом случае, мы хотим избежать неопределённого поведения или ошибки, или проблем с логикой, которую вызвало ПРОСЫПАНИЕ потока
		ЕСЛИ мы не хотим, чтобы поток проснулся и продолжил своё выполнение, мы можем отправить его ОБРАТНО В СОН (СПАТЬ - ибо нефиг было просыпаться)

		Чтобы избежать неконтролируемого ПРОСЫПАНИЯ ПОТОКА "Не при тех условиях и не в то время", МОЖНО 
		В качестве дополнительной Функции-предиката, функция, проверяющая УВСЛОВИЕ, передавать таковую в качестве ВТОРОГО ПАРАМЕТРА в ф-цию wait(mutex, PREDICATE_FUNC())
		
		cond.wait(locker, [](){ return !q.empty();} );
		
		Лямбда-функция [](){ return !q.empty();} - будет возвращать успех, если  q  НЕпусто
		Следовательно: Если поток_2 проснулся, то ТЕПЕРЬ о посмотрит на результат выполнения функции-предиката.
		predicate_fun() == FALSE - и поток уйдёт СПАТЬ дальше
		predicate_fun() == TRUE  - и поток ПРОСНЁТСЯ и продолжит исполнение кода
		
////////////////////////////////////////////////////////////
// Condition Variable
// МНОГО потоков ожидающих на ОДНОЙ УСЛОВНОЙ Переменной

  cond.notify_one(); - Разбудит ТОЛЬКО ОДИН единственный поток.
  
  cond.notify_all(); - Разбудит ВСЕ потоки, что ждут на данной условной переменной.
		

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
// Furure  +  Promise  +  async()

#include <future>

using namespace std;

void factoreal(int N)
{
	int res = 1;
	for (int i = N; i > 1; i--)
	{
		res *= i;
	}

	cout << "Result is: " << res << endl
}

int main()
{
	std::thread t1(factoreal, 4);

	t1.join();
	return 0;
		
}



















// Задачка от Яндекса:
#if 0 // [F ТОЛЬКО ПОЧЕМУ УТЕЧКА ПАМЯТИ] ///////////////////////////////////////////////////
class Foo
{
public:
    Foo(int j) { i = new int[j]; }
    ~Foo() { delete i; }
private:
    int* i;
};

class Bar : Foo
{
public:
    Bar(int j) { i = new char[j]; }
    ~Bar() { delete i; }
private:
    char* i;
};

void main()
{
    Foo* f = new Foo(100);
    Foo* b = new Bar(200);

	*f = *b;

    delete f;
    delete b;
}


// [Q] Перечислите все проблемы, которые вы видите в данном коде :

///////// пример ответа
// 0) если всё оставить как есть, ТО на строчке, где  "delete b;"  произоидёт "core dumped"
// 1) У Foo нет конструктора по умолчанию. А в конструкторе Bar базовый класс Foo никак не инициализируется существующим конструктором Foo::Foo(int j)
//    Конструктора по умолчанию уже нет, и в классе Bar при наследовании от Foo в конструкторе Bar надо вызвать конструктор Foo с параметром. Этого в приведенном коде не делается.
// 2) В строчке Foo* b = new Bar(200) будет ошибка из - за того, что наследование по умолчанию "private".Нужно поставить ключевое слово public перед Foo в строчке class Bar : Foo => class Bar : public Foo.
// 3) Массивы нужно удалять оператором delete[].
// 4) Деструктор в Foo нужно сделать виртуальным, иначе в данном случае не вызывается Bar::~Bar()
// 5) char* i; поле i определено в классе Foo.С точки зрения компилятора всё правильно, т.к. char* i и int* i находятся в разных пространствах имен. Но это может запутать программиста
// 6) В конструкторах, желательно, сделать отдельную инициализацию, если j не положительное или нулевое.
// 7) Строка *f = *b; -утечка памяти.
//    (7) происходит следующим образом: 
// 8) Должен быть описан оператор присваивания +необходимо поле хранящее количество элементов, чтобы при копировании знать, какой длины массив
//	  Строго говоря: Видишь указатель в классе - опиши ТРИ - 1. Оператор присваивания, 2. Коснтруктор копииЮ 3. Деструктор

// (1) 
//Bar(int j) :Foo(j + 100500)
//{
//	i = new char[j];
//}





class Bar;

class Foo
{
public:
	Foo()
	{ i = 0;};

	Foo(int j)
	{
		i = new int[j];
		strcpy((char*)i, (const char *)"foo\n");
	}

	~Foo()
	{
		if (i) delete (char*)i;
		i = 0;
	}


	void print()
	{ printf("%d %d %s", (int)this, (int)i, (char*)i);}

	//Foo &operator=(const Foo & val)
	Foo &operator=(const Foo & val)
	{
		if (&val != this)
		{ strcpy((char*)i, (const char *)val.i); }
		return *this;
	}
	void set_pointer(void * p)
	{ i = p; }
private:
	void * i;
};

//------------------------

class Bar : public Foo
{
public:
	Bar(int j)
	{
		char * p = new char[j];
		strcpy((char*)p, (const char *)"fbar\n");
		set_pointer(p);
	}

};
//------------------------

int main()
{
	Foo* f = new Foo(5);
	Foo* b = new Bar(10);

	*f = *b;

	delete f;
	delete b;
	return 0;
}

























































75

Hallo
Mein Name ist Paul Winterberg
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




