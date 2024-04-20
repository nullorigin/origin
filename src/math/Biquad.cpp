//
//  Biquad.cpp
//
//  Created by Nigel Redmon on 11/24/12
//  EarLevel Engineering: earlevel.com
//  Copyright 2012 Nigel Redmon
//
//  For a complete explanation of the Biquad code:
//  http://www.earlevel.com/main/2012/11/26/biquad-c-source-code/
//
//  License:
//
//  This source code is provided as is, without warranty.
//  You may copy and distribute verbatim copies of this document.
//  You may modify and use this source code to create binary code
//  for your own purposes, free or commercial.
//

#include "Biquad.hpp"
#include "Basic.hpp"

#include <cmath>
namespace origin
{

    Biquad::Biquad(u8 type, f64 Fc, f64 Q, f64 peakGainDB)
    {
        a0 = 1.0;
        a1 = a2 = b1 = b2 = 0.0;
        SetBiquad(type, Fc, Q, peakGainDB);
        z1 = z2 = 0.0;
    }

    void Biquad::SetType(u8 type)
    {
        this->Type = type;
        CalcBiquad();
    }

    void Biquad::SetQ(f64 Q)
    {
        this->Q = Q;
        CalcBiquad();
    }

    void Biquad::SetFc(f64 Fc)
    {
        this->Fc = Fc;
        CalcBiquad();
    }

    void Biquad::SetPeakGain(f64 peakGainDB)
    {
        this->peakGain = peakGainDB;
        CalcBiquad();
    }

    void Biquad::SetBiquad(u8 type, f64 Fc, f64 Q, f64 peakGainDB)
    {
        this->Type = type;
        this->Q = Q;
        this->Fc = Fc;
        SetPeakGain(peakGainDB);
    }

    void Biquad::CalcBiquad()
    {
        f64 norm = NAN;
        const f64 V = POWI(Abs(peakGain) / 20.0, 10);
        const f64 K = Tan(PI * Fc);
        const f64 V2 = V * 2;
        const f64 KK = K * K;
        const f64 KKK = KK * K;
        const f64 sqrt2 = 1.4142135623730950488016887242097;
        const f64 sqrtV2 = Sqrt(V2);
        switch (this->Type)
        {
        case Lowpass:
            norm = 1 / (1 + K / Q + KK);
            a0 = KK * norm;
            a1 = 2 * a0;
            a2 = a0;
            b1 = 2 * (KK - 1) * norm;
            b2 = (1 - K / Q + KK) * norm;
            break;

        case Highpass:
            norm = 1 / (1 + K / Q + KK);
            a0 = 1 * norm;
            a1 = -2 * a0;
            a2 = a0;
            b1 = 2 * (KK - 1) * norm;
            b2 = (1 - K / Q + KK) * norm;
            break;

        case Bandpass:
            norm = 1 / (1 + K / Q + KK);
            a0 = K / Q * norm;
            a1 = 0;
            a2 = -a0;
            b1 = 2 * (KK - 1) * norm;
            b2 = (1 - K / Q + KK) * norm;
            break;

        case Notch:
            norm = 1 / (1 + K / Q + KK);
            a0 = (1 + KK) * norm;
            a1 = 2 * (KK - 1) * norm;
            a2 = a0;
            b1 = a1;
            b2 = (1 - K / Q + KK) * norm;
            break;

        case Peak:
            if (peakGain >= 0)
            { // boost
                norm = 1 / (1 + 1 / Q * KKK);
                a0 = (1 + V / Q * K + KK) * norm;
                a1 = 2 * (KK - 1) * norm;
                a2 = (1 - V / Q * KKK) * norm;
                b1 = a1;
                b2 = (1 - 1 / Q * K + KK) * norm;
            }
            else
            { // cut
                norm = 1 / (1 + V / Q * K + KK);
                a0 = (1 + 1 / Q * K + KK) * norm;
                a1 = 2 * (KK - 1) * norm;
                a2 = (1 - 1 / Q * K + KK) * norm;
                b1 = a1;
                b2 = (1 - V / Q * K + KK) * norm;
            }
            break;
        case Lowshelf:
            if (peakGain >= 0)
            { // boost
                norm = 1 / (1 + sqrt2 * K + KK);
                a0 = (1 + sqrtV2 * K + V * KK) * norm;
                a1 = 2 * (V * KK - 1) * norm;
                a2 = (1 - sqrtV2 * K + V * KK) * norm;
                b1 = 2 * (KK - 1) * norm;
                b2 = (1 - sqrt2 * K + KK) * norm;
            }
            else
            { // cut
                norm = 1 / (1 + sqrtV2 * K + V * K * K);
                a0 = (1 + sqrt2 * K + KK) * norm;
                a1 = 2 * (KK - 1) * norm;
                a2 = (1 - sqrt2 * K + KK) * norm;
                b1 = 2 * (V * KK - 1) * norm;
                b2 = (1 - sqrtV2 * K + V * KK) * norm;
            }
            break;
        case Highshelf:
            if (peakGain >= 0)
            { // boost
                norm = 1 / (1 + sqrt2 * K + KK);
                a0 = (V + sqrtV2 * K + KK) * norm;
                a1 = 2 * (KK - V) * norm;
                a2 = (V - sqrtV2 * K + KK) * norm;
                b1 = 2 * (KK - 1) * norm;
                b2 = (1 - sqrt2 * K + KK) * norm;
            }
            else
            { // cut
                norm = 1 / (V + sqrtV2 * K + KK);
                a0 = (1 + sqrt2 * K + KK) * norm;
                a1 = 2 * (KK - 1) * norm;
                a2 = (1 - sqrt2 * K + KK) * norm;
                b1 = 2 * (KK - V) * norm;
                b2 = (V - sqrtV2 * K + KK) * norm;
            }
            break;
        }
    }
} // namespace origin
