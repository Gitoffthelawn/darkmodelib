// SPDX-License-Identifier: MPL-2.0

/*
 * Copyright (c) 2025 ozone10
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

// This file is part of darkmodelib library.


#pragma once

#if defined(_DARKMODELIB_CUSTOM_MEM) && (_DARKMODELIB_CUSTOM_MEM == 0x001)
	#define DMLIB_MEM_MAKE_UNIQUE ::dmlib_mem::make_unique_nothrow
	#define DMLIB_MEM_NOEXCEPT noexcept

#else
	#define DMLIB_MEM_MAKE_UNIQUE ::std::make_unique
	#define DMLIB_MEM_NOEXCEPT
#endif // defined(_DARKMODELIB_CUSTOM_MEM) && (_DARKMODELIB_CUSTOM_MEM > 0)
