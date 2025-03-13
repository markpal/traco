#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>

#define _ASSEMBLY "CodeEngine.dll"
#define _NAMESPACE "CodeEngine"

MonoDomain *domain;
MonoClass *monoclass;


MonoObject * GetObject(char * name)
{


    domain = mono_jit_init (_ASSEMBLY);

   // if(!domain)error();

    //Load assembly into domain

    MonoAssembly *assembly;
	assembly = mono_domain_assembly_open(domain, _ASSEMBLY);
    //if( !assembly )error();

    MonoImage * image = mono_assembly_get_image(assembly);

    monoclass = mono_class_from_name (image, _NAMESPACE, name);

    MonoObject *my_class_instance = mono_object_new (domain, monoclass);
    mono_runtime_object_init (my_class_instance);

    return my_class_instance;

}

MonoMethod *GetMethod(char *name)
{
//    gpointer iter;

    MonoMethod *m, *method;
    void* iter = NULL;

    while ((m = mono_class_get_methods (monoclass, &iter))) {

	if (strcmp (mono_method_get_name (m), name) == 0)
    {
        method = m;
    }
    }
    return method;

}

void MonoClear()
{
    mono_jit_cleanup(domain);
}

