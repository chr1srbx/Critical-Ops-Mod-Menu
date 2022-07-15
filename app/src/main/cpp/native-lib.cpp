#include <EGL/egl.h> // need to make a common.h that contains all these headers cuz this is nasty
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES2/gl2platform.h>
#include <fstream>
#include <sstream>
#include "nlohmann/json.hpp"
#include "http/cpr/cpr.h"
#include "Misc/Logging.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_android.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "Obfuscation/Obfuscate.h"
#include <stdio.h>
#include <android/native_window_jni.h>
#include <jni.h>
#include <string>
#include <unistd.h>
#include <pthread.h>
#include <dlfcn.h>
#include "Misc/JNIStuff.h"
#include "Misc/FileWrapper.h"
#include "Misc/Utils.h"
#include "ByNameModding/BNM.hpp"
#include "Obfuscation/Custom_Obfuscate.h"
#include "Unity/Unity.h"
#include "Misc/FunctionPointers.h"
#include "Hooking/Hooks.h"
#include "Misc/ImGuiStuff.h"
#include "Menu.h"
#include "Hooking/JNIHooks.h"
#include "Memory/MemoryPatch.h"
// the private version held by certain polarmodders has image loading and a lot more

EGLBoolean (*old_eglSwapBuffers)(...);
EGLBoolean new_eglSwapBuffers(EGLDisplay _display, EGLSurface _surface) {
    SetupImGui();
    Menu::DrawImGui();

    return old_eglSwapBuffers(_display, _surface);
}
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void * reserved)
{
    jvm = vm;
    JNIEnv *env;
    vm->GetEnv((void **) &env, JNI_VERSION_1_6);
    UnityPlayer_cls = env->FindClass(OBFUSCATE("com/unity3d/player/UnityPlayer"));
    UnityPlayer_CurrentActivity_fid = env->GetStaticFieldID(UnityPlayer_cls,
                                                            OBFUSCATE("currentActivity"),
                                                            OBFUSCATE("Landroid/app/Activity;"));
    hook((void *) env->functions->RegisterNatives, (void *) hook_RegisterNatives,
         (void **) &old_RegisterNatives);

    return JNI_VERSION_1_6;
}
bool isHooked = false;



void Patches(){
    Menu::gPatches.radar = MemoryPatch::createWithHex("libil2cpp.so", 0x7DEFF0, "03 00 A0 E3 1E FF 2F E1");
    Menu::gPatches.wallbang = MemoryPatch::createWithHex("libil2cpp.so", 0x618BA0, "00 00 A0 E3 1E FF 2F E1");
    Menu::gPatches.bomb = MemoryPatch::createWithHex("libil2cpp.so", 0x77F2E8, "00 00 A0 E3 1E FF 2F E1");
}

void *hack_thread(void *)
{
    using namespace BNM;
    do {
        sleep(1);
    } while (!Il2cppLoaded());
    AttachIl2Cpp(); // this is required when you use bynamemodding functions
    Menu::Screen_get_height = (int (*)()) OBFUSCATE_BYNAME_METHOD("UnityEngine", "Screen", "get_height",0);
    Menu::Screen_get_width = (int (*)()) OBFUSCATE_BYNAME_METHOD("UnityEngine", "Screen", "get_width", 0);
    DobbyHook((void*)getAbsoluteAddress("libil2cpp.so", 0xD03718), (void*) Menu::ApplyRecoil, (void**)&Menu::oldApplyRecoil);
    DobbyHook((void*)getAbsoluteAddress("libil2cpp.so", 0xD0385C), (void*) Menu::RecoverSpread, (void**)&Menu::oldRecoverSpread);
    DobbyHook((void*)getAbsoluteAddress("libil2cpp.so", 0xBD1098), (void*) Menu::FireRate, (void**)&Menu::oldFire);
    DobbyHook((void*)getAbsoluteAddress("libil2cpp.so", 0xBD0900), (void*) Menu::WeaponUpdate, (void**)&Menu::oldWeaponUpdate);
    DobbyHook((void*)getAbsoluteAddress("libil2cpp.so", 0xBD1098), (void*) Menu::BurstMoveNext, (void**)&Menu::oldBurstMoveNext);
    DobbyHook((void*)getAbsoluteAddress("libil2cpp.so", 0x11DB238), (void*) Menu::fieldOfView, (void**)&Menu::oldfieldOfView);
    DobbyHook((void*)getAbsoluteAddress("libil2cpp.so", 0x63B80C), (void*) Menu::IsValidTarget, (void**)&Menu::oldIsValidTarget);
    DobbyHook((void*)getAbsoluteAddress("libil2cpp.so", 0xD03230), (void*) Menu::CharacterMaxSpeed, (void**)&Menu::oldCharacterMaxSpeed);
    DobbyHook((void*)getAbsoluteAddress("libil2cpp.so", 0xD03520), (void*) Menu::ApplyAimpunch, (void**)&Menu::oldApplyAimpunch);
    DobbyHook((void*)getAbsoluteAddress("libil2cpp.so", 0x1DB2328), (void*) Menu::get_height, (void**)&Menu::oldget_height);
    DobbyHook((void*)getAbsoluteAddress("libil2cpp.so", 0x800230), (void*) Menu::hookedGameplayUpdate, (void**)&Menu::originalGameplayUpdate);
    DobbyHook((void*)getAbsoluteAddress("libil2cpp.so", 0x7FDF1C), (void*) Menu::Destroy, (void**)&Menu::originalDestroy);
    DobbyHook((void*)getAbsoluteAddress("libil2cpp.so", 0x7FBEE8), (void*) Menu::SetRotation, (void**)&Menu::originalSetRotation);
    Pointers::LoadPointers();
    Menu::LoadPointers();
    Patches();
    DetachIl2Cpp();
    return NULL;
}

__attribute__((constructor))
void lib_main()
{
    auto eglhandle = dlopen(OBFUSCATE("libEGL.so"), RTLD_LAZY);
    const char *dlopen_error = dlerror();
    if (dlopen_error)
    {
        eglhandle = dlopen(OBFUSCATE("libunity.so"), RTLD_LAZY);
    }
    auto eglSwapBuffers = dlsym(eglhandle, OBFUSCATE("eglSwapBuffers"));
    const char *dlsym_error = dlerror();
    if (dlsym_error)
    {
        LOGE(OBFUSCATE("Cannot load symbol 'eglSwapBuffers': %s"), dlsym_error);
    } else
    {
        hook(eglSwapBuffers, (void *) new_eglSwapBuffers, (void **) &old_eglSwapBuffers);
    }
    pthread_t ptid;
    pthread_create(&ptid, NULL, hack_thread, NULL);
}