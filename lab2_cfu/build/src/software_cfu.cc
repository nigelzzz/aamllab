/*
 * Copyright 2021 The CFU-Playground Authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdint.h>
#include "software_cfu.h"

//
// In this function, place C code to emulate your CFU. You can switch between
// hardware and emulated CFU by setting the CFU_SOFTWARE_DEFINED DEFINE in
// the Makefile.
uint32_t software_cfu(int funct3, int funct7, uint32_t rs1, uint32_t rs2)
{
    static int16_t input_offset = 0;
  static int16_t filter_offset = 0;
//  (void)funct3;

  switch (funct3) {
    case 0: {
      int32_t sum = 0;
      for (int lane = 0; lane < 4; ++lane) {
        const int shift = lane * 8;
        const int8_t input_val = static_cast<int8_t>((rs1 >> shift) & 0xFF);
        const int8_t filter_val = static_cast<int8_t>((rs2 >> shift) & 0xFF);
        sum += static_cast<int32_t>(input_val + input_offset) *
               static_cast<int32_t>(filter_val + filter_offset);
      }
      return static_cast<uint32_t>(sum);
    }
    case 1:
      input_offset = static_cast<int16_t>(rs1);
      return 0;
    case 2:
      filter_offset = static_cast<int16_t>(rs1);
      return 0;
    default:software_c
      return 0;
  }
  //return (funct3 & 1) ? rs2 : rs1;
}
