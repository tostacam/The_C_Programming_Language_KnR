// 4.11.3 Conditional Inclusion

#if SYSTEM == SYSV
  #define HDR "sysv.h"
#elif SYSTEM == BSD
  #define HDR "bsd.h"
#elif SYSTEM == MSDOS
  #define HDR "msdos.h"
#else
  #define HDR "default.h"
#endif

int main(){
  return 0;
}
