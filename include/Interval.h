/*
 * Interval.h
 *
 *  Created on: 7 wrz 2014
 *      Author: tomhof
 */

#ifndef INTERVAL_H_
#define INTERVAL_H_

#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <fenv.h>
#include <stdlib.h>
#include <stdint.h>
#include <cmath>
#include <mpfr.h>
#include <boost/lexical_cast.hpp>
#include <string.h>
#include <iomanip>
#include <fstream>
#include <float.h>
#include <typeinfo>

using namespace std;

namespace interval_arithmetic {

enum IAMode {
	DINT_MODE, PINT_MODE
};

enum IAPrecision {
	LONGDOUBLE_PREC = 80, DOUBLE_PREC = 60, FLOAT_PREC = 60
};

enum IAOutDigits {
	LONGDOUBLE_DIGITS = 17, DOUBLE_DIGITS = 17, FLOAT_DIGITS = 17
};

template<typename T> class Interval {
private:
	static IAPrecision precision;
	static IAOutDigits outdigits;

public:
	static IAMode mode;
	T a;
	T b;
	Interval();
	Interval(T v);
	Interval(T a, T b);
	virtual ~Interval();
	Interval<T> operator=(const Interval<T>& i);
	Interval<T> operator+(const Interval<T>& i);
	Interval<T> operator-(const Interval<T>& i);
	Interval<T> operator*(const Interval<T>& i);
	Interval<T> operator/(const Interval<T>& i);
	Interval<T> Projection();
	Interval<T> Opposite();
	Interval<T> Inverse();
	T GetWidth();
	static void Initialize();
	static Interval<T> ISqr2();
	static Interval<T> ISqr3();
	static Interval<T> IPi();
	static void SetMode(IAMode m) {mode = m; }
	static IAMode GetMode();
	static void SetPrecision(IAPrecision p);
	static IAPrecision GetPrecision(IAPrecision p);
	static void SetOutDigits(IAOutDigits o);
	static IAOutDigits GetOutDigits(IAOutDigits o);
	static Interval<T> IntRead(const string & sa);
	void IEndsToStrings(string & left, string & right);
	static T LeftRead(const string& sa);
	static T RightRead(const string& sa);
};

template<typename T> IAMode Interval<T>::mode = PINT_MODE;
template<typename T> IAPrecision Interval<T>::precision = LONGDOUBLE_PREC;
template<typename T> IAOutDigits Interval<T>::outdigits = LONGDOUBLE_DIGITS;

template<typename T>
inline Interval<T>::~Interval() {
}

template<typename T>
Interval<T>::Interval() {
	this->a = 0;
	this->b = 0;
}

template<typename T>
inline Interval<T>::Interval(T v) {
	this->a = v;
	this->b = v;
}

template<typename T>
inline Interval<T>::Interval(T a, T b) {
	this->a = a;
	this->b = b;
}

template<typename T>
inline IAMode Interval<T>::GetMode() {
	return Interval<T>::mode;
}

template<typename T>
inline Interval<T> Interval<T>::operator =(const Interval<T>& i) {
	this->a = i.a;
	this->b = i.b;

	return *this;
}

template<typename T>
inline Interval<T> Interval<T>::operator +(const Interval<T>& y) {
	Interval<T> x(this->a, this->b);
	Interval<T> r = {0, 0};
	switch (mode) {
	case PINT_MODE:
		r = IAdd(x, y);
		break;
	case DINT_MODE:
		r = DIAdd(x, y);
		break;
	default:
		r = IAdd(x, y);
		break;
	}

	return r;
}

template<typename T>
inline Interval<T> operator +(Interval<T> x, const Interval<T>& y) {
	switch (Interval<T>::mode) {
	case PINT_MODE:
		return  IAdd(x, y);
	case DINT_MODE:
		return  DIAdd(x, y);
	default:
		return IAdd(x, y);
	}
}

template<typename T>
inline Interval<T> Interval<T>::operator -(const Interval<T>& y) {
	Interval<T> x(this->a, this->b);
	Interval<T> r = {0, 0};
	switch (mode) {
	case PINT_MODE:
		r = ISub(x, y);
		break;
	case DINT_MODE:
		r = DISub(x, y);
		break;
	default:
		r = ISub(x, y);
		break;
	}

	return r;
}

template<typename T>
inline Interval<T> operator -(Interval<T> x, const Interval<T>& y) {
	switch (Interval<T>::mode) {
	case PINT_MODE:
		return  ISub(x, y);
	case DINT_MODE:
		return  DISub(x, y);
	default:
		return ISub(x, y);
	}
}


template<typename T>
inline Interval<T> Interval<T>::operator *(const Interval<T>& y) {
	Interval<T> x(this->a, this->b);
	Interval<T> r = {0, 0};
	switch (mode) {
	case PINT_MODE:
		r = IMul(x, y);
		break;
	case DINT_MODE:
		r = DIMul(x, y);
		break;
	default:
		r = IMul(x, y);
		break;
	}

	return r;
}

template<typename T>
inline Interval<T> operator *(Interval<T> x, const Interval<T>& y) {
	switch (Interval<T>::mode) {
	case PINT_MODE:
		return IMul(x, y);
	case DINT_MODE:
		return DIMul(x, y);
	default:
		return IMul(x, y);
	}
}

template<typename T>
inline Interval<T> Interval<T>::operator /(const Interval<T>& y) {
	Interval<T> x(this->a, this->b);
	Interval<T> r = {0, 0};
	switch (mode) {
	case PINT_MODE:
		r = IDiv(x, y);
		break;
	case DINT_MODE:
		r = DIDiv(x, y);
		break;
	default:
		r = IDiv(x, y);
		break;
	}

	return r;
}

template<typename T>
inline Interval<T> operator /(Interval<T> x, const Interval<T>& y) {
	switch (Interval<T>::mode) {
	case PINT_MODE:
		return IDiv(x, y);
	case DINT_MODE:
		return DIDiv(x, y);
	default:
		return IDiv(x, y);
	}
}
template<typename T>
inline void Interval<T>::SetPrecision(IAPrecision p) {
	Interval<T>::precision = p;
}

template<typename T>
inline IAPrecision Interval<T>::GetPrecision(IAPrecision p) {
	return Interval<T>::precision;
}

template<typename T>
inline void Interval<T>::SetOutDigits(IAOutDigits o) {
	Interval<T>::outdigits = LONGDOUBLE_DIGITS;
}

template<typename T>
inline IAOutDigits Interval<T>::GetOutDigits(IAOutDigits o) {
	return Interval<T>::outdigits;
}

template<typename T>
inline Interval<T> Interval<T>::IntRead(const string& sa) {
	Interval<T> r;
	mpfr_t rop;
	mpfr_init2(rop, precision);
	mpfr_set_str(rop, sa.c_str(), 10, MPFR_RNDD);
	T le = 0.0;
	if (strcmp(typeid(T).name(), typeid(long double).name()) == 0) {
		le = mpfr_get_ld(rop, MPFR_RNDD);
	}
	if (strcmp(typeid(T).name(), typeid(double).name()) == 0) {
		le = mpfr_get_d(rop, MPFR_RNDD);
	}
	if (strcmp(typeid(T).name(), typeid(float).name()) == 0) {
		le = mpfr_get_flt(rop, MPFR_RNDD);
	}

	mpfr_set_str(rop, sa.c_str(), 10, MPFR_RNDU);
	T re = 0.0;
	if (strcmp(typeid(T).name(), typeid(long double).name()) == 0) {
		re = mpfr_get_ld(rop, MPFR_RNDU);
	}
	if (strcmp(typeid(T).name(), typeid(double).name()) == 0) {
		re = mpfr_get_d(rop, MPFR_RNDU);
	}
	if (strcmp(typeid(T).name(), typeid(float).name()) == 0) {
		re = mpfr_get_flt(rop, MPFR_RNDU);
	}
	fesetround(FE_TONEAREST);

	r.a = le;
	r.b = re;
	return r;
}

template<typename T>
inline void Interval<T>::IEndsToStrings(string& left, string& right) {
	mpfr_t rop;
	mpfr_exp_t exponent;
	mpfr_init2(rop, precision);
	char* str = NULL;
	char *buffer = new char(precision + 3);
	mpfr_set_ld(rop, this->a, MPFR_RNDD);

	mpfr_get_str(buffer, &exponent, 10, outdigits, rop, MPFR_RNDD);
	str = buffer;

	stringstream ss;
	int prec = std::numeric_limits<T>::digits10;
	ss.setf(std::ios_base::scientific);
	bool minus = (str[0] == '-');
	int splitpoint = minus ? 1 : 0;
	string sign = minus ? "-" : "";

	ss << std::setprecision(prec) << sign << str[splitpoint] << "."
			<< &str[splitpoint + 1] << "E" << exponent - 1;
	left = ss.str();
	ss.str(std::string());

	mpfr_set_ld(rop, this->b, MPFR_RNDU);
	mpfr_get_str(buffer, &exponent, 10, outdigits, rop, MPFR_RNDU);
	str = buffer;
        minus = (str[0] == '-');
	splitpoint = minus ? 1 : 0;
        sign = minus ? "-" : "";
	ss << std::setprecision(prec) << sign << str[splitpoint] << "."
			<< &str[splitpoint + 1] << "E" << exponent - 1;
	right = ss.str();
	ss.clear();
}

template<typename T>
inline Interval<T> Interval<T>::Projection() {
	Interval<T> x(this->a, this->b);
	Interval<T> r;
	r = x;
	if (x.a > x.b) {
		r.a = x.b;
		r.b = x.a;
	}
	return r;
}

template<typename T>
inline Interval<T> Interval<T>::Opposite() {
	Interval<T> x(this->a, this->b);
	Interval<T> r;
	r.a = -x.a;
	r.b = -x.b;
	return r;
}

template<typename T>
inline Interval<T> Interval<T>::Inverse() {
	Interval<T> x(this->a, this->b);
	Interval<T> z1, z2;

	fesetround(FE_DOWNWARD);
	z1.a = 1 / x.a;
	z2.b = 1 / x.b;
	fesetround(FE_UPWARD);
	z1.b = 1 / x.b;
	z2.a = 1 / x.a;
	fesetround(FE_TONEAREST);
	if (DIntWidth(z1) >= DIntWidth(z2))
		return z1;
	else
		return z2;
}

template<typename T>
inline T Interval<T>::LeftRead(const string& sa) {
	Interval<T> int_number;
	int_number = IntRead(sa);
	return int_number.a;
}

template<typename T>
inline T Interval<T>::GetWidth() {
	Interval<T> x(this->a, this->b);
	switch (mode) {
	case PINT_MODE:
		return IntWidth(x);
	case DINT_MODE:
		return DIntWidth(x);
	default:
		return IntWidth(x);
	}
}

template<typename T>
inline Interval<T> Interval<T>::ISqr2() {
	string i2;
	Interval<T> r;
	i2 = "1.414213562373095048";
	r.a = LeftRead(i2);
	i2 = "1.414213562373095049";
	r.b = RightRead(i2);
	return r;
}

template<typename T>
inline Interval<T> Interval<T>::ISqr3() {
	string i2;
	Interval<T> r;
	i2 = "1.732050807568877293";
	r.a = LeftRead(i2);
	i2 = "1.732050807568877294";
	r.b = RightRead(i2);
	return r;
}

template<typename T>
inline Interval<T> Interval<T>::IPi() {
	string i2;
	Interval<T> r;
	i2 = "3.141592653589793238";
	r.a = LeftRead(i2);
	i2 = "3.141592653589793239";
	r.b = RightRead(i2);
	return r;
}

template<typename T>
inline void Interval<T>::Initialize() {
	if (strcmp(typeid(T).name(), typeid(long double).name()) == 0) {
		Interval<T>::precision = LONGDOUBLE_PREC;
		Interval<T>::outdigits = LONGDOUBLE_DIGITS;
	}

	if (strcmp(typeid(T).name(), typeid(double).name()) == 0) {
		Interval<T>::precision = DOUBLE_PREC;
		Interval<T>::outdigits = DOUBLE_DIGITS;
	}

	if (strcmp(typeid(T).name(), typeid(float).name()) == 0) {
		Interval<T>::precision = FLOAT_PREC;
		Interval<T>::outdigits = FLOAT_DIGITS;
	}
}

template<typename T>
inline T Interval<T>::RightRead(const string& sa) {
	Interval<T> int_number;
	int_number = IntRead(sa);
	return int_number.b;
}

template<typename T>
T IntWidth(const Interval<T>& x) {
	fesetround(FE_UPWARD);
	T w = x.b - x.a;
	fesetround(FE_TONEAREST);
	return w;
}

template<typename T>
T DIntWidth(const Interval<T>& x) {
	long double w1, w2;

	fesetround(FE_UPWARD);
	w1 = x.b - x.a;
	if (w1 < 0)
		w1 = -w1;
	fesetround(FE_DOWNWARD);
	w2 = x.b - x.a;
	if (w2 < 0)
		w2 = -w2;
	fesetround(FE_TONEAREST);
	if (w1 > w2)
		return w1;
	else
		return w2;
}

template<typename T>
Interval<T> ISin(const Interval<T>& x) {
	bool is_even, finished;
	int k;
	int st = 0;
	Interval<T> d, s, w, w1, x2;
	if (x.a > x.b)
		st = 1;
	else {
		s = x;
		w = x;
		x2 = IMul(x, x);
		k = 1;
		is_even = true;
		finished = false;
		st = 0;

		do {
			d.a = (k + 1) * (k + 2);
			d.b = d.a;
			s = IMul(s, IDiv(x2, d));
			if (is_even)
				w1 = ISub(w, s);
			else
				w1 = IAdd(w, s);
			if ((w.a != 0) && (w.b != 0)) {
				if ((abs(w.a - w1.a) / abs(w.a) < 1e-16)
						&& (abs(w.b - w1.b) / abs(w.b) < 1e-16))
					finished = true;
				else
					;
			} else if ((w.a == 0) && (w.b != 0)) {
				if ((abs(w.a - w1.a) < 1e-16)
						&& (abs(w.b - w1.b) / abs(w.b) < 1e-16))
					finished = true;
				else
					;
			} else if (w.a != 0) {
				if ((abs(w.a - w1.a) / abs(w.a) < 1e-16)
						& (abs(w.b - w1.b) < 1e-16))
					finished = true;
				else if ((abs(w.a - w1.a) < 1e-16) & (abs(w.b - w1.b) < 1e-16))
					finished = true;
			}

			if (finished) {
				if (w1.b > 1) {
					w1.b = 1;
					if (w1.a > 1)
						w1.a = 1;
				}
				if (w1.a < -1) {
					w1.a = -1;
					if (w1.b < -1)
						w1.b = -1;
				}
				return w1;
			} else {
				w = w1;
				k = k + 2;
				is_even = !is_even;
				if ((w.a <= 0.0)&&(w.b >=0.0))
				{
					finished = true;
					w = {0,0};
					return w;
				}
			}
		} while (!(finished || (k > INT_MAX / 2)));
	}
	if (!finished)
		st = 2;

	Interval<T> r;
	r.a = 0;
	r.b = 0;
	return r;
}

template<typename T>
Interval<T> ICos(const Interval<T>& x) {
	bool is_even, finished;
	int k;
	int st = 0;
	Interval<T> d, c, w, w1, x2;
	if (x.a > x.b)
		st = 1;
	else {
		c.a = 1;
		c.b = 1;
		w = c;
		x2 = IMul(x, x);
		k = 1;
		is_even = true;
		finished = false;
		st = 0;

		do {
			d.a = k * (k + 1);
			d.b = d.a;
			c = IMul(c, IDiv(x2, d));
			if (is_even)
				w1 = ISub(w, c);
			else
				w1 = IAdd(w, c);

			if ((w.a != 0) && (w.b != 0)) {
				if ((abs(w.a - w1.a) / abs(w.a) < 1e-18)
						&& (abs(w.b - w1.b) / abs(w.b) < 1e-18))
					finished = true;
				else
					;
			} else if ((w.a == 0) && (w.b != 0)) {
				if ((abs(w.a - w1.a) < 1e-18)
						&& (abs(w.b - w1.b) / abs(w.b) < 1e-18))
					finished = true;
				else
					;
			}

			else if (w.a != 0) {
				if ((abs(w.a - w1.a) / abs(w.a) < 1e-18)
						& (abs(w.b - w1.b) < 1e-18))
					finished = true;
				else if ((abs(w.a - w1.a) < 1e-18) & (abs(w.b - w1.b) < 1e-18))
					finished = true;
			}

			if (finished) {
				if (w1.b > 1) {
					w1.b = 1;
					if (w1.a > 1)
						w1.a = 1;
				}
				if (w1.a < -1) {
					w1.a = -1;
					if (w1.b < -1)
						w1.b = -1;
				}
				return w1;
			} else {
				w = w1;
				k = k + 2;
				is_even = !is_even;
			}
		} while (!(finished || (k > INT_MAX / 2)));
	}
	if (!finished)
		st = 2;

	Interval<T> r;
	r.a = 0;
	r.b = 0;
	return r;
}

template<typename T>
Interval<T> IExp(const Interval<T>& x) {
	bool finished;
	int k;
	int st = 0;
	Interval<T> d, e, w, w1;
	if (x.a > x.b)
		st = 1;
	else {
		e.a = 1;
		e.b = 1;
		w = e;
		k = 1;
		finished = false;
		st = 0;
		do {
			d.a = k;
			d.b = k;
			e = IMul(e, IDiv(x, d));
			w1 = IAdd(w, e);
			if ((abs(w.a - w1.a) / abs(w.a) < 1e-18)
					&& (abs(w.b - w1.b) / abs(w.b) < 1e-18)) {
				finished = true;
				return w1;
			} else {
				w = w1;
				k = k + 1;
			}
		} while (!(finished || (k > INT_MAX / 2)));
		if (!finished)
			st = 2;
	}
	Interval<T> r;
	r.a = 0;
	r.b = 0;
	return r;
}

template<typename T>
Interval<T> ISqr(const Interval<T>& x, int & st) {
	long double minx, maxx;
	Interval<T> r;
	r.a = 0;
	r.b = 0;
	if (x.a > x.b)
		st = 1;
	else {
		st = 0;
		if ((x.a <= 0) && (x.b >= 0))
			minx = 0;
		else if (x.a > 0)
			minx = x.a;
		else
			minx = x.b;
		if (abs(x.a) > abs(x.b))
			maxx = abs(x.a);
		else
			maxx = abs(x.b);
		fesetround(FE_DOWNWARD);
		r.a = minx * minx;
		fesetround(FE_UPWARD);
		r.b = maxx * maxx;
		fesetround(FE_TONEAREST);
	}
	return r;
}

template<typename T>
Interval<T> IAdd(const Interval<T>& x, const Interval<T>& y) {
	Interval<T> r;
	fesetround(FE_DOWNWARD);
	r.a = x.a + y.a;
	fesetround(FE_UPWARD);
	r.b = x.b + y.b;
	fesetround(FE_TONEAREST);
	return r;
}

template<typename T>
Interval<T> ISub(const Interval<T>& x, const Interval<T>& y) {
	Interval<T> r;
	fesetround(FE_DOWNWARD);
	r.a = x.a - y.b;
	fesetround(FE_UPWARD);
	r.b = x.b - y.a;
	fesetround(FE_TONEAREST);
	return r;
}

template<typename T>
Interval<T> IMul(const Interval<T>& x, const Interval<T>& y) {
	Interval<T> r(0, 0);
	T x1y1, x1y2, x2y1;

	fesetround(FE_DOWNWARD);
	x1y1 = x.a * y.a;
	x1y2 = x.a * y.b;
	x2y1 = x.b * y.a;
	r.a = x.b * y.b;
	if (x2y1 < r.a)
		r.a = x2y1;
	if (x1y2 < r.a)
		r.a = x1y2;
	if (x1y1 < r.a)
		r.a = x1y1;

	fesetround(FE_UPWARD);
	x1y1 = x.a * y.a;
	x1y2 = x.a * y.b;
	x2y1 = x.b * y.a;

	r.b = x.b * y.b;
	if (x2y1 > r.b)
		r.b = x2y1;
	if (x1y2 > r.b)
		r.b = x1y2;
	if (x1y1 > r.b)
		r.b = x1y1;
	fesetround(FE_TONEAREST);
	return r;
}

template<typename T>
Interval<T> IDiv(const Interval<T>& x, const Interval<T>& y) {
	Interval<T> r;
	T x1y1, x1y2, x2y1, t;

	if ((y.a <= 0) && (y.b >= 0)) {
		throw runtime_error("Division by an interval containing 0.");
	} else {
		fesetround(FE_DOWNWARD);
		x1y1 = x.a / y.a;
		x1y2 = x.a / y.b;
		x2y1 = x.b / y.a;
		r.a = x.b / y.b;
		t = r.a;
		if (x2y1 < t)
			r.a = x2y1;
		if (x1y2 < t)
			r.a = x1y2;
		if (x1y1 < t)
			r.a = x1y1;

		fesetround(FE_UPWARD);
		x1y1 = x.a / y.a;
		x1y2 = x.a / y.b;
		x2y1 = x.b / y.a;

		r.b = x.b / y.b;
		t = r.b;
		if (x2y1 > t)
			r.b = x2y1;
		if (x1y2 > t)
			r.b = x1y2;
		if (x1y1 > t)
			r.b = x1y1;

	}
	fesetround(FE_TONEAREST);
	return r;
}

template<typename T>
Interval<T> DIAdd(const Interval<T>& x, const Interval<T>& y) {
	Interval<T> z1, z2;
	if ((x.a <= x.b) && (y.a <= y.b)) {
		return IAdd(x, y);
	} else {
		fesetround(FE_DOWNWARD);
		z1.a = x.a + y.a;
		z2.b = x.b + y.b;
		fesetround(FE_UPWARD);
		z1.b = x.b + y.b;
		z2.a = x.a + y.a;
		fesetround(FE_TONEAREST);
		if (z1.GetWidth() >= z2.GetWidth())
			return z1;
		else
			return z2;
	}
}

template<typename T>
Interval<T> DISub(const Interval<T>& x, const Interval<T>& y) {
	Interval<T> z1, z2;
	if ((x.a <= x.b) && (y.a <= y.b)) {
		return ISub(x, y);
	} else {
		fesetround(FE_DOWNWARD);
		z1.a = x.a - y.b;
		z2.b = x.b - y.a;
		fesetround(FE_UPWARD);
		z1.b = x.b - y.a;
		z2.a = x.a - y.b;
		fesetround(FE_TONEAREST);
		if (z1.GetWidth() >= z2.GetWidth())
			return z1;
		else
			return z2;
	}
}

template<typename T>
Interval<T> DIMul(const Interval<T>& x, const Interval<T>& y) {
	Interval<T> z1, z2, r;
	long double z;
	bool xn, xp, yn, yp, zero;

	if ((x.a <= x.b) && (y.a <= y.b))
		r = IMul(x, y);
	else {
		xn = (x.a < 0) and (x.b < 0);
		xp = (x.a > 0) and (x.b > 0);
		yn = (y.a < 0) and (y.b < 0);
		yp = (y.a > 0) and (y.b > 0);
		zero = false;
		// A, B in H-T
		if ((xn || xp) && (yn || yp))
			if (xp && yp) {
				fesetround(FE_DOWNWARD);
				z1.a = x.a * y.a;
				z2.b = x.b * y.b;
				fesetround(FE_UPWARD);
				z1.b = x.b * y.b;
				z2.a = x.a * y.a;
			} else if (xp && yn) {
				fesetround(FE_DOWNWARD);
				z1.a = x.b * y.a;
				z2.b = x.a * y.b;
				fesetround(FE_UPWARD);
				z1.b = x.a * y.b;
				z2.a = x.b * y.a;
			} else if (xn && yp) {
				fesetround(FE_DOWNWARD);
				z1.a = x.a * y.b;
				z2.b = x.b * y.a;
				fesetround(FE_UPWARD);
				z1.b = x.b * y.a;
				z2.a = x.a * y.b;
			} else {
				fesetround(FE_DOWNWARD);
				z1.a = x.b * y.b;
				z2.b = x.a * y.a;
				fesetround(FE_UPWARD);
				z1.b = x.a * y.a;
				z2.a = x.b * y.b;
			}
		// A in H-T, B in T
		else if ((xn || xp)
				&& (((y.a <= 0) && (y.b >= 0)) || ((y.a >= 0) && (y.b <= 0))))
			if (xp && (y.a <= y.b)) {
				fesetround(FE_DOWNWARD);
				z1.a = x.b * y.a;
				z2.b = x.b * y.b;
				fesetround(FE_UPWARD);
				z1.b = x.b * y.b;
				z2.a = x.b * y.a;
			} else if (xp && (y.a > y.b)) {
				fesetround(FE_DOWNWARD);
				z1.a = x.a * y.a;
				z2.b = x.a * y.b;
				fesetround(FE_UPWARD);
				z1.b = x.a * y.b;
				z2.a = x.a * y.a;
			} else if (xn && (y.a <= y.b)) {
				fesetround(FE_DOWNWARD);
				z1.a = x.a * y.b;
				z2.b = x.a * y.a;
				fesetround(FE_UPWARD);
				z1.b = x.a * y.a;
				z2.a = x.a * y.b;
			} else {
				fesetround(FE_DOWNWARD);
				z1.a = x.b * y.b;
				z2.b = x.b * y.a;
				fesetround(FE_UPWARD);
				z1.b = x.b * y.a;
				z2.a = x.b * y.b;
			}
		// A in T, B in H-T
		else if ((((x.a <= 0) && (x.b >= 0)) || ((x.a >= 0) && (x.b <= 0)))
				&& (yn || yp))
			if ((x.a <= x.b) && yp) {
				fesetround(FE_DOWNWARD);
				z1.a = x.a * y.b;
				z2.b = x.b * y.b;
				fesetround(FE_UPWARD);
				z1.b = x.b * y.b;
				z2.a = x.a * y.b;
			} else if ((x.a <= 0) && yn) {
				fesetround(FE_DOWNWARD);
				z1.a = x.b * y.a;
				z2.b = x.a * y.a;
				fesetround(FE_UPWARD);
				z1.b = x.a * y.a;
				z2.a = x.b * y.a;
			} else if ((x.a > x.b) && yp) {
				fesetround(FE_DOWNWARD);
				z1.a = x.a * y.a;
				z2.b = x.b * y.a;
				fesetround(FE_UPWARD);
				z1.b = x.b * y.a;
				z2.a = x.a * y.a;
			} else {
				fesetround(FE_DOWNWARD);
				z1.a = x.b * y.b;
				z2.b = x.a * y.b;
				fesetround(FE_UPWARD);
				z1.b = x.a * y.b;
				z2.a = x.b * y.b;
			}
		// A, B in Z-
		else if ((x.a >= 0) && (x.b <= 0) && (y.a >= 0) && (y.b <= 0)) {
			fesetround(FE_DOWNWARD);
			z1.a = x.a * y.a;
			z = x.b * y.b;
			if (z1.a < z)
				z1.a = z;
			z2.b = x.a * y.b;
			z = x.b * y.a;
			if (z < z2.b)
				z2.b = z;
			fesetround(FE_UPWARD);
			z1.b = x.a * y.b;
			z = x.b * y.a;
			if (z < z1.b)
				z1.b = z;
			z2.a = x.a * y.a;
			z = x.b * y.b;
			if (z2.a < z)
				z2.a = z;
		}
		// A in Z and B in Z- or A in Z- and B in Z
		else
			zero = true;
		if (zero) {
			r.a = 0;
			r.b = 0;
		} else if (z1.GetWidth() >= z2.GetWidth())
			r = z1;
		else
			r = z2;
	}

	fesetround(FE_TONEAREST);
	return r;
}

template<typename T>
Interval<T> DIDiv(const Interval<T>& x, const Interval<T>& y) {
	Interval<T> z1, z2, r;
	bool xn, xp, yn, yp, zero;

	if ((x.a <= x.b) && (y.a <= y.b))
		r = IDiv(x, y);
	else {
		xn = (x.a < 0) && (x.b < 0);
		xp = (x.a > 0) && (x.b > 0);
		yn = (y.a < 0) && (y.b < 0);
		yp = (y.a > 0) && (y.b > 0);
		zero = false;
		// A, B in H-T
		if ((xn || xp) && (yn || yp))
			if (xp && yp) {
				fesetround(FE_DOWNWARD);
				z1.a = x.a / y.b;
				z2.b = x.b / y.a;
				fesetround(FE_UPWARD);
				z1.b = x.b / y.a;
				z2.a = x.a / y.b;
			} else if (xp && yn) {
				fesetround(FE_DOWNWARD);
				z1.a = x.b / y.b;
				z2.b = x.a / y.a;
				fesetround(FE_UPWARD);
				z1.b = x.a / y.a;
				z2.a = x.b / y.b;
			} else if (xn && yp) {
				fesetround(FE_DOWNWARD);
				z1.a = x.a / y.a;
				z2.b = x.b / y.b;
				fesetround(FE_UPWARD);
				z1.b = x.b / y.b;
				z2.a = x.a / y.a;
			} else {
				fesetround(FE_DOWNWARD);
				z1.a = x.b / y.a;
				z2.b = x.a / y.b;
				fesetround(FE_UPWARD);
				z1.b = x.a / y.b;
				z2.a = x.b / y.a;
			}
		// A in T, B in H-T
		else if (((x.a <= 0) && (x.b >= 0))
				|| (((x.a >= 0) && (x.b <= 0)) && (yn || yp)))
			if ((x.a <= x.b) && yp) {
				fesetround(FE_DOWNWARD);
				z1.a = x.a / y.a;
				z2.b = x.b / y.a;
				fesetround(FE_UPWARD);
				z1.b = x.b / y.a;
				z2.a = x.a / y.a;
			} else if ((x.a <= x.b) && yn) {
				fesetround(FE_DOWNWARD);
				z1.a = x.b / y.b;
				z2.b = x.a / y.b;
				fesetround(FE_UPWARD);
				z1.b = x.a / y.b;
				z2.a = x.b / y.b;
			} else if ((x.a > x.b) && yp) {
				fesetround(FE_DOWNWARD);
				z1.a = x.a / y.b;
				z2.b = x.b / y.b;
				fesetround(FE_UPWARD);
				z1.b = x.b / y.b;
				z2.a = x.a / y.b;
			} else {
				fesetround(FE_DOWNWARD);
				z1.a = x.b / y.a;
				z2.b = x.a / y.a;
				fesetround(FE_UPWARD);
				z1.b = x.a / y.a;
				z2.a = x.b / y.a;
			}
		else
			zero = true;
		if (zero)
			throw runtime_error("Division by an interval containing 0.");
		else if (z1.GetWidth() >= z2.GetWidth())
			r = z1;
		else
			r = z2;
		fesetround(FE_TONEAREST);
	}
	return r;
}

template<typename T>
Interval<T> DISin(const Interval<T>& x) {
	bool is_even, finished;
	int k;
	int st = 0;
	Interval<T> d, s, w, w1, x2;
	if (x.a > x.b)
		st = 1;
	else {
		s = x;
		w = x;
		x2 = DIMul(x, x);
		k = 1;
		is_even = true;
		finished = false;
		st = 0;

		do {
			d.a = (k + 1) * (k + 2);
			d.b = d.a;
			s = DIMul(s, DIDiv(x2, d));
			if (is_even)
				w1 = DISub(w, s);
			else
				w1 = DIAdd(w, s);
			if ((w.a != 0) && (w.b != 0)) {
				if ((abs(w.a - w1.a) / abs(w.a) < 1e-18)
						&& (abs(w.b - w1.b) / abs(w.b) < 1e-18))
					finished = true;
				else
					;
			} else if ((w.a == 0) && (w.b != 0)) {
				if ((abs(w.a - w1.a) < 1e-18)
						&& (abs(w.b - w1.b) / abs(w.b) < 1e-18))
					finished = true;
				else
					;
			}

			else if (w.a != 0) {
				if ((abs(w.a - w1.a) / abs(w.a) < 1e-18)
						& (abs(w.b - w1.b) < 1e-18))
					finished = true;
				else if ((abs(w.a - w1.a) < 1e-18) & (abs(w.b - w1.b) < 1e-18))
					finished = true;
			}

			if (finished) {
				if (w1.b > 1) {
					w1.b = 1;
					if (w1.a > 1)
						w1.a = 1;
				}
				if (w1.a < -1) {
					w1.a = -1;
					if (w1.b < -1)
						w1.b = -1;
				}
				return w1;
			} else {
				w = w1;
				k = k + 2;
				is_even = !is_even;
			}
		} while (!(finished || (k > INT_MAX / 2)));
	}
	if (!finished)
		st = 2;

	Interval<T> r;
	r.a = 0;
	r.b = 0;
	return r;
}

template<typename T>
Interval<T> DICos(const Interval<T>& x, int & st) {
	bool is_even, finished;
	int k;
	Interval<T> d, c, w, w1, x2;
	if (x.a > x.b)
		st = 1;
	else {
		c.a = 1;
		c.b = 1;
		w = c;
		x2 = DIMul(x, x);
		k = 1;
		is_even = true;
		finished = false;
		st = 0;

		do {
			d.a = k * (k + 1);
			d.b = d.a;
			c = DIMul(c, DIDiv(x2, d));
			if (is_even)
				w1 = DISub(w, c);
			else
				w1 = DIAdd(w, c);

			if ((w.a != 0) && (w.b != 0)) {
				if ((abs(w.a - w1.a) / abs(w.a) < 1e-18)
						&& (abs(w.b - w1.b) / abs(w.b) < 1e-18))
					finished = true;
				else
					;
			} else if ((w.a == 0) && (w.b != 0)) {
				if ((abs(w.a - w1.a) < 1e-18)
						&& (abs(w.b - w1.b) / abs(w.b) < 1e-18))
					finished = true;
				else
					;
			}

			else if (w.a != 0) {
				if ((abs(w.a - w1.a) / abs(w.a) < 1e-18)
						& (abs(w.b - w1.b) < 1e-18))
					finished = true;
				else if ((abs(w.a - w1.a) < 1e-18) & (abs(w.b - w1.b) < 1e-18))
					finished = true;
			}

			if (finished) {
				if (w1.b > 1) {
					w1.b = 1;
					if (w1.a > 1)
						w1.a = 1;
				}
				if (w1.a < -1) {
					w1.a = -1;
					if (w1.b < -1)
						w1.b = -1;
				}
				return w1;
			} else {
				w = w1;
				k = k + 2;
				is_even = !is_even;
			}
		} while (!(finished || (k > INT_MAX / 2)));
	}
	if (!finished)
		st = 2;

	Interval<T> r;
	r.a = 0;
	r.b = 0;
	return r;
}

template<typename T>
Interval<T> DIExp(const Interval<T>& x) {
	bool finished;
	int k;
	int st = 0;
	Interval<T> d, e, w, w1;
	if (x.a > x.b)
		st = 1;
	else {
		e.a = 1;
		e.b = 1;
		w = e;
		k = 1;
		finished = false;
		st = 0;
		do {
			d.a = k;
			d.b = k;
			e = IMul(e, DIDiv(x, d));
			w1 = DIAdd(w, e);
			if ((abs(w.a - w1.a) / abs(w.a) < 1e-18)
					&& (abs(w.b - w1.b) / abs(w.b) < 1e-18)) {
				finished = true;
				return w1;
			} else {
				w = w1;
				k = k + 1;
			}
		} while (!(finished || (k > INT_MAX / 2)));
		if (!finished)
			st = 2;
	}
	Interval<T> r;
	r.a = 0;
	r.b = 0;
	return r;
}

template<typename T>
Interval<T> DISqr(const Interval<T>& x) {
	long double minx, maxx;
	int st = 0;
	Interval<T> r;
	r.a = 0;
	r.b = 0;
	if (x.a > x.b)
		st = 1;
	else {
		st = 0;
		if ((x.a <= 0) && (x.b >= 0))
			minx = 0;
		else if (x.a > 0)
			minx = x.a;
		else
			minx = x.b;
		if (abs(x.a) > abs(x.b))
			maxx = abs(x.a);
		else
			maxx = abs(x.b);
		fesetround(FE_DOWNWARD);
		r.a = minx * minx;
		fesetround(FE_UPWARD);
		r.b = maxx * maxx;
		fesetround(FE_TONEAREST);
	}
	return r;
}

//The explicit instantiation part
template class Interval<long double>;

} /* namespace interval_arithmetic */

#endif /* INTERVAL_H_ */
