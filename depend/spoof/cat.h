#pragma once
#include <windows.h>
#include <map>
#include <vector>
#include <intrin.h>

namespace vars { extern uintptr_t up; }

namespace cat {
    extern "C" void proxy_call_stub();
    extern "C" uintptr_t proxy_call_returns[];
    extern "C" size_t proxy_call_fakestack_size;
    extern "C" uintptr_t* proxy_call_fakestack;

    inline void init(uint32_t max = 12) {
        std::map<int8_t, std::vector<uintptr_t>> ret;
        auto base = (uint8_t*)vars::up;
        auto dos = (IMAGE_DOS_HEADER*)base;
        auto nt = (IMAGE_NT_HEADERS*)(base + dos->e_lfanew);
        auto sec = IMAGE_FIRST_SECTION(nt);

        for (int i = 0; i < nt->FileHeader.NumberOfSections; i++, sec++) {
            if (sec->Characteristics & IMAGE_SCN_MEM_DISCARDABLE) continue;

            auto start = base + sec->VirtualAddress;
            auto end = start + sec->Misc.VirtualSize;

            for (auto p = start; p < end - 5; p++) {
                if (p[0] == 0x48 && p[1] == 0x83 && p[2] == 0xC4 && p[4] == 0xC3)
                    ret[p[3]].push_back((uintptr_t)p);
            }
        }

        std::vector<int8_t> keys;
        for (auto& it : ret) {
            auto idx = it.first / 8;
            proxy_call_returns[idx] = it.second[__rdtsc() % it.second.size()];
            if (idx < 10 && idx % 2 == 1) keys.push_back(it.first);
        }

        std::vector<uintptr_t> stk;
        while (stk.size() < max) {
            auto rnd = __rdtsc();
            auto len = keys[rnd % keys.size()];
            auto& arr = ret[len];
            stk.push_back(arr[rnd % arr.size()]);
            for (int j = 0; j < len / 8; j++)
                stk.push_back((uintptr_t)base + (__rdtsc() % nt->OptionalHeader.SizeOfImage));
        }

        proxy_call_fakestack_size = stk.size();
        proxy_call_fakestack = new uintptr_t[stk.size()];
        memcpy(proxy_call_fakestack, stk.data(), stk.size() * 8);
    }

    template <typename Ret, typename... Args>
    inline auto call(Ret(*fn)(Args...), Args... args) -> Ret {
        return ((Ret(__cdecl*)(Args..., uint64_t, void*))proxy_call_stub)(args..., 0x21376969, (void*)fn);
    }
}