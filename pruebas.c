
#include "heap.h"
#include "testing.h"
#include <stdbool.h>
#include <stdio.h>

int int_cmp(const void* a, const void* b){
    const int* a_i=a;
    const int* b_i=b;
    return *a_i-*b_i;
}

void pruebas_heap_vacio(void){
    heap_t* heap=heap_crear(int_cmp);
    print_test("Heap vacío...",heap_cantidad(heap)==0);
    print_test("Ver max es NULL...",heap_ver_max(heap)==NULL);
    print_test("Desencolar es NULL...",heap_desencolar(heap)==NULL);
    heap_destruir(heap,NULL);
}
void pruebas_enteros(void){
    heap_t* heap=heap_crear(int_cmp);
    printf("ELEMENTOS ORDENADOS:\n");
    int elementos[10]={0,1,2,3,4,5,6,7,8,9};
    bool ok=true;
    for(int i=0;i <10;i++){
        if(!(ok=heap_encolar(heap,&elementos[i]))){
            break;
        }
    }
    print_test("Se encolaron todos los elementos..",ok);
    print_test("Longitud correcta...",heap_cantidad(heap)==10);
    print_test("Ver max correcto...",heap_ver_max(heap)==&elementos[9]);
    for(int i=9;i>=0;i--){
        int* elemento=heap_desencolar(heap);
        if(!(ok=(*elemento==i))){
            break;
        }
    }
    print_test("Los elementos se desencolaron en orden...",ok)
    print_test("Longitud correcta...",heap_cantidad(heap)==0);
    print_test("Ver max correcto...",heap_ver_max(heap)==NULL);

    printf("ELEMENTOS DESORDENADOS:\n");
    int e_desordenados[10]={9,4,6,2,7,5,8,3,1,0};
    for(int i=0;i<10;i++){
        if(!(ok=heap_encolar(heap,&e_desordenados[i]))){
            break;
        }
    }
    print_test("Se encolaron todos los elementos..",ok);
    print_test("Longitud correcta...",heap_cantidad(heap)==10);
    print_test("Ver max correcto...",heap_ver_max(heap)==&elementos[9]);
    for(int i=9;i>=0;i--){
        int* elemento=heap_desencolar(heap);
        if(!(ok=(*elemento==i))){
            break;
        }
    }
    print_test("Los elementos se desencolaron en orden...",ok)
    print_test("Longitud correcta...",heap_cantidad(heap)==0);
    print_test("Ver max correcto...",heap_ver_max(heap)==NULL);
    heap_destruir(heap,NULL);
}
void pruebas_volumen(void){
    printf("PRUEBAS DE VOLUMEN:\n");
    heap_t* heap=heap_crear(int_cmp);
    int elementos[1000][1];
    bool ok=true;
    for(int i=0;i<1000;i++){
        *elementos[i]=i;
        if(!(ok=heap_encolar(heap,elementos[i]))){
            break;
        }
    }
    print_test("Se encolaron todos los elementos..",ok);
    print_test("Longitud correcta...",heap_cantidad(heap)==1000);
    print_test("Ver max correcto...",heap_ver_max(heap)==elementos[999]);
    for(int i=999;i>=0;i--){
        int* elemento=heap_desencolar(heap);
        if(!(ok=(*elemento==i))){
            break;
        }
    }
    print_test("Los elementos se desencolaron en orden...",ok)
    print_test("Longitud correcta...",heap_cantidad(heap)==0);
    print_test("Ver max correcto...",heap_ver_max(heap)==NULL);
    heap_destruir(heap,NULL);
}

void pruebas_heap_alumno(void){
    pruebas_heap_vacio();
    pruebas_enteros();
    pruebas_volumen();
}
