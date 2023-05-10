#include "Fraction.hpp"

#include <numeric>
#include <cmath>
#include <climits>

using namespace ariel;

using namespace std;

void checkOverflow(int, int, char);

// Default constructor
Fraction::Fraction() : _numerator(0), _denominator(1) {}

// Constroctor that gets two ints
Fraction::Fraction(const int &numerator, const int &denominator)
{
    if (denominator == 0)
    {
        throw invalid_argument("denominator cannot be zero!");
    }

    if (numerator < 0 && denominator < 0)
    {
        this->_numerator = -numerator;
        this->_denominator = -denominator;
    }
    else if (denominator < 0)
    {
        this->_numerator = -numerator;
        this->_denominator = -denominator;
    }
    else
    {
        this->_numerator = numerator;
        this->_denominator = denominator;
    }

    reduceFrac();
}

// Constructor that gets a float number
Fraction::Fraction(const float &num)
{
    float num_copy = floatThreeDecimalAcc(num);
    _numerator = num_copy * 1000;
    _denominator = 1000;
    reduceFrac();
}

/*
    Addition
*/
Fraction Fraction::operator+(const Fraction &other) const
{
    int numer1 = _numerator;
    int numer2 = other._numerator;
    int denom1 = _denominator;
    int denom2 = other._denominator;

    checkOverflow(denom1, denom2, '*');
    int commonDenom = denom1 * denom2;

    checkOverflow(numer1, denom2, '*');
    numer1 *= denom2;

    checkOverflow(numer2, denom1, '*');
    numer2 *= denom1;

    checkOverflow(numer1, numer2, '+');
    int numerator = numer1 + numer2;

    Fraction result(numerator, commonDenom);
    return result;
}

Fraction Fraction::operator+(const float &flo) const
{
    float accurate_flo = floatThreeDecimalAcc(flo);
    Fraction frac2(accurate_flo);
    return *this + frac2;
}

/*
    Subtraction
*/
Fraction Fraction::operator-(const Fraction &other) const
{
    int numer1 = _numerator;
    int numer2 = other._numerator;
    int denom1 = _denominator;
    int denom2 = other._denominator;

    checkOverflow(denom1, denom2, '*');
    int commonDenom = denom1 * denom2;

    checkOverflow(numer1, denom2, '*');
    numer1 *= denom2;

    checkOverflow(numer2, denom1, '*');
    numer2 *= denom1;

    checkOverflow(numer1, numer2, '-');
    int numerator = numer1 - numer2;

    Fraction result(numerator, commonDenom);
    return result;
}

Fraction Fraction::operator-(const float &flo) const
{
    float accurate_flo = floatThreeDecimalAcc(flo);
    Fraction frac2(accurate_flo);
    return *this - frac2;
}

/*
    Multiplication
*/
Fraction Fraction::operator*(const Fraction &other) const
{

    checkOverflow(this->_numerator, other._numerator, '*');
    checkOverflow(this->_denominator, other._denominator, '*');

    int numerator = this->_numerator * other._numerator;
    int denominator = this->_denominator * other._denominator;

    Fraction result(numerator, denominator);
    return result;
}

Fraction Fraction::operator*(const float &flo) const
{
    float accurate_val = floatThreeDecimalAcc(flo);
    Fraction frac2(accurate_val);
    return *this * frac2;
}

/*
    Division
*/
Fraction Fraction::operator/(const Fraction &other) const
{
    if (other._numerator == 0)
    {
        throw runtime_error("Cannot divide by zero!");
    }

    Fraction frac2(other._denominator, other._numerator);
    return *this * frac2;
}

Fraction Fraction::operator/(const float &flo) const
{
    if (flo == 0.0)
    {
        throw runtime_error("Cannot divide by zero!");
    }
    float accurate_val = floatThreeDecimalAcc(flo);
    Fraction frac2(accurate_val);
    return *this / frac2;
}

/*
    Equals
*/
bool Fraction::operator==(const Fraction &other) const
{
    bool numerEq = (this->_numerator == other._numerator);
    bool denomEq = (this->_denominator == other._denominator);
    return numerEq && denomEq;
}

bool Fraction::operator==(const float &flo) const
{
    Fraction frac(flo);
    return *this == Fraction(flo);
}

/*
    Bigger than
*/
bool Fraction::operator>(const Fraction &other) const
{
    int numer1 = this->_numerator * other._denominator;
    int numer2 = other._numerator * this->_denominator;
    return numer1 > numer2;
}

bool Fraction::operator>(const float &flo) const
{
    Fraction frac2(flo);
    return *this > frac2;
}

/*
    Increment
*/
Fraction Fraction::operator++() // prefix
{
    *this = *this + Fraction(1, 1);
    return *this;
}

Fraction Fraction::operator++(int postfix) // postfix
{
    Fraction copy = *this;
    *this = *this + Fraction(1, 1);
    return copy;
}

/*
    Decrement
*/
Fraction Fraction::operator--() // prefix
{
    *this = *this - Fraction(1, 1);
    return *this;
}

Fraction Fraction::operator--(int postfix) // postfix
{
    Fraction copy = *this;
    *this = *this - Fraction(1, 1);
    return copy;
}

/*
    Output
*/
ostream &ariel::operator<<(ostream &output, const Fraction &frac)
{
    output << frac.getNumerator() << "/" << frac.getDenominator();
    return output;
}

std::ostream &ariel::operator<<(std::ostream &output, float &flo)
{
    Fraction frac(flo);
    return output << frac;
}

/*
    Input
*/
std::istream &ariel::operator>>(std::istream &input, Fraction &frac)
{
    int numerator = 0;
    int denominator = 1;

    input >> numerator >> denominator;

    if (denominator == 0)
    {
        input.clear();
        throw runtime_error("denominator cannot be zero!");
    }

    if (!input)
    {
        throw invalid_argument("Invalid input");
    }

    Fraction temp(numerator, denominator);
    frac._numerator = temp.getNumerator();
    frac._denominator = temp.getDenominator();

    return input;
}

std::istream &ariel::operator>>(std::istream &input, float &flo)
{
    Fraction frac(flo);
    return input >> frac;
}

/*
    Helper functions
*/

// This function uses std::gcd on the fraction. if gcd!=1 then the fraction is reduced.
void Fraction::reduceFrac()
{
    int gcd_val = gcd(_numerator, _denominator);
    if (gcd_val != 1)
    {
        _numerator /= gcd_val;
        _denominator /= gcd_val;
    }
}

void checkOverflow(int a, int b, char op)
{
    switch (op)
    {
    case '+':
        if (b > 0 && a > INT_MAX - b)
            throw overflow_error("overflow occured");
        if (b < 0 && a < INT_MIN - b)
            throw overflow_error("overflow occured");
        break;

    case '-':
        if (b > 0 && a < INT_MIN + b)
            throw overflow_error("overflow occured");
        if (b < 0 && a > INT_MAX + b)
            throw overflow_error("overflow occured");
        break;

    case '*':
        if (b > 0 && (a > INT_MAX / b || a < INT_MIN / b))
            throw overflow_error("overflow occured");
        if (b < 0 && (a < INT_MAX / b || a > INT_MIN / b))
            throw overflow_error("overflow occured");
        break;
    }
}
