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
#include "BiQuadMessageBase.h"
#include "BiQuadManager/BiQuadManager_types.h"
#include "asplib/constants_typedefs/asplib_typedefs.h"

// prototypes
class CBiQuadMessage_BiQuadHandle;
class CBiQuadMessage_Coefficients;
class CBiQuadMessage;
template<class T> class TBiQuadMessage;

// typedefs
typedef TBiQuadMessage<CBiQuadMessage_BiQuadHandle> BiQuadMessage_BiQuadHandle;
typedef TBiQuadMessage<CBiQuadMessage_Coefficients> BiQuadMessage_Coefficients;
typedef TBiQuadMessage<float> BiQuadMessage_Float;

class CBiQuadMessage_BiQuadHandle
{
  public:
    CBiQuadMessage_BiQuadHandle()
    {
      BiQuadHandle = NULL;
    }

    ~CBiQuadMessage_BiQuadHandle() {}

    ADSP_BiQuad *BiQuadHandle;
};

class CBiQuadMessage_Coefficients
{
  public:
    CBiQuadMessage_Coefficients()
    {
      Coefficients.a0 = 0.0f;
      Coefficients.a1 = 0.0f;
      Coefficients.a2 = 0.0f;

      Coefficients.b1 = 0.0f;
      Coefficients.b2 = 0.0f;

      BiQuadIndex = -1;
    }

    ~CBiQuadMessage_Coefficients() {}

    uint BiQuadIndex;   // BiQuad index to address the correct BiQuad filter.
                        // Only for set messages: BiQuadIndex < 0 --> sets Gain for all filters
    ASPLIB_BIQUAD_COEFFICIENTS Coefficients;
};

class CBiQuadMessage : public CBiQuadMessageBase
{
  public:
    CBiQuadMessage();
    ~CBiQuadMessage();

    typedef enum
    {
      BIQUAD_MESSAGE_UNKNOWN = -1,
      BIQUAD_MESSAGE_SEND_BIQUAD_HANDLE,
      BIQUAD_MESSAGE_DESTROY_BIQUAD_HANDLE,
      BIQUAD_MESSAGE_GET_BIQUAD_CONFIG_CHANNEL,
      BIQAUD_MESSAGE_SEND_COEFFICIENTS,
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
class TBiQuadMessage : public CBiQuadMessage
{
  public:
    TBiQuadMessage()
    {
      m_MessageObj = NULL;
    }

    ~TBiQuadMessage() {}

    void set_MessageObj(T &MessageObj)
    {
      m_MessageObj = MessageObj;
    }

    T &get_MessageObj()
    {
      if(m_MessageObj)
      {
        return m_MessageObj;
      }

      return NULL;
    }

  protected:
    T &m_MessageObj;
};

