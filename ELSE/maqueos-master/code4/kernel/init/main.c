#include <xtos.h>

#define CSR_PRMD 0x1
#define CSR_ERA 0x6
#define CSR_PRMD_PPLV (3UL << 0)
#define CSR_PRMD_PIE (1UL << 2)
#define VMEM_SIZE (1UL << (9 + 9 + 12))
void walk();
void main()
{
	mem_init();
	con_init();
	excp_init();
	process_init();
	walk();
	int_on();
	asm volatile(
		"csrwr %0, %1\n"
		"csrwr $r0, %2\n"
		"li.d $sp, %3\n"
		"ertn\n"
		:
		: "r"(CSR_PRMD_PPLV | CSR_PRMD_PIE), "i"(CSR_PRMD), "i"(CSR_ERA), "i"(VMEM_SIZE));
}
void walk() {
    unsigned long vaddr, paddr;
    unsigned long *pgd, *pmd, *pte;

    for (vaddr = 0; vaddr < VMEM_SIZE; vaddr += PAGE_SIZE) {
        pgd = pgd_offset(0, vaddr);
        if (pgd_none(*pgd) || pgd_bad(*pgd))
            continue;

        pmd = pmd_offset(pgd, vaddr);
        if (pmd_none(*pmd) || pmd_bad(*pmd))
            continue;

        pte = pte_offset(pmd, vaddr);
        if (pte_none(*pte) || pte_bad(*pte))
            continue;

        paddr = pte_pfn(*pte) << PAGE_SHIFT;
        printk("%lx ~ %lx -> %lx ~ %lx\n", vaddr, vaddr + PAGE_SIZE, paddr, paddr + PAGE_SIZE);
    }
}
