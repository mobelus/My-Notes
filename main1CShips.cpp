/*
Имеем сетку из  m x n  позиций, для игры в морской бой.
корабли не могут располагаться по диагонали.
На сетке расположено сколько-то кораблей
как вертикальных, так и горизонтальных, так и одиночных.

Задача: Написать функцию подсчёта кораблей на поле.
*/

#include <vector>

void main()
{
	const int v = 6;
	const int h = 6;

	/*
	bool s[v][h] // 6 ships
	{
		 1,1,0,1,0,1
		,0,0,0,1,0,1
		,1,0,1,0,0,1
		,0,0,0,0,0,1
		,1,1,1,1,1,0
	};
	*/

	std::vector<bool> v_h; // 6 ships
	std::vector<std::vector<bool>> s; // 6 ships
	v_h = { 1,1,0,1,0,1 };	s.push_back(v_h); v_h.clear();
	v_h = { 0,0,0,1,0,1 };	s.push_back(v_h); v_h.clear();
	v_h = { 1,0,1,0,0,1 };	s.push_back(v_h); v_h.clear();
	v_h = { 0,0,0,0,0,1 };	s.push_back(v_h); v_h.clear();
	v_h = { 1,1,1,1,1,0 };	s.push_back(v_h); v_h.clear();

	int ships = 0;

	bool v_found = false, lastv_found = false, lasth_found = false;

	std::vector<bool> v_i; // indexes
	for (int i = 0; i < v - 1; i++) //m
	{
		
		for (int j = 0; j < h - 1; j++) //n
		{

		}
	}

	/*
	for (int i = 0; i < v-1; i++) //m
	{
		bool h_found = false;
		for (int j = 0; j < h-1; j++) //n
		{
			if (!s[i + 1][j] && s[i][j] && s[i][j + 1] && !h_found)	{ h_found = true; ships++; }		else  { h_found = false; }
			if (!s[i][j + 1] && s[i][j] && s[i + 1][j] && !v_found)	{ v_found = true; ships++; }		else  { v_found = false; }

			if( (j + 1) == (h - 1) )
			{
				if (!s[i][h] && s[i+1][h] && !lastv_found)			{ lastv_found = true; ships++; }	else  { lastv_found = false; }
			}
		}

		if ((i + 1) == (v - 1))
		{
			for (int k = 0; k < h - 1; k++)
			{
				if (s[v][k] && s[v + 1][k] && !lasth_found)			{ lasth_found = true; ships++; }	else { lasth_found = false; }
			}
		}
	}
	*/

	//
	int z = 0;
}