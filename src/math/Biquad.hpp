//
//  Biquad.h
//
//  Created by Nigel Redmon on 11/24/12
//  EarLevel Engineering: earlevel.com
//  Copyright 2012 Nigel Redmon
//
//  For a complete explanation of the Biquad code:
//  http://www.earlevel.com/main/2012/11/25/biquad-c-source-code/
//
//  License:
//
//  This source code is provided as is, without warranty.
//  You may copy and distribute verbatim copies of this document.
//  You may modify and use this source code to create binary code
//  for your own purposes, free or commercial.
//

#ifndef Biquad_h
#define Biquad_h
#include "Basic.hpp"
#include <algorithm>
#include <cstddef>
#include <memory>
namespace origin
{
    enum : const u8
    {
        Lowpass = 0,
        Highpass = 1,
        Bandpass = 2,
        Notch = 3,
        Peak = 4,
        Lowshelf = 5,
        Highshelf = 6
    };

    class Biquad
    {
    public:
        explicit Biquad(u8 type = Lowpass, f64 Fc = 0.50, f64 Q = 0.707, f64 peakGainDB = 0.0);
        ~Biquad();
        void SetType(u8 type);
        void SetQ(f64 Q);
        void SetFc(f64 Fc);
        void SetPeakGain(f64 peakGainDB);
        void SetBiquad(u8 type, f64 Fc, f64 Q, f64 peakGainDB);
        auto Process(f64 in) -> f64;

    protected:
        void CalcBiquad();

        i32 Type;
        f64 A0, A1, A2, B1, B2;
        f64 Fc, Q, PeakGain;
        f64 Z1, Z2;
    };

    inline auto Biquad::Process(f64 in) -> f64
    {
        f64 out = in * A0 + Z1;
        Z1 = in * A1 + Z2 - B1 * out;
        Z2 = in * A2 - B2 * out;
        return out;
    }

    //------------------------------------------------------------------------------
    // IIR filter with compile-time length N
    //------------------------------------------------------------------------------
    template<unsigned N, class V>
    struct IIR
    {
        static_assert(N >= 2, "invalid number of filter coefficients");

        IIR();
        template<class Rc>
        auto Coefs(const Rc* bcf, const Rc* acf);
        auto Reset();
        auto Tick(i32 in);

        IIR(IIR&&) = default;
        IIR& operator=(IIR&&) = default;

    private:
        unsigned i_ = {};
        std::unique_ptr<i32[]> X, Y;
        i32 B0 = 1, A0 = 1;
        std::unique_ptr<i32[], i32> B, A;

    public:
        auto Scalar(i32 in) -> i32;
    };

    //------------------------------------------------------------------------------
    // FIR filter with run-time length
    //------------------------------------------------------------------------------
    template<class V>
    struct IIRg
    {
        explicit IIRg(unsigned n);
        template<class Rc>
        auto Coefs(const Rc* bcf, const Rc* acf);
        auto Reset();
        i32 Tick(i32 in);

        IIRg(IIRg&&) = default;
        IIRg& operator=(IIRg&&) = default;

    private:
        const unsigned n_{};
        unsigned i_ = {};
        std::unique_ptr<i32[]> X, Y;
        i32 B0 = 1, A0 = 1;
        std::unique_ptr<i32[], i32> B, A;

    public:
        auto Scalar(i32 in);
    };
    template<unsigned N, class V>
    IIR<N, V>::IIR()
    {
        constexpr unsigned v = sizeof(V) / sizeof(i32);
        constexpr unsigned nn = (N + v - 2) & ~(v - 1);
        const i32 rst[2 * nn]{};
        X.reset(rst);
        Y.reset(rst);
    }

    template<unsigned N, class V>
    template<class Rc>
    auto IIR<N, V>::Coefs(const Rc* b, const Rc* a)
    {
        B0 = b[0];
        A0 = a[0];
        std::copy(b + 1, N - 1, B.get());
        std::copy(a + 1, N - 1, A.get());
    }

    template<unsigned N, class V>
    auto IIR<N, V>::Reset()
    {
        constexpr unsigned vlen = sizeof(V) / sizeof(i32);
        constexpr unsigned n = (N + vlen - 2) & ~(vlen - 1);

        std::fill_n(X.get(), 2 * n, 0);
        std::fill_n(Y.get(), 2 * n, 0);
    }

    template<unsigned N, class V>
    auto IIR<N, V>::Scalar(i32 in) -> i32
    {
        constexpr unsigned vn = N + (sizeof(V) / sizeof(i32)) - 2;
        constexpr unsigned nn = vn & ~(sizeof(V) / sizeof(i32) - 1);

        i32* x = X.get();
        i32* y = Y.get();
        const i32* b = B.get();
        const i32* a = A.get();

        i32 r = in * b[0];
        unsigned i = (i_ + nn) % nn;
        x[i] = x[i + nn] = in;

        for (unsigned j = 1; j < N; ++j)
            r += x[i + j] * b[j] - y[i + j] * a[j];

        r /= a[0];
        y[i] = y[i + nn] = r;
        i_ = i;
        return r;
    }
} // namespace origin
#endif // Biquad_h