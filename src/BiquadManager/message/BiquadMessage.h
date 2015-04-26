#pragma once
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



#include <iostream>
#include "BiquadMessageBase.h"
#include "BiquadManager/BiquadManager_types.h"
#include "asplib/constants_typedefs/asplib_typedefs.h"

// prototypes
class CBiquadMessage_BiquadHandle;
class CBiquadMessage_Coefficients;
class CBiquadMessage;
template<class T> class TBiquadMessage;

// typedefs
typedef TBiquadMessage<CBiquadMessage_BiquadHandle> BiquadMessage_BiquadHandle;
typedef TBiquadMessage<CBiquadMessage_Coefficients> BiquadMessage_Coefficients;
typedef TBiquadMessage<float> BiquadMessage_Float;
typedef TBiquadMessage<float> CBiquadMessage_GainIdx;

//class CBiquadMessage_GainIdx
//{
//  public:
//    
//};

class CBiquadMessage_BiquadHandle
{
  public:
    CBiquadMessage_BiquadHandle()
    {
      BiquadHandle = NULL;
      AudioChannel = AE_DSP_CH_INVALID;
    }

    ~CBiquadMessage_BiquadHandle() {}

    ADSP_Biquad *BiquadHandle;
    AE_DSP_CHANNEL AudioChannel;
};

class CBiquadMessage_Coefficients
{
  public:
    CBiquadMessage_Coefficients()
    {
      Coefficients.a0 = 0.0f;
      Coefficients.a1 = 0.0f;
      Coefficients.a2 = 0.0f;

      Coefficients.b1 = 0.0f;
      Coefficients.b2 = 0.0f;

      c0 = 0.0f;
      d0 = 0.0f;

      BiquadIndex = -1;
      AudioChannel = AE_DSP_CH_INVALID;
    }

    ~CBiquadMessage_Coefficients() {}

    uint BiquadIndex;   // Biquad index to address the correct Biquad filter.
                        // Only for set messages: BiquadIndex < 0 --> sets Gain for all filters
    ASPLIB_BIQUAD_COEFFICIENTS Coefficients;
    float                      c0;
    float                      d0;
    AE_DSP_CHANNEL             AudioChannel;
};

class CBiquadMessage : public CBiquadMessageBase
{
  public:
    CBiquadMessage();
    ~CBiquadMessage();

    typedef enum
    {
      BIQUAD_MESSAGE_UNKNOWN = -1,                // Unknown Biquad message
      BIQUAD_MESSAGE_SEND_BIQUAD_HANDLE,          // request current biquad handle to receive it
      BIQUAD_MESSAGE_SEND_GAIN_IDX,
      //BIQUAD_MESSAGE_DESTROY_BIQUAD_HANDLE,
      //BIQUAD_MESSAGE_GET_BIQUAD_CONFIG_CHANNEL,
      //BIQAUD_MESSAGE_SEND_COEFFICIENTS,
      BIQAUD_MESSAGE_SEND_COEFFIECIENTS_IDX,
      BIQUAD_MESSAGE_GET_SAMPLE_FREQUENCY,
      BIQUAD_MESSAGE_MAX
    }BIQUAD_MESSAGE;

    BIQUAD_MESSAGE  get_MessageType();
    BIQUAD_MESSAGE  set_MessageType(BIQUAD_MESSAGE MessageType);

  private:
    BIQUAD_MESSAGE m_MessageType;
};


template<class T>
class TBiquadMessage : public CBiquadMessage
{
  public:
    TBiquadMessage()
    {
      m_MessageObj = NULL;
    }

    ~TBiquadMessage() {}

    void set_MessageObj(T &MessageObj)
    {
      m_MessageObj = MessageObj;
    }

    T &get_MessageObj()
    {
      return m_MessageObj;
    }

  protected:
    T &m_MessageObj;
};

