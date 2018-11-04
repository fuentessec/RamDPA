// ======================================================================
// Copyright (C) 2018 Alberto Fuentes Rodríguez <fuentessec@gmail.com>
// This file is part of RamDPA <https://github.com/fuentessec/RamDPA>.
//
// RamDPA is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// RamDPA is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with RamDPA.  If not, see <http://www.gnu.org/licenses/>.
// ======================================================================


#include "keyhypothesis_allvalues_8set.h"
#include <stdint.h>


KeyHypothesisAllValues8Set::KeyHypothesisAllValues8Set() : KeyHypothesis8Set (256)
{
    // insert all values in the set
    for (uint16_t i = 0; i <= 0x0FF; i++){
        setElem ((uint8_t*)&i, i);
    }
}
