/* $Id: chresc.c,v 1.1.1.1 2004/12/23 04:04:19 ellson Exp $ $Revision: 1.1.1.1 $ */
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

/*
 * Glenn Fowler
 * AT&T Research
 *
 * return the next character in the string s
 * \ character constants are converted
 * p is updated to point to the next character in s
 */

#include <ast.h>
/* #include <ccode.h> */

int chresc(register const char *s, char **p)
{
    register const char *q;
    register int c;

    switch (c = *s++) {
    case 0:
	s--;
	break;
    case '\\':
	switch (c = *s++) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	    c -= '0';
	    q = s + 2;
	    while (s < q)
		switch (*s) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		    c = (c << 3) + *s++ - '0';
		    break;
		default:
		    q = s;
		    break;
		}
	    break;
	case 'a':
	    c = CC_bel;
	    break;
	case 'b':
	    c = '\b';
	    break;
	case 'f':
	    c = '\f';
	    break;
	case 'n':
	    c = '\n';
	    break;
	case 'r':
	    c = '\r';
	    break;
	case 's':
	    c = ' ';
	    break;
	case 't':
	    c = '\t';
	    break;
	case 'v':
	    c = CC_vt;
	    break;
	case 'x':
	    c = 0;
	    q = s;
	    while (q)
		switch (*s) {
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		    c = (c << 4) + *s++ - 'a' + 10;
		    break;
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		    c = (c << 4) + *s++ - 'A' + 10;
		    break;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		    c = (c << 4) + *s++ - '0';
		    break;
		default:
		    q = 0;
		    break;
		}
	    break;
	case 'E':
	    c = CC_esc;
	    break;
	case 0:
	    s--;
	    break;
	}
	break;
    }
    if (p)
	*p = (char *) s;
    return c;
}
