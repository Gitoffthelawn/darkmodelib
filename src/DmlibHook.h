// SPDX-License-Identifier: MPL-2.0

/*
 * Copyright (c) 2025 ozone10
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

// This file is part of darkmodelib library.


#pragma once

#include <windows.h>

namespace dmlib_hook
{
	template <typename HookGroup>
	class AutoHook
	{
	public:
		AutoHook(bool forceDetach = false) noexcept
			: m_isHooked(HookGroup::hook()), m_forceDetach(forceDetach)
		{}

		AutoHook(const AutoHook&) = delete;
		AutoHook& operator=(const AutoHook&) = delete;

		AutoHook(AutoHook&&) = delete;
		AutoHook& operator=(AutoHook&&) = delete;

		~AutoHook() noexcept
		{
			if (m_isHooked)
			{
				m_isHooked = HookGroup::unhook(m_forceDetach) > 0;
			}
		}

		explicit operator bool() const noexcept
		{
			return m_isHooked;
		}

	private:
		bool m_isHooked = false;
		bool m_forceDetach = false;
	};

#if defined(_DARKMODELIB_USE_SCROLLBAR_FIX) && (_DARKMODELIB_USE_SCROLLBAR_FIX > 0)
	bool loadOpenNcThemeData(const HMODULE& hUxtheme) noexcept;
	/// Makes scroll bars on the specified window and all its children consistent.
	void enableDarkScrollBarForWindowAndChildren(HWND hWnd);
	void fixDarkScrollBar();
#endif

	/// Overrides a specific system color with a custom color.
	void setMySysColor(int nIndex, COLORREF clr) noexcept;

	struct GetSysColor
	{
		/// Hooks system color to support runtime customization.
		static bool hook() noexcept;
		/// Unhooks system color overrides and restores default color behavior.
		static size_t unhook(bool forceDetach = false) noexcept;
	};

	struct TaskDlgTheme
	{
		/// Hooks `GetThemeColor` and `DrawThemeBackgroundEx` to support dark colors.
		static bool hook() noexcept;
		/// Unhooks `GetThemeColor` and `DrawThemeBackgroundEx` overrides and restores default color behavior.
		static size_t unhook(bool forceDetach = false) noexcept;
	};

	/// Updates highlight brush for ChooseFont dialog.
	void updateFontBrush() noexcept;
	/// Updates luminosity slider brush for ChooseColor dialog.
	void updateLumSliderBrush() noexcept;

	struct FontSysColor
	{
		/// Hooks system color to support runtime customization for ChooseFont dialog.
		static bool hook() noexcept;
		/// Unhooks system color overrides for ChooseFont dialog and restores default color behavior.
		static size_t unhook(bool forceDetach = false) noexcept;
	};

	struct FontFillRect
	{
		/// Hooks ::FillRect to support runtime customization for ChooseFont dialog.
		static bool hook() noexcept;
		/// Unhooks ::FillRect override for ChooseFont dialog and restores default behavior.
		static size_t unhook(bool forceDetach = false) noexcept;
	};

	struct ClrGetSysColorBrush
	{
		/// Hooks system color brush to support runtime customization for ChooseColor dialog luminosity slider control.
		static bool hook() noexcept;
		/// Unhooks ::GetSysColorBrush override for ChooseColor dialogs and restores default behavior.
		static size_t unhook(bool forceDetach = false) noexcept;
	};

	struct FontMB
	{
		/// Hooks ::MessageBoxW to apply dark mode for ChooseFont dialog message boxes.
		static bool hook() noexcept;
		/// Unhooks ChooseFont dialog ::MessageBoxW.
		static size_t unhook(bool forceDetach = false) noexcept;
	};
} // namespace dmlib_hook
