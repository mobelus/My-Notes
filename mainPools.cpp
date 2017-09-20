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


// возможных вариантов вхождений / невхождений диапазонов один в другой всего 6:
// === - новый диапазон  [n1 n2]
// ^^^ - старый диапазон [o1 o2]

//                     ===========
//                         ^^^					1) старый внутри нового полностью
//                   ^^^^       ^^^^			2) старый не входит в новый слева 3) старый не входит в новый справа
//               ^^^^^^^^^^^^^^^^^^^^^^^		4) старый не сходит в новый и слева и справа
//         ^^^^                           ^^^^	5) старый не входит целиком и лежит от новго слева 6) --..-- и лежит от нового справа

// 1)  if(n1 <= o1 && n1 <= o2 && n2 >= o1 && n2 >= o2)	=> o  входит в  n
// 2)  if(n1  > o1 && n1 <= o2 && n2 >= o1 && n2 >= o2)	=> получаем часть диапазона [от о1   до n1-1]
// 3)  if(n1 <= o1 && n1 <= o2 && n2 <= o1 && n2 >  o2)	=> получаем часть диапазона [от n2+1 до   o2]
// 4)  if(n1  > o1 && n2 < o2)							=> о  перекрывает собой  n
// 5)  if(n1  > o1 && n2 < o2)							=> старый не входит целиком и лежит от новго слева
// 6)  if(n1  < o1 && n2 < o2)							=> --..-- и лежит от нового справа
//
// 1) if(it->first <= _r.first && it->first <= _r.second && it->second >= _r.first && it->second >= _r.second)	=> it  перекрывает собой  _r (_r уже или равно it)
// 2) if(it->first  > _r.first && it->first <= _r.second && it->second >= _r.first && it->second >= _r.second)	=> получаем часть диапазона [от _r.first   до it->first-1]
// 3) if(it->first <= _r.first && it->first <= _r.second && it->second <= _r.first && it->second >  _r.second)	=> получаем часть диапазона [от it->second+1 до   _r.second]
// 4) if(it->first  > _r.first && it->second < _r.second)														=> _r  перекрывает собой  it (_r больше it)
// 5+6)if( (it->first  > _r.first && it->second < _r.second) || (it->first  < _r.first && it->second < _r.second) ) 
//		=> _r находится за пределами и не пересекается с it ни с лева ни справа, ни в середине

void includeRangeToPool(Pool& _pool, Range _r)
{
	// строго говоря перед добавлением мы должны склеить все пересекающиеся диапазоны
	bool isAdded = false;
	auto it = _pool.begin();
	while (it != _pool.end())
	{
		// _r-ки нужно прикреплять к it-am или добавлять полностью в контейнер

		if (it->first <= _r.first && it->first <= _r.second && it->second >= _r.first && it->second >= _r.second)	//=> it  перекрывает собой  _r (_r уже или равно it)
		{   //отметим как добавленный, и не будем добавлять в пул
			isAdded = true; // уже содержится в каком-то диапазоне
			//break;
		}
		if (it->first > _r.first && it->first <= _r.second && it->second >= _r.first && it->second >= _r.second)	//=> получаем часть диапазона [от _r.first   до it->first-1]
		{
			//Range bigger_left(_r.first, it->second);
			//_pool.erase(it);
			//_pool.push_back(bigger_left);
			it->first = _r.first;
			isAdded = true;
			//break;
		}
		if(it->first <= _r.first && it->first <= _r.second && it->second <= _r.first && it->second >  _r.second)	//=> получаем часть диапазона [от it->second+1 до   _r.second]
		{
			//Range bigger_right(it->first, _r.second);
			//_pool.erase(it);
			//_pool.insert(bigger_right);
			it->second = _r.second;
			isAdded = true;
			//break;
		}
		if(it->first  > _r.first && it->second < _r.second)															//=> _r  перекрывает собой  it (_r больше it)
		{	//"сольём" их воедино
			it->first = _r.first;
			it->second = _r.second;
			isAdded = true;
			break;
		}
		// мы объединяем, так что то, что за пределами мы включаем в итоговый пул через  if (см. ниже за пределами цикла (*) )
		//if( (it->first  > _r.first && it->second < _r.second) || (it->first  < _r.first && it->second < _r.second) ) //=> _r находится за пределами и не пересекается с it ни с лева ни справа, ни в середине

		++it;
	}

	// добавляем элементы в кнтрейнер в случаях, когда:
	// контейнер ещё пуст
	// или мы его ни с кем не объединили, хоть и прошли его от начала и до конца
	if ((!isAdded) && (it == _pool.end())) // (*)
	{
		_pool.push_back(_r);
	}
}

void excludeRangeFromPool(Pool& _pool, Range _r)
{
	auto it = _pool.begin();
	while (it != _pool.end())
	{
		// _r-ки нужно вырезать из it-ов

		if (it->first <= _r.first && it->first <= _r.second && it->second >= _r.first && it->second >= _r.second)	//=> it  перекрывает собой  _r (_r уже или равно it)
		{   // вырежем посерёдке стоящий _r и оставим 2 куска оставшихся от it ИЛИ (...)
			if (it->first != _r.first)
			{
				Range part_left(it->first, _r.first);
				_pool.push_back(part_left);
			}
			if (it->second != _r.second)
			{
				Range part_right(_r.second, it->second);
				_pool.push_back(part_right);
			}
			_pool.erase(it); // (...) ИЛИ удалим весь элемент, ничего не добавляя, если диапазоны совпали
			break;
		}
		if (it->first > _r.first && it->first <= _r.second && it->second >= _r.first && it->second >= _r.second)	//=> оставляем [от _r.second+1   до it->second]
		{
			if (it->second != _r.second)
			{
				Range part_right(_r.second + 1, it->second);
				_pool.push_back(part_right);
			}
			_pool.erase(it);
			break;
		}
		if (it->first <= _r.first && it->first <= _r.second && it->second <= _r.first && it->second >  _r.second)	//=> получаем часть диапазона [от it->first до   _r.first - 1]
		{
			if (it->first != _r.first)
			{
				Range part_left(it->first, _r.first - 1);
				_pool.push_back(part_left);
			}
			_pool.erase(it);
			break;
		}
		if (it->first  > _r.first && it->second < _r.second)															//=> _r  перекрывает собой  it (_r больше it)
		{	// удаляем элемент полностью
			_pool.erase(it);
			break;
		}
		// мы вырезаем, а то, что за пределами мы итак не вырежем
		//if( (it->first  > _r.first && it->second < _r.second) || (it->first  < _r.first && it->second < _r.second) ) //=> _r находится за пределами и не пересекается с it ни с лева ни справа, ни в середине

		++it;
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