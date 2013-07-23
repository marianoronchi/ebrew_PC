// ==================================================================
// Filenaam    : $Id$
// Auteur      : E. van de Logt
// ------------------------------------------------------------------
// Purpose : This include file contains defines for misc.c
// ------------------------------------------------------------------
// Modification History :
// $Log$
// Revision 1.22  2013/07/21 22:32:47  Emile
// - 3rd intermediate version to support ebrew 2.0 rev.1.5 hardware
// - Changes to Measurement Dialog Screen: VHLT, VMLT, THLT, TMLT
// - Registry: several parameters removed + parameters renamed
// - Ttriac & DAC code & parameters removed
//
// Revision 1.21  2013/06/22 23:04:19  Emile
// - Second intermediate version: scheduler added and timer interrupt divided
//   over a number of tasks.
// - Version works with Ebrew hardware, task duration needs to be optimised!
//
// Revision 1.20  2013/06/16 14:39:19  Emile
// Intermediate version for new Ebrew 2.0 USB hardware:
// - Hardware settings Dialog: COM Port + Settings added + LEDx removed
// - PortTalk + i2c_dll + Start_i2c_communication + Reset_I2C_Bus removed
// - New routines for COM-Port added
// - Generate_IO_Signals() now uses COM_port_write to address all hardware
// - This version works with new hardware: PUMP on/off + LEDs are working
// - HEATER led and PWM output do not work yet + TODO: add scheduler.
//
// Revision 1.19  2011/05/29 20:56:26  Emile
// - New Registry variables added: STC_N, STC_TD and STC_ADF
// - PID Settings Dialog screen extended with new parameters for self-tuning
//   controller: possibility to set the system order N, an estimate for the
//   time-delay and a boolean whether or not to use adaptive dir. forgetting.
// - PID Settings Dialog screen: parameters enabled/disabled when a
//   specific PID controller is chosen.
// - New functions time_delay() and init_time_delay() added
// - Changes made in init_pid2() function header.
// - Unit-test cases updated and extended with tests for new functions.
//
// Revision 1.18  2007/08/26 22:23:21  Emile
// - Slope Limiter function added for Thlt, Tmlt, Vhlt, Vmlt and tset_hlt
// - Five Registry variables added: THLT_SLOPE, TMLT_SLOPE, VHLT_SLOPE,
//   VMLT_SLOPE and TSET_HLT_SLOPE
// - Bug-fix setting MA order for HLT Volume: this was coupled to MA order of
//   HLT temperature. Corrected
// - Measurements... and PID controller settings... dialog screen updated.
//
// Revision 1.17  2007/07/06 22:23:02  Emile
// - The real time between two lines from a log-file is now used instead of a
//   fixed 5 sec. time when reading a log-file.
// - Leading-zero bug solved in Mash Progress screen
// - i2c_stop() only called with PT_CLOSE in case of exit of program
// - System Identification library functions added (but not used yet).
//
// Revision 1.16  2006/11/18 23:06:37  Emile
// - View Mash/Sparging screen is improved: time-stamps are placed when a
//   mashing or sparging phase has started.
// - Read_log_file is improved: time-stamps are generated, so that old log-files
//   can be read and time-stamp information can be seen in the Mash/Sparging screen.
// - Datagraps are set to a step-size of 1 instead of 2 (1 div = 100 seconds now).
// - Main screen updated: Heating power is now in % and correct volumes are added.
//
// Revision 1.15  2006/02/19 13:14:35  Emile
// - Bug-fix reading logfile(). If the latest mash timer was not started yet,
//   it was set to a high value (which was the linenumber in the logfile).
//   Setting the mash-timers should be oke now.
// - Max. linenumber changed from 32767 to 65535, meaning that 91 hours in 1
//   log-entry is possible now.
//
// Revision 1.14  2005/08/30 09:17:42  Emile
// - Bug-fix reading log-file. Only entries > 1 minute can be imported.
// - sp_idx added to log-file, instead of PID_ON.
// - Stay 10 seconds in state 5 at start of sparging for logging purposes
// - Reorganisation of routines of reading log file, added print_p_struct().
//
// Revision 1.13  2005/03/26 13:53:21  Emile
// - During State "Mash Preheat" pump is set to ON (again)
// - Added a burner_on option (bit 4 on LSB_IO). For this two new registry
//   variables are introduced (BURNER_HHYST and BURNER_LHYST)
// - Various screens a little enlarged (no scrollbars visible anymore)
//
// Revision 1.12  2004/05/13 20:51:00  emile
// - Main loop timing improved. Only 99 (of 100) cycles were executed. Loop
//   timing is now reset after 100 loops (5 seconds)
// - TS parameter now only works on PID-controller time-slice. Max. is 20 sec.
// - Bug-fix in init_ma() filter when init. to a value (should be /N).
// - LPF for D-term of PID controller added. New reg. var. K_LPF
// - PID Debug label added + checkbox in PID screen. Default off (NO reg var).
// - Statusbar object added
// - Start made with network functionality. Not operational yet.
//
// Revision 1.11  2004/05/08 14:52:52  emile
// - Mash pre-heat functionality added to STD. New registry variable PREHEAT_TIME.
//   tset_hlt is set to next mash temp. if mash timer >= time - PREHEAT_TIME
// - View mash progress screen: reorganised, pre-heat timers added, timers are now
//   in seconds instead of minutes.
// - update_tset() function removed. Now incorporated in STD, states 3-5 + (new state) 13.
// - THLT_HLIMIT and THLT_LLIMIT and state 4 'Bypass Heat Exchanger' removed
// - Reorganisation of several variables (e.g. ms_idx, ms_tot) into (other) structs.
// - 'Apply' Button added to Fix parameters dialog screen.
// - 'Edit mash scheme' no longer resets the (running) mash timers
// - 'Mash progress controlled by' function removed. Registry var 'mash_control' now
//   also removed.
// - Changing init. volume of HLT did not result in an update on screen. Corrected.
//
// Revision 1.10  2004/05/05 15:44:16  emile
// - Main Screen picture update
// - Init_ma() now initialises with a value instead of 0. Avoids reset of signal.
// - STD update: calculation of volumes should be correct now
// - Parameter added for early start of mash timer. Registry var. TOffset2
// - Registry variables Kc, Ti, Td, TOffset and TS are now floats instead of integers.
// - Some screens updated with hints (also of labels)
// - Bug-fix: unnecessary delay after change in gamma. Is corrected now
// - Help via menu now also works
//
// Revision 1.9  2004/01/31 16:01:05  emile
// - Init. HW High/Low limit temp. changed to 70/50 C respectively.
// - Added code for calculation/simulation of Vhlt and Vboil
// - Hardware dialog updated: 3 new controls added for Vhlt and Vboil simulation
// - Registry key no longer in ebrew but in Software\\ebrew
// - First attempt to catch CVS version ID in source code
//
// Revision 1.8  2003/09/15 20:37:22  emile
// - LM76 constants renamed in LM92 constants
// - Pump Popupmenu added (same as already done for the valves)
// - Added support for LED3 and LED4 displays
// - 'I2C settings' renamed into 'Hardware Settings'
// - Added more variables to LED1..LED4 selection. Now 6 variables to select
// - Added SET_LED macro
// - Added Triac Temperature protection functionality
//
// Revision 1.7  2003/07/11 18:34:46  emile
// - tset_mlt added. Also added to log-file (tset_mlt now replaces gamma).
// - Bug solved: transition to 'EMPTY_MLT' was 1 sparging cycle too early.
// - Log-file header updated
// - init_adc(): all vref initialisations are now the same (/ 2560).
//               Removed the / 10 division of AD4 in the main loop, this is
//               now done in init_adc().
// - Multiply and division changed into <<= and >>= (in lm92_read())
//
// Revision 1.6  2003/06/01 13:40:45  emile
// - Bugfix: switch/fix for Tmlt and Thlt were in wrong time-slice. Corrected.
// - Switch/fix for std state added for easier testing
// - Vmash value added to 'Options|Sparge & STD Settings' dialog screen.
//
// Revision 1.5  2003/06/01 11:53:48  emile
// - tset has been renamed in tset_hlt for more clearance
// - STD: state 1 -> 2 has been changed. This was 'ms[0].timer != NOT_STARTED'.
//        This is now 'thlt >= tset_hlt', because timer0 only starts with water
//        in the MLT => this caused a dead-lock.
// - 6 defines have been made adjustable via 'Options|Sparge & STD Settings'.
//   These defines were TMLT_HLIMIT, TMLT_LLIMIT, TIMEOUT_1SEC, VMLT_EMPTY,
//   TIMEOUT3 and TIMEOUT4.
//
// Revision 1.4  2003/01/04 22:35:50  emile
// - Restore Settings function now restores all relevant variables (not just
//   the mashing variables). Several separate functions are created to
//   support this.
//
// Revision 1.3  2002/12/30 20:21:59  emile
// - Bug 2 29-12-02 solved: start mash timers if temp >= tref instead of >.
// - Bug 3 29-12-02 solved: deadlock in std_state 4 when mashing is finished.
// - Bug 4 29-12-02 solved: rush through STD. Sparging parameters were not
//   initialised. New function Init_Sparge_Settings() added.
// - Sparge variables now added to 'View Mash Progress' screen.
// - std_struct added for more flexibility of fixing STD values.
//
// Revision 1.2  2002/12/30 13:33:45  emile
// - Headers with CVS tags added to every source file
// - Restore Settings function is added
// - "ebrew" registry key now in a define REGKEY
//
// 27-07-02 LGT    moving_average() function added
// 13-03-02 LGT    Initial version, derived from brew.c
// ==================================================================
#ifndef MISC_H
#define MISC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#ifndef FALSE
#define FALSE        (0)
#endif
#ifndef TRUE
#define TRUE         (1)
#endif

#define SLEN       (255)
#define MAX_MS      (10)
#define MAX_SP      (10) 
#define NOT_STARTED (-1)

#define LOG_HDR_SIZE (10)
#define LOG_LAST_LINE (3)
#define COLON         ","

typedef struct _log_struct
{
   char          brew_date[20];  /* Brew date */
   unsigned int  bline;          /* First line with valid information */
   unsigned int  eline;          /* Last line with valid information */
   char          btime[20];      /* Begin time of brew session */
   char          etime[20];      /* End time of brew session */
   int           lms_idx;        /* Last known value of ms_idx */
   int           tmr_ms_idx;     /* Timer value of ms_idx timer */
   int           std_val;        /* Last known value of std_state */
   unsigned int  start_lstd;     /* The start line number of the latest ebrew_std */
   unsigned int  start_lmtmr;    /* The start line number of the start of the latest mash timer */
   int           lsp_idx;        /* Last known value of sp_idx */
   unsigned int  mashing_start[MAX_MS];  /* Start line of Mashing */
   unsigned int  sparging_start[MAX_SP]; /* Start line of Sparging */
   unsigned int  sparging_start2[MAX_SP]; /* Start line of Sparging */
   unsigned int  boil_start;     /* Start line of Boiling */
   unsigned int  chill_start;    /* Start line of Chilling */
   double        time_period;    /* Time [sec.] between 2 lines in the log-file */
} log_struct;

typedef struct _maisch_schedule
{
   double time;           /* time (min.) to remain at this temperature */
   double temp;           /* temperature (Celsius) to hold */
   int    timer;          /* timer, init. to NOT_STARTED */
   char   time_stamp[20]; /* time when timer was started */
} maisch_schedule;

typedef struct _sparge_struct
{
   /* Mash Settings */
   double temp_offset;     // Offset to add to Tset to compensate for HLT-MLT losses
   double temp_offset2;    // Offset to add to Tmlt for early start of mash timers
   int    ph_timer;        // Mash pre-heat timer
   /* Sparge Settings */
   int    sp_batches;      // Total number of sparge batches
   int    sp_time;         // Time between two sparge batches in minutes
   int    mash_vol;        // Total mashing volume in litres
   int    sp_vol;          // Total sparge volume in litres
   int    boil_time;       // Total boiling time in minutes
   int    sp_time_ticks;   // sp_time in TS ticks
   int    boil_time_ticks; // boil_time in TS ticks
   double sp_vol_batch;    // Sparge volume of 1 batch = sp_vol / sp_batches
   /* STD Settings */
   double vmlt_empty;      // MLT is empty below this volume
   int    to_xsec;         // Timeout value for state 8
   int    to3;             // Timeout value for state 10 -> 11
   int    to4;             // Timout value for state 11 -> 10
   /* Sparge Time-stamps */
   char   mlt2boil[MAX_SP][40]; // MAX_SP strings for time-stamp moment of MLT -> BOIL
   char   hlt2mlt[MAX_SP][40];  // MAX_SP strings for time-stamp moment of HLT -> MLT
} sparge_struct;

typedef struct _std_struct
{
   int    ebrew_std; // Current state of STD
   int    ms_tot;    // tot. nr. of valid temp & time values
   int    ms_idx;    // index in ms[] array
   int    sp_idx;    // Sparging index [0..sps->sp_batches-1]
   int    timer1;    // Timer for state 'Sparging Rest'
   int    timer2;    // Timer for state 'Delay_1SEC'
   int    timer3;    // Timer for transition to state 'Empty Heat Exchanger'
   int    timer4;    // Timer for state 'Empty Heat Exchanger'
   int    timer5;    // Timer for boiling time
} std_struct;

#define MAX_MA (50)
typedef struct _ma
{
   double T[MAX_MA]; // array with delayed values of input signal
   int    index;     // index in T[] where to store the new input value
   int    N;         // The order of the MA filter. Note that N < MAX_MA
   double sum;       // The running sum of the MA filter
} ma;

#define VBOIL_START (0.0)
typedef struct _volume_struct
{
   double Vhlt;       // Volume of HLT in litres
   double Vmlt;       // Volume of MLT in litres
   double Vboil;      // Volume of Boil kettle in litres
   double Vhlt_old;   // Prev. value of Vhlt, used in STD
   double Vmlt_old;   // Prev. value of Vmlt, used in STD
   double Vboil_old;  // Prev. value of Vboil, used in STD
   // Assumption is made here that Vmlt is always measured.
   int    Vboil_simulated; // true = Vboil is not measured, but calculated
} volume_struct;

//------------------------------
// Defines for read_input_file()
//------------------------------
#define INIT_TIMERS    (1)
#define NO_INIT_TIMERS (0)

//------------------------------------------------------
// Defines for State Transition Diagram.
// The STD is called every second => 1 tick == 1 second.
//------------------------------------------------------
#define S00_INITIALISATION         (0)
#define S01_WAIT_FOR_HLT_TEMP      (1)
#define S02_FILL_MLT               (2)
#define S03_MASH_IN_PROGRESS       (3)
#define S04_MASH_TIMER_RUNNING     (4)
#define S13_MASH_PREHEAT_HLT      (13)
#define S05_SPARGING_REST          (5)
#define S06_PUMP_FROM_MLT_TO_BOIL  (6)
#define S07_PUMP_FROM_HLT_TO_MLT   (7)
#define S08_DELAY_xSEC             (8)
#define S09_EMPTY_MLT              (9)
#define S10_BOILING               (10)
#define S11_EMPTY_HEAT_EXCHANGER  (11)
#define S12_CHILL                 (12)

//--------------------------------------------------------------------------
// #defines for the valves. Each valve can be set manually or automatically
// by the STD. Bit-values are for the variable 'valves'.
//--------------------------------------------------------------------------
#define V7M  (0x8000)
#define V6M  (0x4000)
#define V5M  (0x2000)
#define V4M  (0x1000)
#define V3M  (0x0800)
#define V2M  (0x0400)
#define V1M  (0x0200)
#define P0M  (0x0100)
#define V7b  (0x0080)
#define V6b  (0x0040)
#define V5b  (0x0020)
#define V4b  (0x0010)
#define V3b  (0x0008)
#define V2b  (0x0004)
#define V1b  (0x0002)
#define P0b  (0x0001)

#define V71MTXT "V7 ON (M)"
#define V70MTXT "V7 OFF (M)"
#define V71ATXT "V7 ON (A)"
#define V70ATXT "V7 OFF (A)"
#define V61MTXT "V6 ON (M)"
#define V60MTXT "V6 OFF (M)"
#define V61ATXT "V6 ON (A)"
#define V60ATXT "V6 OFF (A)"
#define V51MTXT "V5 ON (M)"
#define V50MTXT "V5 OFF (M)"
#define V51ATXT "V5 ON (A)"
#define V50ATXT "V5 OFF (A)"
#define V41MTXT "V4 ON (M)"
#define V40MTXT "V4 OFF (M)"
#define V41ATXT "V4 ON (A)"
#define V40ATXT "V4 OFF (A)"
#define V31MTXT "V3 ON (M)"
#define V30MTXT "V3 OFF (M)"
#define V31ATXT "V3 ON (A)"
#define V30ATXT "V3 OFF (A)"
#define V21MTXT "V2 ON (M)"
#define V20MTXT "V2 OFF (M)"
#define V21ATXT "V2 ON (A)"
#define V20ATXT "V2 OFF (A)"
#define V11MTXT "V1 ON (M)"
#define V10MTXT "V1 OFF (M)"
#define V11ATXT "V1 ON (A)"
#define V10ATXT "V1 OFF (A)"
#define P01MTXT "PUMP ON (M)"
#define P00MTXT "PUMP OFF (M)"
#define P01ATXT "PUMP ON (A)"
#define P00ATXT "PUMP OFF (A)"

void add_seconds(char *s, int seconds);
int decode_log_file(FILE *fd, log_struct p[]);
int read_input_file(char *inf, maisch_schedule ms[], int *count, double ts, int init);
int update_std(volume_struct *vol, double tmlt, double thlt, double *tset_mlt,
               double *tset_hlt, unsigned int *kleppen, maisch_schedule ms[],
               sparge_struct *sps, std_struct *std, int pid_on, int std_fx);
void   init_ma(ma *p, int N, double init_val);
double moving_average(ma *p, double x);
void   init_sample_delay(ma *p, int TD);
double sample_delay(ma *p, double x);
void   slope_limiter(const double lim, const double Told, double *Tnew);

#ifdef __cplusplus
};
#endif
#endif /* MISC_H */
