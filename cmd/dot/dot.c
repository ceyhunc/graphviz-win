/**********************************************************
*      This software is part of the graphviz package      *
*                http://www.graphviz.org/                 *
*                                                         *
*            Copyright (c) 1994-2004 AT&T Corp.           *
*                and is licensed under the                *
*            Common Public License, Version 1.0           *
*                      by AT&T Corp.                      *
*                                                         *
*        Information and Software Systems Research        *
*              AT&T Research, Florham Park NJ             *
**********************************************************/

/*
* Written by Stephen North and Eleftherios Koutsofios.
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "gvc.h"
#include "globals.h"

#include <time.h>

char *Info[] = {
	"dot",			/* Program */
	VERSION,			/* Version */
	BUILDDATE			/* Build Date */
};

static GVC_t *Gvc;
static graph_t * G;

static graph_t *create_test_graph(void)
{
#define NUMNODES 5

	Agnode_t *node[NUMNODES];
	Agraph_t *g;
	int j, k;
	char name[10];

	/* Create a new graph */
	g = agopen("new_graph", AGDIGRAPH);

	/* Add nodes */
	for (j = 0; j < NUMNODES; j++) {
		sprintf(name, "%d", j);
		node[j] = agnode(g, name);
	}

	/* Connect nodes */
	for (j = 0; j < NUMNODES; j++) {
		for (k = j + 1; k < NUMNODES; k++) {
			agedge(g, node[j], node[k]);
		}
	}
	return g;
}

int main(int argc, char **argv)
{
	graph_t *prev = NULL;

	Gvc = gvNEWcontext(Info, gvUsername());
	gvParseArgs(Gvc, argc, argv);

	if (MemTest) {
		while (1) {
			/* Create a test graph */
			G = create_test_graph();

			/* Perform layout and cleanup */
			gvLayoutJobs(Gvc, G);  /* take layout engine from command line */
			gvFreeLayout(Gvc, G);

			/* Delete graph */
			agclose(G);
		}
		assert(0);		/* should never exit loop */
	} else {
		while ((G = next_input_graph())) {
			if (prev) {
				gvFreeLayout(Gvc, prev);
				agclose(prev);
			}
			gvLayoutJobs(Gvc, G);  /* take layout engine from command line */
			gvRenderJobs(Gvc, G);
			prev = G;
		}
	}
	return (gvFreeContext(Gvc));
}
