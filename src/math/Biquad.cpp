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
#include <math.h>
namespace Origin {
Biquad::Biquad() {
  type = Lowpass;
  a0 = 1.0;
  a1 = a2 = b1 = b2 = 0.0;
  Fc = 0.50;
  Q = 0.707;
  peakGain = 0.0;
  z1 = z2 = 0.0;
}

Biquad::Biquad(I32 type, F64 Fc, F64 Q, F64 peakGainDB) {
  SetBiquad(type, Fc, Q, peakGainDB);
  z1 = z2 = 0.0;
}

Biquad::~Biquad() {}

void Biquad::SetType(I32 type) {
  this->type = type;
  CalcBiquad();
}

void Biquad::SetQ(F64 Q) {
  this->Q = Q;
  CalcBiquad();
}

void Biquad::SetFc(F64 Fc) {
  this->Fc = Fc;
  CalcBiquad();
}

void Biquad::SetPeakGain(F64 peakGainDB) {
  this->peakGain = peakGainDB;
  CalcBiquad();
}

void Biquad::SetBiquad(I32 type, F64 Fc, F64 Q, F64 peakGainDB) {
  this->type = type;
  this->Q = Q;
  this->Fc = Fc;
  SetPeakGain(peakGainDB);
}

void Biquad::CalcBiquad(void) {
  F64 norm;
  const F64 V = pow(10, fabs(peakGain) / 20.0);
  const F64 K = tan(M_PI * Fc);
  const F64 V2 = V * 2;
  const F64 KK = K * K;
  const F64 KKK = KK * K;
  const F64 sqrt2 = 1.4142135623730950488016887242097;
  const F64 sqrtV2 = sqrt(V2);
  switch (this->type) {
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
    if (peakGain >= 0) { // boost
      norm = 1 / (1 + 1 / Q * KKK);
      a0 = (1 + V / Q * K + KK) * norm;
      a1 = 2 * (KK - 1) * norm;
      a2 = (1 - V / Q * KKK) * norm;
      b1 = a1;
      b2 = (1 - 1 / Q * K + KK) * norm;
    } else { // cut
      norm = 1 / (1 + V / Q * K + KK);
      a0 = (1 + 1 / Q * K + KK) * norm;
      a1 = 2 * (KK - 1) * norm;
      a2 = (1 - 1 / Q * K + KK) * norm;
      b1 = a1;
      b2 = (1 - V / Q * K + KK) * norm;
    }
    break;
  case Lowshelf:
    if (peakGain >= 0) { // boost
      norm = 1 / (1 + sqrt2 * K + KK);
      a0 = (1 + sqrtV2 * K + V * KK) * norm;
      a1 = 2 * (V * KK - 1) * norm;
      a2 = (1 - sqrtV2 * K + V * KK) * norm;
      b1 = 2 * (KK - 1) * norm;
      b2 = (1 - sqrt2 * K + KK) * norm;
    } else { // cut
      norm = 1 / (1 + sqrtV2 * K + V * K * K);
      a0 = (1 + sqrt2 * K + KK) * norm;
      a1 = 2 * (KK - 1) * norm;
      a2 = (1 - sqrt2 * K + KK) * norm;
      b1 = 2 * (V * KK - 1) * norm;
      b2 = (1 - sqrtV2 * K + V * KK) * norm;
    }
    break;
  case Highshelf:
    if (peakGain >= 0) { // boost
      norm = 1 / (1 + sqrt2 * K + KK);
      a0 = (V + sqrtV2 * K + KK) * norm;
      a1 = 2 * (KK - V) * norm;
      a2 = (V - sqrtV2 * K + KK) * norm;
      b1 = 2 * (KK - 1) * norm;
      b2 = (1 - sqrt2 * K + KK) * norm;
    } else { // cut
      norm = 1 / (V + sqrtV2 * K + KK);
      a0 = (1 + sqrt2 * K + KK) * norm;
      a1 = 2 * (KK - 1) * norm;
      a2 = (1 - sqrt2 * K + KK) * norm;
      b1 = 2 * (KK - V) * norm;
      b2 = (V - sqrtV2 * K + KK) * norm;
    }
    break;
  }
  return;
}
} // namespace Origin