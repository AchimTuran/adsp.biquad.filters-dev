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

#define BUTTON_OK             10050
#define BUTTON_CANCEL         10051
#define BUTTON_DEFAULT        10052
#define SLIDER_PREAMP         8000
#define SLIDER_PREAMP_LABEL   8100
#define SLIDER_PREAMP_VALUE   8200
#define SLIDER_32Hz           8001
#define SLIDER_32Hz_LABEL     8101
#define SLIDER_32Hz_VALUE     8201
#define SLIDER_64Hz           8002
#define SLIDER_64Hz_LABEL     8102
#define SLIDER_64Hz_VALUE     8202
#define SLIDER_125Hz          8003
#define SLIDER_125Hz_LABEL    8103
#define SLIDER_125Hz_VALUE    8203
#define SLIDER_250Hz          8004
#define SLIDER_250Hz_LABEL    8104
#define SLIDER_250Hz_VALUE    8204
#define SLIDER_500Hz          8005
#define SLIDER_500Hz_LABEL    8105
#define SLIDER_500Hz_VALUE    8205
#define SLIDER_1kHz           8006
#define SLIDER_1kHz_LABEL     8106
#define SLIDER_1kHz_VALUE     8206
#define SLIDER_2kHz           8007
#define SLIDER_2kHz_LABEL     8107
#define SLIDER_2kHz_VALUE     8207
#define SLIDER_4kHz           8008
#define SLIDER_4kHz_LABEL     8108
#define SLIDER_4kHz_VALUE     8208
#define SLIDER_8kHz           8009
#define SLIDER_8kHz_LABEL     8109
#define SLIDER_8kHz_VALUE     8209
#define SLIDER_16kHz          8010
#define SLIDER_16kHz_LABEL    8110
#define SLIDER_16kHz_VALUE    8210

std::string float_dB_toString(float dB);

CGUIDialogPostProcess::CGUIDialogPostProcess() :
	CGUIDialogBase(	"DialogParametricEQ.xml", false, true )
{
  for(int ii = 0; ii < MAX_FREQ_BANDS +1; ii++)
  {
    m_Sliders[ii] = NULL;
    m_Gains[ii] = 0.0f;
  }
}

CGUIDialogPostProcess::~CGUIDialogPostProcess()
{
}

bool CGUIDialogPostProcess::OnInit()
{
  for(int ii = 0; ii < MAX_FREQ_BANDS +1; ii++)
  {
    m_Sliders[ii] = GUI->Control_getSlider(m_window, SLIDER_PREAMP + ii);
    if(!m_Sliders[ii])
    {
      KODI->Log(ADDON::LOG_ERROR, "Slider with ID: %i not found!", ii);
      return false;
    }

    m_Sliders[ii]->SetFloatRange(-24.0f, 24.f);
    m_Sliders[ii]->SetFloatInterval(2.0f);
    m_Sliders[ii]->SetFloatValue(0.0f);
    m_window->SetControlLabel(SLIDER_PREAMP_LABEL + ii, KODI->GetLocalizedString(30150 + ii));
    m_window->SetControlLabel(SLIDER_PREAMP_VALUE + ii, float_dB_toString(m_Gains[ii]).c_str());
  }

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

    case SLIDER_PREAMP:
    case SLIDER_32Hz:
    case SLIDER_64Hz:
    case SLIDER_125Hz:
    case SLIDER_250Hz:
    case SLIDER_500Hz:
    case SLIDER_1kHz:
    case SLIDER_2kHz:
    case SLIDER_4kHz:
    case SLIDER_8kHz:
    case SLIDER_16kHz:
      m_Gains[controlId - SLIDER_PREAMP] = m_Sliders[controlId - SLIDER_PREAMP]->GetFloatValue();
      m_window->SetControlLabel(controlId + 200, float_dB_toString(m_Gains[controlId - SLIDER_PREAMP]).c_str());
    break;

    default:
      return false;
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
  for(int ii = 0; ii < MAX_FREQ_BANDS +1; ii++)
  {
    if(m_Sliders[ii])
    {
      GUI->Control_releaseSlider(m_Sliders[ii]);
      m_Sliders[ii] = NULL;
    }
  }
}

std::string float_dB_toString(float dB)
{
  std::string str = toString(roundf(dB*10.0f)/10.0f);
  float val10 = (float)((int)fabsf(roundf(dB*10.0f)));
  int fraction = (int)(val10 - ((int)(val10/10.0f)*10.0f));

  if(fraction == 0 || dB == 0.0f)
  {
    str += ".0";
  }

  str += "dB";
  
  return str;
}
