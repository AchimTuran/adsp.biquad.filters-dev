/*
 *      Copyright (C) 2005-2014 Team XBMC
 *      http://xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */



#include "GUIDialogPostProcess.h"
#include "utils/stdStringUtils.h"
#include <math.h>
using namespace std;

#define BUTTON_CANCEL   10050
#define BUTTON_OK       10051
#define BUTTON_DEFAULT  10052
#define SLIDER_32Hz     8000
#define SLIDER_32Hz_LABEL 8001
#define SLIDER_32Hz_VALUE 8002

std::string float_dB_toString(float dB);

CGUIDialogPostProcess::CGUIDialogPostProcess() :
	CGUIDialogBase(	"DialogParametricEQ.xml", false, true )
{
  m_Slider32Hz = NULL;
  m_Gain32Hz = 0.0f;
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
  m_window->SetControlLabel(SLIDER_32Hz_VALUE, float_dB_toString(m_Gain32Hz).c_str());
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
      m_window->SetControlLabel(SLIDER_32Hz_VALUE, float_dB_toString(m_Gain32Hz).c_str());
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

std::string float_dB_toString(float dB)
{
  std::string str = toString(roundf(dB*10.0f)/10.0f);
  float val10 = ((int)fabsf(roundf(dB*10.0f)));
  int fraction = (int)(val10 - ((int)(val10/10.0f)*10.0f));

  if(fraction == 0 || dB == 0.0f)
  {
    str += ".0";
  }

  str += "dB";
  
  return str;
}
