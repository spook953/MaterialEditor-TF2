#pragma once
#include "TextEditor/TextEditor.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_impl_dx9.h"
#include "../SDK/SDK.h"

class CMaterial
{
public:
	std::string m_sName;
	TextEditor m_Text;
	bool m_bOpen;
	IMaterial *m_pMat;
	bool m_bPlayers = false;
	bool m_bArms = false;
	bool m_bWeapon = false;
};

class CEditor
{
private:
	bool m_bOpen = false;
	bool m_bUnload = false;

	IMaterial *m_pBaseMaterial = nullptr;
	IMaterial *m_pOverlayMaterial = nullptr;

private:
	IMaterial *CreateMaterial(const char *szInput);
	std::vector<CMaterial> m_vecMaterials;

private:
	bool m_bPlayers = false;
	bool m_bArms = false;
	bool m_bWeapon = false;

public:
	inline bool IsOpen() { return m_bOpen; };
	inline bool IsUnloading() { return m_bUnload; };

	inline IMaterial *GetBaseMaterial() { return m_pBaseMaterial; }
	inline IMaterial *GetOverlayMaterial() { return m_pOverlayMaterial; }

	inline bool ShouldRenderPlayers() { return m_bPlayers; }
	inline bool ShouldRenderArms() { return m_bArms; }
	inline bool ShouldRenderWeapon() { return m_bWeapon; }

	void Render(IDirect3DDevice9 *pDevice);
};

inline CEditor g_Editor;