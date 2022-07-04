//
// Created by letha on 9/4/2021.
//

#ifndef IMGUIANDROID_FUNCTIONPOINTERS_H
#define IMGUIANDROID_FUNCTIONPOINTERS_H
using namespace BNM::UNITY_STRUCTS;
namespace Pointers{
    bool (*HealPlayer)(void* instance, int, bool, bool);
    bool (*AddArmor)(void* instance, int);
    bool (*AddMoney)(void* instance, int);
    bool (*AddBattleMoney)(void* instance, int);
    bool (*AddLoot)(void* instance, int);
    void LoadPointers()
    {
        HealPlayer = (bool(*)(void*, int, bool, bool)) getAbsoluteAddress("libil2cpp.so", 0x66D6A4);
        AddArmor = (bool(*)(void*, int)) getAbsoluteAddress("libil2cpp.so", 0x66D7F8);
        AddMoney = (bool(*)(void*, int)) getAbsoluteAddress("libil2cpp.so", 0x5627D0);
        AddBattleMoney = (bool(*)(void*, int)) getAbsoluteAddress("libil2cpp.so", 0x562A50);
        AddLoot = (bool(*)(void*, int)) getAbsoluteAddress("libil2cpp.so", 0x5628A0);
    }
#endif IMGUIANDROID_FUNCTIONPOINTERS_H
}