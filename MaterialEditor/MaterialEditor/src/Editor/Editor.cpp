#include "Editor.h"

#pragma warning (disable : 26444)

IMaterial *CEditor::CreateMaterial(const char *szInput)
{
	static int nCreatedMats = 0;
	char szOut[512];
	sprintf_s(szOut, sizeof(szOut), "mat%i.vmt", nCreatedMats++);

	char szMaterial[512];
	sprintf_s(szMaterial, sizeof(szMaterial), szInput);

	CKeyValues *pVals = new CKeyValues;
	pVals->Initialize((char *)szOut);
	pVals->LoadFromBuffer(szOut, szMaterial);

	IMaterial *pCreated = g_pMaterialSystem->CreateMaterial(szOut, pVals);
	pCreated->IncrementReferenceCount();

	return pCreated;
}

void CEditor::Render(IDirect3DDevice9 *pDevice)
{
	static bool bInitImGui = false;

	if (!bInitImGui)
	{
		ImGui::CreateContext();
		ImGui_ImplWin32_Init(FindWindowA(0, "Team Fortress 2"));
		ImGui_ImplDX9_Init(pDevice);

		ImGui::GetStyle().FrameRounding = 1.0f;
		ImGui::GetStyle().GrabRounding = 1.0f;

		ImVec4 *colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_Text] = ImVec4(0.95f, 0.96f, 0.98f, 1.00f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.36f, 0.42f, 0.47f, 1.00f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
		colors[ImGuiCol_ChildBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
		colors[ImGuiCol_Border] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.12f, 0.20f, 0.28f, 1.00f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.09f, 0.12f, 0.14f, 1.00f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.09f, 0.12f, 0.14f, 0.65f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.39f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.18f, 0.22f, 0.25f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.09f, 0.21f, 0.31f, 1.00f);
		colors[ImGuiCol_CheckMark] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.37f, 0.61f, 1.00f, 1.00f);
		colors[ImGuiCol_Button] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
		colors[ImGuiCol_Header] = ImVec4(0.20f, 0.25f, 0.29f, 0.55f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_Separator] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
		colors[ImGuiCol_Tab] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
		colors[ImGuiCol_TabHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
		colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
		colors[ImGuiCol_TabUnfocused] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
		colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
		colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
		colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

		bInitImGui = true;
	}

	if (GetAsyncKeyState(VK_INSERT) & 1)
		g_pSurface->SetCursorAlwaysVisible(m_bOpen = !m_bOpen);

	if (m_bOpen)
	{
		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		if (ImGui::Begin("Editor", nullptr, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse))
		{
			ImGui::SetWindowSize(ImVec2(300, 300), ImGuiCond_Once);

			ImGui::PushItemWidth(200);

			if (ImGui::Button("Reset")) {
				m_pBaseMaterial = nullptr;
				m_pOverlayMaterial = nullptr;
			}

			ImGui::SameLine();

			if (ImGui::Button("Unload"))
				m_bUnload = true;

			char input[20] = { '\0' };

			if (ImGui::InputText("Add", input, 20, ImGuiInputTextFlags_::ImGuiInputTextFlags_EnterReturnsTrue))
			{
				std::string input_str = std::string(input);

				auto AlreadyExists = [&]() -> bool
				{
					for (const auto &mat : m_vecMaterials)
					{
						if (!input_str.compare(mat.m_sName))
							return true;
					}

					return false;
				};

				if (input_str.length() > 0 && !AlreadyExists())
					m_vecMaterials.push_back({ input_str });
			}

			if (ImGui::ListBoxHeader("Materials"))
			{
				for (auto &mat : m_vecMaterials)
				{
					if (ImGui::Selectable(mat.m_sName.c_str()))
						mat.m_bOpen = true;
				}

				ImGui::ListBoxFooter();
			}

			ImGui::Checkbox("Players", &m_bPlayers);
			ImGui::SameLine();
			ImGui::Checkbox("Arms", &m_bArms);
			ImGui::SameLine();
			ImGui::Checkbox("Weapons", &m_bWeapon);

			ImGui::PopItemWidth();

			ImGui::End();
		}

		for (auto &mat : m_vecMaterials)
		{
			if (!mat.m_bOpen)
				continue;

			if (ImGui::Begin(mat.m_sName.c_str(), nullptr, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse))
			{
				if (ImGui::Button("Set as Base"))
				{
					m_pBaseMaterial = CreateMaterial(mat.m_Text.GetText().c_str());

					if (m_pOverlayMaterial == mat.m_pMat)
						m_pOverlayMaterial = nullptr;

					mat.m_pMat = m_pBaseMaterial;
				}
				
				ImGui::SameLine();

				if (ImGui::Button("Set as Overlay"))
				{
					m_pOverlayMaterial = CreateMaterial(mat.m_Text.GetText().c_str());

					if (m_pBaseMaterial == mat.m_pMat)
						m_pBaseMaterial = nullptr;

					mat.m_pMat = m_pOverlayMaterial;
				}

				if (ImGui::Button("Close"))
					mat.m_bOpen = false;

				ImGui::SameLine();

				if (ImGui::Button("Remove"))
				{
					for (size_t n = 0; n < m_vecMaterials.size(); n++)
					{
						std::string sName = m_vecMaterials[n].m_sName;

						if (!sName.compare(mat.m_sName)) {
							m_vecMaterials.erase(m_vecMaterials.begin() + n);
							break;
						}
					}

					if (mat.m_pMat == m_pBaseMaterial)
						m_pBaseMaterial = nullptr;

					if (mat.m_pMat == m_pOverlayMaterial)
						m_pOverlayMaterial = nullptr;

					continue;
				}

				mat.m_Text.Render("Vars", ImVec2(-1, -1));
				
				ImGui::End();
			}
		}
		
		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
	}
}