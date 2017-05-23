//---------------------------------------------------------------------------

#include <vcl.h>
#include <ctype>
#include <string>
#include <IniFiles.hpp>
#pragma hdrstop

#include "fastestTimes.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TScoreForm *ScoreForm;
//---------------------------------------------------------------------------
__fastcall TScoreForm::TScoreForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TScoreForm::Button1Click(TObject *Sender)
{
        Close();
}
//---------------------------------------------------------------------------
void __fastcall TScoreForm::ResetScoresButtonClick(TObject *Sender)
{

        ScoreMemo->Lines->Text = "999,999,999";
        ScoreMemo->Lines->SaveToFile("Times.txt");


        ScoreMemo->Lines->Text = "Anonymous,Anonymous,Anonymous";
        ScoreMemo->Lines->SaveToFile("Names.txt");



        BeginnerTimeLabel->Caption = "999";
        BeginnerLabel->Caption = "Anonymous";


        AdvancedTimeLabel->Caption = "999";
        AdvancedLabel->Caption = "Anonymous";


        ConfirmedTimeLabel->Caption = "999";
        ConfirmedLabel->Caption = "Anonymous";


}
//---------------------------------------------------------------------------

void __fastcall TScoreForm::FormCreate(TObject *Sender)
{



        TIniFile* IniFile = new TIniFile(ChangeFileExt(Application->ExeName,".INI"));
        BeginnerTimeLabel->Caption = IntToStr(IniFile->ReadInteger("Form","BeginnerTime",999));
        AdvancedTimeLabel->Caption = IntToStr(IniFile->ReadInteger("Form","AdvancedTime",999));
        ConfirmedTimeLabel->Caption = IntToStr(IniFile->ReadInteger("Form","ConfirmedTime",999));


        delete IniFile;
        /*ScoreMemo->Lines->LoadFromFile("Times.txt");

        AnsiString Times = ScoreMemo->Lines->GetText();

        AnsiString begTime;
        AnsiString advTime;
        AnsiString confTime;

        for(int i = 1; i <= Times.Length() ; i++)
        {
                if(Times[i] == ',')
                {
                // commaPos = i;
                begTime = Times.SubString(1,i-1);
                Times = Times.SubString(i+1,Times.Length());
                break;
                }
        }

        BeginnerTimeLabel->Caption = begTime;

        for(int i = 1; i <= Times.Length(); i++)
        {
                if(Times[i] == ',')
                {
                // commaPos = i;
                advTime = Times.SubString(1,i-1);
                Times = Times.SubString(i+1,Times.Length());
                confTime = Times;
                break;
                }
        }

        AdvancedTimeLabel->Caption = advTime;
        ConfirmedTimeLabel->Caption = confTime;  */

        /*ScoreMemo->Lines->LoadFromFile("Names.txt");

        AnsiString Names = ScoreMemo->Lines->GetText();

        AnsiString begName;
        AnsiString advName;
        AnsiString confName;


        for(int i = 1; i <= Names.Length() ; i++)
        {
                if(Names[i] == ',')
                {
                //int commaPos = i;
                begName = Names.SubString(1,i-1);
                Names = Names.SubString(i+1,Names.Length());
                break;
                }
        }

        BeginnerLabel->Caption = begName;

        for(int i = 1; i <= Names.Length(); i++)
        {
                if(Names[i] == ',')
                {
               // int commaPos = i;
                advName = Names.SubString(1,i-1);
                Names = Names.SubString(i+1,Names.Length());
                confName = Names;
                break;
                }
        }

        AdvancedLabel->Caption = advName;
        ConfirmedLabel->Caption = confName;    */

}
//---------------------------------------------------------------------------

