# VirtualDesktopAccessor.dll

![Stability:Beta](https://img.shields.io/badge/stability-beta-orange)
[![GitHub tag (latest SemVer)](https://img.shields.io/github/v/release/bforbenny/VirtualDesktopAccessor)](https://github.com/bforbenny/VirtualDesktopAccessor/releases/latest)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](/LICENSE.txt)
[![GitHub issues](https://img.shields.io/github/issues/bforbenny/VirtualDesktopAccessor)](https://GitHub.com/bforbenny/VirtualDesktopAccessor/issues/)

DLL for accessing Windows 11 (tested with build 22621.1105) Virtual Desktop features from e.g. AutoHotkey.

Download the VirtualDesktopAccessor.dll from directory x64\Release\VirtualDesktopAccessor.dll in the repository. This DLL works only on 64 bit Windows 11.

## AutoHotkey script as example:
[Virtual-Desktop-Enhancer](https://github.com/sdias/win-10-virtual-desktop-enhancer)

## All functions exported by DLL:

    * int GetCurrentDesktopNumber()
    * int GetDesktopCount()
    * GUID GetDesktopIdByNumber(int number) // Returns zeroed GUID with invalid number found
    * int GetDesktopNumber(IVirtualDesktop *pDesktop) 
    * int GetDesktopNumberById(GUID desktopId)
    * GUID GetWindowDesktopId(HWND window)
    * int GetWindowDesktopNumber(HWND window)
    * int IsWindowOnCurrentVirtualDesktop(HWND window)
    * BOOL MoveWindowToDesktopNumber(HWND window, int number) 
    * void GoToDesktopNumber(int number)
    * void RegisterPostMessageHook(HWND listener, int messageOffset)
    * void UnregisterPostMessageHook(HWND hwnd)
	* int IsPinnedWindow(HWND hwnd) // Returns 1 if pinned, 0 if not pinned, -1 if not valid
	* void PinWindow(HWND hwnd)
	* void UnPinWindow(HWND hwnd)
	* int IsPinnedApp(HWND hwnd) // Returns 1 if pinned, 0 if not pinned, -1 if not valid
	* void PinApp(HWND hwnd)
	* void UnPinApp(HWND hwnd)
	* int IsWindowOnDesktopNumber(HWND window, int number) / 
	* void RestartVirtualDesktopAccessor() // Call this during taskbar created message

	* void EnableKeepMinimized() // Deprecated, does nothing
	* void RestoreMinimized() // Deprecated, does nothing
