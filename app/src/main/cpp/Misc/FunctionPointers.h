//
// Created by letha on 9/4/2021.
//

#ifndef IMGUIANDROID_FUNCTIONPOINTERS_H
#define IMGUIANDROID_FUNCTIONPOINTERS_H
using namespace BNM::UNITY_STRUCTS;
namespace Pointers{
    struct Vec3
    {
        float x;
        float y;
        float z;
    };

    Vec3(*getTransform)(void* ptr);
    void* (*getLocalPlayer)(void* ptr);
    void LoadPointers()
    {
        getTransform = (Vec3(*)(void*))getAbsoluteAddress("libil2cpp.so", 0x14CF704);
        getLocalPlayer = (void*(*)(void*))getAbsoluteAddress("libil2cpp.so", 0x60E980);
    }
}
#endif IMGUIANDROID_FUNCTIONPOINTERS_H