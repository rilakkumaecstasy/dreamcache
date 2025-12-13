
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

void write_cls_hdr(std::ofstream& out, const char* img, const char* ns, const char* cls, uintptr_t addr) {
    out << "( <HELPER.DREAMCACHE> ( \"" << img << "\", \"" << ns << "\", \"" << cls << "\" );\n";
    uintptr_t rva = addr - vars::ga;
    out << "| [*] rva: 0x" << std::uppercase << std::hex << rva << " | [*] addr: 0x" << addr << std::dec << " |\n";
}
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */


void write_params(std::ofstream& out, const MethodInfo* meth, int cnt) {
    for (int i = 0; i < cnt; i++) {
        auto ptype = meth_param(meth, i);
        const char* pname = ptype ? type_name(ptype) : "System.Object";
        out << pname;
        if (i < cnt - 1) out << ", ";
    }
}

/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */


void write_impl(std::ofstream& out, const char* ret, const char* cls, const MethodInfo* meth, int pcnt, const char* name) {
    out << "\t{\n\t\tMETHOD(" << ret << ", (" << cls << "*";
    if (pcnt > 0) out << ", ";
    write_params(out, meth, pcnt);
    out << ", MethodInfo*), \"" << ret << " " << name << "(";
    write_params(out, meth, pcnt);
    out << ")\");\n\t\treturn function(this";
    if (pcnt > 0) out << ", ";
    for (int i = 0; i < pcnt; i++) {
        out << "arg" << i;
        if (i < pcnt - 1) out << ", ";
    }
    out << ", nullptr);\n\t}\n\t---------[dr3amc4ch3]---------------------------[public-sdk]-----------\n\n";
}

/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */


const char* safe_ns(const char* ns) {
    return (ns && ns[0] != '\0') ? ns : "";
}

/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
