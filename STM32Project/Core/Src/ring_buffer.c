/*
 * ring_buffer.c
 *
 *  Created on: Aug 15, 2024
 *      Author: Gabriela
 */

#include "ring_buffer.h"


void ring_buffer_init(ring_buffer_t *rb, uint8_t *mem, uint8_t cap)
{
    rb->buffer = mem;
    rb->capacity = cap;
    ring_buffer_reset(rb);
}
/*
 *  @brief Esta función reinicia los datos disponibles en el buffer
 *
 *  @retval 0 para volver las banderas a su estado inicial
 */
void ring_buffer_reset(ring_buffer_t *rb)
{
    rb->head = 0;
    rb->tail = 0;
    rb->is_full = 0;
}


/*
 *  @brief Esta función calcula los datos disponibles en el buffer
 *
 *  @retval size: cantidad de datos disponibles
 */

uint8_t ring_buffer_size(ring_buffer_t *rb)
{
    if (rb->is_full) {
        return rb->capacity;
    }
    if (rb->head >= rb->tail) {
        return rb->head - rb->tail;
    }
    return (rb->capacity - rb->tail) + rb->head;
}

/*
 *  @brief Esta función revisa si el buffer esta lleno
 *
 *  @retval is full: 1 si esta lleno, 0 de lo contrario
 */
uint8_t ring_buffer_is_full(ring_buffer_t *rb)
{
    return  rb->is_full;
}

/*
 *  @brief Esta función revisa si el buffer esta vacio
 *
 *  @retval 1 si esta vacio, 0 de lo contrario
 */
uint8_t ring_buffer_is_empty(ring_buffer_t *rb)
{
    return ((rb->head == rb->tail) && !rb->is_full) ? 1 : 0;
}

/**
 *  @brief Esta función escribe un dato en el buffer circular
 *
 *  @param data: El dato que se va a escribir
 *
 *  @retval Ninguno
 */

void ring_buffer_write(ring_buffer_t *rb, uint8_t data)
{
    rb->buffer[rb->head] = data;
    rb->head = (rb->head + 1) % rb->capacity;

    if (rb->is_full) {
        rb->tail = (rb->tail + 1) % rb->capacity;
    }

    rb->is_full = (rb->head == rb->tail);
}

/**
 *  @brief Esta función lee un dato en el buffer circular
 *
 *  @param data: La dirección de donde se va escribir el dato
 *
 *  @retval 1: Hay datos disponibles, 0: No hay datos
 */

uint8_t ring_buffer_read(ring_buffer_t *rb, uint8_t *byte)
{
    if (ring_buffer_is_empty(rb)) {
        return 0; // buffer vacio
    }

    *byte = rb->buffer[rb->tail];
    rb->tail = (rb->tail + 1) % rb->capacity;
    rb->is_full = 0;

    return 1; // buffer con datos
}
