// Exercise 8.7
// malloc accepts a size request without checking its plausibility;
// free believes that the block it is asked to free contains a valid 
// size field. Improve these routines so they take more pains with
// error checking.

#include <unistd.h>
#include <stdio.h>

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

static Header *morecore(unsigned nu);
void kr_free(void *ap);

/* malloc with error checking */
void *malloc_imp(unsigned nbytes){
  Header *p, *prevp;
  unsigned nunits;

  if(nbytes == 0){
    printf("malloc_imp: zero size request\n");
    return NULL;
  }

  nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;

  if((prevp = free_imp) == NULL){
    base.s.ptr = free_imp = prevp = &base;
    base.s.size = 0;
  }

  for(p = prevp->s.ptr; ; prevp = p, p = p->s.ptr){

    if(p->s.size >= nunits){
      if(p->s.size == nunits){
        prevp->s.ptr = p->s.ptr;
      } else {
        p->s.size -= nunits;
        p += p->s.size;
        p->s.size = nunits;
      }
      free_imp = prevp;
      return (void *)(p + 1);
    }

    if(p == free_imp){
      if((p = morecore(nunits)) == NULL){
        printf("malloc_imp: out of memory\n");
        return NULL;
      }
    }
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

/* free with error checking */
void kr_free(void *ap){
  Header *bp, *p;

  if(ap == NULL){
    printf("kr_free: null pointer\n");
    return;
  }

  bp = (Header *)ap - 1;

  if(bp->s.size == 0){
    printf("kr_free: invalid block size\n");
    return;
  }

  if(free_imp == NULL){
    base.s.ptr = free_imp = &base;
    base.s.size = 0;
  }

  for(p = free_imp; !(bp > p && bp < p->s.ptr); p = p->s.ptr){
    if(p >= p->s.ptr && (bp > p || bp < p->s.ptr))
      break;
  }

  if(bp + bp->s.size == p->s.ptr){
    if(p->s.ptr->s.size == 0){
      printf("kr_free: corrupted upper block\n");
      return;
    }
    bp->s.size += p->s.ptr->s.size;
    bp->s.ptr = p->s.ptr->s.ptr;
  } else {
    bp->s.ptr = p->s.ptr;
  }

  if(p + p->s.size == bp){
    if(p->s.size == 0){
      printf("kr_free: corrupted lower block\n");
      return;
    }
    p->s.size += bp->s.size;
    p->s.ptr = bp->s.ptr;
  } else {
    p->s.ptr = bp;
  }

  free_imp = p;
}

/* test */
int main(){
  int *arr = (int *)malloc_imp(5 * sizeof(int));

  if(!arr){
    printf("allocation failed\n");
    return 1;
  }

  for(int i = 0; i < 5; i++)
    arr[i] = i * 10;

  for(int i = 0; i < 5; i++)
    printf("%d ", arr[i]);

  printf("\n");

  kr_free(arr);

  return 0;
}
