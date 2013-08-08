/*
Copyright (c) 2013 Microsoft Corporation. All rights reserved.
Released under Apache 2.0 license as described in the file LICENSE.

Author: Soonho Kong
*/
#pragma once
#include <stdint.h>
#include <mpfr.h>
#include "mpz.h"
#include "mpq.h"
#include "mpbq.h"

namespace lean {
/**
   \brief Wrapper for MPFR
*/
class mpfp {
    friend numeric_traits<mpfp>;
    mpfr_t m_val;

//    static mpfr_t const & zval(mpz const & v) { return v.m_val; }
//    static mpfr_t & zval(mpz & v) { return v.m_val; }
public:
    // friend void swap(mpfp & a, mpfp & b) { mpfr_swap(a.m_val, b.m_val); }
    // friend void swap_numerator(mpfp & a, mpz & b) { mpz_swap(mpfr_numref(a.m_val), zval(b)); mpfr_canonicalize(a.m_val); }
    // friend void swap_denominator(mpfp & a, mpz & b) { mpz_swap(mpfr_denref(a.m_val), zval(b)); mpfr_canonicalize(a.m_val); }

    // Setter functions
    mpfp & set(mpfp const & v, mpfr_rnd_t rnd = MPFR_RNDN) {
        mpfr_set(m_val, v.m_val, MPFR_RNDN); return *this;
    }
    mpfp & set(unsigned long int const v, mpfr_rnd_t rnd = MPFR_RNDN) {
        mpfr_set_ui(m_val, v, MPFR_RNDN); return *this;
    }
    mpfp & set(long int const v, mpfr_rnd_t rnd = MPFR_RNDN) {
        mpfr_set_si(m_val, v, MPFR_RNDN); return *this;
    }
    mpfp & set(float const v, mpfr_rnd_t rnd = MPFR_RNDN) {
        mpfr_set_flt(m_val, v, MPFR_RNDN); return *this;
    }
    mpfp & set(double const v, mpfr_rnd_t rnd = MPFR_RNDN) {
        mpfr_set_d(m_val, v, MPFR_RNDN); return *this;
    }
    mpfp & set(long double const v, mpfr_rnd_t rnd = MPFR_RNDN) {
        mpfr_set_ld(m_val, v, MPFR_RNDN); return *this;
    }
    mpfp & set(mpz_t const & v, mpfr_rnd_t rnd = MPFR_RNDN) {
        mpfr_set_z(m_val, v, MPFR_RNDN); return *this;
    }
    mpfp & set(mpq_t const & v, mpfr_rnd_t rnd = MPFR_RNDN) {
        mpfr_set_q(m_val, v, MPFR_RNDN); return *this;
    }
    mpfp & set(mpf_t const & v, mpfr_rnd_t rnd = MPFR_RNDN) {
        mpfr_set_f(m_val, v, MPFR_RNDN); return *this;
    }
    mpfp & set(mpz   const & v, mpfr_rnd_t rnd = MPFR_RNDN) {
        mpfr_set_z(m_val, v.m_val, MPFR_RNDN); return *this;
    }
    mpfp & set(mpq   const & v, mpfr_rnd_t rnd = MPFR_RNDN) {
        mpfr_set_q(m_val, v.m_val, MPFR_RNDN); return *this;
    }
    mpfp & set(mpbq  const & v, mpfr_rnd_t rnd = MPFR_RNDN) {
        mpfr_set_z(m_val, v.m_num.m_val, rnd);   // this = m_num
        mpfr_div_2ui(m_val, m_val, v.m_k, rnd);  // this = m_num / (2^k)
        return *this;
    }

    // Assignment operators
    mpfp & operator=(mpfp const & v)            { return set(v); }
    mpfp & operator=(unsigned long int const v) { return set(v); }
    mpfp & operator=(long int const v)          { return set(v); }
    mpfp & operator=(float const v)             { return set(v); }
    mpfp & operator=(double const v)            { return set(v); }
    mpfp & operator=(long double const v)       { return set(v); }
    mpfp & operator=(mpz_t const & v)           { return set(v); }
    mpfp & operator=(mpq_t const & v)           { return set(v); }
    mpfp & operator=(mpf_t const & v)           { return set(v); }
    mpfp & operator=(mpz   const & v)           { return set(v); }
    mpfp & operator=(mpq   const & v)           { return set(v); }
    mpfp & operator=(mpbq  const & v)           { return set(v); }

    // Basic Constructors
    mpfp() { mpfr_init(m_val); } // with default precision
    mpfp(mpfr_prec_t prec) { mpfr_init2(m_val, prec); }

    // Constructors using the default precision
    mpfp(float const v      ):mpfp() { set(v); }
    mpfp(double const v     ):mpfp() { set(v); }
    mpfp(long double const v):mpfp() { set(v); }
    mpfp(mpz_t const & v    ):mpfp() { set(v); }
    mpfp(mpq_t const & v    ):mpfp() { set(v); }
    mpfp(mpf_t const & v    ):mpfp() { set(v); }
    mpfp(mpz const & v      ):mpfp() { set(v); }
    mpfp(mpq const & v      ):mpfp() { set(v); }
    mpfp(mpbq const & v     ):mpfp() { set(v); }
    mpfp(mpfp const & v     ):mpfp(mpfr_get_prec(v.m_val)) { set(v); }

    // Constructors using the provided precision
    mpfp(float const v      , mpfr_prec_t p):mpfp(p) { set(v); }
    mpfp(double const v     , mpfr_prec_t p):mpfp(p) { set(v); }
    mpfp(long double const v, mpfr_prec_t p):mpfp(p) { set(v); }
    mpfp(mpz_t const & v    , mpfr_prec_t p):mpfp(p) { set(v); }
    mpfp(mpq_t const & v    , mpfr_prec_t p):mpfp(p) { set(v); }
    mpfp(mpf_t const & v    , mpfr_prec_t p):mpfp(p) { set(v); }
    mpfp(mpz const & v      , mpfr_prec_t p):mpfp(p) { set(v); }
    mpfp(mpq const & v      , mpfr_prec_t p):mpfp(p) { set(v); }
    mpfp(mpbq const & v     , mpfr_prec_t p):mpfp(p) { set(v); }
    mpfp(mpfp const & v     , mpfr_prec_t p):mpfp(p) { set(v); }

    // Constructors using the provided precision and rounding mode
    mpfp(float const v      , mpfr_prec_t p, mpfr_rnd_t rnd):mpfp(p) { set(v, rnd); }
    mpfp(double const v     , mpfr_prec_t p, mpfr_rnd_t rnd):mpfp(p) { set(v, rnd); }
    mpfp(long double const v, mpfr_prec_t p, mpfr_rnd_t rnd):mpfp(p) { set(v, rnd); }
    mpfp(mpz_t const & v    , mpfr_prec_t p, mpfr_rnd_t rnd):mpfp(p) { set(v, rnd); }
    mpfp(mpq_t const & v    , mpfr_prec_t p, mpfr_rnd_t rnd):mpfp(p) { set(v, rnd); }
    mpfp(mpf_t const & v    , mpfr_prec_t p, mpfr_rnd_t rnd):mpfp(p) { set(v, rnd); }
    mpfp(mpz const & v      , mpfr_prec_t p, mpfr_rnd_t rnd):mpfp(p) { set(v, rnd); }
    mpfp(mpq const & v      , mpfr_prec_t p, mpfr_rnd_t rnd):mpfp(p) { set(v, rnd); }
    mpfp(mpbq const & v     , mpfr_prec_t p, mpfr_rnd_t rnd):mpfp(p) { set(v, rnd); }
    mpfp(mpfp const & v     , mpfr_prec_t p, mpfr_rnd_t rnd):mpfp(p) { set(v, rnd); }

    // mpfr(mpfp && s):mpfr() { mpfr_swap(m_val, s.m_val); }
    // template<typename T> explicit mpfr(T const & v):mpfr() { operator=(v); }
    // mpfr(unsigned long int n, unsigned long int d):mpfr() { mpfr_set_ui(m_val, n, d); mpfr_canonicalize(m_val);}
    ~mpfp() { mpfr_clear(m_val); }

    unsigned hash() const { return static_cast<unsigned>(mpfr_get_si(m_val, MPFR_RNDN)); }

    int sgn() const { return mpfr_sgn(m_val); }
    friend int sgn(mpfp const & a) { return a.sgn(); }
    bool is_pos() const { return sgn() > 0; }
    bool is_neg() const { return sgn() < 0; }
    bool is_zero() const { return sgn() == 0; }
    bool is_nonpos() const { return !is_pos(); }
    bool is_nonneg() const { return !is_neg(); }

    void neg() { mpfr_neg(m_val, m_val, MPFR_RNDN); }
    friend mpfp neg(mpfp a) { a.neg(); return a; }

    // Math functions and theirs friend functions
    void abs  (mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_abs(m_val, m_val, rnd); }
    void exp  (mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_exp(m_val, m_val, rnd); }
    void exp2 (mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_exp2(m_val, m_val, rnd); }
    void exp10(mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_exp10(m_val, m_val, rnd); }
    void log  (mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_log(m_val, m_val, rnd); }
    void log2 (mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_log2(m_val, m_val, rnd); }
    void log10(mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_log10(m_val, m_val, rnd); }
    void sin  (mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_sin(m_val, m_val, rnd); }
    void cos  (mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_cos(m_val, m_val, rnd); }
    void tan  (mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_tan(m_val, m_val, rnd); }
    void sec  (mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_sec(m_val, m_val, rnd); }
    void csc  (mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_csc(m_val, m_val, rnd); }
    void cot  (mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_cot(m_val, m_val, rnd); }
    void asin (mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_asin(m_val, m_val, rnd); }
    void acos (mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_acos(m_val, m_val, rnd); }
    void atan (mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_atan(m_val, m_val, rnd); }
    void sinh (mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_sinh(m_val, m_val, rnd); }
    void cosh (mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_cosh(m_val, m_val, rnd); }
    void tanh (mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_tanh(m_val, m_val, rnd); }
    void asinh(mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_asinh(m_val, m_val, rnd); }
    void acosh(mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_acosh(m_val, m_val, rnd); }
    void atanh(mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_atanh(m_val, m_val, rnd); }
    friend mpfp abs  (mpfp a, mpfr_rnd_t rnd = MPFR_RNDN) { a.abs(rnd); return a; }
    friend mpfp exp  (mpfp a, mpfr_rnd_t rnd = MPFR_RNDN) { a.exp(rnd); return a; }
    friend mpfp exp2 (mpfp a, mpfr_rnd_t rnd = MPFR_RNDN) { a.exp2(rnd); return a; }
    friend mpfp exp10(mpfp a, mpfr_rnd_t rnd = MPFR_RNDN) { a.exp10(rnd); return a; }
    friend mpfp log  (mpfp a, mpfr_rnd_t rnd = MPFR_RNDN) { a.log(rnd); return a; }
    friend mpfp log2 (mpfp a, mpfr_rnd_t rnd = MPFR_RNDN) { a.log2(rnd); return a; }
    friend mpfp log10(mpfp a, mpfr_rnd_t rnd = MPFR_RNDN) { a.log10(rnd); return a; }
    friend mpfp sin  (mpfp a, mpfr_rnd_t rnd = MPFR_RNDN) { a.sin(rnd); return a; }
    friend mpfp cos  (mpfp a, mpfr_rnd_t rnd = MPFR_RNDN) { a.cos(rnd); return a; }
    friend mpfp tan  (mpfp a, mpfr_rnd_t rnd = MPFR_RNDN) { a.tan(rnd); return a; }
    friend mpfp sec  (mpfp a, mpfr_rnd_t rnd = MPFR_RNDN) { a.sec(rnd); return a; }
    friend mpfp csc  (mpfp a, mpfr_rnd_t rnd = MPFR_RNDN) { a.csc(rnd); return a; }
    friend mpfp cot  (mpfp a, mpfr_rnd_t rnd = MPFR_RNDN) { a.cot(rnd); return a; }
    friend mpfp asin (mpfp a, mpfr_rnd_t rnd = MPFR_RNDN) { a.asin(rnd); return a; }
    friend mpfp acos (mpfp a, mpfr_rnd_t rnd = MPFR_RNDN) { a.acos(rnd); return a; }
    friend mpfp atan (mpfp a, mpfr_rnd_t rnd = MPFR_RNDN) { a.atan(rnd); return a; }
    friend mpfp sinh (mpfp a, mpfr_rnd_t rnd = MPFR_RNDN) { a.sinh(rnd); return a; }
    friend mpfp cosh (mpfp a, mpfr_rnd_t rnd = MPFR_RNDN) { a.cosh(rnd); return a; }
    friend mpfp tanh (mpfp a, mpfr_rnd_t rnd = MPFR_RNDN) { a.tanh(rnd); return a; }
    friend mpfp asinh(mpfp a, mpfr_rnd_t rnd = MPFR_RNDN) { a.asinh(rnd); return a; }
    friend mpfp acosh(mpfp a, mpfr_rnd_t rnd = MPFR_RNDN) { a.acosh(rnd); return a; }
    friend mpfp atanh(mpfp a, mpfr_rnd_t rnd = MPFR_RNDN) { a.atanh(rnd); return a; }

    // void inv() { mpfr_inv(m_val, m_val, MPFR_RNDN); }
    // friend mpfp inv(mpfp a) { a.inv(); return a; }
    double get_double(mpfr_rnd_t rnd = MPFR_RNDN) const { return mpfr_get_d(m_val, rnd); }
    float  get_float (mpfr_rnd_t rnd = MPFR_RNDN) const { return mpfr_get_flt(m_val, rnd); }

    // bool is_integer() const { return mpz_cmp_ui(mpfr_denref(m_val), 1u) == 0; }

    friend int cmp(mpfp const & a, mpfp const & b           ) { return mpfr_cmp(a.m_val, b.m_val); }
//    friend int cmp(mpfp const & a, mpz const & b);
    friend int cmp(mpfp const & a, unsigned long int const b) { return mpfr_cmp_ui(a.m_val, b); }
    friend int cmp(mpfp const & a, long int const b         ) { return mpfr_cmp_si(a.m_val, b); }
    friend int cmp(mpfp const & a, double const b           ) { return mpfr_cmp_d (a.m_val, b); }
    friend int cmp(mpfp const & a, long double const b      ) { return mpfr_cmp_ld(a.m_val, b); }
    friend int cmp(mpfp const & a, mpz_t const & b          ) { return mpfr_cmp_z (a.m_val, b); }
    friend int cmp(mpfp const & a, mpq_t const & b          ) { return mpfr_cmp_q (a.m_val, b); }
    friend int cmp(mpfp const & a, mpf_t const & b          ) { return mpfr_cmp_f (a.m_val, b); }
    /* TODO */
    // friend int cmp(mpfp const & a, mpz const & b) { return mpfr_cmp_(a.m_val, b); }
    // friend int cmp(mpfp const & a, mpq const & b) { return mpfr_cmp_(a.m_val, b); }
    // friend int cmp(mpfp const & a, mpbq const & b) { return mpfr_cmp_(a.m_val, b); }

    friend bool operator<(mpfp const & a, mpfp const & b           ) { return cmp(a, b) < 0; }
    friend bool operator<(mpfp const & a, mpz const & b            ) { return cmp(a, b) < 0; }
    friend bool operator<(mpfp const & a, unsigned long int const b) { return cmp(a, b) < 0; }
    friend bool operator<(mpfp const & a, long int const b         ) { return cmp(a, b) < 0; }
    friend bool operator<(mpfp const & a, double const b           ) { return cmp(a, b) < 0; }
    friend bool operator<(mpfp const & a, long double const b      ) { return cmp(a, b) < 0; }
    friend bool operator<(mpfp const & a, mpz_t const & b          ) { return cmp(a, b) < 0; }
    friend bool operator<(mpfp const & a, mpq_t const & b          ) { return cmp(a, b) < 0; }
    friend bool operator<(mpfp const & a, mpf_t const & b          ) { return cmp(a, b) < 0; }

    friend bool operator<(mpz const & a            , mpfp const & b) { return cmp(b, a) > 0; }
    friend bool operator<(unsigned long int const a, mpfp const & b) { return cmp(b, a) > 0; }
    friend bool operator<(long int const a         , mpfp const & b) { return cmp(b, a) > 0; }
    friend bool operator<(double const a           , mpfp const & b) { return cmp(b, a) > 0; }
    friend bool operator<(long double const a      , mpfp const & b) { return cmp(b, a) > 0; }
    friend bool operator<(mpz_t const & a          , mpfp const & b) { return cmp(b, a) > 0; }
    friend bool operator<(mpq_t const & a          , mpfp const & b) { return cmp(b, a) > 0; }
    friend bool operator<(mpf_t const & a          , mpfp const & b) { return cmp(b, a) > 0; }

    friend bool operator>(mpfp const & a, mpfp const & b           ) { return cmp(a, b) > 0; }
    friend bool operator>(mpfp const & a, mpz const & b            ) { return cmp(a, b) > 0; }
    friend bool operator>(mpfp const & a, unsigned long int const b) { return cmp(a, b) > 0; }
    friend bool operator>(mpfp const & a, long int const b         ) { return cmp(a, b) > 0; }
    friend bool operator>(mpfp const & a, double const b           ) { return cmp(a, b) > 0; }
    friend bool operator>(mpfp const & a, long double const b      ) { return cmp(a, b) > 0; }
    friend bool operator>(mpfp const & a, mpz_t const & b          ) { return cmp(a, b) > 0; }
    friend bool operator>(mpfp const & a, mpq_t const & b          ) { return cmp(a, b) > 0; }
    friend bool operator>(mpfp const & a, mpf_t const & b          ) { return cmp(a, b) > 0; }

    friend bool operator>(mpz const & a            , mpfp const & b) { return cmp(b, a) < 0; }
    friend bool operator>(unsigned long int const a, mpfp const & b) { return cmp(b, a) < 0; }
    friend bool operator>(long int const a         , mpfp const & b) { return cmp(b, a) < 0; }
    friend bool operator>(double const a           , mpfp const & b) { return cmp(b, a) < 0; }
    friend bool operator>(long double const a      , mpfp const & b) { return cmp(b, a) < 0; }
    friend bool operator>(mpz_t const & a          , mpfp const & b) { return cmp(b, a) < 0; }
    friend bool operator>(mpq_t const & a          , mpfp const & b) { return cmp(b, a) < 0; }
    friend bool operator>(mpf_t const & a          , mpfp const & b) { return cmp(b, a) < 0; }

    friend bool operator<=(mpfp const & a, mpfp const & b           ) { return cmp(a, b) <= 0; }
    friend bool operator<=(mpfp const & a, mpz const & b            ) { return cmp(a, b) <= 0; }
    friend bool operator<=(mpfp const & a, unsigned long int const b) { return cmp(a, b) <= 0; }
    friend bool operator<=(mpfp const & a, long int const b         ) { return cmp(a, b) <= 0; }
    friend bool operator<=(mpfp const & a, double const b           ) { return cmp(a, b) <= 0; }
    friend bool operator<=(mpfp const & a, long double const b      ) { return cmp(a, b) <= 0; }
    friend bool operator<=(mpfp const & a, mpz_t const & b          ) { return cmp(a, b) <= 0; }
    friend bool operator<=(mpfp const & a, mpq_t const & b          ) { return cmp(a, b) <= 0; }
    friend bool operator<=(mpfp const & a, mpf_t const & b          ) { return cmp(a, b) <= 0; }

    friend bool operator<=(mpz const & a            , mpfp const & b) { return cmp(b, a) >= 0; }
    friend bool operator<=(unsigned long int const a, mpfp const & b) { return cmp(b, a) >= 0; }
    friend bool operator<=(long int const a         , mpfp const & b) { return cmp(b, a) >= 0; }
    friend bool operator<=(double const a           , mpfp const & b) { return cmp(b, a) >= 0; }
    friend bool operator<=(long double const a      , mpfp const & b) { return cmp(b, a) >= 0; }
    friend bool operator<=(mpz_t const & a          , mpfp const & b) { return cmp(b, a) >= 0; }
    friend bool operator<=(mpq_t const & a          , mpfp const & b) { return cmp(b, a) >= 0; }
    friend bool operator<=(mpf_t const & a          , mpfp const & b) { return cmp(b, a) >= 0; }

    friend bool operator>=(mpfp const & a, mpfp const & b           ) { return cmp(a, b) >= 0; }
    friend bool operator>=(mpfp const & a, mpz const & b            ) { return cmp(a, b) >= 0; }
    friend bool operator>=(mpfp const & a, unsigned long int const b) { return cmp(a, b) >= 0; }
    friend bool operator>=(mpfp const & a, long int const b         ) { return cmp(a, b) >= 0; }
    friend bool operator>=(mpfp const & a, double const b           ) { return cmp(a, b) >= 0; }
    friend bool operator>=(mpfp const & a, long double const b      ) { return cmp(a, b) >= 0; }
    friend bool operator>=(mpfp const & a, mpz_t const & b          ) { return cmp(a, b) >= 0; }
    friend bool operator>=(mpfp const & a, mpq_t const & b          ) { return cmp(a, b) >= 0; }
    friend bool operator>=(mpfp const & a, mpf_t const & b          ) { return cmp(a, b) >= 0; }

    friend bool operator>=(mpz const & a            , mpfp const & b) { return cmp(b, a) <= 0; }
    friend bool operator>=(unsigned long int const a, mpfp const & b) { return cmp(b, a) <= 0; }
    friend bool operator>=(long int const a         , mpfp const & b) { return cmp(b, a) <= 0; }
    friend bool operator>=(double const a           , mpfp const & b) { return cmp(b, a) <= 0; }
    friend bool operator>=(long double const a      , mpfp const & b) { return cmp(b, a) <= 0; }
    friend bool operator>=(mpz_t const & a          , mpfp const & b) { return cmp(b, a) <= 0; }
    friend bool operator>=(mpq_t const & a          , mpfp const & b) { return cmp(b, a) <= 0; }
    friend bool operator>=(mpf_t const & a          , mpfp const & b) { return cmp(b, a) <= 0; }

    friend bool operator==(mpfp const & a, mpfp const & b) { return mpfr_equal_p(a.m_val, b.m_val) != 0; }
//    friend bool operator==(mpfp const & a, mpz const & b) { return a.is_integer() && mpz_cmp(mpfr_numref(a.m_val), zval(b)) == 0; }
    // friend bool operator==(mpfp const & a, unsigned int b) { return a.is_integer() && mpz_cmp_ui(mpfr_numref(a.m_val), b) == 0; }
    // friend bool operator==(mpfp const & a, int b) { return a.is_integer() && mpz_cmp_si(mpfr_numref(a.m_val), b) == 0; }
    // friend bool operator==(mpz const & a, mpfp const & b) { return operator==(b, a); }
    // friend bool operator==(unsigned int a, mpfp const & b) { return operator==(b, a); }
    // friend bool operator==(int a, mpfp const & b) { return operator==(b, a); }

    friend bool operator!=(mpfp const & a, mpfp const & b) { return !operator==(a,b); }
    // friend bool operator!=(mpfp const & a, mpz const & b) { return !operator==(a,b); }
    // friend bool operator!=(mpfp const & a, unsigned int b) { return !operator==(a,b); }
    // friend bool operator!=(mpfp const & a, int b) { return !operator==(a,b); }
    // friend bool operator!=(mpz const & a, mpfp const & b) { return !operator==(a,b); }
    // friend bool operator!=(unsigned int a, mpfp const & b) { return !operator==(a,b); }
    // friend bool operator!=(int a, mpfp const & b) { return !operator==(a,b); }

    mpfp & add(mpfp const & o, mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_add(m_val, m_val, o.m_val, rnd); return *this; }
    mpfp & add(unsigned long int const o, mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_add_ui(m_val, m_val, o, rnd); return *this; }
    mpfp & add(long int const o, mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_add_si(m_val, m_val, o, rnd); return *this; }
    mpfp & add(double const o, mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_add_d(m_val, m_val, o, rnd); return *this; }
    mpfp & add(mpz_t const & o, mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_add_z(m_val, m_val, o, rnd); return *this; }
    mpfp & add(mpq_t const & o, mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_add_q(m_val, m_val, o, rnd); return *this; }
    mpfp & add(mpz const & o, mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_add_z(m_val, m_val, o.m_val, rnd); return *this; }
    mpfp & add(mpq const & o, mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_add_q(m_val, m_val, o.m_val, rnd); return *this; }
    mpfp & operator+=(mpfp const & o) { return add(o); }
    mpfp & operator+=(unsigned long int o) { return add(o); }
    mpfp & operator+=(long int const o) { return add(o); }
    mpfp & operator+=(double const o) { return add(o); }
    mpfp & operator+=(mpz_t const & o) { return add(o); }
    mpfp & operator+=(mpq_t const & o) { return add(o); }
    mpfp & operator+=(mpz const & o) { return add(o); }
    mpfp & operator+=(mpq const & o) { return add(o); }
    friend mpfp operator+(mpfp a, mpfp const & b) { return a += b; }
    friend mpfp operator+(mpfp a, unsigned long const b) { return a += b; }
    friend mpfp operator+(mpfp a, long int const b) { return a += b; }
    friend mpfp operator+(mpfp a, double const b) { return a += b; }
    friend mpfp operator+(mpfp a, mpz_t const & b) { return a += b; }
    friend mpfp operator+(mpfp a, mpq_t const & b) { return a += b; }
    friend mpfp operator+(mpfp a, mpz const & b) { return a += b; }
    friend mpfp operator+(mpfp a, mpq const & b) { return a += b; }

    mpfp & sub(mpfp const & o, mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_sub(m_val, m_val, o.m_val, rnd); return *this; }
    mpfp & sub(unsigned long int const o, mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_sub_ui(m_val, m_val, o, rnd); return *this; }
    mpfp & sub(long int const o, mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_sub_si(m_val, m_val, o, rnd); return *this; }
    mpfp & sub(double const o, mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_sub_d(m_val, m_val, o, rnd); return *this; }
    mpfp & sub(mpz_t const & o, mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_sub_z(m_val, m_val, o, rnd); return *this; }
    mpfp & sub(mpq_t const & o, mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_sub_q(m_val, m_val, o, rnd); return *this; }
    mpfp & sub(mpz const & o, mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_sub_z(m_val, m_val, o.m_val, rnd); return *this; }
    mpfp & sub(mpq const & o, mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_sub_q(m_val, m_val, o.m_val, rnd); return *this; }
    mpfp & rsub(unsigned long int const o, mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_ui_sub(m_val, o, m_val, rnd); return *this; }
    mpfp & rsub(long int const o, mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_si_sub(m_val, o, m_val, rnd); return *this; }
    mpfp & rsub(double const o, mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_d_sub(m_val, o, m_val, rnd); return *this; }
    mpfp & rsub(mpz_t const & o, mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_z_sub(m_val, o, m_val, rnd); return *this; }
    mpfp & rsub(mpz const & o, mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_z_sub(m_val, o.m_val, m_val, rnd); return *this; }
    mpfp & operator-=(mpfp const & o) { return sub(o); }
    mpfp & operator-=(unsigned long int o) { return sub(o); }
    mpfp & operator-=(long int const o) { return sub(o); }
    mpfp & operator-=(double const o) { return sub(o); }
    mpfp & operator-=(mpz_t const & o) { return sub(o); }
    mpfp & operator-=(mpq_t const & o) { return sub(o); }
    mpfp & operator-=(mpz const & o) { return sub(o); }
    mpfp & operator-=(mpq const & o) { return sub(o); }
    friend mpfp operator-(mpfp a, mpfp const & b) { return a -= b; }
    friend mpfp operator-(mpfp a, unsigned long const b) { return a -= b; }
    friend mpfp operator-(mpfp a, long int const b) { return a -= b; }
    friend mpfp operator-(mpfp a, double const b) { return a -= b; }
    friend mpfp operator-(mpfp a, mpz_t const & b) { return a -= b; }
    friend mpfp operator-(mpfp a, mpq_t const & b) { return a -= b; }
    friend mpfp operator-(mpfp a, mpz const & b) { return a -= b; }
    friend mpfp operator-(mpfp a, mpq const & b) { return a -= b; }
    friend mpfp operator-(unsigned long const a, mpfp b) { return b.rsub(a); }
    friend mpfp operator-(long int const a, mpfp b) { return b.rsub(a); }
    friend mpfp operator-(double const a, mpfp b) { return b.rsub(a); }
    friend mpfp operator-(mpz_t const & a, mpfp b) { return b.rsub(a); }
//    friend mpfp operator-(mpq_t const & a, mpfp b) { return b.rsub(a); }
    friend mpfp operator-(mpz const & a, mpfp b) { return b.rsub(a); }
//    friend mpfp operator-(mpq const & a, mpfp b) { return b.rsub(a); }

    mpfp & mul(mpfp const & o, mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_mul(m_val, m_val, o.m_val, rnd); return *this; }
    mpfp & mul(unsigned long int const o, mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_mul_ui(m_val, m_val, o, rnd); return *this; }
    mpfp & mul(long int const o, mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_mul_si(m_val, m_val, o, rnd); return *this; }
    mpfp & mul(double const o, mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_mul_d(m_val, m_val, o, rnd); return *this; }
    mpfp & mul(mpz_t const & o, mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_mul_z(m_val, m_val, o, rnd); return *this; }
    mpfp & mul(mpq_t const & o, mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_mul_q(m_val, m_val, o, rnd); return *this; }
    mpfp & mul(mpz const & o, mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_mul_z(m_val, m_val, o.m_val, rnd); return *this; }
    mpfp & mul(mpq const & o, mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_mul_q(m_val, m_val, o.m_val, rnd); return *this; }
    mpfp & operator*=(mpfp const & o) { return mul(o); }
    mpfp & operator*=(unsigned long int o) { return mul(o); }
    mpfp & operator*=(long int const o) { return mul(o); }
    mpfp & operator*=(double const o) { return mul(o); }
    mpfp & operator*=(mpz_t const & o) { return mul(o); }
    mpfp & operator*=(mpq_t const & o) { return mul(o); }
    mpfp & operator*=(mpz const & o) { return mul(o); }
    mpfp & operator*=(mpq const & o) { return mul(o); }
    friend mpfp operator*(mpfp a, mpfp const & b) { return a *= b; }
    friend mpfp operator*(mpfp a, unsigned long const b) { return a *= b; }
    friend mpfp operator*(mpfp a, long int const b) { return a *= b; }
    friend mpfp operator*(mpfp a, double const b) { return a *= b; }
    friend mpfp operator*(mpfp a, mpz_t const & b) { return a *= b; }
    friend mpfp operator*(mpfp a, mpq_t const & b) { return a *= b; }
    friend mpfp operator*(mpfp a, mpz const & b) { return a *= b; }
    friend mpfp operator*(mpfp a, mpq const & b) { return a *= b; }

    mpfp & div(mpfp const & o, mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_div(m_val, m_val, o.m_val, rnd); return *this; }
    mpfp & div(unsigned long int const o, mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_div_ui(m_val, m_val, o, rnd); return *this; }
    mpfp & div(long int const o, mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_div_si(m_val, m_val, o, rnd); return *this; }
    mpfp & div(double const o, mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_div_d(m_val, m_val, o, rnd); return *this; }
    mpfp & div(mpz_t const & o, mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_div_z(m_val, m_val, o, rnd); return *this; }
    mpfp & div(mpq_t const & o, mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_div_q(m_val, m_val, o, rnd); return *this; }
    mpfp & div(mpz const & o, mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_div_z(m_val, m_val, o.m_val, rnd); return *this; }
    mpfp & div(mpq const & o, mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_div_q(m_val, m_val, o.m_val, rnd); return *this; }
    mpfp & rdiv(unsigned long int const o, mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_ui_div(m_val, o, m_val, rnd); return *this; }
    mpfp & rdiv(long int const o, mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_si_div(m_val, o, m_val, rnd); return *this; }
    mpfp & rdiv(double const o, mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_d_div(m_val, o, m_val, rnd); return *this; }
    mpfp & operator/=(mpfp const & o) { return div(o); }
    mpfp & operator/=(unsigned long int o) { return div(o); }
    mpfp & operator/=(long int const o) { return div(o); }
    mpfp & operator/=(double const o) { return div(o); }
    mpfp & operator/=(mpz_t const & o) { return div(o); }
    mpfp & operator/=(mpq_t const & o) { return div(o); }
    mpfp & operator/=(mpz const & o) { return div(o); }
    mpfp & operator/=(mpq const & o) { return div(o); }
    friend mpfp operator/(mpfp a, mpfp const & b) { return a /= b; }
    friend mpfp operator/(mpfp a, unsigned long const b) { return a /= b; }
    friend mpfp operator/(mpfp a, long int const b) { return a /= b; }
    friend mpfp operator/(mpfp a, double const b) { return a /= b; }
    friend mpfp operator/(mpfp a, mpz_t const & b) { return a /= b; }
    friend mpfp operator/(mpfp a, mpq_t const & b) { return a /= b; }
    friend mpfp operator/(mpfp a, mpz const & b) { return a /= b; }
    friend mpfp operator/(mpfp a, mpq const & b) { return a /= b; }
    friend mpfp operator/(unsigned long const a, mpfp b) { return b.rdiv(a); }
    friend mpfp operator/(long int const a, mpfp b) { return b.rdiv(a); }
    friend mpfp operator/(double const a, mpfp b) { return b.rdiv(a); }
//    friend mpfp operator/(mpz_t const & a, mpfp b) { return a.rdiv(b); }
//    friend mpfp operator/(mpq_t const & a, mpfp b) { return a.rdiv(b); }
//    friend mpfp operator/(mpz const & a, mpfp b) { return a.rdiv(b); }
//    friend mpfp operator/(mpq const & a, mpfp b) { return a.rdiv(b); }

    mpfp & pow(unsigned long int k, mpfr_rnd_t rnd = MPFR_RNDN) { mpfr_pow_ui(m_val, m_val, k, rnd); return *this; }
    mpfp & operator^=(unsigned long int k) { return pow(k); }
    friend mpfp operator^(mpfp a, unsigned long int k) { return a ^= k; }

    // mpfp & operator++() { return operator+=(1); }
    // mpfp operator++(int) { mpfp r(*this); ++(*this); return r; }

    // mpfp & operator--() { return operator-=(1); }
    // mpfp operator--(int) { mpfp r(*this); --(*this); return r; }

    // void floor();
    // friend mpz floor(mpfp const & a);

    // void ceil();
    // friend mpz ceil(mpfp const & a);

    // friend void power(mpfp & a, mpfp const & b, unsigned k);
    // friend void _power(mpfp & a, mpfp const & b, unsigned k) { power(a, b, k); }
    // friend mpfp power(mpfp a, unsigned k) { power(a, a, k); return a; }

    friend std::ostream & operator<<(std::ostream & out, mpfp const & v);

    // friend void display_decimal(std::ostream & out, mpfp const & a, unsigned prec);

    // class decimal {
    //     mpfp const & m_val;
    //     unsigned     m_prec;
    // public:
    //     decimal(mpfp const & val, unsigned prec = 10):m_val(val), m_prec(prec) {}
    //     friend std::ostream & operator<<(std::ostream & out, decimal const & d) { display_decimal(out, d.m_val, d.m_prec); return out; }
    // };

};

// Macro to implement transcendental functions
#define LEAN_TRANS_MPFP_FUNC(f, v, rnd) v.f(rnd);

template<>
class numeric_traits<mpfp> {
public:
    static thread_local mpfr_rnd_t rnd;
    static bool precise() { return true; }
    static bool is_zero(mpfp const &  v) { return v.is_zero(); }
    static bool is_pos(mpfp const & v) { return v.is_pos(); }
    static bool is_neg(mpfp const & v) { return v.is_neg(); }
    static void set_rounding(bool plus_inf) { rnd = plus_inf ? MPFR_RNDU :MPFR_RNDD; }
    static void neg(mpfp & v) { v.neg(); }
//    static void inv(mpfp & v) { v.inv(); }
//    static void reset(mpfp & v) { v = 0; }
    // v <- v^k
    static void power(mpfp & v, unsigned k) { v.pow(k); }

    // constants
    static mpfp pi_l;
    static mpfp pi_n;
    static mpfp pi_u;
    static inline mpfp pi_lower()       {
        mpfr_const_pi(pi_l.m_val, MPFR_RNDD);
        return pi_l;
    }
    static inline mpfp pi()             {
        mpfr_const_pi(pi_n.m_val, MPFR_RNDN);
        return pi_n;
    }
    static inline mpfp pi_upper()       {
        mpfr_const_pi(pi_u.m_val, MPFR_RNDU);
        return pi_u;
    }
    static inline mpfp pi_half_lower()  { return pi_l / 2lu; }
    static inline mpfp pi_half()        { return pi_n / 2lu; }
    static inline mpfp pi_half_upper()  { return pi_u / 2lu; }
    static inline mpfp pi_twice_lower() { return pi_l * 2lu; }
    static inline mpfp pi_twice()       { return pi_n * 2lu; }
    static inline mpfp pi_twice_upper() { return pi_u * 2lu; }

    // Transcendental functions
    static void exp(mpfp & v)   { LEAN_TRANS_MPFP_FUNC(exp,   v, rnd); }
    static void exp2(mpfp & v)  { LEAN_TRANS_MPFP_FUNC(exp2,  v, rnd); }
    static void exp10(mpfp & v) { LEAN_TRANS_MPFP_FUNC(exp10, v, rnd); }
    static void log(mpfp & v)   { LEAN_TRANS_MPFP_FUNC(log,   v, rnd); }
    static void log2(mpfp & v)  { LEAN_TRANS_MPFP_FUNC(log2,  v, rnd); }
    static void log10(mpfp & v) { LEAN_TRANS_MPFP_FUNC(log10, v, rnd); }
    static void sin(mpfp & v)   { LEAN_TRANS_MPFP_FUNC(sin,   v, rnd); }
    static void cos(mpfp & v)   { LEAN_TRANS_MPFP_FUNC(cos,   v, rnd); }
    static void tan(mpfp & v)   { LEAN_TRANS_MPFP_FUNC(tan,   v, rnd); }
    static void sec(mpfp & v)   { LEAN_TRANS_MPFP_FUNC(sec,   v, rnd); }
    static void csc(mpfp & v)   { LEAN_TRANS_MPFP_FUNC(csc,   v, rnd); }
    static void cot(mpfp & v)   { LEAN_TRANS_MPFP_FUNC(cot,   v, rnd); }
    static void asin(mpfp & v)  { LEAN_TRANS_MPFP_FUNC(asin,  v, rnd); }
    static void acos(mpfp & v)  { LEAN_TRANS_MPFP_FUNC(acos,  v, rnd); }
    static void atan(mpfp & v)  { LEAN_TRANS_MPFP_FUNC(atan,  v, rnd); }
    static void sinh(mpfp & v)  { LEAN_TRANS_MPFP_FUNC(sinh,  v, rnd); }
    static void cosh(mpfp & v)  { LEAN_TRANS_MPFP_FUNC(cosh,  v, rnd); }
    static void tanh(mpfp & v)  { LEAN_TRANS_MPFP_FUNC(tanh,  v, rnd); }
    static void asinh(mpfp & v) { LEAN_TRANS_MPFP_FUNC(asinh, v, rnd); }
    static void acosh(mpfp & v) { LEAN_TRANS_MPFP_FUNC(acosh, v, rnd); }
    static void atanh(mpfp & v) { LEAN_TRANS_MPFP_FUNC(atanh, v, rnd); }
};
}
