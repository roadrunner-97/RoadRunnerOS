#pragma once
#include "stdbool.h"

typedef struct __attribute__((packed))
{
    bool lomem_himem_flag;
    bool boot_device_flag;
    bool cmdline_flag;
    bool boot_modules_flag;
    bool kernel_bin_symbol_table_flag; /* these are mutually exclusive */
    bool kernel_elf_symbol_table_flag;
    bool mem_map_flag;
    bool drive_map_flag;
    bool rom_config_flag;
}multiboot_flags_t;