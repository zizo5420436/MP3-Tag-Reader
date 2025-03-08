#ifndef TYPES_H
#define TYPES_H

/* User defined types */
typedef unsigned int uint;

/* Status will be used in fn. return type */

typedef enum
{
    e_success,
    e_failure
} Status;

typedef enum
{
    p_view,
    p_edit,
    p_help,
    p_unsupported
} OperationType;

#endif