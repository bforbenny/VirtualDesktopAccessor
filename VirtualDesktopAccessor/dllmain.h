#pragma once
#include "stdafx.h"
#include "Win10Desktops.h"

#define DllExport   __declspec( dllexport )

#define VDA_VirtualDesktopCreated 5
#define VDA_VirtualDesktopDestroyBegin 4
#define VDA_VirtualDesktopDestroyFailed 3
#define VDA_VirtualDesktopDestroyed 2
#define VDA_ViewVirtualDesktopChanged 1
#define VDA_CurrentVirtualDesktopChanged 0

#define VDA_IS_NORMAL 1
#define VDA_IS_MINIMIZED 2
#define VDA_IS_MAXIMIZED 3

std::map<HWND, int> listeners;
IServiceProvider* pServiceProvider = nullptr;
IVirtualDesktopManagerInternal *pDesktopManagerInternal = nullptr;
IVirtualDesktopManager *pDesktopManager = nullptr;
IApplicationViewCollection *viewCollection = nullptr;
IVirtualDesktopPinnedApps *pinnedApps = nullptr;
IVirtualDesktopNotificationService* pDesktopNotificationService = nullptr;
BOOL registeredForNotifications = FALSE;

DWORD idNotificationService = 0;

struct ChangeDesktopAction {
	GUID newDesktopGuid;
	GUID oldDesktopGuid;
};

void _PostMessageToListeners(int msgOffset, WPARAM wParam, LPARAM lParam) {
	for each (std::pair<HWND, int> listener in listeners) {
		PostMessage(listener.first, listener.second + msgOffset, wParam, lParam);
	}
}

void _RegisterService(BOOL force = FALSE) {
	if (force) {
		pServiceProvider = nullptr;
		pDesktopManagerInternal = nullptr;
		pDesktopManager = nullptr;
		viewCollection = nullptr;
		pinnedApps = nullptr;
		pDesktopNotificationService = nullptr;
		registeredForNotifications = FALSE;
	}

	if (pServiceProvider != nullptr) {
		return;
	}
	::CoInitialize(NULL);
	::CoCreateInstance(
		CLSID_ImmersiveShell, NULL, CLSCTX_LOCAL_SERVER,
		__uuidof(IServiceProvider), (PVOID*)&pServiceProvider);

	if (pServiceProvider == nullptr) {
		std::wcout << L"FATAL ERROR: pServiceProvider is null";
		return;
	}
	pServiceProvider->QueryService(__uuidof(IApplicationViewCollection), &viewCollection);

	pServiceProvider->QueryService(__uuidof(IVirtualDesktopManager), &pDesktopManager);

	pServiceProvider->QueryService(
		CLSID_VirtualDesktopPinnedApps,
		__uuidof(IVirtualDesktopPinnedApps), (PVOID*)&pinnedApps);

	pServiceProvider->QueryService(
		CLSID_VirtualDesktopManagerInternal,
		__uuidof(IVirtualDesktopManagerInternal), (PVOID*)&pDesktopManagerInternal);

	if (viewCollection == nullptr) {
		std::wcout << L"FATAL ERROR: viewCollection is null";
		return;
	}

	if (pDesktopManagerInternal == nullptr) {
		std::wcout << L"FATAL ERROR: pDesktopManagerInternal is null";
		return;
	}

	// Notification service
	HRESULT hrNotificationService = pServiceProvider->QueryService(
		CLSID_IVirtualNotificationService,
		__uuidof(IVirtualDesktopNotificationService),
		(PVOID*)&pDesktopNotificationService);
}


IApplicationView* _GetApplicationViewForHwnd(HWND hwnd) {
	if (hwnd == 0)
		return nullptr;
	IApplicationView* app = nullptr;
	viewCollection->GetViewForHwnd(hwnd, &app);
	return app;
}

void DllExport EnableKeepMinimized() {
	//_keepMinimized = true;
}

void DllExport RestoreMinimized() {
}

int DllExport GetDesktopCount()
{
	_RegisterService();

	IObjectArray *pObjectArray = nullptr;
	HRESULT hr = pDesktopManagerInternal->GetDesktops(nullptr, &pObjectArray);

	if (SUCCEEDED(hr))
	{
		UINT count;
		hr = pObjectArray->GetCount(&count);
		pObjectArray->Release();
		return count;
	}

	return -1;
}

std::wstring DllExport GetDesktopNameByID(GUID desktopId) {
	_RegisterService();

	IObjectArray* pObjectArray = nullptr;
	HRESULT hr = pDesktopManagerInternal->GetDesktops(nullptr, &pObjectArray);
	int found = -1;
	std::wstring name = L"";

	if (SUCCEEDED(hr))
	{
		UINT count;
		hr = pObjectArray->GetCount(&count);

		if (SUCCEEDED(hr))
		{
			for (UINT i = 0; i < count; i++)
			{
				IVirtualDesktop* pDesktop = nullptr;

				if (FAILED(pObjectArray->GetAt(i, __uuidof(IVirtualDesktop), (void**)&pDesktop)))
					continue;

				GUID id = { 0 };
				std::wstring name = L"";
				if (SUCCEEDED(pDesktop->GetID(&id)) && id == desktopId)
				{
					found = i;
					pDesktop->GetName(&name);
					//name = L"Hello World";
					pDesktop->Release();
					break;
				}

				pDesktop->Release();
			}
		}

		pObjectArray->Release();
	}

	return name;
}

int DllExport GetDesktopNumberById(GUID desktopId) {
	_RegisterService();

	IObjectArray *pObjectArray = nullptr;
	HRESULT hr = pDesktopManagerInternal->GetDesktops(nullptr, &pObjectArray);
	int found = -1;

	if (SUCCEEDED(hr))
	{
		UINT count;
		hr = pObjectArray->GetCount(&count);

		if (SUCCEEDED(hr))
		{
			for (UINT i = 0; i < count; i++)
			{
				IVirtualDesktop *pDesktop = nullptr;

				if (FAILED(pObjectArray->GetAt(i, __uuidof(IVirtualDesktop), (void**)&pDesktop)))
					continue;

				GUID id = { 0 };
				if (SUCCEEDED(pDesktop->GetID(&id)) && id == desktopId)
				{
					found = i;
					pDesktop->Release();
					break;
				}

				pDesktop->Release();
			}
		}

		pObjectArray->Release();
	}

	return found;
}

IVirtualDesktop* _GetDesktopByNumber(int number) {
	_RegisterService();

	IObjectArray *pObjectArray = nullptr;
	HRESULT hr = pDesktopManagerInternal->GetDesktops(nullptr, &pObjectArray);
	IVirtualDesktop* found = nullptr;

	if (SUCCEEDED(hr))
	{
		UINT count;
		hr = pObjectArray->GetCount(&count);
		pObjectArray->GetAt(number, __uuidof(IVirtualDesktop), (void**)&found);
		pObjectArray->Release();
	}

	return found;
}

GUID DllExport GetWindowDesktopId(HWND window) {
	_RegisterService();

	GUID pDesktopId = {};
	pDesktopManager->GetWindowDesktopId(window, &pDesktopId);

	return pDesktopId;
}

int DllExport GetWindowDesktopNumber(HWND window) {
	_RegisterService();

	GUID* pDesktopId = new GUID({ 0 });
	if (SUCCEEDED(pDesktopManager->GetWindowDesktopId(window, pDesktopId))) {
		return GetDesktopNumberById(*pDesktopId);
	}

	return -1;
}

int DllExport IsWindowOnCurrentVirtualDesktop(HWND window) {
	_RegisterService();

	BOOL b;
	if (SUCCEEDED(pDesktopManager->IsWindowOnCurrentVirtualDesktop(window, &b))) {
		return b;
	}

	return -1;
}

GUID DllExport GetDesktopIdByNumber(int number) {
	GUID id;
	IVirtualDesktop* pDesktop = _GetDesktopByNumber(number);
	if (pDesktop != nullptr) {
		pDesktop->GetID(&id);
		pDesktop->Release();
	}
	return id;
}


int DllExport IsWindowOnDesktopNumber(HWND window, int number) {
	_RegisterService();
	IApplicationView* app = nullptr;
	if (window == 0) {
		return -1;
	}
	viewCollection->GetViewForHwnd(window, &app);
	GUID desktopId = { 0 };
	app->GetVirtualDesktopId(&desktopId);
	GUID desktopCheckId = GetDesktopIdByNumber(number);
	app->Release();
	if (desktopCheckId == GUID_NULL || desktopId == GUID_NULL) {
		return -1;
	}

	if (GetDesktopIdByNumber(number) == desktopId) {
		return 1;
	}
	else {
		return 0;
	}
	
	return -1;
}

BOOL DllExport MoveWindowToDesktopNumber(HWND window, int number) {
	_RegisterService();
	IVirtualDesktop* pDesktop = _GetDesktopByNumber(number);
	if (pDesktopManager == nullptr) {
		std::wcout << L"ARRGH?";
		return false;
	}
	if (window == 0) {
		return false;
	}
	if (pDesktop != nullptr) {
		GUID id = { 0 };
		if (SUCCEEDED(pDesktop->GetID(&id))) {
			IApplicationView* app = nullptr;
			viewCollection->GetViewForHwnd(window, &app);
			if (app != nullptr) {
				pDesktopManagerInternal->MoveViewToDesktop(app, pDesktop);
				return true;
			}
		}
	}
	return false;
}


std::wstring DllExport GetDesktopName(IVirtualDesktop* pDesktop) {
	_RegisterService();

	if (pDesktop == nullptr) {
		return L"";
	}

	GUID guid;

	if (SUCCEEDED(pDesktop->GetID(&guid))) {
		return GetDesktopNameByID(guid);
	}

	return L"Err 200012";
}

int DllExport GetDesktopNumber(IVirtualDesktop *pDesktop) {
	_RegisterService();

	if (pDesktop == nullptr) {
		return -1;
	}

	GUID guid;

	if (SUCCEEDED(pDesktop->GetID(&guid))) {
		return GetDesktopNumberById(guid);
	}

	return -1;
}
IVirtualDesktop* GetCurrentDesktop() {
	_RegisterService();

	if (pDesktopManagerInternal == nullptr) {
		return nullptr;
	}
	IVirtualDesktop* found = nullptr;
	pDesktopManagerInternal->GetCurrentDesktop(nullptr, &found);
	return found;
}

int DllExport GetCurrentDesktopNumber() {
	IVirtualDesktop* virtualDesktop = GetCurrentDesktop();
	int number = GetDesktopNumber(virtualDesktop);
	virtualDesktop->Release();
	return number;
}

std::wstring DllExport GetCurrentDesktopName() {
	IVirtualDesktop* virtualDesktop = GetCurrentDesktop();
	std::wstring name = GetDesktopName(virtualDesktop);
	virtualDesktop->Release();
	return name;
}

void DllExport GoToDesktopNumber(int number) {
	_RegisterService();

	if (pDesktopManagerInternal == nullptr) {
		return;
	}

	IVirtualDesktop* oldDesktop = GetCurrentDesktop();
	GUID oldId = { 0 };
	oldDesktop->GetID(&oldId);
	oldDesktop->Release();

	IObjectArray *pObjectArray = nullptr;
	HRESULT hr = pDesktopManagerInternal->GetDesktops(nullptr, &pObjectArray);
	int found = -1;

	if (SUCCEEDED(hr))
	{
		UINT count;
		hr = pObjectArray->GetCount(&count);

		if (SUCCEEDED(hr))
		{
			for (UINT i = 0; i < count; i++)
			{
				IVirtualDesktop *pDesktop = nullptr;

				if (FAILED(pObjectArray->GetAt(i, __uuidof(IVirtualDesktop), (void**)&pDesktop)))
					continue;

				GUID id = { 0 };
				pDesktop->GetID(&id);
				if (i == number) {
					pDesktopManagerInternal->SwitchDesktop(nullptr, pDesktop);
				}

				pDesktop->Release();
			}
		}
		pObjectArray->Release();
	}
}

struct ShowWindowOnDesktopAction {
	int desktopNumber;
	int cmdShow;
};

LPWSTR _GetApplicationIdForHwnd(HWND hwnd) {
	if (hwnd == 0)
		return nullptr;
	IApplicationView* app = _GetApplicationViewForHwnd(hwnd);
	if (app != nullptr) {
		LPWSTR appId = new TCHAR[1024];
		app->GetAppUserModelId(&appId);
		app->Release();
		return appId;
	}
	return nullptr;
}

int DllExport IsPinnedWindow(HWND hwnd) {
	if (hwnd == 0)
		return -1;
	_RegisterService();
	IApplicationView* pView = _GetApplicationViewForHwnd(hwnd);
	BOOL isPinned = false;
	if (pView != nullptr) {
		pinnedApps->IsViewPinned(pView, &isPinned);
		pView->Release();
		if (isPinned) {
			return 1;
		}
		else {
			return 0;
		}
	}

	return -1;
}

void DllExport PinWindow(HWND hwnd) {
	if (hwnd == 0)
		return;
	_RegisterService();
	IApplicationView* pView = _GetApplicationViewForHwnd(hwnd);
	if (pView != nullptr) {
		pinnedApps->PinView(pView);
		pView->Release();
	}
}

void DllExport UnPinWindow(HWND hwnd) {
	if (hwnd == 0)
		return;
	_RegisterService();
	IApplicationView* pView = _GetApplicationViewForHwnd(hwnd);
	if (pView != nullptr) {
		pinnedApps->UnpinView(pView);
		pView->Release();
	}
}

int DllExport IsPinnedApp(HWND hwnd) {
	if (hwnd == 0)
		return -1;
	_RegisterService();
	LPWSTR appId = _GetApplicationIdForHwnd(hwnd);
	if (appId != nullptr) {
		BOOL isPinned = false;
		pinnedApps->IsAppIdPinned(appId, &isPinned);
		if (isPinned) {
			return 1;
		}
		else {
			return 0;
		}
	}
	return -1;
}

void DllExport PinApp(HWND hwnd) {
	if (hwnd == 0)
		return;
	_RegisterService();
	LPWSTR appId = _GetApplicationIdForHwnd(hwnd);
	if (appId != nullptr) {
		pinnedApps->PinAppID(appId);
	}
}

void DllExport UnPinApp(HWND hwnd) {
	if (hwnd == 0)
		return;
	_RegisterService();
	LPWSTR appId = _GetApplicationIdForHwnd(hwnd);
	if (appId != nullptr) {
		pinnedApps->UnpinAppID(appId);
	}
}

class _Notifications : public IVirtualDesktopNotification {
private:
	ULONG _referenceCount;
public:
	// Inherited via IVirtualDesktopNotification
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void ** ppvObject) override
	{
		// Always set out parameter to NULL, validating it first.
		if (!ppvObject)
			return E_INVALIDARG;
		*ppvObject = NULL;

		if (riid == IID_IUnknown || riid == IID_IVirtualDesktopNotification)
		{
			// Increment the reference count and return the pointer.
			*ppvObject = (LPVOID)this;
			AddRef();
			return S_OK;
		}
		return E_NOINTERFACE;
	}

	virtual ULONG STDMETHODCALLTYPE AddRef() override
	{
		return InterlockedIncrement(&_referenceCount);
	}

	virtual ULONG STDMETHODCALLTYPE Release() override
	{
		ULONG result = InterlockedDecrement(&_referenceCount);
		if (result == 0)
		{
			delete this;
		}
		return 0;
	}
	virtual HRESULT STDMETHODCALLTYPE VirtualDesktopCreated(IObjectArray* monitors,IVirtualDesktop * pDesktop) override
	{
		_PostMessageToListeners(VDA_VirtualDesktopCreated, GetDesktopNumber(pDesktop), 0);
		return S_OK;
	}
	virtual HRESULT STDMETHODCALLTYPE VirtualDesktopDestroyBegin(IObjectArray* monitors,IVirtualDesktop * pDesktopDestroyed, IVirtualDesktop * pDesktopFallback) override
	{
		_PostMessageToListeners(VDA_VirtualDesktopDestroyBegin, GetDesktopNumber(pDesktopDestroyed), GetDesktopNumber(pDesktopFallback));
		return S_OK;
	}
	virtual HRESULT STDMETHODCALLTYPE VirtualDesktopDestroyFailed(IObjectArray* monitors, IVirtualDesktop * pDesktopDestroyed, IVirtualDesktop * pDesktopFallback) override
	{
		_PostMessageToListeners(VDA_VirtualDesktopDestroyFailed, GetDesktopNumber(pDesktopDestroyed), GetDesktopNumber(pDesktopFallback));
		return S_OK;
	}
	virtual HRESULT STDMETHODCALLTYPE VirtualDesktopDestroyed(IObjectArray* monitors, IVirtualDesktop * pDesktopDestroyed, IVirtualDesktop * pDesktopFallback) override
	{
		_PostMessageToListeners(VDA_VirtualDesktopDestroyed, GetDesktopNumber(pDesktopDestroyed), GetDesktopNumber(pDesktopFallback));
		return S_OK;
	}
	virtual HRESULT STDMETHODCALLTYPE ViewVirtualDesktopChanged(IApplicationView * pView) override
	{
		_PostMessageToListeners(VDA_ViewVirtualDesktopChanged, 0, 0);
		return S_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE CurrentVirtualDesktopChanged(
		IObjectArray* monitors,
		IVirtualDesktop *pDesktopOld,
		IVirtualDesktop *pDesktopNew) override
	{
		// not sure how/why this happens but have crash dump where it did. 
		if (pDesktopOld == nullptr && pDesktopNew == nullptr) {
			return S_OK;
		}

		viewCollection->RefreshCollection();
		
		ChangeDesktopAction act;
		if (pDesktopOld != nullptr) {
			pDesktopOld->GetID(&act.oldDesktopGuid);
		}

		if (pDesktopNew != nullptr) {
			pDesktopNew->GetID(&act.newDesktopGuid);
		}

		_PostMessageToListeners(VDA_CurrentVirtualDesktopChanged, GetDesktopNumberById(act.oldDesktopGuid), GetDesktopNumberById(act.newDesktopGuid));
		return S_OK;
	}

    virtual HRESULT __stdcall VirtualDesktopIsPerMonitorChanged(BOOL isPerMonitor) override {
        return S_OK;
    }
    
    virtual HRESULT __stdcall VirtualDesktopMoved(IObjectArray* monitors, IVirtualDesktop * pDesktop, UINT64 oldIndex, UINT64 newIndex) override {
        return S_OK;
    }

	// Ben - W11 22H2 to next comment
	virtual HRESULT __stdcall VirtualDesktopRenamed(IVirtualDesktop* pDesktop, HSTRING name) override {
		//virtual HRESULT __stdcall VirtualDesktopNameChanged(IVirtualDesktop * pDesktop, HSTRING name) override {
        return S_OK;
    }
	// Ben - W11 22H2 from prev comment

    virtual HRESULT __stdcall VirtualDesktopWallpaperChanged(IVirtualDesktop * pDesktop, HSTRING name) override {
        return S_OK;
    }
};

void _RegisterDesktopNotifications() {
	_RegisterService();
	if (pDesktopNotificationService == nullptr) {
		return;
	}
	if (registeredForNotifications) {
		return;
	}
	_Notifications *nf = new _Notifications();
	HRESULT res = pDesktopNotificationService->Register(nf, &idNotificationService);
	if (SUCCEEDED(res)) {
		registeredForNotifications = TRUE;
	}
}

void DllExport RestartVirtualDesktopAccessor() {
	_RegisterService(TRUE);
	_RegisterDesktopNotifications();
}

void DllExport RegisterPostMessageHook(HWND listener, int messageOffset) {
	_RegisterService();

	listeners.insert(std::pair<HWND, int>(listener, messageOffset));
	if (listeners.size() != 1) {
		return;
	}
	_RegisterDesktopNotifications();
}

void DllExport UnregisterPostMessageHook(HWND hwnd) {
	_RegisterService();

	listeners.erase(hwnd);
	if (listeners.size() != 0) {
		return;
	}

	if (pDesktopNotificationService == nullptr) {
		return;
	}

	if (idNotificationService > 0) {
		registeredForNotifications = TRUE;
		pDesktopNotificationService->Unregister(idNotificationService);
	}
}

VOID _OpenDllWindow(HINSTANCE injModule) {
}
