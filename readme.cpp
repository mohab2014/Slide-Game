//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "readme.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TReadmeForm *ReadmeForm;
//---------------------------------------------------------------------------
__fastcall TReadmeForm::TReadmeForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TReadmeForm::FormCreate(TObject *Sender)
{
        ReadmeMemo->Lines->LoadFromFile("Readme.txt");        
}
//---------------------------------------------------------------------------

