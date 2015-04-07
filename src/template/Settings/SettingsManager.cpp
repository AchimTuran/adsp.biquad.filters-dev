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



#include "SettingsHelpers.h"
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

  m_IsSettingsXMLLoaded = false;

  m_Settings.clear();
}

CSettingsManager::~CSettingsManager()
{
  destroy();
}

void CSettingsManager::Init()
{
  if(!m_IsSettingsXMLLoaded)
  {
    m_IsSettingsXMLLoaded = true;
    read_SettingsXML();
  }
}

void CSettingsManager::destroy()
{
  write_SettingsXML();

  // delete settings map and its elements
  for(SettingsMap::iterator mapIter = m_Settings.begin(); mapIter != m_Settings.end(); mapIter++)
  {
    //string key = iter->first;
    for(CSettingsList::iterator listIter = mapIter->second.begin(); listIter != mapIter->second.end(); listIter++)
    {
      ISettingsElement *settingsElement = *listIter;
      if(settingsElement)
      {
        delete settingsElement;
        *listIter = NULL;
      }
    }
  }

  // all dynamic memory is deallocated, so we can delete the settings map
  m_Settings.clear();
}
void CSettingsManager::write_SettingsXML()
{
  // ToDo: implement xml stuff
  // isXMLFilePresent?
  // Yes --> update XML data and store it in the corresponding XML file
  // No  --> create XML file and store XML data
}

void CSettingsManager::read_SettingsXML()
{
  // ToDo: implement xml stuff
  // isXMLFilePresent?
  // generate XML data
  // Yes --> read XML data
  // No  --> do nothing
}

bool CSettingsManager::add_Setting( string MainCategory, string SubCategory,
                                    string GroupName, string Key,
                                    ISettingsElement::SettingsTypes Type, void *Value)
{
  if(!Value)
  {
    // ToDo: add some error log text to kodi.log
    return false;
  }

  string settingsStr = MainCategory + SETTINGS_SEPERATOR_STR + SubCategory + SETTINGS_SEPERATOR_STR + GroupName;
  SettingsMap::iterator mapIter = m_Settings.find(settingsStr);
  if(mapIter != m_Settings.end())
  { // first we have to search, if the settings element is present in the founded Main- and Subcategory
    CSettingsList::iterator settingsIter = mapIter->second.begin();
    while(settingsIter != mapIter->second.end() && (*settingsIter)->get_Key() != Key)
    {
      settingsIter++;
    }

    if(settingsIter != mapIter->second.end() && (*settingsIter)->get_Key() == Key && Type == (*settingsIter)->get_Type())
    { // if the Type and Key are the same, we override the current setting with the new value
      // ToDo: add some warning to kodi.log
      // current setting is overwritten!

      // call set function of setting element
      return SetNewElementValue(*settingsIter, Value);
    }
  }

  // No element with the requested Main- and Subcategory and Type exists
  // so we create a new one
  ISettingsElement *settingsElement = CreateElement(Key, Type, Value);
  if(!settingsElement)
  {
    // ToDo: add a error message to kodi.log
    return false;
  }

  if(mapIter != m_Settings.end())
  {
    mapIter->second.push_back(settingsElement);
  }
  else
  {
    CSettingsList settingsList;
    settingsList.push_back(settingsElement);
    m_Settings[settingsStr] = settingsList;
  }

  return true;
}

ISettingsElement *CSettingsManager::CreateElement(string Key, ISettingsElement::SettingsTypes Type, void *Value)
{
  if(!Value)
  {
    // ToDo: add some warning message to kodi.log
    return NULL;
  }

  ISettingsElement *element = NULL;
  switch(Type)
  {
    case ISettingsElement::STRING_SETTING:
    {
      string *pVal = static_cast<string*>(Value);
      CStringSetting *p = new CStringSetting(*pVal, Key, Type);

      if(pVal && p)
      {
        element = dynamic_cast<ISettingsElement*>(p);
      }
      else
      {
        if(p)
        {
          delete p;
          p = NULL;
        }
      }
    }
    break;

    case ISettingsElement::UNSIGNED_INT_SETTING:
    {
      unsigned int *pVal = (unsigned int*)(Value);
      CUnsignedIntSetting *p = new CUnsignedIntSetting(*pVal, Key, Type);

      if(p)
      {
        element = dynamic_cast<ISettingsElement*>(p);
      }
    }
    break;

    case ISettingsElement::INT_SETTING:
    {
      int *pVal = (int*)(Value);
      CIntSetting *p = new CIntSetting(*pVal, Key, Type);

      if(p)
      {
        element = dynamic_cast<ISettingsElement*>(p);
      }
    }
    break;

    case ISettingsElement::FLOAT_SETTING:
    {
      float *pVal = (float*)(Value);
      CFloatSetting *p = new CFloatSetting(*pVal, Key, Type);

      if(p)
      {
        element = dynamic_cast<ISettingsElement*>(p);
      }
    }
    break;

    case ISettingsElement::DOUBLE_SETTING:
    {
      double *pVal = (double*)(Value);
      CDoubleSetting *p = new CDoubleSetting(*pVal, Key, Type);

      if(p)
      {
        element = dynamic_cast<ISettingsElement*>(p);
      }
    }
    break;

    case ISettingsElement::BOOL_SETTING:
    {
      bool *pVal = (bool*)(Value);
      CBoolSetting *p = new CBoolSetting(*pVal, Key, Type);

      if(p)
      {
        element = dynamic_cast<ISettingsElement*>(p);
      }
    }
    break;

    default:
      element = NULL;
    break;
  }

  return element;
}

bool CSettingsManager::SetNewElementValue(ISettingsElement *Element, void *Value)
{
  if(!Element || !Value)
  {
    // ToDo: add some warning message to kodi.log
    return false;
  }

  switch(Element->get_Type())
  {
    case ISettingsElement::STRING_SETTING:
      STRING_SETTINGS(Element)->set_Setting(*static_cast<string*>(Value));
    break;

    case ISettingsElement::UNSIGNED_INT_SETTING:
      UNSIGNED_INT_SETTINGS(Element)->set_Setting(*((unsigned int*)Value));
    break;

    case ISettingsElement::INT_SETTING:
      INT_SETTINGS(Element)->set_Setting(*((int*)Value));
    break;

    case ISettingsElement::FLOAT_SETTING:
      FLOAT_SETTINGS(Element)->set_Setting(*((float*)Value));
    break;

    case ISettingsElement::DOUBLE_SETTING:
      DOUBLE_SETTINGS(Element)->set_Setting(*((double*)Value));
    break;

    case ISettingsElement::BOOL_SETTING:
      BOOL_SETTINGS(Element)->set_Setting(*((bool*)Value));
    break;

    default:
      return false;
    break;
  }

  return true;
}

void CSettingsManager::destroy_Setting(string MainCategory, string SubCategory, string GroupName, string Key)
{
  string settingsStr = MainCategory + SETTINGS_SEPERATOR_STR + SubCategory + SETTINGS_SEPERATOR_STR + GroupName;
  SettingsMap::iterator mapIter = m_Settings.find(settingsStr);
  if(mapIter != m_Settings.end())
  {
    CSettingsList::iterator listIter = mapIter->second.begin();

    // search for the correct key
    while(listIter != mapIter->second.end() && (*listIter)->get_Key() != Key)
    {
      listIter++;
    }

    // if the key was found, delete this setting
    if(listIter != mapIter->second.end() && (*listIter)->get_Key() != Key)
    {
      if(*listIter)
      {
        delete *listIter;
        *listIter = NULL;
      }

      // erase this setting from the list
      mapIter->second.erase(listIter);
    }

    // check if there are other settings, else delete this Main- and Subcategory
    if(mapIter->second.size() <= 0)
    {
      m_Settings.erase(mapIter);
    }

    if(listIter == mapIter->second.end())
    {
      // ToDo: show some warning log message
    }
  }
  else
  {
    // ToDo: show some warning log message
  }
}

ISettingsElement *CSettingsManager::find_Setting(string MainCategory, string SubCategory, string GroupName, string Key)
{
  string settingsStr = MainCategory + SETTINGS_SEPERATOR_STR + SubCategory + SETTINGS_SEPERATOR_STR + GroupName;
  SettingsMap::iterator mapIter = m_Settings.find(settingsStr);
  if(mapIter != m_Settings.end())
  {
    CSettingsList::iterator listIter = mapIter->second.begin();

    // search for the correct key
    while(listIter != mapIter->second.end() && (*listIter)->get_Key() != Key)
    {
      listIter++;
    }

    if(listIter != mapIter->second.end() && (*listIter)->get_Key() == Key)
    {
      return *listIter;
    }
  }

  // ToDo: show some warning log message
  return NULL;
}
