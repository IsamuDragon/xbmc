/*
 *      Copyright (C) 2014 Team XBMC
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

#include "GenericJoystickButtonMapping.h"
#include "input/joysticks/IJoystickButtonMapper.h"
#include "input/joysticks/JoystickTranslator.h"

#include <algorithm>
#include <assert.h>
#include <cmath>

#define AXIS_THRESHOLD  0.5f

CGenericJoystickButtonMapping::CGenericJoystickButtonMapping(IJoystickButtonMapper* buttonMapper, IJoystickButtonMap* buttonMap)
  : m_buttonMapper(buttonMapper),
    m_buttonMap(buttonMap)
{
  assert(m_buttonMapper);
  assert(m_buttonMap);
}

bool CGenericJoystickButtonMapping::OnButtonMotion(unsigned int buttonIndex, bool bPressed)
{
  if (bPressed)
  {
    CJoystickDriverPrimitive buttonPrimitive(buttonIndex);
    if (buttonPrimitive.IsValid())
      return m_buttonMapper->MapPrimitive(m_buttonMap, buttonPrimitive);
  }

  return false;
}

bool CGenericJoystickButtonMapping::OnHatMotion(unsigned int hatIndex, HatDirection direction)
{
  if (direction != HatDirectionNone)
  {
    CJoystickDriverPrimitive hatPrimtive(hatIndex, direction);
    if (hatPrimtive.IsValid())
      return m_buttonMapper->MapPrimitive(m_buttonMap, hatPrimtive);

    return m_buttonMapper->IsMapping();
  }

  return false;
}

bool CGenericJoystickButtonMapping::OnAxisMotion(unsigned int axisIndex, float position)
{
  if (position != 0.0f)
  {
    // Remove axis if it was active in the opposite direction
    CJoystickDriverPrimitive oppositeAxis(axisIndex, CJoystickTranslator::GetDirection(-position));
    Delete(oppositeAxis);

    CJoystickDriverPrimitive semiAxisPrimitive(axisIndex, CJoystickTranslator::GetDirection(position));
    if (semiAxisPrimitive.IsValid())
    {
      const bool bActive = (std::abs(position) >= AXIS_THRESHOLD);

      if (!bActive)
      {
        Delete(semiAxisPrimitive);
      }
      else if (!IsActive(semiAxisPrimitive))
      {
        Record(semiAxisPrimitive);
        return m_buttonMapper->MapPrimitive(m_buttonMap, semiAxisPrimitive);
      }
    }

    return m_buttonMapper->IsMapping();
  }

  return false;
}

void CGenericJoystickButtonMapping::Record(const CJoystickDriverPrimitive& semiAxis)
{
  m_activeAxes.push_back(semiAxis);
}

void CGenericJoystickButtonMapping::Delete(const CJoystickDriverPrimitive& semiAxis)
{
  m_activeAxes.erase(std::remove(m_activeAxes.begin(), m_activeAxes.end(), semiAxis), m_activeAxes.end());
}

bool CGenericJoystickButtonMapping::IsActive(const CJoystickDriverPrimitive& semiAxis)
{
  return std::find(m_activeAxes.begin(), m_activeAxes.end(), semiAxis) != m_activeAxes.end();
}
