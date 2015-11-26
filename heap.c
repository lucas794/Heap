#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"

#define VALOR_MAXIMO_DEFAULT 128

#define HIJO_IZQ(n) ((2*n)+1)
#define HIJO_DER(n) ((2*n)+2)
#define PADRE(n) (((n-1)/2))

struct heap
{
	cmp_func_t f_cmp;
	size_t cant_elementos;
	size_t max_cant_elementos;
	void **arreglo_heap;
};


/* F AUXILIARES */
void swap( void **a, void **b )
{
	void* tmp = *a;

	*a = *b;
	*b = tmp;
}

void up_heap( heap_t *heap )
{
	size_t ini = heap_cantidad(heap);
	
	while( ini > 0 )
	{
		size_t padre = PADRE(ini);
		
		int comparar = heap->f_cmp(heap->arreglo_heap[ini], heap->arreglo_heap[padre]);
		
		if( comparar > 0 )
		{
			swap( &heap->arreglo_heap[ini], &heap->arreglo_heap[padre] );
			ini = padre;
		}
		else
		{
			break;
		}
	}
}

bool heap_redimensionar( heap_t* heap, size_t nuevo_tamanio )
{
	void **data_nueva = realloc( heap->arreglo_heap, nuevo_tamanio * sizeof( void * ) );
	
	if( !data_nueva )
		return false;
		
	heap->arreglo_heap = data_nueva;
	heap->max_cant_elementos = nuevo_tamanio;
	
	return true;
}

void down_heap( void**dato, size_t start, size_t end, cmp_func_t cmp)
{
	size_t root = start;
	
	while( (root * 2 + 1) <= end )
	{
		size_t hijo = (root * 2 + 1);
		size_t cambio = root;
		
		if( cmp(dato[cambio], dato[hijo]) < 0 )
			cambio = hijo;
			
		if( hijo+1 <=end && cmp(dato[cambio], dato[hijo+1]) > 0 )
			cambio = hijo + 1;
		
		if( cambio== root )
			return;
		else
		{
			swap( &dato[root], &dato[cambio] );
			root = cambio;
		}
	}
}

void heapify( void *datos, size_t cant, cmp_func_t cmp )
{
	size_t mitad = (cant - 2) / 2;
	
	while( mitad >= 0 )
	{
		down_heap(datos, mitad, cant - 1, cmp);
		mitad = mitad - 1;
	}
}

/* FIN F AUXILIARES */

heap_t *heap_crear(cmp_func_t cmp)
{
	heap_t* nHeap = malloc( sizeof( heap_t ) );

	if( !nHeap ) 
		return NULL;

	nHeap->f_cmp = cmp;
	nHeap->cant_elementos = 0;
	nHeap->max_cant_elementos = VALOR_MAXIMO_DEFAULT;

	nHeap->arreglo_heap = malloc( sizeof(void *) * nHeap->max_cant_elementos );

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
	if( destruir_elemento )
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
 	
 	if( heap_cantidad(heap) >= heap->max_cant_elementos )
 	{		
		if( !heap_redimensionar(heap, ( 2 * ( heap_cantidad(heap) + 1 ) )) )
			return false;
	}
	heap->arreglo_heap[heap->cant_elementos] = elem;
	up_heap(heap);
	heap->cant_elementos++;
	
	return true;
}

void *heap_desencolar(heap_t *heap)
{
	if( heap_esta_vacio(heap) )
		return NULL;
		
	void *max = heap_ver_max( heap );
	
	heap->arreglo_heap[0] = heap->arreglo_heap[ heap->cant_elementos -1 ];
	
	down_heap( heap->arreglo_heap, 0, heap_cantidad(heap) - 1, heap->f_cmp );
	
	heap->cant_elementos--;
	
	if( heap_cantidad( heap ) < ( heap->max_cant_elementos / 4 ) )
		if( (heap->max_cant_elementos / 2) >= VALOR_MAXIMO_DEFAULT )
			heap_redimensionar( heap, heap_cantidad(heap) / 2 );

	return max;
}

void *heap_ver_max(const heap_t *heap)
{
	return (!heap || heap_esta_vacio(heap)) ? NULL : heap->arreglo_heap[0];
}

void heap_sort(void *elementos[], size_t largo, cmp_func_t cmp)
{
	heapify( elementos, largo, cmp );
	printf("heap sort wii\n");
	size_t final = largo - 1;
	
	while( final > 0 )
	{
		swap( &elementos[final], &elementos[0] );
		final--;
		down_heap(elementos, 0, final, cmp);
	}
}
