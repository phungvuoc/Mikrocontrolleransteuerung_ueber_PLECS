/*
 * Implementation file for: Motorsteuerung_CAN
 * Generated with         : PLECS 4.5.8
 *                          TI2837xS 1.4.4
 * Generated on           : 28 Jan 2022 11:45:45
 */
#include "Motorsteuerung_CAN.h"
#ifndef PLECS_HEADER_Motorsteuerung_CAN_h_
#error The wrong header file "Motorsteuerung_CAN.h" was included. Please
#error check your include path to see whether this file name conflicts with
#error the name of another header file.
#endif /* PLECS_HEADER_Motorsteuerung_CAN_h_ */
#if defined(__GNUC__) && (__GNUC__ > 4)
#   define _ALIGNMENT 16
#   define _RESTRICT __restrict
#   define _ALIGN __attribute__((aligned(_ALIGNMENT)))
#   if defined(__clang__)
#      if __has_builtin(__builtin_assume_aligned)
#         define _ASSUME_ALIGNED(a) __builtin_assume_aligned(a, _ALIGNMENT)
#      else
#         define _ASSUME_ALIGNED(a) a
#      endif
#   else
#      define _ASSUME_ALIGNED(a) __builtin_assume_aligned(a, _ALIGNMENT)
#   endif
#else
#   ifndef _RESTRICT
#      define _RESTRICT
#   endif
#   ifndef _ALIGN
#      define _ALIGN
#   endif
#   ifndef _ASSUME_ALIGNED
#      define _ASSUME_ALIGNED(a) a
#   endif
#endif
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include "plx_hal.h"
#define PLECSRunTimeError(msg) Motorsteuerung_CAN_errorStatus = msg
static const uint32_t Motorsteuerung_CAN_subTaskPeriod[1]= {
   /* [0.5, 0], [0, 0] */
   500
};
static uint32_t Motorsteuerung_CAN_subTaskTick[1];
static char Motorsteuerung_CAN_subTaskHit[1];
static const float Motorsteuerung_CAN_UNCONNECTED = 0;
static bool Motorsteuerung_CAN_D_bool[2];
static uint32_t Motorsteuerung_CAN_tickLo;
static int32_t Motorsteuerung_CAN_tickHi;
Motorsteuerung_CAN_BlockOutputs Motorsteuerung_CAN_B;
#if defined(EXTERNAL_MODE) && EXTERNAL_MODE
const float * const Motorsteuerung_CAN_ExtModeSignals[] = {
   &Motorsteuerung_CAN_B.DataProcessing_atArrivalOfNewDa[0],
   &Motorsteuerung_CAN_B.DataProcessing_atArrivalOfNewDa[1],
   &Motorsteuerung_CAN_B.DataProcessing_atArrivalOfNew_1[0],
   &Motorsteuerung_CAN_B.DataProcessing_atArrivalOfNew_1[1],
   &Motorsteuerung_CAN_B.DataProcessing_atArrivalOfNew_1[2],
   &Motorsteuerung_CAN_B.DataProcessing_atArrivalOfNewDa[0],
   &Motorsteuerung_CAN_B.DataProcessing_atArrivalOfNewDa[1],
   &Motorsteuerung_CAN_B.DataProcessing_atArrivalOfNew_1[0],
   &Motorsteuerung_CAN_B.DataProcessing_atArrivalOfNew_1[1],
   &Motorsteuerung_CAN_B.DataProcessing_atArrivalOfNew_1[2]
};
#endif /* defined(EXTERNAL_MODE) */
Motorsteuerung_CAN_Parameters Motorsteuerung_CAN_P = {
   /* Parameter 'Value' of
    *  Constant : 'Motorsteuerung_CAN/Sub/Constant'
    */
   0.f,
   /* Parameter 'Value' of
    *  Constant : 'Motorsteuerung_CAN/Sub/Constant2'
    */
   1.f,
   /* Parameter 'Value' of
    *  Constant : 'Motorsteuerung_CAN/Sub/Constant3'
    */
   52.3598776f,
   /* Parameter 'Value' of
    *  Constant : 'Motorsteuerung_CAN/Sub/Constant4'
    */
   2.f
};
Motorsteuerung_CAN_ModelStates Motorsteuerung_CAN_X _ALIGN;
const char * Motorsteuerung_CAN_errorStatus;
const float Motorsteuerung_CAN_sampleTime = 0.001f;
const char * const Motorsteuerung_CAN_checksum =
   "71bed93fd00fd535aa1788a6647a30c240f56141";
/* Target declarations */
extern void Motorsteuerung_CAN_initHal();
/* CAN Receive : 'Motorsteuerung_CAN/CAN Receive' */
static unsigned char Can0Mbox0Data[8] = {
   0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};
static bool Can0Mbox0DataReady;
/* CAN Receive : 'Motorsteuerung_CAN/CAN Receive1' */
static unsigned char Can0Mbox1Data[8] = {
   0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};
static bool Can0Mbox1DataReady;

void Motorsteuerung_CAN_initialize(float time)
{
   float remainder;
   size_t i;
   Motorsteuerung_CAN_errorStatus = NULL;
   Motorsteuerung_CAN_tickHi =
      floor(time/(4294967296.0*Motorsteuerung_CAN_sampleTime));
   remainder = time - Motorsteuerung_CAN_tickHi*4294967296.0*
               Motorsteuerung_CAN_sampleTime;
   Motorsteuerung_CAN_tickLo = floor(
                                     remainder/Motorsteuerung_CAN_sampleTime +
                                     .5);
   remainder -= Motorsteuerung_CAN_tickLo*Motorsteuerung_CAN_sampleTime;
   if (fabsf(remainder) > 1e-6*fabsf(time))
   {
      Motorsteuerung_CAN_errorStatus =
         "Start time must be an integer multiple of the base sample time.";
   }
   /* Initialize sub-task tick counters */
   Motorsteuerung_CAN_subTaskTick[0] = 0; /* [0, 0], [0.5, 0] */


   /* Offset sub-task tick counters */
   {
      uint32_t i, n, N, delta;
      N = abs(Motorsteuerung_CAN_tickHi);
      for (i = 0; i < 1; ++i)
      {
         delta = -Motorsteuerung_CAN_subTaskPeriod[i];
         delta %= Motorsteuerung_CAN_subTaskPeriod[i];
         if (Motorsteuerung_CAN_tickHi < 0)
         {
            delta = Motorsteuerung_CAN_subTaskPeriod[i] - delta;
         }
         for (n = 0; n < N; ++n)
         {
            Motorsteuerung_CAN_subTaskTick[i] =
               (Motorsteuerung_CAN_subTaskTick[i] +
                delta) % Motorsteuerung_CAN_subTaskPeriod[i];
         }
         Motorsteuerung_CAN_subTaskTick[i] =
            (Motorsteuerung_CAN_subTaskTick[i] + Motorsteuerung_CAN_tickLo %
             Motorsteuerung_CAN_subTaskPeriod[i]) %
            Motorsteuerung_CAN_subTaskPeriod[i];
      }
   }

   /* Target pre-initialization */
   Motorsteuerung_CAN_initHal();


   /* Initialization for Subsystem : 'Motorsteuerung_CAN/Data Processing\n(at arrival of new data)' */
   Motorsteuerung_CAN_B.DataProcessing_atArrivalOfNewDa[0] = 0.f;
   Motorsteuerung_CAN_B.DataProcessing_atArrivalOfNewDa[1] = 0.f;

   /* Initialization for Subsystem : 'Motorsteuerung_CAN/Data Processing\n(at arrival of new data)1' */
   Motorsteuerung_CAN_B.DataProcessing_atArrivalOfNew_1[0] = 0.f;
   Motorsteuerung_CAN_B.DataProcessing_atArrivalOfNew_1[1] = 0.f;
   Motorsteuerung_CAN_B.DataProcessing_atArrivalOfNew_1[2] = 0.f;

   /* Initialization for Delay : 'Motorsteuerung_CAN/Delay1' */
   Motorsteuerung_CAN_X.Delay1 = 0.f;
}

void Motorsteuerung_CAN_step(void)
{
   if (Motorsteuerung_CAN_errorStatus)
   {
      return;
   }
   {
      size_t i;
      for (i = 0; i < 1; ++i)
      {
         Motorsteuerung_CAN_subTaskHit[i] =
            (Motorsteuerung_CAN_subTaskTick[i] == 0);
      }
   }

   /* CAN Receive : 'Motorsteuerung_CAN/CAN Receive' */
   {
      Can0Mbox0DataReady = PLXHAL_CAN_getMessage(0, 0, &Can0Mbox0Data[0], 8);
   }
   Motorsteuerung_CAN_B.CANReceive[0] = Can0Mbox0Data[0];
   Motorsteuerung_CAN_B.CANReceive[1] = Can0Mbox0Data[1];
   Motorsteuerung_CAN_B.CANReceive[2] = Can0Mbox0Data[2];
   Motorsteuerung_CAN_B.CANReceive[3] = Can0Mbox0Data[3];
   Motorsteuerung_CAN_B.CANReceive[4] = Can0Mbox0Data[4];
   Motorsteuerung_CAN_B.CANReceive[5] = Can0Mbox0Data[5];
   Motorsteuerung_CAN_B.CANReceive[6] = Can0Mbox0Data[6];
   Motorsteuerung_CAN_B.CANReceive[7] = Can0Mbox0Data[7];
   Motorsteuerung_CAN_B.CANReceive[8] = Can0Mbox0DataReady;

   /* Subsystem : 'Motorsteuerung_CAN/Data Processing\n(at arrival of new data)' */
   Motorsteuerung_CAN_D_bool[0] = 0;
   Motorsteuerung_CAN_D_bool[0] = Motorsteuerung_CAN_D_bool[0] ||
                                  Motorsteuerung_CAN_B.CANReceive[8];
   if (Motorsteuerung_CAN_D_bool[0])
   {

      /* Signal Inport : 'Motorsteuerung_CAN/Data Processing\n(at arrival of new data)/d' */
      Motorsteuerung_CAN_B.d[0] = Motorsteuerung_CAN_B.CANReceive[0];
      Motorsteuerung_CAN_B.d[1] = Motorsteuerung_CAN_B.CANReceive[1];
      Motorsteuerung_CAN_B.d[2] = Motorsteuerung_CAN_B.CANReceive[2];
      Motorsteuerung_CAN_B.d[3] = Motorsteuerung_CAN_B.CANReceive[3];
      Motorsteuerung_CAN_B.d[4] = Motorsteuerung_CAN_B.CANReceive[4];
      Motorsteuerung_CAN_B.d[5] = Motorsteuerung_CAN_B.CANReceive[5];
      Motorsteuerung_CAN_B.d[6] = Motorsteuerung_CAN_B.CANReceive[6];
      Motorsteuerung_CAN_B.d[7] = Motorsteuerung_CAN_B.CANReceive[7];

      /* CAN Unpack : 'Motorsteuerung_CAN/Data Processing\n(at arrival of new data)/CAN Unpack' */
      {
         uint32_t val =
            (((uint32_t)(Motorsteuerung_CAN_B.d[0])) <<
            0)|(((uint32_t)((Motorsteuerung_CAN_B.d[1]) & 0x7f)) << 8);
         Motorsteuerung_CAN_B.CANUnpack[0]= ((float)val) * 1 + 0;
      }
      {
         uint32_t val =
            ((uint32_t)(((Motorsteuerung_CAN_B.d[1]) &
                         0x80) >>
                        7))|
            (((uint32_t)(Motorsteuerung_CAN_B.d[2])) <<
            1)|
            (((uint32_t)(Motorsteuerung_CAN_B.d[3])) <<
            9)|
            (((uint32_t)(Motorsteuerung_CAN_B.d[4])) <<
            17)|(((uint32_t)((Motorsteuerung_CAN_B.d[5]) & 0x7f)) << 25);
         float val2 = *((float*)&val);
         Motorsteuerung_CAN_B.CANUnpack[1]= ((float)val2) * 1 + 0;
      }
      Motorsteuerung_CAN_B.DataProcessing_atArrivalOfNewDa[0] =
         Motorsteuerung_CAN_B.CANUnpack[0];
      Motorsteuerung_CAN_B.DataProcessing_atArrivalOfNewDa[1] =
         Motorsteuerung_CAN_B.CANUnpack[1];
   }

   /* CAN Receive : 'Motorsteuerung_CAN/CAN Receive1' */
   {
      Can0Mbox1DataReady = PLXHAL_CAN_getMessage(0, 1, &Can0Mbox1Data[0], 8);
   }
   Motorsteuerung_CAN_B.CANReceive1[0] = Can0Mbox1Data[0];
   Motorsteuerung_CAN_B.CANReceive1[1] = Can0Mbox1Data[1];
   Motorsteuerung_CAN_B.CANReceive1[2] = Can0Mbox1Data[2];
   Motorsteuerung_CAN_B.CANReceive1[3] = Can0Mbox1Data[3];
   Motorsteuerung_CAN_B.CANReceive1[4] = Can0Mbox1Data[4];
   Motorsteuerung_CAN_B.CANReceive1[5] = Can0Mbox1Data[5];
   Motorsteuerung_CAN_B.CANReceive1[6] = Can0Mbox1Data[6];
   Motorsteuerung_CAN_B.CANReceive1[7] = Can0Mbox1Data[7];
   Motorsteuerung_CAN_B.CANReceive1[8] = Can0Mbox1DataReady;

   /* Subsystem : 'Motorsteuerung_CAN/Data Processing\n(at arrival of new data)1' */
   Motorsteuerung_CAN_D_bool[1] = 0;
   Motorsteuerung_CAN_D_bool[1] = Motorsteuerung_CAN_D_bool[1] ||
                                  Motorsteuerung_CAN_B.CANReceive1[8];
   if (Motorsteuerung_CAN_D_bool[1])
   {

      /* Signal Inport : 'Motorsteuerung_CAN/Data Processing\n(at arrival of new data)1/d' */
      Motorsteuerung_CAN_B.d_1[0] = Motorsteuerung_CAN_B.CANReceive1[0];
      Motorsteuerung_CAN_B.d_1[1] = Motorsteuerung_CAN_B.CANReceive1[1];
      Motorsteuerung_CAN_B.d_1[2] = Motorsteuerung_CAN_B.CANReceive1[2];
      Motorsteuerung_CAN_B.d_1[3] = Motorsteuerung_CAN_B.CANReceive1[3];
      Motorsteuerung_CAN_B.d_1[4] = Motorsteuerung_CAN_B.CANReceive1[4];
      Motorsteuerung_CAN_B.d_1[5] = Motorsteuerung_CAN_B.CANReceive1[5];
      Motorsteuerung_CAN_B.d_1[6] = Motorsteuerung_CAN_B.CANReceive1[6];
      Motorsteuerung_CAN_B.d_1[7] = Motorsteuerung_CAN_B.CANReceive1[7];

      /* CAN Unpack : 'Motorsteuerung_CAN/Data Processing\n(at arrival of new data)1/CAN Unpack' */
      {
         uint32_t val =
            (((uint32_t)(Motorsteuerung_CAN_B.d_1[0])) <<
            0)|
            (((uint32_t)(Motorsteuerung_CAN_B.d_1[1])) <<
            8)|
            (((uint32_t)(Motorsteuerung_CAN_B.d_1[2])) <<
            16)|(((uint32_t)(Motorsteuerung_CAN_B.d_1[3])) << 24);
         float val2 = *((float*)&val);
         Motorsteuerung_CAN_B.CANUnpack_1[0]= ((float)val2) * 1 + 0;
      }
      {
         uint32_t val =
            (((uint32_t)(Motorsteuerung_CAN_B.d_1[4])) <<
            0)|
            (((uint32_t)(Motorsteuerung_CAN_B.d_1[5])) <<
            8)|
            (((uint32_t)(Motorsteuerung_CAN_B.d_1[6])) <<
            16)|(((uint32_t)(Motorsteuerung_CAN_B.d_1[7])) << 24);
         float val2 = *((float*)&val);
         Motorsteuerung_CAN_B.CANUnpack_1[1]= ((float)val2) * 1 + 0;
      }
      Motorsteuerung_CAN_B.DataProcessing_atArrivalOfNew_1[0] =
         Motorsteuerung_CAN_B.CANUnpack_1[0];
      Motorsteuerung_CAN_B.DataProcessing_atArrivalOfNew_1[1] =
         Motorsteuerung_CAN_B.CANUnpack_1[1];
      Motorsteuerung_CAN_B.DataProcessing_atArrivalOfNew_1[2] =
         -Motorsteuerung_CAN_B.CANUnpack_1[1] -
         Motorsteuerung_CAN_B.CANUnpack_1[0];
   }

   /* CAN Port : 'Motorsteuerung_CAN/CAN Port' */
   {
      static bool lastBusOn = false;
      bool busOn = 1.f;
      if(!busOn)
      {
         PLXHAL_CAN_setBusOn(0, false);
      }
      else if (!lastBusOn)
      {
         PLXHAL_CAN_setBusOn(0, true);
      }
      lastBusOn = busOn;
   }
   if (Motorsteuerung_CAN_subTaskHit[0])
   {
      /* Delay : 'Motorsteuerung_CAN/Delay1' */
      Motorsteuerung_CAN_B.Delay1 = Motorsteuerung_CAN_X.Delay1;

      /* Logical Operator : 'Motorsteuerung_CAN/Logical\nOperator1' */
      Motorsteuerung_CAN_B.LogicalOperator1 = !Motorsteuerung_CAN_B.Delay1;
   }

   /* Digital Out : 'Motorsteuerung_CAN/LED' */
   PLXHAL_DIO_set(0, Motorsteuerung_CAN_B.LogicalOperator1);

   /* CAN Pack : 'Motorsteuerung_CAN/Sub/CAN Pack' */
   Motorsteuerung_CAN_B.CANPack[0]=
      ((Motorsteuerung_CAN_B.CANPack[0]) &
       0xfe) |
      (((uint8_t) !!((bool)Motorsteuerung_CAN_P.Constant_Value)) << 0)
   ;
   Motorsteuerung_CAN_B.CANPack[0]=
      ((Motorsteuerung_CAN_B.CANPack[0]) &
       0xfd) |
      (((uint8_t) !!((bool)Motorsteuerung_CAN_P.Constant2_Value)) << 1)
   ;
   {
      float curInput = Motorsteuerung_CAN_P.Constant3_Value;
      float scaledInput = ((curInput) - 0) * 1;
      uint32_t val = *((uint32_t*)&scaledInput) & 0xffffffff;
      Motorsteuerung_CAN_B.CANPack[0] =
         (Motorsteuerung_CAN_B.CANPack[0] & 0x3) | (((val) & 0x3f) << 2);
      Motorsteuerung_CAN_B.CANPack[1] = ((val) & 0x3fc0) >> 6;
      Motorsteuerung_CAN_B.CANPack[2] = ((val) & 0x3fc000) >> 14;
      Motorsteuerung_CAN_B.CANPack[3] = ((val) & 0x3fc00000) >> 22;
      Motorsteuerung_CAN_B.CANPack[4] =
         (Motorsteuerung_CAN_B.CANPack[4] &
          0xfc) | (((val) & 0xc0000000) >> 30);
   }
   {
      float curInput = (int16_t)Motorsteuerung_CAN_P.Constant4_Value;
      int32_t scaledInput = ((curInput) - 0) * 1;
      uint32_t val = *((uint32_t*)&scaledInput) & 0xffff;
      Motorsteuerung_CAN_B.CANPack[4] =
         (Motorsteuerung_CAN_B.CANPack[4] & 0x3) | (((val) & 0x3f) << 2);
      Motorsteuerung_CAN_B.CANPack[5] = ((val) & 0x3fc0) >> 6;
      Motorsteuerung_CAN_B.CANPack[6] =
         (Motorsteuerung_CAN_B.CANPack[6] & 0xfc) | (((val) & 0xc000) >> 14);
   }

   /* CAN Transmit : 'Motorsteuerung_CAN/CAN Transmit' */
   {
      unsigned char canData[] = {
         Motorsteuerung_CAN_B.CANPack[0], Motorsteuerung_CAN_B.CANPack[1],
         Motorsteuerung_CAN_B.CANPack[2], Motorsteuerung_CAN_B.CANPack[3],
         Motorsteuerung_CAN_B.CANPack[4], Motorsteuerung_CAN_B.CANPack[5],
         Motorsteuerung_CAN_B.CANPack[6]
      };
      PLXHAL_CAN_putMessage(0, 2, canData, 7);
   }
   if (Motorsteuerung_CAN_errorStatus)
   {
      return;
   }

   /* Update for Subsystem : 'Motorsteuerung_CAN/Data Processing\n(at arrival of new data)' */
   Motorsteuerung_CAN_X.DataProcessing_atArrivalOfNewDa =
      Motorsteuerung_CAN_D_bool[0];

   /* Update for Subsystem : 'Motorsteuerung_CAN/Data Processing\n(at arrival of new data)1' */
   Motorsteuerung_CAN_X.DataProcessing_atArrivalOfNew_1 =
      Motorsteuerung_CAN_D_bool[1];
   if (Motorsteuerung_CAN_subTaskHit[0])
   {
      /* Update for Delay : 'Motorsteuerung_CAN/Delay1' */
      Motorsteuerung_CAN_X.Delay1 = Motorsteuerung_CAN_B.LogicalOperator1;
   }

   /* Increment sub-task tick counters */
   {
      size_t i;
      for (i = 0; i < 1; ++i)
      {
         Motorsteuerung_CAN_subTaskTick[i]++;
         if (Motorsteuerung_CAN_subTaskTick[i] >=
             Motorsteuerung_CAN_subTaskPeriod[i])
         {
            Motorsteuerung_CAN_subTaskTick[i] = 0;
         }
      }
   }
}

void Motorsteuerung_CAN_terminate()
{
}
