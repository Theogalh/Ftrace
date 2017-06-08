/*
** type.c for type in /home/alexandre.kaczor/rendu/tek2/unix/PSU_2016_nmobjdump/src/nm
** 
** Made by Kaczor Alexandre
** Login   <alexandre.kaczor@epitech.net>
** 
** Started on  Sat Feb 18 12:43:05 2017 Kaczor Alexandre
** Last update Jan May 7 22:25:12 2017 Kaczor Alexandre
*/

#include "nm.h"

char	second_type(t_nm *this, Elf64_Sym sym, Elf64_Shdr *shdr, char c)
{
  if (shdr[sym.st_shndx].sh_type == SHT_NOBITS
      && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
    c = 'B';
  if ((shdr[sym.st_shndx].sh_type == SHT_PROGBITS
       && shdr[sym.st_shndx].sh_flags == SHF_ALLOC) ||
      (strcmp(&this->shtab[this->shdr[sym.st_shndx].sh_name], ".rodata") == 0))
    c = 'R';
  if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
      && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
    c = 'D';
  if ((shdr[sym.st_shndx].sh_type == SHT_PROGBITS
       && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR)))
    c = 'T';
  if (shdr[sym.st_shndx].sh_type == SHT_DYNAMIC)
    c = 'D';
  return c;
}

char	first_type(t_nm *this, Elf64_Sym sym, Elf64_Shdr *shdr, char c)
{
  if (ELF64_ST_BIND(sym.st_info) == STB_GNU_UNIQUE)
    c = 'u';
  else if (ELF64_ST_BIND(sym.st_info) == STB_WEAK &&
	   ELF64_ST_TYPE(sym.st_info) == STT_OBJECT)
    {
      c = 'V';
      if (sym.st_shndx == SHN_UNDEF)
	c = 'v';
    }
  else if (ELF64_ST_BIND(sym.st_info) == STB_WEAK)
    {
      c = 'W';
      if (sym.st_shndx == SHN_UNDEF)
	c = 'w';
    }
  else if (sym.st_shndx == SHN_ABS)
    c = 'A';
  else if (sym.st_shndx == SHN_COMMON)
    c = 'C';
  else if (sym.st_shndx == SHN_UNDEF)
    c = 'U';
  return (c == '?' ? second_type(this, sym, shdr, c) : c);
}

char	print_type(t_nm *this, Elf64_Sym sym, Elf64_Shdr *shdr)
{
  char	c;

  c = '?';
  (void)this;
  c = first_type(this, sym, shdr, c);
  if ((strcmp(SH_NAME, ".text") == 0) &&
      (sym.st_shndx == 18 || sym.st_shndx == 19 || sym.st_shndx == 20))
    c = 'T';
  else if (sym.st_shndx == 17 || sym.st_shndx == 18)
    c = 'T';
  else if (strcmp(SH_NAME, ".rodata") == 0)
    c = 'R';
  if (strcmp(&this->shtab[this->shdr[sym.st_shndx].sh_name], ".group") == 0)
    c = 'N';
  if (ELF64_ST_BIND(sym.st_info) == STB_LOCAL && c != '?')
    c += 32;
  return (c);
}
