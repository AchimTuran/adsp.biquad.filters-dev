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



#include "BiQuadMessageBase.h"

CBiQuadMessageBase::CBiQuadMessageBase()
{
  m_ModeID = ADSP_MODE_ID_UNKNOWN;
  m_ChannelID = AE_DSP_CH_INVALID;
}

CBiQuadMessageBase::~CBiQuadMessageBase()
{
}


AE_DSP_CHANNEL CBiQuadMessageBase::get_AudioChannelID()
{
  return m_ChannelID;
}

AE_DSP_CHANNEL CBiQuadMessageBase::set_AudioChannelID(AE_DSP_CHANNEL ChannelID)
{
  if(ChannelID > AE_DSP_CH_INVALID && ChannelID < AE_DSP_CH_MAX)
  {
    m_ChannelID = ChannelID;
  }
  else
  {
    return AE_DSP_CH_INVALID;
  }

  return m_ChannelID;
}

adspProcessingModeIDs CBiQuadMessageBase::get_ModeID()
{
  return m_ModeID;
}

adspProcessingModeIDs CBiQuadMessageBase::set_ModeID(adspProcessingModeIDs ModeID)
{
  if(ModeID > ADSP_MODE_ID_UNKNOWN || ModeID < ADSP_MODE_ID_MAX)
  {
    m_ModeID = ModeID;
  }
  else
  {
    return ADSP_MODE_ID_UNKNOWN;
  }

  return m_ModeID;
}
