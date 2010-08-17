#ifndef __BAIL_H__
#define __BAIL_H__

#ifdef __cplusplus
extern "C"
{
#endif

void bail(int exit_code, char const* const msg1, char const* const msg2);
void bail_with_errno(int exit_code, int use_errno, char const* const msg1, char const* const msg2);

#ifdef __cplusplus
}
#endif

#endif /* defined __BAIL_H__ */
