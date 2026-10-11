#pragma once

/**
 * @brief initialise the general descriptor table for code and data.
 */
void gdt_initialise();

/**
 * @brief initialise the interrupt descriptor table.
 */
void idt_initialise();

/**
 * @brief
 */
void irq_initialise();

/**
 * @brief
 */
void test_descriptor_tables();