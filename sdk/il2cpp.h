#include <il2cpp-api-types.h>
#include <il2cpp-class-internals.h>
#include <il2cpp-object-internals.h>

/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */


/*
       __                                                          __
      |  ]                                                        [  |
  .--.| |  _ .--.  .---.  ,--.   _ .--..--.   .---.  ,--.   .---.  | |--.  .---.
/ /'`\' | [ `/'`\]/ /__\\`'_\ : [ `.-. .-. | / /'`\]`'_\ : / /'`\] | .-. |/ /__\\
| \__/  |  | |    | \__.,// | |, | | | | | | | \__. // | |,| \__.  | | | || \__.,
 '.__.;__][___]    '.__.'\'-;__/[___||__||__]'.___.'\'-;__/'.___.'[___]|__]'.__.'  6000.0.27f1, Orange Game SDK Simplified

*/


/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */


HMODULE asm_ = LoadLibraryA("GameAssembly.dll");
uintptr_t domain, thread, methodptr, methodinfo;

/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

void resolve() {
    domain = scanpat(vars::strings::domain, vars::ga);
    thread = scanpat(vars::strings::thread, vars::ga);
    methodptr = scanpat(vars::strings::methodptr, vars::ga);
    methodinfo = scanpat(vars::strings::methodinfo1, vars::ga);
    if (!methodinfo) methodinfo = scanpat(vars::strings::methodinfo2, vars::ga);
}

/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

Il2CppDomain* getdom() { return spfc(spoof, (Il2CppDomain * (*)())(domain)); }
Il2CppThread* attach(Il2CppDomain* d) { return spfc(spoof, (Il2CppThread * (*)(Il2CppDomain*))(thread), d); }
const char* img_name(const Il2CppImage* img) { return spfc(spoof, (const char* (*)(const Il2CppImage*))((uintptr_t)asm_ + apis["il2cpp_image_get_name"]), img); }
const Il2CppAssembly** dom_asms(const Il2CppDomain* domain, size_t* size) { return spfc(spoof, (const Il2CppAssembly * *(*)(const Il2CppDomain*, size_t*))(vars::ga + apis["il2cpp_domain_get_assemblies"]), domain, size); }
const Il2CppImage* asm_get_img(const Il2CppAssembly* assembly) { return spfc(spoof, (const Il2CppImage * (*)(const Il2CppAssembly*))((uintptr_t)asm_ + apis["il2cpp_assembly_get_image"]), assembly); }
size_t img_cls_cnt(const Il2CppImage* image) { return spfc(spoof, (size_t(*)(const Il2CppImage*))((uintptr_t)asm_ + apis["il2cpp_image_get_class_count"]), image); }
const Il2CppClass* img_cls(const Il2CppImage* image, size_t index) { return spfc(spoof, (const Il2CppClass * (*)(const Il2CppImage*, size_t))((uintptr_t)asm_ + apis["il2cpp_image_get_class"]), image, index); }
const char* cls_name(const Il2CppClass* klass) { return spfc(spoof, (const char* (*)(const Il2CppClass*))((uintptr_t)asm_ + apis["il2cpp_class_get_name"]), klass); }
const char* cls_nsp(const Il2CppClass* klass) { return spfc(spoof, (const char* (*)(const Il2CppClass*))((uintptr_t)asm_ + apis["il2cpp_class_get_namespace"]), klass); }
const MethodInfo* cls_meth(const Il2CppClass* klass, void** iter) { return spfc(spoof, (const MethodInfo * (*)(const Il2CppClass*, void**))((uintptr_t)asm_ + apis["il2cpp_class_get_methods"]), klass, iter); }
void* get_method_info(Il2CppMetadataMethodInfo* m, const Il2CppClass* k, int i) { return spfc(spoof, (void* (*)(Il2CppMetadataMethodInfo*, const Il2CppClass*, int))(methodinfo), m, k, i); }
Il2CppMethodPointer get_method_ptr(const Il2CppImage* img, uint32_t tok) { return spfc(spoof, (Il2CppMethodPointer(*)(const Il2CppImage*, uint32_t))(methodptr), img, tok); }
const char* meth_name(const MethodInfo* method) { return spfc(spoof, (const char* (*)(const MethodInfo*))((uintptr_t)asm_ + apis["il2cpp_method_get_name"]), method); }
const Il2CppType* meth_ret(const MethodInfo* method) { return spfc(spoof, (const Il2CppType * (*)(const MethodInfo*))((uintptr_t)asm_ + apis["il2cpp_method_get_return_type"]), method); }
int meth_param_cnt(const MethodInfo* method) { return spfc(spoof, (int(*)(const MethodInfo*))((uintptr_t)asm_ + apis["il2cpp_method_get_param_count"]), method); }
const Il2CppType* meth_param(const MethodInfo* method, int i) { return spfc(spoof, (const Il2CppType * (*)(const MethodInfo*, int))((uintptr_t)asm_ + apis["il2cpp_method_get_param"]), method, i); }
const char* meth_param_name(const MethodInfo* method, int i) { return spfc(spoof, (const char* (*)(const MethodInfo*, int))((uintptr_t)asm_ + apis["il2cpp_method_get_param_name"]), method, i); }
const char* type_name(const Il2CppType* type) { return spfc(spoof, (const char* (*)(const Il2CppType*))((uintptr_t)asm_ + apis["il2cpp_type_get_name"]), type); }

/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */