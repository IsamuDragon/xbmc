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
#ifndef __PERIPHERAL_CALLBACKS_H__
#define __PERIPHERAL_CALLBACKS_H__

#include "kodi_peripheral_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct CB_PeripheralLib
{
  /*!
   * @brief Trigger a scan for peripherals
   * The add-on calls this if a change in hardware is detected.
   */
  void (*TriggerScan)(void* addonData);

} CB_PeripheralLib;

#ifdef __cplusplus
}
#endif

#endif // __PERIPHERAL_CALLBACKS_H__