#include "heap.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#define TAMANIO_INICIAL 1024

typedef enum pos_registradas
{
	PADRE,
	HIJO_IZQ,
	HIJO_DER
} TIPO_DE_HIJO;

struct heap
{
	size_t cant;
	size_t tam;
	cmp_func_t cmp;
	void **data;
};

size_t obtener_ubicacion( size_t pos_a_iniciar, TIPO_DE_HIJO info )
{
	switch( info )
	{
		case PADRE:    return ( ( pos_a_iniciar - 1 ) / 2 );
		case HIJO_IZQ: return ( ( 2 * pos_a_iniciar ) + 1 );
		case HIJO_DER: return ( ( 2 * pos_a_iniciar ) + 2 );
	}
	return 0;
}

void swap( void **a, void **b )
{
	void *tmp = *a;
	
	*a = *b;
	*b = tmp;
}

void up_heap( heap_t* heap )
{
	size_t posicion = heap_cantidad(heap);
	
	while( posicion > 0 )
	{
		size_t posicion_padre = obtener_ubicacion(posicion, PADRE);
		
		int comparacion = heap->cmp(heap->data[posicion], heap->data[posicion_padre]);
		
		if( comparacion > 0 )
		{
			swap( &heap->data[posicion], &heap->data[posicion_padre] );
			posicion = posicion_padre;
		}
		else
			return;
	}
}

void down_heap( void** datos, size_t inicio, size_t final, cmp_func_t cmp )
{
	size_t auxiliar = inicio;
	size_t hijo_izq = obtener_ubicacion(auxiliar, HIJO_IZQ);
	size_t hijo_der = obtener_ubicacion(auxiliar, HIJO_DER);
	
	int comparar;
	
	if( hijo_izq == final )
	{
		comparar = cmp(datos[auxiliar], datos[hijo_izq]);
		
		if( comparar < 0 )
			swap( &datos[auxiliar], &datos[hijo_izq] );
	}
	else
	{
		if( hijo_izq < final )
		{
			comparar = cmp(datos[hijo_izq], datos[hijo_der]);
			
			if( comparar > 0 )
				auxiliar = hijo_izq;
			else
				auxiliar = hijo_der;
			
			comparar = cmp(datos[inicio], datos[auxiliar]);
			
			if( comparar < 0 )
			{
				swap( &datos[inicio], &datos[auxiliar] );
				down_heap( datos, auxiliar, final, cmp );
			}
		}
	}
}

void heapify( void **datos, size_t cant_elementos, cmp_func_t cmp )
{
	size_t mitad = cant_elementos / 2;
	
	while( mitad )
	{
		down_heap(datos, mitad, cant_elementos, cmp);
		mitad--;
	}
	down_heap(datos, 0, cant_elementos, cmp);
}

bool heap_redimensionar( heap_t* heap, size_t n_tamanio )
{
	void **data_nueva = realloc( heap->data, n_tamanio * sizeof(void *) );
	
	if( !data_nueva ) 
		return false;
		
	heap->data = data_nueva;
	heap->tam = n_tamanio;
	
	return true;
}

void heap_sort( void *elementos[ ], size_t cant, cmp_func_t cmp)
{
	heapify( elementos, cant - 1, cmp );
	cant--;
	
	while( cant > 0 )
	{
		swap( &elementos[0], &elementos[cant] );
		down_heap( elementos, 0, cant - 1, cmp );
		cant--;
	}
}

heap_t *heap_crear( cmp_func_t cmp )
{
	heap_t *n_Heap = malloc( sizeof( heap_t ) );
	
	if( !n_Heap )
		return NULL;
		
	n_Heap->data = malloc( TAMANIO_INICIAL * sizeof(void *) );
	
	if( !n_Heap->data )
	{
		free(n_Heap);
		return NULL;
	}
	n_Heap->tam = TAMANIO_INICIAL;
	n_Heap->cant = 0;
	n_Heap->cmp = cmp;
	
	return n_Heap;
}

void heap_destruir(heap_t *heap, void destruir_elemento(void *e))
{
	if( destruir_elemento )
		for( int i = 0; i < heap->cant; i++ )
			destruir_elemento(heap->data[ i ]);
	
	free(heap->data);
	free(heap);
}

size_t heap_cantidad(const heap_t *heap)
{
	return heap->cant;
}

bool heap_esta_vacio(const heap_t *heap)
{
	return ( heap && !heap->cant );
}

bool heap_encolar(heap_t *heap, void *elem)
{
	if( heap->cant >= heap->tam )
	{
		if( !heap_redimensionar(heap, (2 * (heap->tam + 1) ) ) )
			return false;
	}
	heap->data[heap->cant] = elem;
	up_heap(heap);
	heap->cant++;
	
	return true;
}

void *heap_ver_max(const heap_t *heap)
{
	return ( heap && !heap_esta_vacio(heap) ) ? heap->data[ 0 ] : NULL;
}

void *heap_desencolar(heap_t *heap)
{
	if( heap_esta_vacio(heap) )
		return NULL;
	
	void* ret = heap_ver_max(heap);
	
	heap->data[ 0 ] = heap->data[ heap->cant - 1 ];
	
	down_heap( heap->data, 0, heap_cantidad( heap ) - 1, heap->cmp );
	
	heap->cant--;
	
	if( heap->cant < ( heap->tam / 4 ) && (heap->tam / 2) >= TAMANIO_INICIAL )
	{
		heap_redimensionar(heap, heap->tam / 2);
	}
	
	return ret;
}
