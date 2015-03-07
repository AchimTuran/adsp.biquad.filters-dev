#include "GUIDialogPostProcess.h"
#include <string.h>
#include <iostream>
#include <string>
#include <sstream>

#define BUTTON_CANCEL   10050
#define BUTTON_OK       10051
#define BUTTON_DEFAULT  10052
#define SLIDER_32Hz     8000
#define SLIDER_32Hz_LABEL 8001
#define SLIDER_32Hz_VALUE 8002

std::string floatToString(float Value);

CGUIDialogPostProcess::CGUIDialogPostProcess() :
	CGUIDialogBase(	"DialogParametricEQ.xml", false, true )
{
  m_Slider32Hz = NULL;
}

CGUIDialogPostProcess::~CGUIDialogPostProcess()
{
}

bool CGUIDialogPostProcess::OnInit()
{
  m_Slider32Hz = GUI->Control_getSlider(m_window, SLIDER_32Hz);
  m_Slider32Hz->SetFloatRange(-24.0f, 24.f);
  m_Slider32Hz->SetFloatInterval(2.0f);
  m_Slider32Hz->SetFloatValue(0.0f);
  m_window->SetControlLabel(SLIDER_32Hz_LABEL, "32Hz");
  m_window->SetControlLabel(SLIDER_32Hz_VALUE, std::string(floatToString(m_Gain32Hz) + "dB").c_str());
	return true;
}

bool CGUIDialogPostProcess::OnClick(int controlId)
{
  switch(controlId)
  {
    case BUTTON_CANCEL:
    {
      this->Close();
    }
    break;
  
    case BUTTON_OK:
    {
      this->Close();
      //GUI->Control_releaseSpin(m_spinSpeakerGainTest);
      //GUI->Control_releaseRadioButton(m_radioSpeakerContinuesTest);  
    }
    break;

    case SLIDER_32Hz:
      m_Gain32Hz = m_Slider32Hz->GetFloatValue();
      m_window->SetControlLabel(SLIDER_32Hz_VALUE, std::string(floatToString(m_Gain32Hz) + "dB").c_str());
    break;

    default:
    break;
  }

	return true;
}

bool CGUIDialogPostProcess::OnFocus(int controlId)
{
  return true;
}

bool CGUIDialogPostProcess::OnAction(int actionId)
{
  if(actionId == ADDON_ACTION_CLOSE_DIALOG ||
     actionId == ADDON_ACTION_PREVIOUS_MENU ||
     actionId == ADDON_ACTION_NAV_BACK)
  {
    return OnClick(BUTTON_CANCEL);
  }
  else
  {
    return false;
  }
}

void CGUIDialogPostProcess::OnClose()
{
  if(m_Slider32Hz)
  {
    GUI->Control_releaseSlider(m_Slider32Hz);
  }
}

std::string floatToString(float Value)
{
  std::ostringstream ss;
  ss << (float)((int)(10.0f*Value + 0.5f))/10.0f;
  std::string str(ss.str());
  return str;
}

//template <typename T> string tostr(const T& t)
//{
//  ostringstream os;
//  os<<t;
//  return os.str();
//}
//double x = 14.4;
//int y = 21;
//
//string sx = tostr(x);
//string sy = tostr(y);