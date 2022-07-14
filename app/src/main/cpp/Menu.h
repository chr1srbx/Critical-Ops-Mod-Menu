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


    struct Vec3
    {
        float x;
        float y;
        float z;
    };

    Vec3(*getTransform)(void* ptr);
    void* (*getLocalPlayer)(void* ptr);
//getTransform = (Vec3(*)(void*))getAbsoluteAddress(targetLibName, 0x0FF5E7);
//getLocalPlayer = (void*(*)(void*))getAbsoluteAddress(targetLibName, 0x0FF5E7);

    struct Ent
    {
        void* object{0};
        int health{0};
        int team{0};
        bool firing{0};
        bool initialized{0};
        Vec3 origin{0,0,0};

        // Check if Ent is local
        bool isLocal{ 0 };
    };

    class EntManager
    {
    public:
        Ent entList[32]{0};

        Ent localCharacter{ 0 };

        void Update(void* object)
        {
            bool present = 0;
            bool isLocal = 0;
            int entElement = -1;

            // Get the local character sus lol
            if ((*(void**)((uint64_t)object + 0x90) == getLocalPlayer(*(void**)((uint64_t)object + 0x38))))
            {
                localCharacter.object = object;
                isLocal = 1;
            }



            // Check if ent is in the list and find its element position
            for (int i = 0; i < 32; i++)
            {
                if (entList[i].object != object) continue;
                present = 1;
                entElement = i;
            }

            // If not add them to the list
            if (!present) entElement = Add(object);

            // Update its attributes
            if (entElement != -1)
            {
                //std::cout << "stuff updated!!\n";
                entList[entElement].health = getHealth(object);
                entList[entElement].team = getTeam(object);
                entList[entElement].firing = getFiring(object);
                entList[entElement].initialized = getInitialized(object);
                entList[entElement].origin = getOrigin(object);
                entList[entElement].isLocal = isLocal;
            }
        }
        int Add(void* object)
        {
            for (int i = 0; i < 32; i++)
            {
                if (entList[i].object != nullptr) continue;

                entList[i].object = object;
                return i;
            }
        }
        void Remove(void* object)
        {
            for (int i = 0; i < 32; i++)
            {
                if (entList[i].object != object || entList[i].object == nullptr) continue;

                // Shift the array point by 1,
                for (int j = 0; j < 32; j++)
                {
                    // Overflow protection
                    if ((i + j) > 31) continue;

                    // Checks if we are on the last one, and if so sets it to 0;
                    if ((i + j) == 31) entList[i + j].object == nullptr;

                    // Moves down the object to basically remove it
                    entList[i + j].object = entList[i + j + 1].object;
                }

            }
        }
        int getHealth(void* object)
        {
            return *(int*)((uint64_t)object + 0xC8);
        }
        int getTeam(void* object)
        {
            void* player = *(void**)((uint64_t)object + 0x90);
            void* teamBoxedVal = *(void**)((uint64_t)player + 0x88);
            return (int)*(byte*)((uint64_t)teamBoxedVal + 0x18); // was 0x18 in the old source no idea abt this at all
        }
        bool getFiring(void* object)
        {
            void* charData = *(void**)((uint64_t)object + 0x98);
            return *(bool*)((uint64_t)charData + 0x6C);
        }
        bool getInitialized(void* object)
        {
            return *(bool*)((uint64_t)object + 0xE8);
        }
        Vec3 getOrigin(void* object)
        {
            return getTransform(*(void**)((uint64_t)object + 0x70));
        }
        Vec3 getBonePos(void* object, int bone)
        {
            void* bodyPartsArray = *(void**)((uint64_t)object + 0x78);

            void* wantedBodyPart = nullptr;

            for (int i = 0; i < 10; i++)
            {
                if (*(int*)(((uint64_t)bodyPartsArray + i) + 0x18) != bone) continue;
                wantedBodyPart = (void*)((uint64_t)bodyPartsArray + i);
            }

            void* hitsphere = *(void**)((uint64_t)wantedBodyPart + 0x20);
            return *(Vec3*)((uint64_t)hitsphere + 0x18);
        }
    };



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