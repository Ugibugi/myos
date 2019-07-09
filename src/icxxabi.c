#include <stdint.h>
#include "icxxabi.h"
#include "vga_term.h"

#ifdef __cplusplus
extern "C" {
#endif
atexit_entry_t __atexit_funcs[ATEXIT_MAX_FUNCTIONS];
uint32_t __atexit_funcs_count=0;
//void* __dso_handle=0;
void __cxa_pure_virtual(){}
int __cxa_atexit(void (*dtor)(void*),void* objptr,void* dso)
{
  if(__atexit_funcs_count >= ATEXIT_MAX_FUNCTIONS) return -1;
  __atexit_funcs[__atexit_funcs_count].destructor = dtor;
  __atexit_funcs[__atexit_funcs_count].obj_ptr = objptr;
  __atexit_funcs[__atexit_funcs_count].dso_handle = dso;
  __atexit_funcs_count++;
  return 0;
}

void __cxa_finalize(void* dtor)
{
  uint32_t it = __atexit_funcs_count;
  if(!dtor)
  {
    while(it--)
    {
      if(__atexit_funcs[it].destructor)
      {
        (*__atexit_funcs[it].destructor)(__atexit_funcs[it].obj_ptr);
      }
    }
  }
  else
  {
    while(it--)
    {
      if(__atexit_funcs[it].destructor == dtor)
      {
          (*__atexit_funcs[it].destructor)(__atexit_funcs[it].obj_ptr);
          __atexit_funcs[it].destructor = 0;
      }
    }
  }
}


#ifdef __cplusplus
};
#endif
