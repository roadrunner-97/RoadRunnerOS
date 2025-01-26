#pragma once
#include "private/interrupts_internal.h"

void kdisable_interrupts();
void kenable_interrupts();

typedef void (*irq_handler_t)(regs_t *r);

void install_irq_handler(int irq_index, irq_handler_t irq_handler);
void ack_PIT();