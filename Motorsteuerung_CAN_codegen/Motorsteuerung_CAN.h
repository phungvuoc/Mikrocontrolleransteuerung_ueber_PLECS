/*
 * Header file for: Motorsteuerung_CAN
 * Generated with : PLECS 4.5.8
 *                  TI2837xS 1.4.4
 * Generated on   : 28 Jan 2022 11:45:45
 */
#ifndef PLECS_HEADER_Motorsteuerung_CAN_h_
#define PLECS_HEADER_Motorsteuerung_CAN_h_

#include <stdbool.h>
#include <stdint.h>

/* Target declarations */
typedef int_fast8_t int8_t;
typedef uint_fast8_t uint8_t;
extern void Motorsteuerung_CAN_background(void);


/* Model floating point type */
typedef float Motorsteuerung_CAN_FloatType;

/* Model checksum */
extern const char * const Motorsteuerung_CAN_checksum;

/* Model error status */
extern const char * Motorsteuerung_CAN_errorStatus;


/* Model sample time */
extern const float Motorsteuerung_CAN_sampleTime;


/*
 * Model states */
typedef struct
{
   float DataProcessing_atArrivalOfNewDa; /* Motorsteuerung_CAN/Data Processing (at arrival of new data) */
   float DataProcessing_atArrivalOfNew_1; /* Motorsteuerung_CAN/Data Processing (at arrival of new data)1 */
   bool Delay1;                     /* Motorsteuerung_CAN/Delay1 */
} Motorsteuerung_CAN_ModelStates;
extern Motorsteuerung_CAN_ModelStates Motorsteuerung_CAN_X;


/* Block outputs */
typedef struct
{
   float CANUnpack[2];              /* Motorsteuerung_CAN/Data Processing (at arrival of new data)/CAN Unpack */
   uint8_t d[8];                    /* Motorsteuerung_CAN/Data Processing (at arrival of new data)/d */
   float DataProcessing_atArrivalOfNewDa[2]; /* Motorsteuerung_CAN/Data Processing (at arrival of new data) */
   float CANUnpack_1[2];            /* Motorsteuerung_CAN/Data Processing (at arrival of new data)1/CAN Unpack */
   uint8_t d_1[8];                  /* Motorsteuerung_CAN/Data Processing (at arrival of new data)1/d */
   float DataProcessing_atArrivalOfNew_1[3]; /* Motorsteuerung_CAN/Data Processing (at arrival of new data)1 */
   bool LogicalOperator1;           /* Motorsteuerung_CAN/Logical Operator1 */
   uint8_t CANPack[7];              /* Motorsteuerung_CAN/Sub/CAN Pack */
   uint8_t CANReceive[9];           /* Motorsteuerung_CAN/CAN Receive */
   uint8_t CANReceive1[9];          /* Motorsteuerung_CAN/CAN Receive1 */
   bool Delay1;                     /* Motorsteuerung_CAN/Delay1 */
} Motorsteuerung_CAN_BlockOutputs;
extern Motorsteuerung_CAN_BlockOutputs Motorsteuerung_CAN_B;

#if defined(EXTERNAL_MODE) && EXTERNAL_MODE
/* External mode signals */
#define Motorsteuerung_CAN_NumExtModeSignals 10
extern const float * const Motorsteuerung_CAN_ExtModeSignals[];
/* Tunable parameters */
#define Motorsteuerung_CAN_NumTunableParameters 4
#endif /* defined(EXTERNAL_MODE) */


/* Block parameters */
typedef struct
{
   /* Parameter 'Value' of
    *  Constant : 'Motorsteuerung_CAN/Sub/Constant'
    */
   float Constant_Value;
   /* Parameter 'Value' of
    *  Constant : 'Motorsteuerung_CAN/Sub/Constant2'
    */
   float Constant2_Value;
   /* Parameter 'Value' of
    *  Constant : 'Motorsteuerung_CAN/Sub/Constant3'
    */
   float Constant3_Value;
   /* Parameter 'Value' of
    *  Constant : 'Motorsteuerung_CAN/Sub/Constant4'
    */
   float Constant4_Value;
} Motorsteuerung_CAN_Parameters;
extern Motorsteuerung_CAN_Parameters Motorsteuerung_CAN_P;

/* Entry point functions */
void Motorsteuerung_CAN_initialize(float time);
void Motorsteuerung_CAN_step(void);
void Motorsteuerung_CAN_terminate(void);

#endif /* PLECS_HEADER_Motorsteuerung_CAN_h_ */
