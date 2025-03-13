// Funkcja rozkladaja relacje na czynniki pierwsze
// ma podstawie manuala
// wejscie relacja R
// wyjscie XML

#include <libxml/encoding.h>
#include <libxml/xmlreader.h>
#include <libxml/xmlwriter.h>

int Relation2Xml(Relation r1, String filename)
{
    xmlTextWriterPtr writer;
        bool is_set;
        int dims, dimi, dimo, i;
        char* tmp = new char[255];



        is_set = r1.is_set();  // relacja jest zbiorem

        if(is_set)
                dims = r1.n_set();
        else
        {
                dimi = r1.n_inp();
                dimo = r1.n_out();
        }


        writer = xmlNewTextWriterFilename(filename, 0);

        if (writer == NULL)
        return -1;

        //START XML
        xmlTextWriterStartDocument(writer, NULL, NULL, NULL);


        // <RELATION>

        xmlTextWriterStartElement(writer, BAD_CAST "RELATION");

        // Attribute Kind
    if(is_set)
                xmlTextWriterWriteAttribute(writer, BAD_CAST "kind", BAD_CAST "set");
        else
                xmlTextWriterWriteAttribute(writer, BAD_CAST "kind", BAD_CAST "relation");

        // <DIM>
        xmlTextWriterWriteVFormatString(writer, "\n\t", NULL);
        xmlTextWriterStartElement(writer, BAD_CAST "DIM");


        if(is_set)
        {
                //<DIMS>
                xmlTextWriterWriteVFormatString(writer, "\n\t\t", NULL);
                xmlTextWriterStartElement(writer, BAD_CAST "DIMS");
                sprintf(tmp, "%d", dims);
                xmlTextWriterWriteVFormatString(writer, tmp, NULL);
                xmlTextWriterEndElement(writer);
        }
        else
        {
                //<DIMI>
                xmlTextWriterWriteVFormatString(writer, "\n\t\t", NULL);
                xmlTextWriterStartElement(writer, BAD_CAST "DIMI");
                sprintf(tmp, "%d", dimi);
                xmlTextWriterWriteVFormatString(writer, tmp, NULL);
                xmlTextWriterEndElement(writer);

                //<DIMO>
                xmlTextWriterWriteVFormatString(writer, "\n\t\t", NULL);
                xmlTextWriterStartElement(writer, BAD_CAST "DIMO");
                sprintf(tmp, "%d", dimo);
                xmlTextWriterWriteVFormatString(writer, tmp, NULL);
                xmlTextWriterEndElement(writer);

        }


        // </DIM>
        xmlTextWriterWriteVFormatString(writer, "\n\t", NULL);
        xmlTextWriterEndElement(writer);


        // <VARIABLES>
        xmlTextWriterWriteVFormatString(writer, "\n\t", NULL);
        xmlTextWriterStartElement(writer, BAD_CAST "VARIABLES");

        if(is_set)
        {
                for(i=1; i<=dims; i++)
                {
                        //<SET>

                        xmlTextWriterWriteVFormatString(writer, "\n\t\t", NULL);
                        xmlTextWriterStartElement(writer, BAD_CAST "SET");

                        Variable_ID v = r1.set_var(i);
                        sprintf(tmp, "%s", str(v->name()));

                        xmlTextWriterWriteVFormatString(writer, tmp, NULL);
                        xmlTextWriterEndElement(writer);



                }


        }
        else
        {
                for(i=1; i<=dimi; i++)
                {
                        //<INPUT>

                        xmlTextWriterWriteVFormatString(writer, "\n\t\t", NULL);
                        xmlTextWriterStartElement(writer, BAD_CAST "INPUT");

                        Variable_ID v = r1.input_var(i);

                        sprintf(tmp, "%s", str(v->name()));

                        xmlTextWriterWriteVFormatString(writer, tmp, NULL);
                        xmlTextWriterEndElement(writer);



                }
                for(i=1; i<=dimo; i++)
                {
                        //<OUTPUT>

                        xmlTextWriterWriteVFormatString(writer, "\n\t\t", NULL);
                        xmlTextWriterStartElement(writer, BAD_CAST "OUTPUT");

                        Variable_ID v = r1.output_var(i);
                        sprintf(tmp, "%s", str(v->name()));

                        xmlTextWriterWriteVFormatString(writer, tmp, NULL);
                        xmlTextWriterEndElement(writer);

                }
        }


        // </VARIABLES>
        xmlTextWriterWriteVFormatString(writer, "\n\t", NULL);
        xmlTextWriterEndElement(writer);


        // <CONJUNCTS>
        xmlTextWriterWriteVFormatString(writer, "\n\t", NULL);
        xmlTextWriterStartElement(writer, BAD_CAST "CONJUNCTS");






        for(DNF_Iterator di(r1.query_DNF()); di; di++)
        {
                // <CONJUNCT>
                xmlTextWriterWriteVFormatString(writer, "\n\t\t", NULL);
                xmlTextWriterStartElement(writer, BAD_CAST "CONJUNCT");

                // Exists attribute
                String s = (*di)->print_to_string(1);

                if(strstr(s, "Exists")) // jest Exists
                        xmlTextWriterWriteAttribute(writer, BAD_CAST "Exists", BAD_CAST "yes");
                else
                        xmlTextWriterWriteAttribute(writer, BAD_CAST "Exists", BAD_CAST "no");




                for(Variable_Iterator vi(*(*di)->variables()); vi; vi++)
                {
                        Variable_ID vv = (*vi);
                        Var_Kind vd = vv->kind();

                        switch(vd)
                        {
                                case(Input_Var) :
                                {
                                        break;
                                }
                                case(Output_Var) :
                                {
                                        break;
                                }
                                case(Set_Var) :
                                {
                                        break;
                                }
                                case(Global_Var) :
                                {
                                        xmlTextWriterWriteVFormatString(writer, "\n\t\t\t", NULL);
                                        xmlTextWriterStartElement(writer, BAD_CAST "GLOBALVAR");
                                        sprintf(tmp, "%s", str(vv->name()));
                                        xmlTextWriterWriteVFormatString(writer, tmp, NULL);
                                        xmlTextWriterEndElement(writer);
                                        break;
                                }
                                default :
                                {
                                        xmlTextWriterWriteVFormatString(writer, "\n\t\t\t", NULL);
                                        xmlTextWriterStartElement(writer, BAD_CAST "EXISTSVAR");
                                        sprintf(tmp, "%s", str(vv->name()));
                                        xmlTextWriterWriteVFormatString(writer, tmp, NULL);
                                        xmlTextWriterEndElement(writer);
                                        break;
                                }
                        }

                }


                for(EQ_Iterator ei = (*di)->EQs(); ei; ei++)
                {

                        //<EQ>
                        xmlTextWriterWriteVFormatString(writer, "\n\t\t\t", NULL);
                        xmlTextWriterStartElement(writer, BAD_CAST "EQ");

                        for(Constr_Vars_Iter cvi(*ei); cvi; cvi++)
                        {
                                xmlTextWriterWriteVFormatString(writer, "\n\t\t\t\t", NULL);
                                xmlTextWriterStartElement(writer, BAD_CAST "VAREQ");
                                sprintf(tmp, "%d", (*cvi).coef);
                                xmlTextWriterWriteAttribute(writer, BAD_CAST "COEF", BAD_CAST tmp);
                                sprintf(tmp, "%s", (*cvi).var->char_name());
                                xmlTextWriterWriteVFormatString(writer, tmp, NULL);
                                xmlTextWriterEndElement(writer);
                        }

                        // Dopisz stala
                        xmlTextWriterWriteVFormatString(writer, "\n\t\t\t\t", NULL);
                        xmlTextWriterStartElement(writer, BAD_CAST "CONSTEQ");
                        sprintf(tmp, "%d", (*ei).get_const());
                        xmlTextWriterWriteVFormatString(writer, tmp, NULL);
                        xmlTextWriterEndElement(writer);

                        // </EQ>
                        xmlTextWriterWriteVFormatString(writer, "\n\t\t\t", NULL);
                        xmlTextWriterEndElement(writer);

                }


                for(GEQ_Iterator gi = (*di)->GEQs(); gi; gi++)
                {

                        //<GEQ>
                        xmlTextWriterWriteVFormatString(writer, "\n\t\t\t", NULL);
                        xmlTextWriterStartElement(writer, BAD_CAST "GEQ");

                        for(Constr_Vars_Iter cvi(*gi); cvi; cvi++)
                        {
                                xmlTextWriterWriteVFormatString(writer, "\n\t\t\t\t", NULL);
                                xmlTextWriterStartElement(writer, BAD_CAST "VARGEQ");
                                sprintf(tmp, "%d", (*cvi).coef);
                                xmlTextWriterWriteAttribute(writer, BAD_CAST "COEF", BAD_CAST tmp);
                                sprintf(tmp, "%s", (*cvi).var->char_name());
                                xmlTextWriterWriteVFormatString(writer, tmp, NULL);
                                xmlTextWriterEndElement(writer);


                        }

                        // Dopisz stala
                        xmlTextWriterWriteVFormatString(writer, "\n\t\t\t\t", NULL);
                        xmlTextWriterStartElement(writer, BAD_CAST "CONSTGEQ");
                        sprintf(tmp, "%d", (*gi).get_const());
                        xmlTextWriterWriteVFormatString(writer, tmp, NULL);
                        xmlTextWriterEndElement(writer);

                        // </GEQ>
                        xmlTextWriterWriteVFormatString(writer, "\n\t\t\t", NULL);
                        xmlTextWriterEndElement(writer);



                }

                // </CONJUNCT>
                xmlTextWriterWriteVFormatString(writer, "\n\t\t", NULL);
                xmlTextWriterEndElement(writer);


        }



        // </CONJUNCTS>
        xmlTextWriterWriteVFormatString(writer, "\n\t", NULL);
        xmlTextWriterEndElement(writer);


        // </RELATION>
        xmlTextWriterWriteVFormatString(writer, "\n", NULL);
        xmlTextWriterEndElement(writer);

        // KONIEC XML
        xmlTextWriterEndDocument(writer);
        xmlFreeTextWriter(writer);

        delete tmp;

        return 0;

        // odczytanie zmiennych sparametryzowanych - wyszukanie wszystkich znaczników GLOBALVAR i usuniecie powtarzajacych sie po nazwie
}

static void processNode(xmlTextReaderPtr reader, Relation R);

Relation Xml2Relation(const char *filename)
{
        xmlTextReaderPtr reader;  // parser
    char* tmp = new char[100];

        int ret;
        int is_set = 1; // 0 - relacja, 1 - zbior
        Relation R;

        int dimi, dimo, dims;

        Variable_ID *var_in, *var_out, *var_set;
        int count_in, count_out, count_set; // liczniki

    count_in = count_out = count_set = 0;
        int count_par = 0;

        reader = xmlReaderForFile(filename, NULL, 0);

    if (reader != NULL) {

                ret = xmlTextReaderRead(reader);

                while (ret == 1) {  //czytaj dopoki jest element


                        const xmlChar *name, *value;  //Nazwa i wartosc
                        name = xmlTextReaderConstName(reader);


                        if (!(name == NULL || xmlTextReaderNodeType(reader)==13))  //kiedy nazwa nie jest pusta lub nie whitespace
                        {
                                //RELATION
                                if(xmlStrEqual(name, xmlCharStrdup("RELATION")))  //znacznik poczatkowy
                                {
                                        if(xmlTextReaderHasAttributes(reader) == 1)
                                        {
                                        //sprawdz relacje jaki ma typ
                                        xmlTextReaderMoveToFirstAttribute(reader);
                                        name = xmlTextReaderConstName(reader);
                                        value = xmlTextReaderConstValue(reader);
                                        // jest relacja
                                        if(xmlStrEqual(name, xmlCharStrdup("kind")) && xmlStrEqual(value, xmlCharStrdup("relation")))
                                        is_set = 0;

                                        if(xmlStrEqual(name, xmlCharStrdup("kind")) && xmlStrEqual(value, xmlCharStrdup("set")))
                                        is_set = 1;

                                        }
                                }

                                //DIMI
                                if(xmlStrEqual(name, xmlCharStrdup("DIMI")) && !is_set && xmlTextReaderNodeType(reader)!=15)  //znacznik poczatkowy
                                {
                                        ret = xmlTextReaderRead(reader);
                                        value = xmlTextReaderConstValue(reader);
                                        sprintf(tmp, "%s", value);
                                        dimi = atoi(tmp);

                                        //alokuj tablice
                                        var_in = new Variable_ID[dimi];
                                }

                                //DIMO
                                if(xmlStrEqual(name, xmlCharStrdup("DIMO")) && !is_set && xmlTextReaderNodeType(reader)!=15)  //znacznik poczatkowy
                                {
                                        ret = xmlTextReaderRead(reader);
                                        value = xmlTextReaderConstValue(reader);
                                        sprintf(tmp, "%s", value);
                                        dimo = atoi(tmp);

                                        //alokuj tablice
                                        var_out = new Variable_ID[dimo];
                                }

                                //DIMS
                                if(xmlStrEqual(name, xmlCharStrdup("DIMS")) && is_set && xmlTextReaderNodeType(reader)!=15)  //znacznik poczatkowy
                                {
                                        ret = xmlTextReaderRead(reader);
                                        value = xmlTextReaderConstValue(reader);
                                        sprintf(tmp, "%s", value);
                                        dims = atoi(tmp);

                                        //alokuj tablice
                                        var_set = new Variable_ID[dims];
                                }

                                // </DIM>
                                if(xmlStrEqual(name, xmlCharStrdup("DIM")) && xmlTextReaderNodeType(reader)==15)
                                {
                                        // buduj relacje
                                        if(is_set) //jesli zbior
                                        {
                                                Relation R_temp(dims);
                                                R = R_temp;

                                                //aloklacja zmiennych
                                        }
                                        else //jesli relacja
                                        {
                                                Relation R_temp(dimi, dimo);
                                                R = R_temp;
                                        }



                                }

                                //nazwij je name_set_var i przypisz do tablic

                                //dopoki nie ma /VARIABLES
                                if(xmlStrEqual(name, xmlCharStrdup("VARIABLES")) && xmlTextReaderNodeType(reader)!=15)
                                {
                                while(!(xmlStrEqual(name, xmlCharStrdup("VARIABLES")) && xmlTextReaderNodeType(reader)==15))
                                {
                                        ret = xmlTextReaderRead(reader);
                                        name = xmlTextReaderConstName(reader);

                                        if(xmlStrEqual(name, xmlCharStrdup("INPUT")) && !is_set && xmlTextReaderNodeType(reader)!=15 && !is_set)
                                        {
                                                count_in++;

                                                ret = xmlTextReaderRead(reader);
                                                value = xmlTextReaderConstValue(reader);
                                                sprintf(tmp, "%s", value);

                                                R.name_input_var(count_in, tmp);

                                                var_in[count_in-1] = R.input_var(count_in);
                                        }

                                        if(xmlStrEqual(name, xmlCharStrdup("OUTPUT")) && !is_set && xmlTextReaderNodeType(reader)!=15 && !is_set)
                                        {
                                                count_out++;

                                                ret = xmlTextReaderRead(reader);
                                                value = xmlTextReaderConstValue(reader);
                                                sprintf(tmp, "%s", value);

                                                R.name_output_var(count_out, tmp);

                                                var_out[count_out-1] = R.output_var(count_out);


                                        }
                                        if(xmlStrEqual(name, xmlCharStrdup("SET")) && !is_set && xmlTextReaderNodeType(reader)!=15 && is_set)
                                        {
                                                count_set++;

                                                ret = xmlTextReaderRead(reader);
                                                value = xmlTextReaderConstValue(reader);
                                                sprintf(tmp, "%s", value);

                                                R.name_set_var(count_set, tmp);

                                                var_set[count_set-1] = R.set_var(count_set);
                                        }



                                } //while
                                }









                        }



                        ret = xmlTextReaderRead(reader);
        }

        xmlFreeTextReader(reader);

                if (ret != 0) {
            fprintf(stderr, "%s : failed to parse\n", filename);
        }
    }

        else
       fprintf(stderr, "Unable to open %s\n", filename);

        //
    // Cleanup function for the XML library.
    ///
    xmlCleanupParser();
    //
    // this is to debug memory for regression tests
    //
    xmlMemoryDump();


        return R;
}

