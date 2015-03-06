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



#include <map>
#include <string>

#include "TSettingsElement.h"

// Settings typdefs
typedef TSettingsElement<std::string>   CStringSetting;
typedef TSettingsElement<unsigned int>  CUnsignedIntSetting;
typedef TSettingsElement<int>           CIntSetting;
typedef TSettingsElement<float>         CFloatSetting;
typedef TSettingsElement<double>        CDoubleSetting;
typedef TSettingsElement<bool>          CBoolSetting;

// Settings macro helpers
#define STRING_SETTINGS(X)        dynamic_cast<CStringSetting*>(X)
#define UNSIGNED_INT_SETTINGS(X)  dynamic_cast<CUnsignedIntSetting*>(X)
#define INT_SETTINGS(X)           dynamic_cast<CIntSetting*>(X)
#define FLOAT_SETTINGS(X)         dynamic_cast<CFloatSetting*>(X)
#define DOUBLE_SETTINGS(X)        dynamic_cast<CDoubleSetting*>(X)
#define BOOL_SETTINGS(X)          dynamic_cast<CBoolSetting*>(X)

typedef std::map<std::string, ISettingsElement*> SettingsMap;

class CSettingsManager
{
  public:
    CSettingsManager(std::string XMLFilename);
    ~CSettingsManager();

    void add_Setting(std::string Key, std::string Value);
    void add_Setting(std::string Key, unsigned int Value);
    void add_Setting(std::string Key, int Value);
    void add_Setting(std::string Key, float Value);
    void add_Setting(std::string Key, double Value);
    void add_Setting(std::string Key, bool Value);

    void destroy_Setting(std::string Key);

    ISettingsElement *find_Setting(std::string Key);

  protected:
    //SettingsMap m_Settings;
    SettingsMap m_Settings;
    std::string m_XMLFilename;

  private:
    void save_CurrentSettings();
    void parse_SettingsXML();
};
