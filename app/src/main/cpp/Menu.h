#ifndef MENU
#define MENU
#include "Misc/Logging.h"
#include "Misc/ESP.h"

namespace Mem
{
    std::uintptr_t Read(std::uintptr_t o1)
    {
        return *reinterpret_cast<std::uintptr_t*>(o1);
    }
}
namespace fields
{
    namespace CharacterData
    {
        std::uint32_t aim = 0x8;
        std::uint32_t transform = 0x20;
        std::uint32_t m_moveInput = 0x40;
        std::uint32_t state = 0x48;
        std::uint32_t m_aimPunchY = 0x50;
        std::uint32_t m_aimPunchX = 0x54;
        std::uint32_t slowDown = 0x58;
        std::uint32_t m_speedFactor = 0x5C;
        std::uint32_t m_ticksRecovered = 0x60;
        std::uint32_t m_firing = 0x64;
        std::uint32_t m_weaponSettings = 0x68;
        std::uint32_t m_characterSettings = 0x6C;
        std::uint32_t m_wpn = 0x70;
        std::uint32_t m_lastShotWpn = 0x74;
        std::uint32_t m_armorMoveSpeedReductionRates = 0x78;
    }
    namespace AimData
    {
        std::uint32_t aimSpread = 0x0;
        std::uint32_t rawSpread = 0x4;
        std::uint32_t rawRecoil = 0x8;
        std::uint32_t recoilY = 0xC;
        std::uint32_t recoilX = 0x10;
        std::uint32_t inaccuracy = 0x14;
    }
    namespace Grenade
    {
        std::uint32_t IDk__BackingField = 0x8;
        std::uint32_t ThrowerIDk__BackingField = 0xC;
        std::uint32_t Weaponk__BackingField = 0x10;
        std::uint32_t ProxyIDk__BackingField = 0x14;
        std::uint32_t Positionk__BackingField = 0x18;
        std::uint32_t TeamIndexk__BackingField = 0x24;
        std::uint32_t Actionk__BackingField = 0x28;
        std::uint32_t HasExplodedk__BackingField = 0x2C;
        std::uint32_t m_characterExposureValues = 0x30;
    }
    namespace Weapon
    {
        std::uint32_t SimPlayerIDk__BackingField = 0x8; //=
        std::uint32_t Expirationk__BackingField = 0xC; //=
        std::uint32_t AmmoInClipk__BackingField = 0x10; //=
        std::uint32_t AmmoInInventoryk__BackingField = 0x14; //=
        std::uint32_t m_ID = 0x18; //int
        std::uint32_t m_skinID = 0x1C; //int
        std::uint32_t m_carrier = 0x20; //Character
        std::uint32_t m_shotTickData = 0x24; //ShotTickData
        std::uint32_t m_weaponDefData = 0x28; //WeaponDefData
        std::uint32_t m_position = 0x2C; //Vector3
        std::uint32_t m_rotation = 0x38; //Vector3
        std::uint32_t m_stop = 0x44; //bool
        std::uint32_t m_velocity = 0x48; //Vector3
        std::uint32_t m_angularVelocity = 0x54; //Vector3
    }
    namespace WeaponDefData
    {
        std::uint32_t Name = 0x8; //string
        std::uint32_t ID = 0xC; //int
        std::uint32_t LocalizationKey = 0x10; //string
        std::uint32_t LocalizationGroup = 0x14; //string
        std::uint32_t WeaponType = 0x18; //WeaponType
        std::uint32_t WeaponSlot = 0x1C; //WeaponSlot
        std::uint32_t WeaponCategory = 0x20; //WeaponCategory
        std::uint32_t ReloadType = 0x24; //ReloadType
        std::uint32_t CanBuy = 0x28; //bool
        std::uint32_t BuyPrice = 0x2C; //int
        std::uint32_t MoneyRewardMultiplier = 0x30; //int
        std::uint32_t MaxDamage = 0x34; //float
        std::uint32_t MinDamage = 0x38; //float
        std::uint32_t Force = 0x3C; //float
        std::uint32_t DropOffStartRange = 0x40; //float
        std::uint32_t DropOffEndRange = 0x44; //float
        std::uint32_t Range = 0x48; //float
        std::uint32_t FireRate = 0x4C; //float
        std::uint32_t Burst = 0x50; //int
        std::uint32_t BurstSpread = 0x54; //float
        std::uint32_t ClipSize = 0x58; //int
        std::uint32_t ExtraClips = 0x5C; //int
        std::uint32_t MaxClips = 0x60; //int
        std::uint32_t WallPenetration = 0x64; //WallPenetration
        std::uint32_t ArmorPenetration = 0x68; //ArmorPenetration
        std::uint32_t ReloadTime = 0x6C; //float
        std::uint32_t DeployTime = 0x70; //float
        std::uint32_t PrepareTime = 0x74; //float
        std::uint32_t DryfireRate = 0x78; //float
        std::uint32_t ConsumesAmmo = 0x7C; //bool
        std::uint32_t AimType = 0x80; //AimType
        std::uint32_t AimFovIsVertical = 0x84; //bool
        std::uint32_t AimFov = 0x88; //float
        std::uint32_t AimViewFov = 0x8C; //float
        std::uint32_t AimSpeed = 0x90; //float
        std::uint32_t AimMuzzleEffectsScale = 0x94; //float
        std::uint32_t AimAfterReload = 0x98; //bool
        std::uint32_t MoveSpeedFactor = 0x9C; //float
        std::uint32_t AimMoveSpeedFactor = 0xA0; //float
        std::uint32_t Inaccuracy = 0xA4; //WeaponFactors
        std::uint32_t InaccuracyWhenAiming = 0xA8; //WeaponFactors
        std::uint32_t SpreadCurve = 0xAC; //Curve
        std::uint32_t SpreadFactor = 0xB0; //float
        std::uint32_t SpreadPerShot = 0xB4; //float
        std::uint32_t SpreadRecover = 0xB8; //float
        std::uint32_t RecoilCurveY = 0xBC; //Curve
        std::uint32_t RecoilYFactor = 0xC0; //float
        std::uint32_t RecoilCurveX = 0xC4; //Curve
        std::uint32_t RecoilXFactor = 0xC8; //float
        std::uint32_t RecoilPerShot = 0xCC; //float
        std::uint32_t RecoilRecover = 0xD0; //float
        std::uint32_t ShootingRecoverFactor = 0xD4; //float
        std::uint32_t ShakeFactor = 0xD8; //float
        std::uint32_t ReloadInsertTime = 0xDC; //float
        std::uint32_t ReloadFinishTime = 0xE0; //float
        std::uint32_t BurstFireShots = 0xE4; //int
        std::uint32_t BurstFireCooldown = 0xE8; //float
        std::uint32_t GrenadeType = 0xEC; //GrenadeType
        std::uint32_t GrenadeStartTime = 0xF0; //float
        std::uint32_t GrenadeThrowTime = 0xF4; //float
        std::uint32_t GrenadeInstantiateTime = 0xF8; //float
        std::uint32_t GrenadeExplodeTime = 0xFC; //float
        std::uint32_t GrenadeLifeTime = 0x100; //float
        std::uint32_t GrenadeThrowVelocity = 0x104; //float
        std::uint32_t ExplodeOnImpact = 0x108; //bool
        std::uint32_t ImpactExplosionAngle = 0x10C; //float
        std::uint32_t ImpactExplosionSpeed = 0x110; //float
        std::uint32_t GrenadeBounciness = 0x114; //float
        std::uint32_t GrenadeFrictionFactor = 0x118; //float
    }
}
namespace Menu
{
    namespace options
    {
        static bool recoil, gravity, spread, ammo_move, preparetime, shake;
        static float firerate, aimfov, reloadtime, fov;
        static int burstshots;

    }

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

    void (*oldFetchFollowedCharacterTeamIndex)(void* instance);
    void FetchFollowedCharacterTeamIndex(void* instance) {
        if (instance != NULL) {
            LOGE("FetchFollowedCharacterTeamIndex");
            LOGE("TeamIndex (int): %d", (int*)((uint64_t)instance + 0x38));

            int result = -1;

            *(int*)((uint64_t)instance + 0x38) = -1;

            LOGE("2 TeamIndex (int): %d", *(int*)((uint64_t)instance + 0x38));
        }
        oldFetchFollowedCharacterTeamIndex(instance);
    }

    bool(*oldApplyRecoil)(std::uintptr_t instance);
    bool ApplyRecoil(std::uintptr_t instance){
        if(instance != NULL && options::recoil){
            return false;
        }
        return oldApplyRecoil(instance);
    }

    bool(*oldApplySpread)(std::uintptr_t instance);
    bool ApplySpread(std::uintptr_t instance){
        if(instance != NULL && options::spread){
            return false;
        }
        return oldApplyRecoil(instance);
    }
    float (*get_GravityApproachFactor_old)(void *instance);
    float get_GravityApproachFactor_hook(void* instance)
    {
        float ret = get_GravityApproachFactor_old(instance);
        LOGE("CriticalOps MiddleMan [GRAVITYAPPROACHFACTOR]: %f", ret);
        ret = ret * 2;
        return ret;
    }

    void (*oldFire)(void* instance, std::uintptr_t wpn);
    void Fire(void* instance, std::uintptr_t wpn){
        if(instance != nullptr){
            if(options::firerate != NULL)
                *(float*) Mem::Read(wpn + fields::WeaponDefData::FireRate) = options::firerate;
            if(options::aimfov != NULL)
                *(float*) Mem::Read(wpn + fields::WeaponDefData::AimViewFov) = options::aimfov;
            if(options::burstshots != NULL)
                *(int*) Mem::Read(wpn + fields::WeaponDefData::BurstFireShots) = options::burstshots;
            if(options::ammo_move)
            {
                options::ammo_move = false;
                *(int*) Mem::Read(wpn + fields::WeaponDefData::ClipSize) = *(int*) Mem::Read(wpn + fields::WeaponDefData::ClipSize) * *(int*) Mem::Read(wpn + fields::WeaponDefData::ExtraClips);
                *(int*) Mem::Read(wpn + fields::WeaponDefData::ExtraClips) = 0;
                *(int*) Mem::Read(wpn + fields::WeaponDefData::MaxClips) = 0;
            }

            if(options::shake)
                *(float*) Mem::Read(wpn + fields::WeaponDefData::ShakeFactor) = 0;

            if(options::preparetime)
                *(float*) Mem::Read(wpn + fields::WeaponDefData::PrepareTime) = 0;

            if(options::reloadtime != NULL){
                *(float*) Mem::Read(wpn + fields::WeaponDefData::ReloadTime) = options::reloadtime;
                *(float*) Mem::Read(wpn + fields::WeaponDefData::ReloadFinishTime) = options::reloadtime;
                *(float*) Mem::Read(wpn + fields::WeaponDefData::ReloadInsertTime) = options::reloadtime;
            }

            if(options::fov != NULL)
                *(float*) Mem::Read(wpn + fields::WeaponDefData::AimFov) = options::fov;
        }
    }

    int (*Screen_get_height)();

    int (*Screen_get_width)();
    ImVec4 color = ImVec4(1, 1, 1, 1);

    void DrawMenu()
    {
        static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            ImGui::Begin("Misako - Critical Ops 1.33.0f1870 - chr1s#0002 - whozkiko#6046 - discord.gg/misako");
            if (ImGui::CollapsingHeader("Weapons Mods"))
            {
                  ImGui::Checkbox("No Recoil", &options::recoil);
                  ImGui::SameLine();
                  ImGui::Checkbox("No Spread", &options::spread);
                  ImGui::SameLine();
                  ImGui::Checkbox("No Shake", &options::shake);
                  ImGui::SameLine();
                  ImGui::Checkbox("No Equip Time", &options::preparetime);
                  ImGui::SliderFloat("Reload Time", &options::reloadtime, 0.0f, 60.0f);
                  ImGui::SliderFloat("FireRate", &options::firerate, 0.0f, 60.0f);
                  ImGui::SliderFloat("FOV Scope", &options::aimfov, 0.0f, 360.0f);
                  ImGui::SliderInt("Burst Shots in 1 Fire", &options::burstshots, 0, 120);
                  if(ImGui::Button("No Reload"))
                  {
                      options::ammo_move = true;
                  }
            }
            if (ImGui::CollapsingHeader("Player Mods"))
            {

            }
            if (ImGui::CollapsingHeader("Visual Mods"))
            {
                ImGui::SliderFloat("FOV", &options::fov, 0.0f, 360.0f);
            }
            if (ImGui::CollapsingHeader("Misc Mods")){

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