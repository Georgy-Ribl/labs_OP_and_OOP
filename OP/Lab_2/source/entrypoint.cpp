#include "entrypoint.h"
#include "operations.h"

int doOperations(Operation op,
                 void* p1, void* p2,
                 void* p3, void* p4,
                 void* p5)
{
    return dispatchOperation(op, p1, p2, p3, p4, p5);
}
