/*
Copyright(c) 2015 - 2021 Mbadiwe Nnaemeka Ronald ron2tele@gmail.com

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

#include "fraction.h"
#include <stdexcept>

fraction::fraction(int x, int y)
:num(x), denum(y)
{
    if (denum == 0)
        throw std::invalid_argument("zero division");

    bool isNegative = false;
    register unsigned int chk;

    // Check if numerator is negative and strip it off for now
    if(num < 0)
    {
        isNegative = true;
        num = ~num + 1;
        //num *= -1;
    } // end if
    if(denum < 0)
    {
        if (isNegative)
            isNegative = false;
        else
            isNegative = true;
        denum = ~denum + 1;
        //denum *= -1;
    } // end if

    chk = GCD(num, denum);
    do
    {
        num = num/chk;
        denum = denum/chk;
        chk = GCD(num, denum);
    } while(chk != 1 && chk != num && chk != denum);

    // if numerator was originally negative put it back
    if (isNegative)
        num = ~num + 1;
        //num *= -1;
} // end constructor

// operator functions declarations
//
bool fraction::operator==(const fraction& f) const
{
    if(f.getNumerator() != this->num || f.getDenominator() != this->denum)
        return false;
    return true;
} // end func operator==

bool fraction::operator<(const fraction& f) const
{
    double temp = double(num)/denum;
    double temp2 = double(f.getNumerator())/f.getDenominator();
    if(temp < temp2)
        return true;
    return false;
} // end func operator<

fraction fraction::operator+(const fraction& f) const // operator+, f1 + f2
{
    int fNum = f.getNumerator();
    int fDenum = f.getDenominator();
    return fraction((this->num * fDenum) + (fNum * this->denum), this->denum * fDenum);
} // end func operator+

fraction fraction::operator+(int i) const // operator+, f1 + f2
{
    fraction temp_frac(i);
    return *this + temp_frac;
} // end func operator+

fraction fraction::operator-(const fraction& f) const // operator-, f1 - f2
{
    int fNum = f.getNumerator();
    int fDenum = f.getDenominator();
    return fraction((this->num * fDenum) - (fNum * this->denum), this->denum * fDenum);
} // end func operator-

fraction fraction::operator-(int i) const // operator-, f1 - f2
{
    fraction temp_frac(i);
    return *this - temp_frac;
} // end func operator-

fraction fraction::operator*(const fraction& f) const // operator*, f1 * f2
{
    int fNum = f.getNumerator();
    int fDenum = f.getDenominator();
    return fraction(this->num * fNum, this->denum * fDenum);
} // end operator*

fraction fraction::operator*(int i) const // operator*, f1 * f2
{
    fraction temp_frac(i);
    return *this * temp_frac;
} // end operator*

fraction fraction::operator/(const fraction& f) const // operator/, f1 / f2
{
    int fNum = f.getNumerator();
    int fDenum = f.getDenominator();
    return fraction(this->num * fDenum, fNum * this->denum);
} // end operator /

fraction fraction::operator/(int i) const // operator/, f1 / f2
{
    fraction temp_frac(i);
    return *this / temp_frac;
} // end operator /

ostream &operator<<( ostream &output, const fraction &f )
{
    int num = f.getNumerator();
    int denum = f.getDenominator();

    if (denum == 1)
        output << num;
    else
        output << num << "/" << denum;

    return output; // enables cout << a << b << c;
} // end function operator<<

