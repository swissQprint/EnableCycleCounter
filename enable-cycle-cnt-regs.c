// https://matthewarcus.wordpress.com/2018/01/27/using-the-cycle-counter-registers-on-the-raspberry-pi-3/

#include <linux/module.h>
#include <linux/kernel.h>

void enable_ccr(void *info) {
#if defined __ARM_ARCH_7__ || defined __ARM_ARCH_7A__ || defined __ARM_ARCH_7R__ || defined __ARM_ARCH_7M__ || defined __ARM_ARCH_7S__
      // code taken from https://matthewarcus.wordpress.com/2018/01/27/using-the-cycle-counter-registers-on-the-raspberry-pi-3/

      // Set the User Enable register, bit 0
      asm volatile ("mcr p15, 0, %0, c9, c14, 0" :: "r" (1));
      // Enable all counters in the PNMC control-register
      asm volatile ("MCR p15, 0, %0, c9, c12, 0\t\n" :: "r"(1));
      // Enable cycle counter specifically
      // bit 31: enable cycle counter
      // bits 0-3: enable performance counters 0-3
      asm volatile ("MCR p15, 0, %0, c9, c12, 1\t\n" :: "r"(0x80000000));
#else
#error "Unknown machine. Possibly this module isn't needed at all."
#endif
}

int init_module(void) {
  // Each cpu has its own set of registers
  on_each_cpu(enable_ccr,NULL,0);
  printk (KERN_INFO "Userspace access to CCR enabled for ARM_V7.\n");
  return 0;
}
 
void cleanup_module(void) {
}


MODULE_LICENSE("MIT");
MODULE_AUTHOR("swissQprint");
MODULE_DESCRIPTION("performance monitoring registers - cycle count register");
MODULE_VERSION("1.0");

