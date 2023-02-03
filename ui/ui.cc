#include "ui.hh"
#include "../globals.hh"
#include "../imgui/imgui.h"
#include "../imgui/imgui_internal.h"
#include <d3dx9.h>
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

//Data
static LPDIRECT3D9              g_pD3D = NULL;
static LPDIRECT3DDEVICE9        g_pd3dDevice = NULL;
static D3DPRESENT_PARAMETERS    g_d3dpp = {};
static int listbox_item_current = 0;

void ui::render() {
    if (!globals.active) return;

    ImGui::SetNextWindowPos(ImVec2(window_pos.x, window_pos.y), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(window_size.x, window_size.y));
    ImGui::SetNextWindowBgAlpha(1.0f);

    ImDrawList* drawList = ImGui::GetForegroundDrawList();
    float thickness = ImGui::GetTextLineHeight() * 2.0f;

    if (idk::Tab == 0)
    {
        ImGui::Begin(window_title, &globals.active, window_flags);
        {
            ImGui::SetCursorPos(ImVec2(10, 27));
            ImGui::BeginChild(("##Boxlogin"), ImVec2(250, 175), true);
            {

                ImGui::SetCursorPos(ImVec2(45, 50));
                ImGui::InputText("##Username", globals.user_name, IM_ARRAYSIZE(globals.user_name));

                ImGui::SetCursorPos(ImVec2(45, 80));
                ImGui::InputText("##Password", globals.pass_word, IM_ARRAYSIZE(globals.pass_word), ImGuiInputTextFlags_Password);

                ImGui::SetCursorPos(ImVec2(85, 120));
                if (ImGui::Button("Login", ImVec2(75, 19))) {
                    idk::Tab = 1;
                }
            }ImGui::EndChild();
        }
    }

    else if (idk::Tab == 1)
    {
        ImGui::SetNextWindowPos(ImVec2(window_pos.x, window_pos.y), ImGuiCond_Once);
        ImGui::SetNextWindowSize(ImVec2(ui2::window_size2.x, ui2::window_size2.y));
        ImGui::SetNextWindowBgAlpha(1.0f);

        ImGui::Begin(ui2::window_title2, &globals.active, ui2::window_flags2);
        { 
             ImGui::SetCursorPos(ImVec2(10, 27));
             ImGui::BeginChild(("##Box"), ImVec2(380, 202), true);
             {
                 int width = 100;
                 static int selected_item = 0;

                 ImGui::SetCursorPos(ImVec2(250 / 2 - width / 2, 80));
                 ImGui::Combo("##Games", &selected_item, "csgo [alpha]\0csgo [beta]\0", 2);

             }ImGui::EndChild();

             ImGui::SetCursorPos(ImVec2(55, 234));
             if (ImGui::Button("Load", ImVec2(280, 30))) {

             }
        }
    }
    ImGui::End();
}

void ui::init(LPDIRECT3DDEVICE9 device) {
    dev = device;

    ImGuiStyle& style = ImGui::GetStyle();

    style.WindowPadding = ImVec2(6, 6);
    style.FramePadding = ImVec2(4, 3);
    style.ItemSpacing = ImVec2(8, 4);
    style.ItemInnerSpacing = ImVec2(4, 4);
    style.IndentSpacing = 21;
    style.ScrollbarSize = 1;
    style.GrabMinSize = 1;
    style.WindowBorderSize = 1;
    style.ChildBorderSize = 1;
    style.PopupBorderSize = 1;
    style.FrameBorderSize = 1;
    style.WindowRounding = 0;
    style.ChildRounding = 3;
    style.FrameRounding = 6; 
    style.PopupRounding = 9;
    style.ScrollbarRounding = 9;
    style.GrabRounding = 9;
    style.SelectableTextAlign = ImVec2(0.5f, 0.5f);


    style.Colors[ImGuiCol_Text] = ImVec4(1.000000f, 0.999990f, 0.999990f, 1.000000f);
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.600000f, 0.600000f, 0.600000f, 1.000000f);
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.150000f, 0.150000f, 0.150000f, 0.150000f);
    style.Colors[ImGuiCol_PopupBg] = ImVec4(0.110000f, 0.110000f, 0.140000f, 0.920000f);
    style.Colors[ImGuiCol_Border] = ImVec4(0.430000f, 0.430000f, 0.430000f, 0.430000f);
    style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.170000f, 0.170000f, 0.170000f, 0.170000f);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.250000f, 0.250000f, 0.250000f, 0.250000f);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.250000f, 0.250000f, 0.250000f, 0.250000f);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.250000f, 0.250000f, 0.250000f, 0.250000f);
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.150000f, 0.150000f, 0.150000f, 0.150000f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.150000f, 0.150000f, 0.150000f, 0.150000f);
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.150000f, 0.150000f, 0.150000f, 0.150000f);
    style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.400000f, 0.400000f, 0.550000f, 0.800000f);
    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.200000f, 0.250000f, 0.300000f, 0.600000f);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.622543f, 0.622543f, 0.622549f, 0.300000f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.783353f, 0.783354f, 0.799020f, 0.400000f);
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.446074f, 0.446074f, 0.446078f, 0.600000f);
    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.900000f, 0.900000f, 0.900000f, 0.500000f);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(1.000000f, 1.000000f, 1.000000f, 0.300000f);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.460780f, 0.460780f, 0.460784f, 0.600000f);
    style.Colors[ImGuiCol_Button] = ImVec4(0.250000f, 0.250000f, 0.250000f, 0.250000f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.370000f, 0.370000f, 0.370000f, 0.370000f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.370000f, 0.370000f, 0.370000f, 0.370000f);
    style.Colors[ImGuiCol_Header] = ImVec4(0.383637f, 0.392157f, 0.380623f, 0.450000f);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.634131f, 0.634131f, 0.637255f, 0.800000f);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.595108f, 0.595108f, 0.598039f, 0.800000f);
    style.Colors[ImGuiCol_Separator] = ImVec4(0.500000f, 0.500000f, 0.500000f, 0.600000f);
    style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.629566f, 0.629566f, 0.642157f, 1.000000f);
    style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.396891f, 0.396891f, 0.406863f, 1.000000f);
    style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.000000f, 1.000000f, 1.000000f, 0.160000f);
    style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.780000f, 0.820000f, 1.000000f, 0.600000f);
    style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.780000f, 0.820000f, 1.000000f, 0.900000f);
    style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.000000f, 0.000000f, 1.000000f, 0.350000f);
    style.Colors[ImGuiCol_DragDropTarget] = ImVec4(1.000000f, 1.000000f, 0.000000f, 0.900000f);
    ImGui::GetStyle().WindowTitleAlign = ImVec2(0.5f, 0.5f);


	if (window_pos.x == 0) {
		RECT screen_rect{};
		GetWindowRect(GetDesktopWindow(), &screen_rect);
		screen_res = ImVec2(float(screen_rect.right), float(screen_rect.bottom));
		window_pos = (screen_res - window_size) * 0.5f;

	}
}
