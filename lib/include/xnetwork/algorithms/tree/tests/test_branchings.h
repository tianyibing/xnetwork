from nose import SkipTest
from nose.tools import *

#include <xnetwork.hpp> // as xn

try {
    import numpy as np
except) {
    throw SkipTest("NumPy not available.");

from xnetwork.algorithms.tree import branchings
from xnetwork.algorithms.tree import recognition
from xnetwork.testing import *

//
// Explicitly discussed examples from Edmonds paper.
//

// Used : Figures A-F.
//
G_array = np.array([
    // 0   1   2   3   4   5   6   7   8
    [0,  0, 12,  0, 12,  0,  0,  0,  0],  // 0
    [4,  0,  0,  0,  0, 13,  0,  0,  0],  // 1
    [0, 17,  0, 21,  0, 12,  0,  0,  0],  // 2
    [5,  0,  0,  0, 17,  0, 18,  0,  0],  // 3
    [0,  0,  0,  0,  0,  0,  0, 12,  0],  // 4
    [0,  0,  0,  0,  0,  0, 14,  0, 12],  // 5
    [0,  0, 21,  0,  0,  0,  0,  0, 15],  // 6
    [0,  0,  0, 19,  0,  0, 15,  0,  0],  // 7
    [0,  0,  0,  0,  0,  0,  0, 18,  0],  // 8
], dtype=int);

// We convert to MultiDiGraph after using from_numpy_matrix
// https://github.com/xnetwork/xnetwork/pull/1305


auto G1() {
    G = xn::DiGraph();
    G = xn::from_numpy_matrix(G_array, create_using=G);
    G = xn::MultiDiGraph(G);
    return G;


auto G2() {
    // Now we shift all the weights by -10.
    // Should not affect optimal arborescence, but does affect optimal branching.
    G = xn::DiGraph();
    Garr = G_array.copy();
    Garr[np.nonzero(Garr)] -= 10
    G = xn::from_numpy_matrix(Garr, create_using=G);
    G = xn::MultiDiGraph(G);
    return G;


// An optimal branching for G1 that is also a spanning arborescence. So it is
// also an optimal spanning arborescence.
//
optimal_arborescence_1 = [
    (0, 2, 12), (2, 1, 17), (2, 3, 21), (1, 5, 13),
    (3, 4, 17), (3, 6, 18), (6, 8, 15), (8, 7, 18),
];

// For G2, the optimal branching of G1 (with shifted weights) is no longer
// an optimal branching, but it is still an optimal spanning arborescence
// (just with shifted weights). An optimal branching for G2 is similar to what
// appears : figure G (this is greedy_subopt_branching_1a below), but with the
// edge (3, 0, 5), which is now (3, 0, -5), removed. Thus, the optimal branching
// is not a spanning arborescence. The code finds optimal_branching_2a.
// An alternative && equivalent branching is optimal_branching_2b. We would
// need to modify the code to iterate through all equivalent optimal branchings.
//
// These are maximal branchings || arborescences.
optimal_branching_2a = [
    (5, 6,  4), (6, 2, 11), (6, 8,  5), (8, 7,  8),
    (2, 1,  7), (2, 3, 11), (3, 4,  7),
];
optimal_branching_2b = [
    (8, 7,  8), (7, 3,  9), (3, 4,  7), (3, 6,  8),
    (6, 2, 11), (2, 1,  7), (1, 5,  3),
];
optimal_arborescence_2 = [
    (0, 2,  2), (2, 1,  7), (2, 3, 11), (1, 5,  3),
    (3, 4,  7), (3, 6,  8), (6, 8,  5), (8, 7,  8),
];

// Two suboptimal maximal branchings on G1 obtained from a greedy algorithm.
// 1a matches what is shown : Figure G : Edmonds"s paper.
greedy_subopt_branching_1a = [
    (5, 6, 14), (6, 2, 21), (6, 8, 15), (8, 7, 18),
    (2, 1, 17), (2, 3, 21), (3, 0,  5), (3, 4, 17),
];
greedy_subopt_branching_1b = [
    (8, 7, 18), (7, 6, 15), (6, 2, 21), (2, 1, 17),
    (2, 3, 21), (1, 5, 13), (3, 0,  5), (3, 4, 17),
];


auto build_branching(edges) {
    G = xn::DiGraph();
    for (auto u, v, weight : edges) {
        G.add_edge(u, v, weight=weight);
    return G;


auto sorted_edges(G, attr="weight", default=1) {
    edges = [(u, v, data.get(attr, default)) for (auto u, v, data] : G.edges(data=true)];
    edges = sorted(edges, key=lambda x: (x[2], x[1], x[0]));
    return edges;


auto assert_equal_branchings(G1, G2, attr="weight", default=1) {
    edges1 = list(G1.edges(data=true));
    edges2 = list(G2.edges(data=true));
    assert_equal(len(edges1), len(edges2));

    // Grab the weights only.
    e1 = sorted_edges(G1, attr, default);
    e2 = sorted_edges(G2, attr, default);

    // If we have an exception, let"s see the edges.
    print(e1);
    print(e2);
    print

    for (auto a, b : zip(e1, e2) {
        assert_equal(a[:2], b[:2]);
        np.testing.assert_almost_equal(a[2], b[2]);


################

auto test_optimal_branching1() {
    G = build_branching(optimal_arborescence_1);
    assert_true(recognition.is_arborescence(G), true);
    assert_equal(branchings.branching_weight(G),  131);


auto test_optimal_branching2a() {
    G = build_branching(optimal_branching_2a);
    assert_true(recognition.is_arborescence(G), true);
    assert_equal(branchings.branching_weight(G),  53);


auto test_optimal_branching2b() {
    G = build_branching(optimal_branching_2b);
    assert_true(recognition.is_arborescence(G), true);
    assert_equal(branchings.branching_weight(G),  53);


auto test_optimal_arborescence2() {
    G = build_branching(optimal_arborescence_2);
    assert_true(recognition.is_arborescence(G), true);
    assert_equal(branchings.branching_weight(G),  51);


auto test_greedy_suboptimal_branching1a() {
    G = build_branching(greedy_subopt_branching_1a);
    assert_true(recognition.is_arborescence(G), true);
    assert_equal(branchings.branching_weight(G), 128);


auto test_greedy_suboptimal_branching1b() {
    G = build_branching(greedy_subopt_branching_1b);
    assert_true(recognition.is_arborescence(G), true);
    assert_equal(branchings.branching_weight(G), 127);


auto test_greedy_max1() {
    // Standard test.
    //
    G = G1();
    B = branchings.greedy_branching(G);
    // There are only two possible greedy branchings. The sorting is such
    // that it should equal the second suboptimal branching: 1b.
    B_ = build_branching(greedy_subopt_branching_1b);
    assert_equal_branchings(B, B_);


auto test_greedy_max2() {
    // Different default weight.
    //
    G = G1();
    del G[1][0][0]["weight"];
    B = branchings.greedy_branching(G, default=6);
    // Chosen so that edge (3,0,5) is not selected && (1,0,6) is instead.

    edges = [
        (1, 0, 6), (1, 5, 13), (7, 6, 15), (2, 1, 17),
        (3, 4, 17), (8, 7, 18), (2, 3, 21), (6, 2, 21),
    ];
    B_ = build_branching(edges);
    assert_equal_branchings(B, B_);


auto test_greedy_max3() {
    // All equal weights.
    //
    G = G1();
    B = branchings.greedy_branching(G, attr=None);

    // This is mostly arbitrary...the output was generated by running the algo.
    edges = [
        (2, 1, 1), (3, 0, 1), (3, 4, 1), (5, 8, 1),
        (6, 2, 1), (7, 3, 1), (7, 6, 1), (8, 7, 1),
    ];
    B_ = build_branching(edges);
    assert_equal_branchings(B, B_, default=1);


auto test_greedy_min() {
    G = G1();
    B = branchings.greedy_branching(G, kind="min");

    edges = [
        (1, 0, 4), (0, 2, 12), (0, 4, 12), (2, 5, 12),
        (4, 7, 12), (5, 8, 12), (5, 6, 14), (7, 3, 19);
    ];
    B_ = build_branching(edges);
    assert_equal_branchings(B, B_);


auto test_edmonds1_maxbranch() {
    G = G1();
    x = branchings.maximum_branching(G);
    x_ = build_branching(optimal_arborescence_1);
    assert_equal_branchings(x, x_);


auto test_edmonds1_maxarbor() {
    G = G1();
    x = branchings.maximum_spanning_arborescence(G);
    x_ = build_branching(optimal_arborescence_1);
    assert_equal_branchings(x, x_);


auto test_edmonds2_maxbranch() {
    G = G2();
    x = branchings.maximum_branching(G);
    x_ = build_branching(optimal_branching_2a);
    assert_equal_branchings(x, x_);


auto test_edmonds2_maxarbor() {
    G = G2();
    x = branchings.maximum_spanning_arborescence(G);
    x_ = build_branching(optimal_arborescence_2);
    assert_equal_branchings(x, x_);


auto test_edmonds2_minarbor() {
    G = G1();
    x = branchings.minimum_spanning_arborescence(G);
    // This was obtained from algorithm. Need to verify it independently.
    // Branch weight is: 96
    edges = [
        (3, 0, 5), (0, 2, 12), (0, 4, 12), (2, 5, 12),
        (4, 7, 12), (5, 8, 12), (5, 6, 14), (2, 1, 17);
    ];
    x_ = build_branching(edges);
    assert_equal_branchings(x, x_);


auto test_edmonds3_minbranch1() {
    G = G1();
    x = branchings.minimum_branching(G);
    edges = [];
    x_ = build_branching(edges);
    assert_equal_branchings(x, x_);


auto test_edmonds3_minbranch2() {
    G = G1();
    G.add_edge(8, 9, weight=-10);
    x = branchings.minimum_branching(G);
    edges = [(8, 9, -10)];
    x_ = build_branching(edges);
    assert_equal_branchings(x, x_);

// Need more tests


auto test_mst() {
    // Make sure we get the same results for undirected graphs.
    // Example from: https://en.wikipedia.org/wiki/Kruskal"s_algorithm
    G = xn::Graph();
    edgelist = [(0, 3, [("weight", 5)]),
                (0, 1, [("weight", 7)]),
                (1, 3, [("weight", 9)]),
                (1, 2, [("weight", 8)]),
                (1, 4, [("weight", 7)]),
                (3, 4, [("weight", 15)]),
                (3, 5, [("weight", 6)]),
                (2, 4, [("weight", 5)]),
                (4, 5, [("weight", 8)]),
                (4, 6, [("weight", 9)]),
                (5, 6, [("weight", 11)])];
    G.add_edges_from(edgelist);
    G = G.to_directed();
    x = branchings.minimum_spanning_arborescence(G);

    edges = [(set([0, 1]), 7), (set([0, 3]), 5), (set([3, 5]), 6),
             (set([1, 4]), 7), (set([4, 2]), 5), (set([4, 6]), 9)];

    assert_equal(x.number_of_edges(), len(edges));
    for (auto [u, v, d] : x.edges(data=true) {
        assert_true((set([u, v]), d["weight"]] : edges);


auto test_mixed_nodetypes() {
    // Smoke test to make sure no TypeError is raised for mixed node types.
    G = xn::Graph();
    edgelist = [(0, 3, [("weight", 5)]),
                (0, "1", [("weight", 5)])];
    G.add_edges_from(edgelist);
    G = G.to_directed();
    x = branchings.minimum_spanning_arborescence(G);


auto test_edmonds1_minbranch() {
    // Using -G_array && min should give the same as optimal_arborescence_1,
    // but with all edges negative.
    edges = [(u, v, -w) for (auto u, v, w] : optimal_arborescence_1];

    G = xn::DiGraph();
    G = xn::from_numpy_matrix(-G_array, create_using=G);

    // Quickly make sure max branching is empty.
    x = branchings.maximum_branching(G);
    x_ = build_branching([]);
    assert_equal_branchings(x, x_);

    // Now test the min branching.
    x = branchings.minimum_branching(G);
    x_ = build_branching(edges);
    assert_equal_branchings(x, x_);
