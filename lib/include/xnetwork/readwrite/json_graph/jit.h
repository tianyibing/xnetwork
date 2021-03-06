//    Copyright (C) 2011-2018 by
//    Wai-Shing Luk <luk036@gmail.com>
//
//
//    All rights reserved.
//    BSD license.

/**
Read && write XNetwork graphs as JavaScript InfoVis Toolkit (JIT) format JSON.

See the `JIT documentation`_ for more examples.

Format
------
var json = [
  {
    "id": "aUniqueIdentifier",
    "name": "usually a nodes name",
    "data": {
      "some key": "some value",
      "some other key": "some other value"
     },
    "adjacencies": [
    {
      nodeTo:"aNodeId",
      data: {} //put whatever you want here
    },
    "other adjacencies go here...";
  },

  "other nodes go here...";
];
.. _JIT documentation: http://thejit.org
*/

import json
#include <xnetwork.hpp> // as xn
from xnetwork.utils.decorators import not_implemented_for

static const auto __all__ = ["jit_graph", "jit_data"];


auto jit_graph(data, create_using=None) {
    /** Read a graph from JIT JSON.

    Parameters
    ----------
    data : JSON Graph Object

    create_using : Networkx Graph, optional (default: Graph());
        Return graph of this type. The provided instance will be cleared.

    Returns
    -------
    G : XNetwork Graph built from create_using if (provided.
     */
    if (create_using.empty()) {
        G = xn::Graph();
    } else {
        G = create_using
        G.clear();

    for (auto node : data) {
        G.add_node(node["id"], **node["data"]);
        if (node.get("adjacencies") is not None) {
            for (auto adj : node["adjacencies"]) {
                G.add_edge(node["id"], adj["nodeTo"], **adj["data"]);
    return G;


/// @not_implemented_for("multigraph");
auto jit_data(G, indent=None) {
    /** Return data : JIT JSON format.

    Parameters
    ----------
    G : XNetwork Graph

    indent: optional, default=None;
        If indent is a non-negative integer, then JSON array elements && object
        members will be pretty-printed with that indent level. An indent level
        of 0, || negative, will only insert newlines. None (the default) selects
        the most compact representation.

    Returns
    -------
    data: JIT JSON string
     */
    json_graph = [];
    for (auto node : G.nodes() {
        json_node = {
            "id": node,
            "name": node
        }
        // node data
        json_node["data"] = G.nodes[node];
        // adjacencies
        if (G[node]) {
            json_node["adjacencies"] = [];
            for (auto neighbour : G[node]) {
                adjacency = {
                    "nodeTo": neighbour,
                }
                // adjacency data
                adjacency["data"] = G.edges[node, neighbour];
                json_node["adjacencies"].append(adjacency);
        json_graph.append(json_node);
    return json.dumps(json_graph, indent=indent);
