//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("Slider.res");
USEFORM("slide.cpp", SliderForm);
USEFORM("readme.cpp", ReadmeForm);
USEFORM("About.cpp", AboutSlider);
USEFORM("fastestTimes.cpp", ScoreForm);
USEFORM("Congratulations.cpp", CongratulationForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TSliderForm), &SliderForm);
                 Application->CreateForm(__classid(TReadmeForm), &ReadmeForm);
                 Application->CreateForm(__classid(TScoreForm), &ScoreForm);
                 Application->CreateForm(__classid(TCongratulationForm), &CongratulationForm);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
