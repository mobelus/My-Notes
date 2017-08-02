
# CURRENT WORK:

https://trello.com/b/Fq1hkaXR/blackbird-web



# DEUTSCHLAND WORK:

Lead Software Engineer | Bildverarbeitung im Automotive-Umfeld | bis 80.000€ | Inhouse (m/w)

http://stellenanzeige.monster.de/lead-software-engineer-bildverarbeitung-im-automotive-umfeld-bis-80-000%E2%82%AC-inhouse-m-w-job-stuttgart-baden-w%C3%BCrttemberg-deutschland-175698424.aspx?mescoid=1100011001001&jobPosition=2


Leiter Softwareentwicklung C++ | Verantwortung für 15 Mitarbeiter | bis 100.000 € (m/w)

http://stellenanzeige.monster.de/leiter-softwareentwicklung-c-verantwortung-f%C3%BCr-15-mitarbeiter-bis-100-000-%E2%82%AC-m-w-job-gro%C3%9Fraum-stuttgart-baden-w%C3%BCrttemberg-deutschland-185780809.aspx?mescoid=1100011001001&jobPosition=2


Softwareentwickler C#/WPF und/oder C++/MFC (m/w)

http://stellenanzeige.monster.de/softwareentwickler-c-wpf-und-oder-c-mfc-m-w-job-aachen-nordrhein-westfalen-deutschland-186267323.aspx?mescoid=1500127001001&jobPosition=2

Softwareentwickler C++ / QT / QML | Bedienoberfläche / GUI / HMI für Medizintechnik | Inhouse (m/w)

http://stellenanzeige.monster.de/softwareentwickler-c-qt-qml-bedienoberfl%C3%A4che-gui-hmi-f%C3%BCr-medizintechnik-inhouse-m-w-job-frankfurt-am-main-hessen-deutschland-181337266.aspx?mescoid=1500127001001&jobPosition=2

Softwarearchitekt und Softwareentwickler C++ | Labortechnik | bis 90T € | Inhouse (m/w)

http://stellenanzeige.monster.de/softwarearchitekt-und-softwareentwickler-c-labortechnik-bis-90t-%E2%82%AC-inhouse-m-w-job-m%C3%BCnchen-nord-bayern-deutschland-186544018.aspx?mescoid=1500127001001&jobPosition=2

Senior C++ Architekt/ Technische Leitung (m/w) Standort Bremen

http://stellenanzeige.monster.de/senior-c-architekt-technische-leitung-m-w-standort-bremen-job-bremen-bremen-deutschland-185000187.aspx?mescoid=9901111000004&jobPosition=2

Softwareentwickler C++ | Software unter MS Visual Studio entwickeln | bis zu 80.000 € (m/w)

http://stellenanzeige.monster.de/softwareentwickler-c-software-unter-ms-visual-studio-entwickeln-bis-zu-80-000-%E2%82%AC-m-w-job-m%C3%BCnchen-hamburg-stuttgart-deutschland-185780236.aspx?mescoid=1500127001001&jobPosition=2

Softwareentwickler C++ / QT / QML | Bedienoberfläche / GUI / HMI für Medizintechnik | Inhouse (m/w)

http://stellenanzeige.monster.de/softwareentwickler-c-qt-qml-bedienoberfl%C3%A4che-gui-hmi-f%C3%BCr-medizintechnik-inhouse-m-w-job-frankfurt-am-main-hessen-deutschland-181337266.aspx?mescoid=1500127001001&jobPosition=2


////////////////////////////////////////////////////////////////


http://a4academics.com/interview-questions/57-c-plus-plus/419-cpp-interview-questions-answers

http://www.arraynotfound.com/2016/07/cpp-interview-questions-and-answers-from-freshers-to-experienced.html#Q_7_1_1

https://tests4geeks.com/cpp-interview-questions/

https://stackoverflow.com/questions/9736833/new-intsize-vs-stdvector

http://www.geeksforgeeks.org/commonly-asked-c-interview-questions-set-1/
























DROP VIEW APO.AUTODEALER_COMPANY;

/* Formatted on 16.06.2017 14:22:56 (QP5 v5.149.1003.31008) */
CREATE OR REPLACE FORCE VIEW APO.AUTODEALER_COMPANY
(
   ID,
   SUBJECT_FEDERATION_CODE_FK,
   AUTO_DEALER_ID_FK
)
AS
   SELECT id, subject_federation_code_fk, auto_dealer_id_fk
     FROM rgsscc.ref_autodealer_company1
    WHERE     date_from <= SYSDATE
          AND NVL (date_to, SYSDATE) >= SYSDATE
          AND START_date <= SYSDATE
          AND NVL (END_date, SYSDATE) >= SYSDATE;
	  
	  



	  
DROP VIEW APO.FRANSHIZE_7_3_53;

/* Formatted on 16.06.2017 14:24:24 (QP5 v5.149.1003.31008) */
CREATE OR REPLACE FORCE VIEW APO.FRANSHIZE_7_3_53
(
   K4_ID,
   CODE_T_FR,
   NAME_T_FR,
   CODE_ED_IZM_FR,
   NAME_ED_IZM_FR,
   FRANCHISE_PERCENT,
   VEHICLE_GROUP_ID,
   VEHICLE_GROUP_NAME,
   PRODUCT_ID,
   PRODUCT_NAME,
   CASCO_TERRITORY_ID,
   CASCO_TERRITORY_NAME,
   CODE,
   BRAND_NAME,
   MODEL_NAME,
   PROJECT_ID,
   PROJECT_NAME,
   COEFF_VALUE,
   START_DATE,
   END_DATE
)
AS
     SELECT ckk_7_3_53.k4_id,
            ckk_4_2_34.code_t_fr,
            ckk_4_2_34.name_t_fr,
            ckk_4_2_35.code_ed_izm_fr,
            ckk_4_2_35.name_ed_izm_fr,
            ckk_7_3_53.franchise_percent,
            ckk_7_2_9.vehicle_group_id,
            ckk_7_2_9.vehicle_group_name,
            ckk_7_3_2.product_id,
            ckk_7_3_2.product_name,
            ckk_7_2_8.casco_territory_id,
            ckk_7_2_8.casco_territory_name,
            ckk_5_1_3.code,
            ckk_5_1_3.brand_name,
            ckk_5_1_3.model_name,
            ckk_7_4_8.project_id,
            ckk_7_4_8.project_name,
            ckk_7_3_53.coeff_value,
            ckk_7_3_53.start_date,
            ckk_7_3_53.end_date
       FROM rgsscc.ref_cascodictk04 ckk_7_3_53
            LEFT JOIN rgsscc.ref_autodictvehiclegroup ckk_7_2_9
               ON (ckk_7_3_53.vehicle_group_id_lnk_fk_ = ckk_7_2_9.scc_id
                   AND ckk_7_2_9.scc_status = 0)
            LEFT JOIN rgsscc.ref_ed_izm_franshiza ckk_4_2_35
               ON (ckk_7_3_53.to_4235_fk_ = ckk_4_2_35.scc_id
                   AND ckk_4_2_35.scc_status = 0)
            LEFT JOIN rgsscc.ref_product ckk_7_3_2
               ON (ckk_7_3_53.to_732_fk_ = ckk_7_3_2.scc_id
                   AND ckk_7_3_2.scc_status = 0)
            LEFT JOIN rgsscc.ref_autodictcascoterritory ckk_7_2_8
               ON (    ckk_7_3_53.link_7353_to_728_fk_ = ckk_7_2_8.scc_id
                   AND ckk_7_2_8.scc_status = 0
                   AND ckk_7_2_8.active_entry = 'Y')
            LEFT JOIN apo.carrier_models ckk_5_1_3
               ON ckk_7_3_53.vehicle_code_fk_ = ckk_5_1_3.scc_id
            LEFT JOIN rgsscc.ref_dictproject ckk_7_4_8
               ON (ckk_7_3_53.project_id_fk_ = ckk_7_4_8.scc_id
                   AND ckk_7_4_8.scc_status = 0)
            LEFT JOIN rgsscc.ref_t_franshiza ckk_4_2_34
               ON (ckk_7_3_53.code_t_fr_lnk_fk_ = ckk_4_2_34.scc_id
                   AND ckk_4_2_34.scc_status = 0)
      WHERE ckk_7_3_53.scc_status = 0
   ORDER BY TO_NUMBER (ckk_7_3_2.product_id),
            TO_NUMBER (ckk_4_2_34.code_t_fr),
            TO_NUMBER (ckk_7_3_53.franchise_percent),
            TO_NUMBER (ckk_7_2_9.vehicle_group_id),
            TO_NUMBER (ckk_4_2_35.code_ed_izm_fr);	  




DROP VIEW APO.NSFA_DICT_PAY_DOCTYPE_7_4_33;

/* Formatted on 16.06.2017 14:25:09 (QP5 v5.149.1003.31008) */
CREATE OR REPLACE FORCE VIEW APO.NSFA_DICT_PAY_DOCTYPE_7_4_33
(
   ID,
   IS_USE_PAY_VIRTU,
   PAYMENT_DOC_ID,
   PAYMENT_DOC_NAME
)
AS
   SELECT skk_7_4_33.ID,
          skk_7_4_33.IS_USE_PAY_VIRTU,
          CAST (skk_7_4_33.PAYMENT_DOC_ID AS NUMBER) AS PAYMENT_DOC_ID,
          skk_7_4_33.PAYMENT_DOC_NAME
     FROM rgsscc.REF_DICTPAYMENTDOCUMENT skk_7_4_33
    WHERE skk_7_4_33.scc_status = 0;
    
    
    

# ANALITIK:

- https://habrahabr.ru/post/178475/
- https://habrahabr.ru/company/nordavind/blog/177571/
- http://jobfine.ru/rabota/analitik-chto-nuzhno-znat/
- http://buduguru.org/profession/23

# ANALITIK:

Т.к. В том чате уже идет взаимодействие с 3 людьми
edited 
В первую очередь надо ознакомиться с 
http://getbootstrap.com/
http://getbootstrap.com/css/#grid
Это фреймворк для работы с css

Потом фреймворк Angular2(он уже 4, но это не важно)
https://angular.io/

Для того чтобы быстро начать работу на нем, тебе поможет геренатор проекта:
https://github.com/angular/angular-cli
Getbootstrap
Bootstrap · The world's most popular mobile-first and responsive front-end framework.
Bootstrap, a sleek, intuitive, and powerful mobile first front-end framework for faster and easier web development.
 обещанная книга по второму ангуляру
[ng-book2-angular-4-r60.pdf] 30.1 MB
[ng-book2-angular-4-r60-code-samples.zip] 11.6 MB
 https://career.luxoft.com/careers/150789/senior-regular-c-developer/
https://career.luxoft.com/careers/143386/dsp-audio-embedded-developer/
куда тебя лучше порекомендовать?

Luxoft
Senior/Regular C++ Developer - May 30, 2017 - Moscow, Russian Federation
Luxoft is looking for Senior/Regular C++ Developer in Moscow, Russian Federation - May 30, 2017
 Еще одна вакансия по шарпам
https://career.luxoft.com/careers/145307/regular-senior-net-asp-developer/

Luxoft
Regular/Senior .NET ASP Developer - May 2, 2017 - Moscow, Russian Federation
Luxoft is looking for Regular/Senior .NET ASP Developer in Moscow, Russian Federation - May 2, 2017
 Ты кстати с гитхабом хорошо дружишь?

Книги пришли пожалуйста вот сюда
Я ж вроде уже прислал
 или тебе на почту?

mobelus@mail.ru

Жень,  пока всё только просматриваю поверхностно, и в лёгкую гуглю. Исходя из инструкции на гитхабе вопрос такой, Ангулярный проект ставится на Винду нормально ?

[12:38:47 PM] Евгений Миронов Джавист:
Да, вполне себе ставится)
 https://nodejs.org/en/
 ставь 6.10 версию

[12:49:09 PM] Pavel:
Ок

[12:50:06 PM] Евгений Миронов Джавист:
Кстати, финансовые вопросы тебе придется решать с Сашей, рекомендую обсудить сразу время, финансы и т.д., чтобы вы хорошо понимали друг друга
 Чтобы не получилось, что ты тратишь своё время впустую

[12:53:09 PM] Pavel:
Окей






http://getbooststrap.com
http://getbooststrap.com/css/#grid

https://angular.io

https://github.com/angular/angular-cli



# NIGHT SHIFTS:
https://hh.ru/vacancy/20388381?utm_source=gorodrabot.ru&utm_medium=referral&utm_campaign=gr


https://career.ru/vacancy/20487562?query=%D1%82%D0%B0%D0%BD%D1%86%D0%BE%D0%B2%D1%89%D0%B8%D0%BA
	

https://career.ru/vacancy/20558955?query=%D0%BD%D0%BE%D1%87%D0%BD%D0%BE%D0%B9

https://career.ru/vacancy/20593762?query=%D0%BD%D0%BE%D1%87%D0%BD%D0%BE%D0%B9


https://career.ru/vacancy/20038408?query=%D0%BD%D0%BE%D1%87%D0%BD%D0%BE%D0%B9
(2-3 месяца) дневной график: смены чередуются (8.00-14.00 / 14.00-20.00 или 8.00-20.00)

http://rabotavmcdonalds.ru/vacancy/rabotnik_restorana/?utm_source=careerru&utm_medium=banner_760_60&utm_campaign=russia

https://career.ru/vacancy/20413032?query=%D0%BD%D0%BE%D1%87%D0%BD%D0%BE%D0%B9

https://hh.ru/vacancy/19962324?query=%D0%BD%D0%BE%D1%87%D0%BD%D0%BE%D0%B9
1 неделя стажировки - 5 дней с 10 до 18 (!!!)


https://career.ru/vacancy/20674968?query=%D0%BD%D0%BE%D1%87%D0%BD%D0%BE%D0%B9

https://career.ru/vacancy/20674899


https://hh.ru/vacancy/18552430?query=%D0%BD%D0%BE%D1%87%D0%BD%D0%BE%D0%B9
https://career.ru/vacancy/18600556?query=%D0%BD%D0%BE%D1%87%D0%BD%D0%BE%D0%B9
https://hh.ru/vacancy/17654036?query=%D0%BD%D0%BE%D1%87%D0%BD%D0%BE%D0%B9
https://career.ru/vacancy/18481877?query=%D0%BD%D0%BE%D1%87%D0%BD%D0%BE%D0%B9
https://career.ru/vacancy/17309095?query=%D0%BD%D0%BE%D1%87%D0%BD%D0%BE%D0%B9

# NIGHT SHIFTS









http://knizhnik.org/dzhasper-fforde/polnyj-vpered-nazad-ili-ottenki-serogo/1?d=0


/*
////////////////////////////////////
ITERATOR:
i++ / ++i

i = 2;
k = i++; // post // k = i ,  i = i+1 // 
k = ++i; // pre //  i = i+1, k = i

for(iterator it; it<n; it++) - временный объект создаём который равен текущему значению итератора до увеличения на один и увеличиваем только ПОСЛЕ того как вернули это временное значение
for(iterator it; it<n; ++it) - МЫ ВОЗВРАЩАЕМ АКУТАЛЬНУЮ ВЕРСИЮ ИТЕРАТОР И НЕ ГЕНЕРИРУЕТСЯ ВРЕМЕННЫЙ ОБЪЕКТ. 1) Увеличили итератор на 1 ... 2) отправляем в цикл увеличенный на 1 элемент и работаем с ним
// временный объект - копия текущего итератора, но со следующей позицией 

*/

/*
доступ рандомный к каждому эл-ту
дек - двутороняя очередь - пушбэк / пушфронт
вектор - есть только пушбек

.begin() - действительный ПЕРВЫЙ элемент
.end() - Следующий ПОСЛЕ последнего элемента элемент (недействительный)

".size() == 0"  ВМЕСТО ЭТОГО всегда ЛУЧШЕ  ".empty()"
Причина - .size()  - вызывает пересчёт всех элементов
Причина - .empty() - возвращает bool-значение.

////////////////////////////////////
ВЕКТОР
забит до 100-тни. вектор делаем пушбек - пересоздаётся новый буфер как правило расширенный вдвое
1) существующие элоементы туда в него копируются из старого и после 2) вставляется новый вставленный элемент.
Все итераторы при этом стали НЕвалидные, которые указывали не предыдущий кусок памяти.
- перераспределение памяти каждый раз перекопирует всё полностью
+ вектора (Стринг и Вектор - есть метод vec.data() = получаем указатель на весь смежный 
участок памяти который занимает весь вектор и работем с ним как с обычным буфером (массив данных))
+ доступ к произвольному эелементу присуствует 
Вставка в вектор - О(1) - ПРИЧИНА - потому что это массив и мы оп индексу можем спокойно обратиться к любому элементу, тоесть операция получения эл-та по индексу (его "номеру") 
Джосатис - о вставке - иногда это бывает О(n) - если надо перераспоределять буфер - изза того, что линейно последовательно происходит копирование по одному элементу из старого места на новое старого вектора на место нового +выделение памяти под размер нового вектора, размер которого вдвое больше старого.

////////////////////////////////////
ДЕК (DEQUE) - Двусторонняя очередь
забит до 100-тни. в дек делаем пушбек/пушфронт - ВСЕ ИТЕРАТОРЫ целые остаются.
Все ссылки так и остались на своём месте, только добавилась новая.
+ перераспределение памяти удобнее и быстрее
- невозможно использовать весь дек целиком, потомучто все элементы фрагментированы и лежат каждый в своём месте.
- доступ к произвольному эелементу присуствует. Только используя итераторы.

STD::SORT - ТРЕБУЕТ От контейнера итератора произвольного доступа (random iterator).
quick_sort - можно использовать как к ДЕКу так и к ВЕКТОРу - QUICK_SORT

////////////////////////////////////
СПИСОК (LIST)
обычный STD::SORT изза последовательного доступа к элементам использовать нельзя
.list_sort() - сортировка СЛИЯНИЕМ = MERGE_SORT. Сложность O(n*log(n))

Поиск элемента О(n), потомучто надо пройти по всем элементам

Удаление элемента - итераторы на всё 
////////////////////////////////////
Во всех Красно-Чёрное Дерево. 
О(log(n)) во всех функциях, где n - число элементов
SET, MULTISET, MAP, MULTIMAP

SET - хранит все элементы в отсортированном виде (с поправкой на тип элементов)
SET.insert() - 

MAP _map

MULTIMAP _mmap
_mmap - вернёт последний вставленный элемент

Сет - только один параметр, value
Map - имеет два параметра, key <-> value
Соответсвенно, когда нам избыточно key и не нужно его указывать и мы готовы использовать обычные key индексы которые нам предоставляет Сет, используем его.
Если же хотим задавать собственные key - то стоит использовать map

ВЕКТОР против СЕТ для сохранения и сортировки названия файлов.
1) Сет вставка -> n*log(n). вектор вставка -> n*(операция перераспределения вектора при каждой вставке). 
2) Сортировка Вектора - наиболее оптимальную для случая с вектором можем взять быстрыю сортировку n*log(n). Сортировка Сета не нужна вообще.
3) Обработать каждый элемент - накопить, сортировать и обработать. Через Итератор О(n) - последовательно обрабатываем каждый элемент

////////////////////////////////////
UNORDERED_SET
UNORDERED_MAP

При попадании в одну и туже ячейку, тоесть произошла коллизия, то список расширяется. Можно задавать - хэш промахи +фрагментация
Insert, Search, Remove - O(1) НО 


*/

/*
SWAP()
Всегда стоит использовать ФУНКЦИЮ ЧЛЕН, она всегда БЫСТРЕЕ, чем обобщённая работает. (С итератором последовательного доступа для списков и доугих контейнеров)


Есть функции для обработки блоков элементов:
INSERT_RANGE() - функции, которые обрабатывают целые интервалы, всегда работают быстрее, чем в циклах с использованием аналогичных итераторов
*/

/*
События с Автособросом / Без автосброса.
thrd1.CreateEvent(AUTO_RESET)
thrd1.SetEvent() - Установили в СИГНАЛЬНОЕ СОСТОЯНИЕ

while()
{
// Событие Без_Автосброса то нужно явно вызывать ResetEvent() - перевод в НЕСИГНАЛЬНОЕ СОСТОЯНИЕ
  thrd2.WaitForSingleObject()
  ResetEvent();
  thrd3.WaitForSingleObject()
  ResetEvent();
}

while()
{
// Событие C_Автосбросом то НЕ нужно явно вызывать ResetEvent(), он по выходу из WaitForSingleObject сбросится сам
  thrd2.WaitForSingleObject()
  thrd3.WaitForSingleObject()
}


ИСПОЛЬЗОРВАНИЕ СОБЫТИЙ:
МЫ ВНУТРИ СВОЕГО ПРОЦЕССА ПОНАСОЗДАВАЛИ ОБРАБОТЧИКИ СОБЫТИЙ, И ОБРАБАТЫВАЕМ ИХ ТОГДА КОГДА ОНИ перешли из несгнального сосотяния в сигналоьное соотсветсвенно.
Причём и мы можем отслеживать и сторонние приложенияы тоже, по ID-события / Импени события.

*/

/*

*/




убрать расчёт коэффициентов
убрать расчёт К5
из рассчёта застрахованных убрать расчёт К6


# DIRECTSHOW

DirectShow requires NET.Framework v.4 at least

https://www.microsoft.com/net/download/framework

Try downloading SDK such as Windows SDK "http://www.microsoft.com/downloads/details.aspx?FamilyID=6b6c21d2-2006-4afa-9702-529fa782d63b&displaylang=en". There are usually a bunch of samples for directshow. But, mainly they either use commandline "nmake" (not make) or "cl" (not cc or gcc) to build. Sometimes they provide *.sln files to be used under VS. Your vcam package is only a dll and you still need to write an application to test this. Based on the samples from there, I believe you can be able to cook up one hello-world app for your vcam ;)


# маркер edding 140s ЧЕРНЫЙ

http://www.vseinstrumenti.ru/ruchnoy_instrument/dlya_shtukaturno-otdelochnyh_rabot/razmetochnyi/edding/4sht_0_3mm_e-140-4s/?gclid=CP6Cs4-bydICFV5lGQod4-cOcQ

http://www.vseinstrumenti.ru/selfDelivery/shop/3.html



# BEST OF SORTING ALGORITHM:

Timsort - Хорошее описание https://habrahabr.ru/company/infopulse/blog/133303/
, просто процитирую основную идею:
- Специальный алгоритм разделяет входной массив на подмассивы
- Каждый подмассив сортируется обычной сортировкой вставками
- Отсортированные подмассивы собираются в единый массив с помощью модифицированной сортировки слиянием

Он, имея сложность не более O(n log n), ускоряется в случае сортировки частично упорядоченных данных и имеет сложность O(n), если данные изначально отсортированны. Но это не единственный алгоритм с такими заявленными свойствами. Существует еще как минимум два более-менее известных метода с похожей сложностью — это Smoothsort и сортировка Шелла.
 !!! Сложность алгоритма O(n log n) означает, что при больших n время работы алгоритма (или общее количество операций) не более чем C · n log n, где C — некая положительная константа.


Хочу заметить, что я сравнивал именно производительность, и специально не заострял внимание на других параметрах (вроде использования дополнительной памяти).

1) Мой субъективный вывод — если нужен очень хороший алгоритм сортировки для встраивания в библиотеку или в большой проект то лучше всего подойдет Timsort. 
2) В случае же небольших задач, где нет времени и необходимости писать сложные алгоритмы, а результат нужен быстро — то вполне можно обойтись и Quicksort'ом — так как он дает лучшую из простых в написании алгоритмов производительность.



# OFTEN USED CODE PARTS:

double arr[] = { 10.99, 34.66, 3.14567, 1.7 };

int size  = sizeof(arr)/sizeof(arr[0]);



// О ВИРТ. ФУНКЦИЯХ
/////////////////////////////////////////////////////////////

// http://www.cyberforum.ru/cpp-beginners/thread1391513.html#post7321173

// 17.03.2015, 23:25  [ТС]

    AA* pa; 
// Указателю на базовый класс присваиваем адрес ПРОИЗВОДНОГО класса:
    pa=&b;   
    pa->f();// виртуальный вызов f() из B
    pa->AA::f();// невиртуальный вызов f() из AA


// РЕАЛИЗОВАТЬ СВОЙ  УМНЫЙ УКАЗАТЕЛЬ
/////////////////////////////////////////////////////////////

// РЕАЛИЗОВАТЬ СВОЙ  УМНЫЙ УКАЗАТЕЛЬ - UNIQUE_PTR
/////////////////////////////////////////////////////////////

// РЕАЛИЗОВАТЬ СВОЙ  УМНЫЙ УКАЗАТЕЛЬ - SHARED_PTR
/////////////////////////////////////////////////////////////

MY SHARED_PTR:
http://www.cyberforum.ru/cpp-beginners/thread943866.html

// РЕАЛИЗОВАТЬ СВОЙ  LIST
/////////////////////////////////////////////////////////////

http://www.cyberforum.ru/cpp-beginners/thread178335.html#post1039880


NEED LIST WITH A    NODE
struct node
{
	char some;
	int key;
};
	


// РЕАЛИЗОВАТЬ СВОЙ  VECTOR
/////////////////////////////////////////////////////////////
	
http://www.cyberforum.ru/cpp-beginners/thread178335.html#post1693182



// РЕАЛИЗОВАТЬ СВОЙ  HASH TABLE
/////////////////////////////////////////////////////////////

http://www.programmersforum.ru/showthread.php?t=69994

const int maxn=10000;
struct node
{
	char znac[20];
	int key;
};

int kolcol;
int kolsl;
int ObTable;

node hashtable[maxn];


// РЕАЛИЗОВАТЬ СВОЙ  MAP
/////////////////////////////////////////////////////////////

	

// РЕАЛИЗОВАТЬ СВОЮ ФУНКЦИЮ  ATOI
/////////////////////////////////////////////////////////////

int atoi(char s[])
{
    int i, n;
    n = 0;
    for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i)
		n = (n * 10) + (s[i] - '0');
    return n;
}

int atoi(char* s)
{
    int n = 0;
    while( *s >= '0' && *s <= '9' ) {
        n *= 10;
        n += *s++;
        n -= '0';
    }
    return n;
}

int my_atoi(const char*  src)
{
	int result = 0;
	int digit = 1;
	const int DIGIT_DIFFERENCE = 10;
	const char ZERO_SYMBOL = '0';
	for(int i = (strlen(str)-1); i >= 0; i--)
	{
		result = result + (digit * int(str[i]-ZERO_SYMBOL));
		digit = digit * DIGIT_DIFFERENCE;
	}
	return result;
	
	// NO delimiters 
	// NO trim string fuction for space-characters 
	// NO negative numbers / multiple minus symbols in string
	// NO check if there exist other symbols than numbers in string
}


#include <iostream>
#include <cstdlib>
using namespace std;
static const char MINUS = '-';
char* my_trimLeft(const char* src);
int my_atoi(const char*  src);

int main()
{
	cout << my_atoi("bjk vvh-)(-20856--fbhcfr f");
	cin.get();
	return 0;
}

// Implement the function, that transforms string into integer.
int my_atoi(const char*  src)
{
	bool isNegative = false;
	char* str = my_trimLeft(src);
	if(str == NULL)
	{
		return EXIT_FAILURE;			// input error, terminating
	}
	if(str[0] == MINUS)
	{
		isNegative = true;
		str++;
	}
	int result = 0;
	int digit = 1;
	const int DIGIT_DIFFERENCE = 10;
	const char ZERO_SYMBOL = '0';
	for(int i = (strlen(str)-1); i >= 0; i--)
	{
		result = result + (digit * int(str[i]-ZERO_SYMBOL));
		digit = digit * DIGIT_DIFFERENCE;
	}
	if(isNegative == false)
	{
		delete [] str;
		return result;
	}
	else
	{
		str--;
		delete [] str;
		return -result;
	}
}

char* my_trimLeft(const char* src)
{
	if(strlen(src) == 0)	// there's no string
	{
		return NULL;
	}
	char* resultStr = new char[strlen(src)];
	int srcIndex = 0;
	int resultIndex = 0;
	while(	(0 == isdigit(src[srcIndex]))
		&&
			(srcIndex < strlen(src))
		)
	{
		if ((src[srcIndex] == MINUS) && (0 != isdigit(src[srcIndex+1])))
		{
			resultStr[resultIndex] = MINUS;
			resultIndex++;
		}
		srcIndex++;
	}
	// now srcIndex indexes the first numeric in the string
	while(	(0 != isdigit(src[srcIndex]))
		&&
			(srcIndex < strlen(src))
		)
	{
		resultStr[resultIndex] = src[srcIndex];
		resultIndex++;
		srcIndex++;
	}
	resultStr[resultIndex] = '\0';
	if(resultIndex == 0)	// no numerics in the string
	{
		return NULL;
	}
	return resultStr;
}


int my_atoi(const char*  src)
{
  int result = 0;
  const char*  tmp_src;
  tmp_src = src;

  if (*tmp_src=='-')
	  tmp_src++;
  for(;strlen(tmp_src)>0; result = (result*10) + ((char)*(tmp_src++)-'0'));
  result *= (*src == '-') ? -1 : 1;
  
  return result;
}


#include <iostream.h>
#include <string.h>
#include <ctype.h>

char *itoa (int n, char *s)
{
 char *t=s;
 int z=0;
 
 if (n<0) { z=1; n = -n; }
 do *s++ = n%10 + '0';
 while (n/=10);
 if (z) *s++ = '-';
 *s = '\0';
 
 return strrev(t);
}

int atoi (char *s)
{
 int z=0, n=0;
 while(isspace(*s)) s++;
 
 if (*s=='-')
 { z=1; s++; }
 else if (*s=='+')
	 s++;
 while (isdigit(*s))
	 n = (10*n) + *s++ - '0';
 return (z?-n:n);
}

void main ()
{
 int n=-31289;
 char buf[80];
 cout << "\nitoa=" << itoa (n,buf);
 cout << "\natoi=" << atoi (buf);
 cin.get();
}

/////////////////////////////////////////////////////////////
// РАЗВЕРНУТЬ СТРОКУ
/////////////////////////////////////////////////////////////

// STL РЕШЕНИЕ
#include <iostream>
#include<string>
#include <algorithm>

std::string goodbyeWorld="Hello World";
std::reverse(goodbyeWorld.begin(), goodbyeWorld.end());
std::cout<<goodbyeWorld<<std::endl;

// ШАБЛОННОЕ РЕШЕНИЕ
#include <iostream>
#include <algorithm>

template<typename T> void t_reverse(T* a, T* b) 
{
    T t;
    for(b -= 1; a < b; ++a, --b) {
        t  = *a;
       *a = *b;
       *b = t;
   }
}


int main()
{
   char s[] = "123";
   puts(s);  // исходная строка
   t_reverse(s, s + strlen(s));
   puts(s);  // вывод реверс-строки
	
   double arr[] = { 10.99, 34.66, 3.14567, 1.7 };
   int size  = sizeof(arr)/sizeof(arr[0]);

   // выведем исходный массив
   std::copy(arr, arr + size, std::ostream_iterator<double>(std::cout, "\t"));
   t_reverse(arr, arr + size);
   std::cout << std::endl;
   // выведем реверс массив
   std::copy(arr, arr + size, std::ostream_iterator<double>(std::cout, "\t"));
   return 0;
}



// РЕКУРСИВНОЕ РЕШЕНИЕ
#include <iostream.h>
 
void RevStr(char* S,int l)
{
    char c;
    if (l > 1)
    {
      c=S[0];
      S[0]=S[l-1];
      S[l-1]=c;
      RevStr(S+1,l-2);
    }             
}       
 
int main(int argc, char* argv[])
{
    char S[12]="Test of pen";
    RevStr(S,11);
    cout << S << endl;
    return 0;
}


// РЕШЕНИЕ НА УКАЗАТЕЛЯХ
char* strrev(char* str)
{
    char* left = str;
    char* rigth = str;
    while (*str++)
		str -= 2;
    while (left < str)
    {
        char c = *left;
        *left++ = *str;
        *str-- = c;
    }
    return rigth;
}

int main()
{
    char x[100] = {"String reverse"};
    std::cout << strrev(x);
    return 0;
}

// ЧЕРЕЗ ПОЛОВИНУ С ЛЕВОЙ СТОРОНЫ
{
   char str[] = "12345678";
   const size_t strLen = sizeof(str);
   for (size_t i = (strLen/2)-1; i--;)
      swap(str[i], str[strLen-i-2]);
   cout << str << endl;
}

// ЧЕРЕЗ ПОЛОВИНУ С ПРАВОЙ СТОРОНЫ
  l = strlen(s);
  for (i = 0; i < l/2; i++)
  {
     s[l+1] = s[i];
     s[i] = s[l-i];
     s[l-i] = s[l+1];
  } 
  s[l+1]=0;

  
//////////////////////////////////////////////////////////////////////////////////////  


# C++ LECTURES:

double arr[] = { 10.99, 34.66, 3.14567, 1.7 };
int size  = sizeof(arr)/sizeof(arr[0]);
   
   

# C++ LECTURES:

STACK AND HEAP IN C++ - https://www.youtube.com/watch?v=_8-ht2AKyH4

Big O Notation - https://www.youtube.com/watch?v=v4cd1O4zkGw


# CYBERFORUM:

http://www.cyberforum.ru/cpp-beginners/thread1949139.html#post10272753


# UNIT TESTING LIB:

https://habrahabr.ru/post/69160/


# GOOGLE INTERVIES EXAMPLES:

https://www.youtube.com/watch?v=ko-KkSmp-Lk

https://www.youtube.com/watch?v=XKu_SEDAykw


статическая переменная функции - сохраняет свое значение после выхода из функции 
void foo()
{
    static int i = 0;
    std::cout << i++ << '\n';
}
 
int  main()
{
    for (int i = 0; i < 4; ++i)
       foo();
}

Output: 0,1,2,3


# LAMBDA FUNCTIONS GUIDE TUTTORIAL ЛЯМБДА ФУНКЦИИ

https://blog.feabhas.com/2014/03/demystifying-c-lambdas/

# PUBLIC PROTECTED PRIVATE

https://cppforeach.wordpress.com/

# EFFECTIVE FUNCTIONS

http://www.cyberforum.ru/cpp-beginners/thread1948635.html



# STD некоторая информация про контейнеры

std::list - двусвязный список, имеющий 2 указателя внутри каждого элемента на Предыдущ. и След. элемент
std::forward_list - односвязный список, только один указатель на следующий элемент.

Как написать СВОЙ Двусвязный список:
http://ci-plus-plus-snachala.ru/?p=60


Перестановка элементов в односвязном списке
http://ru.stackoverflow.com/questions/381470/Перестановка-элементов-в-односвязном-списке


# Some info about basic strings, char pointers and strings in a buffer

http://www.math.spbu.ru/user/dlebedin/ncpp11.pdf

# CLASS Mystring

http://www.sql.ru/forum/909926/ispolzovanie-sobstvennogo-klassa-strok

https://www.linux.org.ru/forum/development/911016

# SOME CODE FOR EXPERIMENTS

//#include "stdio.h" // printf, scanf
//#include <stdio.h> // printf, scanf
//#include <iostream.h>
#include <iostream> // cout, cin


void pause()
{
	std::cin.sync();
	std::cout << "\nPAUSED\n";
	std::cin.ignore();
}

int main()
{
	printf("");

/*
	int **a__[2];
	int *(*a_)[2] = 0;

	int* ad1; // = 0;
	int* ad2; // = 0;
	//ad1 = **a__;
	ad2 = **a_;

	int elem1 = ad1[1];
	int elem2 = ad2[1];
*/

//*
	char buf[4] = "str"; //определение массива символов
	char buf_[] = "str"; //определение массива символов // строковой константы

	//Б. Страуструп, ЯП C++ [5.2.2. Строковые литералы]:
	//Строковый литерал можно присвоить переменной типа char*. Это разрешается, потому что в предыдущих определениях C и C++ типом строкового литерала был char*/ Благодаря такому разрешению миллионы строк кода на C и C++ остаются синтаксически корректными.
	
	char* p_buf  = "str"; //это указатель на char (char* buf_), инициализированный константной строкой "str" = const std::string("str"). писать в константные строки нехорошо константная секция данных 
	//char* bf[4] = "str\0"; //это массив из 4 указателей на char, нулевой элемент инициализирован указателем на константную строку, остальные 3 нулем
	//char* bf[4] = "str\0"; // char *[4] = const char [5]; // can NOT convert;
	char* p_bf[4] = { "str\0" }; //это массив из 4 указателей на char, нулевой элемент инициализирован указателем на константную строку, остальные 3 нулем
	char* p_bf_[] = { "str\0" }; //это массив из 4 указателей на char, нулевой элемент инициализирован указателем на константную строку, остальные 3 нулем


	buf_[0] = '1';
	buf_[1] = '2';
	buf_[2] = '3';
	buf_[3] = '4';
	buf_[4] = '5';

	buf[0] = '1';
	buf[1] = '2';
	buf[2] = '3';
	buf[3] = '4';
	buf[4] = '5';

	*p_buf = '1';

	//*p_buf_ = 'z';
	//*p_buf_ = (char)"sm";

	//*p_bf[0] = '1';
	//*p_bf[1] = '2';
	//*p_bf[2] = '3';

//*/

# DIRTY.RU

     if(EInsOGRN->Text.Trim().Length()>13) { EInsOGRN->Text = nextOGRN.SubString(0, 12); }

//////////////////////////////////////////////////////////////////////////////////////////////

Арндт против ООО Руланд Иммобилиен и других
Тема: Пересылка копий

Уважаемая г. Арндт

настоящим передаю вам копии документов, полученные мной за эту и предыдущую неделю,
для вашего дальнейшего с ними ознакомления.

МФГ 
Симон Кекер
Адвокат

//////////////////////////////////////////////////////////////////////////////////////////////

Арндт против Сисай и ООО Руланд Иммобилиен
Тема: Отзыв и взыскание (полномочия/доверенность) Поручения о списании средств 

Уважаемый г. Руланд,
Раздел B, Пункт 2.6.1 специальных условий осуществления дебетовых операция списания:
настоящим через представление вам оригинала доверенности, сообщаю вам, что я являюсь
оффициальным  представителем интересов г. Тамары Арндт, Вагедесштр. 2, 40479 Дюс-рф.

  1. Мой клиент, которая является обладательницей права на долгосрочное пребывание и
не являющаяся собтвенницей вышеобозначенной квартиры, множество раз, начиная с
06.04.2016 совершила попытки вернуть себе от вас неправомерно снятый вами с неё
специальный налог в размере 10.518,00 Евро. Так же она потребовала, чтобы вы
предоставили разрешение на списание средств. По сегодняшний день всё, что ей было
передано является только копия документа о списании средств.
  От имени и по запросу моей подзащитной настоящим я 
  отзываю 
  все с вашей стороны совершённые денежные запросы
по оплате касающиеся квартиры и требую вас совершить данные переводы обратно мне.
  По мимо прочего я так же требую с вам сообщить мне не располагаетели вы ещё
какими-либо другими разрешениями на списание средств.
  Если до 06.01.2017 вышеказанные мной документы не будут присланы мне, то данный
запрос на получение документов будет оформлено как ходатайство и может быть
перевено в статус официального судебного требования.

  2. В письме от 23.11.2016 вы утверждалои, что у вас на руках присуствует разрешение
на списание средств моей подзащитной, которая по вашему утверждению давала вам
право на списание специального налога. Если в своих показаниях вы ссылаетесь на
посланную вами копию документа от 31.12.2003 то из него вы можете чётко и дасловно
увидеть, что она не имеет достоточной юридической силы для совершения, списания
специального налога, которое является предметом данного спора, по причине того,
что разрешение на списание средств ограничивается лишь ежемесячной оплатой ЖКУ
(жилищно комунальных услуг). 
  По сему, если вы не располагаете каким-либо другим разрешением на списание
средств, то я вынужден уже сегодня вас настоятельно призвать к тому, чтобы вы
осуществили перевод в размере 10.518,00 Евро соответсвенно до 06.01.2017 на
мой вышеобозначенный счёт.

3. Что касается сбора дебиторской задолженности вам необходимо обратиться к
владельцам жилплощади Госпоже Рут Михельс, Катрин Пасс и Инес Трогш, чьи
адреса вы можете посмотреть в выписке из поземельной книги.

МФГ 
Симон Кекер
Адвокат

//////////////////////////////////////////////////////////////////////////////////////////////

Арндт против Сисай и ООО Руланд Иммобилиен
Тема: Ваше замечание 736/2/11/1 

Уважаемый г. Руланд,

Уажаемый г. Хонен,
Раздел B, Пункт 2.6.1 специальных условий осуществления дебетовых операция списания:
  Мой клиент г. Тамара Арндт Вагедесштрассе 2, 40479 Дюссельдорф передала мне ваше
письмо от 21.12.2016, и просил меня сообщить вам следующее:

  1. Мой клиент на настоящий момент явялется правообладателем на проживание и не
являющийся собственником вышеупомянутой квартиры. Собственники квартиры - г. Рут
Михельс, г. Катрин Паас, г. Инес Трогш, чьи адреса вы можете посмотреть в выписке
из поземельной книги. В данном письме речь ведётся об участниках, совокупно владеющих
наследством господина Эмануеля Арндта.

  В вашем письме от 21.12.2006 информируются участники, совокупно владеющие
наследством, о нынешнем положении дел касательно конфликта, причиной которого явился
отзыв снятие средств на уплату специального налога, который был неправомерно
произведён с моей подзащитной. Касательно осуществления Жилищно комунальных платежей,

мой клиент так же собирается составить долгосрочный договор, который будет касаться
выделения отдельного счёта, принадлежащего собственникам.

  2. Я был уполномочен стребовать с вашей предшественницы, не правомерно снятые
06.04.2016 с моего клиента денежные средства на оплату специального налога в размере
10.518 Евро. Информируя вас, передаю в приложении мое соотв. письмо от 28.12.2016.

  3. Я прошу сообщить мне в ближайшее время о принципиальной готовности общества
собственников восстановить моему клиенту неправомерно снятую с её счёта сумму и
перенаправить запрос о списании специального налога на собственников как этого 
требует закон, а так же порядок ведения подобных дел. Если я не получу от вас 
никакой информации до 17.01.2017, я буду исходить в дальнейшем, что с вашей стороны,
вы не готовы решать вопрос.

МФГ 
Симон Кекер
Адвокат

//////////////////////////////////////////////////////////////////////////////////////////////

Арндт против Михельс, Паас и Трогш
Тема: Передача документов и требование восттановления потраченных средств 

Уважаемая г. Михельс,
Раздел B, Пункт 2.6.1 специальных условий осуществления дебетовых операция списания:
настоящим через представление вам оригинала доверенности, сообщаю вам, что я являюсь
оффициальным  представителем интересов г. Тамары Арндт, Вагедесштр. 2, 40479 Дюс-рф.

  1. Как вам уже известно из вашего разговора с г. Арндтом, с жиро-счёта моей
клиентки были списаны 06.04.2016 действующей на то время управляющей компанией, за
принадлежащую вам квартиру по алресу Вагедесштрассе 2, денежные средства в размере
10.518 Евро неправомерным образом для оплаты специального налога.

  Все попытки получить деньги обратно по сегодняшний день ничем не увенчались.
  
  Моей клиентке согласно Параграфу 1049 Часть 1, а так же Параграфу 1093 Часть 1
гражданского кодекса ФРГ предоставляется право выдвинуть тиребование по
восстановлению расходов, понесённых ею за квартиру, к которой вы непосредственно
относитесь, как участник общества наследников, и по мимо прочего в вашем случае
несёте за неё как собственники коллективную финансовую ответсвенность.
  Согласно завещанию и расзрешению на регистрацию от 30.03.2011 моя клиентка 
является лишь правообладательницей на долгосрочное проживание и не является 
(узуфруктуаром) юридическим субъектом, имеющим право владения имуществом,
 вышеупомянутой квартиры. По этой причине, безусловно единственное к чему 
она обязуется законом, это проводить косметический ремонт внутри квартиры, 
и осуществлять оплату за жил-комунал. услуги.

  Однако инициированные обществом совладельцев многоквартирного дома следующие
строительные работы - Ремонтные работы крытой части сводчатого подъезда дома и
балконов - согласно закону не подпадают под определение "регулярное поддержане
квартиры в исправном состоянии". К действиям по поддержанию условий сохранности
недвижимого имущества согласно закону относятся лишь таковые, которые при обычной
эксплуатации жилья проводятся регулярно, хотя и имеют определённые сравнительно
короткие временные промежутки между проведением предыдущего и следующего акта
поддержания жилья в надлежащем состоянии (согласно решению Федерального Верховного
Суда Германии от 5 сентября 1991 IV R 40/90 Вестник федерального налогового
управления. II 1992, страница 192).
  
  В нашем случае речь идёт о внеочередной работе по Профилактике и ремонту дома.
Это в основе своей является делом и задачей собственников-участникоы общества
наследников, а не моей клиентки, как правообладательницы на долгосрочное проживание
в данной квартире (смотри решение Федерального верховного суда Германии от
13.07.2005, VII ZR 311/04;  Федеральное собрание ... статьи 139, 28, 30 ). Даже
в случае если бы моя клиантка являлась бы узуфруктуаром, т.е. имела бы полное право
пользоваться имуществом, о чём однако не имеется записи в поземельной книге, то
даже в этом случае, она не должна была бы нести данные издержки.

  Так же из разговора с г. Арндтом сообщаю вам, что ваше надуманное расширение
понятия из пункта 2, 3-ей страницы завещания указанных там предметов, которые вы
определили, как "движимое имущество", не подпадают под объекты недвижимого
имущества, как указано пункта 1 вышеуказанного завещания. В пункте 1 завещания,
в явном виде, описаны положения касаемые обязанностей несения расходов моей
клиентки, которые воспрещают раздвигать рамки совершаемых актов, внутри квартиры,
до в какой-либо организационно-правовой форме распространяющихся актов за её пределами.

  Таким образом, общество наследников имеет долговое обязательство, в виде
возврата, за списанный с моей клиентки специальный налог, суммы в размере 10.518 Евро.

  По этой причине я вынужден требовать с вас осуществить перевод данных средств
на мой вышеуказанный счёт до 19.01.2015.
  
  2. ЖЭК Вагедесштрассе 2 на данный момент находится под управлением ООО GRUVA.
По причине текущеих проблем моя клиентка не будет предоставлять подтверждение
на списание денежных средств с её счёта. Что с законодательной точки зрения
наиболее правильно, по причине того, что задолжник денег на "домовые расходы"
в в отноешниях между товариществом собственников жилья и собсивенниками жилья,
являются именно собственники жилья и никто другой, коими являетеь вы, как
общество наследников.

  Само собой моя клиентка будет уплачивать "домовые расходы", только в данном
случае вам, как части общества наследников, а не напрямую через списания денежных
средств в ЖЕК.

  ООО GRUVA я по данному вопросу уже предупредил и прилагаю далее соотв-ющее письмо.
  
  Пожалуйста сообщите мне номер счёта  общества наследников, на который моя клиантка
в дальнейшем сможет осуществлять денежные перводы связанные с "домовыми расходами".
  
  В соответсвующем акте, я для данной операции указал вам срок до 12.01.2017.
  
Документы для остальных участников общества наследников, можно найти в приложении.

МФГ 
Симон Кекер
Адвокат

//////////////////////////////////////////////////////////////////////////////////////////////

Арндт ./. Шпаркасса Дюссельдорфа
Тема: Отзыв неавторизованного списания со счёта 

Уважаемая дамы и господа,

настоящим через представление вам оригинала доверенности, сообщаю вам, что я являюсь
оффициальным  представителем интересов г. Тамары Арндт, Вагедесштр. 2, 40479 Дюс-рф.

Моя клиентка расолагает в вашем банке Жиро-счёт № 1005841125.

  В начале апреля 2016 года моей клиентке было сообщено, что товарищество 
собственников жилья по адресу Вагедесштрассе 2-4 будет нести дополнительные расходы
на рестарвционно-ремонтные работы, согласно заключённому договору, в размере 
10.518 Евро, с каждой единицы живой площади.

  Моя клиентка однако, в отношении данной квартиры является лишь правообладательницей
на долгосрочное проживание, и не является собственницей жилья, как вы можете увидеть
исходя из ксерокопии поземельной книги. По этой причине она не обязана нести
дополнительных расходов, и была несогласна с тем, что с её счёта будут взыматься
вышеуказанные средства.
////////////////////////////////////////////////Раздел B, Пункт 2.6.1 специальных условий осуществления дебетовых операция списания:  
  Моя клиентка пожилого возраста, обратилась в вашу компанию 04.04.2016, за 2 дня до
запланированного дня списания средств, к вашей сотруднице, в вашем филиале в 
Роксусмаркте, для предостващения списания данных средств с её счёта. Что как вам 
известно, на тот момент ещё было вполне возможно сделать, без лишних проволочек.

  Там ей было сказано, что операция списание производится заранее, и что запрос на 
списание уже был отправлен в систему. Было сказано, что ничем более ей помочь никто
не может. Ей посоветовали забрать деньги с ЖЭКа. Ей так же не были пересланы 
какие-либо необходимыей ей согласно статье 675х согласно закону о ведении поземельных
книг, документации, исходя из которых можно было бы установить факт списания, или факт
того, что она по закону может с этим запросом пойти в ЖЭК. Операцию проведения списания,
не смотря на обращение и возражения моей клиентки против такового, вы можете наблюдать
в выписке из банковского счёта от 08.04.2016.

  Далее моя клиентка утрудила себя получить с ЖЭКа, ООО Сисэй и Руланд Иммобилиен,
по адресу Глокеншпитц 323, 47809 Крефельд, платёжное поручение, на основании
произошедшего списания с её счёта.

  Ей был направлен вышеуказанный документ, из которого вы можете видеть, что списание
со счёта было произведено неавторизованно, если, сопоставить это списание с платёжным
поручением.

  С одной стороны: Данное (полномочие/доверенность) поручение о списании средств со
счёта от 31.12.2003 связано со счётом умершего супруга, который несёт в себе его
подпись которой моя клиентка не была обязана и не несла обязательств вести дела
данного счёта в соответсвии с тем как его вёл ранее её супруг.

  С другой стороны: (полномочия/доверенность) Поручения о списании средств со счёта к
которым обязуется моя подзащитная, а именно ежемесячные Платежи за коммунальные услуги,
которые не должны превышать 600 евро.
  
  Наличествуют ли у вас ещё какие-либо другие (полномочия/доверенность) поручения
о списании средств со счёта, мне неизвестно. Моя клиентка не может вспомнить, чтобы
она сама давала (полномочия/доверенность) Поручения о списании средств со счёта 
со своей стороны.

Раздел B, Пункт 2.6.1 специальных условий осуществления дебетовых операция списания:
  От имени и по запросу моей подзащитной настоящим я отзываю неавторизированный 
процесс списания со счёта от 06.04.2016 во временных, рамках установленных законом,
равным 13-ти месяцам, согласно Разделу B Пункта 2.6.1 Предложение 2-ое, специальных
условий осуществления дебетовых операция списания, и прошу вас снова пополнить счёт
моей клиентки безотлагательно(незамедлительно) на сумму в 10.518 Евро.

  Все релевантные выкладки касающиеся специальных условий осуществления дебетовых 
операция списания я также прикладываю к письму.

  В случае, если у вас имеется (полномочия/доверенность) Поручение о списании средств
со счёта, прошу вас в скорейшем времени передать мне таковое. На разрешение данного
вопроса я обозначил в письме срок до 06.01.2017.

МФГ 
Симон Кекер
Адвокат

Дополнения ниже
//////////////////////////////////////////////////////////////////////////////////////////////
ДОПОЛНЕНИЕ

Раздел B, Пункт 2.6.1 специальных условий осуществления дебетовых операция списания:

"В случае наличия неавторизованного клиентом платежа банк не имеет права на 
какое-либо возмещения расходов, которые понёс банк. Банк обязуется, снятые средства
с клиентского счёта восстановить в полном размере безотлагательно. При этом счёт 
должен быть вернут банком в то состояние в котором данный счёт был, до совершённого
неавторизированного списания."

Раздел B, Пункт 2.6.5 абзатц второй, специальных условий осуществления дебетовых 
операция списания:

"Запросы/Претензии/Требования клиента (...) и отрицание/отклонение ответчиком
(клиентом) иска в сторону банка, по причине ошибочно проведённого платежа или 
вследствии неавторизованного платежа не допускаются со стороны Банка, если клиент 
проинформировал Банк как минимум в пределах 13-ти месяцев, с момента совершения 
списания денег, об ошибочно проведённом платеже или о неавторизоавнном 
осуществлённом платеже. Данный срок начинается только с того момента, как Банк 
проифнормирует клиента о проводке по дебету соотвествующего платежа, в соответсвии
с передаваемыми клиенту данными о счёте путём Выписки со счёта, в течение месяца, 
с момента вышеупомянутой проводке по дебету; в любом другом случае, начало данного
срока поределяется в соответсвии с днём, когда банк осведомит клиента любым другим
способом о данной проводке по дебету."

//////////////////////////////////////////////////////////////////////////////////////////////

# Stadtsparkasse Düsseldorf

Camphausenstraße 18, 40479 Düsseldorf, Германия
sskduesseldorf.de
+49 211 8782211
Открыто:  24 часа в сутки

Предложить исправление



# Быстрые пути в Проводнике

https://www.sevenforums.com/tutorials/85487-common-file-dialog-box-customize-places-bar.html


# HelloWorld
My first Project on Github

BEFORE EVERY INTERVIEW | BEFORE EVERY INTERVIEW | BEFORE EVERY INTERVIEW
https://www.slideshare.net/olvemaudal/deep-c/16-What_will_happen_if_you

BEFORE EVERY INTERVIEW | BEFORE EVERY INTERVIEW | BEFORE EVERY INTERVIEW


100% Threadsafe code
http://www.bogotobogo.com/cplusplus/C11/8_C11_Race_Conditions.php


http://stellenanzeige.monster.de/softwareentwickler-c-m-w-job-nürnberg-bayern-deutschland-180510068.aspx?mescoid=1500127001001&jobPosition=1


https://www.monster.de/karriereberatung/artikel/anschreiben-bewerbung-softwareingenieur

Moskau, den 20. Februar 2017
 
Bewerbung als Softwareentwickler C++
Anzeige /www.monster.de vom 10. November 2011

Sehr geehrter Herr Göpfert



Ich freue mich, Sie in einem persönlichen Gespräch überzeugen zu können. Mit freundlichen Grüßen

Klaus-Peter Magenau (als Unterschrift)

Anlagen




LINKEDIN

https://ru.linkedin.com/in/pavel-obrosov-416481130

XING

https://www.xing.com/profile/Obrosov_Pavel?sc_o=mxb_p

MONSTER.DE

https://www.monster.de/profile/profile/



Website with an example of how the Text in MD-File here on Git will look like:

http://dillinger.io



Джеффри РИХТЕР - WINDOWS для Профессионалов (C++) [Вся книга Онлайн]

http://wm-help.net/books-online/book/59464/59464.html

http://www.e-reading.club/bookreader.php/135055/Rihter_-_Windows_dlya_professionalov__sozdanie_effektivnyh_Win32-prilozheniii_s_uchetom_specifiki_64-razryadnoii--oe_izd.pdf


МиниРихтер

http://bsuir-helper.ru/sites/default/files/2011/01/24/met/spo_lectures.doc


_beginthread vs _beginthreadex vs CreateThread C++
http://stackoverflow.com/questions/331536/windows-threading-beginthread-vs-beginthreadex-vs-createthread-c
CreateThread() is a raw Win32 API call for creating another thread of control at the kernel level.

_beginthread() & _beginthreadex() are C runtime library calls that call CreateThread() behind the scenes. Once CreateThread() has returned, _beginthread/ex() takes care of additional bookkeeping to make the C runtime library usable & consistent in the new thread.

In C++ you should almost certainly use _beginthreadex() unless you won't be linking to the C runtime library at all (aka MSVCRT*.dll/.lib).


# Взаимная Блокировка DEADLOCK

Простейший пример взаимной блокировки[править | править вики-текст]

Шаг_Процесс 1___________________________Процесс 2

0. Хочет захватить A и B, начинает с A___Хочет захватить A и B, начинает с B
1. Захватывает ресурс A__________________Захватывает ресурс B
2. Ожидает освобождения ресурса B________Ожидает освобождения ресурса A
3. Взаимная блокировка


Отладка взаимных блокировок, как и других ошибок синхронизации, усложняется тем, что для их возникновения нужны специфические условия одновременного выполнения нескольких процессов (в вышеописанном примере если бы процесс 1 успел захватить ресурс B до процесса 2, то ошибка не произошла бы).

Что такое Deadlock, в каких случаях он бывает, как его можно избежать?

Deadlock, он же взаимная блокировка, явление при котором все потоки находятся в режиме ожидания. Чтобы уменьшить шанс появления deadlock'a не рекомендуется использовать методы wait() и notify(). 

Пример: поток 1 захватывает ресурс A, поток 2 - ресурс B. Потоку 1 из ресурса А нужно захватить ресурс В, который удерживается потоком 2, а потоку 2, наоборот, нужно из ресурса В вызвать ресурс А, который удерживается потоком 1. Получается такая ситуация, что оба потока ждут, пока ресурсы станут доступны. Других потоков в системе нет и они оба бесконечно ждут. Это и называется Deadlock.
Синонимом Deadlock'a называют Livelock, когда все потоки занимаются бесполезной работой и состояние системы не меняется с течением времени.

РЕШЕНИЕ ПРОБЛЕМЫ: ОРГАНИЗРВАТЬ ОЧЕРЕДЬ ЗАПРОСОВ К РЕСУРСАМ.



# Критическая Секция

Критическая секция — участок исполняемого кода программы, в котором производится доступ к общему ресурсу (данным или устройству), который не должен быть одновременно использован более чем одним потоком исполнения. При нахождении в критической секции двух (или более) процессов возникает состояние «гонки» («состязания»). Для избежания данной ситуации необходимо выполнение четырех условий:

Два процесса не должны одновременно находиться в критических областях.
В программе не должно быть предположений о скорости или количестве процессоров.
Процесс, находящийся вне критической области, не может блокировать другие процессы.
Невозможна ситуация, в которой процесс вечно ждет попадания в критическую область.
Критическая секция (англ. critical section) — объект синхронизации потоков, позволяющий предотвратить одновременное выполнение некоторого набора операций (обычно связанных с доступом к данным) несколькими потоками. Критическая секция выполняет те же задачи, что и мьютекс.

Между мьютексом и критической секцией есть терминологические различия, так процедура, аналогичная захвату мьютекса, называется входом в критическую секцию (англ. enter), снятию блокировки мьютекса — выходом из критической секции (англ. leave).

Процедура входа и выхода из критических секций обычно занимает меньшее время, нежели аналогичные операции мьютекса, что связано с отсутствием необходимости обращаться к ядру ОС.

В операционных системах семейства Microsoft Windows разница между мьютексом и критической секцией в том, что мьютекс является объектом ядра и может быть использован несколькими процессами одновременно, критическая секция же принадлежит процессу и служит для синхронизации только его потоков.

Критические секции Windows имеют оптимизацию, заключающуюся в использовании атомарно изменяемой переменной наряду с объектом «событие синхронизации» ядра. Захват критической секции означает атомарное увеличение переменной на 1. Переход к ожиданию на событии ядра осуществляется только в случае, если значение переменной до захвата было уже больше 0, то есть происходит реальное «соревнование» двух или более потоков за ресурс.

Таким образом, при отсутствии соревнования захват/освобождение критической секции обходятся без обращений к ядру.

Кроме того, захват уже занятой критической секции до обращения к ядру какое-то малое время ждёт в цикле (кол-во итераций цикла (англ. spin count) задаётся функциями InitializeCriticalSectionAndSpinCount() или SetCriticalSectionSpinCount()) опроса переменной числа текущих пользователей, и, если эта переменная становится равной 0, то захват происходит без обращений к ядру.

Сходный объект в ядре Windows называется FAST_MUTEX (ExAcquire/ReleaseFastMutex). Он отличается от критической секции отсутствием поддержки рекурсивного повторного захвата тем же потоком.

Аналогичный объект в Linux называется фьютекс.



# Перегружать можно следующие операторы:

http://interviewinit.com/2015/03/какие-операторы-нельзя-перегружать-к/

+ — * / % ^ & | ~ ! = < >

+= -= *= /= %= ^= &= |=

<< >> >>= <<= == != <= >=

&& || ++ — ->* , -> [] ()

new new[] delete delete[]

# ПЕРЕГРУЖАТЬ НЕЛЬЗЯ

     :: (разрешение области видимости)
     . (выбор члена)
     .* (выбор члена через указатель на член)
     ?: тернарный оператор
     sizeof, typeid
У первых трех в правой части имя, а не значение.

У тернарного оператора аж 3 параметра, к тому же его возвращаемое значение является l-value.

Переопределять sizeof, typeid, думаю, просто нет смысла.


    Для встроенных типов данных перегружать операции нельзя, потому что тип — это набор данных и операций над ними. Изменяя операции, выполняемые над данными типа, мы меняем само определение типа. Также, нельзя изменить приоритет операции и определить новую операцию.


# Как работает REALLOC

http://cppstudio.com/post/860/





# DEUTSCHLAND ARBEITS ANGEBOTE

Wir bieten Ihnen interessante fachliche Herausforderungen und ein angenehmes Betriebsklima. Ihre gründliche Einarbeitung erachten wir als wesentlichen Baustein für unseren gemeinsamen Erfolg. Wir freuen uns auf Ihre aussagekräftige Bewerbung, die Sie uns idealerweise 
per E-Mail in einer 

PDF-Datei, unter Angabe Ihrer 

Gehaltsvorstellungen und des frühestmöglichen 

Ihrer Gehaltsvorstellungen (Bruttojahreszielgehalt)

sowie ggf. Reise- und Umzugsbereitschaft

Eintrittstermins zukommen lassen.

    //Standort: Nürnberg
MFC - http://stellenanzeige.monster.de/softwareentwickler-c-weiterentwicklung-eines-branchenspezifischen-erp-systems-inhouse-m-w-job-nürnberg-bayern-deutschland-175698832.aspx?mescoid=1500127001001&jobPosition=1

    //Standort: Rosenheim
MFC - http://stellenanzeige.monster.de/softwareentwickler-c-entwicklung-von-anwendungen-bei-einem-produkthersteller-inhouse-m-w-job-rosenheim-bayern-deutschland-180244220.aspx?mescoid=1500127001001&jobPosition=1


    //Standort: Rosenheim
QT - bis-65-000-€ - http://stellenanzeige.monster.de/softwareentwickler-c-qt-guis-für-messtechnik-bis-65-000-€-inhouse-m-w-job-rosenheim-bayern-deutschland-167878006.aspx?mescoid=1500127001001&jobPosition=1

    //Standort: Rosenheim
QT - bis-70-000-€ - http://stellenanzeige.monster.de/software-achitekt-c-qt-monitoring-systeme-bis-70-000-€-inhouse-m-w-job-rosenheim-bayern-deutschland-172107908.aspx?mescoid=9901111000004&jobPosition=1

    //Standort: Hannover
QT - http://stellenanzeige.monster.de/softwareentwickler-c-qt-ms-visual-studio-oracle-mit-pl-sql-inhouse-m-w-job-hannover-niedersachsen-deutschland-167876875.aspx?mescoid=1500127001001&jobPosition=1

    // Standort: Kiel
QT - http://stellenanzeige.monster.de/softwareentwickler-c-qt-m-w-job-kiel-schleswig-holstein-deutschland-178564604.aspx?mescoid=1500127001001&jobPosition=1

    // Standort: Braunschweig //GOM GmbH Schmitzstraße 2 Deutschland Tel.: 0531 390290 E-Mail: jobs@gom.com 
QT - 3D-Bildbearbeitung / CAD-/CAM-Umfeld - http://stellenanzeige.monster.de/softwareentwickler-c-m-w-bildverarbeitung-robotik-gui-job-braunschweig-niedersachsen-deutschland-180784810.aspx?mescoid=1500127001001&jobPosition=1



# USA JOB SEARCH INSTRUCTIONS

https://habrahabr.ru/post/285640/

# USA JOB SEARCH INSTRUCTIONS



# USA JOB OFFER

    //WEBSITES // WITH H1B

http://www.techfetch.com/


http://www.techfetch.com/JS/JS_view_job.aspx?js=3131574

http://www.techfetch.com/JS/JS_view_job.aspx?js=3119668

http://www.techfetch.com/JS/JS_view_job.aspx?js=3126725



https://www.glassdoor.com/job-listing/senior-c-mfc-software-engineer-penrad-JV_IC1142551_KO0,30_KE31,37.htm?jl=2278574677

https://duo.com/about/careers/job/46835?gh_jid=46835&gh_src=76gjcl

http://chm.tbe.taleo.net/chm03/ats/careers/requisition.jsp?org=TRIMBLE&cws=1&rid=10097

https://www.glassdoor.com/job-listing/software-developer-cc-in-windows-icl-georgia-tech-research-institute-JV_IC1155583_KO0,36_KE37,68.htm?jl=1861913514

https://www.glassdoor.com/job-listing/sr-software-engineer-veritas-JV_IC1162334_KO0,20_KE21,28.htm?jl=1988795595

    //Standort: Nürnberg
MFC - 

# UK JOB OFFERS

    //WEBSITES // WITH H1B

https://uk.jora.com/MFC-C++-Developer-jobs#email_alert_modal



# БАНК-КЛИЕНТ

Необходимо разработать сервис для работы с банковскими учётными записями, и приложение "Банк-Клиент".

ФТ (Функциональные требования):

ПРИЛОЖЕНИЕ "БАНК-КЛИЕНТ":
- Необходимо разработать приложение для взаимодействия с владельцем учетной записи банка и симулирующую процесс работы и его обслуживания в банкомате.
- У приложения должны быть следующие экранные формы:
1. Форма "Приветствия" (Сделайте доступным для ввода 4 целых числа - id пользователя, для симуляции сканирования карты банка)
2. Форма ввода PIN-кода
3. Главное меню с ссылками на следующие Формы. Дополните как функциональность так и формы для этих опций.
3.1. Проверка баланса
3.2. Выдача наличных
3.3. смена PIN-кода
3.4. Выписка со счёта клиента
- Для ввода информации используйте мышь и клавиатуру.
- Осуществляя трансакцию снимите фото человека используя веб-камеру. Если веб-камера отсутствует, используйте симулятор веб-камеры.
- Сохраните фото в директории приложения с названием файла в формате "idпользователя_датавремя"
- URL для соединения с сервисом, имя клиента и пароль настраиваются на стороне клиента в config-файле.

СЕРВИС:
- Для создания облачного (cloud based) Веб-Сервис используйте технологию RESTful.
1. Сервис должен содержать в себе систему защиты - логин/пароль.
2. Каждый логин уникален и идентифицирует каждую подключившуюся к системе пользовательскую машину.
3. Конфигурация каждого пользователя расположено в config-файле.
4. Сервис предоставляет все необходимые методы и действия, которые требуются для работы приложения "Банк-Клиент"

Техническое задание

Сервис: 
- Должен быть разработан с использованием Casablanca C++ REST SDK.
- Должен использовать обычный текстовый файл для хранения данных, а не полноценную БД.

Приложение "Банк-Клиент":
- Должно быть создано как "MFC windows forms application".
- Установка должна будет производиться как windows shell, а не из под explorer.exe.
- Приложение должно использовать "Рыбу" вместо полноценной БД (Рекомендуется обычный текстовый файл).
- Для работы с Веб-камерой используйте DirectShow или Windows platform SDK или любое другое API.
- Встройте валидацию, на вводимые символы, цифры, и значения, где это возможно или необходимо, как на стороне Сервиса так и на стороне Приложения.
- Приложение должно быть полностью рабочим - не допускайте в коде Критических ошибок, Выброса исключений и Непредвиденных падений приложения. 
- Добавьте недостающего функционала по необходимости, если вам покажется это правильным с логической и пользовательской точки зрения.
- НАПИШИТЕ ЮНИТ-ТЕСТЫ !!!



RUST Client-Server

http://mariusbancila.ro/blog/2013/08/19/full-fledged-client-server-example-with-cpprest-sdk-110/

http://stackoverflow.com/questions/20496231/jsoncpp-when-having-a-jsonvalue-object-how-can-i-know-its-key-name

field_map
http://stackoverflow.com/questions/38828463/c-rest-casablanca-webjsonvalue-has-no-member-named-field-map

WebCamera - C++ - DirectShow 
http://www.orgler.it/mfcdirectshow.htm

Get Image DirectShow - 
http://stackoverflow.com/questions/11398758/best-directshow-way-to-capture-image-from-web-cam-preview-samplegrabber-is-dep

WEBCAM
http://stackoverflow.com/questions/6912346/webcam-video-capture-using-visual-c-6-0

https://www.codeproject.com/kb/audio-video/videoimagegrabber.aspx


https://social.msdn.microsoft.com/Forums/windowsdesktop/en-US/fa7e41ed-107e-4f77-8154-62f22b0187a6/where-is-directshow-sdk-yes-yet-again-?forum=windowsdirectshowdevelopment

Where is DirectShow SDK ?

C:\Program Files\Microsoft Platform SDK for Windows Server 2003 R2\Samples\Multimedia\DirectShow\BaseClasses\streams.h
C:\Program Files\Microsoft SDKs\Windows\v6.1\Samples\Multimedia\DirectShow\BaseClasses\streams.h
C:\Program Files\Microsoft SDKs\Windows\v7.0\Samples\multimedia\directshow\baseclasses\streams.h


FINAL

https://www.codeproject.com/Articles/6712/Simultaneous-Previewing-Video-Capture-using-Direct

https://www.codeproject.com/Articles/21048/Video-Preview-and-Frames-Capture-to-Memory-with-Sa


---
http://stackoverflow.com/questions/39629008/getting-the-values-from-jsonvalue-using-rest-api-c

http://stackoverflow.com/questions/31674575/c-rest-sdk-casablanca-webjson-iteration

------------------

Real REST RESTful WebService Example: 

https://picoledelimao.github.io/blog/2015/10/13/building-a-restful-web-service-in-c-plus-plus/

Real RESTful Credentials and Register User on Server (log in / password based security):

https://katyscode.wordpress.com/2014/04/02/lightswitch-for-games-part-4-odata-access-from-c-client-code-with-the-c-rest-sdk/

Real Connect to HTTP servers (C++ REST SDK) :

https://msdn.microsoft.com/en-us/library/jj950081.aspx

REST Casablanca MFC App

http://codexpert.ro/blog/2015/05/23/using-lambdas-in-mfc-applications-part-3-dealing-with-c-rest-sdk/


# LAMBDA FUNCTIONS: 

https://blog.feabhas.com/2014/03/demystifying-c-lambdas/


------------------

# DROPBOX API using  RESTful  Example: 

https://msdn.microsoft.com/en-us/magazine/dn342869.aspx


# РЕПЕТИТОРЫ С++: 

http://repetitors.info/predmet/c-plus-plus/

http://profi.ru/repetitor/prog/

http://www.repetit.ru/repetitors/informatika-i-programmirovanie/cpp/online/










"Купить квартиру на кутузовском"

ZIAN
REALTY DREAM
DOMOFOND
BEST HOME



http://www.gotfreefax.com/Fax-to-Germany.aspx

Pavel
omnio2006@ya.ru
+79263862556

Tamara
+492113613736


4930568373288


2-ух комнатная квартира
68 м^2 
5 этаж 9-ти этажного дома
17.900.000
Возможен Торг

Квартира свободна, никто не прописан
более 10 лет в собственности
окна выходят во двро
дом кирпичный
железо-бетонные перекрытия
пластиковые окна
хороший ремонт, но требует косметики
сталинский дом
потоолки 3 метра
балкона - нет
изолированные комнаты 18 и 21 метр
кухня 9 м^2
санузел раздельный
2 коридора
перепланировки не было
всё готово к сделке

большой зелёный двро
ключи от шлагбаума
чистый подъед
лифт заменен на новый 2017 год


# DATABASE QUREIS IN YEARS: 

458 549,16   -  21.01.18 

306 559,15   -  07.07.17

198 111,05   -  24.06.17

473 740,98   -  05.01.18

533 476,20   -  23.12.17

496 353,01   -  02.12.17
