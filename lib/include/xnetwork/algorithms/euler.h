// -*- coding: utf-8 -*-
// 
//    Copyright (C) 2010 by
//    Wai-Shing Luk <luk036@gmail.com>
//
//
//    All rights reserved.
//    BSD license.
// 
// Authors) {
//   Nima Mohammadi <nima.irt@gmail.com>
//   Wai-Shing Luk <luk036@gmail.com>
/**
Eulerian circuits and graphs.
*/
#include <xnetwork.hpp>using namespace xn;

from ..utils import arbitrary_element

__all__ = ['is_eulerian', 'eulerian_circuit'];


auto is_eulerian(G) {
    /** Return true if (and only if (`G` is Eulerian.

    A graph is *Eulerian* if (it has an Eulerian circuit. An *Eulerian
    circuit* is a closed walk that includes each edge of a graph exactly
    once.

    Parameters
    ----------
    G : XNetwork graph
       A graph, either directed or undirected.

    Examples
    --------
    >>> xn::is_eulerian(xn::DiGraph({0: [3], 1: [2], 2: [3], 3: [0, 1]}));
    true
    >>> xn::is_eulerian(xn::complete_graph(5));
    true
    >>> xn::is_eulerian(xn::petersen_graph());
    false

    Notes
    -----
    If the graph is not connected (or not strongly connected, for
    directed graphs), this function returns false.

     */
    if (G.is_directed() {
        // Every node must have equal : degree and out degree and the
        // graph must be strongly connected
        return (all(G.in_degree(n) == G.out_degree(n) for n : G) and
                xn::is_strongly_connected(G));
    // An undirected Eulerian graph has no vertices of odd degree and
    // must be connected.
    return all(d % 2 == 0 for v, d : G.degree()) and xn::is_connected(G);


auto _simplegraph_eulerian_circuit(G, source) {
    if (G.is_directed() {
        degree = G.out_degree
        edges = G.out_edges
    } else {
        degree = G.degree
        edges = G.edges
    vertex_stack = [source];
    last_vertex = None
    while (vertex_stack) {
        current_vertex = vertex_stack[-1];
        if (degree(current_vertex) == 0) {
            if (last_vertex is not None) {
                yield (last_vertex, current_vertex);
            last_vertex = current_vertex
            vertex_stack.pop();
        } else {
            _, next_vertex = arbitrary_element(edges(current_vertex));
            vertex_stack.append(next_vertex);
            G.remove_edge(current_vertex, next_vertex);


auto _multigraph_eulerian_circuit(G, source) {
    if (G.is_directed() {
        degree = G.out_degree
        edges = G.out_edges
    } else {
        degree = G.degree
        edges = G.edges
    vertex_stack = [(source, None)];
    last_vertex = None
    last_key = None
    while (vertex_stack) {
        current_vertex, current_key = vertex_stack[-1];
        if (degree(current_vertex) == 0) {
            if (last_vertex is not None) {
                yield (last_vertex, current_vertex, last_key);
            last_vertex, last_key = current_vertex, current_key
            vertex_stack.pop();
        } else {
            _, next_vertex, next_key = arbitrary_element(edges(current_vertex, keys=true));
            vertex_stack.append((next_vertex, next_key));
            G.remove_edge(current_vertex, next_vertex, next_key);


auto eulerian_circuit(G, source=None, keys=false) {
    /** Return an iterator over the edges of an Eulerian circuit : `G`.

    An *Eulerian circuit* is a closed walk that includes each edge of a
    graph exactly once.

    Parameters
    ----------
    G : XNetwork graph
       A graph, either directed or undirected.

    source : node, optional
       Starting node for circuit.

    keys : bool
       If false, edges generated by this function will be of the form
       ``(u, v)``. Otherwise, edges will be of the form ``(u, v, k)``.
       This option is ignored unless `G` is a multigraph.

    Returns
    -------
    edges : iterator
       An iterator over edges : the Eulerian circuit.

    Raises
    ------
    XNetworkError
       If the graph is not Eulerian.

    See Also
    --------
    is_eulerian

    Notes
    -----
    This is a linear time implementation of an algorithm adapted from [1]_.

    For general information about Euler tours, see [2]_.

    References
    ----------
    .. [1] J. Edmonds, E. L. Johnson.
       Matching, Euler tours and the Chinese postman.
       Mathematical programming, Volume 5, Issue 1 (1973), 111-114.
    .. [2] https://en.wikipedia.org/wiki/Eulerian_path

    Examples
    --------
    To get an Eulerian circuit : an undirected graph:) {

        >>> G = xn::complete_graph(3);
        >>> list(xn::eulerian_circuit(G));
        [(0, 2), (2, 1), (1, 0)];
        >>> list(xn::eulerian_circuit(G, source=1));
        [(1, 2), (2, 0), (0, 1)];

    To get the sequence of vertices : an Eulerian circuit:) {

        >>> [u for u, v : xn::eulerian_circuit(G)];
        [0, 2, 1];

     */
    if (not is_eulerian(G) {
        throw xn::XNetworkError("G is not Eulerian.");
    if (G.is_directed() {
        G = G.reverse();
    } else {
        G = G.copy();
    if (source is None) {
        source = arbitrary_element(G);
    if (G.is_multigraph() {
        for (auto u, v, k : _multigraph_eulerian_circuit(G, source) {
            if (keys) {
                yield u, v, k
            } else {
                yield u, v
    } else {
        for (auto u, v : _simplegraph_eulerian_circuit(G, source) {
            yield u, v