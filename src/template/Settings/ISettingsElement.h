#pragma once
/*      Copyright (C) 2005-2014 Team XBMC
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



class ISettingsElement
{
public:
  typedef enum SettingsTypes
  {
      MIN_SETTING = -1,
      STRING_SETTING,
      UNSIGNED_INT_SETTING,
      INT_SETTING,
      FLOAT_SETTING,
      DOUBLE_SETTING,
      BOOL_SETTING,
      MAX_SETTING
  };

  ISettingsElement(std::string Key, SettingsTypes Type)
  {
    if(Type <= MIN_SETTING || Type >= MAX_SETTING)
    {
      // ToDo: throw exception!
    }

    if(Key.empty() || Key == "")
    {
      // ToDo: throw exception!
    }

    m_Type = Type;
    m_Key = Key;
  }

  virtual ~ISettingsElement() {}

  SettingsTypes get_Type()  { return m_Type; }
  std::string   get_Key()   { return m_Key; }

private:
  SettingsTypes m_Type;
  std::string   m_Key;
};
