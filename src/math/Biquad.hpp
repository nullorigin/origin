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
#include "../Origin.hpp"
namespace Origin {
enum : const I32 {
  Lowpass = 0,
  Highpass = 1,
  Bandpass = 2,
  Notch = 3,
  Peak = 4,
  Lowshelf = 5,
  Highshelf = 6
};

class Biquad {
public:
  Biquad();
  Biquad(I32 type, F64 Fc, F64 Q, F64 peakGainDB);
  ~Biquad();
  void SetType(I32 type);
  void SetQ(F64 Q);
  void SetFc(F64 Fc);
  void SetPeakGain(F64 peakGainDB);
  void SetBiquad(I32 type, F64 Fc, F64 Q, F64 peakGainDB);
  F32 Process(F32 in);

protected:
  void CalcBiquad(void);

  I32 type;
  F64 a0, a1, a2, b1, b2;
  F64 Fc, Q, peakGain;
  F64 z1, z2;
};

inline F32 Biquad::Process(F32 in) {
  F64 out = in * a0 + z1;
  z1 = in * a1 + z2 - b1 * out;
  z2 = in * a2 - b2 * out;
  return out;
}
} // namespace Origin
#endif // Biquad_h