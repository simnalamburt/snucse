typedef struct ELE {
  int val;
  struct ELE *next;
} *list_ptr;

int rsum_list(list_ptr ls)
{
  if (!ls)
    return 0;
  else {
    int val = ls->val;
    int rest = rsum_list(ls->next);
    return val + rest;
  }
}
