#include <stdio.h>
#include <jni.h>
#include <string.h>


JNIEnv* create_vm(JavaVM ** jvm) {

    JNIEnv *env;
    JavaVMInitArgs vm_args;
    JavaVMOption options;
    options.optionString = "-Djava.class.path=java/"; //Path to the java source code
    vm_args.version = 0x0010006; //JDK version. This indicates version 1.6
    vm_args.nOptions = 1;
    vm_args.options = &options;
    vm_args.ignoreUnrecognized = 0;

    int ret = JNI_CreateJavaVM(jvm, (void**)&env, &vm_args);
    if(ret < 0)
    	printf("\nUnable to Launch JVM\n");
	return env;
}

int parseloop(char *plik, char *omegaloop)
{
	JNIEnv *env;
	JavaVM * jvm;
	env = create_vm(&jvm);
	if (env == NULL)
		return 1;

	jobjectArray SBoxes = NULL;

	jclass clsP=NULL;
	jclass clsS=NULL;

    jmethodID midTest = NULL;
    jmethodID midDelHalfVar = NULL;
	jmethodID midChainLoad = NULL;

	jmethodID midSBoxC = NULL;

    //Obtaining Classes
    clsP = env->FindClass("ParseLoop");
    clsS = env->FindClass("StringBox");

	//Obtaining Method IDs
    if (clsP != NULL)
    {
		midDelHalfVar   = env->GetStaticMethodID(clsP,"DelHalfVar","(Ljava/lang/String;Ljava/lang/String;)V");
		midChainLoad   = env->GetStaticMethodID(clsP,"ChainLoad","(Ljava/lang/String;[LStringBox;)V");
	}
	else
    {
    	printf("\nUnable to find the requested class\n");
    	return 1;
    }

    if(clsS != NULL)
	{
		//Get constructor ID for ControlDetail
		midSBoxC = env->GetMethodID(clsS, "<init>", "(Ljava/lang/String;Ljava/lang/String;)V");

	}
	else
    {
    	printf("\nUnable to find the requested class\n");
    }

    jstring str = env->NewStringUTF(plik);
    jstring str2 = env->NewStringUTF(omegaloop);
    //env->CallStaticVoidMethod(clsP, midTest, NULL);
   // env->CallStaticVoidMethod(clsP, midDelHalfVar, str, str2);

    if(midChainLoad != NULL)
    {
       if(clsS != NULL && midSBoxC != NULL)
       {
             SBoxes = (jobjectArray)env->NewObjectArray(2, clsS, env->NewObject(clsS, midSBoxC, env->NewStringUTF(""),  env->NewStringUTF("")));

             for(int i=0; i<2; i++)
                env->SetObjectArrayElement(SBoxes, i, env->NewObject(clsS, midSBoxC, env->NewStringUTF("t9t"),  env->NewStringUTF("tt")));
       }

    }
    else
        printf("error");

    if(SBoxes != NULL && midChainLoad != NULL)
        env->CallStaticVoidMethod(clsP, midChainLoad, str, SBoxes);
    else
        printf("error");







}

