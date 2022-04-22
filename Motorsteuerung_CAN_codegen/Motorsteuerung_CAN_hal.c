/*
 * Hardware configuration file for: TI2837xS
 * Generated with                 : PLECS 4.5.8
 * Generated on                   : Fri Jan 28 11:45:45 2022
 */

#include "plx_hal.h"
#include "plx_dispatcher.h"
#include "pil.h"
#include "Motorsteuerung_CAN.h"
#include "plx_sci.h"
#include "plx_canbus.h"
#include "plx_dio.h"

void DevInit(Uint16 clock_source, Uint16 imult, Uint16 fmult);
void InitFlashHz(Uint32 clkHz);
void DSP28x_usDelay(long LoopCount);

// Clock configurations
#define SYSCLK_HZ 190000000L
#define SYSCLK_WC_HI_HZ 196000000L
#define LSPCLK_HZ (SYSCLK_HZ / 4l)
#define PLL_SYSCLK_DIV 1
#define PLL_FMULT 0
#define PLL_IMULT 38
#define PLL_SRC 0
#define PLX_DELAY_US(A)  DSP28x_usDelay( \
                                        ((((long double) A * \
                                           1000.0L) / \
                                          5.263158L) - 9.0L) / 5.0L)

PIL_Obj_t PilObj;
PIL_Handle_t PilHandle = 0;
PLX_SCI_Obj_t SciObj;
PLX_SCI_Handle_t SciHandle;
uint16_t ScopeBuffer[1020] /*__attribute__((aligned(16)))*/;
extern void PIL_setAndConfigScopeBuffer(PIL_Handle_t aPilHandle,
                                        uint16_t* aBufPtr, uint16_t aBufSize,
                                        uint16_t aMaxTraceWidthInWords);
extern const char * const Motorsteuerung_CAN_checksum;

// external mode helper symbols

PIL_CONFIG_DEF(uint32_t, ExtMode_targetFloat_Size,
               sizeof(Motorsteuerung_CAN_FloatType));

PIL_CONFIG_DEF(uint32_t, ExtMode_targetPointer_Size,
               sizeof(Motorsteuerung_CAN_FloatType*));

PIL_CONFIG_DEF(uint32_t, ExtMode_sampleTime_Ptr,
               (uint32_t)&Motorsteuerung_CAN_sampleTime);

PIL_CONFIG_DEF(uint32_t, ExtMode_checksum_Ptr,
               (uint32_t)&Motorsteuerung_CAN_checksum);

#if defined(Motorsteuerung_CAN_NumTunableParameters) && \
   (Motorsteuerung_CAN_NumTunableParameters > 0)

PIL_CONFIG_DEF(uint32_t, ExtMode_P_Ptr, (uint32_t)&Motorsteuerung_CAN_P);

PIL_CONFIG_DEF(uint32_t, ExtMode_P_Size,
               (uint32_t)Motorsteuerung_CAN_NumTunableParameters);

#endif

#if defined(Motorsteuerung_CAN_NumExtModeSignals) && \
   (Motorsteuerung_CAN_NumExtModeSignals > 0)

PIL_CONFIG_DEF(uint32_t, ExtMode_ExtModeSignals_Ptr,
               (uint32_t)&Motorsteuerung_CAN_ExtModeSignals[0]);

PIL_CONFIG_DEF(uint32_t, ExtMode_ExtModeSignals_Size,
               (uint32_t)Motorsteuerung_CAN_NumExtModeSignals);

#endif


#define CODE_GUID {0x09, 0x3c, 0x97, 0x5e, 0xdb, 0x2d, 0xb8, 0x40};
PIL_CONST_DEF(unsigned char, Guid[], CODE_GUID);
PIL_CONST_DEF(unsigned char, CompiledDate[], "01/28/2022 11:45 AM");
PIL_CONST_DEF(unsigned char, CompiledBy[], "PLECS Coder");
PIL_CONST_DEF(uint16_t, FrameworkVersion, PIL_FRAMEWORK_VERSION);
PIL_CONST_DEF(char, FirmwareDescription[], "TIC2000 Project");
PIL_CONST_DEF(uint16_t, StationAddress, 0);
PIL_CONST_DEF(uint32_t, BaudRate, 14400);
static void SciPoll(PIL_Handle_t aHandle)
{
   if(PLX_SCI_breakOccurred(SciHandle))
   {
      PLX_SCI_reset(SciHandle);
   }

   while(PLX_SCI_rxReady(SciHandle))
   {
      // assuming that there will be a "break" when FIFO is empty
      PIL_SERIAL_IN(aHandle, (int16)PLX_SCI_getChar(SciHandle));
   }

   int16_t ch;
   if(!PLX_SCI_txIsBusy(SciHandle))
   {
      if(PIL_SERIAL_OUT(aHandle, &ch))
      {
         PLX_SCI_putChar(SciHandle, ch);
      }
   }
}

PLX_CANBUS_Handle_t CanHandles[1];
PLX_CANBUS_Obj_t CanObj[1];
bool PLXHAL_CAN_getMessage(uint16_t aChannel, uint16_t aMailBox,
                           unsigned char data[], unsigned char lenMax)
{
   return PLX_CANBUS_getMessage(CanHandles[aChannel], aMailBox, data, lenMax);
}
void PLXHAL_CAN_putMessage(uint16_t aChannel, uint16_t aMailBox,
                           unsigned char data[], unsigned char len)
{
   (void)PLX_CANBUS_putMessage(CanHandles[aChannel], aMailBox, data, len);
}
void PLXHAL_CAN_setBusOn(uint16_t aChannel, bool aBusOn)
{
   PLX_CANBUS_setBusOn(CanHandles[aChannel], aBusOn);
}
bool PLXHAL_CAN_getIsBusOn(uint16_t aChannel)
{
   return PLX_CANBUS_isBusOn(CanHandles[aChannel]);
}
bool PLXHAL_CAN_getIsErrorActive(uint16_t aChannel)
{
   return PLX_CANBUS_isErrorActive(CanHandles[aChannel]);
}
PLX_DIO_Handle_t DoutHandles[1];
PLX_DIO_Obj_t DoutObj[1];
void PLXHAL_DIO_set(uint16_t aHandle, bool aVal)
{
   PLX_DIO_set(DoutHandles[aHandle], aVal);
}
interrupt void Motorsteuerung_CAN_baseTaskInterrupt(void)
{
   CpuTimer0Regs.TCR.bit.TIF = 1;
   PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
   IER |= M_INT1;
   DISPR_dispatch();
}


extern PIL_Handle_t PilHandle;
DISPR_TaskObj_t TaskObj[1];
extern void Motorsteuerung_CAN_step();
extern void Motorsteuerung_CAN_enableTasksInterrupt();
extern void Motorsteuerung_CAN_syncTimers();
static void Tasks(bool aInit, void * const aParam)
{
   if(aInit)
   {
      Motorsteuerung_CAN_enableTasksInterrupt();
   }
   else
   {
      Motorsteuerung_CAN_step();
   }
}



void Motorsteuerung_CAN_enableTasksInterrupt(void)
{
   IER |= M_INT1;
}

void Motorsteuerung_CAN_syncTimers(void)
{
   CpuTimer0Regs.TCR.bit.TSS = 0;
}

void Motorsteuerung_CAN_background(void)
{

}

static bool HalInitialized = false;
void Motorsteuerung_CAN_initHal()
{
   if(HalInitialized == true)
   {
      return;
   }
   HalInitialized = true;
   DevInit(PLL_SRC, PLL_IMULT, PLL_FMULT);
   InitFlashHz(SYSCLK_WC_HI_HZ);
   // set cpu timers to same clock as ePWM
   CpuTimer0Regs.TPR.all = 3;
   CpuTimer1Regs.TPR.all = 3;
   CpuTimer2Regs.TPR.all = 3;
   EALLOW;
   CpuSysRegs.PCLKCR0.bit.CPUTIMER0 = 1;
   CpuSysRegs.PCLKCR0.bit.CPUTIMER1 = 1;
   CpuSysRegs.PCLKCR0.bit.CPUTIMER2 = 1;
   CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;      // stop all the TB clocks
   ClkCfgRegs.PERCLKDIVSEL.bit.EPWMCLKDIV = 1;
   EDIS;

   SciHandle = PLX_SCI_init(&SciObj, sizeof(SciObj));
   PLX_SCI_configure(SciHandle, 2, 47500000);
   (void)PLX_SCI_setupPort(SciHandle, 14400);
   PilHandle = PIL_init(&PilObj, sizeof(PilObj));
   PIL_setGuid(PilHandle, PIL_GUID_PTR);
   PIL_setChecksum(PilHandle, Motorsteuerung_CAN_checksum);
   PIL_setAndConfigScopeBuffer(PilHandle, (uint16_t *)&ScopeBuffer, 1020, 20);
   PIL_setSerialComCallback(PilHandle, (PIL_CommCallbackPtr_t)SciPoll);
   {
      PLX_CANBUS_sinit();
      int i;
      for(i=0; i < 1; i++)
      {
         CanHandles[i] = PLX_CANBUS_init(&CanObj[i], sizeof(CanObj[i]));
      }
   }
   // Configure CAN B at 250000.000 Bit/s, with sampling at 60.0%
   {
      PLX_CANBUS_Params_t params;
      params.tseg1 = 5;
      params.tseg2 = 4;
      params.sjw = 4;
      params.sam = 0;
      params.brp = 76;
      params.autoBusOn = 1;
      PLX_CANBUS_configure(CanHandles[0], PLX_CANBUS_CAN_B, 10, &params);
      (void)PLX_CANBUS_setupMailbox(CanHandles[0], 1, 0, 3, 0, 8);
      (void)PLX_CANBUS_setupMailbox(CanHandles[0], 2, 1, 1, 0, 7);
      (void)PLX_CANBUS_setupMailbox(CanHandles[0], 0, 0, 2, 0, 8);
   }
   {
      PLX_DIO_sinit();
      int i;
      for(i=0; i < 1; i++)
      {
         DoutHandles[i] = PLX_DIO_init(&DoutObj[i], sizeof(DoutObj[i]));
      }
   }

   {
      PLX_DIO_OutputProperties_t props = {
         0
      };
      props.type = PLX_DIO_PUSHPULL;
      props.enableInvert = false;
      PLX_DIO_configureOut(DoutHandles[0], 34,  &props);
   }
   {
      CpuTimer0Regs.TCR.bit.TSS = 1;   // stop timer
      CpuTimer0Regs.TPRH.all = 0;
      CpuTimer0Regs.PRD.all = 47500-1;
      CpuTimer0Regs.TCR.bit.TRB = 1;   // reload period
      CpuTimer0Regs.TCR.bit.TIE = 1;   // enable trigger to SOC/interrupt
      PieCtrlRegs.PIEIER1.bit.INTx7 = 1;
      EALLOW;
      PieVectTable.TIMER0_INT = &Motorsteuerung_CAN_baseTaskInterrupt;
      EDIS;
      PieCtrlRegs.PIEIER1.bit.INTx7 = 1;
      PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;           // acknowledge interrupt to PIE

   }
   DISPR_sinit();
   DISPR_configure((uint32_t)(47500), PilHandle, &TaskObj[0],
                   sizeof(TaskObj)/sizeof(DISPR_TaskObj_t));
   DISPR_registerIdleTask(&Motorsteuerung_CAN_background);
   DISPR_registerSyncCallback(&Motorsteuerung_CAN_syncTimers);
   DISPR_setPowerupDelay(1);
   {
      static int taskId = 0;
      // Task 0 at 1.000000e+03 Hz
      DISPR_registerTask(0, &Tasks, 47500L, (void *)&taskId);
   }

   // Post init code (for modules that depend on other modules)

}
