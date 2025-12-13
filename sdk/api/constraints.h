std::map<std::string, uintptr_t> apis; 

/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

namespace dreamcache {

    void api() {
        auto dr3ammap = scanpat(vars::strings::api, vars::up);
        if (!dr3ammap) return;
        for (auto p = dr3ammap; p < dr3ammap + 0x2000; p++) {
            if (!match(p, vars::strings::leardx)) continue;
            if (!match(p + 12, vars::strings::mov)) continue;
            auto n = (char*)(p + read<int>(p + 3) + 7);
            auto s = p + 12 + read<int>(p + 15) + 7;
            auto ptr = read<uintptr_t>(s);
            auto off = ptr - vars::ga;
            apis[n] = off;
        }
    }

}
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */