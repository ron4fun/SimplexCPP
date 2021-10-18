## SimplexCPP



`SimplexCPP` is a c++ library that helps solves `Linear Programming Equations` i.e Maximization problems, easily also providing you with neat results. 


Unittest
---------
	Test vectors were gotten from -

	ADVANCED ENGINEERING MATHEMATICS (K.A STRAUD) 4th Edition
	Programme 23 - Optimization and linear programming 
	Page 940



Example
---------

```c++
#include <iostream>
#include "Simplex.h"

using namespace std;

/*
Solve using the Simplex method the following problem:
Maximize 	Z = f(x,y) = 3x + 2y
subject to: 	2x + y ≤ 18
                2x + 3y ≤ 42
                3x + y ≤ 24
                x ≥ 0 , y ≥ 0
*/
int main()
{	
    // problem setup
    MATRIX problem = {
	LINE("w1", { 2, 1, 1, 0, 0, 18 }),
	LINE("w2", { 2, 3, 0, 1, 0, 42 }),
        LINE("w3", { 3, 1, 0, 0, 1, 24 }),
	LINE("P", { -3, -2, 0, 0, 0, 0 })
    };
		
    S_RESULTS result = Simplex::SolveEq(problem, 2); // where 2 is the total number of variables

    cout << result.GetValue("Pmax") << endl; // 33

    return 0;
}
```


License
----------
    Copyright (c) 2021 Mbadiwe Nnaemeka Ronald ron2tele@gmail.com

    This software is provided 'as-is', without any express or implied
    warranty. In no event will the author be held liable for any damages
    arising from the use of this software.
    Permission is granted to anyone to use this software for any purpose,
    including commercial applications, and to alter it and redistribute it
    freely, subject to the following restrictions:
    
    1. The origin of this software must not be misrepresented; you must not
    claim that you wrote the original software. If you use this software
    in a product, an acknowledgment in the product documentation must be
    specified.
    
    2. Altered source versions must be plainly marked as such, and must not be
    misrepresented as being the original software.
    
    3. This notice may not be removed or altered from any source distribution.
        
        
