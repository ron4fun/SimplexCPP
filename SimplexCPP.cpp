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

#include <iostream>
#include "Simplex.h"

using namespace std;

void check(const fraction &expected, const fraction &result) 
{ 
	if (expected != result)
	{
		ostringstream s;
		s << "Expected " << expected << " but got " << result;
		throw runtime_error(s.str());
	}
};

// Test vectors were gotten from -
//
// ADVANCED ENGINEERING MATHEMATICS (K.A STRAUD) 4th Edition
// Programme 23 - Optimization and linear programming 
// Page 940
//
int main()
{
	MATRIX problem;
	S_RESULTS result;

	// 2 Problem Variables  & 2 Slack Variables

	// problem setup
	problem = {
		LINE("w1", { -1, 2, 1, 0, 6 }),
		LINE("w2", { 5, 4, 0, 1, 40 }),
		LINE("P", { -1, -4, 0, 0, 0 })
	};
		
	result = Simplex::SolveEq(problem, 2);

	check(4, result.GetValue("x1"));
	check(5, result.GetValue("x2"));
	check(24, result.GetValue("Pmax"));

	// 2 Problem Variables & 3 Slack Variables
	
	// 1 - problem setup
	problem = {
		LINE("w1", { 0, 1, 1, 0, 0, 3 }),
		LINE("w2", { 1, 1, 0, 1, 0, 5 }),
		LINE("w3", { 1, -2, 0, 0, 1, 2 }),
		LINE("P", { -1, -2, 0, 0, 0, 0 })
	};

	result = Simplex::SolveEq(problem, 2);

	check(2, result.GetValue("x1"));
	check(3, result.GetValue("x2"));
	check(6, result.GetValue("w3"));
	check(8, result.GetValue("Pmax"));

	// 2 - problem setup
	problem = {
		LINE("w1", { -1, 1, 1, 0, 0, 4 }),
		LINE("w2", { 1, 2, 0, 1, 0, 14 }),
		LINE("w3", { 2, 1, 0, 0, 1, 16 }),
		LINE("P", { -4, -3, 0, 0, 0, 0 })
	};
	
	result = Simplex::SolveEq(problem, 2);

	check(6, result.GetValue("x1"));
	check(4, result.GetValue("x2"));
	check(6, result.GetValue("w1"));
	check(36, result.GetValue("Pmax"));

	// 3 - problem setup
	problem = {
		LINE("w1", { 2, 1, 1, 0, 0, 150 }),
		LINE("w2", { 4, 3, 0, 1, 0, 350 }),
		LINE("w3", { 1, 1, 0, 0, -1, 80 }),
		LINE("P", { -7, -4, 0, 0, 0, 0 })
	};
	
	result = Simplex::SolveEq(problem, 2);

	check(50, result.GetValue("x1"));
	check(50, result.GetValue("x2"));
	check(20, result.GetValue("w3"));
	check(550, result.GetValue("Pmax"));

	// 3 Problem Variables & 3 Slack Variables
	
	// 1 - problem setup
	problem = {
		LINE("w1", { 2, 5, 2, 1, 0, 0, 38 }),
		LINE("w2", { 4, 2, 3, 0, 1, 0, 57 }),
		LINE("w3", { 1, 3, 5, 0, 0, 1, 57 }),
		LINE("P", { -2, -6, -4, 0, 0, 0, 0 })
	};

	result = Simplex::SolveEq(problem, 3);

	check(0, result.GetValue("x1"));
	check(4, result.GetValue("x2"));
	check(9, result.GetValue("x3"));
	check(60, result.GetValue("Pmax"));

	// 2 - problem setup
	problem = {
		LINE("w1", { 2, 3, 1, 0, 0, 0, 120 }),
		LINE("w2", { 1, 1, 0, 1, 0, 0, 45 }),
		LINE("w3", { -3, 5, 0, 0, -1, 1, 25 }),
		LINE("P", { -8, -4, 0, 0, 0, 1, 0 })
	};

	result = Simplex::SolveEq(problem, 3);

	check(25, result.GetValue("x1"));
	check(20, result.GetValue("x2"));
	check(10, result.GetValue("x3"));
	check(280, result.GetValue("Pmax"));

	// 3 Problem Variables & 4 Slack Variables
	
	// problem setup

	problem = {
		LINE("w1", { 2, 1, 2, 1, 0, 0, 0, 98 }),
		LINE("w2", { 1, 1, 1, 0, 1, 0, 0, 60 }),
		LINE("w3", { 3, 4, 2, 0, 0, 1, 0, 145 }),
		LINE("w4", { 4, 3, 2, 0, 0, 0, 1, 160 }),
		LINE("P", { -84, -72, -52, 0, 0, 0, 0, 0 })
	};

	result = Simplex::SolveEq(problem, 3);

	check(23, result.GetValue("x1"));
	check(8, result.GetValue("x2"));
	check(22, result.GetValue("x3"));
	check(7, result.GetValue("w2"));
	check(3652, result.GetValue("Pmax"));

	//
    cout << "All tests ran successfully!" << endl;
}