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

void (*oldLogin)(std::uintptr_t instance, std::uintptr_t eventData);
void Login(std::uintptr_t instance, std::uintptr_t eventData) {
    if (instance != NULL && !isHooked) {
        isHooked = true;

        LOGE("-> Hooking swapbuffer..");
        auto eglhandle = dlopen(OBFUSCATE("libunity.so"), RTLD_LAZY);
        dlerror();
        auto eglSwapBuffers = dlsym(eglhandle, OBFUSCATE("eglSwapBuffers"));
        const char *dlsym_error = dlerror();
        if (dlsym_error)
        {
            LOGE(OBFUSCATE("Cannot load symbol 'eglSwapBuffers': %s"), dlsym_error);
        } else
        {
            hook(eglSwapBuffers, (void *) new_eglSwapBuffers, (void **) &old_eglSwapBuffers);
        }
    }
    else if(instance != NULL)
    {
        LOGE("-> The login function has been called.");
    }
    oldLogin(instance, eventData);
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
    DobbyHook((void*)getAbsoluteAddress("libil2cpp.so", 0xD03404), (void*) Menu::Inaccuaracy, (void**)&Menu::oldInaccuaracy);
    DobbyHook((void*)getAbsoluteAddress("libil2cpp.so", 0x8A45F0), (void*) Login, (void**)&oldLogin);
    Pointers::LoadPointers();
    DetachIl2Cpp(); // remember to detach when you are done using bynamemodding functions
    return NULL;
}



__attribute__((constructor))
void lib_main()
{
    pthread_t ptid;
    pthread_create(&ptid, NULL, hack_thread, NULL);
}