#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"

#define VALOR_MAXIMO_DEFAULT 128

#define HIJO_IZQ(n) ((2*n))
#define HIJO_DER(n) (((2*n)+1))
#define PADRE(n) (((n-1)/2))

struct heap
{
	cmp_func_t f_cmp;
	size_t cant_elementos;
	size_t max_cant_elementos;
	void **arreglo_heap;
}


/* F AUXILIARES */
void swap( void *a, void *b )
{
	void tmp = *a;

	*a = *b;
	*b = temp;
}

/*void upheap( heap_t *heap, size_t posNodo )
{
	if( posNodo != 0 )
	{
		size_t padrepos = PADRE(posNodo);
		
		if( heap->f_cmp(heap->arreglo_heap[padrepos], heap->arreglo_heap[posNodo]) > 0 )
		{
			swap( &heap->arreglo_heap[padrepos], &heap->arreglo[posNodo] );
			upheap( heap, padrepos );
		}
	}
}*/

/* FIN F AUXILIARES */

heap_t *heap_crear(cmp_func_t cmp)
{
	heap_t* nHeap = malloc( sizeof( heap_t ) );

	if( !nHeap ) 
		return NULL;

	nHeap->f_cmp = cmp;
	nHeap->cant_elementos = 0;
	nHeap->max_cant_elementos = VALOR_MAXIMO_DEFAULT;

	nHeap->arreglo_heap = malloc( sizeof(void *) * nHeap->max_cant_elementos )

	if( !nHeap->arreglo_heap )
	{
		free(nHeap);
		return NULL;
	}
	
	for( size_t i = 0; i < nHeap->max_cant_elementos; i++ )
		nHeap->arreglo_heap[ i ] = NULL;

	return nHeap;
}

void heap_destruir(heap_t *heap, void destruir_elemento(void *e))
{	
	if( destruir_dato )
		for( size_t i = 0 ;i < heap->max_cant_elementos; i++)
			if( heap->arreglo_heap[i] )
				destruir_elemento(heap->arreglo_heap[i]);

	free(heap->arreglo_heap);
	free(heap);

	return;
}

size_t heap_cantidad(const heap_t *heap)
{
	return heap->cant_elementos;
}

bool heap_esta_vacio(const heap_t *heap)
{
	return !heap_cantidad(heap);
}

bool heap_encolar(heap_t *heap, void *elem)
{
	if( !elem )
		return false;

 	// nota: hay que redimensionar!!!
 	
	/*heap->arreglo_heap[cant_elementos] = elem;
	
	heap->cant_elementos++;
	
	upheap(heap->cant_elementos - 1);*/
	heap->cant_elementos++;
	
	size_t i = heap->cant_elementos - 1;
	
	while( i > 0 && heap->f_cmp(heap->arreglo_heap[ PADRE(i) ], elem) < 0 )
	{
		heap->arreglo_heap[ i ] = heap->arreglo_heap[ PADRE(i) ];
		i = PADRE(i);
	}
	heap->arreglo_heap[i] = elem;
}

void *heap_desencolar(heap_t *heap)
{
	void *max = heap->arreglo_heap[0]
	arreglo_heap[0] = heap->arreglo_heap[heap->cant_elementos -1];
	
	heap->cant_elementos--;
	
	max_heapify( heap, 0 ); // heapify es heapifiar a partir de lo heapifiado
}

void max_heapify( heap *heap, pos )
{
	size_t izq_index = HIJO_IZQ(pos);
	size_t der_index = HIJO_DER(pos);
	size_t pos_mayor = pos;
	
	if( izq_index < heap->cant_elementos && heap->f_cmp(heap->arreglo_heap[izq_index], heap->arreglo_heap[pos]) > 0 )
	{
		pos_mayor = izq_index;
	}
	else
	{
		pos_mayor = pos;
	}
	
	if( der_index < heap->cant_elementos && heap->f_cmp(heap->arreglo_heap[der_index], heap->arreglo_heap[pos_mayor]) > 0 )
	{
		pos_mayor = der_index;
	}
	
	if( pos_mayor != pos )
	{
		swap( &heap->arreglo_heap[pos], &heap->arreglo_heap[pos_mayor]);
		max_heapify( heap, pos_mayor );
	}
}

void *heap_ver_max(const heap_t *heap)
{
	return heap->heap[0];
}

