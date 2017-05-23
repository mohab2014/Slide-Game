//---------------------------------------------------------------------------

#ifndef fastestTimesH
#define fastestTimesH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TScoreForm : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *BeginnerTimeLabel;
        TLabel *AdvancedTimeLabel;
        TLabel *ConfirmedTimeLabel;
        TLabel *Label7;
        TLabel *Label8;
        TLabel *Label9;
        TLabel *BeginnerLabel;
        TLabel *AdvancedLabel;
        TLabel *ConfirmedLabel;
        TButton *Button1;
        TButton *ResetScoresButton;
        TMemo *ScoreMemo;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall ResetScoresButtonClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
        
public:		// User declarations
        __fastcall TScoreForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TScoreForm *ScoreForm;
//---------------------------------------------------------------------------
#endif
