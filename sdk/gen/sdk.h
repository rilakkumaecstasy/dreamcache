/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

void dump() {
    std::ofstream out("dr3amc4ch3.txt");
    auto domain = getdom();
    attach(domain);

    size_t asm_cnt = 0;
    auto asms = dom_asms(domain, &asm_cnt);

    for (size_t i = 0; i < asm_cnt; i++) {
        auto assembly = asms[i];
        if (!assembly) break;

        auto image = asm_get_img(assembly);
        if (!image) continue;

        const char* image_name = img_name(image);
        const char* img_str = image_name ? image_name : "NULL";

        out << "\"" << img_str << "\"\n------ [*] " << img_str << " [*] ------\n\n";

        size_t cls_cnt = img_cls_cnt(image);
        for (size_t c = 0; c < cls_cnt; c++) {
            auto klass = img_cls(image, c);
            if (!klass) break;

            auto klass_name = cls_name(klass);
            if (!klass_name || strchr(klass_name, '<')) continue;

            auto ns = safe_ns(cls_nsp(klass));
            uintptr_t klass_addr = reinterpret_cast<uintptr_t>(klass);
            write_cls_hdr(out, img_str, ns, klass_name, klass_addr);

            void* iter = nullptr;
            int method_idx = 0;

            while (auto method = cls_meth(klass, &iter)) {
                auto method_name = meth_name(method);
                if (!method_name) {
                    method_idx++;
                    continue;
                }

                Il2CppMetadataMethodInfo method_info = {};
                if (!get_method_info(&method_info, klass, method_idx) || method_info.token == 0) {
                    method_idx++;
                    continue;
                }

                auto method_ptr = get_method_ptr(image, method_info.token);
                if (!method_ptr) {
                    method_idx++;
                    continue;
                }

                int param_cnt = meth_param_cnt(method);
                auto return_type = meth_ret(method);
                const char* ret_name = return_type ? type_name(return_type) : "System.Void";

                uintptr_t method_addr = reinterpret_cast<uintptr_t>(method_ptr);
                uintptr_t method_rva = method_addr - vars::ga;

                out << "\tRVA: 0x" << std::uppercase << std::hex << method_rva << " | Addr: 0x" << method_addr << std::dec;
                out << " | <HELPER.DREAMCACHE>( -> findmethod(\"" << img_str << "\", \"" << ns << "\", \"" << klass_name << "\", \"" << method_name << "\", " << param_cnt << "); <- )\n";
                out << "\t" << ret_name << " " << method_name << "(";
                write_params(out, method, param_cnt);
                out << ")\n";
                write_impl(out, ret_name, klass_name, method, param_cnt, method_name);

                method_idx++;
            }

            out << "\n";
        }
        out << "\n";
    }

    out.close();
}

/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
