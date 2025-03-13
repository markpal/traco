/* example-isl.c */
#include <cloog/cloog.h>
#include <cloog/isl/cloog.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>


char* codegen(char * str_context, int nb_parameters, char ** parameter_name, char** iterator_name, int num_dom, char** str_domains, char** str_scattering)
{

    int i;

  isl_ctx *ctx;
  isl_set *set_context, *set1;
  isl_map *map1;
  CloogDomain *context, *domain1;
  CloogScattering *scattering1;
  CloogUnionDomain *domains;
  CloogInput *input;
  CloogState *state;
  CloogOptions *options;
  struct clast_stmt *root;
  char loop[2048];

  /* Build isl structures for context, sets and mapping */
  ctx = isl_ctx_alloc();
  set_context = isl_set_read_from_str(ctx, str_context);
  context = cloog_domain_from_isl_set(set_context);
  domains = cloog_union_domain_alloc(nb_parameters);


  for(i=0; i<num_dom; i++)
  {
     set1 = isl_set_read_from_str(ctx, str_domains[i]);

     map1 = isl_map_read_from_str(ctx, str_scattering[i]);

     domain1 = cloog_domain_from_isl_set(set1);
     scattering1 = cloog_scattering_from_isl_map(map1);

     char s1[3] = "S1";
     sprintf(s1, "S%d", i+1);
     cloog_union_domain_add_domain(domains, s1, domain1, scattering1, NULL);

  }

    i = 0;
    while(parameter_name[i])
    {
       cloog_union_domain_set_name(domains, CLOOG_PARAM, i, parameter_name[i]);
       i++;
    }

    i = 0;
    while(iterator_name[i])
    {
       cloog_union_domain_set_name(domains, CLOOG_ITER, i, iterator_name[i]);
       i++;
    }


  /* Build the input, generate the AST of the scanning code and print it */
  input = cloog_input_alloc(context, domains);
  state = cloog_isl_state_malloc(ctx);
  options = cloog_options_malloc(state);
  //options->f = 3;
  options->otl = 1;
  options->quiet = 1;
  root = cloog_clast_create_from_input(input, options);
  //int     FD[2];
  //FILE *inputf;
  //pipe(FD);
  //inputf = fdopen(FD[1], "w");

  FILE *plik;
  plik = fopen("tmp/cloog_loop.c", "wt");
  //clast_pprint(inputf, root, 0, options);
  clast_pprint(plik, root, 0, options);

  //fclose(inputf);
  //close(FD[1]);
  //read(FD[0], loop, 2048);
  fclose(plik);
  //plik = fopen("tmp/cloog_loop.c", "r");
  //i = 0;
  //while (!feof(plik)){
  // fscanf(plik, "%c", &loop[i]);
  // i++;
 //}

  //fclose(plik);
  /* Recycle allocated memory */
  cloog_clast_free(root);
  cloog_options_free(options);
  cloog_state_free(state);
  isl_ctx_free(ctx);

    return loop;

}


