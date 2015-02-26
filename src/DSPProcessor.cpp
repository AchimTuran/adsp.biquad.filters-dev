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


//! Example process class method implementations.
/*!
 * \file DSPProcessor.cpp
 * ToDo: detailed description!
 */
#include <string.h>

#include "DSPProcessor.h"
#include "template/ADSPHelpers.h"
using namespace asplib;

// set addon properties here
CDSPProcessor::CDSPProcessor()
{
  m_MaxFreqBands = 10;
  m_MaxProcessingChannels = 0;
  m_ChannelHandle = NULL;
}

// delete your buffers here
CDSPProcessor::~CDSPProcessor()
{
  if(m_ChannelHandle)
  {
    for(int ii = 0; ii < m_MaxProcessingChannels; ii++)
    {
      ASPLIB_ERR err = CBiQuadFactory::destroy_BiQuads(&m_ChannelHandle->BiQuadHandle);
      if(err != ASPLIB_ERR_NO_ERROR)
      {
        // ToDo: show some error message!
      }
    }
    delete[] m_ChannelHandle;
    m_ChannelHandle = NULL;
  } 
}

AE_DSP_ERROR CDSPProcessor::Create()
{
  m_MaxProcessingChannels = m_StreamSettings.iOutChannels;
  m_ChannelHandle = new ADSP_CHANNEL_HANDLE[m_MaxProcessingChannels];
  if(!m_ChannelHandle)
  {
    // ToDo: throw error message!
  }

  int lastChannelID = 0;
  for(int ii = 0; ii < m_MaxProcessingChannels; ii++)
  {
    // ToDo: add functions for opt modules and channel bypass!
    m_ChannelHandle[ii].BiQuadHandle = CBiQuadFactory::get_BiQuads(m_MaxFreqBands, m_StreamSettings.iProcessSamplerate, ASPLIB_OPT_NATIVE);
    if(!m_ChannelHandle[ii].BiQuadHandle)
    {
      // ToDo: throw some error message!
    }

    // set all gain values to 0dB
    CBiQuadFactory::set_constQPeakingParams(m_ChannelHandle[ii].BiQuadHandle, 0.0f);

    // map next channel to BiQuad Filter
    unsigned long tempChannelFlag = 1<<lastChannelID;
    m_ChannelHandle[ii].ChannelID = CADSPHelpers::GetNextChID(m_StreamSettings.iOutChannels,
                                                              CADSPHelpers::Translate_ChFlag_TO_ChID((AE_DSP_CHANNEL_PRESENT)tempChannelFlag));
    m_ChannelHandle[ii].ChannelFlag = CADSPHelpers::Translate_ChID_TO_ChFlag((AE_DSP_CHANNEL)m_ChannelHandle[ii].ChannelID);
    if(m_ChannelHandle[ii].ChannelID == AE_DSP_CH_INVALID)
    {
      // ToDo: throw some error message!
      // no next channel found!
    }
    lastChannelID = m_ChannelHandle[ii].ChannelID +1;
  }

  return AE_DSP_ERROR_NO_ERROR;
}

unsigned int CDSPProcessor::PostProcess(unsigned int Mode_id, float **Array_in, float **Array_out, unsigned int Samples)
{
  for(int ii = 0; ii < m_MaxProcessingChannels; ii++)
  {
    ASPLIB_ERR err = CBiQuadFactory::calc_BiQuadSamples(m_ChannelHandle[ii].BiQuadHandle,
                                                        Array_in[m_ChannelHandle[ii].ChannelID],
                                                        Array_out[m_ChannelHandle[ii].ChannelID],
                                                        Samples);
    if(err != ASPLIB_ERR_NO_ERROR)
    {
      // ToDo: throw some error message!
      return 0;
    }
  }

  return Samples;
}
