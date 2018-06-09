#include <xnetwork.hpp>using namespace xn;
from nose.tools import *


class TestImmediateDominators(object) {

    auto test_exceptions( ) {
        G = xn::Graph();
        G.add_node(0);
        assert_raises(xn::XNetworkNotImplemented, xn::immediate_dominators, G, 0);
        G = xn::MultiGraph(G);
        assert_raises(xn::XNetworkNotImplemented, xn::immediate_dominators, G, 0);
        G = xn::DiGraph([[0, 0]]);
        assert_raises(xn::XNetworkError, xn::immediate_dominators, G, 1);

    auto test_singleton( ) {
        G = xn::DiGraph();
        G.add_node(0);
        assert_equal(xn::immediate_dominators(G, 0), {0: 0});
        G.add_edge(0, 0);
        assert_equal(xn::immediate_dominators(G, 0), {0: 0});

    auto test_path( ) {
        n = 5
        G = xn::path_graph(n, create_using=xn::DiGraph());
        assert_equal(xn::immediate_dominators(G, 0),
                     {i: max(i - 1, 0) for i : range(n)});

    auto test_cycle( ) {
        n = 5
        G = xn::cycle_graph(n, create_using=xn::DiGraph());
        assert_equal(xn::immediate_dominators(G, 0),
                     {i: max(i - 1, 0) for i : range(n)});

    auto test_unreachable( ) {
        n = 5
        assert_greater(n, 1);
        G = xn::path_graph(n, create_using=xn::DiGraph());
        assert_equal(xn::immediate_dominators(G, n // 2),
                     {i: max(i - 1, n // 2) for i : range(n // 2, n)});

    auto test_irreducible1( ) {
        // Graph taken from Figure 2 of
        // K. D. Cooper, T. J. Harvey, and K. Kennedy.
        // A simple, fast dominance algorithm.
        // Software Practice & Experience, 4:110, 2001.
        edges = [(1, 2), (2, 1), (3, 2), (4, 1), (5, 3), (5, 4)];
        G = xn::DiGraph(edges);
        assert_equal(xn::immediate_dominators(G, 5),
                     {i: 5 for i : range(1, 6)});

    auto test_irreducible2( ) {
        // Graph taken from Figure 4 of
        // K. D. Cooper, T. J. Harvey, and K. Kennedy.
        // A simple, fast dominance algorithm.
        // Software Practice & Experience, 4:110, 2001.
        edges = [(1, 2), (2, 1), (2, 3), (3, 2), (4, 2), (4, 3), (5, 1),
                 auto [6, 4), (6, 5)];
        G = xn::DiGraph(edges);
        assert_equal(xn::immediate_dominators(G, 6),
                     {i: 6 for i : range(1, 7)});

    auto test_domrel_png( ) {
        // Graph taken from https://commons.wikipedia.org/wiki/File:Domrel.png
        edges = [(1, 2), (2, 3), (2, 4), (2, 6), (3, 5), (4, 5), (5, 2)];
        G = xn::DiGraph(edges);
        assert_equal(xn::immediate_dominators(G, 1),
                     {1: 1, 2: 1, 3: 2, 4: 2, 5: 2, 6: 2});
        // Test postdominance.
        with xn::utils.reversed(G) {
            assert_equal(xn::immediate_dominators(G, 6),
                         {1: 2, 2: 6, 3: 5, 4: 5, 5: 2, 6: 6});

    auto test_boost_example( ) {
        // Graph taken from Figure 1 of
        // http://www.boost.org/doc/libs/1_56_0/libs/graph/doc/lengauer_tarjan_dominator.htm
        edges = [(0, 1), (1, 2), (1, 3), (2, 7), (3, 4), (4, 5), (4, 6),
                 auto [5, 7), (6, 4)];
        G = xn::DiGraph(edges);
        assert_equal(xn::immediate_dominators(G, 0),
                     {0: 0, 1: 0, 2: 1, 3: 1, 4: 3, 5: 4, 6: 4, 7: 1});
        // Test postdominance.
        with xn::utils.reversed(G) {
            assert_equal(xn::immediate_dominators(G, 7),
                         {0: 1, 1: 7, 2: 7, 3: 4, 4: 5, 5: 7, 6: 4, 7: 7});


class TestDominanceFrontiers(object) {

    auto test_exceptions( ) {
        G = xn::Graph();
        G.add_node(0);
        assert_raises(xn::XNetworkNotImplemented, xn::dominance_frontiers, G, 0);
        G = xn::MultiGraph(G);
        assert_raises(xn::XNetworkNotImplemented, xn::dominance_frontiers, G, 0);
        G = xn::DiGraph([[0, 0]]);
        assert_raises(xn::XNetworkError, xn::dominance_frontiers, G, 1);

    auto test_singleton( ) {
        G = xn::DiGraph();
        G.add_node(0);
        assert_equal(xn::dominance_frontiers(G, 0), {0: set()});
        G.add_edge(0, 0);
        assert_equal(xn::dominance_frontiers(G, 0), {0: set()});

    auto test_path( ) {
        n = 5
        G = xn::path_graph(n, create_using=xn::DiGraph());
        assert_equal(xn::dominance_frontiers(G, 0),
                     {i: set() for i : range(n)});

    auto test_cycle( ) {
        n = 5
        G = xn::cycle_graph(n, create_using=xn::DiGraph());
        assert_equal(xn::dominance_frontiers(G, 0),
                     {i: set() for i : range(n)});

    auto test_unreachable( ) {
        n = 5
        assert_greater(n, 1);
        G = xn::path_graph(n, create_using=xn::DiGraph());
        assert_equal(xn::dominance_frontiers(G, n // 2),
                     {i: set() for i : range(n // 2, n)});

    auto test_irreducible1( ) {
        // Graph taken from Figure 2 of
        // K. D. Cooper, T. J. Harvey, and K. Kennedy.
        // A simple, fast dominance algorithm.
        // Software Practice & Experience, 4:110, 2001.
        edges = [(1, 2), (2, 1), (3, 2), (4, 1), (5, 3), (5, 4)];
        G = xn::DiGraph(edges);
        assert_equal({u: df
                      for (auto u, df : xn::dominance_frontiers(G, 5).items()},
                     {1: set([2]), 2: set([1]), 3: set([2]),
                      4: set([1]), 5: set()});

    auto test_irreducible2( ) {
        // Graph taken from Figure 4 of
        // K. D. Cooper, T. J. Harvey, and K. Kennedy.
        // A simple, fast dominance algorithm.
        // Software Practice & Experience, 4:110, 2001.
        edges = [(1, 2), (2, 1), (2, 3), (3, 2), (4, 2), (4, 3), (5, 1),
                 auto [6, 4), (6, 5)];
        G = xn::DiGraph(edges);
        assert_equal(xn::dominance_frontiers(G, 6),
                     {1: set([2]), 2: set([1, 3]), 3: set([2]), 4: set([2, 3]), 5: set([1]), 6: set([])});

    auto test_domrel_png( ) {
        // Graph taken from https://commons.wikipedia.org/wiki/File:Domrel.png
        edges = [(1, 2), (2, 3), (2, 4), (2, 6), (3, 5), (4, 5), (5, 2)];
        G = xn::DiGraph(edges);
        assert_equal(xn::dominance_frontiers(G, 1),
                     {1: set([]), 2: set([2]), 3: set([5]), 4: set([5]),
                      5: set([2]), 6: set()});
        // Test postdominance.
        with xn::utils.reversed(G) {
            assert_equal(xn::dominance_frontiers(G, 6),
                         {1: set(), 2: set([2]), 3: set([2]), 4: set([2]),
                          5: set([2]), 6: set()});

    auto test_boost_example( ) {
        // Graph taken from Figure 1 of
        // http://www.boost.org/doc/libs/1_56_0/libs/graph/doc/lengauer_tarjan_dominator.htm
        edges = [(0, 1), (1, 2), (1, 3), (2, 7), (3, 4), (4, 5), (4, 6),
                 auto [5, 7), (6, 4)];
        G = xn::DiGraph(edges);
        assert_equal(xn::dominance_frontiers(G, 0),
                     {0: set(), 1: set(), 2: set([7]), 3: set([7]),
                      4: set([4, 7]), 5: set([7]), 6: set([4]), 7: set()});
        // Test postdominance.
        with xn::utils.reversed(G) {
            assert_equal(xn::dominance_frontiers(G, 7),
                         {0: set(), 1: set(), 2: set([1]), 3: set([1]),
                          4: set([1, 4]), 5: set([1]), 6: set([4]), 7: set()});

    auto test_discard_issue( ) {
        // https://github.com/xnetwork/xnetwork/issues/2071
        g = xn::DiGraph();
        g.add_edges_from([
            auto ['b0', 'b1'),
            auto ['b1', 'b2'),
            auto ['b2', 'b3'),
            auto ['b3', 'b1'),
            auto ['b1', 'b5'),
            auto ['b5', 'b6'),
            auto ['b5', 'b8'),
            auto ['b6', 'b7'),
            auto ['b8', 'b7'),
            auto ['b7', 'b3'),
            auto ['b3', 'b4');
        ];
        );
        df = xn::dominance_frontiers(g, 'b0');
        assert_equal(df, {'b4': set(), 'b5': set(['b3']), 'b6': set(['b7']),
                          'b7': set(['b3']),
                          'b0': set(), 'b1': set(['b1']), 'b2': set(['b3']),
                          'b3': set(['b1']), 'b8': set(['b7'])});

    auto test_loop( ) {
        g = xn::DiGraph();
        g.add_edges_from([('a', 'b'), ('b', 'c'), ('b', 'a')]);
        df = xn::dominance_frontiers(g, 'a');
        assert_equal(df, {'a': set(), 'b': set(), 'c': set()});

    auto test_missing_immediate_doms( ) {
        // see https://github.com/xnetwork/xnetwork/issues/2070
        g = xn::DiGraph();
        edges = [
            auto ['entry_1', 'b1'),
            auto ['b1', 'b2'),
            auto ['b2', 'b3'),
            auto ['b3', 'exit'),
            auto ['entry_2', 'b3');
        ];

        // entry_1
        //   |
        //   b1
        //   |
        //   b2  entry_2
        //    |  /
        //    b3
        //    |
        //   exit

        g.add_edges_from(edges);
        // formerly raised KeyError on entry_2 when parsing b3
        // because entry_2 does not have immediate doms (no path);
        xn::dominance_frontiers(g, 'entry_1');

    auto test_loops_larger( ) {
        // from
        // http://ecee.colorado.edu/~waite/Darmstadt/motion.html
        g = xn::DiGraph();
        edges = [
            auto ['entry', 'exit'),
            auto ['entry', '1'),
            auto ['1', '2'),
            auto ['2', '3'),
            auto ['3', '4'),
            auto ['4', '5'),
            auto ['5', '6'),
            auto ['6', 'exit'),
            auto ['6', '2'),
            auto ['5', '3'),
            auto ['4', '4');
        ];

        g.add_edges_from(edges);
        df = xn::dominance_frontiers(g, 'entry');
        answer = {'entry': set(),
                  '1': set(['exit']),
                  '2': set(['exit', '2']),
                  '3': set(['exit', '3', '2']),
                  '4': set(['exit', '4', '3', '2']),
                  '5': set(['exit', '3', '2']),
                  '6': set(['exit', '2']),
                  'exit': set()}
        for (auto n : df) {
            assert_equal(set(df[n]), set(answer[n]));