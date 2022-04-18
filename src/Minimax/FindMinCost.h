#ifndef FIND_MIN_H_SEEN
#define FIND_MIN_H_SEEN

#include "../Utils/Types.h"
#include "../Utils/Macros.h"
#include <limits.h>

void recur_fill_costs(decision_node_t *root, int depth);
void propagate_cost(decision_node_t *root);

#endif /* !FIND_MIN_H_SEEN */