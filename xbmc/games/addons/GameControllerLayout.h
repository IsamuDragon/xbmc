/*
 *      Copyright (C) 2015 Team XBMC
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
#pragma once

#include "GameControllerFeature.h"

#include <string>
#include <vector>

class TiXmlElement;

namespace GAME
{

class CGameControllerLayout
{
public:
  CGameControllerLayout(void) { Reset(); }

  void Reset(void);

  unsigned int       Label(void) const   { return m_label; }
  const std::string& Image(void) const   { return m_strImage; }
  const std::string& Overlay(void) const { return m_strOverlay; }
  unsigned int       Width(void) const   { return m_width; }
  unsigned int       Height(void) const  { return m_height; }

  const std::vector<CGameControllerFeature>& Features(void) const { return m_features; }

  unsigned int FeatureCount(FeatureType type = FEATURE_UNKNOWN, ButtonType buttonType = BUTTON_UNKNOWN) const;

  bool Deserialize(const TiXmlElement* pLayoutElement);

private:
  unsigned int m_label;
  std::string  m_strImage;
  std::string  m_strOverlay;
  unsigned int m_width;
  unsigned int m_height;

  std::vector<CGameControllerFeature> m_features;
};

}
