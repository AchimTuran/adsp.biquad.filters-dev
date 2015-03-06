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
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */



#include "IAddonException.h"
#include <string>

template<class C>
class TAddonException : public IAddonException<C>
{
  public:
    TAddonException(C Exception, std::string Function="", std::string Filename="", int Line=-1, std::string Module="")
      : IAddonException<C>(Function, Filename, Line, Module)
    {
      m_Exception = Exception;
    }

    ~TAddonException() {}

    virtual C &what() { return m_Exception; }
};

// type definitions
typedef TAddonException<std::string> CAddonStringException;

// ToDo: Add Linux and Windows compiler flags for __FUNCTION__
#define __FUNCTION__ ""

#define ADDON_STRING_EXCEPTION_HANDLER(ErrorStr)  CAddonStringException(ErrorStr, __FUNCTION__, __FILE__, __LINE__)
#define ADDON_STRING_MODULE_EXCEPTION_HANDLER(ErrorStr, Module)  CAddonStringException(ErrorStr, __FUNCTION__, __FILE__, __LINE__, Module)
