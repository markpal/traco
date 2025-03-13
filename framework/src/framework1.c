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

#include <boost/regex.hpp>
/*
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/strong_components.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/graph_utility.hpp>
*/


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

//Free_Var_Decl q("q");

Tuple<String> NameFVD;

Tuple<String> ginstr;
Tuple<String> goutstr;

char *petitLoopfilename;


#define _TC 0
#define _TC_N 5

#include "include/lib.h"
#include "include/simplify_R.h"
#include "include/sources_of_slices.h"
#include "include/parsing.h"
#include "include/gen_code_to_scan_slices.h"
#include "include/parsetuple.h"
#include "include/jparse.h"
#include "include/algorytmy.h"
#include "include/menu.h"
//#include "include/SCC.h"


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
/*
#include "include/CLoop.h"
#include "include/clp.h"
#include "include/Imp.h"
*/


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

	if (argc<2) {
		cout << "Program usage : " << endl
			  << "\tpetit <petit_file> [simplify]" << endl
			  << "\t[simplify] - simplification strength [ max|min|none|sf(save and fast) ]" << endl;
		return -1;
	}

////////////////////
	maxGEQs=10000;
	maxEQs=10000;


	// =========================================
    // =========================================
    // WYZNACZANIE LD - przestrzenii iteracji
	char *plik = argv[1];
	petitLoopfilename = argv[1];
	/*
	printf("=== %s == " , plik);
	plik = argv[1];

	std::map<int,Relation> allIterations;
	CLoop *petla = new CLoop(plik);
	allIterations = petla->CreateAllIterations();
	Relation LD = allIterations.begin()->second;

	LD.simplify();
	LD = MaxSimplify(LD);
    //	LD.print();

	LD =  FindAllPerfectNestedLoop();
*/
// ========================================
// =========================================

	int simplify=3; //domyslan wartosc uproszczenia to save_and_fast

	char *argvGMaker[6] = {"petit","-b -4","-g", "-Fc", "-R./analysis/petit.out"};

	if (argc>=3)
	{
		if (!strcmp(argv[2],"none")) simplify=0;
		else if (!strcmp(argv[2],"min")) simplify=1;
		else if (!strcmp(argv[2],"max")) simplify=2;
		else simplify=3;
	}

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


/************************UWAGA*************************/
    /*
    Tuple<Relation> petitRelations;
    Tuple<bool> petitRelationsVecType;
    Tuple<Relation> petitDepVector;
    Tuple<int> petitFrom;
    Tuple<int> petitTo;
    Tuple<char *> petitRelationsType; */
/************************UWAGA************************/


// ==================================================================================================
// ==================================================================================================


	ComplexRelation BaseRel, *BaseOut = new ComplexRelation;
	BaseRel.R = petitRelations;
	BaseRel.VecType = petitRelationsVecType;
	BaseRel.DepVect = petitDepVector;
	BaseRel.From = petitFrom;
	BaseRel.To = petitTo;
	BaseRel.Type = petitRelationsType;

printf("%i", maxmaxGEQs);
    printRelations(petitRelations, 1);

    Relation Rs;
  /*  Relation R = globalUnion(petitRelations);


  /*  R.print();
    Rs = Star(copy(R));
    Rs.print();
    exit(0);
*/
    OneTouch(BaseRel, Rs);


    Rel_Struct Sources;
    Sources = CalcSources(BaseRel, 1);


    //parseloop("ttt", "rrr");

    return 0; // shut the compiler up
}

