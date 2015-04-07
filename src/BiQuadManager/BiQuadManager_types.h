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


#include <asplib/BiQuads/apslib_BiQuadFactory.h>
#include <kodi/kodi_adsp_types.h>
#include "template/ADSPHelpers.h"

typedef enum
{
  BIQUAD_DESIGN_UNKOWN = -1,
  BIQUAD_CONST_Q_EQ,
  BIQUAD_NON_CONST_Q_EQ,
  BIQUAD_BUTTERWORTH_LOW_PASS,
  BIQUAD_BUTTERWORTH_HIGH_PASS,
  BIQUAD_DESIGN_MAX
}BiQuadDesignMethod;

typedef struct
{
  BiQuadDesignMethod    DesignMethod;     // Stores the BiQuad Design method. For details see BiQuadDesignMethod
  AE_DSP_CHANNEL        AudioChannel;     // Stores the requested AudioChannel
  AE_DSP_CHANNEL_FLAGS  ChannelFlag;      // Stores the requested AudioChannelFlag
  unsigned int          SampleFrequency;  // Stores the used sample frequency by the BiQuad.
  unsigned int          Quantity;         // Stores the amount of used BiQuads
  ASPLIB_BIQUAD_HANDLE  *BiQuadHandle;    // store the BiQuad Filter and the used optimization module
}ADSP_BiQuad;
