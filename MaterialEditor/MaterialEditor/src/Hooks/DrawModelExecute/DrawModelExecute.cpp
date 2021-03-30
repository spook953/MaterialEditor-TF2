#include "DrawModelExecute.h"
#include "../../Editor/Editor.h"

#pragma warning (disable : 26812)

void __stdcall Hooks::DrawModelExecute::Func(const DrawModelState_t &pState, const ModelRenderInfo_t &pInfo, matrix3x4 *pBoneToWorld)
{
	IMaterial *pBackupMat = nullptr;
	OverrideType_t nBackupOverrideType = {};
	g_pModelRender->GetMaterialOverride(&pBackupMat, &nBackupOverrideType);

	if (g_Editor.ShouldRenderPlayers())
	{
		if (pInfo.entity_index > 0 && pInfo.entity_index < 32)
		{
			if (const auto &pBase = g_Editor.GetBaseMaterial())
				g_pModelRender->ForcedMaterialOverride(pBase);
			
			Hook.CallOriginal<fn>()(g_pModelRender, pState, pInfo, pBoneToWorld);

			if (const auto &pOverlay = g_Editor.GetOverlayMaterial()) {
				g_pModelRender->ForcedMaterialOverride(pOverlay);
				Hook.CallOriginal<fn>()(g_pModelRender, pState, pInfo, pBoneToWorld);
			}

			g_pModelRender->ForcedMaterialOverride(pBackupMat);
			return;
		}
	}

	if (g_Editor.ShouldRenderArms())
	{
		IClientEntity *pEntity = g_pClientEntityList->GetClientEntity(pInfo.entity_index);

		if (pEntity)
		{
			std::string_view szModelName(g_pModelInfo->GetModelName(pInfo.pModel));

			if (szModelName.find("arm") != std::string_view::npos)
			{
				if (const auto &pBase = g_Editor.GetBaseMaterial())
					g_pModelRender->ForcedMaterialOverride(pBase);

				Hook.CallOriginal<fn>()(g_pModelRender, pState, pInfo, pBoneToWorld);

				if (const auto &pOverlay = g_Editor.GetOverlayMaterial()) {
					g_pModelRender->ForcedMaterialOverride(pOverlay);
					Hook.CallOriginal<fn>()(g_pModelRender, pState, pInfo, pBoneToWorld);
				}

				g_pModelRender->ForcedMaterialOverride(pBackupMat);
				return;
			}
		}
	}

	if (g_Editor.ShouldRenderWeapon())
	{
		IClientEntity *pEntity = g_pClientEntityList->GetClientEntity(pInfo.entity_index);

		if (!pEntity && pInfo.pModel)
		{
			std::string_view szModelName(g_pModelInfo->GetModelName(pInfo.pModel));

			if (szModelName.find("weapon") != std::string_view::npos
				&& szModelName.find("arrow") == std::string_view::npos
				&& szModelName.find("w_syringe") == std::string_view::npos
				&& szModelName.find("nail") == std::string_view::npos
				&& szModelName.find("shell") == std::string_view::npos
				&& szModelName.find("parachute") == std::string_view::npos
				&& szModelName.find("buffbanner") == std::string_view::npos
				&& szModelName.find("shogun_warbanner") == std::string_view::npos
				&& szModelName.find("targe") == std::string_view::npos
				&& szModelName.find("shield") == std::string_view::npos
				&& szModelName.find("repair_claw") == std::string_view::npos)
			{
				if (const auto &pBase = g_Editor.GetBaseMaterial())
					g_pModelRender->ForcedMaterialOverride(pBase);

				Hook.CallOriginal<fn>()(g_pModelRender, pState, pInfo, pBoneToWorld);

				if (const auto &pOverlay = g_Editor.GetOverlayMaterial()) {
					g_pModelRender->ForcedMaterialOverride(pOverlay);
					Hook.CallOriginal<fn>()(g_pModelRender, pState, pInfo, pBoneToWorld);
				}

				g_pModelRender->ForcedMaterialOverride(pBackupMat);
				return;
			}
		}
	}

	Hook.CallOriginal<fn>()(g_pModelRender, pState, pInfo, pBoneToWorld);
};

void Hooks::DrawModelExecute::Init()
{
	fn FN = reinterpret_cast<fn>(Utils::GetVFuncPtr(g_pModelRender, 19));
	Hook.Create(reinterpret_cast<void *>(FN), reinterpret_cast<void *>(Func));
}