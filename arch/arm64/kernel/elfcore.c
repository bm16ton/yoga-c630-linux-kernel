// SPDX-License-Identifier: GPL-2.0-only

#include <linux/coredump.h>
#include <linux/elfcore.h>
#include <linux/kernel.h>
#include <linux/mm.h>

#include <asm/cpufeature.h>
#include <asm/mte.h>

<<<<<<< HEAD
#define for_each_mte_vma(cprm, i, m)					\
	if (system_supports_mte())					\
		for (i = 0, m = cprm->vma_meta;				\
		     i < cprm->vma_count;				\
		     i++, m = cprm->vma_meta + i)			\
			if (m->flags & VM_MTE)

static unsigned long mte_vma_tag_dump_size(struct core_vma_metadata *m)
{
	return (m->dump_size >> PAGE_SHIFT) * MTE_PAGE_TAG_STORAGE;
=======
#define for_each_mte_vma(tsk, vma)					\
	if (system_supports_mte())					\
		for (vma = tsk->mm->mmap; vma; vma = vma->vm_next)	\
			if (vma->vm_flags & VM_MTE)

static unsigned long mte_vma_tag_dump_size(struct vm_area_struct *vma)
{
	if (vma->vm_flags & VM_DONTDUMP)
		return 0;

	return vma_pages(vma) * MTE_PAGE_TAG_STORAGE;
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
}

/* Derived from dump_user_range(); start/end must be page-aligned */
static int mte_dump_tag_range(struct coredump_params *cprm,
<<<<<<< HEAD
			      unsigned long start, unsigned long len)
=======
			      unsigned long start, unsigned long end)
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
{
	int ret = 1;
	unsigned long addr;
	void *tags = NULL;

<<<<<<< HEAD
	for (addr = start; addr < start + len; addr += PAGE_SIZE) {
=======
	for (addr = start; addr < end; addr += PAGE_SIZE) {
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
		struct page *page = get_dump_page(addr);

		/*
		 * get_dump_page() returns NULL when encountering an empty
		 * page table entry that would otherwise have been filled with
		 * the zero page. Skip the equivalent tag dump which would
		 * have been all zeros.
		 */
		if (!page) {
			dump_skip(cprm, MTE_PAGE_TAG_STORAGE);
			continue;
		}

		/*
		 * Pages mapped in user space as !pte_access_permitted() (e.g.
		 * PROT_EXEC only) may not have the PG_mte_tagged flag set.
		 */
		if (!test_bit(PG_mte_tagged, &page->flags)) {
			put_page(page);
			dump_skip(cprm, MTE_PAGE_TAG_STORAGE);
			continue;
		}

		if (!tags) {
			tags = mte_allocate_tag_storage();
			if (!tags) {
				put_page(page);
				ret = 0;
				break;
			}
		}

		mte_save_page_tags(page_address(page), tags);
		put_page(page);
		if (!dump_emit(cprm, tags, MTE_PAGE_TAG_STORAGE)) {
<<<<<<< HEAD
=======
			mte_free_tag_storage(tags);
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
			ret = 0;
			break;
		}
	}

	if (tags)
		mte_free_tag_storage(tags);

	return ret;
}

<<<<<<< HEAD
Elf_Half elf_core_extra_phdrs(struct coredump_params *cprm)
{
	int i;
	struct core_vma_metadata *m;
	int vma_count = 0;

	for_each_mte_vma(cprm, i, m)
=======
Elf_Half elf_core_extra_phdrs(void)
{
	struct vm_area_struct *vma;
	int vma_count = 0;

	for_each_mte_vma(current, vma)
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
		vma_count++;

	return vma_count;
}

int elf_core_write_extra_phdrs(struct coredump_params *cprm, loff_t offset)
{
<<<<<<< HEAD
	int i;
	struct core_vma_metadata *m;

	for_each_mte_vma(cprm, i, m) {
=======
	struct vm_area_struct *vma;

	for_each_mte_vma(current, vma) {
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
		struct elf_phdr phdr;

		phdr.p_type = PT_AARCH64_MEMTAG_MTE;
		phdr.p_offset = offset;
<<<<<<< HEAD
		phdr.p_vaddr = m->start;
		phdr.p_paddr = 0;
		phdr.p_filesz = mte_vma_tag_dump_size(m);
		phdr.p_memsz = m->end - m->start;
=======
		phdr.p_vaddr = vma->vm_start;
		phdr.p_paddr = 0;
		phdr.p_filesz = mte_vma_tag_dump_size(vma);
		phdr.p_memsz = vma->vm_end - vma->vm_start;
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
		offset += phdr.p_filesz;
		phdr.p_flags = 0;
		phdr.p_align = 0;

		if (!dump_emit(cprm, &phdr, sizeof(phdr)))
			return 0;
	}

	return 1;
}

<<<<<<< HEAD
size_t elf_core_extra_data_size(struct coredump_params *cprm)
{
	int i;
	struct core_vma_metadata *m;
	size_t data_size = 0;

	for_each_mte_vma(cprm, i, m)
		data_size += mte_vma_tag_dump_size(m);
=======
size_t elf_core_extra_data_size(void)
{
	struct vm_area_struct *vma;
	size_t data_size = 0;

	for_each_mte_vma(current, vma)
		data_size += mte_vma_tag_dump_size(vma);
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2

	return data_size;
}

int elf_core_write_extra_data(struct coredump_params *cprm)
{
<<<<<<< HEAD
	int i;
	struct core_vma_metadata *m;

	for_each_mte_vma(cprm, i, m) {
		if (!mte_dump_tag_range(cprm, m->start, m->dump_size))
=======
	struct vm_area_struct *vma;

	for_each_mte_vma(current, vma) {
		if (vma->vm_flags & VM_DONTDUMP)
			continue;

		if (!mte_dump_tag_range(cprm, vma->vm_start, vma->vm_end))
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
			return 0;
	}

	return 1;
}
