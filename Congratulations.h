//---------------------------------------------------------------------------

#ifndef CongratulationsH
#define CongratulationsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TCongratulationForm : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TLabel *Label2;
        TEdit *NameEdit;
        TButton *Button1;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall NameEditEnter(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TCongratulationForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TCongratulationForm *CongratulationForm;
//---------------------------------------------------------------------------
#endif
