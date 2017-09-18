/*
Имеем DHCP-сервер, который выдаёт конечным пользователям IP-адреса из пула.
Пул представляет собой набор диапазонов адресов IPv4. При изменении настроек пула
необходимо получить диапазоны IP-адресов, которые входили в старый пул, но не входят в новый,
чтобы пометить их в системе как устаревшие. Реализуйте функцию, которая будет вычислять устаревшие
диапазоны, сравнивая новый и старый пул. Предложите тест-кейсы, позволяющие убедиться в корректности
работы алгоритма.
*/

#include <iostream>
#include <algorithm>    // std::find

#include <vector>
#include <map>
#include <set>


// Используйте следующие типы для IP-адресов, диапазонов и пулов:
using IPAddress = uint32_t; 					// Адрес IPv4 представлен целочисленным типом uint32_t
using Range = std::pair<IPAddress, IPAddress>;	// Диапазон IP-адресов, границы включены
//using Pool = ? // предложите оптимальный STL-котейнер для хранения диапазонов IP-адресов (Range)
												// Диапазоны IP-адресов в пулах могут пересекаться. Порядок их расположения в пуле - произвольный.

												// Функция, вычисляющая разницу между старым и новым пулами:
												// `old_pool` - старый пул IP-адресов
												// `new_pool` - новый  пул IP-адресов
												// return value - пул диапазонов "устаревших" IP-адресов



/*
// Old range
192.0.1.11    - 192.1.1.100
192.150.1.11  - 192.150.1.100
192.150.2.51  - 192.150.3.2
192.111.23.98 - 192.111.23.247

// New range
192.122.1.11  - 192.122.1.100
192.150.2.60  - 192.150.3.1		// ! -> got_old:  [192.150.2.51 - 192.150.2.59]; [192.150.3.2 - 192.150.3.2]
192.111.22.34 - 192.111.23.116	// ! -> got_old:  [192.111.23.117 to 192.111.23.247]

*/

struct IpAddressType
{
	IpAddressType()
		: ip_1(0), ip_2(0), ip_3(0), ip_4(0)
	{};
	uint8_t ip_1, ip_2, ip_3, ip_4;
};

IpAddressType converAddrNumToType(uint32_t _ipAddressNum)
{
	IpAddressType addr;
	if (_ipAddressNum)
	{
		addr.ip_1 = _ipAddressNum >> 0;
		addr.ip_2 = _ipAddressNum >> 8;
		addr.ip_3 = _ipAddressNum >> 16;
		addr.ip_4 = _ipAddressNum >> 24;
		//char ipAddressFinal[16];
		//sprintf(ipAddressFinal, "%d.%d.%d.%d", addr.ip_4, addr.ip_3, addr.ip_2, addr.ip_1);
	}
	return addr;
}

using Pool = std::map<IPAddress, IPAddress>; // предложите оптимальный STL-котейнер для хранения диапазонов IP-адресов (Range)

/*
Pool find_diff(const Pool& old_pool, const Pool& new_pool)
{
	// возможных вариантов вхождений / невхождений диапазонов один в другой всего 6:
	// === - новый диапазон
	// ^^^ - старый диапазон
	//
	//                     ===========
	//                         ^^^					1) старый внутри нового полностью
	//                   ^^^^       ^^^^			2) старый не входит в новый слева 3) старый не входит в новый справа
	//               ^^^^^^^^^^^^^^^^^^^^^^^		4) старый не сходит в новый и слева и справа
	//         ^^^^                           ^^^^	5) старый не входит целиком и лежит от новго слева 6) --..-- и лежит от нового справа

	Pool result;
	//for (auto &it_new : new_pool )

	Pool::const_iterator it_new = new_pool.begin();
	uint32_t num_it_new = 1;
	uint32_t size_pool_new = new_pool.size();

	for (const auto &it_old : old_pool)
	{
		// старый левым краем равен правому новому краю
		// или относительно текущего нового правого края у СЛЕДУЮЩЕГО старого диапазона его левый край больше, чем у текущего правый новый 
		if ((it_old.first == it_new->second) || (it_old.first > it_new->second))
		{
			if (size_pool_new > num_it_new)
			{
				num_it_new++;
				it_new++;
			}
		}

		if (it_old.first < it_new->first) // left_old < left_new (*)
		{
			// старый левым краем лежит за пределами левого нового, надо проверить что с правым краем старого
			if (it_old.second < it_new->first) // (*) && right_old < left_new
			{
				// старый левым краем лежит за пределами левого нового, и своим правы краем даже не достаёт до нового
				// => диапазон устарел целиком => помещаем весь [left_old ; right_old] в устаревшие
				result.insert(it_old); // Range(it_old.first, it_old.second)
			}
			else // (*) && right_old >= left_new  => надо проверить правый конец старого диапазонa
			{
				// старый левым краем лежит за пределами левого нового, а своим правы краем равен краю правого нового или даже больше правого нового
				// в любом случае добавляем от левого старого, до левого нового - ибо он устаревший
				if (it_old.second >= it_new->first)
				{
					result.insert(Range(it_old.first, it_new->first - 1));
				}

				// осталось проверить, где находится правый край старого относительно правого нового:
				if (it_old.second > it_new->second) // (*) right_old > right_new 
				{
					// старый левым краем лежит за пределами нового, а правым уходит за пределы нового
					// добавляем от правого нового, до правого старого - ибо он устаревший
					result.insert(Range(it_new->second + 1, it_old.second));
				}
				else // (*) right_old =< right_new 
				{
					// старый левым краем лежит за пределами нового, а правым тоже лежит в новом 
					// левую часть уже добавили в устаревшие, а правую нет смысла
				}
			}
		}
		else // left_old >= left_new (**)
		{
			// старый левым краем лежит внутри нового, или вообще за пределами диапазона, надо проверить его правый край 
			if (it_old.second > it_new->second) // (**) && right_old > right_new
			{
				if (it_old.first > it_new->second) // (**) && left_old > right_new
				{
					// правее последнего нового лежат все оставшиеся старые диапазоны
					if (size_pool_new == num_it_new) // + новые диапазоны уже кончились
					  result.insert(Range(it_old.first, it_old.second));
				}
				else
				{
					// старый левым краем лежит внутри нового, а правый край старого за пределами нового
					// берём правый конец нового до правого конца старого и помещаем в Устаревший
					result.insert(Range(it_new->second + 1, it_old.second));
				}
			}
			else // (**) && (it_old.second <= it_new.second)
			{
				// старый левым краем лежит внутри нового, и правым тоже лежит в новом 
				// никуда его не добавляем
			}
		}
	}

	// где-то необходимо будет пройтись по элементам и искать через find() или at() до куда есть несовпадение
	// custom = convert(begin_range); custom2 = convert(end_range); // нужо будет вставить корректную конвертацию из чисола в IP-шную тип-структуру

	return result;
}
//*/

/*
Pool find_diff(const Pool& old_pool, const Pool& new_pool)
{
	// возможных вариантов вхождений / невхождений диапазонов один в другой всего 6:
	// === - новый диапазон
	// ^^^ - старый диапазон
	//
	//                     ===========
	//                         ^^^					1) старый внутри нового полностью
	//                   ^^^^       ^^^^			2) старый не входит в новый слева 3) старый не входит в новый справа
	//               ^^^^^^^^^^^^^^^^^^^^^^^		4) старый не сходит в новый и слева и справа
	//         ^^^^                           ^^^^	5) старый не входит целиком и лежит от новго слева 6) --..-- и лежит от нового справа

	Pool result;
	//for (auto &it_new : new_pool )
	uint32_t size_pool_old = old_pool.size();
	uint32_t size_pool_new = new_pool.size();

	if (size_pool_old > size_pool_new)
	{
		Pool::const_iterator it_new = new_pool.begin();
		uint32_t num_it_new = 1;

		for (const auto &it_old : old_pool)
		{
			// старый левым краем равен правому новому краю
			// или относительно текущего нового правого края у СЛЕДУЮЩЕГО старого диапазона его левый край больше, чем у текущего правый новый 
			if ((it_old.first == it_new->second) || (it_old.first > it_new->second))
			{
				if (size_pool_new > num_it_new)
				{
					num_it_new++;
					it_new++;
				}
			}

			if (it_old.first < it_new->first) // left_old < left_new (*)
			{
				// старый левым краем лежит за пределами левого нового, надо проверить что с правым краем старого
				if (it_old.second < it_new->first) // (*) && right_old < left_new
				{
					// старый левым краем лежит за пределами левого нового, и своим правы краем даже не достаёт до нового
					// => диапазон устарел целиком => помещаем весь [left_old ; right_old] в устаревшие
					result.insert(it_old); // Range(it_old.first, it_old.second)
				}
				else // (*) && right_old >= left_new  => надо проверить правый конец старого диапазонa
				{
					// старый левым краем лежит за пределами левого нового, а своим правы краем равен краю правого нового или даже больше правого нового
					// в любом случае добавляем от левого старого, до левого нового - ибо он устаревший
					if (it_old.second >= it_new->first)
					{
						result.insert(Range(it_old.first, it_new->first - 1));
					}

					// осталось проверить, где находится правый- край старого относительно правого нового:
					if (it_old.second > it_new->second) // (*) right_old > right_new 
					{
						// старый левым краем лежит за пределами нового, а правым уходит за пределы нового
						// добавляем от правого нового, до правого старого - ибо он устаревший
						result.insert(Range(it_new->second + 1, it_old.second));
					}
					else // (*) right_old =< right_new 
					{
						// старый левым краем лежит за пределами нового, а правым тоже лежит в новом 
						// левую часть уже добавили в устаревшие, а правую нет смысла
					}
				}
			}
			else // left_old >= left_new (**)
			{
				// старый левым краем лежит внутри нового, или вообще за пределами диапазона, надо проверить его правый край 
				if (it_old.second > it_new->second) // (**) && right_old > right_new
				{
					if (it_old.first > it_new->second) // (**) && left_old > right_new
					{
						// правее последнего нового лежат все оставшиеся старые диапазоны
						if (size_pool_new == num_it_new) // + новые диапазоны уже кончились
							result.insert(Range(it_old.first, it_old.second));
					}
					else
					{
						// старый левым краем лежит внутри нового, а правый край старого за пределами нового
						// берём правый конец нового до правого конца старого и помещаем в Устаревший
						result.insert(Range(it_new->second + 1, it_old.second));
					}
				}
				else // (**) && (it_old.second <= it_new.second)
				{
					// старый левым краем лежит внутри нового, и правым тоже лежит в новом 
					// никуда его не добавляем
				}
			}
		}
	}
	else
	{
		Pool::const_iterator it_old = old_pool.begin();
		uint32_t num_it_old = 1;

		for (const auto &it_new : new_pool)
		{
			// 
			if ((it_old->first == it_new.second) || (it_old->first > it_new.second))
			{
				if (size_pool_old > num_it_old)
				{
					num_it_old++;
					it_old++;
				}
			}

			// старый левым краем равен правому новому краю
			// или относительно текущего нового правого края у СЛЕДУЮЩЕГО старого диапазона его левый край больше, чем у текущего правый новый 
			if ((it_old->first == it_new.second) || (it_old->first > it_new.second))
			{
				if (size_pool_old > num_it_old)
				{
					num_it_old++;
					it_old++;
				}
			}

			if (it_old->first < it_new.first) // left_old < left_new (*)
			{
				// старый левым краем лежит за пределами левого нового, надо проверить что с правым краем старого
				if (it_old->second < it_new.first) // (*) && right_old < left_new
				{
					// старый левым краем лежит за пределами левого нового, и своим правы краем даже не достаёт до нового
					// => диапазон устарел целиком => помещаем весь [left_old ; right_old] в устаревшие
					result.insert(*it_old); // Range(it_old->first, it_old->second)
				}
				else // (*) && right_old >= left_new  => надо проверить правый конец старого диапазонa
				{
					// старый левым краем лежит за пределами левого нового, а своим правы краем равен краю правого нового или даже больше правого нового
					// в любом случае добавляем от левого старого, до левого нового - ибо он устаревший
					if (it_old->second >= it_new.first)
					{
						result.insert(Range(it_old->first, it_new.first - 1));
					}

					// осталось проверить, где находится правый край старого относительно правого нового:
					if (it_old->second > it_new.second) // (*) right_old > right_new 
					{
						// старый левым краем лежит за пределами нового, а правым уходит за пределы нового
						// добавляем от правого нового, до правого старого - ибо он устаревший
						result.insert(Range(it_new.second + 1, it_old->second));
					}
					else // (*) right_old =< right_new 
					{
						// старый левым краем лежит за пределами нового, а правым тоже лежит в новом 
						// левую часть уже добавили в устаревшие, а правую нет смысла
					}
				}
			}
			else // left_old >= left_new (**)
			{
				// старый левым краем лежит внутри нового, или вообще за пределами диапазона, надо проверить его правый край 
				if (it_old->second > it_new.second) // (**) && right_old > right_new
				{
					if (it_old->first > it_new.second) // (**) && left_old > right_new
					{
						// правее последнего нового лежат все оставшиеся старые диапазоны
						if (size_pool_old == num_it_old) // + новые диапазоны уже кончились
							result.insert(Range(it_old->first, it_old->second));
					}
					else
					{
						// старый левым краем лежит внутри нового, а правый край старого за пределами нового
						// берём правый конец нового до правого конца старого и помещаем в Устаревший
						result.insert(Range(it_new.second + 1, it_old->second));
					}
				}
				else // (**) && (it_old->second <= it_new.second)
				{
					// старый левым краем лежит внутри нового, и правым тоже лежит в новом 
					// никуда его не добавляем
				}
			}
		}
	}

	// где-то необходимо будет пройтись по элементам и искать через find() или at() до куда есть несовпадение
	// custom = convert(begin_range); custom2 = convert(end_range); // нужо будет вставить корректную конвертацию из чисола в IP-шную тип-структуру

	return result;
}
//*/

//Pool find_diff(const Pool& old_pool, const Pool& new_pool)
Pool find_diff(Pool& old_pool, const Pool& new_pool)
{
	// возможных вариантов вхождений / невхождений диапазонов один в другой всего 6:
	// === - новый диапазон
	// ^^^ - старый диапазон
	//
	//                     ===========
	//                         ^^^					1) старый внутри нового полностью
	//                   ^^^^       ^^^^			2) старый не входит в новый слева 3) старый не входит в новый справа
	//               ^^^^^^^^^^^^^^^^^^^^^^^		4) старый не сходит в новый и слева и справа
	//         ^^^^                           ^^^^	5) старый не входит целиком и лежит от новго слева 6) --..-- и лежит от нового справа

	Pool result;
	//for (auto &it_new : new_pool )
	uint32_t size_pool_old = old_pool.size();
	uint32_t size_pool_new = new_pool.size();

	if (size_pool_old >= size_pool_new)
	{
		Pool::const_iterator it_new = new_pool.begin();
		uint32_t num_it_new = 1;

		for (const auto &it_old : old_pool)
		{
			// старый левым краем равен правому новому краю
			// или относительно текущего нового правого края у СЛЕДУЮЩЕГО старого диапазона его левый край больше, чем у текущего правый новый 
			if ((it_old.first == it_new->second) || (it_old.first > it_new->second))
			{
				if (size_pool_new > num_it_new)
				{
					num_it_new++;
					it_new++;
				}
			}

			if (it_old.first < it_new->first) // left_old < left_new (*)
			{
				// старый левым краем лежит за пределами левого нового, надо проверить что с правым краем старого
				if (it_old.second < it_new->first) // (*) && right_old < left_new
				{
					// старый левым краем лежит за пределами левого нового, и своим правы краем даже не достаёт до нового
					// => диапазон устарел целиком => помещаем весь [left_old ; right_old] в устаревшие
					result.insert(it_old); // Range(it_old.first, it_old.second)
				}
				else // (*) && right_old >= left_new  => надо проверить правый конец старого диапазонa
				{
					// старый левым краем лежит за пределами левого нового, а своим правы краем равен краю правого нового или даже больше правого нового
					// в любом случае добавляем от левого старого, до левого нового - ибо он устаревший
					if (it_old.second >= it_new->first)
					{
						result.insert(Range(it_old.first, it_new->first - 1));
					}

					// осталось проверить, где находится правый край старого относительно правого нового:
					if (it_old.second > it_new->second) // (*) right_old > right_new 
					{
						// старый левым краем лежит за пределами нового, а правым уходит за пределы нового
						// добавляем от правого нового, до правого старого - ибо он устаревший
						result.insert(Range(it_new->second + 1, it_old.second));
					}
					else // (*) right_old =< right_new 
					{
						// старый левым краем лежит за пределами нового, а правым тоже лежит в новом 
						// левую часть уже добавили в устаревшие, а правую нет смысла
					}
				}
			}
			else // left_old >= left_new (**)
			{
				// старый левым краем лежит внутри нового, или вообще за пределами диапазона, надо проверить его правый край 
				if (it_old.second > it_new->second) // (**) && right_old > right_new
				{
					if (it_old.first > it_new->second) // (**) && left_old > right_new
					{
						// правее последнего нового лежат все оставшиеся старые диапазоны
						if (size_pool_new == num_it_new) // + новые диапазоны уже кончились
							result.insert(Range(it_old.first, it_old.second));
					}
					else
					{
						// старый левым краем лежит внутри нового, а правый край старого за пределами нового
						// берём правый конец нового до правого конца старого и помещаем в Устаревший
						result.insert(Range(it_new->second + 1, it_old.second));
					}
				}
				else // (**) && (it_old.second <= it_new.second)
				{
					// старый левым краем лежит внутри нового, и правым тоже лежит в новом 
					// никуда его не добавляем
				}
			}
		}
	}
	else
	{
		Pool::const_iterator it_old = old_pool.begin();
		uint32_t num_it_old = 1;
		uint32_t left_old = 0;
		uint32_t right_old = 0;

		for (const auto &it_new : new_pool)
		{
			// случай когда новый диапазон за пределами старого слева
			//if (it->first < _r.first && _r.second < it->second)
			if ((it_new.first < it_old->first) && (it_new.second < it_old->first))
				continue;

			// случай полного вхождения старого диапазона в новый [...___...]
			//if (_r.first < it->first && _r.second > it->second)
			if ((it_new.first <= it_old->first) && (it_new.second >= it_old->second))
			{
				if (size_pool_old > num_it_old)
				{
					num_it_old++;
					it_old++;
				}
			}
			                                                   //    ____
			// случай частичного вхождения старого в новый слева [.....]
			if ((it_new.first <= it_old->first) && (it_old->first <= it_new.second && it_new.second <= it_old->second))
			{
				//result.insert(Range(it_new.second, it_old->second));
				left_old = it_new.second + 1;
			}

			// случай полного вхождения нового диапазона в старый [___...___]
			if ((it_old->first < it_new.first) && (it_new.second < it_old->second))
			{
				if (left_old > 0)
				{
					right_old = it_new.first - 1;
					result.insert(Range(left_old, right_old));
					left_old = it_new.second + 1;
					right_old = 0;
				}
			}

			// случай частичного вхождения старого в новый справа [___...]
			if (it_old->first <= it_new.first && it_new.first <= it_old->second && it_old->second <= it_new.second)
			{
				if (left_old > 0)
				{
					right_old = it_new.first - 1;
					result.insert(Range(left_old, right_old));
					left_old = right_old;
					right_old = 0;
				}
			}
			//
		}
	}

	// где-то необходимо будет пройтись по элементам и искать через find() или at() до куда есть несовпадение
	// custom = convert(begin_range); custom2 = convert(end_range); // нужо будет вставить корректную конвертацию из чисола в IP-шную тип-структуру

	return result;
}

void print_test_line(const std::string test_name)
{
	std::cout << "========================" << test_name.c_str() << "==========================" << std::endl;
}

void show_pool(const std::string pool_name, const Pool& print_pool)
{
	std::cout << pool_name.c_str() << std::endl;
	for (const auto item : print_pool)
	{
		std::cout << "[" << item.first << " : " << item.second << "]" << std::endl;
	}
	std::cout << std::endl;
}


void addAddrToPool(Pool& _pool, Range _r)
{
	if (_pool.count(_r.first) != 0) //m.count(key) == 1 //m.count(key) > 0 // found
	{
		// Тут мы используем свойство map-а, и если находятся диапазоны начинающиеся с одного и того же номера,
		// но отличающиеся правой частью диапазона, то мы оставляем тот диапазон, что больше
		// случай частичного вхождения справа с совпадающей границей [_...]
		if (_pool[_r.first] < _r.second)
		{
			_pool[_r.first] = _r.second;
		}
	}
	else
	{
		// строго говоря перед добавлением мы должны склеить все пересекающиеся пулы
		bool isAdded = false;
		auto it = _pool.begin();
		while(it != _pool.end())
		{
			// случай лишнего вхождения оного диапазона в другой (диапазон из-за повторов расширять е надо и они нам вообще не нужны) [__...__]
			if (it->first < _r.first && _r.second < it->second)
			{
				break;
			}

			// случай полного вхождения оного диапазона в другой [...___...]
			if (_r.first < it->first && _r.second > it->second)
			{
				_pool.erase(it);
				_pool.insert(_r);
				isAdded = true;
				break;
			}

			// случай частичного вхождения слева [...___]
			if (_r.first <= it->first && it->first <= _r.second && _r.second <= it->second)
			{
				Range bigger_left(_r.first, it->second);
				_pool.erase(it);
				_pool.insert(bigger_left);
				isAdded = true;
				break;
			}

			// случай частичного вхождения справа [___...]
			if (it->first <= _r.first && _r.first <= it->second && it->second <= _r.second)
			{
				Range bigger_right(it->first, _r.second);
				_pool.erase(it);
				_pool.insert(bigger_right);
				isAdded = true;
				break;
			}
			
			++it;
		}

		if( (!isAdded) && (it == _pool.end()) )
		{
			_pool.insert(_r);
		}

		// если не хотим заниматься склейкой, то можем просто вставлять:
		//_pool.insert(_r);
	}
}

//            1===3		4===6		10===12		  15=16  
//          0^1           5^^^8       11^12     13^^^16
//            1^^^3
void test_1_pools()
{
	print_test_line("test_1");

	Pool old_pool;
	addAddrToPool(old_pool, Range(0,  1));
	addAddrToPool(old_pool, Range(13, 16));
	addAddrToPool(old_pool, Range(5,  8));
	addAddrToPool(old_pool, Range(11, 12));
	addAddrToPool(old_pool, Range(1,  3));
	show_pool("old_pool", old_pool);

	Pool new_pool;
	addAddrToPool(new_pool, Range(15, 16));
	addAddrToPool(new_pool, Range(4,  6));
	addAddrToPool(new_pool, Range(1,  3));
	addAddrToPool(new_pool, Range(10, 12));
	show_pool("new_pool", new_pool);


	Pool res_pool = find_diff(old_pool, new_pool);
	show_pool("res_pool", res_pool);
}

//            11=========21						       40=========50   
//                15^16                                    45^46                      
//          10^12       20^22                        35^42       50^62                
//       8^^^^^^^^^^^^^^^^^^^^^24                   30^40        50^^^^72               
// 4^^6                           26^28      25^^35                     65^80         
	
void test_2_pools()
{
	print_test_line("test_2");

	Pool old_pool;
	addAddrToPool(old_pool, Range(4, 6));
	addAddrToPool(old_pool, Range(26, 28));
	addAddrToPool(old_pool, Range(8, 24));
	addAddrToPool(old_pool, Range(10, 12));
	addAddrToPool(old_pool, Range(20, 22));
	addAddrToPool(old_pool, Range(15, 16));

	addAddrToPool(old_pool, Range(25, 35));
	addAddrToPool(old_pool, Range(30, 40));
	addAddrToPool(old_pool, Range(50, 62));
	addAddrToPool(old_pool, Range(65, 80));
	addAddrToPool(old_pool, Range(35, 42));
	addAddrToPool(old_pool, Range(50, 72));
	addAddrToPool(old_pool, Range(45, 46));

	show_pool("old_pool", old_pool);

	Pool new_pool;
	addAddrToPool(new_pool, Range(11, 21));
	addAddrToPool(new_pool, Range(4,  6));
	addAddrToPool(new_pool, Range(40, 50));
	show_pool("new_pool", new_pool);


	Pool res_pool = find_diff(old_pool, new_pool);
	show_pool("res_pool", res_pool);
}

//                                               res =  43^44 47^49
//            11^^^^^^^^^21						       40^^^^^^^^^50   
//                15=16                                    45=46                      
//          10=12       20=22                        35=42       50=62                
//       8=====================24                   30=40        50===72               
// 4==6                           26=28      25==35                     65=80         

void test_2_reverse_pools()
{
	print_test_line("test_2_rev");

	Pool new_pool;
	addAddrToPool(new_pool, Range(4, 6));
	addAddrToPool(new_pool, Range(26, 28));
	addAddrToPool(new_pool, Range(8, 24));
	addAddrToPool(new_pool, Range(10, 12));
	addAddrToPool(new_pool, Range(20, 22));
	addAddrToPool(new_pool, Range(15, 16));

	addAddrToPool(new_pool, Range(25, 35));
	addAddrToPool(new_pool, Range(30, 40));
	addAddrToPool(new_pool, Range(50, 72));
	addAddrToPool(new_pool, Range(65, 80));
	addAddrToPool(new_pool, Range(35, 42));
	addAddrToPool(new_pool, Range(50, 62));
	addAddrToPool(new_pool, Range(45, 46));

	show_pool("new_pool", new_pool);

	Pool old_pool;
	addAddrToPool(old_pool, Range(11, 21));
	addAddrToPool(old_pool, Range(4, 6));
	addAddrToPool(old_pool, Range(40, 50));
	show_pool("old_pool", old_pool);


	Pool res_pool = find_diff(old_pool, new_pool);
	show_pool("res_pool", res_pool);
}

//                   16===========================================50
//            11=========21						          
//                15^16                                    45^46                      
//          10^12       20^22                        35^42       50^62                
//       8^^^^^^^^^^^^^^^^^^^^^24                   30^40        50^^^72               
// 4^^6                           26^28      25^^35                     65^80         

void test_3_pools()
{
	print_test_line("test_3");

	Pool old_pool;
	addAddrToPool(old_pool, Range(4, 6));
	addAddrToPool(old_pool, Range(26, 28));
	addAddrToPool(old_pool, Range(8, 24));
	addAddrToPool(old_pool, Range(10, 12));
	addAddrToPool(old_pool, Range(20, 22));
	addAddrToPool(old_pool, Range(15, 16));

	addAddrToPool(old_pool, Range(25, 35));
	addAddrToPool(old_pool, Range(30, 40));
	addAddrToPool(old_pool, Range(50, 62));
	addAddrToPool(old_pool, Range(65, 80));
	addAddrToPool(old_pool, Range(35, 42));
	addAddrToPool(old_pool, Range(50, 72));
	addAddrToPool(old_pool, Range(45, 46));

	show_pool("old_pool", old_pool);

	Pool new_pool;
	addAddrToPool(new_pool, Range(11, 21));
	addAddrToPool(new_pool, Range(4, 6));
	addAddrToPool(new_pool, Range(16, 50));
	show_pool("new_pool", new_pool);


	Pool res_pool = find_diff(old_pool, new_pool);
	show_pool("res_pool", res_pool);
}


void main()
{
	// Покачто на примере простых Чисел, а не айпиадресов
	
	test_1_pools();
	test_2_pools();
	test_2_reverse_pools();
	test_3_pools();

	getchar();
}

