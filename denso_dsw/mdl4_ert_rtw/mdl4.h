/*
 * File: mdl4.h
 *
 * Code generated for Simulink model 'mdl4'.
 *
 * Model version                  : 1.17
 * Simulink Coder version         : 8.6 (R2014a) 27-Dec-2013
 * C/C++ source code generated on : Wed Apr 13 01:16:19 2016
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Specified
 * Emulation hardware selection:
 *    Differs from embedded hardware (32-bit Generic)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_mdl4_h_
#define RTW_HEADER_mdl4_h_
#include <math.h>
#include <string.h>
#ifndef mdl4_COMMON_INCLUDES_
# define mdl4_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* mdl4_COMMON_INCLUDES_ */

#include "mdl4_types.h"
#include "rt_zcfcn.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block signals (auto storage) */
typedef struct {
  real_T mdl4_Block7360_1;             /* '<Root>/Block7360' */
  real_T mdl4_SubSystem2483_Block7367_1;/* '<S1>/Block7367' */
} BlockIO_mdl4;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T Block7383_DSTATE;             /* '<S4>/Block7383' */
  real_T Block7382_DSTATE;             /* '<S4>/Block7382' */
  real_T Block7368_DSTATE;             /* '<S1>/Block7368' */
  real_T DSM259[3];                    /* '<S2>/Block7409' */
  real_T DSM43;                        /* '<S2>/Block7410' */
  real_T DSM103[3];                    /* '<S2>/Block7411' */
  real_T DSM105[3];                    /* '<S2>/Block7412' */
  real_T DSM107[3];                    /* '<S2>/Block7413' */
  real_T DSM109[3];                    /* '<S2>/Block7414' */
  real_T DSM111[3];                    /* '<S2>/Block7415' */
  real_T DSM113[3];                    /* '<S2>/Block7416' */
  real_T DSM114[3];                    /* '<S2>/Block7417' */
  real_T DSM117[3];                    /* '<S2>/Block7418' */
  real_T DSM118[3];                    /* '<S2>/Block7419' */
  real_T DSM121[3];                    /* '<S2>/Block7420' */
  real_T DSM124[3];                    /* '<S2>/Block7421' */
  real_T DSM127[3];                    /* '<S2>/Block7422' */
  real_T DSM273;                       /* '<S2>/Block7423' */
  real_T DSM274[3];                    /* '<S2>/Block7424' */
  real_T DSM275[3];                    /* '<S2>/Block7425' */
  real_T DSM276;                       /* '<S2>/Block7426' */
  real_T DSM277;                       /* '<S2>/Block7427' */
  real_T DSM278;                       /* '<S2>/Block7428' */
  real_T DSM279[100];                  /* '<S2>/Block7429' */
  real_T DSM280[100];                  /* '<S2>/Block7430' */
  real_T DSM281[100];                  /* '<S2>/Block7431' */
  real_T DSM282[100];                  /* '<S2>/Block7432' */
  real_T DSM283;                       /* '<S2>/Block7433' */
  real_T DSM284;                       /* '<S2>/Block7434' */
  real_T DSM285;                       /* '<S2>/Block7435' */
  real_T DSM286;                       /* '<S2>/Block7436' */
  real_T DSM287;                       /* '<S2>/Block7437' */
  real_T DSM288;                       /* '<S2>/Block7438' */
  real_T DSM289[3];                    /* '<S2>/Block7439' */
  real_T DSM290[3];                    /* '<S2>/Block7440' */
  real_T DSM291[3];                    /* '<S2>/Block7441' */
  real_T DSM292[3];                    /* '<S2>/Block7442' */
  real_T DSM293[100];                  /* '<S2>/Block7443' */
  real_T DSM294;                       /* '<S2>/Block7444' */
  real_T DSM295[100];                  /* '<S2>/Block7445' */
  real_T DSM296;                       /* '<S2>/Block7446' */
  real_T DSM297;                       /* '<S2>/Block7447' */
  real_T DSM298;                       /* '<S2>/Block7448' */
  real_T DSM299;                       /* '<S2>/Block7449' */
  real_T DSM300[3];                    /* '<S2>/Block7450' */
  real_T DSM301[3];                    /* '<S2>/Block7451' */
  real_T DSM302[3];                    /* '<S2>/Block7452' */
  real_T DSM303[3];                    /* '<S2>/Block7453' */
  real_T DSM258[3];                    /* '<Root>/Block7327' */
  struct {
    void *TimePtr;
    void *DataPtr;
    void *RSimInfoPtr;
  } Block7331_PWORK;                   /* '<Root>/Block7331' */

  struct {
    void *TimePtr;
    void *DataPtr;
    void *RSimInfoPtr;
  } Block7330_PWORK;                   /* '<Root>/Block7330' */

  struct {
    int_T PrevIndex;
  } Block7331_IWORK;                   /* '<Root>/Block7331' */

  struct {
    int_T PrevIndex;
  } Block7330_IWORK;                   /* '<Root>/Block7330' */
} D_Work_mdl4;

/* Zero-crossing (trigger) state */
typedef struct {
  ZCSigState SubSystem2577_Trig_ZCE;   /* '<S2>/SubSystem2577' */
  ZCSigState SubSystem2494_Trig_ZCE;   /* '<S2>/SubSystem2494' */
} PrevZCSigStates_mdl4;

/* Real-time Model Data Structure */
struct tag_RTM_mdl4 {
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
extern BlockIO_mdl4 mdl4_B;

/* Block states (auto storage) */
extern D_Work_mdl4 mdl4_DWork;

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern real_T mdl4_Block7331_1;        /* '<Root>/Block7331' */
extern real_T mdl4_SubSystem2483_SubSystem2485_Block7383_1;/* '<S4>/Block7383' */
extern real_T mdl4_SubSystem2483_SubSystem2485_SubSystem2490_RO1_1;/* '<S9>/RO1' */
extern real_T mdl4_Block7326_1;        /* '<Root>/Block7326' */
extern real_T mdl4_SubSystem2483_SubSystem2485_Block7373_1;/* '<S4>/Block7373' */
extern real_T mdl4_SubSystem2483_SubSystem2485_Block7375_1;/* '<S4>/Block7375' */
extern real_T mdl4_Block7325_1;        /* '<Root>/Block7325' */
extern real_T mdl4_Block7330_1;        /* '<Root>/Block7330' */
extern real_T mdl4_SubSystem2483_SubSystem2485_Block7374_1;/* '<S4>/Block7374' */
extern real_T mdl4_SubSystem2483_SubSystem2485_Block7376_1;/* '<S4>/Block7376' */
extern real_T mdl4_SubSystem2483_SubSystem2485_Block7382_1;/* '<S4>/Block7382' */
extern real_T mdl4_SubSystem2483_SubSystem2485_Block7380_1;/* '<S4>/Block7380' */
extern real_T mdl4_SubSystem2483_SubSystem2485_Block7381_1;/* '<S4>/Block7381' */
extern real_T mdl4_SubSystem2483_SubSystem2485_Block7377_1;/* '<S4>/Block7377' */
extern real_T mdl4_SubSystem2483_SubSystem2485_Block7378_1;/* '<S4>/Block7378' */
extern real_T mdl4_SubSystem2483_SubSystem2485_SubSystem2491_Block7387_1;/* '<S10>/Block7387' */
extern real_T mdl4_SubSystem2483_SubSystem2485_SubSystem2491_Block7386_1;/* '<S10>/Block7386' */
extern real_T mdl4_SubSystem2483_SubSystem2485_SubSystem2491_SubSystem2492_RO1_1;/* '<S13>/RO1' */
extern real_T mdl4_SubSystem2483_SubSystem2485_SubSystem2491_SubSystem2492_RO2_1;/* '<S13>/RO2' */
extern real_T mdl4_SubSystem2483_SubSystem2485_SubSystem2491_SubSystem2492_LO1_1;/* '<S13>/LO1' */
extern real_T mdl4_SubSystem2483_SubSystem2485_SubSystem2491_Block7388_1;/* '<S10>/Block7388' */
extern real_T mdl4_SubSystem2483_Block7366_1;/* '<S1>/Block7366' */
extern real_T mdl4_SubSystem2483_Block7368_1;/* '<S1>/Block7368' */
extern real_T mdl4_SubSystem2483_SubSystem2484_RO1_1;/* '<S3>/RO1' */
extern real_T mdl4_SubSystem2483_Block7365_1;/* '<S1>/Block7365' */
extern real_T mdl4_Block7328_1[3];     /* '<Root>/Block7328' */
extern real_T mdl4_SubSystem2493_SubSystem2577_SubSystem2579_Block7705_1;/* '<S100>/Block7705' */
extern real_T mdl4_SubSystem2493_SubSystem2577_SubSystem2579_Block7706_1;/* '<S100>/Block7706' */
extern real_T mdl4_SubSystem2493_SubSystem2577_SubSystem2579_Block7707_1;/* '<S100>/Block7707' */
extern real_T mdl4_SubSystem2493_SubSystem2577_SubSystem2579_Block7708_1;/* '<S100>/Block7708' */
extern real_T mdl4_SubSystem2493_SubSystem2577_SubSystem2579_Block7709_1;/* '<S100>/Block7709' */
extern real_T mdl4_SubSystem2493_SubSystem2577_SubSystem2579_Block7711_1;/* '<S100>/Block7711' */
extern real_T mdl4_SubSystem2493_SubSystem2577_SubSystem2579_Block7712_1;/* '<S100>/Block7712' */
extern real_T mdl4_SubSystem2493_SubSystem2577_SubSystem2579_Block7713_1;/* '<S100>/Block7713' */
extern real_T mdl4_SubSystem2493_SubSystem2577_SubSystem2579_Block7714_1;/* '<S100>/Block7714' */
extern real_T mdl4_SubSystem2493_SubSystem2577_SubSystem2579_Block7715_1;/* '<S100>/Block7715' */
extern real_T mdl4_SubSystem2493_SubSystem2577_SubSystem2579_Block7716_1;/* '<S100>/Block7716' */
extern real_T mdl4_SubSystem2493_SubSystem2577_SubSystem2579_Block7717_1;/* '<S100>/Block7717' */
extern real_T mdl4_SubSystem2493_SubSystem2577_SubSystem2579_Block7710_1;/* '<S100>/Block7710' */
extern real_T
  mdl4_SubSystem2493_SubSystem2577_SubSystem2579_SubSystem2580_For_loop_SFunction_idx;/* '<S101>/For_loop' */
extern real_T
  mdl4_SubSystem2493_SubSystem2577_SubSystem2579_SubSystem2581_Block7736_1;/* '<S102>/Block7736' */
extern real_T
  mdl4_SubSystem2493_SubSystem2577_SubSystem2579_SubSystem2581_Block7732_1;/* '<S102>/Block7732' */
extern real_T
  mdl4_SubSystem2493_SubSystem2577_SubSystem2579_SubSystem2581_Block7733_1;/* '<S102>/Block7733' */
extern real_T
  mdl4_SubSystem2493_SubSystem2577_SubSystem2579_SubSystem2581_Block7734_1;/* '<S102>/Block7734' */
extern real_T
  mdl4_SubSystem2493_SubSystem2577_SubSystem2579_SubSystem2581_Block7735_1;/* '<S102>/Block7735' */
extern real_T
  mdl4_SubSystem2493_SubSystem2577_SubSystem2579_SubSystem2581_Block7737_1;/* '<S102>/Block7737' */
extern real_T
  mdl4_SubSystem2493_SubSystem2577_SubSystem2579_SubSystem2581_Block7738_1;/* '<S102>/Block7738' */
extern real_T
  mdl4_SubSystem2493_SubSystem2577_SubSystem2579_SubSystem2581_Block7739_1;/* '<S102>/Block7739' */
extern real_T
  mdl4_SubSystem2493_SubSystem2577_SubSystem2579_SubSystem2581_Block7740_1;/* '<S102>/Block7740' */
extern real_T
  mdl4_SubSystem2493_SubSystem2577_SubSystem2579_SubSystem2581_Block7741_1;/* '<S102>/Block7741' */
extern real_T
  mdl4_SubSystem2493_SubSystem2577_SubSystem2579_SubSystem2581_Block7742_1;/* '<S102>/Block7742' */
extern real_T
  mdl4_SubSystem2493_SubSystem2577_SubSystem2579_SubSystem2581_Block7743_1;/* '<S102>/Block7743' */
extern real_T
  mdl4_SubSystem2493_SubSystem2577_SubSystem2579_SubSystem2581_Block7744_1;/* '<S102>/Block7744' */
extern real_T
  mdl4_SubSystem2493_SubSystem2577_SubSystem2579_SubSystem2581_SubSystem2594_Inside_DSR_1
  [100];                               /* '<S116>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2577_SubSystem2579_SubSystem2581_SubSystem2594_Assignment_1
  [100];                               /* '<S116>/Assignment' */
extern real_T
  mdl4_SubSystem2493_SubSystem2577_SubSystem2579_SubSystem2581_SubSystem2593_Inside_DSR_1
  [100];                               /* '<S115>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2577_SubSystem2579_SubSystem2581_SubSystem2593_Assignment_1
  [100];                               /* '<S115>/Assignment' */
extern real_T
  mdl4_SubSystem2493_SubSystem2577_SubSystem2579_SubSystem2581_SubSystem2592_Inside_DSR_1
  [100];                               /* '<S114>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2577_SubSystem2579_SubSystem2581_SubSystem2592_Assignment_1
  [100];                               /* '<S114>/Assignment' */
extern real_T
  mdl4_SubSystem2493_SubSystem2577_SubSystem2579_SubSystem2581_SubSystem2591_Inside_DSR_1
  [3];                                 /* '<S113>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2577_SubSystem2579_SubSystem2581_SubSystem2591_Assignment_1
  [3];                                 /* '<S113>/Assignment' */
extern real_T
  mdl4_SubSystem2493_SubSystem2577_SubSystem2579_SubSystem2581_SubSystem2590_Inside_DSR_1
  [3];                                 /* '<S112>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2577_SubSystem2579_SubSystem2581_SubSystem2590_Assignment_1
  [3];                                 /* '<S112>/Assignment' */
extern real_T
  mdl4_SubSystem2493_SubSystem2577_SubSystem2579_SubSystem2581_SubSystem2589_Inside_DSR_1
  [3];                                 /* '<S111>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2577_SubSystem2579_SubSystem2581_SubSystem2589_Assignment_1
  [3];                                 /* '<S111>/Assignment' */
extern real_T
  mdl4_SubSystem2493_SubSystem2577_SubSystem2579_SubSystem2581_SubSystem2588_Inside_DSR_1
  [3];                                 /* '<S110>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2577_SubSystem2579_SubSystem2581_SubSystem2588_Assignment_1
  [3];                                 /* '<S110>/Assignment' */
extern real_T
  mdl4_SubSystem2493_SubSystem2577_SubSystem2579_SubSystem2581_SubSystem2587_Inside_DSR_1
  [3];                                 /* '<S109>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2577_SubSystem2579_SubSystem2581_SubSystem2587_Assignment_1
  [3];                                 /* '<S109>/Assignment' */
extern real_T
  mdl4_SubSystem2493_SubSystem2577_SubSystem2579_SubSystem2581_SubSystem2586_Inside_DSR_1
  [100];                               /* '<S108>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2577_SubSystem2579_SubSystem2581_SubSystem2586_Assignment_1
  [100];                               /* '<S108>/Assignment' */
extern real_T
  mdl4_SubSystem2493_SubSystem2577_SubSystem2579_SubSystem2581_SubSystem2585_Inside_DSR_1
  [100];                               /* '<S107>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2577_SubSystem2579_SubSystem2581_SubSystem2585_Assignment_1
  [100];                               /* '<S107>/Assignment' */
extern real_T
  mdl4_SubSystem2493_SubSystem2577_SubSystem2579_SubSystem2581_SubSystem2584_Inside_DSR_1
  [100];                               /* '<S106>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2577_SubSystem2579_SubSystem2581_SubSystem2584_Assignment_1
  [100];                               /* '<S106>/Assignment' */
extern real_T
  mdl4_SubSystem2493_SubSystem2577_SubSystem2579_SubSystem2581_SubSystem2583_Inside_DSR_1
  [3];                                 /* '<S105>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2577_SubSystem2579_SubSystem2581_SubSystem2583_Assignment_1
  [3];                                 /* '<S105>/Assignment' */
extern real_T
  mdl4_SubSystem2493_SubSystem2577_SubSystem2579_SubSystem2581_SubSystem2582_Inside_DSR_1
  [3];                                 /* '<S104>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2577_SubSystem2579_SubSystem2581_SubSystem2582_Assignment_1
  [3];                                 /* '<S104>/Assignment' */
extern real_T mdl4_SubSystem2493_SubSystem2494_Block7473_1;/* '<S14>/Block7473' */
extern real_T mdl4_SubSystem2493_SubSystem2494_Block7480_1;/* '<S14>/Block7480' */
extern real_T mdl4_SubSystem2493_SubSystem2494_Block7472_1;/* '<S14>/Block7472' */
extern real_T mdl4_SubSystem2493_SubSystem2494_Block7469_1;/* '<S14>/Block7469' */
extern real_T mdl4_SubSystem2493_SubSystem2494_Block7481_1;/* '<S14>/Block7481' */
extern real_T mdl4_SubSystem2493_SubSystem2494_SubSystem2495_RO1_1;/* '<S16>/RO1' */
extern real_T mdl4_SubSystem2493_SubSystem2494_Block7476_1;/* '<S14>/Block7476' */
extern real_T mdl4_SubSystem2493_SubSystem2494_Block7475_1;/* '<S14>/Block7475' */
extern real_T mdl4_SubSystem2493_SubSystem2494_Block7474_1;/* '<S14>/Block7474' */
extern real_T mdl4_SubSystem2493_SubSystem2494_Block7482_1;/* '<S14>/Block7482' */
extern real_T mdl4_SubSystem2493_SubSystem2494_SubSystem2496_RO1_1;/* '<S17>/RO1' */
extern real_T mdl4_SubSystem2493_SubSystem2494_Block7479_1;/* '<S14>/Block7479' */
extern real_T mdl4_SubSystem2493_SubSystem2494_Block7478_1;/* '<S14>/Block7478' */
extern real_T mdl4_SubSystem2493_SubSystem2494_Block7477_1;/* '<S14>/Block7477' */
extern real_T mdl4_SubSystem2493_SubSystem2494_Block7483_1;/* '<S14>/Block7483' */
extern real_T mdl4_SubSystem2493_SubSystem2494_SubSystem2497_RO1_1;/* '<S18>/RO1' */
extern real_T mdl4_SubSystem2493_SubSystem2494_Block7470_1;/* '<S14>/Block7470' */
extern real_T mdl4_SubSystem2493_SubSystem2494_Block7486_1;/* '<S14>/Block7486' */
extern real_T mdl4_SubSystem2493_SubSystem2494_Block7485_1;/* '<S14>/Block7485' */
extern real_T mdl4_SubSystem2493_SubSystem2494_Block7484_1;/* '<S14>/Block7484' */
extern real_T mdl4_SubSystem2493_SubSystem2494_Block7471_1;/* '<S14>/Block7471' */
extern real_T mdl4_SubSystem2493_SubSystem2494_SubSystem2498_RO1_1;/* '<S19>/RO1' */
extern real_T mdl4_SubSystem2493_SubSystem2494_SubSystem2500_Block7489_1;/* '<S20>/Block7489' */
extern real_T mdl4_SubSystem2493_SubSystem2494_SubSystem2500_Block7494_1;/* '<S20>/Block7494' */
extern real_T mdl4_SubSystem2493_SubSystem2494_SubSystem2500_Block7493_1;/* '<S20>/Block7493' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_Block7497_1;/* '<S24>/Block7497' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_Block7506_1;/* '<S24>/Block7506' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_Block7498_1;/* '<S24>/Block7498' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_Block7496_1;/* '<S24>/Block7496' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2506_RO1_1;/* '<S26>/RO1' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_Block7507_1[4];/* '<S24>/Block7507' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_Block7586_1;/* '<S31>/Block7586' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_Block7583_1;/* '<S31>/Block7583' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_Block7600_1;/* '<S31>/Block7600' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_Block7582_1;/* '<S31>/Block7582' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2534_RO1_1;/* '<S54>/RO1' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_Block7584_1;/* '<S31>/Block7584' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2535_RO1_1;/* '<S55>/RO1' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_Block7585_1;/* '<S31>/Block7585' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2536_RO1_1;/* '<S56>/RO1' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_Block7599_SigLabel300
  [2];                                 /* '<S31>/Block7599' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2567_Block7679_1;/* '<S62>/Block7679' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2567_Block7682_1;/* '<S62>/Block7682' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2567_Block7681_1;/* '<S62>/Block7681' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2567_Block7680_1;/* '<S62>/Block7680' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2567_Block7683_1;/* '<S62>/Block7683' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2567_SubSystem2573_For_loop_SFunction_idx;/* '<S95>/For_loop' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2567_SubSystem2574_Block7696_1;/* '<S96>/Block7696' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2567_SubSystem2574_Block7700_1;/* '<S96>/Block7700' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2567_SubSystem2574_Block7697_1;/* '<S96>/Block7697' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2567_SubSystem2574_Block7701_1;/* '<S96>/Block7701' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2567_SubSystem2574_SubSystem2576_Inside_DSR_1
  [100];                               /* '<S99>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2567_SubSystem2574_SubSystem2576_SigLabel298;/* '<S99>/Selector' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2567_SubSystem2574_SubSystem2575_Inside_DSR_1
  [100];                               /* '<S98>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2567_SubSystem2574_SubSystem2575_SigLabel299;/* '<S98>/Selector' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2567_SubSystem2572_Product_1
  [2];                                 /* '<S94>/Product' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2567_SubSystem2571_Inside_DSR_1
  [3];                                 /* '<S93>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2567_SubSystem2571_Assignment_1
  [3];                                 /* '<S93>/Assignment' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2567_SubSystem2570_Inside_DSR_1
  [3];                                 /* '<S92>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2567_SubSystem2570_Assignment_1
  [3];                                 /* '<S92>/Assignment' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2567_SubSystem2569_Inside_DSR_1
  [3];                                 /* '<S91>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2567_SubSystem2569_Assignment_1
  [3];                                 /* '<S91>/Assignment' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2567_SubSystem2568_Inside_DSR_1
  [3];                                 /* '<S90>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2567_SubSystem2568_Assignment_1
  [3];                                 /* '<S90>/Assignment' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2557_Block7653_1;/* '<S61>/Block7653' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2557_Block7656_1;/* '<S61>/Block7656' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2557_Block7655_1;/* '<S61>/Block7655' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2557_Block7654_1;/* '<S61>/Block7654' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2557_Block7657_1;/* '<S61>/Block7657' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2557_SubSystem2563_For_loop_SFunction_idx;/* '<S85>/For_loop' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2557_SubSystem2564_Block7670_1;/* '<S86>/Block7670' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2557_SubSystem2564_Block7674_1;/* '<S86>/Block7674' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2557_SubSystem2564_Block7671_1;/* '<S86>/Block7671' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2557_SubSystem2564_Block7675_1;/* '<S86>/Block7675' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2557_SubSystem2564_SubSystem2566_Inside_DSR_1
  [100];                               /* '<S89>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2557_SubSystem2564_SubSystem2566_SigLabel297;/* '<S89>/Selector' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2557_SubSystem2564_SubSystem2565_Inside_DSR_1
  [100];                               /* '<S88>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2557_SubSystem2564_SubSystem2565_SigLabel296;/* '<S88>/Selector' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2557_SubSystem2562_Product_1
  [2];                                 /* '<S84>/Product' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2557_SubSystem2561_Inside_DSR_1
  [3];                                 /* '<S83>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2557_SubSystem2561_Assignment_1
  [3];                                 /* '<S83>/Assignment' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2557_SubSystem2560_Inside_DSR_1
  [3];                                 /* '<S82>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2557_SubSystem2560_Assignment_1
  [3];                                 /* '<S82>/Assignment' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2557_SubSystem2559_Inside_DSR_1
  [3];                                 /* '<S81>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2557_SubSystem2559_Assignment_1
  [3];                                 /* '<S81>/Assignment' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2557_SubSystem2558_Inside_DSR_1
  [3];                                 /* '<S80>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2557_SubSystem2558_Assignment_1
  [3];                                 /* '<S80>/Assignment' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2547_Block7627_1;/* '<S60>/Block7627' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2547_Block7630_1;/* '<S60>/Block7630' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2547_Block7629_1;/* '<S60>/Block7629' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2547_Block7628_1;/* '<S60>/Block7628' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2547_Block7631_1;/* '<S60>/Block7631' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2547_SubSystem2553_For_loop_SFunction_idx;/* '<S75>/For_loop' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2547_SubSystem2554_Block7644_1;/* '<S76>/Block7644' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2547_SubSystem2554_Block7648_1;/* '<S76>/Block7648' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2547_SubSystem2554_Block7645_1;/* '<S76>/Block7645' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2547_SubSystem2554_Block7649_1;/* '<S76>/Block7649' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2547_SubSystem2554_SubSystem2556_Inside_DSR_1
  [100];                               /* '<S79>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2547_SubSystem2554_SubSystem2556_SigLabel294;/* '<S79>/Selector' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2547_SubSystem2554_SubSystem2555_Inside_DSR_1
  [100];                               /* '<S78>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2547_SubSystem2554_SubSystem2555_SigLabel295;/* '<S78>/Selector' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2547_SubSystem2552_Product_1
  [2];                                 /* '<S74>/Product' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2547_SubSystem2551_Inside_DSR_1
  [3];                                 /* '<S73>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2547_SubSystem2551_Assignment_1
  [3];                                 /* '<S73>/Assignment' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2547_SubSystem2550_Inside_DSR_1
  [3];                                 /* '<S72>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2547_SubSystem2550_Assignment_1
  [3];                                 /* '<S72>/Assignment' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2547_SubSystem2549_Inside_DSR_1
  [3];                                 /* '<S71>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2547_SubSystem2549_Assignment_1
  [3];                                 /* '<S71>/Assignment' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2547_SubSystem2548_Inside_DSR_1
  [3];                                 /* '<S70>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2547_SubSystem2548_Assignment_1
  [3];                                 /* '<S70>/Assignment' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2544_Block7622_1;/* '<S59>/Block7622' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2544_Block7624_1;/* '<S59>/Block7624' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2544_SubSystem2546_Inside_DSR_1
  [100];                               /* '<S69>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2544_SubSystem2546_Assignment_1
  [100];                               /* '<S69>/Assignment' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2544_SubSystem2545_Inside_DSR_1
  [100];                               /* '<S68>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2544_SubSystem2545_Assignment_1
  [100];                               /* '<S68>/Assignment' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2541_Block7616_1;/* '<S58>/Block7616' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2541_Block7618_1;/* '<S58>/Block7618' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2541_SubSystem2543_Inside_DSR_1
  [100];                               /* '<S67>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2541_SubSystem2543_Assignment_1
  [100];                               /* '<S67>/Assignment' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2541_SubSystem2542_Inside_DSR_1
  [100];                               /* '<S66>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2541_SubSystem2542_Assignment_1
  [100];                               /* '<S66>/Assignment' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2537_Block7605_1;/* '<S57>/Block7605' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2537_Block7606_1;/* '<S57>/Block7606' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2537_Block7611_1;/* '<S57>/Block7611' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2537_Block7607_1;/* '<S57>/Block7607' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2537_SubSystem2540_RO1_1;/* '<S65>/RO1' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2537_Block7612_1;/* '<S57>/Block7612' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2537_Block7604_1;/* '<S57>/Block7604' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2537_Block7610_1;/* '<S57>/Block7610' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2537_SubSystem2539_Inside_DSR_1
  [100];                               /* '<S64>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2537_SubSystem2539_Assignment_1
  [100];                               /* '<S64>/Assignment' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2537_SubSystem2538_Inside_DSR_1
  [100];                               /* '<S63>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2537_SubSystem2538_Assignment_1
  [100];                               /* '<S63>/Assignment' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2519_Block7556_1;/* '<S30>/Block7556' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2519_Block7557_1;/* '<S30>/Block7557' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2519_Block7558_1;/* '<S30>/Block7558' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2519_Block7559_1;/* '<S30>/Block7559' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2519_Block7560_1;/* '<S30>/Block7560' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2519_Block7576_1;/* '<S30>/Block7576' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2519_Block7567_SigLabel293
  [2];                                 /* '<S30>/Block7567' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2519_SubSystem2532_RO1_1
  [2];                                 /* '<S53>/RO1' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2519_Block7577_1
  [2];                                 /* '<S30>/Block7577' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2519_SubSystem2531_Inside_DSR_1
  [3];                                 /* '<S52>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2519_SubSystem2531_Selector_1;/* '<S52>/Selector' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2519_SubSystem2530_Inside_DSR_1
  [3];                                 /* '<S51>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2519_SubSystem2530_Selector_1;/* '<S51>/Selector' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2519_SubSystem2529_Inside_DSR_1
  [3];                                 /* '<S50>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2519_SubSystem2529_Selector_1;/* '<S50>/Selector' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2519_SubSystem2528_Inside_DSR_1
  [3];                                 /* '<S49>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2519_SubSystem2528_Selector_1;/* '<S49>/Selector' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2519_SubSystem2527_Inside_DSR_1
  [3];                                 /* '<S48>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2519_SubSystem2527_Selector_1;/* '<S48>/Selector' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2519_SubSystem2526_Inside_DSR_1
  [3];                                 /* '<S47>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2519_SubSystem2526_Selector_1;/* '<S47>/Selector' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2519_SubSystem2525_Inside_DSR_1
  [3];                                 /* '<S46>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2519_SubSystem2525_Selector_1;/* '<S46>/Selector' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2519_SubSystem2524_Inside_DSR_1
  [3];                                 /* '<S45>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2519_SubSystem2524_Selector_1;/* '<S45>/Selector' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2519_SubSystem2523_Inside_DSR_1
  [3];                                 /* '<S44>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2519_SubSystem2523_Selector_1;/* '<S44>/Selector' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2519_SubSystem2522_Inside_DSR_1
  [3];                                 /* '<S43>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2519_SubSystem2522_Selector_1;/* '<S43>/Selector' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2519_SubSystem2521_Inside_DSR_1
  [3];                                 /* '<S42>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2519_SubSystem2521_Selector_1;/* '<S42>/Selector' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2519_SubSystem2520_Inside_DSR_1
  [3];                                 /* '<S41>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2519_SubSystem2520_Selector_1;/* '<S41>/Selector' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2511_Block7549_SigLabel286;/* '<S29>/Block7549' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2511_Block7541_1;/* '<S29>/Block7541' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2511_Block7552_SigLabel290;/* '<S29>/Block7552' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2511_Block7550_SigLabel283;/* '<S29>/Block7550' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2511_Block7548_SigLabel289;/* '<S29>/Block7548' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2511_Block7551_SigLabel280;/* '<S29>/Block7551' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2511_Block7553_1;/* '<S29>/Block7553' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2511_SubSystem2518_Inside_DSR_1
  [3];                                 /* '<S40>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2511_SubSystem2518_Assignment_1
  [3];                                 /* '<S40>/Assignment' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2511_SubSystem2517_Inside_DSR_1
  [3];                                 /* '<S39>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2511_SubSystem2517_Assignment_1
  [3];                                 /* '<S39>/Assignment' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2511_SubSystem2516_Inside_DSR_1
  [3];                                 /* '<S38>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2511_SubSystem2516_Assignment_1
  [3];                                 /* '<S38>/Assignment' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2511_SubSystem2515_Inside_DSR_1
  [3];                                 /* '<S37>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2511_SubSystem2515_Assignment_1
  [3];                                 /* '<S37>/Assignment' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2511_SubSystem2514_Inside_DSR_1
  [3];                                 /* '<S36>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2511_SubSystem2514_Selector_1;/* '<S36>/Selector' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2511_SubSystem2513_Inside_DSR_1
  [3];                                 /* '<S35>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2511_SubSystem2513_Selector_1;/* '<S35>/Selector' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2511_SubSystem2512_Inside_DSR_1
  [3];                                 /* '<S34>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2511_SubSystem2512_Selector_1;/* '<S34>/Selector' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2509_Block7524_1;/* '<S28>/Block7524' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2509_Block7525_1;/* '<S28>/Block7525' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2509_Block7526_1;/* '<S28>/Block7526' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2509_Block7530_1
  [2];                                 /* '<S28>/Block7530' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2509_SubSystem2510_RO1_1;/* '<S33>/RO1' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2509_Block7531_1;/* '<S28>/Block7531' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2509_Block7527_1;/* '<S28>/Block7527' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2509_Block7528_1;/* '<S28>/Block7528' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2507_Block7509_1;/* '<S27>/Block7509' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2507_Block7510_1;/* '<S27>/Block7510' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2507_Block7511_1;/* '<S27>/Block7511' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2507_Block7517_1
  [2];                                 /* '<S27>/Block7517' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2507_SubSystem2508_RO1_1;/* '<S32>/RO1' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2507_Block7518_1;/* '<S27>/Block7518' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2507_Block7512_1;/* '<S27>/Block7512' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2507_Block7513_1;/* '<S27>/Block7513' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2505_Inside_DSR_1
  [3];                                 /* '<S25>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2505_Assignment_1
  [3];                                 /* '<S25>/Assignment' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2503_Inside_DSR_1[3];/* '<S23>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2503_Assignment_1[3];/* '<S23>/Assignment' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2502_Inside_DSR_1[3];/* '<S22>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2502_Selector_1;/* '<S22>/Selector' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2501_Inside_DSR_1[3];/* '<S21>/Inside_DSR' */
extern real_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2501_Selector_1;/* '<S21>/Selector' */
extern real_T mdl4_SubSystem2483_SubSystem2485_SubSystem2489_Product_1;/* '<S8>/Product' */
extern real_T mdl4_SubSystem2483_SubSystem2485_SubSystem2488_Product_Constant1_1;/* '<S12>/Constant1' */
extern real_T mdl4_SubSystem2483_SubSystem2485_SubSystem2488_Product_Constant2_1;/* '<S12>/Constant2' */
extern real_T
  mdl4_SubSystem2483_SubSystem2485_SubSystem2488_Product_RelationalOperator_1;/* '<S12>/RelationalOperator' */
extern real_T mdl4_SubSystem2483_SubSystem2485_SubSystem2488_Product_Switch1_1;/* '<S12>/Switch1' */
extern real_T mdl4_SubSystem2483_SubSystem2485_SubSystem2488_Product_Product_1;/* '<S12>/Product' */
extern real_T mdl4_SubSystem2483_SubSystem2485_SubSystem2488_Product_Switch_1;/* '<S12>/Switch' */
extern real_T mdl4_SubSystem2483_SubSystem2485_SubSystem2487_Product_1;/* '<S6>/Product' */
extern real_T mdl4_SubSystem2483_SubSystem2485_SubSystem2486_Product_Constant1_1;/* '<S11>/Constant1' */
extern real_T mdl4_SubSystem2483_SubSystem2485_SubSystem2486_Product_Constant2_1;/* '<S11>/Constant2' */
extern real_T
  mdl4_SubSystem2483_SubSystem2485_SubSystem2486_Product_RelationalOperator_1;/* '<S11>/RelationalOperator' */
extern real_T mdl4_SubSystem2483_SubSystem2485_SubSystem2486_Product_Switch1_1;/* '<S11>/Switch1' */
extern real_T mdl4_SubSystem2483_SubSystem2485_SubSystem2486_Product_Product_1;/* '<S11>/Product' */
extern real_T mdl4_SubSystem2483_SubSystem2485_SubSystem2486_Product_Switch_1;/* '<S11>/Switch' */
extern real32_T mdl4_SubSystem2483_SubSystem2485_SubSystem2490_single1_1;/* '<S9>/single1' */
extern real32_T mdl4_SubSystem2483_SubSystem2485_SubSystem2490_single2_1;/* '<S9>/single2' */
extern real32_T
  mdl4_SubSystem2483_SubSystem2485_SubSystem2491_SubSystem2492_single1_1;/* '<S13>/single1' */
extern real32_T
  mdl4_SubSystem2483_SubSystem2485_SubSystem2491_SubSystem2492_single2_1;/* '<S13>/single2' */
extern real32_T mdl4_SubSystem2483_SubSystem2484_single1_1;/* '<S3>/single1' */
extern real32_T mdl4_SubSystem2483_SubSystem2484_single2_1;/* '<S3>/single2' */
extern real32_T mdl4_SubSystem2493_SubSystem2494_SubSystem2495_single1_1;/* '<S16>/single1' */
extern real32_T mdl4_SubSystem2493_SubSystem2494_SubSystem2495_single2_1;/* '<S16>/single2' */
extern real32_T mdl4_SubSystem2493_SubSystem2494_SubSystem2496_single1_1;/* '<S17>/single1' */
extern real32_T mdl4_SubSystem2493_SubSystem2494_SubSystem2496_single2_1;/* '<S17>/single2' */
extern real32_T mdl4_SubSystem2493_SubSystem2494_SubSystem2497_single1_1;/* '<S18>/single1' */
extern real32_T mdl4_SubSystem2493_SubSystem2494_SubSystem2497_single2_1;/* '<S18>/single2' */
extern real32_T mdl4_SubSystem2493_SubSystem2494_SubSystem2498_single1_1;/* '<S19>/single1' */
extern real32_T mdl4_SubSystem2493_SubSystem2494_SubSystem2498_single2_1;/* '<S19>/single2' */
extern real32_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2506_single1_1;/* '<S26>/single1' */
extern real32_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2506_single2_1;/* '<S26>/single2' */
extern real32_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2534_single1_1;/* '<S54>/single1' */
extern real32_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2534_single2_1;/* '<S54>/single2' */
extern real32_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2535_single1_1;/* '<S55>/single1' */
extern real32_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2535_single2_1;/* '<S55>/single2' */
extern real32_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2536_single1_1;/* '<S56>/single1' */
extern real32_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2536_single2_1;/* '<S56>/single2' */
extern real32_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2537_SubSystem2540_single1_1;/* '<S65>/single1' */
extern real32_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2533_SubSystem2537_SubSystem2540_single2_1;/* '<S65>/single2' */
extern real32_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2519_SubSystem2532_single1_1
  [2];                                 /* '<S53>/single1' */
extern real32_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2519_SubSystem2532_single2_1;/* '<S53>/single2' */
extern real32_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2509_SubSystem2510_single1_1;/* '<S33>/single1' */
extern real32_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2509_SubSystem2510_single2_1;/* '<S33>/single2' */
extern real32_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2507_SubSystem2508_single1_1;/* '<S32>/single1' */
extern real32_T
  mdl4_SubSystem2493_SubSystem2494_SubSystem2500_SubSystem2504_SubSystem2507_SubSystem2508_single2_1;/* '<S32>/single2' */

/* Model entry point functions */
extern void mdl4_initialize(void);
extern void mdl4_step(void);
extern void mdl4_terminate(void);

/* Real-time Model object */
extern RT_MODEL_mdl4 *const mdl4_M;

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
 * '<Root>' : 'mdl4'
 * '<S1>'   : 'mdl4/SubSystem2483'
 * '<S2>'   : 'mdl4/SubSystem2493'
 * '<S3>'   : 'mdl4/SubSystem2483/SubSystem2484'
 * '<S4>'   : 'mdl4/SubSystem2483/SubSystem2485'
 * '<S5>'   : 'mdl4/SubSystem2483/SubSystem2485/SubSystem2486'
 * '<S6>'   : 'mdl4/SubSystem2483/SubSystem2485/SubSystem2487'
 * '<S7>'   : 'mdl4/SubSystem2483/SubSystem2485/SubSystem2488'
 * '<S8>'   : 'mdl4/SubSystem2483/SubSystem2485/SubSystem2489'
 * '<S9>'   : 'mdl4/SubSystem2483/SubSystem2485/SubSystem2490'
 * '<S10>'  : 'mdl4/SubSystem2483/SubSystem2485/SubSystem2491'
 * '<S11>'  : 'mdl4/SubSystem2483/SubSystem2485/SubSystem2486/Product'
 * '<S12>'  : 'mdl4/SubSystem2483/SubSystem2485/SubSystem2488/Product'
 * '<S13>'  : 'mdl4/SubSystem2483/SubSystem2485/SubSystem2491/SubSystem2492'
 * '<S14>'  : 'mdl4/SubSystem2493/SubSystem2494'
 * '<S15>'  : 'mdl4/SubSystem2493/SubSystem2577'
 * '<S16>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2495'
 * '<S17>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2496'
 * '<S18>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2497'
 * '<S19>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2498'
 * '<S20>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500'
 * '<S21>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2501'
 * '<S22>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2502'
 * '<S23>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2503'
 * '<S24>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504'
 * '<S25>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2505'
 * '<S26>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2506'
 * '<S27>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2507'
 * '<S28>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2509'
 * '<S29>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2511'
 * '<S30>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2519'
 * '<S31>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2533'
 * '<S32>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2507/SubSystem2508'
 * '<S33>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2509/SubSystem2510'
 * '<S34>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2511/SubSystem2512'
 * '<S35>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2511/SubSystem2513'
 * '<S36>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2511/SubSystem2514'
 * '<S37>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2511/SubSystem2515'
 * '<S38>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2511/SubSystem2516'
 * '<S39>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2511/SubSystem2517'
 * '<S40>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2511/SubSystem2518'
 * '<S41>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2519/SubSystem2520'
 * '<S42>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2519/SubSystem2521'
 * '<S43>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2519/SubSystem2522'
 * '<S44>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2519/SubSystem2523'
 * '<S45>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2519/SubSystem2524'
 * '<S46>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2519/SubSystem2525'
 * '<S47>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2519/SubSystem2526'
 * '<S48>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2519/SubSystem2527'
 * '<S49>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2519/SubSystem2528'
 * '<S50>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2519/SubSystem2529'
 * '<S51>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2519/SubSystem2530'
 * '<S52>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2519/SubSystem2531'
 * '<S53>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2519/SubSystem2532'
 * '<S54>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2533/SubSystem2534'
 * '<S55>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2533/SubSystem2535'
 * '<S56>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2533/SubSystem2536'
 * '<S57>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2533/SubSystem2537'
 * '<S58>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2533/SubSystem2541'
 * '<S59>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2533/SubSystem2544'
 * '<S60>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2533/SubSystem2547'
 * '<S61>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2533/SubSystem2557'
 * '<S62>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2533/SubSystem2567'
 * '<S63>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2533/SubSystem2537/SubSystem2538'
 * '<S64>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2533/SubSystem2537/SubSystem2539'
 * '<S65>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2533/SubSystem2537/SubSystem2540'
 * '<S66>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2533/SubSystem2541/SubSystem2542'
 * '<S67>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2533/SubSystem2541/SubSystem2543'
 * '<S68>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2533/SubSystem2544/SubSystem2545'
 * '<S69>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2533/SubSystem2544/SubSystem2546'
 * '<S70>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2533/SubSystem2547/SubSystem2548'
 * '<S71>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2533/SubSystem2547/SubSystem2549'
 * '<S72>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2533/SubSystem2547/SubSystem2550'
 * '<S73>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2533/SubSystem2547/SubSystem2551'
 * '<S74>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2533/SubSystem2547/SubSystem2552'
 * '<S75>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2533/SubSystem2547/SubSystem2553'
 * '<S76>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2533/SubSystem2547/SubSystem2554'
 * '<S77>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2533/SubSystem2547/SubSystem2553/For_loop'
 * '<S78>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2533/SubSystem2547/SubSystem2554/SubSystem2555'
 * '<S79>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2533/SubSystem2547/SubSystem2554/SubSystem2556'
 * '<S80>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2533/SubSystem2557/SubSystem2558'
 * '<S81>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2533/SubSystem2557/SubSystem2559'
 * '<S82>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2533/SubSystem2557/SubSystem2560'
 * '<S83>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2533/SubSystem2557/SubSystem2561'
 * '<S84>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2533/SubSystem2557/SubSystem2562'
 * '<S85>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2533/SubSystem2557/SubSystem2563'
 * '<S86>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2533/SubSystem2557/SubSystem2564'
 * '<S87>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2533/SubSystem2557/SubSystem2563/For_loop'
 * '<S88>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2533/SubSystem2557/SubSystem2564/SubSystem2565'
 * '<S89>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2533/SubSystem2557/SubSystem2564/SubSystem2566'
 * '<S90>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2533/SubSystem2567/SubSystem2568'
 * '<S91>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2533/SubSystem2567/SubSystem2569'
 * '<S92>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2533/SubSystem2567/SubSystem2570'
 * '<S93>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2533/SubSystem2567/SubSystem2571'
 * '<S94>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2533/SubSystem2567/SubSystem2572'
 * '<S95>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2533/SubSystem2567/SubSystem2573'
 * '<S96>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2533/SubSystem2567/SubSystem2574'
 * '<S97>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2533/SubSystem2567/SubSystem2573/For_loop'
 * '<S98>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2533/SubSystem2567/SubSystem2574/SubSystem2575'
 * '<S99>'  : 'mdl4/SubSystem2493/SubSystem2494/SubSystem2500/SubSystem2504/SubSystem2533/SubSystem2567/SubSystem2574/SubSystem2576'
 * '<S100>' : 'mdl4/SubSystem2493/SubSystem2577/SubSystem2579'
 * '<S101>' : 'mdl4/SubSystem2493/SubSystem2577/SubSystem2579/SubSystem2580'
 * '<S102>' : 'mdl4/SubSystem2493/SubSystem2577/SubSystem2579/SubSystem2581'
 * '<S103>' : 'mdl4/SubSystem2493/SubSystem2577/SubSystem2579/SubSystem2580/For_loop'
 * '<S104>' : 'mdl4/SubSystem2493/SubSystem2577/SubSystem2579/SubSystem2581/SubSystem2582'
 * '<S105>' : 'mdl4/SubSystem2493/SubSystem2577/SubSystem2579/SubSystem2581/SubSystem2583'
 * '<S106>' : 'mdl4/SubSystem2493/SubSystem2577/SubSystem2579/SubSystem2581/SubSystem2584'
 * '<S107>' : 'mdl4/SubSystem2493/SubSystem2577/SubSystem2579/SubSystem2581/SubSystem2585'
 * '<S108>' : 'mdl4/SubSystem2493/SubSystem2577/SubSystem2579/SubSystem2581/SubSystem2586'
 * '<S109>' : 'mdl4/SubSystem2493/SubSystem2577/SubSystem2579/SubSystem2581/SubSystem2587'
 * '<S110>' : 'mdl4/SubSystem2493/SubSystem2577/SubSystem2579/SubSystem2581/SubSystem2588'
 * '<S111>' : 'mdl4/SubSystem2493/SubSystem2577/SubSystem2579/SubSystem2581/SubSystem2589'
 * '<S112>' : 'mdl4/SubSystem2493/SubSystem2577/SubSystem2579/SubSystem2581/SubSystem2590'
 * '<S113>' : 'mdl4/SubSystem2493/SubSystem2577/SubSystem2579/SubSystem2581/SubSystem2591'
 * '<S114>' : 'mdl4/SubSystem2493/SubSystem2577/SubSystem2579/SubSystem2581/SubSystem2592'
 * '<S115>' : 'mdl4/SubSystem2493/SubSystem2577/SubSystem2579/SubSystem2581/SubSystem2593'
 * '<S116>' : 'mdl4/SubSystem2493/SubSystem2577/SubSystem2579/SubSystem2581/SubSystem2594'
 */
#endif                                 /* RTW_HEADER_mdl4_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
