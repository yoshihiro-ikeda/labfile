/*
 * File: mdl5.h
 *
 * Code generated for Simulink model 'mdl5'.
 *
 * Model version                  : 1.17
 * Simulink Coder version         : 8.6 (R2014a) 27-Dec-2013
 * C/C++ source code generated on : Tue Mar  8 17:18:38 2016
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Specified
 * Emulation hardware selection:
 *    Differs from embedded hardware (32-bit Generic)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_mdl5_h_
#define RTW_HEADER_mdl5_h_
#include <math.h>
#include <string.h>
#ifndef mdl5_COMMON_INCLUDES_
# define mdl5_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* mdl5_COMMON_INCLUDES_ */

#include "mdl5_types.h"
#include "rt_zcfcn.h"
#include "rt_look.h"
#include "rt_look1d.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block signals (auto storage) */
typedef struct {
  real_T mdl5_SwitchController_Numerical[57];/* '<S3>/NumericalUnity' */
} BlockIO_mdl5;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T Block7838_DSTATE;             /* '<S1>/Block7838' */
  real_T Block7853_DSTATE;             /* '<S5>/Block7853' */
  real_T Block7852_DSTATE;             /* '<S5>/Block7852' */
  real_T DSM36[3];                     /* '<S2>/Block7884' */
  real_T DSM43;                        /* '<S2>/Block7885' */
  real_T DSM102[3];                    /* '<S2>/Block7886' */
  real_T DSM104[3];                    /* '<S2>/Block7887' */
  real_T DSM106[3];                    /* '<S2>/Block7888' */
  real_T DSM108[3];                    /* '<S2>/Block7889' */
  real_T DSM110[3];                    /* '<S2>/Block7890' */
  real_T DSM112[3];                    /* '<S2>/Block7891' */
  real_T DSM115[3];                    /* '<S2>/Block7892' */
  real_T DSM116[3];                    /* '<S2>/Block7893' */
  real_T DSM119[3];                    /* '<S2>/Block7894' */
  real_T DSM120[3];                    /* '<S2>/Block7895' */
  real_T DSM147[3];                    /* '<S2>/Block7896' */
  real_T DSM318[3];                    /* '<S2>/Block7897' */
  real_T DSM319[3];                    /* '<S2>/Block7898' */
  real_T DSM320[3];                    /* '<S2>/Block7899' */
  real_T DSM321[3];                    /* '<S2>/Block7900' */
  real_T DSM322;                       /* '<S2>/Block7901' */
  real_T DSM323;                       /* '<S2>/Block7902' */
  real_T DSM324;                       /* '<S2>/Block7903' */
  real_T DSM325;                       /* '<S2>/Block7904' */
  real_T DSM326;                       /* '<S2>/Block7905' */
  real_T DSM327;                       /* '<S2>/Block7906' */
  real_T DSM328;                       /* '<S2>/Block7907' */
  real_T DSM329;                       /* '<S2>/Block7908' */
  real_T DSM330;                       /* '<S2>/Block7909' */
  real_T DSM331;                       /* '<S2>/Block7910' */
  real_T DSM332;                       /* '<S2>/Block7911' */
  real_T DSM333[3];                    /* '<S2>/Block7912' */
  real_T DSM334[3];                    /* '<S2>/Block7913' */
  real_T DSM335[3];                    /* '<S2>/Block7914' */
  real_T DSM336[3];                    /* '<S2>/Block7915' */
  real_T DSM337[3];                    /* '<S2>/Block7916' */
  real_T DSM338;                       /* '<S2>/Block7917' */
  real_T DSM339;                       /* '<S2>/Block7918' */
  real_T DSM340;                       /* '<S2>/Block7919' */
  real_T DSM341;                       /* '<S2>/Block7920' */
  real_T DSM342;                       /* '<S2>/Block7921' */
  real_T DSM343[5];                    /* '<S2>/Block7922' */
  real_T DSM344;                       /* '<S2>/Block7923' */
  real_T DSM345;                       /* '<S2>/Block7924' */
  real_T DSM346[3];                    /* '<S2>/Block7925' */
  real_T DSM347[3];                    /* '<S2>/Block7926' */
  real_T DSM348[3];                    /* '<S2>/Block7927' */
  real_T DSM349[3];                    /* '<S2>/Block7928' */
  real_T DSM350[5];                    /* '<S2>/Block7929' */
  real_T DSM351[5];                    /* '<S2>/Block7930' */
  real_T DSM352;                       /* '<S2>/Block7931' */
  real_T DSM353;                       /* '<S2>/Block7932' */
  real_T DSM354;                       /* '<S2>/Block7933' */
  real_T DSM355;                       /* '<S2>/Block7934' */
  real_T DSM356;                       /* '<S2>/Block7935' */
  real_T DSM122[3];                    /* '<S2>/Block7936' */
  real_T DSM123[3];                    /* '<S2>/Block7937' */
  real_T DSM125[3];                    /* '<S2>/Block7938' */
  real_T DSM126[3];                    /* '<S2>/Block7939' */
  real_T DSM361;                       /* '<S2>/Block7940' */
  real_T DSM97[3];                     /* '<S2>/Block7941' */
  real_T DSM304[3];                    /* '<Root>/Block7769' */
  struct {
    void *TimePtr;
    void *DataPtr;
    void *RSimInfoPtr;
  } Block7776_PWORK;                   /* '<Root>/Block7776' */

  struct {
    void *TimePtr;
    void *DataPtr;
    void *RSimInfoPtr;
  } Block7773_PWORK;                   /* '<Root>/Block7773' */

  struct {
    void *TimePtr;
    void *DataPtr;
    void *RSimInfoPtr;
  } Block7772_PWORK;                   /* '<Root>/Block7772' */

  struct {
    void *TimePtr;
    void *DataPtr;
    void *RSimInfoPtr;
  } Block7774_PWORK;                   /* '<Root>/Block7774' */

  struct {
    void *TimePtr;
    void *DataPtr;
    void *RSimInfoPtr;
  } Block7775_PWORK;                   /* '<Root>/Block7775' */

  struct {
    int_T PrevIndex;
  } Block7776_IWORK;                   /* '<Root>/Block7776' */

  struct {
    int_T PrevIndex;
  } Block7773_IWORK;                   /* '<Root>/Block7773' */

  struct {
    int_T PrevIndex;
  } Block7772_IWORK;                   /* '<Root>/Block7772' */

  struct {
    int_T PrevIndex;
  } Block7774_IWORK;                   /* '<Root>/Block7774' */

  struct {
    int_T PrevIndex;
  } Block7775_IWORK;                   /* '<Root>/Block7775' */
} D_Work_mdl5;

/* Zero-crossing (trigger) state */
typedef struct {
  ZCSigState SubSystem2691_Trig_ZCE;   /* '<S2>/SubSystem2691' */
  ZCSigState SubSystem2612_Trig_ZCE;   /* '<S2>/SubSystem2612' */
} PrevZCSigStates_mdl5;

/* Constant parameters (auto storage) */
typedef struct {
  /* Expression: map_mr4_01
   * Referenced by: '<S73>/Block8122'
   */
  real_T Block8122_XData[47];

  /* Expression: map_mr4_02
   * Referenced by: '<S73>/Block8122'
   */
  real_T Block8122_YData[47];

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by:
   *   '<S73>/Block8123'
   *   '<S73>/Block8124'
   */
  real_T pooled8[51];

  /* Expression: map_mr4_04
   * Referenced by: '<S73>/Block8123'
   */
  real_T Block8123_YData[51];

  /* Expression: map_mr4_06
   * Referenced by: '<S73>/Block8124'
   */
  real_T Block8124_YData[51];

  /* Expression: map_mr4_07
   * Referenced by: '<S73>/Block8125'
   */
  real_T Block8125_XData[51];

  /* Expression: map_mr4_08
   * Referenced by: '<S73>/Block8125'
   */
  real_T Block8125_YData[51];
} ConstParam_mdl5;

/* Real-time Model Data Structure */
struct tag_RTM_mdl5 {
  const char_T * volatile errorStatus;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
  } Timing;
};

/* Block signals (auto storage) */
extern BlockIO_mdl5 mdl5_B;

/* Block states (auto storage) */
extern D_Work_mdl5 mdl5_DWork;

/* Constant parameters (auto storage) */
extern const ConstParam_mdl5 mdl5_ConstP;

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern real_T mdl5_Block7746_1;        /* '<Root>/Block7746' */
extern real_T mdl5_Block7747_1;        /* '<Root>/Block7747' */
extern real_T mdl5_Block7748_1;        /* '<Root>/Block7748' */
extern real_T mdl5_Block7749_1[3];     /* '<Root>/Block7749' */
extern real_T mdl5_Block7750_1[3];     /* '<Root>/Block7750' */
extern real_T mdl5_Block7751_1[3];     /* '<Root>/Block7751' */
extern real_T mdl5_Block7752_1[3];     /* '<Root>/Block7752' */
extern real_T mdl5_Block7753_1[3];     /* '<Root>/Block7753' */
extern real_T mdl5_Block7754_1[3];     /* '<Root>/Block7754' */
extern real_T mdl5_Block7755_1[3];     /* '<Root>/Block7755' */
extern real_T mdl5_Block7756_1[3];     /* '<Root>/Block7756' */
extern real_T mdl5_Block7757_1[3];     /* '<Root>/Block7757' */
extern real_T mdl5_Block7758_1[3];     /* '<Root>/Block7758' */
extern real_T mdl5_Block7759_1[3];     /* '<Root>/Block7759' */
extern real_T mdl5_Block7760_1[3];     /* '<Root>/Block7760' */
extern real_T mdl5_Block7761_1[3];     /* '<Root>/Block7761' */
extern real_T mdl5_Block7762_1[3];     /* '<Root>/Block7762' */
extern real_T mdl5_Block7763_1[3];     /* '<Root>/Block7763' */
extern real_T mdl5_Block7764_1[3];     /* '<Root>/Block7764' */
extern real_T mdl5_Block7765_1[3];     /* '<Root>/Block7765' */
extern real_T mdl5_Block7766_1[3];     /* '<Root>/Block7766' */
extern real_T mdl5_Block7830_1;        /* '<Root>/Block7830' */
extern real_T mdl5_SubSystem2601_Block7836_1;/* '<S1>/Block7836' */
extern real_T mdl5_SubSystem2601_Block7838_1;/* '<S1>/Block7838' */
extern real_T mdl5_Block7776_1;        /* '<Root>/Block7776' */
extern real_T mdl5_SubSystem2601_SubSystem2603_Block7853_1;/* '<S5>/Block7853' */
extern real_T mdl5_SubSystem2601_SubSystem2603_SubSystem2608_RO1_1;/* '<S10>/RO1' */
extern real_T mdl5_Block7768_1;        /* '<Root>/Block7768' */
extern real_T mdl5_SubSystem2601_SubSystem2603_Block7843_1;/* '<S5>/Block7843' */
extern real_T mdl5_SubSystem2601_SubSystem2603_Block7845_1;/* '<S5>/Block7845' */
extern real_T mdl5_Block7767_1;        /* '<Root>/Block7767' */
extern real_T mdl5_Block7773_1;        /* '<Root>/Block7773' */
extern real_T mdl5_SubSystem2601_SubSystem2603_Block7844_1;/* '<S5>/Block7844' */
extern real_T mdl5_SubSystem2601_SubSystem2603_Block7846_1;/* '<S5>/Block7846' */
extern real_T mdl5_SubSystem2601_SubSystem2603_Block7852_1;/* '<S5>/Block7852' */
extern real_T mdl5_SubSystem2601_SubSystem2603_Block7850_1;/* '<S5>/Block7850' */
extern real_T mdl5_SubSystem2601_SubSystem2603_Block7851_1;/* '<S5>/Block7851' */
extern real_T mdl5_SubSystem2601_SubSystem2603_Block7847_1;/* '<S5>/Block7847' */
extern real_T mdl5_SubSystem2601_SubSystem2603_Block7848_1;/* '<S5>/Block7848' */
extern real_T mdl5_SubSystem2601_SubSystem2603_SubSystem2609_Block7857_1;/* '<S11>/Block7857' */
extern real_T mdl5_SubSystem2601_SubSystem2603_SubSystem2609_Block7856_1;/* '<S11>/Block7856' */
extern real_T mdl5_SubSystem2601_SubSystem2603_SubSystem2609_SubSystem2610_RO1_1;/* '<S14>/RO1' */
extern real_T mdl5_SubSystem2601_SubSystem2603_SubSystem2609_SubSystem2610_RO2_1;/* '<S14>/RO2' */
extern real_T mdl5_SubSystem2601_SubSystem2603_SubSystem2609_SubSystem2610_LO1_1;/* '<S14>/LO1' */
extern real_T mdl5_SubSystem2601_SubSystem2603_SubSystem2609_Block7858_1;/* '<S11>/Block7858' */
extern real_T mdl5_SubSystem2601_SubSystem2603_Block7849_1;/* '<S5>/Block7849' */
extern real_T mdl5_SubSystem2601_SubSystem2602_RO1_1;/* '<S4>/RO1' */
extern real_T mdl5_SubSystem2601_Block7835_1;/* '<S1>/Block7835' */
extern real_T mdl5_SubSystem2601_Block7837_1;/* '<S1>/Block7837' */
extern real_T mdl5_Block7772_1;        /* '<Root>/Block7772' */
extern real_T mdl5_Block7774_1;        /* '<Root>/Block7774' */
extern real_T mdl5_Block7775_1;        /* '<Root>/Block7775' */
extern real_T mdl5_SwitchController_Sw1_1[57];/* '<S3>/Sw1' */
extern real_T mdl5_Block7770_1[3];     /* '<Root>/Block7770' */
extern real_T mdl5_SubSystem2611_SubSystem2691_SubSystem2693_Block8254_1;/* '<S94>/Block8254' */
extern real_T mdl5_SubSystem2611_SubSystem2691_SubSystem2693_Block8235_1;/* '<S94>/Block8235' */
extern real_T mdl5_SubSystem2611_SubSystem2691_SubSystem2693_Block8236_1;/* '<S94>/Block8236' */
extern real_T mdl5_SubSystem2611_SubSystem2691_SubSystem2693_Block8237_1;/* '<S94>/Block8237' */
extern real_T mdl5_SubSystem2611_SubSystem2691_SubSystem2693_Block8238_1;/* '<S94>/Block8238' */
extern real_T mdl5_SubSystem2611_SubSystem2691_SubSystem2693_Block8239_1;/* '<S94>/Block8239' */
extern real_T mdl5_SubSystem2611_SubSystem2691_SubSystem2693_Block8240_1;/* '<S94>/Block8240' */
extern real_T mdl5_SubSystem2611_SubSystem2691_SubSystem2693_Block8243_1;/* '<S94>/Block8243' */
extern real_T mdl5_SubSystem2611_SubSystem2691_SubSystem2693_Block8245_1;/* '<S94>/Block8245' */
extern real_T mdl5_SubSystem2611_SubSystem2691_SubSystem2693_Block8246_1;/* '<S94>/Block8246' */
extern real_T mdl5_SubSystem2611_SubSystem2691_SubSystem2693_Block8247_1;/* '<S94>/Block8247' */
extern real_T mdl5_SubSystem2611_SubSystem2691_SubSystem2693_Block8241_1;/* '<S94>/Block8241' */
extern real_T mdl5_SubSystem2611_SubSystem2691_SubSystem2693_Block8242_1;/* '<S94>/Block8242' */
extern real_T mdl5_SubSystem2611_SubSystem2691_SubSystem2693_Block8244_1;/* '<S94>/Block8244' */
extern real_T mdl5_SubSystem2611_SubSystem2691_SubSystem2693_Block8248_1;/* '<S94>/Block8248' */
extern real_T mdl5_SubSystem2611_SubSystem2691_SubSystem2693_Block8249_1;/* '<S94>/Block8249' */
extern real_T mdl5_SubSystem2611_SubSystem2691_SubSystem2693_Block8251_1;/* '<S94>/Block8251' */
extern real_T mdl5_SubSystem2611_SubSystem2691_SubSystem2693_Block8252_1;/* '<S94>/Block8252' */
extern real_T mdl5_SubSystem2611_SubSystem2691_SubSystem2693_Block8253_1;/* '<S94>/Block8253' */
extern real_T mdl5_SubSystem2611_SubSystem2691_SubSystem2693_Block8250_1;/* '<S94>/Block8250' */
extern real_T mdl5_SubSystem2611_SubSystem2691_SubSystem2693_Block8255_1;/* '<S94>/Block8255' */
extern real_T mdl5_SubSystem2611_SubSystem2691_SubSystem2693_Block8256_1;/* '<S94>/Block8256' */
extern real_T mdl5_SubSystem2611_SubSystem2691_SubSystem2693_Block8257_1;/* '<S94>/Block8257' */
extern real_T mdl5_SubSystem2611_SubSystem2691_SubSystem2693_Block8258_1;/* '<S94>/Block8258' */
extern real_T mdl5_SubSystem2611_SubSystem2691_SubSystem2693_Block8259_1;/* '<S94>/Block8259' */
extern real_T mdl5_SubSystem2611_SubSystem2691_SubSystem2693_Block8260_1;/* '<S94>/Block8260' */
extern real_T mdl5_SubSystem2611_SubSystem2691_SubSystem2693_Block8261_1;/* '<S94>/Block8261' */
extern real_T mdl5_SubSystem2611_SubSystem2691_SubSystem2693_Block8262_1;/* '<S94>/Block8262' */
extern real_T mdl5_SubSystem2611_SubSystem2691_SubSystem2693_Block8263_1;/* '<S94>/Block8263' */
extern real_T mdl5_SubSystem2611_SubSystem2691_SubSystem2693_Block8264_1;/* '<S94>/Block8264' */
extern real_T mdl5_SubSystem2611_SubSystem2691_SubSystem2693_Block8265_1;/* '<S94>/Block8265' */
extern real_T mdl5_SubSystem2611_SubSystem2691_SubSystem2693_Block8266_1;/* '<S94>/Block8266' */
extern real_T mdl5_SubSystem2611_SubSystem2691_SubSystem2693_Block8267_1;/* '<S94>/Block8267' */
extern real_T mdl5_SubSystem2611_SubSystem2691_SubSystem2693_Block8234_1;/* '<S94>/Block8234' */
extern real_T
  mdl5_SubSystem2611_SubSystem2691_SubSystem2693_SubSystem2694_For_loop_SFunction_idx;/* '<S95>/For_loop' */
extern real_T
  mdl5_SubSystem2611_SubSystem2691_SubSystem2693_SubSystem2695_Block8302_1;/* '<S96>/Block8302' */
extern real_T
  mdl5_SubSystem2611_SubSystem2691_SubSystem2693_SubSystem2695_Block8301_1;/* '<S96>/Block8301' */
extern real_T
  mdl5_SubSystem2611_SubSystem2691_SubSystem2693_SubSystem2695_Block8300_1;/* '<S96>/Block8300' */
extern real_T
  mdl5_SubSystem2611_SubSystem2691_SubSystem2693_SubSystem2695_Block8303_1;/* '<S96>/Block8303' */
extern real_T
  mdl5_SubSystem2611_SubSystem2691_SubSystem2693_SubSystem2695_Block8304_1;/* '<S96>/Block8304' */
extern real_T
  mdl5_SubSystem2611_SubSystem2691_SubSystem2693_SubSystem2695_Block8305_1;/* '<S96>/Block8305' */
extern real_T
  mdl5_SubSystem2611_SubSystem2691_SubSystem2693_SubSystem2695_Block8306_1;/* '<S96>/Block8306' */
extern real_T
  mdl5_SubSystem2611_SubSystem2691_SubSystem2693_SubSystem2695_Block8307_1;/* '<S96>/Block8307' */
extern real_T
  mdl5_SubSystem2611_SubSystem2691_SubSystem2693_SubSystem2695_Block8308_1;/* '<S96>/Block8308' */
extern real_T
  mdl5_SubSystem2611_SubSystem2691_SubSystem2693_SubSystem2695_Block8309_1;/* '<S96>/Block8309' */
extern real_T
  mdl5_SubSystem2611_SubSystem2691_SubSystem2693_SubSystem2695_SubSystem2706_Inside_DSR_1
  [3];                                 /* '<S108>/Inside_DSR' */
extern real_T
  mdl5_SubSystem2611_SubSystem2691_SubSystem2693_SubSystem2695_SubSystem2706_Assignment_1
  [3];                                 /* '<S108>/Assignment' */
extern real_T
  mdl5_SubSystem2611_SubSystem2691_SubSystem2693_SubSystem2695_SubSystem2705_Inside_DSR_1
  [3];                                 /* '<S107>/Inside_DSR' */
extern real_T
  mdl5_SubSystem2611_SubSystem2691_SubSystem2693_SubSystem2695_SubSystem2705_Assignment_1
  [3];                                 /* '<S107>/Assignment' */
extern real_T
  mdl5_SubSystem2611_SubSystem2691_SubSystem2693_SubSystem2695_SubSystem2704_Inside_DSR_1
  [3];                                 /* '<S106>/Inside_DSR' */
extern real_T
  mdl5_SubSystem2611_SubSystem2691_SubSystem2693_SubSystem2695_SubSystem2704_Assignment_1
  [3];                                 /* '<S106>/Assignment' */
extern real_T
  mdl5_SubSystem2611_SubSystem2691_SubSystem2693_SubSystem2695_SubSystem2703_Inside_DSR_1
  [3];                                 /* '<S105>/Inside_DSR' */
extern real_T
  mdl5_SubSystem2611_SubSystem2691_SubSystem2693_SubSystem2695_SubSystem2703_Assignment_1
  [3];                                 /* '<S105>/Assignment' */
extern real_T
  mdl5_SubSystem2611_SubSystem2691_SubSystem2693_SubSystem2695_SubSystem2702_Inside_DSR_1
  [3];                                 /* '<S104>/Inside_DSR' */
extern real_T
  mdl5_SubSystem2611_SubSystem2691_SubSystem2693_SubSystem2695_SubSystem2702_Assignment_1
  [3];                                 /* '<S104>/Assignment' */
extern real_T
  mdl5_SubSystem2611_SubSystem2691_SubSystem2693_SubSystem2695_SubSystem2701_Inside_DSR_1
  [3];                                 /* '<S103>/Inside_DSR' */
extern real_T
  mdl5_SubSystem2611_SubSystem2691_SubSystem2693_SubSystem2695_SubSystem2701_Assignment_1
  [3];                                 /* '<S103>/Assignment' */
extern real_T
  mdl5_SubSystem2611_SubSystem2691_SubSystem2693_SubSystem2695_SubSystem2700_Inside_DSR_1
  [3];                                 /* '<S102>/Inside_DSR' */
extern real_T
  mdl5_SubSystem2611_SubSystem2691_SubSystem2693_SubSystem2695_SubSystem2700_Assignment_1
  [3];                                 /* '<S102>/Assignment' */
extern real_T
  mdl5_SubSystem2611_SubSystem2691_SubSystem2693_SubSystem2695_SubSystem2699_Inside_DSR_1
  [3];                                 /* '<S101>/Inside_DSR' */
extern real_T
  mdl5_SubSystem2611_SubSystem2691_SubSystem2693_SubSystem2695_SubSystem2699_Assignment_1
  [3];                                 /* '<S101>/Assignment' */
extern real_T
  mdl5_SubSystem2611_SubSystem2691_SubSystem2693_SubSystem2695_SubSystem2698_Inside_DSR_1
  [3];                                 /* '<S100>/Inside_DSR' */
extern real_T
  mdl5_SubSystem2611_SubSystem2691_SubSystem2693_SubSystem2695_SubSystem2698_Assignment_1
  [3];                                 /* '<S100>/Assignment' */
extern real_T
  mdl5_SubSystem2611_SubSystem2691_SubSystem2693_SubSystem2695_SubSystem2697_Inside_DSR_1
  [3];                                 /* '<S99>/Inside_DSR' */
extern real_T
  mdl5_SubSystem2611_SubSystem2691_SubSystem2693_SubSystem2695_SubSystem2697_Assignment_1
  [3];                                 /* '<S99>/Assignment' */
extern real_T
  mdl5_SubSystem2611_SubSystem2691_SubSystem2693_SubSystem2695_SubSystem2696_Inside_DSR_1
  [3];                                 /* '<S98>/Inside_DSR' */
extern real_T
  mdl5_SubSystem2611_SubSystem2691_SubSystem2693_SubSystem2695_SubSystem2696_Assignment_1
  [3];                                 /* '<S98>/Assignment' */
extern real_T mdl5_SubSystem2611_SubSystem2612_Block7975_1;/* '<S15>/Block7975' */
extern real_T mdl5_SubSystem2611_SubSystem2612_Block7962_1;/* '<S15>/Block7962' */
extern real_T mdl5_SubSystem2611_SubSystem2612_Block7964_1;/* '<S15>/Block7964' */
extern real_T mdl5_SubSystem2611_SubSystem2612_Block7988_1;/* '<S15>/Block7988' */
extern real_T mdl5_SubSystem2611_SubSystem2612_SubSystem2613_RO1_1;/* '<S17>/RO1' */
extern real_T mdl5_SubSystem2611_SubSystem2612_Block7973_1;/* '<S15>/Block7973' */
extern real_T mdl5_SubSystem2611_SubSystem2612_Block7965_1;/* '<S15>/Block7965' */
extern real_T mdl5_SubSystem2611_SubSystem2612_Block7989_1;/* '<S15>/Block7989' */
extern real_T mdl5_SubSystem2611_SubSystem2612_SubSystem2614_RO1_1;/* '<S18>/RO1' */
extern real_T mdl5_SubSystem2611_SubSystem2612_Block7974_1;/* '<S15>/Block7974' */
extern real_T mdl5_SubSystem2611_SubSystem2612_Block7966_1;/* '<S15>/Block7966' */
extern real_T mdl5_SubSystem2611_SubSystem2612_Block7986_1;/* '<S15>/Block7986' */
extern real_T mdl5_SubSystem2611_SubSystem2612_SubSystem2615_RO1_1;/* '<S19>/RO1' */
extern real_T mdl5_SubSystem2611_SubSystem2612_Block7963_1;/* '<S15>/Block7963' */
extern real_T mdl5_SubSystem2611_SubSystem2612_Block7996_1[2];/* '<S15>/Block7996' */
extern real_T mdl5_SubSystem2611_SubSystem2612_Block7997_1[2];/* '<S15>/Block7997' */
extern real_T mdl5_SubSystem2611_SubSystem2612_Block7995_1[2];/* '<S15>/Block7995' */
extern real_T mdl5_SubSystem2611_SubSystem2612_Block7967_1;/* '<S15>/Block7967' */
extern real_T mdl5_SubSystem2611_SubSystem2612_Block7990_1;/* '<S15>/Block7990' */
extern real_T mdl5_SubSystem2611_SubSystem2612_SubSystem2616_RO1_1;/* '<S20>/RO1' */
extern real_T mdl5_SubSystem2611_SubSystem2612_Block7970_1;/* '<S15>/Block7970' */
extern real_T mdl5_SubSystem2611_SubSystem2612_Block7968_1;/* '<S15>/Block7968' */
extern real_T mdl5_SubSystem2611_SubSystem2612_Block7991_1;/* '<S15>/Block7991' */
extern real_T mdl5_SubSystem2611_SubSystem2612_SubSystem2617_RO1_1;/* '<S21>/RO1' */
extern real_T mdl5_SubSystem2611_SubSystem2612_Block7971_1;/* '<S15>/Block7971' */
extern real_T mdl5_SubSystem2611_SubSystem2612_Block7969_1;/* '<S15>/Block7969' */
extern real_T mdl5_SubSystem2611_SubSystem2612_Block7987_1;/* '<S15>/Block7987' */
extern real_T mdl5_SubSystem2611_SubSystem2612_SubSystem2618_RO1_1;/* '<S22>/RO1' */
extern real_T mdl5_SubSystem2611_SubSystem2612_Block7972_1;/* '<S15>/Block7972' */
extern real_T mdl5_SubSystem2611_SubSystem2612_Block7993_1[2];/* '<S15>/Block7993' */
extern real_T mdl5_SubSystem2611_SubSystem2612_Block7994_1[2];/* '<S15>/Block7994' */
extern real_T mdl5_SubSystem2611_SubSystem2612_Block7992_1[2];/* '<S15>/Block7992' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_Block8102_1;/* '<S69>/Block8102' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_Block8109_1;/* '<S69>/Block8109' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_Block8103_1;/* '<S69>/Block8103' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_Block8099_1;/* '<S69>/Block8099' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2669_RO1_1;/* '<S72>/RO1' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_Block8108_1;/* '<S69>/Block8108' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_Block8100_1;/* '<S69>/Block8100' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2668_RO1_1;/* '<S71>/RO1' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_Block8101_1;/* '<S69>/Block8101' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_Block8111_1;/* '<S69>/Block8111' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_Block8110_1;/* '<S69>/Block8110' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_Block8141_1;/* '<S74>/Block8141' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_Block8143_1;/* '<S74>/Block8143' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_Block8135_1;/* '<S74>/Block8135' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2685_RO1_1;/* '<S88>/RO1' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_Block8142_1;/* '<S74>/Block8142' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_Block8140_1;/* '<S74>/Block8140' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2686_RO1_1;/* '<S89>/RO1' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_Block8139_1;/* '<S74>/Block8139' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_Block8134_1;/* '<S74>/Block8134' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_Block8136_1;/* '<S74>/Block8136' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_Block8137_1;/* '<S74>/Block8137' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_Block8138_1;/* '<S74>/Block8138' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_Block8167_1
  [6];                                 /* '<S74>/Block8167' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_Block8166_1
  [6];                                 /* '<S74>/Block8166' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2687_Block8176_1;/* '<S90>/Block8176' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2687_Block8174_1;/* '<S90>/Block8174' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2687_Block8223_1;/* '<S90>/Block8223' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2687_Block8179_1;/* '<S90>/Block8179' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2687_SubSystem2688_RO1_1;/* '<S91>/RO1' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2687_Block8180_1;/* '<S90>/Block8180' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2687_SubSystem2689_RO1_1;/* '<S92>/RO1' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2687_Block8181_1;/* '<S90>/Block8181' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2687_SubSystem2690_RO1_1;/* '<S93>/RO1' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2687_Block8217_1;/* '<S90>/Block8217' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2687_Block8216_1;/* '<S90>/Block8216' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2687_Block8177_1;/* '<S90>/Block8177' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2687_Block8172_1;/* '<S90>/Block8172' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2687_Block8225_1;/* '<S90>/Block8225' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2687_Block8214_1;/* '<S90>/Block8214' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2687_Block8213_1;/* '<S90>/Block8213' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2687_Block8178_1;/* '<S90>/Block8178' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2687_Block8175_1;/* '<S90>/Block8175' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2687_Block8226_1;/* '<S90>/Block8226' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2687_Block8215_1;/* '<S90>/Block8215' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2687_Block8229_1
  [6];                                 /* '<S90>/Block8229' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2687_Block8228_1
  [6];                                 /* '<S90>/Block8228' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2687_Block8230_1
  [6];                                 /* '<S90>/Block8230' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2687_Block8170_1;/* '<S90>/Block8170' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2687_Block8222_1;/* '<S90>/Block8222' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2687_Block8171_1;/* '<S90>/Block8171' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2687_Block8224_1;/* '<S90>/Block8224' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2687_Block8169_1
  [6];                                 /* '<S90>/Block8169' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2687_Block8173_1;/* '<S90>/Block8173' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2687_Block8212_1;/* '<S90>/Block8212' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2687_Block8227_1
  [6];                                 /* '<S90>/Block8227' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2684_Inside_DSR_1
  [3];                                 /* '<S87>/Inside_DSR' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2684_Assignment_1
  [3];                                 /* '<S87>/Assignment' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2683_Inside_DSR_1
  [3];                                 /* '<S86>/Inside_DSR' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2683_Assignment_1
  [3];                                 /* '<S86>/Assignment' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2682_Inside_DSR_1
  [3];                                 /* '<S85>/Inside_DSR' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2682_Assignment_1
  [3];                                 /* '<S85>/Assignment' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2681_Inside_DSR_1
  [3];                                 /* '<S84>/Inside_DSR' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2681_Assignment_1
  [3];                                 /* '<S84>/Assignment' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2680_Inside_DSR_1
  [3];                                 /* '<S83>/Inside_DSR' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2680_Selector_1;/* '<S83>/Selector' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2679_Inside_DSR_1
  [3];                                 /* '<S82>/Inside_DSR' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2679_Selector_1;/* '<S82>/Selector' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2678_Inside_DSR_1
  [3];                                 /* '<S81>/Inside_DSR' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2678_Selector_1;/* '<S81>/Selector' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2677_Inside_DSR_1
  [3];                                 /* '<S80>/Inside_DSR' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2677_Selector_1;/* '<S80>/Selector' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2670_Block8114_1;/* '<S73>/Block8114' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2670_Block8122_1;/* '<S73>/Block8122' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2670_Block8123_1;/* '<S73>/Block8123' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2670_Block8124_1;/* '<S73>/Block8124' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2670_Block8125_1;/* '<S73>/Block8125' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2670_Block8115_1
  [5];                                 /* '<S73>/Block8115' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2670_Block8128_1
  [5];                                 /* '<S73>/Block8128' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2670_Block8129_1;/* '<S73>/Block8129' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2670_Block8117_1;/* '<S73>/Block8117' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2670_Block8113_1;/* '<S73>/Block8113' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2670_SubSystem2675_RO1_1;/* '<S79>/RO1' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2670_Block8116_1
  [5];                                 /* '<S73>/Block8116' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2670_Block8127_1
  [5];                                 /* '<S73>/Block8127' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2670_Block8130_1;/* '<S73>/Block8130' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2670_Block8131_1;/* '<S73>/Block8131' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2670_SubSystem2674_Inside_DSR_1
  [3];                                 /* '<S78>/Inside_DSR' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2670_SubSystem2674_Assignment_1
  [3];                                 /* '<S78>/Assignment' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2670_SubSystem2673_Inside_DSR_1
  [3];                                 /* '<S77>/Inside_DSR' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2670_SubSystem2673_Selector_1;/* '<S77>/Selector' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2670_SubSystem2672_Inside_DSR_1
  [3];                                 /* '<S76>/Inside_DSR' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2670_SubSystem2672_Selector_1;/* '<S76>/Selector' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2670_SubSystem2671_Inside_DSR_1
  [3];                                 /* '<S75>/Inside_DSR' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2670_SubSystem2671_Selector_1;/* '<S75>/Selector' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2667_Inside_DSR_1
  [3];                                 /* '<S70>/Inside_DSR' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2667_Assignment_1
  [3];                                 /* '<S70>/Assignment' */
extern real_T mdl5_SubSystem2611_SubSystem2612_SubSystem2620_Block8000_1;/* '<S23>/Block8000' */
extern real_T mdl5_SubSystem2611_SubSystem2612_SubSystem2620_Block8002_1;/* '<S23>/Block8002' */
extern real_T mdl5_SubSystem2611_SubSystem2612_SubSystem2620_Block8001_1;/* '<S23>/Block8001' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_Block8005_1;/* '<S28>/Block8005' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_Block8044_1;/* '<S28>/Block8044' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_Block8007_1;/* '<S28>/Block8007' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_Block8006_1;/* '<S28>/Block8006' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_Block8004_1;/* '<S28>/Block8004' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2636_RO1_1;/* '<S32>/RO1' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_Block8045_1;/* '<S28>/Block8045' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_Block8008_1;/* '<S28>/Block8008' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_Block8065_1;/* '<S35>/Block8065' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_Block8066_1;/* '<S35>/Block8066' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_Block8067_1;/* '<S35>/Block8067' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_Block8068_1;/* '<S35>/Block8068' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_Block8069_1;/* '<S35>/Block8069' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_Block8070_1;/* '<S35>/Block8070' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_Block8071_1;/* '<S35>/Block8071' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_SubSystem2664_RO1_1;/* '<S68>/RO1' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_SubSystem2659_RO1_1;/* '<S63>/RO1' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_SubSystem2661_RO1_1;/* '<S65>/RO1' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_SubSystem2660_RO1_1;/* '<S64>/RO1' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_SubSystem2662_RO1_1;/* '<S66>/RO1' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_SubSystem2663_RO1_1;/* '<S67>/RO1' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_Block8093_1
  [2];                                 /* '<S35>/Block8093' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_Block8092_1
  [2];                                 /* '<S35>/Block8092' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_Block8091_1
  [2];                                 /* '<S35>/Block8091' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_Block8090_1
  [2];                                 /* '<S35>/Block8090' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_Block8089_1
  [2];                                 /* '<S35>/Block8089' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_Block8088_1
  [2];                                 /* '<S35>/Block8088' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_SubSystem2658_Inside_DSR_1
  [3];                                 /* '<S62>/Inside_DSR' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_SubSystem2658_Selector_1;/* '<S62>/Selector' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_SubSystem2657_Inside_DSR_1
  [3];                                 /* '<S61>/Inside_DSR' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_SubSystem2657_Selector_1;/* '<S61>/Selector' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_SubSystem2656_Inside_DSR_1
  [3];                                 /* '<S60>/Inside_DSR' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_SubSystem2656_Selector_1;/* '<S60>/Selector' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_SubSystem2655_Inside_DSR_1
  [3];                                 /* '<S59>/Inside_DSR' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_SubSystem2655_Selector_1;/* '<S59>/Selector' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_SubSystem2654_Inside_DSR_1
  [3];                                 /* '<S58>/Inside_DSR' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_SubSystem2654_Selector_1;/* '<S58>/Selector' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_SubSystem2653_Inside_DSR_1
  [3];                                 /* '<S57>/Inside_DSR' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_SubSystem2653_Selector_1;/* '<S57>/Selector' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_SubSystem2652_Inside_DSR_1
  [3];                                 /* '<S56>/Inside_DSR' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_SubSystem2652_Selector_1;/* '<S56>/Selector' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_SubSystem2651_Inside_DSR_1
  [3];                                 /* '<S55>/Inside_DSR' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_SubSystem2651_Selector_1;/* '<S55>/Selector' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_SubSystem2650_Inside_DSR_1
  [3];                                 /* '<S54>/Inside_DSR' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_SubSystem2650_Selector_1;/* '<S54>/Selector' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_SubSystem2649_Inside_DSR_1
  [3];                                 /* '<S53>/Inside_DSR' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_SubSystem2649_Selector_1;/* '<S53>/Selector' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_SubSystem2648_Inside_DSR_1
  [3];                                 /* '<S52>/Inside_DSR' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_SubSystem2648_Selector_1;/* '<S52>/Selector' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_SubSystem2647_Inside_DSR_1
  [3];                                 /* '<S51>/Inside_DSR' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_SubSystem2647_Selector_1;/* '<S51>/Selector' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_SubSystem2646_Inside_DSR_1
  [3];                                 /* '<S50>/Inside_DSR' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_SubSystem2646_Selector_1;/* '<S50>/Selector' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_SubSystem2645_Inside_DSR_1
  [3];                                 /* '<S49>/Inside_DSR' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_SubSystem2645_Selector_1;/* '<S49>/Selector' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2638_Block8049_1;/* '<S34>/Block8049' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2638_Block8052_1;/* '<S34>/Block8052' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2638_Block8061_SigLabel310;/* '<S34>/Block8061' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2638_Block8048_1;/* '<S34>/Block8048' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2638_Block8059_1;/* '<S34>/Block8059' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2638_Block8053_1;/* '<S34>/Block8053' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2638_Block8060_1;/* '<S34>/Block8060' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2638_Block8050_1;/* '<S34>/Block8050' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2638_Block8054_1;/* '<S34>/Block8054' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2638_Block8062_1;/* '<S34>/Block8062' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2638_Block8051_1;/* '<S34>/Block8051' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2638_SubSystem2643_Min1_1;/* '<S48>/Min1' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2638_SubSystem2642_Product_1;/* '<S47>/Product' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2638_SubSystem2641_SigLabel309;/* '<S46>/Product' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2638_SubSystem2640_Inside_DSR_1
  [3];                                 /* '<S45>/Inside_DSR' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2638_SubSystem2640_Selector_1;/* '<S45>/Selector' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2638_SubSystem2639_Inside_DSR_1
  [3];                                 /* '<S44>/Inside_DSR' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2638_SubSystem2639_Selector_1;/* '<S44>/Selector' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2637_Max1_1;/* '<S33>/Max1' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2637_Min1_1;/* '<S33>/Min1' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2627_Block8038_1;/* '<S31>/Block8038' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2627_Block8025_1;/* '<S31>/Block8025' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2627_Block8035_1;/* '<S31>/Block8035' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2627_Block8039_1;/* '<S31>/Block8039' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2627_Block8026_1;/* '<S31>/Block8026' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2627_Block8036_1;/* '<S31>/Block8036' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2627_Block8040_1;/* '<S31>/Block8040' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2627_Block8037_1;/* '<S31>/Block8037' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2627_Block8023_1;/* '<S31>/Block8023' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2627_Block8022_1;/* '<S31>/Block8022' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2627_SubSystem2635_RO1_1;/* '<S43>/RO1' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2627_Block8042_1;/* '<S31>/Block8042' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2627_Block8024_1;/* '<S31>/Block8024' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2627_Block8034_1;/* '<S31>/Block8034' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2627_Block8041_1;/* '<S31>/Block8041' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2627_SubSystem2634_Inside_DSR_1
  [3];                                 /* '<S42>/Inside_DSR' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2627_SubSystem2634_Assignment_1
  [3];                                 /* '<S42>/Assignment' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2627_SubSystem2633_Inside_DSR_1
  [3];                                 /* '<S41>/Inside_DSR' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2627_SubSystem2633_Assignment_1
  [3];                                 /* '<S41>/Assignment' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2627_SubSystem2632_Inside_DSR_1
  [3];                                 /* '<S40>/Inside_DSR' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2627_SubSystem2632_Assignment_1
  [3];                                 /* '<S40>/Assignment' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2627_SubSystem2631_Inside_DSR_1
  [3];                                 /* '<S39>/Inside_DSR' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2627_SubSystem2631_Assignment_1
  [3];                                 /* '<S39>/Assignment' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2627_SubSystem2630_Inside_DSR_1
  [3];                                 /* '<S38>/Inside_DSR' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2627_SubSystem2630_Selector_1;/* '<S38>/Selector' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2627_SubSystem2629_Inside_DSR_1
  [3];                                 /* '<S37>/Inside_DSR' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2627_SubSystem2629_Selector_1;/* '<S37>/Selector' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2627_SubSystem2628_Inside_DSR_1
  [3];                                 /* '<S36>/Inside_DSR' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2627_SubSystem2628_Selector_1;/* '<S36>/Selector' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2626_Inside_DSR_1
  [3];                                 /* '<S30>/Inside_DSR' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2626_Assignment_1
  [3];                                 /* '<S30>/Assignment' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2625_Inside_DSR_1
  [3];                                 /* '<S29>/Inside_DSR' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2625_Assignment_1
  [3];                                 /* '<S29>/Assignment' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2623_Inside_DSR_1[3];/* '<S27>/Inside_DSR' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2623_Assignment_1[3];/* '<S27>/Assignment' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2622_Inside_DSR_1[3];/* '<S26>/Inside_DSR' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2622_Selector_1;/* '<S26>/Selector' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2621_Inside_DSR_1[3];/* '<S25>/Inside_DSR' */
extern real_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2621_Selector_1;/* '<S25>/Selector' */
extern real_T mdl5_SubSystem2601_SubSystem2603_SubSystem2607_Product_1;/* '<S9>/Product' */
extern real_T mdl5_SubSystem2601_SubSystem2603_SubSystem2606_Product_Constant1_1;/* '<S13>/Constant1' */
extern real_T mdl5_SubSystem2601_SubSystem2603_SubSystem2606_Product_Constant2_1;/* '<S13>/Constant2' */
extern real_T
  mdl5_SubSystem2601_SubSystem2603_SubSystem2606_Product_RelationalOperator_1;/* '<S13>/RelationalOperator' */
extern real_T mdl5_SubSystem2601_SubSystem2603_SubSystem2606_Product_Switch1_1;/* '<S13>/Switch1' */
extern real_T mdl5_SubSystem2601_SubSystem2603_SubSystem2606_Product_Product_1;/* '<S13>/Product' */
extern real_T mdl5_SubSystem2601_SubSystem2603_SubSystem2606_Product_Switch_1;/* '<S13>/Switch' */
extern real_T mdl5_SubSystem2601_SubSystem2603_SubSystem2605_Product_1;/* '<S7>/Product' */
extern real_T mdl5_SubSystem2601_SubSystem2603_SubSystem2604_Product_Constant1_1;/* '<S12>/Constant1' */
extern real_T mdl5_SubSystem2601_SubSystem2603_SubSystem2604_Product_Constant2_1;/* '<S12>/Constant2' */
extern real_T
  mdl5_SubSystem2601_SubSystem2603_SubSystem2604_Product_RelationalOperator_1;/* '<S12>/RelationalOperator' */
extern real_T mdl5_SubSystem2601_SubSystem2603_SubSystem2604_Product_Switch1_1;/* '<S12>/Switch1' */
extern real_T mdl5_SubSystem2601_SubSystem2603_SubSystem2604_Product_Product_1;/* '<S12>/Product' */
extern real_T mdl5_SubSystem2601_SubSystem2603_SubSystem2604_Product_Switch_1;/* '<S12>/Switch' */
extern real32_T mdl5_SubSystem2601_SubSystem2602_single1_1;/* '<S4>/single1' */
extern real32_T mdl5_SubSystem2601_SubSystem2603_SubSystem2608_single1_1;/* '<S10>/single1' */
extern real32_T mdl5_SubSystem2601_SubSystem2603_SubSystem2608_single2_1;/* '<S10>/single2' */
extern real32_T
  mdl5_SubSystem2601_SubSystem2603_SubSystem2609_SubSystem2610_single1_1;/* '<S14>/single1' */
extern real32_T
  mdl5_SubSystem2601_SubSystem2603_SubSystem2609_SubSystem2610_single2_1;/* '<S14>/single2' */
extern real32_T mdl5_SubSystem2601_SubSystem2602_single2_1;/* '<S4>/single2' */
extern real32_T mdl5_SubSystem2611_SubSystem2612_SubSystem2613_single1_1;/* '<S17>/single1' */
extern real32_T mdl5_SubSystem2611_SubSystem2612_SubSystem2613_single2_1;/* '<S17>/single2' */
extern real32_T mdl5_SubSystem2611_SubSystem2612_SubSystem2614_single1_1;/* '<S18>/single1' */
extern real32_T mdl5_SubSystem2611_SubSystem2612_SubSystem2614_single2_1;/* '<S18>/single2' */
extern real32_T mdl5_SubSystem2611_SubSystem2612_SubSystem2615_single1_1;/* '<S19>/single1' */
extern real32_T mdl5_SubSystem2611_SubSystem2612_SubSystem2615_single2_1;/* '<S19>/single2' */
extern real32_T mdl5_SubSystem2611_SubSystem2612_SubSystem2616_single1_1;/* '<S20>/single1' */
extern real32_T mdl5_SubSystem2611_SubSystem2612_SubSystem2616_single2_1;/* '<S20>/single2' */
extern real32_T mdl5_SubSystem2611_SubSystem2612_SubSystem2617_single1_1;/* '<S21>/single1' */
extern real32_T mdl5_SubSystem2611_SubSystem2612_SubSystem2617_single2_1;/* '<S21>/single2' */
extern real32_T mdl5_SubSystem2611_SubSystem2612_SubSystem2618_single1_1;/* '<S22>/single1' */
extern real32_T mdl5_SubSystem2611_SubSystem2612_SubSystem2618_single2_1;/* '<S22>/single2' */
extern real32_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2669_single1_1;/* '<S72>/single1' */
extern real32_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2669_single2_1;/* '<S72>/single2' */
extern real32_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2668_single1_1;/* '<S71>/single1' */
extern real32_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2668_single2_1;/* '<S71>/single2' */
extern real32_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2685_single1_1;/* '<S88>/single1' */
extern real32_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2685_single2_1;/* '<S88>/single2' */
extern real32_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2686_single1_1;/* '<S89>/single1' */
extern real32_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2686_single2_1;/* '<S89>/single2' */
extern real32_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2687_SubSystem2688_single1_1;/* '<S91>/single1' */
extern real32_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2687_SubSystem2688_single2_1;/* '<S91>/single2' */
extern real32_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2687_SubSystem2689_single1_1;/* '<S92>/single1' */
extern real32_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2687_SubSystem2689_single2_1;/* '<S92>/single2' */
extern real32_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2687_SubSystem2690_single1_1;/* '<S93>/single1' */
extern real32_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2676_SubSystem2687_SubSystem2690_single2_1;/* '<S93>/single2' */
extern real32_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2670_SubSystem2675_single1_1;/* '<S79>/single1' */
extern real32_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2665_SubSystem2666_SubSystem2670_SubSystem2675_single2_1;/* '<S79>/single2' */
extern real32_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2636_single1_1;/* '<S32>/single1' */
extern real32_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2636_single2_1;/* '<S32>/single2' */
extern real32_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_SubSystem2664_single1_1;/* '<S68>/single1' */
extern real32_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_SubSystem2664_single2_1;/* '<S68>/single2' */
extern real32_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_SubSystem2659_single1_1;/* '<S63>/single1' */
extern real32_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_SubSystem2659_single2_1;/* '<S63>/single2' */
extern real32_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_SubSystem2661_single1_1;/* '<S65>/single1' */
extern real32_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_SubSystem2661_single2_1;/* '<S65>/single2' */
extern real32_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_SubSystem2660_single1_1;/* '<S64>/single1' */
extern real32_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_SubSystem2660_single2_1;/* '<S64>/single2' */
extern real32_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_SubSystem2662_single1_1;/* '<S66>/single1' */
extern real32_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_SubSystem2662_single2_1;/* '<S66>/single2' */
extern real32_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_SubSystem2663_single1_1;/* '<S67>/single1' */
extern real32_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2644_SubSystem2663_single2_1;/* '<S67>/single2' */
extern real32_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2627_SubSystem2635_single1_1;/* '<S43>/single1' */
extern real32_T
  mdl5_SubSystem2611_SubSystem2612_SubSystem2620_SubSystem2624_SubSystem2627_SubSystem2635_single2_1;/* '<S43>/single2' */
extern boolean_T mdl5_SwitchController_SwitchControl_1;/* '<S3>/SwitchControl' */

/* Model entry point functions */
extern void mdl5_initialize(void);
extern void mdl5_step(void);
extern void mdl5_terminate(void);

/* Real-time Model object */
extern RT_MODEL_mdl5 *const mdl5_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'mdl5'
 * '<S1>'   : 'mdl5/SubSystem2601'
 * '<S2>'   : 'mdl5/SubSystem2611'
 * '<S3>'   : 'mdl5/SwitchController'
 * '<S4>'   : 'mdl5/SubSystem2601/SubSystem2602'
 * '<S5>'   : 'mdl5/SubSystem2601/SubSystem2603'
 * '<S6>'   : 'mdl5/SubSystem2601/SubSystem2603/SubSystem2604'
 * '<S7>'   : 'mdl5/SubSystem2601/SubSystem2603/SubSystem2605'
 * '<S8>'   : 'mdl5/SubSystem2601/SubSystem2603/SubSystem2606'
 * '<S9>'   : 'mdl5/SubSystem2601/SubSystem2603/SubSystem2607'
 * '<S10>'  : 'mdl5/SubSystem2601/SubSystem2603/SubSystem2608'
 * '<S11>'  : 'mdl5/SubSystem2601/SubSystem2603/SubSystem2609'
 * '<S12>'  : 'mdl5/SubSystem2601/SubSystem2603/SubSystem2604/Product'
 * '<S13>'  : 'mdl5/SubSystem2601/SubSystem2603/SubSystem2606/Product'
 * '<S14>'  : 'mdl5/SubSystem2601/SubSystem2603/SubSystem2609/SubSystem2610'
 * '<S15>'  : 'mdl5/SubSystem2611/SubSystem2612'
 * '<S16>'  : 'mdl5/SubSystem2611/SubSystem2691'
 * '<S17>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2613'
 * '<S18>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2614'
 * '<S19>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2615'
 * '<S20>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2616'
 * '<S21>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2617'
 * '<S22>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2618'
 * '<S23>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2620'
 * '<S24>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2665'
 * '<S25>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2620/SubSystem2621'
 * '<S26>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2620/SubSystem2622'
 * '<S27>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2620/SubSystem2623'
 * '<S28>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2620/SubSystem2624'
 * '<S29>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2620/SubSystem2624/SubSystem2625'
 * '<S30>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2620/SubSystem2624/SubSystem2626'
 * '<S31>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2620/SubSystem2624/SubSystem2627'
 * '<S32>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2620/SubSystem2624/SubSystem2636'
 * '<S33>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2620/SubSystem2624/SubSystem2637'
 * '<S34>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2620/SubSystem2624/SubSystem2638'
 * '<S35>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2620/SubSystem2624/SubSystem2644'
 * '<S36>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2620/SubSystem2624/SubSystem2627/SubSystem2628'
 * '<S37>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2620/SubSystem2624/SubSystem2627/SubSystem2629'
 * '<S38>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2620/SubSystem2624/SubSystem2627/SubSystem2630'
 * '<S39>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2620/SubSystem2624/SubSystem2627/SubSystem2631'
 * '<S40>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2620/SubSystem2624/SubSystem2627/SubSystem2632'
 * '<S41>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2620/SubSystem2624/SubSystem2627/SubSystem2633'
 * '<S42>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2620/SubSystem2624/SubSystem2627/SubSystem2634'
 * '<S43>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2620/SubSystem2624/SubSystem2627/SubSystem2635'
 * '<S44>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2620/SubSystem2624/SubSystem2638/SubSystem2639'
 * '<S45>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2620/SubSystem2624/SubSystem2638/SubSystem2640'
 * '<S46>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2620/SubSystem2624/SubSystem2638/SubSystem2641'
 * '<S47>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2620/SubSystem2624/SubSystem2638/SubSystem2642'
 * '<S48>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2620/SubSystem2624/SubSystem2638/SubSystem2643'
 * '<S49>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2620/SubSystem2624/SubSystem2644/SubSystem2645'
 * '<S50>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2620/SubSystem2624/SubSystem2644/SubSystem2646'
 * '<S51>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2620/SubSystem2624/SubSystem2644/SubSystem2647'
 * '<S52>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2620/SubSystem2624/SubSystem2644/SubSystem2648'
 * '<S53>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2620/SubSystem2624/SubSystem2644/SubSystem2649'
 * '<S54>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2620/SubSystem2624/SubSystem2644/SubSystem2650'
 * '<S55>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2620/SubSystem2624/SubSystem2644/SubSystem2651'
 * '<S56>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2620/SubSystem2624/SubSystem2644/SubSystem2652'
 * '<S57>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2620/SubSystem2624/SubSystem2644/SubSystem2653'
 * '<S58>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2620/SubSystem2624/SubSystem2644/SubSystem2654'
 * '<S59>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2620/SubSystem2624/SubSystem2644/SubSystem2655'
 * '<S60>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2620/SubSystem2624/SubSystem2644/SubSystem2656'
 * '<S61>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2620/SubSystem2624/SubSystem2644/SubSystem2657'
 * '<S62>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2620/SubSystem2624/SubSystem2644/SubSystem2658'
 * '<S63>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2620/SubSystem2624/SubSystem2644/SubSystem2659'
 * '<S64>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2620/SubSystem2624/SubSystem2644/SubSystem2660'
 * '<S65>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2620/SubSystem2624/SubSystem2644/SubSystem2661'
 * '<S66>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2620/SubSystem2624/SubSystem2644/SubSystem2662'
 * '<S67>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2620/SubSystem2624/SubSystem2644/SubSystem2663'
 * '<S68>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2620/SubSystem2624/SubSystem2644/SubSystem2664'
 * '<S69>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2665/SubSystem2666'
 * '<S70>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2665/SubSystem2666/SubSystem2667'
 * '<S71>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2665/SubSystem2666/SubSystem2668'
 * '<S72>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2665/SubSystem2666/SubSystem2669'
 * '<S73>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2665/SubSystem2666/SubSystem2670'
 * '<S74>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2665/SubSystem2666/SubSystem2676'
 * '<S75>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2665/SubSystem2666/SubSystem2670/SubSystem2671'
 * '<S76>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2665/SubSystem2666/SubSystem2670/SubSystem2672'
 * '<S77>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2665/SubSystem2666/SubSystem2670/SubSystem2673'
 * '<S78>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2665/SubSystem2666/SubSystem2670/SubSystem2674'
 * '<S79>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2665/SubSystem2666/SubSystem2670/SubSystem2675'
 * '<S80>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2665/SubSystem2666/SubSystem2676/SubSystem2677'
 * '<S81>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2665/SubSystem2666/SubSystem2676/SubSystem2678'
 * '<S82>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2665/SubSystem2666/SubSystem2676/SubSystem2679'
 * '<S83>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2665/SubSystem2666/SubSystem2676/SubSystem2680'
 * '<S84>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2665/SubSystem2666/SubSystem2676/SubSystem2681'
 * '<S85>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2665/SubSystem2666/SubSystem2676/SubSystem2682'
 * '<S86>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2665/SubSystem2666/SubSystem2676/SubSystem2683'
 * '<S87>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2665/SubSystem2666/SubSystem2676/SubSystem2684'
 * '<S88>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2665/SubSystem2666/SubSystem2676/SubSystem2685'
 * '<S89>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2665/SubSystem2666/SubSystem2676/SubSystem2686'
 * '<S90>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2665/SubSystem2666/SubSystem2676/SubSystem2687'
 * '<S91>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2665/SubSystem2666/SubSystem2676/SubSystem2687/SubSystem2688'
 * '<S92>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2665/SubSystem2666/SubSystem2676/SubSystem2687/SubSystem2689'
 * '<S93>'  : 'mdl5/SubSystem2611/SubSystem2612/SubSystem2665/SubSystem2666/SubSystem2676/SubSystem2687/SubSystem2690'
 * '<S94>'  : 'mdl5/SubSystem2611/SubSystem2691/SubSystem2693'
 * '<S95>'  : 'mdl5/SubSystem2611/SubSystem2691/SubSystem2693/SubSystem2694'
 * '<S96>'  : 'mdl5/SubSystem2611/SubSystem2691/SubSystem2693/SubSystem2695'
 * '<S97>'  : 'mdl5/SubSystem2611/SubSystem2691/SubSystem2693/SubSystem2694/For_loop'
 * '<S98>'  : 'mdl5/SubSystem2611/SubSystem2691/SubSystem2693/SubSystem2695/SubSystem2696'
 * '<S99>'  : 'mdl5/SubSystem2611/SubSystem2691/SubSystem2693/SubSystem2695/SubSystem2697'
 * '<S100>' : 'mdl5/SubSystem2611/SubSystem2691/SubSystem2693/SubSystem2695/SubSystem2698'
 * '<S101>' : 'mdl5/SubSystem2611/SubSystem2691/SubSystem2693/SubSystem2695/SubSystem2699'
 * '<S102>' : 'mdl5/SubSystem2611/SubSystem2691/SubSystem2693/SubSystem2695/SubSystem2700'
 * '<S103>' : 'mdl5/SubSystem2611/SubSystem2691/SubSystem2693/SubSystem2695/SubSystem2701'
 * '<S104>' : 'mdl5/SubSystem2611/SubSystem2691/SubSystem2693/SubSystem2695/SubSystem2702'
 * '<S105>' : 'mdl5/SubSystem2611/SubSystem2691/SubSystem2693/SubSystem2695/SubSystem2703'
 * '<S106>' : 'mdl5/SubSystem2611/SubSystem2691/SubSystem2693/SubSystem2695/SubSystem2704'
 * '<S107>' : 'mdl5/SubSystem2611/SubSystem2691/SubSystem2693/SubSystem2695/SubSystem2705'
 * '<S108>' : 'mdl5/SubSystem2611/SubSystem2691/SubSystem2693/SubSystem2695/SubSystem2706'
 */
#endif                                 /* RTW_HEADER_mdl5_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
