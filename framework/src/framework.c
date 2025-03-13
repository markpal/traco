#pragma GCC diagnostic ignored "-Wreorder"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wreturn-type"
#pragma GCC diagnostic ignored "-Wformat-security"
#pragma GCC diagnostic ignored "-Wconversion-null"

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/strong_components.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/graph_utility.hpp>

#include <boost/regex.hpp>

#include <omega.h>

#include <code_gen/code_gen.h>
#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#if !defined(EXCLUDE_UNIFORM)
#include <uniform/uniform.h>
#endif

#include <petit/Exit.h>

#include <petit/petit_args.h>
#include <petit/debug.h>
#include <petit/f2p.h>
#include <petit/depend_filter.h>
#include <petit/parse_and_analyse.h>
#include <petit/build_stmt_rel.h>
#include <petit/message.h>
#include <petit/browse.h>
#include <petit/system.h>
#include <petit/langmenu.h>
#include <petit/timer.h>
#include <petit/print.h>
#include <petit/hpp.h>
#include <petit/affine.h>
#include <petit/lang-interf.h>

#define PAR_SOURCES 1

int disp = 0;

Free_Var_Decl vv1("vv1");
Free_Var_Decl vv2("vv2");
Free_Var_Decl vv3("vv3");
Free_Var_Decl vv4("vv4");
Free_Var_Decl vv5("vv5");
Free_Var_Decl vv6("vv6");
Free_Var_Decl vv7("vv7");
Free_Var_Decl vv8("vv8");
Free_Var_Decl vv9("vv9");
Free_Var_Decl vv10("vv10");
Free_Var_Decl x1("x1");
Free_Var_Decl x2("x2");
Free_Var_Decl x3("x3");
Free_Var_Decl x4("x4");
Free_Var_Decl x5("x5");

Tuple<Global_Var_Decl *> xi;

//zmienne ti do generowania codegen slicing
Tuple<Global_Var_Decl *> zti;
Tuple<String>  NameFVD;

Tuple<String> ginstr;
Tuple<String> goutstr;

char *petitLoopfilename;
std::string outputFileC;
std::string INDFileC;
std::string fs_pragma;
Tuple<int> relSCC;

#define APROX 0  //shedule aprox R* only


int __TC;
int findIND = 0;
int CODEGEN_KIND = 0;
int RETURN_R = 0;
int _SILENT = 0;
int _NOMENU = 0;
int _RELPRINT = 0;
int _PARSEPRINT = 0;
int _FS_FOR_TILING = 0;
int _SCHEDULE_TYPE = 8;
int _NOSOURCES = 0;

double begin2;

#define _R_UCS 1
#define __TC_N 5


#include "include/ce_lib/ce_Mathematica.h"
#include "include/ce_lib/ce_Omega2C.h"
#include "include/ce_lib/ce_While.h"
#include "include/ce_lib/ce_Chain.h"
#include "include/ce_lib/ce_Tree.h"
#include "include/ce_lib/ce_Graph.h"
#include "include/ce_lib/ce_SynchLib.h"


#include "include/lib.h"

#include "include/codegen_extra.h"

//#include "include/xml.h"
#include "include/simplify_R.h"
#include "include/sources_of_slices.h"
#include "include/topology.h"
#include "include/parsing.h"







// #include "include/codeengine.h"
#include "include/chains.h"
#include "include/tree.h"
#include "include/graphs.h"



#include "include/gen_code_to_scan_slices.h"
#include "include/parsetuple.h"

//#include "include/jparse.h"
#include "include/algorytmy.h"
#include "include/prepare_relations.h"

#include "include/synch.h"


string thepath = "";


#include "include/Interfaces.h"
#include "include/Convert.h"
#include "include/GraphRDG.h"

#include "include/scc.h"
#include "../../omega_lib/include/omega/AST.h"
#include "include/rk.h"
#include "include/fs.h"
#include "include/Rk_slices.h"
#include "include/ParseOutput.h"

#include "include/makeR.h"
#include "include/menu.h"
#include "include/priv_engine.h"





Tuple<Relation> *_petitRelations;

using namespace omega;

//extern int a;

static void grab_memory()
    {
    char *initial_memory_grab = getenv("PETIT_INITIAL_MEMORY_GRAB");
    long unsigned int grab_amount;

    if (initial_memory_grab)
        grab_amount = atol(initial_memory_grab);
    else
        grab_amount = 124280000; // default to ~ 5M

    void *foo = malloc(grab_amount);

    if (foo) free((char *)foo);
    } /* grab_memory */

// next gMaker
int GMakerPetit(int argc, char *argv[]) {
    _petitRelations = new Tuple<Relation>();

    set_signals();  // set reactions to signals

    grab_memory(); // Preallocate some memory so latter allocations are faster

    all_debugging_off(); // all presburger debugging off

    process_args(argc, argv);

    convert_to_petit(); // convert from Fortran if .t extension

    set_debug_files();

    depend_filter_init();

	int found = parse_and_analyse(petit_args.FileName);

	if (petit_args.DepWrFile[0])
	{
		write_depends(found, petit_args.FileName, _petitRelations);


	}
	else if (petit_args.doOEcompare)
		compare_tests(found);
	else if (petit_args.testClosure)
		test_closure(found);
	else if (petit_args.uniform)
		{
			if (!found)
	 			Error("Input file not found, exiting\n");
#if !defined(EXCLUDE_UNIFORM)
        uniform(petit_args.uniform_args);
#else
        Error("Uniform is not included in this executable\n");
#endif
		}
	else if (petit_args.hpp_only)
		hpp_generate(0);
	else
		brdd_write(0);

    return 0;
}

#include "include/CLoop.h"
#include "include/clp.h"
#include "include/Imp.h"



//Tuple<Relation> petitRelations;

// Tablica liczy sie od 1
//ponizej zbior scisle zwiazany z <petitRelations>, dla kazdej relacji z <petitRelations>
//istnieje odpowiedni element w <petitRelationsVecType> (na tej samej pozycji)
//opisujacy czy wektor zaleznosci dla relacji jest staly (wartosc 1)
//czy zmienny (wartosc 0)

//Tuple<bool> petitRelationsVecType;

//pozizej zbior zawierajacy wektory zaleznosci dla odpowiednich relacji

//Tuple<Relation> petitDepVector;

//ponizej struktura do przechowywania numeru wierszy instukcji
//miedzy którymi zachodzi zale¿noæ

//Tuple<int> petitFrom;
//Tuple<int> petitTo;
//Tuple<char *> petitRelationsType;



int main(int argc, char *argv[])
{

	begin2 = gettime();

        double start3 = gettime();


        if (argc<2) {
		cout << "Program usage : " << endl
			  << "\tpetit <petit_file> [simplify]" << endl
			  << "\t[simplify] - simplification strength [ max|min|none|sf(save and fast) ]" << endl;
	 	return -1;
	}

////////////////////
	maxGEQs=10000;
	maxEQs=10000;

    // pobierz folder programu

    //printf("%s\n", the_path);


	// =========================================
    // =========================================
    // WYZNACZANIE LD - przestrzenii iteracji
	char *plik = argv[1];
	int numSCC;
	petitLoopfilename = argv[1];
	thepath = argv[0];
	boost::replace_all(thepath, "framework/obj/framework", "");

	string rem_deps = "";

   // if(argc>=3)
 //     __TC = atoi(argv[2]);
  //  else numSCC = 0;
//	if(argc>=4)
 //     numSCC = atoi(argv[3]);
 //   else numSCC = -1;

    numSCC = -1; //all scc, >=0 selected scc
    __TC = 0; //omega closure, 1 and 2 klimek closure
    CODEGEN_KIND = 0; // omega codegen, 1 - barvinok, 2 omega +

    for(int y=3; y<=argc; y++)
    {
        string val(argv[y-1]);


        if(val.find("--tc=") != string::npos)
        {
            val = ReplaceStr(val, "--tc=", "");
             __TC = atoi(val.c_str());
        }

        if(val.find("--scc=") != string::npos)
        {
             val = ReplaceStr(val, "--scc=", "");
             numSCC = atoi(val.c_str());
        }

        if(val.find("--codegen=") != string::npos)
        {
            val = ReplaceStr(val, "--codegen=", "");
             CODEGEN_KIND = atoi(val.c_str());
        }

        if(val.find("--nomenu=") != string::npos)
        {
            val = ReplaceStr(val, "--nomenu=", "");
             _NOMENU = atoi(val.c_str());

             _SILENT = _NOMENU; //diable menu disable debug if not SILENT is later set
        }

        if(val.find("--output_C=") != string::npos)
        {
            val = ReplaceStr(val, "--output_C=", "");
             outputFileC = val;

        }

        if(val.find("--path_issf=") != string::npos)
        {
            val = ReplaceStr(val, "--path_issf=", "");
             thepath = val + "/";

        }

        if(val.find("--silent=") != string::npos)
        {
            val = ReplaceStr(val, "--silent=", "");
             _SILENT = atoi(val.c_str());

        }

        if(val.find("--rem_deps=") != string::npos)
        {
            val = ReplaceStr(val, "--rem_deps=", "");
            rem_deps = val;

        }

        if(val.find("--fs_pragma=") != string::npos)
        {
            val = ReplaceStr(val, "--fs_pragma=", "");
            fs_pragma = val;

        }

        if(val.find("--return=") != string::npos)
        {
             val = ReplaceStr(val, "--return=", "");
             RETURN_R = atoi(val.c_str());
        }

        if(val.find("--ind_loop=") != string::npos)
        {
            val = ReplaceStr(val, "--ind_loop=", "");
            INDFileC = val;
        }

        if(val.find("--relation_print") != string::npos)
        {
            val = ReplaceStr(val, "--relation_print", "");
            _RELPRINT = 1;
        }
        // drukuj relacje , nie baw sie w R* i Srepr
        if(val.find("--no_sources") != string::npos)
        {
            val = ReplaceStr(val, "----no_sources", "");
            _NOSOURCES = 1;
        }

        if(val.find("--parse_print") != string::npos)
        {
            _PARSEPRINT = -1;
            if(val.find("--parse_print=") != string::npos){
                val = ReplaceStr(val, "--parse_print=", "");
                    _PARSEPRINT = atoi(val.c_str());
            }
        }
        //schedule for tiling
        if(val.find("--fs_for_tiling=") != string::npos)
        {
            val = ReplaceStr(val, "--fs_for_tiling=", "");
            _FS_FOR_TILING =  atoi(val.c_str());
            // 1 domyslnie , 2 always schedule

        }

        //schedule for tiling
        if(val.find("--schedule_type=") != string::npos)
        {
            val = ReplaceStr(val, "--schedule_type=", "");
            _SCHEDULE_TYPE =  atoi(val.c_str());
            if(_SCHEDULE_TYPE != 8 && _SCHEDULE_TYPE != 9)
                _SCHEDULE_TYPE = 8;
             // 1 domyslnie , 2 always schedule

        }
        // flaga czy dawac FS czy zostawiac sekw

    }

    if(!_SILENT)
        cout << "Parameters: TC " << __TC << " SCC" << numSCC << " CODEGEN " << CODEGEN_KIND << endl;


    if(!_SILENT)
        printf("=== %s == " , plik);
	plik = argv[1];

    copyFile(plik, "input.txt");

    if(_PARSEPRINT != 0)
    {
        ParseOutput();
        exit(0);
    }
        // ----------------------------------------------

              //     printf("o\n");
	std::map<int,Relation> allIterations;

        CLoop *petla;
        if(!_SILENT)
            printf("o\n");
        Relation LD;

        if(findIND)
        {
           petla = new CLoop(plik);
            allIterations = petla->CreateAllIterations();
            LD = allIterations.begin()->second;

            LD.simplify();
            LD = MaxSimplify(LD);
            LD = SimplifyNumConjuncts(LD);
            if(!_SILENT)
            {
                 printf("\nLD");
                LD.print();
            }

/*
zrobic IND - mozna
masz LD zapisac z parametrem w pliku oaobnym
zrobic roznice LD i uruchomic skrypt oc
a nastepnie codegen i dopisac do parallel

todo priv
*/

exit(0);

            petitRelations.clear();
            petitRelationsVecType.clear();
            petitDepVector.clear();
            petitFrom.clear();
            petitTo.clear();
            petitRelationsType.clear();

        }


        for(int u=1; u<=50; u++)
        {
            Global_Var_Decl *g =  new Global_Var_Decl("v");
            zti.append(g);
        }

        for(int u=1; u<=50; u++)
        {
            Global_Var_Decl *g =  new Global_Var_Decl("x");
            xi.append(g);
        }



	//LD =  FindAllPerfectNestedLoop(); linux nie wiem po co to

// ========================================
// =========================================

	//int simplify=3; //domyslan wartosc uproszczenia to save_and_fast
// -Fc
	char *argvGMaker[6] = {"petit","-b -4","-g", " ", "-R./analysis/petit.out"};

/*	if (argc>=3)
	{
		if (!strcmp(argv[2],"none")) simplify=0;
		else if (!strcmp(argv[2],"min")) simplify=1;
		else if (!strcmp(argv[2],"max")) simplify=2;
		else simplify=3;
	}
*/
	mkdir("analysis", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	mkdir("code", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);


	if (1) {
		//petla nie idealnie zagniezdzona
		argvGMaker[3] = argvGMaker[4];
		argvGMaker[4] = argv[1];
		GMakerPetit(5,argvGMaker);
		//loopAnalysis = new CMinSynchNonPerfect(arguments,loop,petitRelations,petitDepVector,
		// 										petitRelationsVecType,petitFrom,petitTo);

	}
	else {
		//petla idealnie zagniezdzona
		/*******TYMACZASOWO ZABRANIAM ANALIZOWANIA PETLI IDEALNIE ZAGNIEZDZONYCH******************************/
		argvGMaker[5] = argv[1]; //podmieniamy plik wejsciowy z petla w peticie
		GMakerPetit(6,argvGMaker);
		//loopAnalysis = new CMinSynchPerfect(arguments,loop,petitRelations,petitDepVector,	petitRelationsVecType,petitFrom,petitTo);
		/**************************************/
		//printf("Petla idealnie zagniezdzona - analiza przerwana\n");
		//exit(1);
	}

/* Zmiany naniesiono w petit_args.c i .h oraz browsedd.h


               ----      UWAGA     -----

    Tuple<Relation> petitRelations;
    Tuple<bool> petitRelationsVecType;
    Tuple<Relation> petitDepVector;
    Tuple<int> petitFrom;
    Tuple<int> petitTo;
    Tuple<char *> petitRelationsType;
    Kolekcje są w petit_args.h
                -----    UWAGA     -----               */


// ==================================================================================================
// ==================================================================================================

   double end3 = gettime();
   if(!_SILENT)
        printf("\n--------> Analiza: %.2f\n", (double)((end3 - start3)));
 //  exit(0);

    ComplexRelation BaseRel; // *BaseOut = new ComplexRelation;
    BaseRel.R = petitRelations;
    BaseRel.VecType = petitRelationsVecType;
    BaseRel.DepVect = petitDepVector;
    BaseRel.From = petitFrom;
    BaseRel.To = petitTo;
    BaseRel.Type = petitRelationsType;
    BaseRel.Line = petitLine;
    BaseRel.Var = petitVar;

    Relation Rs;


    //usun zaleznosci na zadanie
    ComplexRelation *BaseOut;
    if(rem_deps != "")
    {
        BaseOut = new ComplexRelation;
        std::vector<std::string> rd;
        boost::split(rd, rem_deps, boost::is_any_of(","));


        for(int j1 = 1; j1<=BaseRel.R.length(); j1++)
        {


            int add = 1;
            for(int j2 = 0; j2 <rd.size(); j2++)
            {
                if(atoi(rd[j2].c_str()) == j1)
                {
                    add = 0;
                    break;
                }
            }


            if(add)
            {
                BaseOut->R.append(BaseRel.R[j1]);
                BaseOut->DepVect.append(BaseRel.DepVect[j1]);
                BaseOut->VecType.append(BaseRel.VecType[j1]);
                BaseOut->Type.append(BaseRel.Type[j1]);
                BaseOut->From.append(BaseRel.From[j1]);
                BaseOut->To.append(BaseRel.To[j1]);
                BaseOut->Var.append(BaseRel.Var[j1]);
                BaseOut->Line.append(BaseRel.Line[j1]);
            }
        }

        BaseRel = *BaseOut;

    }



    if(BaseRel.R.length()==0)
    {
        if(outputFileC != "")
        {
            ofstream myfile;
            myfile.open(outputFileC.c_str());
            myfile << "#pragma omp parallel for";
            myfile.close();
        }
        exit(0);
    }


   // int i;






// RK!!!!
    /*
    Relation UDS = Difference(Domain(copy(Ru)), Range(copy(Ru)));
    UDS.simplify(2, 5);
    printf("UDS\n");
    UDS.print();
    Relation Z = Rk(copy(Ru));
    Z = Upper_Bound(copy(Z));
    Z.print();

    Relation Sk = Range(Restrict_Domain(copy(Z), copy(UDS)));

    Sk = Difference(copy(Sk), Range(Composition(copy(Z), Star(Ru, 1))));  //?


    Sk.simplify();

    Sk.print();

   // exit(0);
    Relation SOUT = Sk;
    SOUT = Complement(Difference(copy(Sk), copy(Sk)));
    SOUT.simplify();

    SOUT = Extend_Set(copy(SOUT), 1);
    SOUT.simplify();
    SOUT.print();


    int dim = Sk.n_set();

    Variable_ID ex[10];


    for(i=0; i<dim; i++)
        ex[i] = SOUT.input_var(i+2);



    F_And *fex_and = SOUT.and_with_and();


     S_Add_Exist2(Sk, SOUT, fex_and, ex);

     SOUT.name_set_var(1, "y");
     String nazwa;

     for(i=1; i<=Sk.n_set(); i++)
     {
	  nazwa =  Sk.set_var(i)->name();
          SOUT.name_set_var(i+1, nazwa);
     }


     Variable_ID v;
      for(i=1; i<=SOUT.global_decls()->length(); i++)
     {
       v = SOUT.global_decls()->operator [](i);
       if(strcmp(str(v->name()), "K")==0)
           break;
     }


     Variable_ID x = SOUT.set_var(1);
     F_And *fand = SOUT.and_with_and();
     EQ_Handle xx = fand->add_EQ();
     xx.update_coef(x,-1);
     xx.update_coef(v,1);
    SOUT.print();
     SOUT = Project(copy(SOUT), v);

     SOUT.simplify();
     SOUT.print();

     String petla2 = LoopCodeGen(SOUT, 1);

     printf("%s", str(petla2));
exit(0);





    int dim = Sk.n_set();
    Relation SOUT(dim+1);

    Variable_ID ex[10];

    int i;
    for(i=0; i<dim-1; i++)
        ex[i] = SOUT.input_var(i+2);



    F_And *fex_and = SOUT.add_and();

    S_Add_Exist2(Sk, SOUT, fex_and, ex);
exit(0);
    String nazwa;

    for(i=1; i<=Sk.n_set(); i++)
    {
	  nazwa =  Sk.set_var(i)->name();
          SOUT.name_set_var(i+1, nazwa);
    }
    exit(0);
    Variable_ID v;
    for(i=1; i<=SOUT.global_decls()->length(); i++)
    {
       v = SOUT.global_decls()->operator [](i);
       if(strcmp(str(v->name()), "K"))
           break;
    }

    Variable_ID x = SOUT.set_var(1);




    F_And *fand = SOUT.and_with_and();
    EQ_Handle xx = fand->add_EQ();
    xx.update_coef(x,-1);
    xx.update_coef(v,1);

    SOUT.simplify();
    SOUT.print();


    exit(0);






    Relation R1 = BaseRel.R[3];

    R1.print();
// ------------------- SK
    Relation S = Domain(copy(R1));
    Relation S1(3);
    Variable_ID ex[10];
     ex[0] = S1.input_var(2);
     ex[1] = S1.input_var(3);
      F_And *fex_and = S1.add_and();

    S.print();
    int i;

     S_Add_Exist2(S, S1, fex_and, ex);


     	String nazwa;
	String name_tab[10];   // tablica nazw zmiennych e''
     	for(i=1; i<=S.n_inp(); i++)
	{
		nazwa =  S.set_var(i)->name();
		name_tab[i-1] = nazwa;
                S1.name_set_var(i+1, nazwa);
	}
        S1.name_set_var(1, "K");

     S1.print();

       for(i=1; i<=S1.global_decls()->length(); i++)
       {
     Variable_ID v = S1.global_decls()->operator [](i);
     if(strcmp(str(v->name()), "k"))
         break;
       }

// -------------------------

    Relation R2(2,2);
    Variable_ID j2 = R2.output_var(2);
    F_And *fand = R2.add_and();





    Variable_ID ex[10];
    ex[0] = R2.input_var(1);
    Free_Var_Decl x("x");
    Variable_ID R_x = R2.get_local(&x);
    ex[1] = R_x;

    R_Add_Exist2(R1, R2, fand, ex, 0, 0);





    R2.copy_names(R1);
     * */



  /*  R2.print();
    R2.simplify(2, 5);




   R2.print();*/


  // exit(0);



    /*
    Relation Z = Domain(copy(BaseRel.R[1])), Y;
    Z.print();

    Y = LexForward(Z.n_set());
    Y.simplify();
    Y.print_with_subs();

    Y = Maximize(copy(Z));
    Y.simplify();
    Y.print_with_subs();


    Y = Minimize(copy(Z));
    Y.simplify();
    Y.print_with_subs();


    exit(0);
*/

 //   for(int k=1; k<=BaseRel.R.length(); k++)
   //     printf("%s", BaseRel.Type[k]);

 //   exit(0);
    if(findIND)
    {
        // brakuje wersji imperfect

        Relation IND = globalUnion(NormalizeRel(BaseRel.R));


        IND = Difference(copy(LD), Union(Domain(copy(IND)), Range(copy(IND))));
        IND.simplify();
        IND.print();
        IND = SymSimplify2(IND);
        printf("IND\n");
        IND.print();
        if(IND.number_of_conjuncts()> 0)
            printf("\n%s\n", str(LoopCodeGen(IND, 0)));


    }
   /*
    Relation Ru = globalUnion(BaseRel.R);
    Ru.simplify();
    Ru.print_with_subs();
    Relation Z = Domain(copy(Ru));
    Z.print_with_subs();
    Z = Range(copy(Ru));
    Z.print_with_subs();
    //exit(0);
  */
      // -------------------------------------------------------------------------


    if(!_SILENT)
        printf("Liczba relacji %i \n", petitRelations.length());
    int numberofSCC = ShowScc();
    if(!_SILENT)
        printf("Liczba SCC %i \n", numberofSCC);
    BaseRel.SCC = relSCC;

  //  printf("Liczba rels %i \n", BaseRel.Line.length());

    FILE *fff = fopen("tmp.txt", "w");
	for(int i=1; i<=BaseRel.Line.length(); i++)
	    BaseRel.R[i].print(fff);
    fclose(fff);

    if(!_SILENT)
	for(int i=1; i<=BaseRel.Var.length(); i++)
	{
        printf("%s ", BaseRel.Var[i]);
	    cout << BaseRel.Line[i]<<endl;

	}


   // GetPrivVariables(BaseRel);

   // BaseRel.R[5] = Ch_Relation(BaseRel.R[5], 2);
  //  BaseRel.R[5].print();



if(!_SILENT)
    cout << numSCC << endl;
   // exit(0);
    if(numSCC != -1)
        BaseRel = chooseSCC(BaseRel, numSCC, disp);

    //Test8(BaseRel.R[1]);

    Relation T = Domain(copy(BaseRel.R[1]));
    if(!_SILENT)
        T.print();

    // cout << Card(T);
   //  cout << endl << endl;
   //  cout << OmegaPlusCodegen(T);

  //  exit(0);
    if(0)
    DivideRelSet(BaseRel);
    else
    OneTouch(BaseRel, Rs);

  //  CodeEngine::Omega2C oc;





    return 0; // shut the compiler up
}





