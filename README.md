# HelloWorld
My first Project on Github

Website with an example of how the Text in MD-File here on Git will look like:

http://dillinger.io



Джеффри РИХТЕР - WINDOWS для Профессионалов (C++) [Вся книга Онлайн]

http://wm-help.net/books-online/book/59464/59464.html


_beginthread vs _beginthreadex vs CreateThread C++
http://stackoverflow.com/questions/331536/windows-threading-beginthread-vs-beginthreadex-vs-createthread-c
CreateThread() is a raw Win32 API call for creating another thread of control at the kernel level.

_beginthread() & _beginthreadex() are C runtime library calls that call CreateThread() behind the scenes. Once CreateThread() has returned, _beginthread/ex() takes care of additional bookkeeping to make the C runtime library usable & consistent in the new thread.

In C++ you should almost certainly use _beginthreadex() unless you won't be linking to the C runtime library at all (aka MSVCRT*.dll/.lib).


