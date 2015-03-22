typedef struct ELE {
  int val;
  struct ELE *next;
} *list_ptr;

int sum_list(list_ptr ls)
{
  int val = 0;
  while (ls) {
    val += ls->val;
    ls = ls->next;
  }
  return val;
}
