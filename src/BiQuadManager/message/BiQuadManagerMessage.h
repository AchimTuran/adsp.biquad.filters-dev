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



#include "BiQuadMessage.h"
#include <iostream>

// prototypes
template<class T> class TBiQuadManagerMessage;
class CBiQuadManagerMessage_Gain;

// typedefs
typedef TBiQuadManagerMessage<CBiQuadManagerMessage_Gain> BiQuadManagerMessage_Gain;
typedef TBiQuadManagerMessage<uint> BiQuadManagerMessage_Quantity;

class CBiQuadManagerMessage_Gain
{
  public:
    CBiQuadManagerMessage_Gain()
    {
      BiQuadIndex = -1;
      Gain = 0.0f;
    }

    uint BiQuadIndex;   // BiQuad index to address the correct BiQuad filter.
                        // Only for set messages: BiQuadIndex < 0 --> sets Gain for all filters
    float Gain;         // Gain in dB
};

class CBiQuadManagerMessage : public CBiQuadMessage
{
  public:
    CBiQuadManagerMessage();
    ~CBiQuadManagerMessage();

    typedef enum
    {
      BIQUAD_MANAGER_MESSAGE_UNKNOWN = -1,
      BIQUAD_MANAGER_MESSAGE_SET_GAIN,
      BIQUAD_MANAGER_MESSAGE_SET_GAIN_IDX,
      BIQUAD_MANAGER_MESSAGE_GET_GAIN_IDX,
      BIQUAD_MANAGER_MESSAGE_SET_QUANTITY,
      BIQUAD_MANAGER_MESSAGE_GET_QUANTITY,
      BIQUAD_MANAGER_MESSAGE_MAX
    }BIQUAD_MANAGER_MESSAGE;

    BIQUAD_MANAGER_MESSAGE get_MessageType();
    BIQUAD_MANAGER_MESSAGE set_MessageType(BIQUAD_MANAGER_MESSAGE MessageType);

  private:
    BIQUAD_MANAGER_MESSAGE m_MessageType;
};

template<class T>
class TBiQuadManagerMessage : public CBiQuadManagerMessage
{
  public:
    TBiQuadManagerMessage()
    {
      m_MessageObj = NULL;
    }

    ~TBiQuadManagerMessage() {}

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
