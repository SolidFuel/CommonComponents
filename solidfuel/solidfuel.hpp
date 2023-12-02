/****
 * Solid Fuel Common Components
 * Copyright (C) 2023 Solid Fuel
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the 
 * Free Software Foundation, either version 3 of the License, or (at your 
 * option) any later version. This program is distributed in the hope that it 
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the LICENSE file
 * in the root directory.
 ****/


/*******************************************************************************
 * This file declares a JUCE module for the shared library code implemented in
 * this directory. The block below is read by the Projucer to automatically
 * generate project code that uses the module. For details, see the
 * JUCE Module Format.txt file in the JUCE directory.

   BEGIN_JUCE_MODULE_DECLARATION
    ID:                 solidfuel
    vendor:             SolidFuel
    version:            0.1.0
    name:               SolidFuel
    license:            GPL/Commercial
    description:        Common modules for SolidFuel Plugins
    minimumCppStandard: 17
    dependencies:       juce_gui_basics
   END_JUCE_MODULE_DECLARATION
*******************************************************************************/

#pragma once

#include "Source/ValueListener.hpp"
#include "Source/BoxComponent.hpp"
#include "Source/ButtonGroupComponent.hpp"
