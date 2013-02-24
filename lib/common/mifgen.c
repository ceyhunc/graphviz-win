/* $Id: mifgen.c,v 1.7 2005/10/18 18:48:21 ellson Exp $ $Revision: 1.7 $ */
/* vim:set shiftwidth=4 ts=8: */

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


#include "render.h"

#define	NONE	0
#define	NODE	1
#define	EDGE	2
#define	CLST	3

/* MIF font modifiers */
#define REGULAR 0
#define BOLD	1
#define ITALIC	2

/* MIF patterns */
#define P_SOLID	0
#define P_NONE  15
#define P_DOTTED 4		/* i wasn't sure about this */
#define P_DASHED 11		/* or this */

/* MIF bold line constant */
#define WIDTH_NORMAL 1
#define WIDTH_BOLD 3

static int N_pages;
/* static 	point	Pages; */
static double Scale;
static int Rot;
static box PB;
static int onetime = TRUE;

typedef struct context_t {
    char color_ix, *fontfam, fontopt, font_was_set;
    char pen, fill, penwidth, style_was_set;
    double fontsz;
} context_t;

#define MAXNEST 4
static context_t cstk[MAXNEST];
static int SP;

static char *FillStr = "<Fill 3>";
static char *NoFillStr = "<Fill 15>";

static void mif_reset(void)
{
    onetime = TRUE;
}


static void init_mif(void)
{
    SP = 0;
    cstk[0].color_ix = 0;	/* MIF color index 0-7 */
    cstk[0].fontfam = "Times";	/* font family name */
    cstk[0].fontopt = REGULAR;	/* modifier: REGULAR, BOLD or ITALIC */
    cstk[0].pen = P_SOLID;	/* pen pattern style, default is solid */
    cstk[0].fill = P_NONE;
    cstk[0].penwidth = WIDTH_NORMAL;
}

static pointf mifpt(pointf p)
{
    pointf tmp, rv;
    tmp.x = p.x * Scale;
    tmp.y = Scale * p.y;
    if (Rot == 0) {
	rv.x = tmp.x;
	rv.y = PB.UR.y - PB.LL.y - tmp.y;
    } else {
	rv.x = PB.UR.x - PB.LL.x - tmp.y;
	rv.y = tmp.x;
    }
    return rv;
}

static void mifptarray(point * A, int n)
{
    int i;
    pointf p;

    fprintf(Output_file, " <NumPoints %d>\n", n);
    for (i = 0; i < n; i++) {
	p.x = A[i].x;
	p.y = A[i].y;
	p = mifpt(p);
	fprintf(Output_file, " <Point %.2f %.2f>\n", p.x, p.y);
    }
}

static void mif_font(context_t * cp)
{
    char *fw, *fa;

    fw = fa = "Regular";
    switch (cp->fontopt) {
    case BOLD:
	fw = "Bold";
	break;
    case ITALIC:
	fa = "Italic";
	break;
    }
    fprintf(Output_file,
	    "<Font <FFamily `%s'> <FSize %.1f pt> <FWeight %s> <FAngle %s>>\n",
	    cp->fontfam, Scale * cp->fontsz, fw, fa);
}

static void mif_color(int i)
{
    static char *mifcolor[] = {
	"black", "white", "red", "green", "blue", "cyan",
	"magenta", "yellow", "comment",
	"aquamarine", "plum", "peru", "pink", "mediumpurple", "grey",
	"lightgrey", "lightskyblue", "lightcoral", "yellowgreen",
	(char *) 0
    };
    if (i <= 8)
	fprintf(Output_file, "<Separation %d>\n", i);
    if (i > 8)
	fprintf(Output_file, "<ObColor `%s'>\n", mifcolor[i]);
}

static void mif_style(context_t * cp)
{
    fprintf(Output_file, "<Pen %d> <Fill %d> <PenWidth %d>\n",
	    cp->pen, cp->fill, cp->penwidth);
}

static void mif_comment(char *str)
{
    fprintf(Output_file, "# %s\n", str);
}

static void
mif_begin_job(FILE * ofp, graph_t * g, char **lib, char *user,
	      char *info[], point pages)
{
    /* Pages = pages; */
    N_pages = pages.x * pages.y;
    fprintf(Output_file,
	    "<MIFFile 3.00> # Generated by %s version %s (%s)\n", info[0],
	    info[1], info[2]);
    fprintf(Output_file, "# For: %s\n", user);
    fprintf(Output_file, "# Title: %s\n", g->name);
    fprintf(Output_file, "# Pages: %d\n", N_pages);
    fprintf(Output_file, "<Units Upt>\n");
    fprintf(Output_file, "<ColorCatalog \n");
    fprintf(Output_file, " <Color \n");
    fprintf(Output_file, "  <ColorTag `Black'>\n");
    fprintf(Output_file, "  <ColorCyan  0.000000>\n");
    fprintf(Output_file, "  <ColorMagenta  0.000000>\n");
    fprintf(Output_file, "  <ColorYellow  0.000000>\n");
    fprintf(Output_file, "  <ColorBlack  100.000000>\n");
    fprintf(Output_file, "  <ColorAttribute ColorIsBlack>\n");
    fprintf(Output_file, "  <ColorAttribute ColorIsReserved>\n");
    fprintf(Output_file, " > # end of Color\n");
    fprintf(Output_file, " <Color \n");
    fprintf(Output_file, "  <ColorTag `White'>\n");
    fprintf(Output_file, "  <ColorCyan  0.000000>\n");
    fprintf(Output_file, "  <ColorMagenta  0.000000>\n");
    fprintf(Output_file, "  <ColorYellow  0.000000>\n");
    fprintf(Output_file, "  <ColorBlack  0.000000>\n");
    fprintf(Output_file, "  <ColorAttribute ColorIsWhite>\n");
    fprintf(Output_file, "  <ColorAttribute ColorIsReserved>\n");
    fprintf(Output_file, " > # end of Color\n");
    fprintf(Output_file, " <Color \n");
    fprintf(Output_file, "  <ColorTag `Red'>\n");
    fprintf(Output_file, "  <ColorCyan  0.000000>\n");
    fprintf(Output_file, "  <ColorMagenta  100.000000>\n");
    fprintf(Output_file, "  <ColorYellow  100.000000>\n");
    fprintf(Output_file, "  <ColorBlack  0.000000>\n");
    fprintf(Output_file, "  <ColorAttribute ColorIsRed>\n");
    fprintf(Output_file, "  <ColorAttribute ColorIsReserved>\n");
    fprintf(Output_file, " > # end of Color\n");
    fprintf(Output_file, " <Color \n");
    fprintf(Output_file, "  <ColorTag `Green'>\n");
    fprintf(Output_file, "  <ColorCyan  100.000000>\n");
    fprintf(Output_file, "  <ColorMagenta  0.000000>\n");
    fprintf(Output_file, "  <ColorYellow  100.000000>\n");
    fprintf(Output_file, "  <ColorBlack  0.000000>\n");
    fprintf(Output_file, "  <ColorAttribute ColorIsGreen>\n");
    fprintf(Output_file, "  <ColorAttribute ColorIsReserved>\n");
    fprintf(Output_file, " > # end of Color\n");
    fprintf(Output_file, " <Color \n");
    fprintf(Output_file, "  <ColorTag `Blue'>\n");
    fprintf(Output_file, "  <ColorCyan  100.000000>\n");
    fprintf(Output_file, "  <ColorMagenta  100.000000>\n");
    fprintf(Output_file, "  <ColorYellow  0.000000>\n");
    fprintf(Output_file, "  <ColorBlack  0.000000>\n");
    fprintf(Output_file, "  <ColorAttribute ColorIsBlue>\n");
    fprintf(Output_file, "  <ColorAttribute ColorIsReserved>\n");
    fprintf(Output_file, " > # end of Color\n");
    fprintf(Output_file, " <Color \n");
    fprintf(Output_file, "  <ColorTag `Cyan'>\n");
    fprintf(Output_file, "  <ColorCyan  100.000000>\n");
    fprintf(Output_file, "  <ColorMagenta  0.000000>\n");
    fprintf(Output_file, "  <ColorYellow  0.000000>\n");
    fprintf(Output_file, "  <ColorBlack  0.000000>\n");
    fprintf(Output_file, "  <ColorAttribute ColorIsCyan>\n");
    fprintf(Output_file, "  <ColorAttribute ColorIsReserved>\n");
    fprintf(Output_file, " > # end of Color\n");
    fprintf(Output_file, " <Color \n");
    fprintf(Output_file, "  <ColorTag `Magenta'>\n");
    fprintf(Output_file, "  <ColorCyan  0.000000>\n");
    fprintf(Output_file, "  <ColorMagenta  100.000000>\n");
    fprintf(Output_file, "  <ColorYellow  0.000000>\n");
    fprintf(Output_file, "  <ColorBlack  0.000000>\n");
    fprintf(Output_file, "  <ColorAttribute ColorIsMagenta>\n");
    fprintf(Output_file, "  <ColorAttribute ColorIsReserved>\n");
    fprintf(Output_file, " > # end of Color\n");
    fprintf(Output_file, " <Color \n");
    fprintf(Output_file, "  <ColorTag `Yellow'>\n");
    fprintf(Output_file, "  <ColorCyan  0.000000>\n");
    fprintf(Output_file, "  <ColorMagenta  0.000000>\n");
    fprintf(Output_file, "  <ColorYellow  100.000000>\n");
    fprintf(Output_file, "  <ColorBlack  0.000000>\n");
    fprintf(Output_file, "  <ColorAttribute ColorIsYellow>\n");
    fprintf(Output_file, "  <ColorAttribute ColorIsReserved>\n");
    fprintf(Output_file, " > # end of Color\n");
    fprintf(Output_file, " <Color \n");
    fprintf(Output_file, "  <ColorTag `aquamarine'>\n");
    fprintf(Output_file, "  <ColorCyan  100.000000>\n");
    fprintf(Output_file, "  <ColorMagenta  0.000000>\n");
    fprintf(Output_file, "  <ColorYellow  18.000000>\n");
    fprintf(Output_file, "  <ColorBlack  0.000000>\n");
    fprintf(Output_file, " > # end of Color\n");
    fprintf(Output_file, " <Color \n");
    fprintf(Output_file, "  <ColorTag `plum'>\n");
    fprintf(Output_file, "  <ColorCyan  0.000000>\n");
    fprintf(Output_file, "  <ColorMagenta  100.000000>\n");
    fprintf(Output_file, "  <ColorYellow  0.000000>\n");
    fprintf(Output_file, "  <ColorBlack  33.000000>\n");
    fprintf(Output_file, " > # end of Color\n");
    fprintf(Output_file, " <Color \n");
    fprintf(Output_file, "  <ColorTag `peru'>\n");
    fprintf(Output_file, "  <ColorCyan  0.000000>\n");
    fprintf(Output_file, "  <ColorMagenta  24.000000>\n");
    fprintf(Output_file, "  <ColorYellow  100.000000>\n");
    fprintf(Output_file, "  <ColorBlack  32.000000>\n");
    fprintf(Output_file, " > # end of Color\n");
    fprintf(Output_file, " <Color \n");
    fprintf(Output_file, "  <ColorTag `pink'>\n");
    fprintf(Output_file, "  <ColorCyan  0.000000>\n");
    fprintf(Output_file, "  <ColorMagenta  50.000000>\n");
    fprintf(Output_file, "  <ColorYellow  0.000000>\n");
    fprintf(Output_file, "  <ColorBlack  0.000000>\n");
    fprintf(Output_file, " > # end of Color\n");
    fprintf(Output_file, " <Color \n");
    fprintf(Output_file, "  <ColorTag `mediumpurple'>\n");
    fprintf(Output_file, "  <ColorCyan  40.000000>\n");
    fprintf(Output_file, "  <ColorMagenta  100.000000>\n");
    fprintf(Output_file, "  <ColorYellow  0.000000>\n");
    fprintf(Output_file, "  <ColorBlack  0.000000>\n");
    fprintf(Output_file, " > # end of Color\n");
    fprintf(Output_file, " <Color \n");
    fprintf(Output_file, "  <ColorTag `grey'>\n");
    fprintf(Output_file, "  <ColorCyan  0.000000>\n");
    fprintf(Output_file, "  <ColorMagenta  0.000000>\n");
    fprintf(Output_file, "  <ColorYellow  0.000000>\n");
    fprintf(Output_file, "  <ColorBlack  50.000000>\n");
    fprintf(Output_file, " > # end of Color\n");
    fprintf(Output_file, " <Color \n");
    fprintf(Output_file, "  <ColorTag `lightgrey'>\n");
    fprintf(Output_file, "  <ColorCyan  0.000000>\n");
    fprintf(Output_file, "  <ColorMagenta  0.000000>\n");
    fprintf(Output_file, "  <ColorYellow  0.000000>\n");
    fprintf(Output_file, "  <ColorBlack  25.000000>\n");
    fprintf(Output_file, " > # end of Color\n");
    fprintf(Output_file, " <Color \n");
    fprintf(Output_file, "  <ColorTag `lightskyblue'>\n");
    fprintf(Output_file, "  <ColorCyan  38.000000>\n");
    fprintf(Output_file, "  <ColorMagenta  33.000000>\n");
    fprintf(Output_file, "  <ColorYellow  0.000000>\n");
    fprintf(Output_file, "  <ColorBlack  0.000000>\n");
    fprintf(Output_file, " > # end of Color\n");
    fprintf(Output_file, " <Color \n");
    fprintf(Output_file, "  <ColorTag `lightcoral'>\n");
    fprintf(Output_file, "  <ColorCyan  0.000000>\n");
    fprintf(Output_file, "  <ColorMagenta  50.000000>\n");
    fprintf(Output_file, "  <ColorYellow  60.000000>\n");
    fprintf(Output_file, "  <ColorBlack  0.000000>\n");
    fprintf(Output_file, " > # end of Color\n");
    fprintf(Output_file, " <Color \n");
    fprintf(Output_file, "  <ColorTag `yellowgreen'>\n");
    fprintf(Output_file, "  <ColorCyan  31.000000>\n");
    fprintf(Output_file, "  <ColorMagenta  0.000000>\n");
    fprintf(Output_file, "  <ColorYellow  100.000000>\n");
    fprintf(Output_file, "  <ColorBlack  0.000000>\n");
    fprintf(Output_file, " > # end of Color\n");
    fprintf(Output_file, "> # end of ColorCatalog\n");
}

static void mif_end_job(void)
{
    fprintf(Output_file, "# end of MIFFile\n");
}

static void mif_begin_graph(GVC_t * gvc, graph_t * g, box bb, point pb)
{
    PB = bb;
    if (onetime) {
	fprintf(Output_file, "<BRect %d %d %d %d>\n",
		PB.LL.x, PB.UR.y, PB.UR.x - PB.LL.x, PB.UR.y - PB.LL.y);
	init_mif();
	onetime = FALSE;
    }
}

static void
mif_begin_page(graph_t * g, point page, double scale, int rot,
	       point offset)
{
    /* int          page_number; */
    /* point        sz; */

    Scale = scale;
    Rot = rot;
    /* page_number =  page.x + page.y * Pages.x + 1; */
    /* sz = sub_points(PB.UR,PB.LL); */
    fprintf(Output_file,
	    " <ArrowStyle <TipAngle 15> <BaseAngle 90> <Length %.1f> <HeadType Filled>>\n",
	    14 * Scale);
}

static void mif_begin_context(void)
{
    assert(SP + 1 < MAXNEST);
    cstk[SP + 1] = cstk[SP];
    SP++;
}

static void mif_end_context(void)
{
    int c, psp = SP - 1;
    assert(SP > 0);
    if (cstk[SP].color_ix != (c = cstk[psp].color_ix))
	mif_color(c);
    if (cstk[SP].font_was_set)
	mif_font(&(cstk[psp]));
    if (cstk[SP].style_was_set)
	mif_style(&(cstk[psp]));
    /*free(cstk[psp].fontfam); */
    SP = psp;
}

static void mif_set_font(char *name, double size)
{
    char *p, *q;
    context_t *cp;

    cp = &(cstk[SP]);
    cp->font_was_set = TRUE;
    cp->fontsz = size;
    p = strdup(name);
    if ((q = strchr(p, '-'))) {
	*q++ = 0;
	if (strcasecmp(q, "italic") == 0)
	    cp->fontopt = ITALIC;
	else if (strcasecmp(q, "bold") == 0)
	    cp->fontopt = BOLD;
    }
    cp->fontfam = p;
    mif_font(&cstk[SP]);
}

static void mif_set_color(char *name)
{
    int i;
    char *tok;

    static char *mifcolor[] = {
	"black", "white", "red", "green", "blue", "cyan",
	"magenta", "yellow", "comment",
	"aquamarine", "plum", "peru", "pink", "mediumpurple", "grey",
	"lightgrey", "lightskyblue", "lightcoral", "yellowgreen",
	(char *) 0
    };

    tok = canontoken(name);
    for (i = 0; mifcolor[i]; i++) {
	if (strcasecmp(mifcolor[i], tok) == 0) {
	    cstk[SP].color_ix = i;
	    mif_color(i);
	    return;
	}
    }
    agerr(AGERR, "color %s not supported in MIF\n", name);
}

static void mif_set_style(char **s)
{
    char *line;
    context_t *cp;

    cp = &(cstk[SP]);
    while ((line = *s++)) {
	if (streq(line, "solid"))
	    cp->pen = P_SOLID;
	else if (streq(line, "dashed"))
	    cp->pen = P_DASHED;
	else if (streq(line, "dotted"))
	    cp->pen = P_DOTTED;
	else if (streq(line, "invis"))
	    cp->pen = P_NONE;
	else if (streq(line, "bold"))
	    cp->penwidth = WIDTH_BOLD;
	else if (streq(line, "filled"))
	    cp->fill = P_SOLID;
	else if (streq(line, "unfilled"))
	    cp->fill = P_NONE;
	else {
	    agerr(AGERR,
		  "mif_set_style: unsupported style %s - ignoring\n",
		  line);
	}
	cp->style_was_set = TRUE;
    }
    if (cp->style_was_set)
	mif_style(cp);
}

static char *mif_string(char *s)
{
    static char *buf = NULL;
    static int bufsize = 0;
    int pos = 0;
    char *p, esc;

    if (!buf) {
	bufsize = 64;
	buf = N_GNEW(bufsize, char);
    }

    p = buf;
    while (*s) {
	if (pos > (bufsize - 8)) {
	    bufsize *= 2;
	    buf = grealloc(buf, bufsize);
	    p = buf + pos;
	}
	esc = 0;
	switch (*s) {
	case '\t':
	    esc = 't';
	    break;
	case '>':
	case '\'':
	case '`':
	case '\\':
	    esc = *s;
	    break;
	}
	if (esc) {
	    *p++ = '\\';
	    *p++ = esc;
	    pos += 2;
	} else {
	    *p++ = *s;
	    pos++;
	}
	s++;
    }
    *p = '\0';
    return buf;
}

static void mif_textline(point p, textline_t * line)
{
    pointf mp;
    char *str = line->str;
    char *anchor;

    mp.x = p.x;
    mp.y = p.y - cstk[SP].fontsz / 2 + 2;
    switch (line->just) {
    case 'l':
	anchor = "Left";
	break;
    case 'r':
	anchor = "Right";
	break;
    default:
    case 'n':
	anchor = "Center";
	break;
    }
    mp = mifpt(mp);
    fprintf(Output_file,
	    "<TextLine <Angle %d> <TLOrigin %.2f %.2f> <TLAlignment %s>",
	    Rot, mp.x, mp.y, anchor);
    fprintf(Output_file, " <String `%s'>>\n", mif_string(str));
}

static void mif_bezier(point * A, int n, int arrow_at_start,
		       int arrow_at_end, int filled)
{
    fprintf(Output_file,
	    "<PolyLine <Fill 15> <Smoothed Yes> <HeadCap Square>\n");
    mifptarray(A, n);
    fprintf(Output_file, ">\n");
}

static void mif_polygon(point * A, int n, int filled)
{
    fprintf(Output_file, "<Polygon %s\n", (filled ? FillStr : NoFillStr));
    mifptarray(A, n);
    fprintf(Output_file, ">\n");
}

static void mif_ellipse(point p, int rx, int ry, int filled)
{
    pointf tl, mp;
    tl.x = p.x - rx;
    tl.y = p.y + ry;
    if (Rot) {
	int t;
	t = rx;
	rx = ry;
	ry = t;
    }
    mp = mifpt(tl);
    fprintf(Output_file, "<Ellipse %s <BRect %.2f %.2f %.1f %.1f>>\n",
	    filled ? FillStr : NoFillStr,
	    mp.x, mp.y, Scale * (rx + rx), Scale * (ry + ry));
}

static void mif_polyline(point * A, int n)
{
    fprintf(Output_file, "<PolyLine <HeadCap Square>\n");
    mifptarray(A, n);
    fprintf(Output_file, ">\n");
}

static void mif_user_shape(char *name, point * A, int n, int filled)
{
    static bool onetime = TRUE;
    if (onetime) {
	agerr(AGERR, "custom shapes not available with this driver\n");
	onetime = FALSE;
    }
}

codegen_t MIF_CodeGen = {
    mif_reset,
    mif_begin_job, mif_end_job,
    mif_begin_graph, 0,		/* mif_end_graph */
    mif_begin_page, 0,		/* mif_end_page */
    0, /* mif_begin_layer */ 0,	/* mif_end_layer */
    0, /* mif_begin_cluster */ 0, /* mif_end_cluster */
    0, /* mif_begin_nodes */ 0,	/* mif_end_nodes */
    0, /* mif_begin_edges */ 0,	/* mif_end_edges */
    0, /* mif_begin_node */  0,	/* mif_end_node */
    0, /* mif_begin_edge */  0,	/* mif_end_edge */
    mif_begin_context, mif_end_context,
    0, /* mif_begin_anchor */ 0,	/* mif_end_anchor */
    mif_set_font, mif_textline,
    mif_set_color, mif_set_color, mif_set_style,
    mif_ellipse, mif_polygon,
    mif_bezier, mif_polyline,
    0,				/* bezier_has_arrows */
    mif_comment,
    0,				/* mif_textsize */
    mif_user_shape,
    0				/* mif_usershapesize */
};
