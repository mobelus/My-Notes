#include <climits>
#include <iostream>

#include <vector>
#include <map>
#include <set>
/*
Имеем DHCP-сервер, который выдаёт конечным пользователям IP-адреса из пула.
Пул представляет собой набор диапазонов адресов IPv4. При изменении настроек пула
необходимо получить диапазоны IP-адресов, которые входили в старый пул, но не входят в новый,
чтобы пометить их в системе как устаревшие. Реализуйте функцию, которая будет вычислять устаревшие
диапазоны, сравнивая новый и старый пул. Предложите тест-кейсы, позволяющие убедиться в корректности
работы алгоритма.
*/

// Используйте следующие типы для IP-адресов, диапазонов и пулов:
using IPAddress = uint32_t; 					// Адрес IPv4 представлен целочисленным типом uint32_t
using Range = std::pair<IPAddress, IPAddress>;	// Диапазон IP-адресов, границы включены
//using Pool = std::map<IPAddress, std::map<IPAddress, int>>; // предложите оптимальный STL-котейнер для хранения диапазонов IP-адресов (Range)
using Pool = std::set<Range>; // предложите оптимальный STL-котейнер для хранения диапазонов IP-адресов (Range)
												// Диапазоны IP-адресов в пулах могут пересекаться. Порядок их расположения в пуле - произвольный.

												// Функция, вычисляющая разницу между старым и новым пулами:
												// `old_pool` - старый пул IP-адресов
												// `new_pool` - новый  пул IP-адресов
												// return value - пул диапазонов "устаревших" IP-адресов

Pool find_diff(const Pool& old_pool, const Pool& new_pool)
{
	Pool result;

	bool found = false;
	for (auto &item : old_pool)
	{
		if (new_pool.find(item) == new_pool.end()) // нет в новом, значит устарел
		{
			std::cout << "NOT FOUND IN NEW: ";  
			std::cout << "[" << item.first << " : " << item.second << "]" << std::endl;
			result.insert(item);
		}
	}
	std::cout << std::endl;

	return result;
}

void show_pool(const std::string pool_name, const Pool& print_pool)
{
	std::cout << pool_name.c_str() << std::endl;
	for (auto &item : print_pool)
	{
		std::cout << "[" << item.first << " : " << item.second << "]" << std::endl;
	}
	std::cout << std::endl;
}

void test_pools()
{
	//[ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 ]
	Pool old_pool;
	old_pool.insert(std::pair<IPAddress, IPAddress>(1,  3));
	old_pool.insert(std::pair<IPAddress, IPAddress>(5,  7));
	old_pool.insert(std::pair<IPAddress, IPAddress>(12, 12));
	old_pool.insert(std::pair<IPAddress, IPAddress>(13, 16));
	show_pool("old_pool", old_pool);

	Pool new_pool;
	new_pool.insert(std::pair<IPAddress, IPAddress>(1,   3));
	new_pool.insert(std::pair<IPAddress, IPAddress>(4,  6));
	new_pool.insert(std::pair<IPAddress, IPAddress>(10, 11));
	new_pool.insert(std::pair<IPAddress, IPAddress>(14, 15));
	show_pool("new_pool", new_pool);

	// Вопрос на уточнение здесь только один, а именно что делать
	// со случаями:
	// 1) КОГДА пулы пересекаются: в нашем случае, это:
	// в старом был диапазон [5, 6, 7], в новом появился [4, 5, 6]
	// забить на их пересечение, и просто сказать, что [5-7]
	// не совпадает полностью с новым [4-6], и забросить [5-7]
	// в результирующий список утаревших пулов, или сделать что-то ещё ...
	// 2) КОГДА пулы содержатся внутри друг друга: в нашем случае, это:
	// в старом был диапазон [13, 14, 15, 16], в новом появился [14, 15]

	// Хотя вроде бы я черезчур заморачиваюсь и получается, что нужно просто найти
	// те, что тупо перестали содержаться в новом и забросить их в устаревшие и всё.


	// Вопрос в задаче скорее по всей видимости
	// даже не в сложности реализации алгоритма
	
	// а именно в выборе оптимального под задачу STL-контейнера
	// при учёте того, что в случае с std::set мы имеем метод find()
	// я набросал один вариант решения
	
	// однако стоит попробовать реализовать с помощью std::map и
	// посмотреть на сколько быстрее будет работать алгоритм
	// метод find() есть и в мэпэ, находит элемент с конкретным ключом

	Pool res_pool = find_diff(old_pool, new_pool);
	show_pool("res_pool", res_pool);
}

void main()
{
	test_pools();
	getchar();
}
