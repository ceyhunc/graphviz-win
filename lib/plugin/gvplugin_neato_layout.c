/* $Id: gvplugin_neato_layout.c,v 1.1 2005/07/28 17:52:09 ellson Exp $ $Revision: 1.1 $ */
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

#include "gvplugin.h"

extern gvplugin_installed_t gvlayout_neato_types;

static gvplugin_api_t apis[] = {
    {API_layout, &gvlayout_neato_types},
    {(api_t)0, NULL},
};

gvplugin_library_t gvplugin_neato_layout_LTX_library = { "neato_layout", apis };
