/*
 * ring_buffer.c
 *
 *  Created on: Aug 15, 2024
 *      Author: Gabriela
 */

#include "ring_buffer.h"

#define capacity (8)
uint8_t ring_buffer[capacity];
uint8_t head_ptr;
uint8_t tail_ptr;

uint8_t is_full;

/*
 *  @brief Esta función reinicia el buffer
 *
 *  @retval 0 para volver las banderas a su estado inicial
 */
void ring_buffer_reset(void)
{
    head_ptr = 0;
    tail_ptr = 0;
    is_full = 0;
}

/*
 *  @brief Esta función calcula los datos disponibles en el buffer
 *
 *  @retval size: cantidad de datos disponibles
 */

uint8_t ring_buffer_size(void)
{
	uint8_t size = 0;
	if(head_ptr > tail_ptr){
		size = head_ptr - tail_ptr;
	}else{
		size = capacity - (tail_ptr - head_ptr);
	}
	return size;
}

/*
 *  @brief Esta función revisa si el buffer esta lleno
 *
 *  @retval 1 si esta lleno, 0 de lo contrario
 */
uint8_t ring_buffer_is_full(void)
{
    return ((head_ptr + 1) % capacity) == tail_ptr;
}

/*
 *  @brief Esta función revisa si el buffer esta vacio
 *
 *  @retval 1 si esta vacio, 0 de lo contrario
 */
uint8_t ring_buffer_is_empty(void)
{
    return (head_ptr == tail_ptr && !is_full);
}

/**
 *  @brief Esta función escribe un dato en el buffer circular
 *
 *  @param data: El dato que se va a escribir
 *
 *  @retval Ninguno
 */

void ring_buffer_write(uint8_t data)
{
	ring_buffer[head_ptr] = data;
	head_ptr = head_ptr + 1;

	if(head_ptr >= capacity){ //Si la cabeza llega al final de la memoria
			head_ptr= 0;
		}

	if(is_full !=0){ //si se pierden datos viejos
			tail_ptr = tail_ptr + 1;
		}

	if(tail_ptr >= capacity){ //Si la cola llega al final de la memoria
			tail_ptr= 0;
		}

	if(head_ptr == tail_ptr){ //si la cabeza alcanza la cola
			is_full = 1;
		}

}

/**
 *  @brief Esta función lee un dato en el buffer circular
 *
 *  @param data: La dirección de donde se va escribir el dato
 *
 *  @retval 1: Hay datos disponibles, 0: No hay datos
 */

uint8_t ring_buffer_read(uint8_t * byte)
{
	  if((is_full != 0) || (head_ptr != tail_ptr)){
		  *byte = ring_buffer[tail_ptr];
	      tail_ptr = tail_ptr +  1;
		  if(tail_ptr >=capacity){
			  tail_ptr = 0;
			  }
		  is_full = 0;
		  return 1; // buffer con datos
	  }
	return 0; //buffer vacio
}
