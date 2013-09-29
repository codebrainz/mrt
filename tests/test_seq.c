#include <mrt/list.h>
#include <mrt/list-link-impl.h>
#include <mrt/none.h>
#include <stdio.h>

int main()
{
  MRT_Seq *seq = mrt_list_new();

#if 0
  MRT_ListLink *link;
  link = mrt_list_link_new(mrt_none(), NULL, NULL);
  printf("Link: %p\n", link);
#endif

  MRT_Value *none = mrt_none();

  mrt_value_unref(none);

  //mrt_seq_add(seq, 0, mrt_none());
  //mrt_seq_add(seq, 0, mrt_none());
  //mrt_seq_add(seq, 0, mrt_none());

  printf("Number of Elements: %u\n", mrt_seq_size(seq));

  mrt_value_unref(MRT_VALUE(seq));

  return 0;
}
