//---------------------------------------------------------------------------
// This application is coded in c++ by Moh. Ahmed Awad ElKariem
// Faculty of Mathematical Sciences, Third year , in September 2001



#include <vcl.h>


#pragma hdrstop

#include <stdlib.h>
#include <IniFiles.hpp>
#include <memory>
#include "slide.h"
#include "About.h"
#include "readme.h"
#include "fastestTimes.h"
#include "Congratulations.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSliderForm *SliderForm;
bool Puzzle1514;
bool Pause = false;

//------------------------------------------------------------------------------
__fastcall TSliderForm::TSliderForm(TComponent* Owner)
        : TForm(Owner)
{
}

//------------------------------------------------------------------------------

void __fastcall TSliderForm::SetSquare(int x,int y,int status)
{

     int   xl,xr,yt,yb;

     xl = fxpos + XPX * x;
     xr = xl + XPX - 1  ;
     yt = fypos + YPX * y;
     yb = yt + YPX - 1   ;

     if(Value(x,y) == lastNum)
     {
     Canvas->Pen->Color = clSilver;
     Canvas->Brush->Color = clBlack;
     Canvas->Rectangle(xl,yt,xr,yb);
     return;
     }

     Canvas->Brush->Color = clLtGray;
     Canvas->Pen->Color = clDkGray;
     Canvas->Rectangle(xl,yt,xr,yb);

     if(status)
     {
     Canvas->Pen->Color = clWhite;
     Canvas->MoveTo(xr - 1,yt);
     Canvas->LineTo(xl,yt);
     Canvas->LineTo(xl,yb - 1);

     Canvas->Pen->Color = clSilver;
     Canvas->MoveTo(xr,yt);
     Canvas->LineTo(xr,yb);
     Canvas->LineTo(xl,yb);
     }


}
//------------------------------------------------------------------------------
void __fastcall TSliderForm::DrawSquares()
{

        AnsiString num = "0";

        int  xl,yt;

        for(int x = 0; x < rows; x++)
                for(int y = 0; y < cols ; y++)
                {


                        SetSquare(x,y,1);
                        if(Value(x,y) >= lastNum)
                                continue;

                        Canvas->Font->Color = clBlack;
                        num = IntToStr(Value(x,y));

                        if(Value(x,y) < 10)
                                Canvas->TextOut(fxpos + XPX*x + 20,
                                fypos + YPX*y+10,num);
                        else
                                Canvas->TextOut(fxpos + XPX*x + 10,
                                fypos + YPX*y+10,num);

                }



}

//------------------------------------------------------------------------------
void __fastcall TSliderForm::SetNumbers(int maxNum)
{

        TSquare* p = square;
        int x,y;

        for (int i = rows * cols; i > 0 ; i--,p++)
        {
                p->value = 0;
                p->sqPress = false;

        }

        for(int num = 1; num <= lastNum ; num++)
        {


                do
                {
                 x = random(rows);
                 y = random(cols);
                }while(Value(x,y) != 0);

                Value(x,y) = num;

        }

}
//------------------------------------------------------------------------------

void __fastcall TSliderForm::Swap(int &x,int &y)
{
        int temp = x;
        x = y;
        y = temp;
}
//------------------------------------------------------------------------------
void __fastcall TSliderForm::FormCreate(TObject *Sender)
{


        TIniFile* IniFile = new TIniFile(ChangeFileExt(Application->ExeName,".INI"));
        Top = IniFile->ReadInteger("Form","Top",100);
        Left = IniFile->ReadInteger("Form","Left",100);
        /*BeginnerTime = IniFile->ReadInteger("Form","BeginnerTime",999);
        AdvancedTime = IniFile->ReadInteger("Form","AdvancedTime",999);
        ConfirmedTime = IniFile->ReadInteger("Form","ConfirmedTime",999);   */
        int lastNumFromFile = IniFile->ReadInteger("Form","lastNumFromFile",16);

        fxpos = 120;
        fypos = 50;

     /*   SizeMemo->Clear();
        SizeMemo->Lines->LoadFromFile("sliderSize.txt");

        AnsiString NumString = SizeMemo->Lines->GetText();

        int lastNumFromFile = NumString.ToInt();    */

        if(lastNumFromFile == 16)
        {
        rows = 4;
        cols = 4;
        }
        else if(lastNumFromFile == 20)
        {
        rows = 5;
        cols = 4;

        fxpos = 100;
        fypos = 50;

        }
        else if(lastNumFromFile == 24)
        {
        rows = 6;
        cols = 4;

        fxpos = 80;
        fypos = 50;
        }
        else    //if(lastNumFromFile == 9) OR ANY NUMBER OTHER THA N THE ABOVE
        {
        rows = 3;
        cols = 3;
        }

        /*rows = DEFROWS;
        cols = DEFCOLS; */

        if(lastNumFromFile == 9 || lastNumFromFile == 16 ||
           lastNumFromFile == 20 || lastNumFromFile == 24)
                lastNum = lastNumFromFile;
        else
                lastNum = 9; // set 9 as the default slider

        square = new TSquare[rows * cols];

        randomize();
        SetNumbers(lastNum);
        Puzzle1514 = false;

        Timer1->Enabled = false;

        Application->OnMinimize = StopTimer;
        Application->OnRestore = RestartTimer;

        delete IniFile;

}
//------------------------------------------------------------------------------
void __fastcall TSliderForm::FormPaint(TObject *Sender)
{
        DrawSquares();
}
//------------------------------------------------------------------------------


void __fastcall TSliderForm::FormMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{



        if((FormLabel->Caption == "    WINNER !!!") || (FormLabel->Caption == "    Game Over !!!"))
                return;
        if(Timer1->Tag == 0)
                Timer1->Enabled = true;

        if(Pause == true)
                Timer1->Enabled = true;

        if(X < fxpos || Y < fypos)
                return;


        int x = (X - fxpos)/XPX;
        int y = (Y - fypos)/YPX;

        if(x < 0 || x >= rows || y < 0 || y >= cols)
                return;

        if(Value(x,y) >= lastNum)
                return;


        if(!IsPress(x,y) && Shift.Contains(ssLeft))
        {

                IsPress(x,y) = true;
                SetSquare(x,y,0);

                AnsiString num = IntToStr(Value(x,y));

                if(Value(x,y) < 10)
                                Canvas->TextOut(fxpos + XPX*x + 20,
                                fypos + YPX*y+10,num);
                else
                                Canvas->TextOut(fxpos + XPX*x + 10,
                                fypos + YPX*y+10,num);



                PRESSEDX = x;
                PRESSEDY = y;

        }


}
//------------------------------------------------------------------------------

void __fastcall TSliderForm::FormMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{




        int x = (X - fxpos)/XPX;
        int y = (Y - fypos)/YPX;

        if(x < 0 || x >= rows || y < 0 || y >= cols)
                return;


         if(x != PRESSEDX || y != PRESSEDY)
        {

                IsPress(PRESSEDX,PRESSEDY) = false;
                DrawSquares();

        }

       if(X < fxpos || Y < fypos)  // Check boundaries
               return;


        int emptyX,emptyY;

                for(int i = 0; i < rows ; i++)
                        for(int j = 0;j < cols; j++)
                        {
                                if(Value(i,j) == lastNum)
                                {
                                emptyX = i;
                                emptyY = j;
                                break;
                                }

                        }


            if(IsPress(x,y) )
            {

                if(x == emptyX && y == emptyY-1 )
                {
                 Swap(Value(x,y),Value(x,y+1));
                 DrawSquares();
                }

                else if(x == emptyX && y == emptyY+1)
                {
                Swap(Value(x,y),Value(x,y-1));
                DrawSquares();
                }

                else if(x == emptyX + 1 && y == emptyY)
                {
                Swap(Value(x,y),Value(x-1,y));
                DrawSquares();
                }
                else if(x == emptyX - 1 && y == emptyY)
                {
                Swap(Value(x,y),Value(x+1,y));
                DrawSquares();
                }
                else if(x == emptyX && y == emptyY-2)
                {
                Swap(Value(x,y),Value(x,y+1));
                Swap(Value(x,y),Value(x,y+2));
                DrawSquares();
                }
                else if(x == emptyX && y == emptyY-3)
                {
                Swap(Value(x,y),Value(x,y+1));
                Swap(Value(x,y),Value(x,y+2));
                Swap(Value(x,y),Value(x,y+3));
                DrawSquares();
                }

                else if(x == emptyX && y == emptyY-4)
                {
                Swap(Value(x,y),Value(x,y+1));
                Swap(Value(x,y),Value(x,y+2));
                Swap(Value(x,y),Value(x,y+3));
                Swap(Value(x,y),Value(x,y+4));
                DrawSquares();
                }

                else if(x == emptyX && y == emptyY-5)
                {
                Swap(Value(x,y),Value(x,y+1));
                Swap(Value(x,y),Value(x,y+2));
                Swap(Value(x,y),Value(x,y+3));
                Swap(Value(x,y),Value(x,y+4));
                Swap(Value(x,y),Value(x,y+5));
                DrawSquares();
                }

                else if(x == emptyX-2 && y == emptyY)
                {
                Swap(Value(x,y),Value(x+1,y));
                Swap(Value(x,y),Value(x+2,y));
                DrawSquares();
                }
                else if(x == emptyX-3 && y == emptyY)
                {
                Swap(Value(x,y),Value(x+1,y));
                Swap(Value(x,y),Value(x+2,y));
                Swap(Value(x,y),Value(x+3,y));
                DrawSquares();
                }

                else if(x == emptyX-4 && y == emptyY)
                {
                Swap(Value(x,y),Value(x+1,y));
                Swap(Value(x,y),Value(x+2,y));
                Swap(Value(x,y),Value(x+3,y));
                Swap(Value(x,y),Value(x+4,y));
                DrawSquares();
                }

                else if(x == emptyX-5 && y == emptyY)
                {
                Swap(Value(x,y),Value(x+1,y));
                Swap(Value(x,y),Value(x+2,y));
                Swap(Value(x,y),Value(x+3,y));
                Swap(Value(x,y),Value(x+4,y));
                Swap(Value(x,y),Value(x+5,y));
                DrawSquares();
                }
                else if(x == emptyX+2 && y == emptyY)
                {
                Swap(Value(x,y),Value(x-1,y));
                Swap(Value(x,y),Value(x-2,y));
                DrawSquares();
                }
                else if(x == emptyX+3 && y == emptyY)
                {
                Swap(Value(x,y),Value(x-1,y));
                Swap(Value(x,y),Value(x-2,y));
                Swap(Value(x,y),Value(x-3,y));
                DrawSquares();
                }
                else if(x == emptyX+4 && y == emptyY)
                {
                Swap(Value(x,y),Value(x-1,y));
                Swap(Value(x,y),Value(x-2,y));
                Swap(Value(x,y),Value(x-3,y));
                Swap(Value(x,y),Value(x-4,y));
                DrawSquares();
                }
                else if(x == emptyX+5 && y == emptyY)
                {
                Swap(Value(x,y),Value(x-1,y));
                Swap(Value(x,y),Value(x-2,y));
                Swap(Value(x,y),Value(x-3,y));
                Swap(Value(x,y),Value(x-4,y));
                Swap(Value(x,y),Value(x-5,y));
                DrawSquares();
                }
                else if(x == emptyX && y == emptyY+2)
                {
                Swap(Value(x,y),Value(x,y-1));
                Swap(Value(x,y),Value(x,y-2));
                DrawSquares();
                }
                else if(x == emptyX && y == emptyY+3)
                {
                Swap(Value(x,y),Value(x,y-1));
                Swap(Value(x,y),Value(x,y-2));
                Swap(Value(x,y),Value(x,y-3));
                DrawSquares();
                }
                else if(x == emptyX && y == emptyY+4)
                {
                Swap(Value(x,y),Value(x,y-1));
                Swap(Value(x,y),Value(x,y-2));
                Swap(Value(x,y),Value(x,y-3));
                Swap(Value(x,y),Value(x,y-4));
                DrawSquares();
                }
                else if(x == emptyX && y == emptyY+5)
                {
                Swap(Value(x,y),Value(x,y-1));
                Swap(Value(x,y),Value(x,y-2));
                Swap(Value(x,y),Value(x,y-3));
                Swap(Value(x,y),Value(x,y-4));
                Swap(Value(x,y),Value(x,y-5));
                DrawSquares();
                }

                else
                DrawSquares();
             }
        IsPress(x,y) = false;

}
//------------------------------------------------------------------------------

void __fastcall TSliderForm::FormDestroy(TObject *Sender)
{
        delete square;
        square = 0;
  
}

//------------------------------------------------------------------------------
void __fastcall TSliderForm::Puzzle15Click(TObject *Sender)
{

        fxpos = 120;
        fypos = 50;

        rows = DEFROWS;
        cols = DEFCOLS;
        lastNum = 16;


        if(square)
                delete square;

        square = new TSquare[rows*cols];

        randomize();
        SetNumbers(lastNum);
        Repaint();
        Puzzle1514 = false;

        Timer1->Tag = 0;
        TimeLabel->Caption = 0;
        Timer1->Enabled = false;
        FormLabel->Caption = "Click a tile to slide it";




}
//---------------------------------------------------------------------------

void __fastcall TSliderForm::Exit1Click(TObject *Sender)
{
        Close();
}
//---------------------------------------------------------------------------

void __fastcall TSliderForm::Puzzle1415Click(TObject *Sender)
{

        fxpos = 144;
        fypos = 50;

        rows = DEFROWS;
        cols = DEFCOLS;
        lastNum = 16;

        if(square)
                delete square;

        square = new TSquare[rows*cols];

        Value(0,0) = lastNum;
        Value(1,0) = 1;
        Value(2,0) = 2;
        Value(3,0) = 3;
        Value(0,1) = 4;
        Value(1,1) = 5;
        Value(2,1) = 6;
        Value(3,1) = 7;
        Value(0,2) = 8;
        Value(1,2) = 9;
        Value(2,2) = 10;
        Value(3,2) = 11;
        Value(0,3) = 12;
        Value(1,3) = 13;
        Value(3,3) = 14;
        Value(2,3) = 15;

        Repaint();
        Puzzle1514 = true;

        Timer1->Tag = 0;
        TimeLabel->Caption = 0;
        Timer1->Enabled = false;
        FormLabel->Caption = "Click a tile to slide it";

}
//---------------------------------------------------------------------------


void __fastcall TSliderForm::Puzzle8Click(TObject *Sender)
{

        fxpos = 150;
        fypos = 50;

        rows = 3;
        cols = 3;

        lastNum = 9;

        if(square)
                delete square;

        square = new TSquare[rows*cols];


        randomize();
        SetNumbers(lastNum);
        Repaint();
        Puzzle1514 = false;

        Timer1->Tag = 0;
        TimeLabel->Caption = 0;
        Timer1->Enabled = false;
        FormLabel->Caption = "Click a tile to slide it";

}
//---------------------------------------------------------------------------

void __fastcall TSliderForm::About1Click(TObject *Sender)
{
        std::auto_ptr<TAboutSlider> AboutSlider(new TAboutSlider(0));

        AboutSlider->ShowModal();
}
//---------------------------------------------------------------------------



void __fastcall TSliderForm::New1Click(TObject *Sender)
{
        NewGameButtonClick(0);
}
//---------------------------------------------------------------------------

void __fastcall TSliderForm::Timer1Timer(TObject *Sender)
{


        if(FormLabel->Caption == "    WINNER !!!")
                return;

        if(Timer1->Tag == 998)
        {
                StopTimer(0);
                FormLabel->Caption = "    Game Over !!!";
        }



        if(CheckSlider())
        {
                StopTimer(0);
                FormLabel->Caption = "    WINNER !!!";

                AnsiString Time = TimeLabel->Caption;
                SizeMemo->Lines->Text = Time;

               /*

                if(lastNum == 16 && !Puzzle1514)
                {
                ScoreForm->ScoreMemo->Lines->LoadFromFile("begginer.txt");
                if(Time.ToInt() >= ScoreForm->ScoreMemo->Lines->Text.ToInt())
                        return;
                }
                else if(lastNum == 20)
                {
                ScoreForm->ScoreMemo->Lines->LoadFromFile("Advanced.txt");
                if(Time.ToInt() >= ScoreForm->ScoreMemo->Lines->Text.ToInt())
                        return;
                }
                else if(lastNum == 24)
                {
                ScoreForm->ScoreMemo->Lines->LoadFromFile("Confirmed.txt");
                if(Time.ToInt() >= ScoreForm->ScoreMemo->Lines->Text.ToInt())
                        return;
                }

                if(lastNum != 9)
                {
                CongratulationForm->ShowModal();
                ScoreForm->ScoreMemo->Lines->Text = CongratulationForm->NameEdit->Text;
                }


                if(lastNum == 16 && !Puzzle1514)
                {
                        SizeMemo->Lines->SaveToFile("begginer.txt");
                        ScoreForm->ScoreMemo->Lines->SaveToFile("begginerName.txt");
                }
                else if(lastNum == 20)
                {
                        SizeMemo->Lines->SaveToFile("Advanced.txt");
                        ScoreForm->ScoreMemo->Lines->SaveToFile("AdvancedName.txt");
                }
                else if(lastNum == 24)
                {
                        SizeMemo->Lines->SaveToFile("Confirmed.txt");
                        ScoreForm->ScoreMemo->Lines->SaveToFile("ConfirmedName.txt");
                }
             */

              if(lastNum == 16 && !Puzzle1514)
                {
                ScoreForm->ScoreMemo->Lines->LoadFromFile("Times.txt");
                if(Time.ToInt() >= ScoreForm->BeginnerTimeLabel->Caption.ToInt())
                        return;
                }
                else if(lastNum == 20)
                {
                ScoreForm->ScoreMemo->Lines->LoadFromFile("Times.txt");
                if(Time.ToInt() >= ScoreForm->AdvancedTimeLabel->Caption.ToInt())
                        return;
                }
                else if(lastNum == 24)
                {
                ScoreForm->ScoreMemo->Lines->LoadFromFile("Times.txt");
                if(Time.ToInt() >= ScoreForm->ConfirmedTimeLabel->Caption.ToInt())
                        return;
                }

                if(lastNum != 9)
                {
                CongratulationForm->ShowModal();
                ScoreForm->ScoreMemo->Lines->Text = CongratulationForm->NameEdit->Text;
                }

                AnsiString Name = ScoreForm->ScoreMemo->Lines->Text;

                if(lastNum == 16 && !Puzzle1514)
                {
                        TIniFile* IniFile = new TIniFile(ChangeFileExt(Application->ExeName,".INI"));
                        IniFile->WriteInteger("Form","BeginnerTime",StrToInt(Time));
                        IniFile->WriteString("Form","BeginnerLabel",Name);

                        SizeMemo->Lines->Text = Time + ',' + ScoreForm->AdvancedTimeLabel->Caption + ','
                                                     + ScoreForm->ConfirmedTimeLabel->Caption;
                        SizeMemo->Lines->SaveToFile("Times.txt");

                        SizeMemo->Lines->Text = Name + ',' + ScoreForm->AdvancedLabel->Caption + ','
                                                + ScoreForm->ConfirmedLabel->Caption;

                        SizeMemo->Lines->SaveToFile("Names.txt");

                        delete IniFile;
                }
                else if(lastNum == 20)
                {
                        TIniFile* IniFile = new TIniFile(ChangeFileExt(Application->ExeName,".INI"));
                        IniFile->WriteInteger("Form","AdvancedTime",StrToInt(Time));
                        IniFile->WriteString("Form","AdvancedLabel",Name);

                        SizeMemo->Lines->Text = ScoreForm->BeginnerTimeLabel->Caption + ',' + Time + ','
                                                     + ScoreForm->ConfirmedTimeLabel->Caption;
                        SizeMemo->Lines->SaveToFile("Times.txt");

                        SizeMemo->Lines->Text =
                        ScoreForm->BeginnerLabel->Caption + ',' + Name + ','
                                                + ScoreForm->ConfirmedLabel->Caption;

                        SizeMemo->Lines->SaveToFile("Names.txt");
                        delete IniFile;
                }
                else if(lastNum == 24)
                {
                        TIniFile* IniFile = new TIniFile(ChangeFileExt(Application->ExeName,".INI"));
                        IniFile->WriteInteger("Form","ConfirmedTime",StrToInt(Time));
                        IniFile->WriteString("Form","ConfirmedLabel",Name);
                        SizeMemo->Lines->Text = ScoreForm->BeginnerTimeLabel->Caption + ','
                                                + ScoreForm->AdvancedTimeLabel->Caption + ',' + Time;

                        SizeMemo->Lines->SaveToFile("Times.txt");

                        SizeMemo->Lines->Text = ScoreForm->BeginnerLabel->Caption + ','
                                                 + ScoreForm->AdvancedLabel->Caption + ','
                                                 + Name;

                        SizeMemo->Lines->SaveToFile("Names.txt");
                        delete IniFile;
                }

        }
        else
        {
        Timer1->Tag++;
        TimeLabel->Caption = Timer1->Tag;
        }


}
//---------------------------------------------------------------------------
void __fastcall TSliderForm::StopTimer(TObject *Sender)
{

        Timer1->Enabled = false;

}
//------------------------------------------------------------------------------

void __fastcall TSliderForm::RestartTimer(TObject *Sender)
{
        if(!Pause)
        Timer1->Enabled = true;
}

//-------------------------------------------------------------------------------

bool __fastcall TSliderForm::CheckSlider()
{

int counter = 1;
        for(int y = 0; y < cols ; y++)
                for(int x = 0; x < rows ; x++,counter++)
                {
                        if(Value(x,y) !=  counter)
                                return false;
                }

        return true;

}
//------------------------------------------------------------------------------


void __fastcall TSliderForm::NewGameButtonClick(TObject *Sender)
{



        if(Puzzle1514)
                Puzzle1415Click(NULL);
        else
        {
        randomize();
        SetNumbers(lastNum);
        DrawSquares();
        }

        Timer1->Tag = 0;
        TimeLabel->Caption = 0;
        Timer1->Enabled = false;

        FormLabel->Caption = "Click a tile to slide it";


}

//---------------------------------------------------------------------------

void __fastcall TSliderForm::CloseButtonClick(TObject *Sender)
{
       /* SizeMemo->Clear();
        SizeMemo->Lines->Text = AnsiString(lastNum);
        SizeMemo->Lines->SaveToFile("sliderSize.txt");   */
        Close();
}
//---------------------------------------------------------------------------


void __fastcall TSliderForm::Readme1Click(TObject *Sender)
{
        ReadmeForm->Show();

}
//---------------------------------------------------------------------------

void __fastcall TSliderForm::Advanced1Click(TObject *Sender)
{

        fxpos = 100;
        fypos = 50;

        rows = 5;
        cols = 4;

        lastNum = 20;

        if(square)
                delete square;

        square = new TSquare[rows*cols];


        randomize();
        SetNumbers(lastNum);
        Repaint();
        Puzzle1514 = false;

        Timer1->Tag = 0;
        TimeLabel->Caption = 0;
        Timer1->Enabled = false;
        FormLabel->Caption = "Click a tile to slide it";

}
//---------------------------------------------------------------------------

void __fastcall TSliderForm::Begginer1Click(TObject *Sender)
{
        fxpos = 120;
        fypos = 50;

        rows = DEFROWS;
        cols = DEFCOLS;
        lastNum = 16;


        if(square)
                delete square;

        square = new TSquare[rows*cols];

        randomize();
        SetNumbers(lastNum);
        Repaint();
        Puzzle1514 = false;

        Timer1->Tag = 0;
        TimeLabel->Caption = 0;
        Timer1->Enabled = false;
        FormLabel->Caption = "Click a tile to slide it";

}
//---------------------------------------------------------------------------

void __fastcall TSliderForm::Confirmed1Click(TObject *Sender)
{
        fxpos = 80;
        fypos = 50;

        rows = 6;
        cols = 4;

        lastNum = 24;

        if(square)
                delete square;

        square = new TSquare[rows*cols];


        randomize();
        SetNumbers(lastNum);
        Repaint();
        Puzzle1514 = false;

        Timer1->Tag = 0;
        TimeLabel->Caption = 0;
        Timer1->Enabled = false;
        FormLabel->Caption = "Click a tile to slide it";

}
//---------------------------------------------------------------------------


void __fastcall TSliderForm::Pause1Click(TObject *Sender)
{
        StopTimer(0);
        Pause = true;
}
//---------------------------------------------------------------------------


void __fastcall TSliderForm::Music1Click(TObject *Sender)
{
        if(Music1->Checked == false)
        {
                Music1->Checked = true;
                MediaPlayer1->Play();

        }
        else
        {
                Music1->Checked = false;
                MediaPlayer1->Stop();
        }

}
//---------------------------------------------------------------------------


void __fastcall TSliderForm::BestTimes1Click(TObject *Sender)
{
        ScoreForm->ShowModal();
}
//---------------------------------------------------------------------------



void __fastcall TSliderForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
        TIniFile* IniFile = new TIniFile(ChangeFileExt(Application->ExeName,".INI"));

        IniFile->WriteInteger("Form","Top",Top);
        IniFile->WriteInteger("Form","Left",Left);
        IniFile->WriteInteger("Form","lastNumFromFile",lastNum);

        delete IniFile;        
}
//---------------------------------------------------------------------------

