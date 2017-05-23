//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Congratulations.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TCongratulationForm *CongratulationForm;
//---------------------------------------------------------------------------
__fastcall TCongratulationForm::TCongratulationForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TCongratulationForm::Button1Click(TObject *Sender)
{
        Close();
}
//---------------------------------------------------------------------------
void __fastcall TCongratulationForm::NameEditEnter(TObject *Sender)
{
        Close();        
}
//---------------------------------------------------------------------------

