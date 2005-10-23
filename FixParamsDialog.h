// ==========================================================================
// Filename    : $Id$
// Author      : E. van de Logt
// Purpose     : Provides a form where various parameters can be manually
//               (fixed) to a particular value.
// --------------------------------------------------------------------------
// $Log$
// Revision 1.7  2004/05/08 14:52:50  emile
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
// Revision 1.6  2004/03/10 10:10:38  emile
// - Reduced complexity of several routines:
//   - T50msecTimer split, new routine Generate_IO_Signals added
//   - PopupMenu1Popup now uses (new) macro SET_POPUPMENU
//   - Reset_I2C_Bus now included in SET_LED macro
// - Every I2C write action now in a separate time-slice to avoid
//   I2C bus errors if fscl is low
// - This is the first version where the help file function is enabled
//   - All help buttons and F1 function key are operational
//   - Help file sources: ebrew.rtf and ebrew.hpj are added to CVS
// - ad1, ad2 and ad3 variables -> thlt, tmlt and ttriac (new variables)
//
// Revision 1.5  2003/06/01 19:36:34  emile
// - Switch/Fix added for Vmlt
//
// Revision 1.4  2003/06/01 14:08:06  emile
// - Same as previous log entry: CVS and BCB got confused => saved old files.
//
// Revision 1.3  2003/06/01 13:37:42  emile
// - Bugfix: switch/fix for Tmlt and Thlt were in wrong time-slice. Corrected.
// - Switch/fix for std state added for easier testing
// - Vmash value added to 'Options|Sparge & STD Settings' dialog screen.
//
// Revision 1.2  2002/12/30 13:33:44  emile
// - Headers with CVS tags added to every source file
// - Restore Settings function is added
// - "ebrew" registry key now in a define REGKEY
//
// ==========================================================================

//---------------------------------------------------------------------------
#ifndef FixParamsDialogH
#define FixParamsDialogH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Mask.hpp>
//---------------------------------------------------------------------------
class TFix_Params : public TForm
{
__published:	// IDE-managed Components
        TCheckBox *CB_Gamma;
        TCheckBox *CB_Tset;
        TMaskEdit *Gamma_MEdit;
        TMaskEdit *Tset_MEdit;
        TLabel *Gamma_Label;
        TLabel *Tset_Label;
        TButton *Button1;
        TButton *Button2;
        TButton *Help_Button;
        TLabel *Label1;
        TCheckBox *CB_Tad1;
        TMaskEdit *Tad1_MEdit;
        TLabel *Label2;
        TCheckBox *CB_Tad2;
        TMaskEdit *Tad2_MEdit;
        TCheckBox *CB_std;
        TMaskEdit *STD_MEdit;
        TCheckBox *CB_vmlt;
        TMaskEdit *Vmlt_MEdit;
        TLabel *Label3;
        TButton *Apply_Button;
        TLabel *Label4;
        TCheckBox *CB_vhlt;
        TMaskEdit *Vhlt_MEdit;
        TLabel *Label5;
        TCheckBox *CB_ttriac;
        TMaskEdit *Ttriac_MEdit;
        TLabel *Label6;
        void __fastcall CB_GammaClick(TObject *Sender);
        void __fastcall CB_TsetClick(TObject *Sender);
        void __fastcall Gamma_MEditClick(TObject *Sender);
        void __fastcall Tset_MEditClick(TObject *Sender);
        void __fastcall CB_Tad1Click(TObject *Sender);
        void __fastcall Tad1_MEditClick(TObject *Sender);
        void __fastcall CB_Tad2Click(TObject *Sender);
        void __fastcall Tad2_MEditDblClick(TObject *Sender);
        void __fastcall CB_stdClick(TObject *Sender);
        void __fastcall STD_MEditClick(TObject *Sender);
        void __fastcall CB_vmltClick(TObject *Sender);
        void __fastcall Vmlt_MEditClick(TObject *Sender);
        void __fastcall Help_ButtonClick(TObject *Sender);
        void __fastcall Apply_ButtonClick(TObject *Sender);
        void __fastcall CB_vhltClick(TObject *Sender);
        void __fastcall Vhlt_MEditClick(TObject *Sender);
        void __fastcall CB_ttriacClick(TObject *Sender);
        void __fastcall Ttriac_MEditClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFix_Params(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFix_Params *Fix_Params;
//---------------------------------------------------------------------------
#endif
