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
  m_BiQuads = NULL;
  m_TempBiQuad = NULL;
  m_PostGain = NULL;
  m_NewMessage = false;
  m_BiQuadCoefficientsMessage = NULL;
  m_BiQuadHandleMessage = NULL;
}

// delete your buffers here
CDSPProcessor::~CDSPProcessor()
{
  if(m_BiQuads)
  {
    for(int ii = 0; ii < m_MaxProcessingChannels; ii++)
    {
      ASPLIB_ERR err = CBiQuadFactory::destroy_BiQuads(&m_BiQuads->BiQuadHandle);
      if(err != ASPLIB_ERR_NO_ERROR)
      {
        // ToDo: show some error message!
      }
    }
    delete[] m_BiQuads;
    m_BiQuads = NULL;
  } 

  if(m_PostGain)
  {
    delete [] m_PostGain;
    m_PostGain = NULL;
  }
}

AE_DSP_ERROR CDSPProcessor::Create()
{
  m_MaxProcessingChannels = m_StreamSettings.iOutChannels;
  m_BiQuads = new ADSP_BiQuad[m_MaxProcessingChannels];
  if(!m_BiQuads)
  {
    // ToDo: throw error message!
  }

  m_PostGain = new float[m_MaxProcessingChannels];
  if(m_PostGain)
  {
    KODI->Log(ADDON::LOG_ERROR, "%s line %i: Post gain array not created! Not enough free memory?", __func__, __LINE__);
    return AE_DSP_ERROR_FAILED;
  }
  int lastAudioChannel = 0;
  for(int ii = 0; ii < m_MaxProcessingChannels; ii++)
  {
    // ToDo: add functions for opt modules and channel bypass!
    m_BiQuads[ii].BiQuadHandle = CBiQuadFactory::get_BiQuads(m_MaxFreqBands, (float)m_StreamSettings.iProcessSamplerate, ASPLIB_OPT_NATIVE);
    if(!m_BiQuads[ii].BiQuadHandle)
    {
      // ToDo: throw some error message!
    }

    // set all gain values to 0dB
    CBiQuadFactory::set_constQPeakingParams(m_BiQuads[ii].BiQuadHandle, 0.0f);

    // map next channel to BiQuad Filter
    unsigned long tempChannelFlag = 1<<lastAudioChannel;
    m_BiQuads[ii].AudioChannel = CADSPHelpers::GetNextChID(m_StreamSettings.lOutChannelPresentFlags,
                                                              CADSPHelpers::Translate_ChFlag_TO_ChID((AE_DSP_CHANNEL_PRESENT)tempChannelFlag));
    m_BiQuads[ii].ChannelFlag = CADSPHelpers::Translate_ChID_TO_ChFlag((AE_DSP_CHANNEL)m_BiQuads[ii].AudioChannel);
    if(m_BiQuads[ii].AudioChannel == AE_DSP_CH_INVALID)
    {
      // ToDo: throw some error message!
      // no next channel found!
    }
    lastAudioChannel = m_BiQuads[ii].AudioChannel +1;
  }

  return AE_DSP_ERROR_NO_ERROR;
}

unsigned int CDSPProcessor::PostProcess(unsigned int Mode_id, float **Array_in, float **Array_out, unsigned int Samples)
{
  if(m_NewMessage)
  {
    process_NewMessage();
    m_NewMessage = false;
  }

  for(int ii = 0; ii < m_MaxProcessingChannels; ii++)
  {
    ASPLIB_ERR err = CBiQuadFactory::calc_BiQuadSamples(m_BiQuads[ii].BiQuadHandle,
                                                        Array_in[m_BiQuads[ii].AudioChannel],
                                                        Array_out[m_BiQuads[ii].AudioChannel],
                                                        Samples);
      if(m_PostGain[ch] != 1.0f)
      {
        for(uint ii = 0; ii < Samples; ii++)
        {
          Array_out[ch][ii] *= m_PostGain[ii];
        }
      }
    if(err != ASPLIB_ERR_NO_ERROR)
    {
      // ToDo: throw some error message!
      return 0;
    }
  }

  return Samples;
}

CBiQuadMessageBase::BIQUAD_MESSAGE_RET CDSPProcessor::send_Message(CBiQuadMessage *Message)
{
  if(!Message || Message->get_ModeID() != POST_MODE_PARAMETRIC_EQ_ID)
  {
    return CBiQuadMessage::BiQuadMessage_InvalidInput;
  }

  int biquadHandleIdx = -1;
  for(int ch = 0; ch < m_MaxProcessingChannels; ch++)
  {
    if(!(CADSPHelpers::Translate_ChID_TO_ChFlag(Message->get_AudioChannelID()) & m_BiQuads[ch].ChannelFlag))
    {
      biquadHandleIdx = ch;
    }
  }

  if(biquadHandleIdx < 0)
  {
    return CBiQuadMessage::BiQuadMessage_AudioChannelNotPresent;
  }

  // wait for old message to be processed
  while(m_NewMessage);

  // process biquad message
  switch(Message->get_MessageType())
  {
    case CBiQuadMessage::BIQUAD_MESSAGE_SEND_BIQUAD_HANDLE:
    {
      m_BiQuadHandleMessage = dynamic_cast<CBiQuadMessage_BiQuadHandle*>(Message);

      if(!m_BiQuadHandleMessage)
      {
        KODI->Log(ADDON::LOG_ERROR, "%s line %i: Invalid CBiQuadMessage_BiQuadHandle object pointer! Please contact Addon author.", __func__, __LINE__);
        return CBiQuadMessage::BiQuadMessage_InvalidInput;
      }

      m_NewMessage = true;
      while(m_NewMessage);  // wait until message is processed
    }
    break;

//    case CBiQuadMessage::BIQAUD_MESSAGE_SEND_COEFFICIENTS:
//    {
//      m_BiQuadCoefficientsMessage = (CBiQuadMessage_Coefficients*)Message;
//
//      m_NewMessage = true;
//      while(m_NewMessage); // wait for message to be processed
//    }
//    break;

    case CBiQuadMessage::BIQAUD_MESSAGE_SEND_COEFFIECIENTS_IDX:
    {
      m_BiQuadCoefficientsMessage = dynamic_cast<CBiQuadMessage_Coefficients*>(Message);

      if(!m_BiQuadCoefficientsMessage)
      {
        KODI->Log(ADDON::LOG_ERROR, "%s line %i: Invalid CBiQuadMessage_Coefficients object pointer! Please contact Addon author.", __func__, __LINE__);
        return CBiQuadMessage::BiQuadMessage_InvalidInput;
      }

      m_NewMessage = true;
    }
    break;

    case CBiQuadMessage::BIQUAD_MESSAGE_GET_SAMPLE_FREQUENCY:
      dynamic_cast<BiQuadMessage_Float*>(Message)->get_MessageObj() = (float)m_StreamSettings.iProcessSamplerate;
    break;

    default:
      return CBiQuadMessage::BiQuadMessage_UnsupportedMessageType;
    break;
  }

  return CBiQuadMessage::BiQuadMessage_Success;
}

void CDSPProcessor::process_NewMessage()
{
  if(m_BiQuadCoefficientsMessage)
  {
    if(CADSPHelpers::IsChannelID_Present(m_StreamSettings.lOutChannelPresentFlags, m_BiQuadCoefficientsMessage->AudioChannel))
    {
      ADSP_BiQuad *p = NULL;
      for(uint ch = 0; ch < m_MaxFreqBands; ch++)
      {
        if(m_BiQuads[ch].AudioChannel == m_BiQuadCoefficientsMessage->AudioChannel)
        {
          p = &m_BiQuads[ch];
        }
      }
      if(!p)
      {
        return;
      }

      ASPLIB_ERR err = CBiQuadFactory::set_BiQuadCoefficients(p->BiQuadHandle,
                                                              &m_BiQuadCoefficientsMessage->Coefficients,
                                                              m_BiQuadCoefficientsMessage->BiQuadIndex,
                                                              m_BiQuadCoefficientsMessage->c0,
                                                              m_BiQuadCoefficientsMessage->d0);
      if(err != ASPLIB_ERR_NO_ERROR)
      {
        KODI->Log(ADDON::LOG_ERROR, "During setting new biquad coefficients an error occurred!");
      }
    }
  }

  if(m_BiQuadHandleMessage)
  {
    ADSP_BiQuad *p = NULL;
    for(uint ch = 0; ch < m_MaxFreqBands; ch++)
    {
      if(m_BiQuads[ch].AudioChannel == m_BiQuadHandleMessage->AudioChannel)
      {
        p = &m_BiQuads[ch];
      }
    }
    if(!p)
    {
      return;
    }

    ASPLIB_BIQUAD_HANDLE biquadHandle;
    biquadHandle.BiQuads = p->BiQuadHandle->BiQuads;

    // change pointers to return biquad handle
    p->BiQuadHandle->BiQuads = m_BiQuadHandleMessage->BiQuadHandle->BiQuadHandle->BiQuads;
    m_BiQuadHandleMessage->BiQuadHandle->BiQuadHandle->BiQuads = biquadHandle.BiQuads;
  }
}
