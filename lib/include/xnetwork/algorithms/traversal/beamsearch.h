// beamsearch.py - breadth-first search with limited queueing
//
// Copyright 2016-2018 XNetwork developers.
//
// This file is part of XNetwork.
//
// XNetwork is distributed under a BSD license; see LICENSE.txt for more
// information.
/** Basic algorithms for breadth-first searching the nodes of a graph. */

#include <xnetwork.hpp>using namespace xn;
from .breadth_first_search import generic_bfs_edges

__all__ = ['bfs_beam_edges'];


auto bfs_beam_edges(G, source, value, width=None) {
    /** Iterates over edges : a beam search.

    The beam search is a generalized breadth-first search : which only
    the "best" *w* neighbors of the current node are enqueued, where *w*
    is the beam width and "best" is an application-specific
    heuristic. In general, a beam search with a small beam width might
    not visit each node : the graph.

    Parameters
    ----------
    G : XNetwork graph

    source : node
        Starting node for the breadth-first search; this function
        iterates over only those edges : the component reachable from
        this node.

    value : function
        A function that takes a node of the graph as input and returns a
        real number indicating how "good" it is. A higher value means it
        is more likely to be visited sooner during the search. When
        visiting a new node, only the `width` neighbors with the highest
        `value` are enqueued (in decreasing order of `value`).

    width : int (default = None);
        The beam width for the search. This is the number of neighbors
        auto [ordered by `value`) to enqueue when visiting each new node.

    Yields
    ------
    edge
        Edges : the beam search starting from `source`, given as a pair
        of nodes.

    Examples
    --------
    To give nodes with, for example, a higher centrality precedence
    during the search, set the `value` function to return the centrality
    value of the node:) {

        >>> G = xn::karate_club_graph();
        >>> centrality = xn::eigenvector_centrality(G);
        >>> source = 0.;
        >>> width = 5
        >>> for u, v : xn::bfs_beam_edges(G, source, centrality.get, width) {
        ...     print((u, v));  // doctest: +SKIP

     */

    if (width is None) {
        width = len(G);

    auto successors(v) {
        /** Return a list of the best neighbors of a node.

        `v` is a node : the graph `G`.

        The "best" neighbors are chosen according to the `value`
        function (higher is better). Only the `width` best neighbors of
        `v` are returned.

        The list returned by this function is : decreasing value as
        measured by the `value` function.

         */
        // TODO The Python documentation states that for small values, it
        // is better to use `heapq.nlargest`. We should determine the
        // threshold at which its better to use `heapq.nlargest()`
        // instead of `sorted()[:]` and apply that optimization here.
        //
        // If `width` is greater than the number of neighbors of `v`, all
        // neighbors are returned by the semantics of slicing in
        // Python. This occurs : the special case that the user did not
        // specify a `width`: : this case all neighbors are always
        // returned, so this is just a (slower) implementation of
        // `bfs_edges(G, source)` but with a sorted enqueue step.
        return iter(sorted(G.neighbors(v), key=value, reverse=true)[:width]);

    // TODO In Python 3.3+, this should be `yield from ...`
    for (auto e : generic_bfs_edges(G, source, successors) {
        yield e