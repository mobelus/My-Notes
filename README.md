# My-Notes
My first Project on Github



О работе:
Пришёл работать тестировщиком ПО в компанию Айсберг.
В компании велась разработка АРМа занимающегося 3-мя вещами - 
1) Управление наливом нефтепродуктов по цистернам на нефтебазах.
2) Отправка отчётности, документации и выписки квитанций по налитым / отпущенным продуктам
3) Система мониторинга утечек на конкретных учатсках трубы
4) Система смешивания нефтепродуктов, для получения нефтепродуктов нужной консестенции и т.д.
Фактически являлся самописной СКАДА системой, но более гибкой ибо был написан на Си++

  |- система Автообновления (Служба Windows)
  V
  АРМ --> Система печати чеков
  |
  |--> управления наливом
  |--> Мониторинг утечек и сигналов на схеме трубопровода
  |--> управления наливом

Автообновление - (Служба Windows)
 UPDATER.EXE - работала автономно в ОС, и периодически просматривала есть ли на сервере обновлений новая сборка и если появлялась более новая
 то скачивался ZIPархив, разархивировался, выполнялся .BAT-файл, который заменял всё на новую версию из архива, помещал все файлы по по нужным путям с заменой старых
  
0) ПРОВЕРКА СТРЕССОУСТОЙЧИВОСТИ ПРОГРАММЫ
Причина: Надо было максимально проверять на то как может поломаться программа (Вылететь исключение, закрыться, непредвиденно зависнуть и т.д.).
ИБО, если она поломается во время технологического процесса, это могло привести к АВАРИИ на объекте
от пролива нефтепродукта ЛИТРАМИ, до ПОЖАРА на объекте и т.д.  
  
1) управление наливом тестировалось на тестовых стендах.
Стенд представлял из себя электрическую схему, полный аналог того, что будет на нефтебазе, с нужным числом триггеров, и подводок.
Присуствовал счётчик, тоесть надо было проверять правильно ли на железо отправляются все значения и цифры.
Успешно ли отрабатывают НАливы / ДОливы / ПРОливы / НЕДОливы.
Успешно ли отрабатывает налив одновременный на нескольких колонках (аналог бензоклонки) с одной, двух трёх и более.
Успешно лои отрабатывает отрпавка всех команд от АРМа от программной части до железа, успешно ли железо завершает работу и т.д.

Вёлся Анализ ЛОГОВ, в которые фиксировались действия пользхователей, чтобы полнять 
на каком этапе упала программа или после каких дествтий произошла та или иная ошибка, нестандартное поведение.

Вёлся Анализ логов сервиса/службы автообновления. Служба тоже иногда умирала, валилась, тупила, перезапускать службу приходилось, но редко.


2) После налива, кассир на нефтебазе должен был распечатывать аналог "Чека" сколько отлил, нефтеперевозчик какой он компании,
данные водителя, и ещё какое-то число данных о водителе, ТС и числе и цене налитого нефтепродукта.
Тестирование того на сколько правильно заполняются эти "Чеки". Работа со специалистами, по БД, которые вели эту часть отдельно,
мне передавали только готовые селекты, и прочие данные, если лони мне были нужны.
АРМ отправлял данные по наливу в систему отчётности. Система отчётности была написана на Си Шарп, была отдельным софтом. Частично и её приходилось тестировать.

Надо было Сверять перепроверять успешно ли данные доходят до Чека, верно ли распечатывается чек, появляются ли на чеке именно те данные, что мы задали в программе отчётности и т.д.
Проверять в базе данных данные с чеков, или данные по компаниям, данные по водителям, писать какие-то селекты, чтобы их отбирать или находить и т.д.
Пример запросов в Базу: какие из водителей компании BP налили больше 5000 литров 28-го августа 2015-го года, и Т.Д.

3) Система мониторигна утечек тестировалась в основном так же на железе.
Тестовые стенды строились отдельно инженерами, устанавливались датчики давления, ЭМУЛИРОВАЛИСЬ утечки, необходимо было следить за работой ПО.
Тестирловалось сколько программа может работать без перезапуска, потому как пользователям надо было круглосуточно наблюдать за программой.

4) Система смешения нефтепродуктов - выбираем те нефтепродукты которые хотим смешать с чем-то или подмешать в них что-то, чтобы 
 Многовариабельность на выходе. Выгрузка результата смешения в XML-файл
 Анализ верно ли сформировался XML-файл, после всех шагов в программе.
 Сверка какие продукты с камими смешивать можно / какие нельзя.



Тестировал при помощи:
1) Ручное тестировнаие:
-- Нового функционала, касающегося изменения/доработки интерфейса
-- Нового функционала, касающегося изменения логики работы программы, без изменения интерфейсаса
-- Тест системы автообновления программы
-- Тест на отправку отчётности по результатам налива продуктов
-- взаимодействие с сервисом отчётности [УТОЧНИТЬ НАЗВАНИЕ У ИЛЬИ]

2) тестирование отрабатываемыми сценариями, описаныыми в батниках
3) начали вводить автотестирование при помощи программы BadBoy.
Хотели в качестве альтернативы ещё использовать TestCompleter,
но надо было работать, и это дело откладывалось и откладывалось

4) Принципы автотестирования я понимаю, на примере программы BadBoy, тоесть как там в ней можно описать последовательность действий,
вызовов программы, эмулировать нажатия кнопок, эмулимровать ввод данных с клавиатуры, и любые другие действия пользователя с программой.
В этом и заключается суть автотестов - то, что поддаётся описанию и чёткой последоватльности действий, которую как ТЕСТ-КЕЙС хорошо можно
описать фреймворку / программе-автотестирования (фреймворк - другое название для программы или библиотеки), на её языке, это и есть автотест.

Пример автотеста, написанного для TestCompleter:

 Мы хотим протестировать отрабатывает ли процесс налива в нашей программе.
 Нам известно, что программа должна работать так: Запусукаем нашу программу.
 Открывается АРМ. В АРМе есть кнопка "Начать налив" - мы на неё нажимаем,
 после чего налив пошёл, и он должен закочиться через 5 секунд.
 Во время налива у кнопки меняется название на "Налив начался"
 как только налив завершился, название кнопки меняется на "Налив завершён".
 
TestForNalivButton()
{
 var element;					// ввели переменную, чтобы сохранить в неё элемент интерфеса, который нам будет нужен в процессе тестов
 ExecuteProgramm(Aisberg.exe);	// запустили программу
 FindElementOnForm(var, "TButton", "Начать налив");
 ClickButton(element);
 Sleep(1000); // пауза на 1 секунду, чтобы дать системе запустить налив и поменять название кнопки
 CheckButtonText(element, "Налив начался");
 Sleep(5000); // пауза на 5 секунд
 CheckButtonText(element, "Налив завершён");
}

Если последовательность команд внутри теста TestForNalivButton() застопорится
или отработает с отрицательным результатом, тест считается не пройденным.
Шаг на котором произошла ошибка внутри теста, фиксируется внутри проги TestCompleter.
Со всеми командами TestCompleter можно ознакомиться на его сайте с хоршим описанием.
Можно так же писать и свои команды внутри TestCompleter на C++, Java, и других языках.




Любому тестировщику нужно 3 вещи:
- Ознакомиться с системой - в последствии знать систему и как она работает сейчас
- как должен работать какой-то новый функционал, чтобы понимать как его тестировать - СТАНДАРТНЫЕ СЦЕНАРИИ - то как ДОЛЖНО работать
- задаваться постоянно вопросом "ЧТО ЕСЛИ" и тестировать НЕСТАНДАРТНЫЕ СЦЕНАРИИ - то как МОЖЕТ работать, но не факт, что так ДОЛЖНО или вообще НЕ ДОЛЖНО



1. Ручное тестирование 
2. Автотесты

Для обоих важно ОДНО:

Важно соблюдать методологию тестирования
Чтобы ПО согласно Жизненниу циклу разработки ПО шло строго по 5-ти пунктам:

1. Анализ требований
2. Проектирование
3. Разработка
4. Тестирование
5. Эксплуатация, Тех подержка

ПРИЧИНА И ПРИМЕР: в жизни может произойти так: из 3-го этапа сразу в 5-тый.
Программст закодил фичу. Подумал, что закодил всё без ошибок.
Отдал заказчику, не стал изза столь мелкой фичи беспокоить тестировщика.
Заказчик помстпавил прогу с Фичей, фича уронила ВСЁ приложение.


1. тестирование Фронт Энда
  Как правило тестирование верно реализованной логики согласно:
  БТ - Бизрнестребование
  ФТ - Функциональным требованиям
  ТЗ / ЧТЗ  - (Частное) Техгническое Задание
 Важно соблюдать методологию тестирования
 Чтобы ПО согласно Жизненниу циклу разработки ПО шло строго по 5-ти пунктам:
  
2. тестирование Бэкэнда
 Через .bat-файлы. Скриптовые тесты. Тесты при помощи спец. программ.
 Бэк энд это как правило СЕРВЕР. Для сервера проводится обычно НАГРУЗОЧНОЕ тестирование.
 Сколько сотен / тысяч / миллионов запросов в секунду и с каокй интенсивностью сервес способен держать запросов. Как быстро он под нагрузкой способен работать и не УПАСТЬ.

 

contiues Integration

автосбока

Код закодили.
Его выкачивают через гит из ветки.
его компилят компилятором, или несколькими компиляторами
потом запускаются юнит тесты (юнит тесты пишутся разработчиками)









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

