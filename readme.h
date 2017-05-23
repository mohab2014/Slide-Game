//---------------------------------------------------------------------------

#ifndef readmeH
#define readmeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TReadmeForm : public TForm
{
__published:	// IDE-managed Components
        TMemo *ReadmeMemo;
        void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TReadmeForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TReadmeForm *ReadmeForm;
//---------------------------------------------------------------------------
#endif
