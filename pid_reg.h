/*==================================================================
  File name    : $Id$
  Author       : E. vd Logt
  ------------------------------------------------------------------
  Purpose : This file contains the defines for the PID controller.
  ------------------------------------------------------------------
  $Log$
  Revision 1.8  2005/03/26 13:53:21  Emile
  - During State "Mash Preheat" pump is set to ON (again)
  - Added a burner_on option (bit 4 on LSB_IO). For this two new registry
    variables are introduced (BURNER_HHYST and BURNER_LHYST)
  - Various screens a little enlarged (no scrollbars visible anymore)

  Revision 1.7  2004/05/13 20:51:00  emile
  - Main loop timing improved. Only 99 (of 100) cycles were executed. Loop
    timing is now reset after 100 loops (5 seconds)
  - TS parameter now only works on PID-controller time-slice. Max. is 20 sec.
  - Bug-fix in init_ma() filter when init. to a value (should be /N).
  - LPF for D-term of PID controller added. New reg. var. K_LPF
  - PID Debug label added + checkbox in PID screen. Default off (NO reg var).
  - Statusbar object added
  - Start made with network functionality. Not operational yet.

  Revision 1.6  2004/05/10 20:54:30  emile
  - Bug-fix: log-file header: '\n' was removed, is corrected now
  - Hints added to PID dialog screen
  - Now four PID controllers to choose from. Old ebrew version is still listed,
    but should not be used anymore. Simulation showed stability problems.
    Preferably use the type C controller.

  Revision 1.5  2004/05/08 14:52:52  emile
  - Mash pre-heat functionality added to STD. New registry variable PREHEAT_TIME.
    tset_hlt is set to next mash temp. if mash timer >= time - PREHEAT_TIME
  - View mash progress screen: reorganised, pre-heat timers added, timers are now
    in seconds instead of minutes.
  - update_tset() function removed. Now incorporated in STD, states 3-5 + (new state) 13.
  - THLT_HLIMIT and THLT_LLIMIT and state 4 'Bypass Heat Exchanger' removed
  - Reorganisation of several variables (e.g. ms_idx, ms_tot) into (other) structs.
  - 'Apply' Button added to Fix parameters dialog screen.
  - 'Edit mash scheme' no longer resets the (running) mash timers
  - 'Mash progress controlled by' function removed. Registry var 'mash_control' now
    also removed.
  - Changing init. volume of HLT did not result in an update on screen. Corrected.

  Revision 1.4  2004/05/05 15:44:16  emile
  - Main Screen picture update
  - Init_ma() now initialises with a value instead of 0. Avoids reset of signal.
  - STD update: calculation of volumes should be correct now
  - Parameter added for early start of mash timer. Registry var. TOffset2
  - Registry variables Kc, Ti, Td, TOffset and TS are now floats instead of integers.
  - Some screens updated with hints (also of labels)
  - Bug-fix: unnecessary delay after change in gamma. Is corrected now
  - Help via menu now also works

  Revision 1.3  2004/04/25 14:02:17  emile
  - Added a 'type C' PID controller, function pid_reg3(). Possible to select
    this from the PID settings dialog screen. Left the old one in for
    compatibility. New registry variable PID_Model.
  - Gamma added to log-file, so that the PID controller can be tuned.

  Revision 1.2  2002/12/30 13:33:45  emile
  - Headers with CVS tags added to every source file
  - Restore Settings function is added
  - "ebrew" registry key now in a define REGKEY

  V0.1 060302 First version
  ==================================================================
*/
#ifndef PID_REG_H
#define PID_REG_H

#ifdef __cplusplus
extern "C" {
#endif

// These defines are needed for loop timing and PID controller timing
#define TWENTY_SECONDS (400)
#define TEN_SECONDS    (200)
#define FIVE_SECONDS   (100)
#define ONE_SECOND      (20)
// Period time of TTimer in msec.
#define T_50MSEC        (50)
#define PI             (3.141592654)
#define NODF            (1)

// PID controller upper & lower limit [%]
#define GMA_HLIM (100.0)
#define GMA_LLIM   (0.0)

// Constants needed for system identification
typedef double vector[6];
typedef double matrix[6][6];

typedef struct _pid_params
{
   double kc; // Controller gain from Dialog Box
   double ti; // Time-constant for I action from Dialog Box
   double td; // Time-constant for D action from Dialog Box
   double ts; // Sample time [sec.] from Dialog Box
   double k_lpf; // Time constant [sec.] for LPF filter
   double k0; // k0 value for PID controller
   double k1; // k1 value for PID controller
   double k2; // k2 value for PID controller
   double k3; // k3 value for PID controller
   double lpf1; // value for LPF filter
   double lpf2; // value for LPF filter
   int    ts_ticks;  // ticks for timer
   int    pid_model; // PID Controller type [0..3]
   int    burner_hyst_h; // Upper hysteresis limit for gas burner
   int    burner_hyst_l; // Lower hysteresis limit for gas burner
   double pp; // debug
   double pi; // debug
   double pd; // debug
} pid_params; // struct pid_params

//------------------------------------------------------------------
// This struct contains the estimated values for the PID controller.
// These are the optimum settings for the Takahashi controller and
// are calculated from the system identification function sys_id()
// and calc_ultimate_gain_period()
//------------------------------------------------------------------
typedef struct _sys_id_params
{
   int    N;   // order N for system identification and parameter estimation
   double kpu; // Ultimate gain
   double tu;  // Ultimate period
   double kc;  // Controller gain
   double ti;  // Time-constant for I action
   double td;  // Time-constant for D action
   double kr;  // Kr value for PID Takahashi controller
   double ki;  // ki value for PID Takahashi controller
   double kd;  // kd value for PID Takahashi controller
} sys_id_params; // struct sys_id_params

//--------------------
// Function Prototypes
//--------------------
void init_pid1(pid_params *p);
void pid_reg1(double xk, double *yk, double tset, pid_params *p, int vrg);
void init_pid2(pid_params *p);
void pid_reg2(double xk, double *yk, double tset, pid_params *p, int vrg);
void init_pid3(pid_params *p);
void pid_reg3(double xk, double *yk, double tset, pid_params *p, int vrg);
void init_pid4(pid_params *p);
void pid_reg4(double xk, double *yk, double tset, pid_params *p, int vrg);
void init_pid5(pid_params *p, int N);

void   sys_id(double uk, double yk, int N, int nodf);
int    calc_ultimate_gain_geriod(sys_id_params *p, double ts);
void   calc_pid_parameters(sys_id_params *p, double ts);
void   pid_reg5(double xk, double *yk, double tset, pid_params *p, int vrg,
                sys_id_params *psys_id, int st);

double vxv2s(vector vec1, vector vec2, int N);
void   vxv2m(vector vec1, vector vec2, matrix *m, int N);
void   vxm2v(vector vec1, matrix m1, vector *vecr, int N);
void   mxv2v(matrix m1, vector vec1, vector *vecr, int N);
void   vxs2v(vector *vec, double x, int N);
void   vav2v(vector *vec1, vector vec2, int N);
void   mxs2m(matrix *m, double x, int N);
void   mam2m(matrix *m1, matrix m2, int N);

#ifdef __cplusplus
};
#endif
#endif
