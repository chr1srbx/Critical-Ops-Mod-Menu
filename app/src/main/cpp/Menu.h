#ifndef MENU
#define MENU
#include "Misc/Logging.h"
#include "Misc/ESP.h"
namespace Menu
{
    static bool recoil, gravity;

    void (*oldInaccuaracy)(std::uintptr_t instance);
    void Inaccuaracy(std::uintptr_t instance) {
        if (instance != NULL && gravity) {
            LOGE("I EXIST");
            std::uintptr_t chardata = *(std::uintptr_t*)(instance + 0x6C);
            float* gravity = (float*)(chardata + 0x50);
            LOGE("Gravity: %f", *gravity);
            *gravity = 9.81f / 3;
        }
        oldInaccuaracy(instance);
    }

    bool(*oldApplyRecoil)(std::uintptr_t instance);
    bool ApplyRecoil(std::uintptr_t instance){
        if(instance != NULL && recoil){
            LOGE("RECOIL");
            return false;
        }
        return oldApplyRecoil(instance);
    }

    int (*Screen_get_height)();

    int (*Screen_get_width)();
    ImVec4 color = ImVec4(1, 1, 1, 1);

    void DrawMenu()
    {
        static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            ImGui::Begin("Misako - Censorious Ops - chr1s#0002 - whozkiko#6046 - discord.gg/misako");
            if (ImGui::CollapsingHeader("Account Mods"))
            {
                  ImGui::Checkbox("Reecoil", &recoil);
                  ImGui::Checkbox("Innacuarracy", &gravity);
            }
            if (ImGui::CollapsingHeader("Player Mods"))
            {

            }
            if (ImGui::CollapsingHeader("Weapon Mods")){

            }
            ImGui::End();
        }
    }

    int SHITTYACHEIGHT(){
        return Screen_get_height();
    }

    int SHITTYACWIDTH(){
        return Screen_get_width();
    }
    void DrawImGui()
    {
        if (init && Screen_get_height)
        {
            LOGE("Screen_height : %d", Screen_get_width());
            LOGE("Screen_width : %d", Screen_get_height());
            ImGuiIO &io = ImGui::GetIO();
            static bool WantTextInputLast = false;
//            if (io.WantTextInput && !WantTextInputLast)
//                displayKeyboard(true);
//            WantTextInputLast = io.WantTextInput;
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplAndroid_NewFrame(Screen_get_width(),Screen_get_height());
            ImGui::NewFrame();
            DrawMenu();
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            io.KeysDown[io.KeyMap[ImGuiKey_UpArrow]] = false;
            io.KeysDown[io.KeyMap[ImGuiKey_DownArrow]] = false;
            io.KeysDown[io.KeyMap[ImGuiKey_LeftArrow]] = false;
            io.KeysDown[io.KeyMap[ImGuiKey_RightArrow]] = false;
            io.KeysDown[io.KeyMap[ImGuiKey_Tab]] = false;
            io.KeysDown[io.KeyMap[ImGuiKey_Enter]] = false;
            io.KeysDown[io.KeyMap[ImGuiKey_Backspace]] = false;
            io.KeysDown[io.KeyMap[ImGuiKey_PageUp]] = false;
            io.KeysDown[io.KeyMap[ImGuiKey_PageDown]] = false;
            io.KeysDown[io.KeyMap[ImGuiKey_Escape]] = false;
            io.KeysDown[io.KeyMap[ImGuiKey_Delete]] = false;
            io.KeysDown[io.KeyMap[ImGuiKey_Home]] = false;
            io.KeysDown[io.KeyMap[ImGuiKey_End]] = false;
            io.KeysDown[io.KeyMap[ImGuiKey_Insert]] = false;

            ImGui::EndFrame();
        }
    }
}
#endif MENU