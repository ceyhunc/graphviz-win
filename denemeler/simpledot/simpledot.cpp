// simpledot.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "config.h"
#include "gvc.h"

static GVC_t *Gvc;
static graph_t * G;

char *Info[]={
	"simpledot", "1.0", "2013"
};

double _HUGE = 1e9;

int main(int argc, char* argv[])
{
	Gvc = gvNEWcontext(Info, gvUsername());
	gvParseArgs(Gvc, argc, argv);
	G=next_input_graph();
	gvLayoutJobs(Gvc, G);  /* take layout engine from command line */
	gvRenderJobs(Gvc, G);
	gvFreeContext(Gvc);

	return 0;
}

