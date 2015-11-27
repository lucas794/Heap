#include "testing.h"
#include <stdlib.h>
#include <stdio.h>
#include "pruebas.h"

/* ******************************************************************
 *                        PROGRAMA PRINCIPAL
 * *****************************************************************/

int main(int argc, char *argv[])
{
    printf("~~~ PRUEBAS ALUMNO ~~~\n");
    pruebas_heap_alumno();

    return failure_count() > 0;
}
