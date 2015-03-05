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



#include <string>
#include "ISettingsElement.h"

template<typename T>
class CSettingsElementTemplate : public ISettingsElement
{
  public:
    typedef enum SettingsTypes
    {
        MIN_SETTING = -1,
        STRING_SETTING,
        UNSIGNED_INT_SETTING,
        INT_SETTING,
        FLOAT_SETTING,
        BOOL_SETTING,
        MAX_SETTING
    };

    CSettingsElementTemplate(T &Value, std::string Key, SettingsTypes Type) :
      ISettingsElement(Key, Type)
    {
      m_Value = Value;
    }

    virtual ~CSettingsElementTemplate() {}

    virtual T get_Setting()               { return m_Value; }
    virtual void set_Setting(T &Setting)  { m_Value = Setting; }

  protected:
    T m_Value;
};
