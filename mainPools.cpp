#if 0

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

void show_pool(const std::string pool_name, const std::vector<Range>& print_pool)
{
	std::cout << pool_name.c_str() << std::endl;
	for (const auto item : print_pool)
	{
		std::cout << "[" << item.first << " : " << item.second << "]" << std::endl;
	}
	std::cout << std::endl;
}


void addRangeToPool(Pool& _pool, Range _r)
{
	// строго говоря перед добавлением мы должны склеить все пересекающиеся пулы
	bool isAdded = false;
	auto it = _pool.begin();
	while (it != _pool.end())
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
	
		// случай лишнего вхождения оного диапазона в другой (диапазон из-за повторов расширять не надо и они нам вообще не нужны) [__...__]
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
	
	// контейнер ещё пуст, потому добавляем элемент в контейнер
	// или мы не нашли в контейнере элемент хоть и прошли его от начала и до конца
	if ((!isAdded) && (it == _pool.end()))
	{
		_pool.insert(_r);
	}
}

Pool getOldExcludeNew(Pool& old_pool, Pool& new_pool)
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

	Pool res;

	for (const auto &it : old_pool)
	{
/*
		if (_pool.count(it.first) != 0) //m.count(key) == 1 //m.count(key) > 0 // found
		{
			// Тут мы используем свойство map-а, и если находятся диапазоны начинающиеся с одного и того же номера,
			// но отличающиеся правой частью диапазона, то мы оставляем тот диапазон, что больше
			// случай частичного вхождения справа с совпадающей границей [_...]
			if (_pool[it.first] < it.second)
			{
				_pool[it.first] = it.second;
			}
		}
		else
		{
			// строго говоря перед добавлением мы должны склеить все пересекающиеся пулы
			bool isAdded = false;
			//auto it = _pool.begin();
			//while (it != _pool.end())
			{
				// случай лишнего вхождения оного диапазона в другой (диапазон из-за повторов расширять е надо и они нам вообще не нужны) [__...__]
				if (it->first < it.first && it.second < it->second)
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

			if ((!isAdded) && (it == _pool.end()))
			{
				_pool.insert(_r);
			}

			// если не хотим заниматься склейкой, то можем просто вставлять:
			//_pool.insert(_r);
		}
*/
	}

	return res;
}

//Pool find_diff(const Pool& old_pool, const Pool& new_pool)
Pool find_diff(const std::vector<Range>& old_pool, const std::vector<Range>& new_pool)
{
	Pool old_ppool;
	Pool new_ppool;
	Pool res_ppool;

	show_pool("old_pool", old_pool);
	for (const auto &it_old : old_pool)
		addRangeToPool(old_ppool, it_old);
	show_pool("old_ppool", old_ppool);

	show_pool("new_pool", new_pool);
	for (const auto &it_new : new_pool)
		addRangeToPool(new_ppool, it_new);
	show_pool("new_ppool", new_ppool);

	return getOldExcludeNew(old_ppool, new_ppool);

}

//            1===3		4===6		10===12		  15=16  
//          0^1           5^^^8       11^12     13^^^16
//            1^^^3

void test_0_pools()
{
	print_test_line("test_0");
	int new_mas[] = { 1,3, 4,6, 10,12, 15,16 };
	int old_mas[] = { 0,1, 0,2, 0,3, 1,3, 5,8, 11,12, 13,16 };

	//Pool old_pool;
	std::vector<Range> old_pool;
	for (int i = 0, ilen = sizeof(old_mas) / sizeof(old_mas[0]); i < ilen; i += 2)
	{
		//old_pool.insert(Range(old_mas[i], old_mas[i + 1]));
		old_pool.push_back(Range(old_mas[i], old_mas[i + 1]));
	}
	show_pool("old_pool", old_pool);

	//Pool new_pool;
	std::vector<Range> new_pool;
	for (int i = 0, ilen = sizeof(new_mas) / sizeof(new_mas[0]); i < ilen; i++)
	{
		//new_pool.insert(Range(new_mas[i], new_mas[i + 1]));
		new_pool.push_back(Range(new_mas[i], new_mas[i + 1]));
	}
	show_pool("new_pool", new_pool);


	Pool res_pool = find_diff(old_pool, new_pool);
	show_pool("res_pool", res_pool);
}

/*
//            1===3		4===6		10===12		  15=16  
//          0^1           5^^^8       11^12     13^^^16
//            1^^^3
void test_1_pools()
{
	print_test_line("test_1");
	int new_mas[] = { 1,3, 4,6, 10,12, 15,16 };
	int old_mas[] = { 0,1, 1,3, 5,8, 11,12, 13,16 };

	Pool old_pool;
	for (int i = 0, ilen = sizeof(old_mas) / sizeof(old_mas[0]); i < ilen; i+=2)
	{
		old_pool.insert(Range(old_mas[i], old_mas[i+1]));
	}
	show_pool("old_pool", old_pool);

	Pool new_pool;
	for (int i = 0, ilen = sizeof(new_mas) / sizeof(new_mas[0]); i < ilen; i++)
	{
		new_pool.insert(Range(new_mas[i], new_mas[i + 1]));
	}
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
	addRangeToPool(old_pool, Range(4, 6));
	addRangeToPool(old_pool, Range(26, 28));
	addRangeToPool(old_pool, Range(8, 24));
	addRangeToPool(old_pool, Range(10, 12));
	addRangeToPool(old_pool, Range(20, 22));
	addRangeToPool(old_pool, Range(15, 16));

	addRangeToPool(old_pool, Range(25, 35));
	addRangeToPool(old_pool, Range(30, 40));
	addRangeToPool(old_pool, Range(50, 62));
	addRangeToPool(old_pool, Range(65, 80));
	addRangeToPool(old_pool, Range(35, 42));
	addRangeToPool(old_pool, Range(50, 72));
	addRangeToPool(old_pool, Range(45, 46));

	show_pool("old_pool", old_pool);

	Pool new_pool;
	addRangeToPool(new_pool, Range(11, 21));
	addRangeToPool(new_pool, Range(4,  6));
	addRangeToPool(new_pool, Range(40, 50));
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
	addRangeToPool(new_pool, Range(4, 6));
	addRangeToPool(new_pool, Range(26, 28));
	addRangeToPool(new_pool, Range(8, 24));
	addRangeToPool(new_pool, Range(10, 12));
	addRangeToPool(new_pool, Range(20, 22));
	addRangeToPool(new_pool, Range(15, 16));

	addRangeToPool(new_pool, Range(25, 35));
	addRangeToPool(new_pool, Range(30, 40));
	addRangeToPool(new_pool, Range(50, 72));
	addRangeToPool(new_pool, Range(65, 80));
	addRangeToPool(new_pool, Range(35, 42));
	addRangeToPool(new_pool, Range(50, 62));
	addRangeToPool(new_pool, Range(45, 46));

	show_pool("new_pool", new_pool);

	Pool old_pool;
	addRangeToPool(old_pool, Range(11, 21));
	addRangeToPool(old_pool, Range(4, 6));
	addRangeToPool(old_pool, Range(40, 50));
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
	addRangeToPool(old_pool, Range(4, 6));
	addRangeToPool(old_pool, Range(26, 28));
	addRangeToPool(old_pool, Range(8, 24));
	addRangeToPool(old_pool, Range(10, 12));
	addRangeToPool(old_pool, Range(20, 22));
	addRangeToPool(old_pool, Range(15, 16));

	addRangeToPool(old_pool, Range(25, 35));
	addRangeToPool(old_pool, Range(30, 40));
	addRangeToPool(old_pool, Range(50, 62));
	addRangeToPool(old_pool, Range(65, 80));
	addRangeToPool(old_pool, Range(35, 42));
	addRangeToPool(old_pool, Range(50, 72));
	addRangeToPool(old_pool, Range(45, 46));

	show_pool("old_pool", old_pool);

	Pool new_pool;
	addRangeToPool(new_pool, Range(11, 21));
	addRangeToPool(new_pool, Range(4, 6));
	addRangeToPool(new_pool, Range(16, 50));
	show_pool("new_pool", new_pool);


	Pool res_pool = find_diff(old_pool, new_pool);
	show_pool("res_pool", res_pool);
}
*/

/*
void main()
{
	// Покачто на примере простых Чисел, а не айпиадресов
	
	test_0_pools();
	//test_1_pools();
	//test_2_pools();
	//test_2_reverse_pools();
	//test_3_pools();

	getchar();
}
*/

#endif


#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <map>

using namespace std;

// Используйте следующие типы для IP-адресов, диапазонов и пулов:
using IPAddress = uint32_t; 				// Адрес IPv4 представлен целочисленным типом uint32_t
using Range = pair<IPAddress, IPAddress>;	// Диапазон IP-адресов, границы включены
using Pool  = vector<Range>;				// предложите оптимальный STL-котейнер для хранения диапазонов IP-адресов (Range)
											//using Pool = ; //? // предложите оптимальный STL-котейнер для хранения диапазонов IP-адресов (Range)
											// Диапазоны IP-адресов в пулах могут пересекаться. Порядок их расположения в пуле - произвольный.

											// Функция, вычисляющая разницу между старым и новым пулами:
											// `old_pool` - старый пул IP-адресов
											// `new_pool` - новый  пул IP-адресов
											// return value - пул диапазонов "устаревших" IP-адресов
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Ip4
{
private:
	uint8_t m_ip_1, m_ip_2, m_ip_3, m_ip_4;

public:
	Ip4() : m_ip_1(0), m_ip_2(0), m_ip_3(0), m_ip_4(0)
	{}

	Ip4(uint8_t _ip_4, uint8_t _ip_3, uint8_t _ip_2, uint8_t _ip_1)
	{
		this->m_ip_4 = _ip_4;
		this->m_ip_3 = _ip_3;
		this->m_ip_2 = _ip_2;
		this->m_ip_1 = _ip_1;
	}

	uint32_t getUint32()
	{
		return this->m_ip_1 + this->m_ip_2 * 256 + this->m_ip_3 * 256 * 256 + this->m_ip_4 * 256 * 256 * 256;
	}

	void setIp4(uint32_t _ipAddressNum)
	{
		if (_ipAddressNum)
		{
			this->m_ip_1 = _ipAddressNum >> 0;
			this->m_ip_2 = _ipAddressNum >> 8;
			this->m_ip_3 = _ipAddressNum >> 16;
			this->m_ip_4 = _ipAddressNum >> 24;
		}
	}

	void printUint32()
	{
		cout << this->getUint32() << endl;
	}

	void printIp4()
	{
		cout << this->m_ip_4 << "." << this->m_ip_3 << "." << this->m_ip_2 << "." << this->m_ip_1 << endl;
	}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool pred(IPAddress ip_1, IPAddress ip_2)
{
	return ip_1 < ip_2;
}

// fill out of   _pool_from   into    _pool_to
void fillVVectorFromPool(const Pool& _pool_from, vector<vector<IPAddress>>& _pool_to)
{
	for (auto it_range : _pool_from)
	{
		vector<IPAddress> diapason;
		for (IPAddress i = it_range.first, ilen = it_range.second; i <= ilen; i++)
			diapason.push_back(i);

		sort(diapason.begin(), diapason.end(), pred);
		_pool_to.push_back(diapason);
	}
}

// fill out of   _pool_from   into    _pool_to
void fillPoolFromVVector(vector<vector<IPAddress>>& _pool_from, Pool& _pool_to)
{
	// отработает, даже если элемент в it_vrange всего один, просто добавится диапазон [ххх ; ххх]
	for (auto it_vrange : _pool_from)
		_pool_to.push_back( Range(it_vrange[0], it_vrange[it_vrange.size() - 1]) );
}


void addRangeToPool(Pool& _pool, Range _r)
{
	// строго говоря перед добавлением мы должны склеить все пересекающиеся пулы
	// возможных вариантов вхождений / невхождений диапазонов один в другой всего 6:
	// === - новый диапазон [new_left right]
	// ^^^ - старый диапазон
	//
	//                     ===========
	//                         ^^^					1) старый внутри нового полностью
	//                   ^^^^       ^^^^			2) старый не входит в новый слева 3) старый не входит в новый справа
	//               ^^^^^^^^^^^^^^^^^^^^^^^		4) старый не сходит в новый и слева и справа
	//         ^^^^                           ^^^^	5) старый не входит целиком и лежит от новго слева 6) --..-- и лежит от нового справа
	//
	//                     ===========
	//                         ^^^					1) старый внутри нового полностью
	//                   ^^^^       ^^^^			2) старый не входит в новый слева 3) старый не входит в новый справа
	//               ^^^^^^^^^^^^^^^^^^^^^^^		4) старый не сходит в новый и слева и справа
	//         ^^^^                           ^^^^	5) старый не входит целиком и лежит от новго слева 6) --..-- и лежит от нового справа

	bool isAdded = false;
	auto it = _pool.begin();
	while (it != _pool.end())
	{
		// случай лишнего вхождения оного диапазона в другой [__...__]
		// старый полностью лежищий в старом => отбрасываем
		if (it->first < _r.first && _r.second < it->second)
		{
			break;
		}

		// случай полного вхождения оного диапазона в другой [...___...]
		if (_r.first < it->first && _r.second > it->second)
		{
			_pool.erase(it);
			_pool.insert((_r);
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

	// контейнер ещё пуст, потому добавляем элемент в контейнер
	// или мы не нашли в контейнере элемент хоть и прошли его от начала и до конца
	if ((!isAdded) && (it == _pool.end()))
	{
		_pool.insert(_r);
	}
}


// Pool = vector<pair<uint32_t, uint32_t>>
Pool find_diff(const Pool& _old_pool, const Pool& _new_pool)
{
	Pool result_pool;

	vector<vector<IPAddress>> old_pool;
	fillVVectorFromPool(_old_pool, old_pool);

	vector<vector<IPAddress>> new_pool;
	fillVVectorFromPool(_new_pool, new_pool);

	vector<vector<IPAddress>> diff_result;
	for (auto old_item : old_pool)
	{
		vector<IPAddress> diff;
		for (auto new_item : new_pool)
		{
			diff.clear();
			// make this algorythm do all the work for us //
			set_difference(old_item.begin(), old_item.end(), new_item.begin(), new_item.end(),
				inserter(diff, diff.begin()), pred);

			if (diff.size() < old_item.size())
			{
				old_item = diff;
				if (old_item.empty() || diff.empty())
					break;
			}
		}
		if (!old_item.empty())
		diff_result.push_back(old_item);
	}

	//for (auto diap : diff_result)
	//{
	//	for (auto ip : diap)
	//		cout << ip;
	//}

	fillPoolFromVVector(diff_result, result_pool);

	return result_pool;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void fillPoolFromArray(unsigned _arr_from[], size_t _arr_len, Pool& _pool_to)
{
	for (size_t i = 0, ilen = _arr_len; i < ilen; i += 2)
		_pool_to.push_back(Range(_arr_from[i], _arr_from[i + 1]));
}

//    1=3		4===6		10===12		  15=16  
//  0^1           5^^^8       11^12     13^^^16
//  0^^2
//  0^^^3
//    1^3


void test_1_pools()
{
	print_test_line("test_1");
	//unsigned new_mas[] = { 5,6, 15,18 };
	//unsigned old_mas[] = { 0,10, 10,20 };

	unsigned new_mas[] = { 1,3, 4,6, 10,12, 15,16 };
	unsigned old_mas[] = { 0,1, 0,2, 0,3, 1,3, 5,8, 11,12, 13,16 };
	size_t size_mas = 0;

	Pool old_pool;
	size_mas = (sizeof(old_mas) / sizeof(old_mas[0]));
	fillPoolFromArray(old_mas, size_mas, old_pool);
	show_pool("old_pool", old_pool);

	Pool new_pool;
	size_mas = (sizeof(new_mas) / sizeof(new_mas[0]));
	fillPoolFromArray(new_mas, size_mas, new_pool);
	show_pool("new_pool", new_pool);


	Pool res_pool = find_diff(old_pool, new_pool);
	show_pool("res_pool", res_pool);
}


void main()
{
	test_1_pools();

	getchar();
}