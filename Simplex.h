/*
Copyright(c) 2021 Mbadiwe Nnaemeka Ronald ron2tele@gmail.com

This software is provided 'as-is', without any express or implied
warranty.In no event will the author be held liable for any damages
arising from the use of this software.
Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter itand redistribute it
freely, subject to the following restrictions :

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software.If you use this software
in a product, an acknowledgment in the product documentation must be
specified.

2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.

3. This notice must not be removed or altered from any source distribution.
*/

#pragma once

#include <vector>
#include <ostream>
#include "include/fraction.h"

using namespace std;

typedef vector<fraction> ROW;

class LINE
{
private:
	string _key;
	ROW _row;

public:
	LINE(const string& key = "", const ROW& row = {})
		: _key(key), _row(row)
	{}

	string Key() const {
		return _key;
	}

	string& Key() {
		return _key;
	}

	ROW Row() const
	{
		return _row;
	}

	ROW& Row()
	{
		return _row;
	}
};

typedef vector<LINE> MATRIX;

class S_RESULT
{
private:
	string _key;
	fraction _value;

public:
	S_RESULT(const string &key = "", const fraction &value = fraction(0))
		: _key(key), _value(value)
	{}

	string Key() const {
		return _key;
	}

	fraction Value() const
	{
		return _value;
	}

	bool IsNull() const
	{
		return _key.length() == 0;
	}
};

class S_RESULTS
{
private:
	vector<string> keys;
	vector<S_RESULT> results;

public:
	S_RESULTS(vector<S_RESULT> res = {})
	{
		for (int i = 0; i < (int)res.size(); i++)
		{
			S_RESULT val = res[i];
			
			if (val.IsNull()) continue;

			keys.push_back(val.Key());
			results.push_back(val);
		}
	}

	void Add(const S_RESULT& value)
	{
		if (value.IsNull()) return;

		keys.push_back(value.Key());
		results.push_back(value);
	}

	S_RESULT GetResult(const string& key) const
	{
		for (int i = 0; i < (int)keys.size(); i++)
		{
			if (key == keys[i]) return results[i];
		}

		throw runtime_error("Key does not exist");
	}

	fraction GetValue(const string& key) const
	{
		for (int i = 0; i < (int)keys.size(); i++)
		{
			if (key == keys[i]) return results[i].Value();
		}

		throw runtime_error("Key does not exist");
	}

	vector<S_RESULT> GetAll() const
	{
		return results;
	}

	int Length() const
	{
		return keys.size();
	}
};

class Simplex
{
public:
	static S_RESULTS SolveEq(const MATRIX& array, const int no_variables)
	{
		bool optimal;
		int col;

		bool artificial_var = HasArtificialVariable(array, no_variables);

		MATRIX arr = SimplexEngine(array);

		while (ShouldIterate(arr)) arr = SimplexEngine(arr);
					
		if (artificial_var)
		{
			optimal = IsOptimal(arr, no_variables, col);

			while (!optimal)
			{
				arr = SimplexEngine(arr, optimal, col);
				optimal = IsOptimal(arr, no_variables, col);
			}
		}

		S_RESULTS ans;
		for (int i = 0; i < (int)arr.size(); i++)
		{
			LINE line = arr[i];
			S_RESULT res = ResolveResult(line, no_variables);
			
			ans.Add(res);
		}
		
		// clean result
		for (int i = 0; i < no_variables; i++)
		{
			ostringstream s;
			s << "x" << i + 1;
			try
			{
				ans.GetValue(s.str());
			}
			catch (exception e)
			{
				ans.Add(S_RESULT(s.str(), fraction(0)));
			}			
		}
		
		for (int i = 0; i < (int)arr.size(); i++)
		{
			ostringstream s;
			s << "w" << i + 1;
			try
			{
				ans.GetValue(s.str());
			}
			catch (exception e)
			{
				ans.Add(S_RESULT(s.str(), fraction(0)));
			}
		}

		return ans;
	}		

private:
	static MATRIX SimplexEngine(const MATRIX& _arr, const bool optimal = true, const int optimal_col = 0)
	{
		MATRIX arr = _arr;
		int key_col, key_row, pivot_row = 0, pivot_col = 0;
		ROW row, main_row;
		LINE line;
		fraction divisor, val, smallest_postive_no;

		// get the key row
		for (int i = 0; i < (int)arr.size(); i++)
		{
			line = arr[i];
			if (line.Key() == "P")
			{
				key_row = i;
				break;
			}			
		}		

		// get the key column
		if (optimal)
		{
			fraction col, min_value;
			row = arr[key_row].Row();
			for (int i = 0; i < (int)row.size(); i++)
			{
				col = row[i];
				if (col < min_value)
				{
					min_value = col;
					key_col = i;
				}
				
			}
		}
		else
		{
			key_col = optimal_col;
		}						
			
		// get the pivot
		for (int i = 0; i < (int)arr.size(); i++)
		{
			line = arr[i];
			row = line.Row();
			divisor = row[key_col];
			if (line.Key() != "P" && divisor != 0)
			{				
				fraction temp = row[row.size() - 1] / divisor;
				if (temp > 0 && smallest_postive_no == 0)
				{
					smallest_postive_no = temp;
					pivot_row = i, pivot_col = key_col;
				}
				else if (temp > 0 && temp < smallest_postive_no)
				{
					smallest_postive_no = temp;
					pivot_row = i, pivot_col = key_col;
				}				
			}			
		}		
		
		// sanitize the key row		
		val = arr[pivot_row].Row()[pivot_col];
		for (int i = 0; i < (int)arr[pivot_row].Row().size(); i++)
		{
			arr[pivot_row].Row()[i] /= val;
		}
				
		// sanitize the key col
		main_row = arr[pivot_row].Row();
		for (int i = 0; i < (int)arr.size(); i++)
		{
			line = arr[i];
			row = line.Row();
			divisor = row[key_col];
			if (line.Key() != arr[pivot_row].Key() && divisor != 0)
			{
				for (int j = 0; j < (int)row.size(); j++)
				{
					arr[i].Row()[j] -= (main_row[j] * divisor);
				}
					
			}
		}			

		return arr;
	}

	static inline bool IsOptimal(const MATRIX &arr, const int no_variables, int &col)
	{
		bool is_optimal = true;
		col = 0;

		for (int i = 0; i < (int)arr.size(); i++)
		{
			if (arr[i].Key() == "P")
			{
				ROW row = arr[i].Row();
				for (i = 0; i < no_variables; i++)
				{
					if (row[i] > 0)
					{
						col = i;
						is_optimal = false;
						break;
					}
				}

				break;
			}
			
		}

		return is_optimal;
	}
	
	static inline bool ShouldIterate(const MATRIX &arr)
	{
		bool iterate = false;

		for (int i = 0; i < (int)arr.size(); i++)
		{
			if (arr[i].Key() == "P")
			{
				ROW row = arr[i].Row();
				for (i = 0; i < (int)row.size(); i++)
				{
					if (row[i] < 0)
					{
						iterate = true;
						break;
					}
				}

				break;
			}
		}

		return iterate;
	}

	static inline bool HasArtificialVariable(const MATRIX& arr, const int no_variables)
	{
		LINE line;
		ROW row;

		for (int i = 0, j = no_variables; i < (int)arr.size(); i++, j++)
		{
			line = arr[i];
			row = line.Row();
			if (line.Key() != "P")
			{
				for (int j = no_variables; j < (int)row.size() - 1; j++) // check all slack variable for -1
				{
					if (row[j] < 0)
					{
						return true;
					}
				}
			}
		}

		return false;
	}

	static inline S_RESULT ResolveResult(const LINE &line, const int no_variables)
	{
		ROW row = line.Row();
		int pos = 0;
		ostringstream output;

		if (line.Key() == "P") return S_RESULT("Pmax", row[row.size() - 1]);
		
				
		for (int i = 0; i < (int)row.size() - 1; i++) // without the constant `b`
		{
			if (row[i] == 1)
			{
				pos = i;
				break;
			}			
		}
		
		if (pos < no_variables)
		{
			output << "x" << pos + 1;
			return S_RESULT(output.str(), row[row.size() - 1]);
		}

		if (pos >= no_variables)
		{
			output << "w" << (pos - no_variables) + 1;
			return S_RESULT(output.str(), row[row.size() - 1]);
		}

		return S_RESULT();
	}
};