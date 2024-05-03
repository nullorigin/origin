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
namespace Origin
{
    Biquad::Biquad(u8 type, f64 Fc, f64 Q, f64 peakGainDB)
    {
        A0 = 1.0;
        A1 = A2 = B1 = B2 = 0.0;
        SetBiquad(type, Fc, Q, peakGainDB);
        Z1 = Z2 = 0.0;
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
        this->PeakGain = peakGainDB;
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
        f64 norm = 0.0;
        const f64 v = powi(abs(PeakGain) / 20.0, 10);
        const f64 k = tan(PI * Fc);
        const f64 v2 = v * 2;
        const f64 kk = k * k;
        const f64 kkk = kk * k;
        const f64 sqrt2 = 1.4142135623730950488016887242097;
        const f64 sqrt_v2 = sqrt(v2);
        switch (this->Type)
        {
        case Lowpass:
            norm = 1 / (1 + k / Q + kk);
            A0 = kk * norm;
            A1 = 2 * A0;
            A2 = A0;
            B1 = 2 * (kk - 1) * norm;
            B2 = (1 - k / Q + kk) * norm;
            break;

        case Highpass:
            norm = 1 / (1 + k / Q + kk);
            A0 = 1 * norm;
            A1 = -2 * A0;
            A2 = A0;
            B1 = 2 * (kk - 1) * norm;
            B2 = (1 - k / Q + kk) * norm;
            break;

        case Bandpass:
            norm = 1 / (1 + k / Q + kk);
            A0 = k / Q * norm;
            A1 = 0;
            A2 = -A0;
            B1 = 2 * (kk - 1) * norm;
            B2 = (1 - k / Q + kk) * norm;
            break;

        case Notch:
            norm = 1 / (1 + k / Q + kk);
            A0 = (1 + kk) * norm;
            A1 = 2 * (kk - 1) * norm;
            A2 = A0;
            B1 = A1;
            B2 = (1 - k / Q + kk) * norm;
            break;

        case Peak:
            if (PeakGain >= 0)
            { // boost
                norm = 1 / (1 + 1 / Q * kkk);
                A0 = (1 + v / Q * k + kk) * norm;
                A1 = 2 * (kk - 1) * norm;
                A2 = (1 - v / Q * kkk) * norm;
                B1 = A1;
                B2 = (1 - 1 / Q * k + kk) * norm;
            }
            else
            { // cut
                norm = 1 / (1 + v / Q * k + kk);
                A0 = (1 + 1 / Q * k + kk) * norm;
                A1 = 2 * (kk - 1) * norm;
                A2 = (1 - 1 / Q * k + kk) * norm;
                B1 = A1;
                B2 = (1 - v / Q * k + kk) * norm;
            }
            break;
        case Lowshelf:
            if (PeakGain >= 0)
            { // boost
                norm = 1 / (1 + sqrt2 * k + kk);
                A0 = (1 + sqrt_v2 * k + v * kk) * norm;
                A1 = 2 * (v * kk - 1) * norm;
                A2 = (1 - sqrt_v2 * k + v * kk) * norm;
                B1 = 2 * (kk - 1) * norm;
                B2 = (1 - sqrt2 * k + kk) * norm;
            }
            else
            { // cut
                norm = 1 / (1 + sqrt_v2 * k + v * k * k);
                A0 = (1 + sqrt2 * k + kk) * norm;
                A1 = 2 * (kk - 1) * norm;
                A2 = (1 - sqrt2 * k + kk) * norm;
                B1 = 2 * (v * kk - 1) * norm;
                B2 = (1 - sqrt_v2 * k + v * kk) * norm;
            }
            break;
        case Highshelf:
            if (PeakGain >= 0)
            { // boost
                norm = 1 / (1 + sqrt2 * k + kk);
                A0 = (v + sqrt_v2 * k + kk) * norm;
                A1 = 2 * (kk - v) * norm;
                A2 = (v - sqrt_v2 * k + kk) * norm;
                B1 = 2 * (kk - 1) * norm;
                B2 = (1 - sqrt2 * k + kk) * norm;
            }
            else
            { // cut
                norm = 1 / (v + sqrt_v2 * k + kk);
                A0 = (1 + sqrt2 * k + kk) * norm;
                A1 = 2 * (kk - 1) * norm;
                A2 = (1 - sqrt2 * k + kk) * norm;
                B1 = 2 * (kk - v) * norm;
                B2 = (v - sqrt_v2 * k + kk) * norm;
            }
            break;
        }
    }
} // namespace Origin
