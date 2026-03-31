// Exercise 8.6
// The standard library function calloc(n, size) return a pointer to
// n objects of size size, with the storage initialized to zero. Write
// calloc, by calling malloc or by modifying it.

#include <stdio.h>
#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>

void *malloc_imp(unsigned nbytes);

void *calloc_imp(size_t n, size_t size){
  size_t total_size = n * size;
  unsigned char *ptr = (unsigned char *)malloc_imp(total_size);

  if (ptr == NULL)
    return NULL;

  for (size_t i = 0; i < total_size; ++i)
    ptr[i] = 0;

  return (void *)ptr;
}

typedef long Align;

union header {
  struct {
    union header *ptr;
    unsigned size;
  } s;
  Align x;
};

typedef union header Header;

static Header base;
static Header *free_imp = NULL;

#define NALLOC 1024

/* forward declarations */
static Header *morecore(unsigned);
void kr_free(void *ap);

/* malloc implementation */
void *malloc_imp(unsigned nbytes){
  Header *p, *prevp;
  unsigned nunits;

  nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;

  if((prevp = free_imp) == NULL){
    base.s.ptr = free_imp = prevp = &base;
    base.s.size = 0;
  }

  for(p = prevp->s.ptr; ; prevp = p, p = p->s.ptr){
    if(p->s.size >= nunits){
      if(p->s.size == nunits)           /* exact fit */
        prevp->s.ptr = p->s.ptr;
      else {                            /* allocate tail */
        p->s.size -= nunits;
        p += p->s.size;
        p->s.size = nunits;
      }
      free_imp = prevp;
      return (void *)(p + 1);
    }

    if(p == free_imp)                   /* wrapped around */
      if((p = morecore(nunits)) == NULL)
        return NULL;
  }
}

/* request more memory */
static Header *morecore(unsigned nu){
  char *cp;
  Header *up;

  if(nu < NALLOC)
    nu = NALLOC;

  cp = sbrk(nu * sizeof(Header));
  if(cp == (char *) -1)
    return NULL;

  up = (Header *) cp;
  up->s.size = nu;

  kr_free((void *)(up + 1));
  return free_imp;
}

/* free implementation */
void kr_free(void *ap){
  Header *bp, *p;

  bp = (Header *)ap - 1;

  for(p = free_imp; !(bp > p && bp < p->s.ptr); p = p->s.ptr){
    if(p >= p->s.ptr && (bp > p || bp < p->s.ptr))
      break;
  }

  if(bp + bp->s.size == p->s.ptr){
    bp->s.size += p->s.ptr->s.size;
    bp->s.ptr = p->s.ptr->s.ptr;
  } else {
    bp->s.ptr = p->s.ptr;
  }

  if(p + p->s.size == bp){
    p->s.size += bp->s.size;
    p->s.ptr = bp->s.ptr;
  } else {
    p->s.ptr = bp;
  }

  free_imp = p;
}

int main(){
  int *arr = (int *)calloc_imp(5, sizeof(int));

  if(arr == NULL){
    printf("Allocation failed\n");
    return 1;
  }

  for (int i = 0; i < 5; ++i)
    printf("%d ", arr[i]); // just printing zeros to check

  printf("\n");

  kr_free(arr);
  return 0;
}
