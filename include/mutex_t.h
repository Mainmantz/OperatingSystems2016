#include <xinu.h>

typedef int mutex_t;

extern mutex_t wormlock;

extern int currworms;
extern int procs[100];

extern int next;
