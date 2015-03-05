#include "GUIDialogPostProcess.h"

#define BUTTON_CANCEL   10050
#define BUTTON_OK       10051
#define BUTTON_DEFAULT  10052


CGUIDialogPostProcess::CGUIDialogPostProcess() :
	CGUIDialogBase(	"DialogParametricEQ.xml", false, true )
{
}

CGUIDialogPostProcess::~CGUIDialogPostProcess()
{
}

bool CGUIDialogPostProcess::OnInit()
{
	return true;
}

bool CGUIDialogPostProcess::OnClick(int controlId)
{
	return true;
}

bool CGUIDialogPostProcess::OnFocus(int controlId)
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
    default:
    break;
  }
return true;
}

bool CGUIDialogPostProcess::OnAction(int actionId)
{
  if(actionId == ADDON_ACTION_CLOSE_DIALOG ||
     actionId == ADDON_ACTION_PREVIOUS_MENU)
  {
    return OnClick(BUTTON_CANCEL);
  }
  else
  {
    return false;
  }
}