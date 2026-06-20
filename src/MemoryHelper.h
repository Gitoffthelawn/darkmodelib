// SPDX-License-Identifier: MPL-2.0

/*
 * Copyright (c) 2025 ozone10
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

// This file is part of darkmodelib library.


#pragma once

#include <memory>
#include <new>
#include <type_traits>
#include <utility>

namespace dmlib_mem
{
	// NOLINTBEGIN(modernize-use-constraints) // keep c++17 compatibility for now

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 26485) // Expression 'array-name': No array to pointer decay (bounds.3).
#endif

	/// Nothrow variant of std::make_unique
	template <class T, class... Args, std::enable_if_t<!std::is_array_v<T>, int> = 0>
	[[nodiscard]] inline std::unique_ptr<T> make_unique_nothrow(Args&&... args) noexcept(noexcept(std::remove_reference_t<T>(std::forward<Args>(args)...)))
	{
		return std::unique_ptr<T>(new (std::nothrow) T(std::forward<Args>(args)...)); // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
	}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

	/// Nothrow variant of std::make_unique
	template <class T, std::enable_if_t<std::is_array_v<T>&& std::extent_v<T> == 0, int> = 0>
	[[nodiscard]] inline std::unique_ptr<T> make_unique_nothrow(const size_t size) noexcept
	{
		using U = std::remove_extent_t<T>;
		return std::unique_ptr<T>(new (std::nothrow) U[size]());
	}

	/// Nothrow variant of std::make_unique
	template <class T, class... Args, std::enable_if_t<std::extent_v<T> != 0, int> = 0>
	void make_unique_nothrow(Args&&...) = delete;

	// NOLINTEND(modernize-use-constraints)
} // namespace dmlib_mem
