#include "Hooks/Hooks.h"
#include "Editor/Editor.h"

DWORD WINAPI MainThread(LPVOID lpParam)
{
	g_pMaterialSystem	= reinterpret_cast<IMaterialSystem *>(g_Interface.Get(L"materialsystem.dll", "VMaterialSystem081"));
	g_pModelRender		= reinterpret_cast<IVModelRender *>(g_Interface.Get(L"engine.dll", "VEngineModel016"));
	g_pSurface			= reinterpret_cast<ISurface *>(g_Interface.Get(L"vguimatsurface.dll", "VGUI_Surface030"));
	g_pInputSystem		= reinterpret_cast<IInputSystem *>(g_Interface.Get(L"inputsystem.dll", "InputSystemVersion001"));
	g_pModelInfo		= reinterpret_cast<IVModelInfo *>(g_Interface.Get(L"engine.dll", "VModelInfoClient006"));
	g_pClientEntityList = reinterpret_cast<IClientEntityList *>(g_Interface.Get(L"client.dll", "VClientEntityList003"));
	g_dwDirectXDevice	= **reinterpret_cast<DWORD **>(g_Pattern.Find(L"shaderapidx9.dll", L"A1 ? ? ? ? 50 8B 08 FF 51 0C") + 0x1);

	g_Hooks.Init();

	while (!g_Editor.IsUnloading())
		Sleep(100);
	
	g_Hooks.Exit();
	g_pSurface->SetCursorAlwaysVisible(false);

	FreeLibraryAndExitThread(static_cast<HMODULE>(lpParam), EXIT_SUCCESS);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		if (auto hMainThread = CreateThread(0, 0, MainThread, hinstDLL, 0, 0))
			CloseHandle(hMainThread);
	}

	return TRUE;
}