#include <stdio.h>
#include <stdlib.h>
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

#include <omega.h>

using namespace omega;

static void grab_memory()
    {
    char *initial_memory_grab = getenv("PETIT_INITIAL_MEMORY_GRAB");
    long unsigned int grab_amount;

    if (initial_memory_grab)
        grab_amount = atol(initial_memory_grab);
    else
        grab_amount = 5242800; // default to ~ 5M

    void *foo = malloc(grab_amount);

    if (foo) free((char *)foo);
    } /* grab_memory */

// next gMaker
int main(int argc, char *argv[]) {
    set_signals();  // set reactions to signals

    grab_memory(); // Preallocate some memory so latter allocations are faster

    all_debugging_off(); // all presburger debugging off

    process_args(argc, argv);

    convert_to_petit(); // convert from Fortran if .t extension

    set_debug_files();

    depend_filter_init();





    return 0; // shut the compiler up
} /* main */
