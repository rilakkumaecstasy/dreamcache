/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
void dump() {
    std::ofstream out("dr3amc4ch3.txt");

    auto domain = getdom();
    attach(domain);

    size_t count = 0;
    auto assemblys = dom_asms(domain, &count);

    for (size_t i = 0; i < count; i++) {
        auto assembly = assemblys[i];
        if (!assembly) break;

        auto image = asm_get_img(assembly);
        if (!image) continue;

        auto imgName = img_name(image);
        out << "\"" << imgName << "\"\n------ [*] " << imgName << " [*] ------\n\n";

        size_t classCount = img_cls_cnt(image);
        for (size_t c = 0; c < classCount; c++) {
            auto klass = img_cls(image, c);
            if (!klass) break;

            auto className = cls_name(klass);
            if (!className || strchr(className, '<')) continue;

            auto ns = safe_ns(cls_nsp(klass));
            write_cls_hdr(out, imgName, ns, className);

            void* iter{};
            int index = 0;
            while (auto method = cls_meth(klass, &iter)) {
                auto methodName = meth_name(method);
                if (!methodName) {
                    index++;
                    continue;
                }

                Il2CppMetadataMethodInfo methodInfo = {};
                if (!get_method_info(&methodInfo, klass, index) || methodInfo.token == 0) {
                    index++;
                    continue;
                }

                auto methodPtr = get_method_ptr(image, methodInfo.token);
                if (!methodPtr) {
                    index++;
                    continue;
                }

                auto params = meth_param_cnt(method);
                auto returnType = meth_ret(method);
                auto returnName = returnType ? type_name(returnType) : "System.Void";

                uintptr_t addr = (uintptr_t)methodPtr;
                uintptr_t rva = addr - vars::ga;

                out << "\trva: 0x" << std::uppercase << std::hex << rva << " | Addr: " << addr << std::dec << "\n";
                out << "\t" << returnName << " " << methodName << "(";
                write_params(out, method, params);
                out << ")\n";

                write_impl(out, returnName, className, method, params, methodName);
                index++;
            }
            out << "\n";
        }
        out << "\n";
    }
    out.close();
}

/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
