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




# USA JOB OFFER

    //WEBSITES // WITH H1B

http://www.techfetch.com/

http://www.techfetch.com/JS/JS_view_job.aspx?js=3131574
http://www.techfetch.com/JS/JS_view_job.aspx?js=3119668
http://www.techfetch.com/JS/JS_view_job.aspx?js=3126725

    //Standort: Nürnberg
MFC - http://stellenanzeige.monster.de/softwareentwickler-c-weiterentwicklung-eines-branchenspezifischen-erp-systems-inhouse-m-w-job-nürnberg-bayern-deutschland-175698832.aspx?mescoid=1500127001001&jobPosition=1

