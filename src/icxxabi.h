
#define ATEXIT_MAX_FUNCTIONS 32
#ifndef ICXXABI_H
#define ICXXABI_H

#ifdef __cplusplus
extern "C" {
#endif

void __cxa_pure_virtual();

struct atexit_entry_t
{
  void (*destructor)(void*);
  void* obj_ptr;
  void* dso_handle;
};
int __cxa_atexit(void (*dtor)(void*),void* objptr,void* dso);
void __cxa_finalize(void *f);

#ifdef __cplusplus
};
#endif

#endif
