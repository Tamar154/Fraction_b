#pragma once

#include <iostream>
const int ACC_FACTOR = 1000.0;

namespace ariel
{

    class Fraction
    {

    private:
        int _numerator;
        int _denominator;

    public:
        /*
        Constructors
         */
        Fraction();
        Fraction(const int &, const int &);
        Fraction(const float &);

        /*
            Getters
        */
        int getNumerator() const { return _numerator; }

        int getDenominator() const { return _denominator; }

        /*
            + oprator
        */
        Fraction operator+(const Fraction &other) const;
        Fraction operator+(const float &flo) const;
        friend Fraction operator+(const float &flo, const Fraction &frac) { return frac + flo; }

        /*
            - oprator
        */
        Fraction operator-(const Fraction &other) const;
        Fraction operator-(const float &flo) const;
        friend Fraction operator-(const float &flo, const Fraction &frac)
        {
            Fraction ans = frac - flo;
            ans._numerator = -ans._numerator;
            return ans;
        }

        /*
         * oprator
         */
        Fraction operator*(const Fraction &other) const;
        Fraction operator*(const float &flo) const;
        friend Fraction operator*(const float &flo, const Fraction &frac) { return frac * flo; }

        /*
            / oprator
        */
        Fraction operator/(const Fraction &other) const;
        Fraction operator/(const float &flo) const;
        friend Fraction operator/(const float &flo, const Fraction &frac)
        {
            Fraction frac1(flo);
            return frac1 / frac;
        }

        /*
            == oprator
        */
        bool operator==(const Fraction &other) const;
        bool operator==(const float &flo) const;
        friend bool operator==(const float &flo, const Fraction &frac) { return frac == flo; }

        /*
            > oprator
        */
        bool operator>(const Fraction &other) const;
        bool operator>(const float &flo) const;
        friend bool operator>(const float &flo, const Fraction &frac)
        {
            return Fraction(flo) > frac;
        }

        /*
            < oprator
         */
        bool operator<(const Fraction &other) const { return other > *this; }
        bool operator<(const float &flo) const { return flo > *this; }
        friend bool operator<(const float &flo, const Fraction &frac)
        {
            return frac > flo;
        }

        /*
            >= oprator
        */
        bool operator>=(const Fraction &other) const { return (*this > other) || (*this == other); }
        bool operator>=(const float &flo) const { return (*this > flo) || (*this == flo); }
        friend bool operator>=(const float &flo, const Fraction &frac) { return (flo > frac) || (flo == frac); }

        /*
            <= oprator
        */
        bool operator<=(const Fraction &other) const { return (*this < other) || (*this == other); }
        bool operator<=(const float &flo) const { return (*this < flo) || (*this == flo); }
        friend bool operator<=(const float &flo, const Fraction &frac) { return (flo < frac) || (flo == frac); }

        /*
          ++ oprator
        */
        Fraction operator++();
        Fraction operator++(int postfix);

        /*
           -- oprator
         */
        Fraction operator--();
        Fraction operator--(int postfix);

        /*
           << oprator
         */
        friend std::ostream &operator<<(std::ostream &output, const Fraction &frac);
        friend std::ostream &operator<<(std::ostream &output, float &flo);

        /*
           >> oprator
         */
        friend std::istream &operator>>(std::istream &input, Fraction &frac);
        friend std::istream &operator>>(std::istream &input, float &flo);

        void reduceFrac(); // friend??
        static float floatThreeDecimalAcc(float flo)
        {
            // std::cout << (int)(flo * 1000) / 1000.0 << std::endl;
            return static_cast<int>(flo * ACC_FACTOR) / static_cast<float>(ACC_FACTOR);

        } // friend??
    };

}