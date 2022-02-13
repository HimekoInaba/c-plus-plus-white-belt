#include <iostream>
#include <set>

using namespace std;

int gcd (int a, int b) {
    if (b == 0)
        return a;
    else
        return gcd (b, a % b);
}

class Rational {
public:
    Rational() {
        numerator = 0;
        denominator = 1;
    }

    Rational(int numerator, int denominator) {
        if (denominator == 0) {
            throw invalid_argument("denominator can not be 0");
        }

        int res = abs(gcd(numerator, denominator));
        if (denominator < 0){
            numerator *= -1;
            denominator *= -1;
        }

        this->numerator = numerator / res;
        this->denominator = denominator / res;
    }

    int Numerator() const {
        return this->numerator;
    }

    int Denominator() const {
        return this->denominator;
    }
private:
    int numerator, denominator;
};

Rational operator + (const Rational& a, const Rational& b) {
    int lcd = (a.Denominator() / gcd(a.Denominator(), b.Denominator())) * b.Denominator();
    return {
            (a.Numerator() * (lcd / a.Denominator())) + (b.Numerator() * (lcd / b.Denominator())),
            lcd
    };
}

Rational operator - (const Rational& a,const Rational& b) {
    int lcd = (a.Denominator() / gcd(a.Denominator(), b.Denominator())) * b.Denominator();
    return {
            (a.Numerator() * (lcd / a.Denominator())) - (b.Numerator() * (lcd / b.Denominator())),
            lcd
    };
}

Rational operator * (const Rational& a, const Rational& b) {
    return {a.Numerator() * b.Numerator(), a.Denominator() * b.Denominator()};
}

Rational operator / (const Rational& a, const Rational& b) {
    if (b.Numerator() == 0) {
        throw domain_error("dividers numerator cannot be 0");
    }
    return {a.Numerator() * b.Denominator(), a.Denominator() * b.Numerator()};
}

bool operator == (const Rational& a, const Rational& b) {
    return a.Numerator() == b.Numerator() && a.Denominator() == b.Denominator();
}

bool operator < (const Rational& a, const Rational& b) {
    int lcd = (a.Denominator() / gcd(a.Denominator(), b.Denominator())) * b.Denominator();
    int ka = lcd / a.Denominator();
    int kb = lcd / b.Denominator();
    return (a.Numerator() * ka)  < (b.Numerator() * kb);
}

ostream& operator<<(ostream& stream, const Rational& rational) {
    stream << rational.Numerator() << "/" << rational.Denominator();
    return stream;
}

istream& operator>>(istream& stream, Rational& r) {
    if (stream.eof()) {
        stream.setstate(ios::failbit);
        return stream;
    }
    int numerator, denominator;
    char separator;
    stream >> numerator >> separator >> denominator;
    if (stream.fail() || separator != '/') {
        return stream;
    }
    r = {numerator, denominator};
    return stream;
}
