// ==========================================================================
// Filename    : $Id$
// Author      : E. van de Logt
// Purpose     : Provides a form where parameters for the I2C Bus related
//               settings can be modified.
// --------------------------------------------------------------------------
// $Log$
// Revision 1.5  2013/06/16 14:39:19  Emile
// Intermediate version for new Ebrew 2.0 USB hardware:
// - Hardware settings Dialog: COM Port + Settings added + LEDx removed
// - PortTalk + i2c_dll + Start_i2c_communication + Reset_I2C_Bus removed
// - New routines for COM-Port added
// - Generate_IO_Signals() now uses COM_port_write to address all hardware
// - This version works with new hardware: PUMP on/off + LEDs are working
// - HEATER led and PWM output do not work yet + TODO: add scheduler.
//
// Revision 1.4  2004/03/10 10:10:38  emile
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
// Revision 1.3  2003/09/15 20:37:21  emile
// - LM76 constants renamed in LM92 constants
// - Pump Popupmenu added (same as already done for the valves)
// - Added support for LED3 and LED4 displays
// - 'I2C settings' renamed into 'Hardware Settings'
// - Added more variables to LED1..LED4 selection. Now 6 variables to select
// - Added SET_LED macro
// - Added Triac Temperature protection functionality
//
// Revision 1.2  2002/12/30 13:33:44  emile
// - Headers with CVS tags added to every source file
// - Restore Settings function is added
// - "ebrew" registry key now in a define REGKEY
//
// ==========================================================================

//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "I2CSettingsDialog.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TI2C_Settings *I2C_Settings;
//---------------------------------------------------------------------------
__fastcall TI2C_Settings::TI2C_Settings(TComponent* Owner)
        : TForm(Owner)
{
   update_i2c_gui();
}
//---------------------------------------------------------------------------

#define IDH_HARDWARESETTINGS (0x10090)
void __fastcall TI2C_Settings::Help_ButtonClick(TObject *Sender)
{
   Application->HelpContext(IDH_HARDWARESETTINGS);
}

void __fastcall TI2C_Settings::update_i2c_gui(void)
{
   switch (System_Mode->ItemIndex)
   {
        case 0: // Modulating Gas-Burner (20 kHz PWM)
                S0_Lbl->Enabled   = true;
                S0L_Edit->Enabled = true;  S0U_Edit->Enabled = true;
                S0L_L1a->Enabled  = true;  S0L_L1b->Enabled  = true;
                S0U_L1a->Enabled  = true;  S0U_L1b->Enabled  = true;
                S1_Lbl->Enabled   = false;
                S1L_Edit->Enabled = false; S1U_Edit->Enabled = false;
                S1L_L1a->Enabled  = false; S1L_L1b->Enabled  = false;
                S1U_L1a->Enabled  = false; S1U_L1b->Enabled  = false;
                S2_Lbl->Enabled   = false;
                S2L_Edit->Enabled = false; S2U_Edit->Enabled = false;
                S2L_L1a->Enabled  = false; S2L_L1b->Enabled  = false;
                S2U_L1a->Enabled  = false; S2U_L1b->Enabled  = false;
                break;
        case 1: // Non-Modulating Gas-Burner (Relay, On/Off)
                S0_Lbl->Enabled   = false;
                S0L_Edit->Enabled = false; S0U_Edit->Enabled = false;
                S0L_L1a->Enabled  = false; S0L_L1b->Enabled  = false;
                S0U_L1a->Enabled  = false; S0U_L1b->Enabled  = false;
                S1_Lbl->Enabled   = true;
                S1L_Edit->Enabled = true;  S1U_Edit->Enabled = true;
                S1L_L1a->Enabled  = true;  S1L_L1b->Enabled  = true;
                S1U_L1a->Enabled  = true;  S1U_L1b->Enabled  = true;
                S2_Lbl->Enabled   = false;
                S2L_Edit->Enabled = false; S2U_Edit->Enabled = false;
                S2L_L1a->Enabled  = false; S2L_L1b->Enabled  = false;
                S2U_L1a->Enabled  = false; S2U_L1b->Enabled  = false;
                break;
        case 2: // Electrical Heating Element (Triac, T=5 sec.)
                S0_Lbl->Enabled   = false;
                S0L_Edit->Enabled = false; S0U_Edit->Enabled = false;
                S0L_L1a->Enabled  = false; S0L_L1b->Enabled  = false;
                S0U_L1a->Enabled  = false; S0U_L1b->Enabled  = false;
                S1_Lbl->Enabled   = false;
                S1L_Edit->Enabled = false; S1U_Edit->Enabled = false;
                S1L_L1a->Enabled  = false; S1L_L1b->Enabled  = false;
                S1U_L1a->Enabled  = false; S1U_L1b->Enabled  = false;
                S2_Lbl->Enabled   = true;
                S2L_Edit->Enabled = true;  S2U_Edit->Enabled = true;
                S2L_L1a->Enabled  = true;  S2L_L1b->Enabled  = true;
                S2U_L1a->Enabled  = true;  S2U_L1b->Enabled  = true;
                break;
   } // switch
} // update_i2c_gui()

//---------------------------------------------------------------------------
void __fastcall TI2C_Settings::System_ModeExit(TObject *Sender)
{
   update_i2c_gui();
} // System_ModeExit()
//---------------------------------------------------------------------------

