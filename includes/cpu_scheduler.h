#ifndef CPU_SCHEDULER_H
# define CPU_SCHEDULER_H

typedef struct	input{
	int			(*function)(struct input *);
}				tinput;

typedef struct	node{
	int			data;
	struct node	prev;
	struct node	next;
}				tnode;

typedef struct	rdque{
	int			count;
	tnode		head;
	tnode		tail;
}				trdque;

#endif