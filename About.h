//----------------------------------------------------------------------------
#ifndef AboutH
#define AboutH
//----------------------------------------------------------------------------
#include <vcl\System.hpp>
#include <vcl\Windows.hpp>
#include <vcl\SysUtils.hpp>
#include <vcl\Classes.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\ExtCtrls.hpp>
//----------------------------------------------------------------------------
class TAboutSlider : public TForm
{
__published:
	TPanel *Panel1;
	TLabel *ProductName;
	TButton *OKButton;
        TLabel *Comments;
private:
public:
	virtual __fastcall TAboutSlider(TComponent* AOwner);
};
//----------------------------------------------------------------------------
//extern PACKAGE TAboutSlider *AboutSlider;
//----------------------------------------------------------------------------
#endif    
