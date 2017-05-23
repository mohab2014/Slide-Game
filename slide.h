//---------------------------------------------------------------------------

#ifndef slideH
#define slideH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <MPlayer.hpp>
//---------------------------------------------------------------------------

struct TSquare
{
        int value;        // Number of square
        bool sqPress;    // square: is pressed

}*square;

class TSliderForm : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu1;
        TMenuItem *Game1;
        TMenuItem *Help1;
        TMenuItem *Puzzle1415;
        TMenuItem *Puzzle8;
        TMenuItem *About1;
        TMenuItem *Exit1;
        TMenuItem *New1;
        TMenuItem *N1;
        TLabel *FormLabel;
        TLabel *label;
        TLabel *TimeLabel;
        TTimer *Timer1;
        TSpeedButton *NewGameButton;
        TSpeedButton *CloseButton;
        TMenuItem *Readme1;
        TMenuItem *N2;
        TMenuItem *Advanced1;
        TMenuItem *N4;
        TMenuItem *Begginer1;
        TMenuItem *Confirmed1;
        TMenuItem *N5;
        TMenuItem *Pause1;
        TMediaPlayer *MediaPlayer1;
        TMenuItem *Music1;
        TMemo *SizeMemo;
        TMenuItem *N3;
        TMenuItem *BestTimes1;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormPaint(TObject *Sender);
        void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall FormMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall Puzzle15Click(TObject *Sender);
        void __fastcall Exit1Click(TObject *Sender);
        void __fastcall Puzzle1415Click(TObject *Sender);
        void __fastcall Puzzle8Click(TObject *Sender);
        void __fastcall About1Click(TObject *Sender);
        void __fastcall New1Click(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall NewGameButtonClick(TObject *Sender);
        void __fastcall CloseButtonClick(TObject *Sender);
        void __fastcall Readme1Click(TObject *Sender);
        void __fastcall Advanced1Click(TObject *Sender);
        void __fastcall Begginer1Click(TObject *Sender);
        void __fastcall Confirmed1Click(TObject *Sender);
        void __fastcall Pause1Click(TObject *Sender);
        void __fastcall Music1Click(TObject *Sender);
        void __fastcall BestTimes1Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        
private:	// User declarations

        int fxpos,fypos,rows,cols,lastNum,PRESSEDX,PRESSEDY;
        
        void __fastcall SetNumbers(int maxNum);
        void __fastcall SetSquare(int x,int y,int status);
        void __fastcall DrawSquares();
        void __fastcall SlideTile(int x,int y);
        void __fastcall Swap(int &x,int &y);


        int& Value(int x,int y) { return  (square + x*cols + y)->value; }
        bool& IsPress(int x,int y) {return (square + x*cols + y)->sqPress; }


        void __fastcall StopTimer(TObject* Sender);
        void __fastcall RestartTimer(TObject* Sender);
        bool __fastcall CheckSlider();

public:		// User declarations
        __fastcall TSliderForm(TComponent* Owner);


};
//---------------------------------------------------------------------------
extern PACKAGE TSliderForm *SliderForm;
//---------------------------------------------------------------------------



const int XPX = 50;
const int YPX = 50;
const int DEFROWS = 4;
const int DEFCOLS = 4;


#endif
