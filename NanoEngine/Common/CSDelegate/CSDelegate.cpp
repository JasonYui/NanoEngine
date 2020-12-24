#include "NanoEngine/Common/CSDelegate/CSDelegate.hpp"

bool Nano::CSDelegate::Init()
{
    const char* dllPath = "C:/Code/NanoEngine/NanoEngine/CSTest.dll";
    m_Domain = mono_jit_init("Nano");
    MonoAssembly* assembly = mono_domain_assembly_open(m_Domain, dllPath);
    MonoImage* image = mono_assembly_get_image(assembly);
    MonoClass* mainClass = mono_class_from_name(image, "Nano", "CSTest");

    MonoMethodDesc* entry_point_method_desc = mono_method_desc_new("Nano.CSTest:Main()", true);
    MonoMethod* entry_point_method = mono_method_desc_search_in_class(entry_point_method_desc, mainClass);
    mono_method_desc_free(entry_point_method_desc);
    mono_runtime_invoke(entry_point_method, NULL, NULL, NULL);
    return true;
}

void Nano::CSDelegate::Close()
{
    mono_jit_cleanup(m_Domain);
    delete m_Domain;
    m_Domain = nullptr;
}