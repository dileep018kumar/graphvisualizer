/* $Id$ $Revision$ */
/* vim:set shiftwidth=4 ts=8: */

/*************************************************************************
 * Copyright (c) 2011 AT&T Intellectual Property 
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * Contributors: See CVS logs. Details at http://www.graphviz.org/
 *************************************************************************/

/* Note that, with the call to gvParseArgs(), this application assumes that
 * a known layout algorithm is going to be specified. This can be done either
 * using argv[0] or requiring the user to run this code with a -K flag specifying
 * which layout to use. In the former case, after this program has been built as
 * 'demo', you will need to rename it as one of the installed layout engines such
 * as dot, neato, sfdp, etc. 
 */
#include <graphviz/gvc.h>

char* to_string(int x) {
    assert(x > 0);
    char c[1000];
    int i = 0;
    while (x > 0) {
	    c[i++] += '0'+(x%10);
	    x /= 10;
    }
    c[i] = '\0';
    return c;
}

const int N = 105;
const int M = N * N;

int main(int argc, char **argv)
{
    Agraph_t *g;
    Agnode_t *v[N];
    Agedge_t *e[M];
    GVC_t *gvc;

    /* set up a graphviz context */
    gvc = gvContext();

    /* parse command line args - minimally argv[0] sets layout engine */
    gvParseArgs(gvc, argc, argv);

    /* Create a simple digraph */
    g = agopen("g", Agundirected, 0);
    
    int n, m;
    scanf("%d %d", &n, &m);
    //printf("%d %d read\n", n, m);
    assert(n > 0 && n < N);
    assert(m > 0 && m < M);
    for (int i=1;i<=n;++i) {
	    int p; 
	    scanf("%d", &p);
	    //printf("%d color of %d read\n", c, i);

        int x = i;

        char str[1000];
        int j = 0;
        while (x > 0) {
	        str[j++] = '0'+(x%10);
	        x /= 10;
        }
        str[j] = '\0';

	    v[i] = agnode(g, str, 1);
	    // agsafeset(v[i], "color", (c == 0 ? "red" : "blue"), "");
	    // agsafeset(v[i], "style", "filled", "");
        for (int k=0;k<p;++k) {
            char name[1000], value[1000];
            scanf("%s %s", name, value);
            agsafeset(v[i], name, value, "");
        }
    }
    for (int i=0;i<m;++i) {
	    //printf("enter edge %d : ", i);
	    int a, b;
        char str[100];
	    scanf("%d %d", &a, &b);
        // scanf("%s", str);
	    assert(a > 0 && a < N && b > 0 && b < N);
        // fprintf(stderr, "%s read\n", str);
	    e[i] = agedge(g, v[a], v[b], 0, 1);
        int p;
        scanf("%d", &p);
        for (int k=0;k<p;++k) {
            char name[1000], value[1000];
            scanf("%s %s", name, value);
            agsafeset(e[i], name, value, "");
        }
        // agsafeset(e[i], "label", "from 1 to 2", "");
	    //printf("%d %d edge added", a, b);
    }
    
    //n = agnode(g, "n", 1);
    //m = agnode(g, "m", 1);
    //e = agedge(g, n, m, 0, 1);

    /* Set an attribute - in this case one that affects the visible rendering */
    //agsafeset(n, "color", "red", "");

    /* Compute a layout using layout engine from command line args */
    gvLayoutJobs(gvc, g);

    /* Write the graph according to -T and -o options */
    gvRenderJobs(gvc, g);

    /* Free layout data */
    gvFreeLayout(gvc, g);

    /* Free graph structures */
    agclose(g);

    /* close output file, free context, and return number of errors */
    return (gvFreeContext(gvc));
}
