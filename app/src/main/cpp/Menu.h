#ifndef MENU
#define MENU
#include "Misc/Logging.h"
#include "Misc/ESP.h"
#include "Memory/MemoryPatch.h"

namespace Menu
{
    namespace options
    {
        static bool recoil, firerateb, spread, ammo_move, preparetime, shake, retardbots, bomb, radar, wallbang, burstshots, aimpunch;
        static float aimfov, reloadtime, fov, speed, fly;
        static int firerate;
    }

    struct GlobalPatches {
        MemoryPatch bomb, wallbang, radar;
    }gPatches;

    /*void (*oldupdateGraphics)(void* instance, std::uintptr_t v1);
    void updateGraphics(void* instance, std::uintptr_t v1) {
        if (instance != NULL) {
            LOGE("updateGraphics has been called.");
            std::uintptr_t profile = *reinterpret_cast<std::uintptr_t*>((uint64_t)instance + 0x14);

            int screenScale = *reinterpret_cast<int*>(profile + 0x24);
            LOGE("Profile: %d", screenScale);

            //*screenScale = 1.0;
        }
        oldupdateGraphics(instance, v1);
    }*/

    void (*oldRequestBanCreate)(void* instance, const char* Username, int Time, const char* banMessage);
    void RequestBanCreate(void* instance, const char* Username, int Time, const char* banMessage) {
        if (instance != NULL) {
            LOGE("A ban request has been made.");
            LOGE("Instance: %p", (uintptr_t)instance);
            LOGE("Username: %s", Username);
            LOGE("Time: %d", Time);
            LOGE("banMessage: %s", banMessage);
        }
        oldRequestBanCreate(instance, Username, Time, banMessage);
    }

    bool(*oldApplyRecoil)(std::uintptr_t instance);
    bool ApplyRecoil(std::uintptr_t instance){
        if(instance != NULL && options::recoil){
            return false;
        }
        return oldApplyRecoil(instance);
    }

    bool(*oldRecoverSpread)(std::uintptr_t instance);
    bool RecoverSpread(std::uintptr_t instance){
        if(instance != NULL && options::spread){
            return false;
        }
        return oldRecoverSpread(instance);
    }

    bool(*oldApplyAimpunch)(std::uintptr_t instance);
    bool ApplyAimpunch(std::uintptr_t instance){
        if(instance != NULL && options::aimpunch){
            return false;
        }
        return oldApplyAimpunch(instance);
    }

    bool (*oldFire)(void* instance);
    bool FireRate(void* instance){
        if(instance != nullptr & options::firerate != NULL){
            *(float*)((uint64_t) instance + 0x20) = 0;
        }
        return oldFire(instance);
    }

    bool(*oldBurstMoveNext)(std::uintptr_t instance);
    bool BurstMoveNext(std::uintptr_t instance){
        if(instance != NULL && options::burstshots){
            *(int*)((uint64_t) instance + 0x24) = 30;
        }
        return oldBurstMoveNext(instance);
    }

    bool(*oldIsValidTarget)(std::uintptr_t instance);
    bool IsValidTarget(std::uintptr_t instance){
        if(instance != NULL && options::retardbots){
             return false;
        }
        return oldIsValidTarget(instance);
    }

    float (*oldfieldOfView)(void* instance);
    float fieldOfView(void* instance){
        if(instance != nullptr & options::fov != NULL){
            return options::fov;
        }
        return oldfieldOfView(instance);
    }

    bool(*oldWeaponUpdate)(std::uintptr_t instance);
    bool WeaponUpdate(std::uintptr_t instance){
        if(instance != NULL){
            if(options::ammo_move){
                *(int*)((uint64_t) instance + 0x34) = *(int*)((uint64_t) instance + 0x34) + *(int*)((uint64_t) instance + 0x38);
                *(int*)((uint64_t) instance + 0x38) = 0;
                options::ammo_move = false;
            }
        }
        return oldWeaponUpdate(instance);
    }

    float (*oldCharacterMaxSpeed)(void* instance);
    float CharacterMaxSpeed(void* instance){
        if(instance != nullptr & options::speed != NULL){
            return options::speed;
        }
        return oldCharacterMaxSpeed(instance);
    }

    float (*oldget_height)(void* instance);
    float get_height(void* instance){
        if(instance != nullptr & options::fly != NULL){
            return options::fly;
        }
        return oldget_height(instance);
    }

    int (*Screen_get_height)();

    int (*Screen_get_width)();
    ImVec4 color = ImVec4(1, 1, 1, 1);

    void DrawMenu()
    {
        static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            ImGui::Begin("Misako - Critical Ops 1.33.0f1870 - chr1s#0002 - discord.gg/misako");
            if (ImGui::CollapsingHeader("Weapons Mods"))
            {
                  ImGui::Checkbox("No Recoil", &options::recoil);
                  ImGui::SameLine();
                  ImGui::Checkbox("No Spread", &options::spread);
                  ImGui::SameLine();
                  ImGui::Checkbox("No Equip Time", &options::preparetime);
                  ImGui::SliderInt("FireRate", &options::firerate, 0, 60);
                  ImGui::Checkbox("Wall-bang", &options::wallbang);
                  ImGui::Checkbox("Burst Shots in 1 Fire", &options::burstshots);
                  if(ImGui::Button("No Reload"))
                  {
                      options::ammo_move = true;
                  }
                if(options::wallbang){
                    gPatches.wallbang.Modify();
                }
                else{
                    gPatches.wallbang.Restore();
                }
            }
            if (ImGui::CollapsingHeader("Player Mods"))
            {
                ImGui::SliderFloat("Speed", &options::speed, 0.0f, 30.0f);
                ImGui::SliderFloat("Fly", &options::fly, 0.0f, 20.0f);

            }
            if (ImGui::CollapsingHeader("Visual Mods"))
            {
                ImGui::SliderFloat("FOV", &options::fov, 0.0f, 360.0f);
                ImGui::SameLine();
                ImGui::Checkbox("No Aim-Punch", &options::aimpunch);
                ImGui::SameLine();
                ImGui::Checkbox("Radar", &options::radar);

                if(options::radar){
                    gPatches.radar.Modify();
                }
                else{
                    gPatches.radar.Restore();
                }
            }
            if (ImGui::CollapsingHeader("Misc Mods")){
                ImGui::Checkbox("Dumb Bots", &options::retardbots);
                ImGui::SameLine();
                ImGui::Checkbox("No Smoke/Flash/Grenade", &options::bomb);
                if(options::bomb){
                    gPatches.bomb.Modify();
                }
                else{
                    gPatches.bomb.Restore();
                }
            }
            ImGui::End();
        }
    }

    void DrawImGui()
    {
        if (init && Screen_get_height)
        {
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