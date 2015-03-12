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
 *  along with XBMC; see the file COPYING.  If not, write to
 *  the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 *  http://www.gnu.org/copyleft/gpl.html
 *
 */



#include "BiQuadManagerMessage.h"

CBiQuadManagerMessage::CBiQuadManagerMessage()
{
  m_MessageType = BIQUAD_MANAGER_MESSAGE_UNKNOWN;
  set_ModeID(ADSP_MODE_ID_UNKNOWN);
  set_AudioChannelID(AE_DSP_CH_INVALID);
}

CBiQuadManagerMessage::~CBiQuadManagerMessage()
{
}


CBiQuadManagerMessage::BIQUAD_MANAGER_MESSAGE CBiQuadManagerMessage::get_MessageType()
{
  return m_MessageType;
}

CBiQuadManagerMessage::BIQUAD_MANAGER_MESSAGE CBiQuadManagerMessage::set_MessageType(BIQUAD_MANAGER_MESSAGE MessageType)
{
  if(MessageType > BIQUAD_MANAGER_MESSAGE_UNKNOWN && MessageType < BIQUAD_MANAGER_MESSAGE_MAX)
  {
    m_MessageType = MessageType;
  }
  else
  {
    return BIQUAD_MANAGER_MESSAGE_UNKNOWN;
  }

  return m_MessageType;
}
