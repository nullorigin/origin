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
        f64 a0, a1, a2, b1, b2;
        f64 Fc, Q, peakGain;
        f64 z1, z2;
    };

    inline auto Biquad::Process(f64 in) -> f64
    {
        f64 out = in * a0 + z1;
        z1 = in * a1 + z2 - b1 * out;
        z2 = in * a2 - b2 * out;
        return out;
    }
} // namespace origin
#endif // Biquad_h