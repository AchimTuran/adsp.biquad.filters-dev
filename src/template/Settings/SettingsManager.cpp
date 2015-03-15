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



#include <iterator>
#include "SettingsManager.h"

#include "../AddonExceptions/TAddonException.h"
using namespace std;

CSettingsManager::CSettingsManager(string XMLFilename)
{
  if(XMLFilename == "" || XMLFilename.empty())
  {
    throw ADDON_STRING_EXCEPTION_HANDLER("Invalid XML filename!");
  }
  m_XMLFilename = XMLFilename;

  m_Settings.clear();

  parse_SettingsXML();
}

CSettingsManager::~CSettingsManager()
{
  destroy();
}

void CSettingsManager::destroy()
{
  save_CurrentSettings();

  // delete settings map and its elements
  for(SettingsMap::iterator iter = m_Settings.begin(); iter != m_Settings.end(); iter++)
  {
    string key = iter->first;
    ISettingsElement *settingsElement = iter->second;

    if(settingsElement)
    {
      delete settingsElement;
      iter->second = NULL;
    }

    m_Settings.erase(iter);
  }
}
void CSettingsManager::save_CurrentSettings()
{
  // ToDo: implement xml stuff
  // isXMLFilePresent?
  // Yes --> update XML data and store it in the corresponding XML file
  // No  --> create XML file and store XML data
}

void CSettingsManager::parse_SettingsXML()
{
  // ToDo: implement xml stuff
  // isXMLFilePresent?
  // generate XML data
  // Yes --> read XML data
  // No  --> do nothing
}

void CSettingsManager::add_Setting(std::string Key, std::string Value)
{
  SettingsMap::iterator iter = m_Settings.find(Key);
  if(iter != m_Settings.end())
  { // replace current value with the new value
    STRING_SETTINGS(iter->second)->set_Setting(Value);
  }
  else
  { // generate a new Element
    ISettingsElement *element = new CStringSetting(Value, Key, ISettingsElement::STRING_SETTING);
    if(!element)
    {
      throw ADDON_STRING_EXCEPTION_HANDLER("Couldn't create settings element! Not enough free dynamic memory?");
    }

    m_Settings[Key] = element;
  }
}

void CSettingsManager::add_Setting(std::string Key, unsigned int Value)
{
  SettingsMap::iterator iter = m_Settings.find(Key);
  if(iter != m_Settings.end())
  { // replace current value with the new value
    UNSIGNED_INT_SETTINGS(iter->second)->set_Setting(Value);
  }
  else
  { // generate a new Element
    ISettingsElement *element = new CUnsignedIntSetting(Value, Key, ISettingsElement::UNSIGNED_INT_SETTING);
    if(!element)
    {
      throw ADDON_STRING_EXCEPTION_HANDLER("Couldn't create settings element! Not enough free dynamic memory?");
    }

    m_Settings[Key] = element;
  }
}

void CSettingsManager::add_Setting(std::string Key, int Value)
{
  SettingsMap::iterator iter = m_Settings.find(Key);
  if(iter != m_Settings.end())
  { // replace current value with the new value
    INT_SETTINGS(iter->second)->set_Setting(Value);
  }
  else
  { // generate a new Element
    ISettingsElement *element = new CIntSetting(Value, Key, ISettingsElement::INT_SETTING);
    if(!element)
    {
      throw ADDON_STRING_EXCEPTION_HANDLER("Couldn't create settings element! Not enough free dynamic memory?");
    }

    m_Settings[Key] = element;
  }
}

void CSettingsManager::add_Setting(std::string Key, float Value)
{
  SettingsMap::iterator iter = m_Settings.find(Key);
  if(iter != m_Settings.end())
  { // replace current value with the new value
    FLOAT_SETTINGS(iter->second)->set_Setting(Value);
  }
  else
  { // generate a new Element
    ISettingsElement *element = new CFloatSetting(Value, Key, ISettingsElement::FLOAT_SETTING);
    if(!element)
    {
      throw ADDON_STRING_EXCEPTION_HANDLER("Couldn't create settings element! Not enough free dynamic memory?");
    }

    m_Settings[Key] = element;
  }
}

void CSettingsManager::add_Setting(std::string Key, double Value)
{
  SettingsMap::iterator iter = m_Settings.find(Key);
  if(iter != m_Settings.end())
  { // replace current value with the new value
    DOUBLE_SETTINGS(iter->second)->set_Setting(Value);
  }
  else
  { // generate a new Element
    ISettingsElement *element = new CDoubleSetting(Value, Key, ISettingsElement::DOUBLE_SETTING);
    if(!element)
    {
      throw ADDON_STRING_EXCEPTION_HANDLER("Couldn't create settings element! Not enough free dynamic memory?");
    }

    m_Settings[Key] = element;
  }
}

void CSettingsManager::add_Setting(std::string Key, bool Value)
{
  SettingsMap::iterator iter = m_Settings.find(Key);
  if(iter != m_Settings.end())
  { // replace current value with the new value
    BOOL_SETTINGS(iter->second)->set_Setting(Value);
  }
  else
  { // generate a new Element
    ISettingsElement *element = (ISettingsElement*)new CBoolSetting(Value, Key, ISettingsElement::BOOL_SETTING);
    if(!element)
    {
      throw ADDON_STRING_EXCEPTION_HANDLER("Couldn't create settings element! Not enough free dynamic memory?");
    }

    m_Settings[Key] = element;
  }
}

void CSettingsManager::destroy_Setting(std::string Key)
{
  SettingsMap::iterator iter = m_Settings.find(Key);
  if(iter != m_Settings.end())
  {
    delete iter->second;
    iter->second = NULL;
    m_Settings.erase(iter);
  }
}

ISettingsElement *CSettingsManager::find_Setting(std::string Key)
{
  SettingsMap::iterator iter = m_Settings.find(Key);

  if(iter != m_Settings.end())
  {
    return iter->second;
  }
  else
  {
    return NULL;
  }
}
