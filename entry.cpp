#include "in.h"

/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/*
       __                                                          __
      |  ]                                                        [  |
  .--.| |  _ .--.  .---.  ,--.   _ .--..--.   .---.  ,--.   .---.  | |--.  .---.
/ /'`\' | [ `/'`\]/ /__\\`'_\ : [ `.-. .-. | / /'`\]`'_\ : / /'`\] | .-. |/ /__\\
| \__/  |  | |    | \__.,// | |, | | | | | | | \__. // | |,| \__.  | | | || \__.,
 '.__.;__][___]    '.__.'\'-;__/[___||__||__]'.___.'\'-;__/'.___.'[___]|__]'.__.'  6000.0.27f1, Orange Game SDK Simplified

                christmas ! 


/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */



void entry(LPVOID lpParam) {

    vars::ga = (uintptr_t)GetModuleHandle("GameAssembly.dll");
    vars::up = (uintptr_t)GetModuleHandle("UnityPlayer.dll");

    spoof = scanpat<uint64_t*>("FF 23", vars::ga);

    dreamcache::api();

    resolve();

    Sleep(3000);

    auto dom = getdom();
    if (dom) {
        attach(dom);
        Log::log("[+] Dreamcache Reference, 12/13/25 Merry Chrimaaahhh!");
        dump();
    }

}

BOOL APIENTRY DllMain(HMODULE h, DWORD d)
{
    if (d == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(h);
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)entry, h, 0, nullptr);
    }
    return TRUE;
}