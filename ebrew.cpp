// ==========================================================================
// Filename    : $Id$
// Author      : E. van de Logt
// Purpose     : 
// --------------------------------------------------------------------------
// $Log$
// Revision 1.5  2004/03/10 10:10:39  emile
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
// Revision 1.4  2003/12/21 21:16:59  emile
// - Old About screen removed, replaced by Version Aware About box. This
//   new About screen shows the version number (and a nice picture!).
//
// Revision 1.3  2002/12/30 13:33:45  emile
// - Headers with CVS tags added to every source file
// - Restore Settings function is added
// - "ebrew" registry key now in a define REGKEY
//
// ==========================================================================

//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("ebrew.res");
USEFORM("Unit1.cpp", MainForm);
USEFORM("PID_Settings_Dialog.cpp", PID_Settings);
USEFORM("FixParamsDialog.cpp", Fix_Params);
USEFORM("I2CSettingsDialog.cpp", I2C_Settings);
USEUNIT("MISC.C");
USEUNIT("PID_REG.C");
USEFORM("EditMashScheme.cpp", EditMashSchemeDlg);
USEFORM("ViewMashProgressForm.cpp", ViewMashProgress);
USEFORM("DataGraphForm.cpp", ShowDataGraphs);
USEFORM("Sparge_Settings.cpp", SpargeSettings);
USEUNIT("i2c_dll\i2c_dll.cpp");
USEFORM("RestoreSettings.cpp", Restore_Program_Settings);
USEFORM("VersionAwareAbout.cpp", VersionAwareAbout);
USEFORM("MeasurementsDialog.cpp", Measurements);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "E-Brew!";
                 Application->HelpFile = "C:\\DATA\\ebrew\\win_app\\EBREW.HLP";
                 Application->CreateForm(__classid(TMainForm), &MainForm);
                 Application->CreateForm(__classid(TPID_Settings), &PID_Settings);
                 Application->CreateForm(__classid(TFix_Params), &Fix_Params);
                 Application->CreateForm(__classid(TI2C_Settings), &I2C_Settings);
                 Application->CreateForm(__classid(TEditMashSchemeDlg), &EditMashSchemeDlg);
                 Application->CreateForm(__classid(TViewMashProgress), &ViewMashProgress);
                 Application->CreateForm(__classid(TShowDataGraphs), &ShowDataGraphs);
                 Application->CreateForm(__classid(TSpargeSettings), &SpargeSettings);
                 Application->CreateForm(__classid(TRestore_Program_Settings), &Restore_Program_Settings);
                 Application->CreateForm(__classid(TVersionAwareAbout), &VersionAwareAbout);
                 Application->CreateForm(__classid(TMeasurements), &Measurements);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
