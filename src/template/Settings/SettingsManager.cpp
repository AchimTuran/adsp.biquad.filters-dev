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

bool CSettingsManager::add_Setting( std::string MainCategory, std::string SubCategory,
                                    std::string Element, std::string Key,
                                    ISettingsElement::SettingsTypes Type, void *Value)
{
  if(!Value)
  {
    // ToDo: add some error log text to kodi.log
    return false;
  }

  bool retVal = true;
  string settingsStr = MainCategory + "." + SubCategory + "." + Element;
  SettingsMap::iterator iter = m_Settings.find(settingsStr);
  if(iter != m_Settings.end())
  { // try to replace the current value with the new value

    // first we have to search if the settings element is present in the founded Main- and Subcategory
    CSettingsList::iterator settingsIter = iter->second.front();
    while(settingsIter != iter->second.end() && (*settingsIter)->m_Key != Key)
    {
      settingsIter++;
    }

    if(settingsIter != iter->second.end())
    {
      // now we have to check if the type is the same
      if(Type != (*settingsIter)->m_Type)
      {
        // ToDo: add some warning message to kodi.log
        return false;
      }

      // ToDo call set function of setting element
      //STRING_SETTINGS(iter->second)->set_Setting(Value);
      return retVal;
    }
  }

  // No element with the requested Main- and Subcategory, Type exists
  // so we create a new one
  ISettingsElement *element = CreateElement(Key, Type, Value);
  if(!element)
  {
    //throw ADDON_STRING_EXCEPTION_HANDLER("Couldn't create settings element! Not enough free dynamic memory?");
    // ToDo: add a error message to kodi.log
    return false;
  }

  m_Settings[Key].push_back(element);

  return retVal;
}

ISettingsElement *CSettingsManager::CreateElement(std::string Key, ISettingsElement::SettingsTypes Type, void *Value)
{
  ISettingsElement *element = NULL;

  switch(Type)
  {
    case ISettingsElement::STRING_SETTING:
    {
      string *pVal = dynamic_cast<string*>(Value);
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
      int *pVal = (unsigned int*)(Value);
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

bool SetNewElementValue(ISettingsElement *Element)
{
  bool retVal = false;

  switch(Element->m_Type)
  {
    case ISettingsElement::STRING_SETTING:
    break;

    case ISettingsElement::UNSIGNED_INT_SETTING:
    break;

    case ISettingsElement::INT_SETTING:
    break;

    case ISettingsElement::FLOAT_SETTING:
    break;

    case ISettingsElement::DOUBLE_SETTING:
    break;

    case ISettingsElement::BOOL_SETTING:
    break;

    default:
      retVal = false;
    break;
  }

  return retVal;
}

void CSettingsManager::add_Setting(std::string MainCategory, std::string SubCategory, std::string Element, std::string Key, std::string Value)
{
  string settingsStr = MainCategory + "." + SubCategory + "." + Element;
  SettingsMap::iterator iter = m_Settings.find(settingsStr);
  if(iter != m_Settings.end())
  { // replace current value with the new value
    CSettingsList::iterator settingsIter = iter->second.front();
    while(settingsIter != iter->second.end() && (*settingsIter)->m_Key != Key)
    {
      settingsIter++;
    }

    if(settingsIter != iter->second.end())
    {
      if(ISettingsElement::STRING_SETTING != (*settingsIter)->m_Type)
      {
        // ToDo: show some warning and return false!
        return;
      }
      else
      {
        STRING_SETTINGS(iter->second)->set_Setting(Value);
      }
    }
    else
    {
      // ToDo: create new element!
    }
  }
  else
  { // generate a new Element


    ISettingsElement *element = dynamic_cast<ISettingsElement*>(new CStringSetting(Value, Key, ISettingsElement::STRING_SETTING));
    if(!element)
    {
      throw ADDON_STRING_EXCEPTION_HANDLER("Couldn't create settings element! Not enough free dynamic memory?");
    }

    m_Settings[Key] = element;
  }
}

void CSettingsManager::add_Setting(std::string MainCategory, std::string SubCategory, std::string Element, unsigned int Value)
{
  SettingsMap::iterator iter = m_Settings.find(Key);
  if(iter != m_Settings.end())
  { // replace current value with the new value
    UNSIGNED_INT_SETTINGS(iter->second)->set_Setting(Value);
  }
  else
  { // generate a new Element
    ISettingsElement *element = dynamic_cast<ISettingsElement*>(new CUnsignedIntSetting(Value, Key, ISettingsElement::UNSIGNED_INT_SETTING));
    if(!element)
    {
      throw ADDON_STRING_EXCEPTION_HANDLER("Couldn't create settings element! Not enough free dynamic memory?");
    }

    m_Settings[Key] = element;
  }
}

void CSettingsManager::add_Setting(std::string MainCategory, std::string SubCategory, std::string Element, int Value)
{
  SettingsMap::iterator iter = m_Settings.find(Key);
  if(iter != m_Settings.end())
  { // replace current value with the new value
    INT_SETTINGS(iter->second)->set_Setting(Value);
  }
  else
  { // generate a new Element
    ISettingsElement *element = dynamic_cast<ISettingsElement*>(new CIntSetting(Value, Key, ISettingsElement::INT_SETTING));
    if(!element)
    {
      throw ADDON_STRING_EXCEPTION_HANDLER("Couldn't create settings element! Not enough free dynamic memory?");
    }

    m_Settings[Key] = element;
  }
}

void CSettingsManager::add_Setting(std::string MainCategory, std::string SubCategory, std::string Element, float Value)
{
  SettingsMap::iterator iter = m_Settings.find(Key);
  if(iter != m_Settings.end())
  { // replace current value with the new value
    FLOAT_SETTINGS(iter->second)->set_Setting(Value);
  }
  else
  { // generate a new Element
    ISettingsElement *element = dynamic_cast<ISettingsElement*>(new CFloatSetting(Value, Key, ISettingsElement::FLOAT_SETTING));
    if(!element)
    {
      throw ADDON_STRING_EXCEPTION_HANDLER("Couldn't create settings element! Not enough free dynamic memory?");
    }

    m_Settings[Key] = element;
  }
}

void CSettingsManager::add_Setting(std::string MainCategory, std::string SubCategory, std::string Element, double Value)
{
  SettingsMap::iterator iter = m_Settings.find(Key);
  if(iter != m_Settings.end())
  { // replace current value with the new value
    DOUBLE_SETTINGS(iter->second)->set_Setting(Value);
  }
  else
  { // generate a new Element
    ISettingsElement *element = dynamic_cast<ISettingsElement*>(new CDoubleSetting(Value, Key, ISettingsElement::DOUBLE_SETTING));
    if(!element)
    {
      throw ADDON_STRING_EXCEPTION_HANDLER("Couldn't create settings element! Not enough free dynamic memory?");
    }

    m_Settings[Key] = element;
  }
}

void CSettingsManager::add_Setting(std::string MainCategory, std::string SubCategory, std::string Element, std::string Key, bool Value)
{
  SettingsMap::iterator iter = m_Settings.find(MainCategory + "." + SubCategory + "." + Element);
  if(iter != m_Settings.end())
  { // replace current value with the new value
    BOOL_SETTINGS(iter->second)->set_Setting(Value);
  }
  else
  { // generate a new Element
    ISettingsElement *element = dynamic_cast<ISettingsElement*>(new CBoolSetting(Value, Key, ISettingsElement::BOOL_SETTING));
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
