#Fraction Class#


A C++ Implementation of fraction class like the one in python and added features


Example
---------



    
    #include <iostream>
    using namespace std;
     
	#include "fraction.h"

    int main()
	{
	    fraction f(1,5);
	    fraction f2 = f.inverse();
	    fraction f3 = f * 6;
	    fraction f4(23, 57);
	    fraction f5 = f;
	    const fraction f6(4,8);
	    fraction f7(-28);
	    fraction f8(0);
	
	    cout << f << " + " << f2 << " = " << f+f2 << endl;
	    cout << f << " * " << 6 << " = " << f3 << endl;
	    cout << "(" << f4 << ")^5 = " << f4.pow(5) << endl;
	    cout << f5 << " > " << f2 << " : " << (f5 > f2) << endl;
	    cout << f4 << " -= 1 : ";
	    f4 -= 1;
	    cout << f4 << endl;
	    cout << "(" << f << ")++  : ";
	    ++f;
	    cout << f << endl;
	    cout << f5 << " * " << f4 << " = " << f5*f4 << endl;
	    cout << "(" << f6 << ")^3 = " << f6.pow(3) << endl;
	
	    cout << "f7.inverse() = " << f7.inverse() << endl;
	    cout << "f8 = " << f8 << endl;
	    cout << "f6 = " << f6 << endl << "f6.inverse() = " << f6.inverse() << endl;
	
	    return 0;
	} // end func main

Note
------

	The fraction class is purposefully made to be within the <int> range and if 
	need be it can be extended to support big integer values.
	

License
----------
    Copyright (c) 2015 - 2021 Mbadiwe Nnaemeka Ronald ron2tele@gmail.com

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
    
    3. This notice must not be removed or altered from any source distribution.
        
        