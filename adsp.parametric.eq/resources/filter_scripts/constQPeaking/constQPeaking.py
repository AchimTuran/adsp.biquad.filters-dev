# -*- coding: utf-8 -*-
"""
 * Copyright (C) 2014 Achim Turan, Achim.Turan@o2online.de
 * https://github.com/AchimTuran/asplib
 *
 * This file is part of asplib (Achim's Signal Processing LIBrary)
 *
 * asplib (Achim's Signal Processing LIBrary) is free software:
 * you can redistribute it and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * asplib (Achim's Signal Processing LIBrary) is distributed
 * in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with asplib (Achim's Signal Processing LIBrary).
 * ifnot, see <http://www.gnu.org/licenses/>.
"""

from numpy import *

def calcCoefficients():
    # ToDo: Clamp values like vlc Biquads!
    Q = 1.0     # Quality
    fc = 1.0    # center frequency 
    fs = 1.0    # sample frequency
    Gain = 1.0  # frequency band gain [dB]
    
    # Coefficients
    a0 = 0.0
    a1 = 0.0
    a2 = 0.0
    b1 = 0.0
    b2 = 0.0
    
    # ToDo: check values to avoid division by zero!
    K = tan(pi*fc/fs)
    V0 = pow(10.0, Gain/20.0)
    d0 = 1.0 + K/Q + K*K
    e0 = 1.0 + K/(Q*V0) + K*K
    
    alpha = 1.0 + K*V0/Q + K*K
    beta = 2.0*(K*K - 1.0)
    gamma = 1.0 - V0*K / Q + K*K
    delta = 1.0 - K/Q + K*K
    eta = 1.0 - K/(V0*Q) + K*K
    
    
    if Gain > 0.0:
    # boost design equations
        a0 = alpha/d0
        a1 = beta/d0
        a2 = gamma/d0
        
        b1 = -beta/d0
        b2 = -delta/d0
    else:
    # cut design equations
        a0 = d0/e0
        a1 = beta/e0
        a2 = delta/e0
        
        b1 = -beta/e0
        b2 = -eta/e0
        
    return array([a0, a1, a2, b1, b2])
    
coe = calcCoefficients()