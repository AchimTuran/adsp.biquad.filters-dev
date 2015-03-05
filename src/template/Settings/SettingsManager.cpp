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



#include "SettingsManager.h"
using namespace std;

CSettingsManager::CSettingsManager(string XMLFilename)
{
  if(XMLFilename == "" || XMLFilename.empty())
  {
    // ToDo: throw exception!
  }

  m_Settings.erase();
}

CSettingsManager::~CSettingsManager()
{
  save_CurrentSettings();
}

void CSettingsManager::save_CurrentSettings()
{
    // ToDo: implement xml stuff
    iterator<map<std::string, *ISettingsElement>> iter = m_Settings.begin();
}

void CSettingsManager::add_Setting(std::string Key, std::string Value)
{
  // ToDo: Implement this method
}

void CSettingsManager::add_Setting(std::string Key, unsigned int Value)
{
  // ToDo: Implement this method
}

void CSettingsManager::add_Setting(std::string Key, int Value)
{
  // ToDo: Implement this method
}

void CSettingsManager::add_Setting(std::string Key, float Value)
{
  // ToDo: Implement this method
}

void CSettingsManager::add_Setting(std::string Key, double Value)
{
  // ToDo: Implement this method
}

void CSettingsManager::add_Setting(std::string Key, bool Value)
{
  // ToDo: Implement this method
}

void CSettingsManager::destroy_Setting(std::string Key)
{
  // ToDo: Implement this method
}

ISettingsElement *CSettingsManager::find_Setting(std::string Key)
{
  // ToDo: Implement this method

  return NULL;
}
