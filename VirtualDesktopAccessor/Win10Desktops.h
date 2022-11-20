#pragma once

#include "stdafx.h"

const IID IID_IServiceProvider = {
	0x6D5140C1, 0x7436, 0x11CE, 0x80, 0x34, 0x00, 0xAA, 0x00, 0x60, 0x09, 0xFA };

const CLSID CLSID_ImmersiveShell = {
	0xC2F03A33, 0x21F5, 0x47FA, 0xB4, 0xBB, 0x15, 0x63, 0x62, 0xA2, 0xF2, 0x39 };

const CLSID CLSID_VirtualDesktopManagerInternal = {
	0xC5E0CDCA, 0x7B6E, 0x41B2, 0x9F, 0xC4, 0xD9, 0x39, 0x75, 0xCC, 0x46, 0x7B };

const CLSID CLSID_IVirtualNotificationService = {
	0xA501FDEC, 0x4A09, 0x464C, 0xAE, 0x4E, 0x1B, 0x9C, 0x21, 0xB8, 0x49, 0x18 
};

const CLSID CLSID_IVirtualDesktopManager = {
	0xAA509086, 0x5CA9, 0x4C25, { 0x8f, 0x95, 0x58, 0x9d, 0x3c, 0x07, 0xb4, 0x8a }
};

const CLSID CLSID_VirtualDesktopPinnedApps = {
	0xb5a399e7, 0x1c87, 0x46b8, 0x88, 0xe9, 0xfc, 0x57, 0x47, 0xb1, 0x71, 0xbd
};

// IID same as in MIDL IVirtualDesktopNotification
const IID IID_IVirtualDesktopNotification = {
    0xCD403E52, 0xDEED, 0x4C13, { 0xB4, 0x37, 0xB9, 0x83, 0x80, 0xF2, 0xB1, 0xE8 }
};

// Ignore following API's:
#define IAsyncCallback UINT
#define IImmersiveMonitor UINT
#define APPLICATION_VIEW_COMPATIBILITY_POLICY UINT
#define IShellPositionerPriority UINT
#define IApplicationViewOperation UINT
#define APPLICATION_VIEW_CLOAK_TYPE UINT
#define IApplicationViewPosition UINT

DECLARE_INTERFACE_IID_(IApplicationView, IInspectable, "372E1D3B-38D3-42E4-A15B-8AB2B178F513")
{
	/*** IUnknown methods ***/
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObject) PURE;
	STDMETHOD_(ULONG, AddRef)(THIS) PURE;
	STDMETHOD_(ULONG, Release)(THIS) PURE;

	/*** IInspectable methods ***/
	STDMETHOD(GetIids)(__RPC__out ULONG *iidCount, __RPC__deref_out_ecount_full_opt(*iidCount) IID **iids) PURE;
	STDMETHOD(GetRuntimeClassName)(__RPC__deref_out_opt HSTRING *className) PURE;
	STDMETHOD(GetTrustLevel)(__RPC__out TrustLevel *trustLevel) PURE;

	/*** IApplicationView methods ***/
	STDMETHOD(SetFocus)(THIS) PURE;
	STDMETHOD(SwitchTo)(THIS) PURE;
	STDMETHOD(TryInvokeBack)(THIS_ IAsyncCallback*) PURE;
	STDMETHOD(GetThumbnailWindow)(THIS_ HWND*) PURE;
	STDMETHOD(GetMonitor)(THIS_ IImmersiveMonitor**) PURE;
	STDMETHOD(GetVisibility)(THIS_ int*) PURE;
	STDMETHOD(SetCloak)(THIS_ APPLICATION_VIEW_CLOAK_TYPE, int) PURE;
	STDMETHOD(GetPosition)(THIS_ REFIID, void**) PURE;
	STDMETHOD(SetPosition)(THIS_ IApplicationViewPosition*) PURE;
	STDMETHOD(InsertAfterWindow)(THIS_ HWND) PURE;
	STDMETHOD(GetExtendedFramePosition)(THIS_ RECT*) PURE;
	STDMETHOD(GetAppUserModelId)(THIS_ PWSTR*) PURE;
	STDMETHOD(SetAppUserModelId)(THIS_ PCWSTR) PURE;
	STDMETHOD(IsEqualByAppUserModelId)(THIS_ PCWSTR, int*) PURE;
	STDMETHOD(GetViewState)(THIS_ UINT*) PURE;
	STDMETHOD(SetViewState)(THIS_ UINT) PURE;
	STDMETHOD(GetNeediness)(THIS_ int*) PURE;
	STDMETHOD(GetLastActivationTimestamp)(THIS_ ULONGLONG*) PURE;
	STDMETHOD(SetLastActivationTimestamp)(THIS_ ULONGLONG) PURE;
	STDMETHOD(GetVirtualDesktopId)(THIS_ GUID*) PURE;
	STDMETHOD(SetVirtualDesktopId)(THIS_ REFGUID) PURE;
	STDMETHOD(GetShowInSwitchers)(THIS_ int*) PURE;
	STDMETHOD(SetShowInSwitchers)(THIS_ int) PURE;
	STDMETHOD(GetScaleFactor)(THIS_ int*) PURE;
	STDMETHOD(CanReceiveInput)(THIS_ BOOL*) PURE;
	STDMETHOD(GetCompatibilityPolicyType)(THIS_ APPLICATION_VIEW_COMPATIBILITY_POLICY*) PURE;
	STDMETHOD(SetCompatibilityPolicyType)(THIS_ APPLICATION_VIEW_COMPATIBILITY_POLICY) PURE;
	//STDMETHOD(GetPositionPriority)(THIS_ IShellPositionerPriority**) PURE; // removed in 1803
	//STDMETHOD(SetPositionPriority)(THIS_ IShellPositionerPriority*) PURE; // removed in 1803
	STDMETHOD(GetSizeConstraints)(THIS_ IImmersiveMonitor*, SIZE*, SIZE*) PURE;
	STDMETHOD(GetSizeConstraintsForDpi)(THIS_ UINT, SIZE*, SIZE*) PURE;
	STDMETHOD(SetSizeConstraintsForDpi)(THIS_ const UINT*, const SIZE*, const SIZE*) PURE;
	//STDMETHOD(QuerySizeConstraintsFromApp)(THIS) PURE; // removed in 1803
	STDMETHOD(OnMinSizePreferencesUpdated)(THIS_ HWND) PURE;
	STDMETHOD(ApplyOperation)(THIS_ IApplicationViewOperation*) PURE;
	STDMETHOD(IsTray)(THIS_ BOOL*) PURE;
	STDMETHOD(IsInHighZOrderBand)(THIS_ BOOL*) PURE;
	STDMETHOD(IsSplashScreenPresented)(THIS_ BOOL*) PURE;
	STDMETHOD(Flash)(THIS) PURE;
	STDMETHOD(GetRootSwitchableOwner)(THIS_ IApplicationView**) PURE;
	STDMETHOD(EnumerateOwnershipTree)(THIS_ IObjectArray**) PURE;
	
	STDMETHOD(GetEnterpriseId)(THIS_ PWSTR*) PURE;
	STDMETHOD(IsMirrored)(THIS_ BOOL*) PURE;

	// Unsure
	STDMETHOD(Unknown1)(THIS_ int*) PURE;
	STDMETHOD(Unknown2)(THIS_ int*) PURE;
	STDMETHOD(Unknown3)(THIS_ int*) PURE;
	STDMETHOD(Unknown4)(THIS_ int) PURE;

	// 17661?
	//STDMETHOD(Unknown5)(THIS) PURE;
	//STDMETHOD(Unknown6)(THIS_ int*) PURE;
	//STDMETHOD(Unknown7)(THIS_ int) PURE;
	//STDMETHOD(Unknown8)(THIS_ int, THIS_ int) PURE;

};

const __declspec(selectany) IID & IID_IApplicationView = __uuidof(IApplicationView);

DECLARE_INTERFACE_IID_(IVirtualDesktopPinnedApps, IUnknown, "4ce81583-1e4c-4632-a621-07a53543148f")
{
	/*** IUnknown methods ***/
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObject) PURE;
	STDMETHOD_(ULONG, AddRef)(THIS) PURE;
	STDMETHOD_(ULONG, Release)(THIS) PURE;

	/*** IVirtualDesktopPinnedApps methods ***/
	STDMETHOD(IsAppIdPinned)(THIS_ PCWSTR appId, BOOL*) PURE;
	STDMETHOD(PinAppID)(THIS_ PCWSTR appId) PURE;
	STDMETHOD(UnpinAppID)(THIS_ PCWSTR appId) PURE;
	STDMETHOD(IsViewPinned)(THIS_ IApplicationView*, BOOL*) PURE;
	STDMETHOD(PinView)(THIS_ IApplicationView*) PURE;
	STDMETHOD(UnpinView)(THIS_ IApplicationView*) PURE;

};

// Ignore following API's:
#define IImmersiveApplication UINT
#define IApplicationViewChangeListener UINT

DECLARE_INTERFACE_IID_(IApplicationViewCollection, IUnknown, "1841C6D7-4F9D-42C0-AF41-8747538F10E5")
{
	/*** IUnknown methods ***/
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObject) PURE;
	STDMETHOD_(ULONG, AddRef)(THIS) PURE;
	STDMETHOD_(ULONG, Release)(THIS) PURE;

	/*** IApplicationViewCollection methods ***/
	STDMETHOD(GetViews)(THIS_ IObjectArray**) PURE;
	STDMETHOD(GetViewsByZOrder)(THIS_ IObjectArray**) PURE;
	STDMETHOD(GetViewsByAppUserModelId)(THIS_ PCWSTR, IObjectArray**) PURE;
	STDMETHOD(GetViewForHwnd)(THIS_ HWND, IApplicationView**) PURE;
	STDMETHOD(GetViewForApplication)(THIS_ IImmersiveApplication*, IApplicationView**) PURE;
	STDMETHOD(GetViewForAppUserModelId)(THIS_ PCWSTR, IApplicationView**) PURE;
	STDMETHOD(GetViewInFocus)(THIS_ IApplicationView**) PURE;
    STDMETHOD(TryGetLastActiveVisibleView)(IApplicationView** ) PURE;
    STDMETHOD(RefreshCollection)(THIS) PURE;
	STDMETHOD(RegisterForApplicationViewChanges)(THIS_ IApplicationViewChangeListener*, DWORD*) PURE;
	// STDMETHOD(RegisterForApplicationViewPositionChanges)(THIS_ IApplicationViewChangeListener*, DWORD*) PURE;
	STDMETHOD(UnregisterForApplicationViewChanges)(THIS_ DWORD) PURE;
};

MIDL_INTERFACE("536D3495-B208-4CC9-AE26-DE8111275BF8")
IVirtualDesktop : public IUnknown
{
public:
	virtual HRESULT STDMETHODCALLTYPE IsViewVisible(
		IApplicationView *pView,
		int *pfVisible) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetID(
		GUID *pGuid) = 0;

	// Ben - W11 22H2 to next comment
    //virtual HRESULT STDMETHODCALLTYPE GetMonitor(
    //    HMONITOR *monitor) = 0;
	// Ben - W11 22H2 from prev comment

	virtual HRESULT STDMETHODCALLTYPE Unknown1() = 0;
#if NET5_0_OR_GREATER
	virtual HRESULT STDMETHODCALLTYPE GetString() = 0;
#else
	virtual HRESULT STDMETHODCALLTYPE GetName() = 0;
#endif
	virtual HRESULT STDMETHODCALLTYPE GetWallpaperPath() = 0;
};

enum AdjacentDesktop
{
	LeftDirection = 3,
	RightDirection = 4
};

MIDL_INTERFACE("b2f925b9-5a0f-4d2e-9f4d-2b1507593c10")
IVirtualDesktopManagerInternal : public IUnknown
{
public:
	virtual HRESULT STDMETHODCALLTYPE GetCount(
        HMONITOR monitor,
		UINT *pCount) = 0;

	virtual HRESULT STDMETHODCALLTYPE MoveViewToDesktop(
		IApplicationView *pView,
		IVirtualDesktop *pDesktop) = 0;

	// Since build 10240
	virtual HRESULT STDMETHODCALLTYPE CanViewMoveDesktops(
		IApplicationView *pView,
		int *pfCanViewMoveDesktops) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetCurrentDesktop(
        HMONITOR monitor,
		IVirtualDesktop** desktop) = 0;

	// Ben - W11 22H2 to next comment
	virtual HRESULT STDMETHODCALLTYPE GetAllCurrentDesktops(
		IObjectArray **ppDesktops) = 0;
	// Ben - W11 22H2 from prev comment

	virtual HRESULT STDMETHODCALLTYPE GetDesktops(
        HMONITOR monitor,
		IObjectArray **ppDesktops) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetAdjacentDesktop(
		IVirtualDesktop *pDesktopReference,
		AdjacentDesktop uDirection,
		IVirtualDesktop **ppAdjacentDesktop) = 0;

	virtual HRESULT STDMETHODCALLTYPE SwitchDesktop(
        HMONITOR monitor,
		IVirtualDesktop *pDesktop) = 0;

	virtual HRESULT STDMETHODCALLTYPE CreateDesktop(
        HMONITOR monitor,
		IVirtualDesktop **ppNewDesktop) = 0;

	virtual HRESULT STDMETHODCALLTYPE MoveDesktop(
		IVirtualDesktop* desktop, 
		HMONITOR monitor, 
		INT32 index);

	virtual HRESULT STDMETHODCALLTYPE RemoveDesktop(
		IVirtualDesktop *pRemove,
		IVirtualDesktop *pFallbackDesktop) = 0;

	// Since build 10240
	virtual HRESULT STDMETHODCALLTYPE FindDesktop(
		GUID *desktopId,
		IVirtualDesktop **ppDesktop) = 0;

	// Ben - W11 22H2 to next comment
	virtual HRESULT STDMETHODCALLTYPE GetDesktopSwitchIncludeExcludeViews(
		IVirtualDesktop *pDesktop //, 
		//out IObjectArray unknown1, out IObjectArray unknown2
	) = 0;
#if NET5_0_OR_GREATER
	virtual HRESULT STDMETHODCALLTYPE SetName(
		IVirtualDesktop      *pDesktop, 
		UINT *newName) = 0;

	virtual HRESULT STDMETHODCALLTYPE SetWallpaper(
		IVirtualDesktop *pDesktop, 
		UINT*path) = 0;
#else
	virtual HRESULT STDMETHODCALLTYPE SetDesktopName(
		IVirtualDesktop *pDesktop, 
		HSTRING name) = 0;

	virtual HRESULT STDMETHODCALLTYPE SetDesktopWallpaper(
		IVirtualDesktop *pDesktop, 
		HSTRING path) = 0;
#endif
	virtual HRESULT STDMETHODCALLTYPE UpdateWallpaperPathForAllDesktops(
		HSTRING path) = 0;

	virtual HRESULT STDMETHODCALLTYPE CopyDesktopState(
		IApplicationView *pView0, 
		IApplicationView *pView1) = 0;

	virtual HRESULT STDMETHODCALLTYPE  GetDesktopIsPerMonitor() = 0;

	virtual HRESULT STDMETHODCALLTYPE SetDesktopIsPerMonitor(
		bool state) = 0;
	// Ben - W11 22H2 from prev comment
};

MIDL_INTERFACE("a5cd92ff-29be-454c-8d04-d82879fb3f1b")
IVirtualDesktopManager : public IUnknown
{
public:
	virtual HRESULT STDMETHODCALLTYPE IsWindowOnCurrentVirtualDesktop(
		/* [in] */ __RPC__in HWND topLevelWindow,
		/* [out] */ __RPC__out BOOL *onCurrentDesktop) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetWindowDesktopId(
		/* [in] */ __RPC__in HWND topLevelWindow,
		/* [out] */ __RPC__out GUID *desktopId) = 0;

	virtual HRESULT STDMETHODCALLTYPE MoveWindowToDesktop(
		/* [in] */ __RPC__in HWND topLevelWindow,
		/* [in] */ __RPC__in REFGUID desktopId) = 0;
};

MIDL_INTERFACE("CD403E52-DEED-4C13-B437-B98380F2B1E8")
IVirtualDesktopNotification : public IUnknown
{
public:
	virtual HRESULT STDMETHODCALLTYPE VirtualDesktopCreated(
		// Ben - W11 22H2 to next comment
		IObjectArray* monitors,
		// Ben - W11 22H2 from prev comment
		IVirtualDesktop *pDesktop) = 0;

	virtual HRESULT STDMETHODCALLTYPE VirtualDesktopDestroyBegin(
		// Ben - W11 22H2 to next comment
		IObjectArray* monitors,
		// Ben - W11 22H2 from prev comment
		IVirtualDesktop *pDesktopDestroyed,
		IVirtualDesktop *pDesktopFallback) = 0;

	virtual HRESULT STDMETHODCALLTYPE VirtualDesktopDestroyFailed(
		// Ben - W11 22H2 to next comment
		IObjectArray* monitors,
		// Ben - W11 22H2 from prev comment
		IVirtualDesktop *pDesktopDestroyed,
		IVirtualDesktop *pDesktopFallback) = 0;

	virtual HRESULT STDMETHODCALLTYPE VirtualDesktopDestroyed(
		// Ben - W11 22H2 to next comment
		IObjectArray* monitors,
		// Ben - W11 22H2 from prev comment
		IVirtualDesktop *pDesktopDestroyed,
		IVirtualDesktop *pDesktopFallback) = 0;

	// Ben - W11 22H2 to next comment
	/*virtual HRESULT STDMETHODCALLTYPE Proc7(
		int ppDesktop
	) = 0;*/
	// Ben - W11 22H2 from prev comment


    virtual HRESULT STDMETHODCALLTYPE VirtualDesktopIsPerMonitorChanged(
        BOOL isPerMonitor) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE VirtualDesktopMoved(
		IObjectArray* monitors,
        IVirtualDesktop *pDesktop,
        UINT64 oldIndex, 
        UINT64 newIndex) = 0;

	// Ben - W11 22H2 to next comment
	virtual HRESULT STDMETHODCALLTYPE VirtualDesktopRenamed(
    //virtual HRESULT STDMETHODCALLTYPE VirtualDesktopNameChanged(
        IVirtualDesktop *pDesktop,
        HSTRING name) = 0;
	// Ben - W11 22H2 from prev comment

    virtual HRESULT STDMETHODCALLTYPE ViewVirtualDesktopChanged(
		IApplicationView *pView) = 0;

	virtual HRESULT STDMETHODCALLTYPE CurrentVirtualDesktopChanged(
		IObjectArray* monitors,
		IVirtualDesktop *pDesktopOld,
		IVirtualDesktop *pDesktopNew) = 0;

    virtual HRESULT STDMETHODCALLTYPE VirtualDesktopWallpaperChanged(
        IVirtualDesktop *pDesktop,
        HSTRING name) = 0;

};

MIDL_INTERFACE("0CD45E71-D927-4F15-8B0A-8FEF525337BF")
IVirtualDesktopNotificationService : public IUnknown
{
public:
	virtual HRESULT STDMETHODCALLTYPE Register(
		IVirtualDesktopNotification *pNotification,
		DWORD *pdwCookie) = 0;

	virtual HRESULT STDMETHODCALLTYPE Unregister(
		DWORD dwCookie) = 0;
};
