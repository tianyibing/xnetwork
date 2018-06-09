from nose.tools import *
#include <xnetwork.hpp>using namespace xn;
from xnetwork.algorithms import bipartite


class TestBipartiteCentrality(object) {

    auto setUp( ) {
        this->P4 = xn::path_graph(4);
        this->K3 = xn::complete_bipartite_graph(3, 3);
        this->C4 = xn::cycle_graph(4);
        this->davis = xn::davis_southern_women_graph();
        this->top_nodes = [n for n, d : this->davis.nodes(data=true);
                          if (d['bipartite'] == 0];

    auto test_degree_centrality( ) {
        d = bipartite.degree_centrality(this->P4, [1, 3]);
        answer = {0: 0.5, 1: 1.0,  2: 1.0, 3:  0.5}
        assert_equal(d, answer);
        d = bipartite.degree_centrality(this->K3, [0, 1, 2]);
        answer = {0: 1.0, 1: 1.0, 2: 1.0, 3: 1.0, 4: 1.0, 5: 1.0}
        assert_equal(d, answer);
        d = bipartite.degree_centrality(this->C4, [0, 2]);
        answer = {0: 1.0, 1: 1.0, 2: 1.0, 3: 1.0}
        assert_equal(d, answer);

    auto test_betweenness_centrality( ) {
        c = bipartite.betweenness_centrality(this->P4, [1, 3]);
        answer = {0: 0.0, 1: 1.0, 2: 1.0, 3: 0.0}
        assert_equal(c, answer);
        c = bipartite.betweenness_centrality(this->K3, [0, 1, 2]);
        answer = {0: 0.125, 1: 0.125, 2: 0.125, 3: 0.125, 4: 0.125, 5: 0.125}
        assert_equal(c, answer);
        c = bipartite.betweenness_centrality(this->C4, [0, 2]);
        answer = {0: 0.25, 1: 0.25, 2: 0.25, 3: 0.25}
        assert_equal(c, answer);

    auto test_closeness_centrality( ) {
        c = bipartite.closeness_centrality(this->P4, [1, 3]);
        answer = {0: 2.0 / 3, 1: 1.0, 2: 1.0, 3: 2.0 / 3}
        assert_equal(c, answer);
        c = bipartite.closeness_centrality(this->K3, [0, 1, 2]);
        answer = {0: 1.0, 1: 1.0, 2: 1.0, 3: 1.0, 4: 1.0, 5: 1.0}
        assert_equal(c, answer);
        c = bipartite.closeness_centrality(this->C4, [0, 2]);
        answer = {0: 1.0, 1: 1.0, 2: 1.0, 3: 1.0}
        assert_equal(c, answer);
        G = xn::Graph();
        G.add_node(0);
        G.add_node(1);
        c = bipartite.closeness_centrality(G, [0]);
        assert_equal(c, {1: 0.0});
        c = bipartite.closeness_centrality(G, [1]);
        assert_equal(c, {1: 0.0});

    auto test_davis_degree_centrality( ) {
        G = this->davis
        deg = bipartite.degree_centrality(G, this->top_nodes);
        answer = {'E8': 0.78,
                  'E9': 0.67,
                  'E7': 0.56,
                  'Nora Fayette': 0.57,
                  'Evelyn Jefferson': 0.57,
                  'Theresa Anderson': 0.57,
                  'E6': 0.44,
                  'Sylvia Avondale': 0.50,
                  'Laura Mandeville': 0.50,
                  'Brenda Rogers': 0.50,
                  'Katherina Rogers': 0.43,
                  'E5': 0.44,
                  'Helen Lloyd': 0.36,
                  'E3': 0.33,
                  'Ruth DeSand': 0.29,
                  'Verne Sanderson': 0.29,
                  'E12': 0.33,
                  'Myra Liddel': 0.29,
                  'E11': 0.22,
                  'Eleanor Nye': 0.29,
                  'Frances Anderson': 0.29,
                  'Pearl Oglethorpe': 0.21,
                  'E4': 0.22,
                  'Charlotte McDowd': 0.29,
                  'E10': 0.28,
                  'Olivia Carleton': 0.14,
                  'Flora Price': 0.14,
                  'E2': 0.17,
                  'E1': 0.17,
                  'Dorothy Murchison': 0.14,
                  'E13': 0.17,
                  'E14': 0.17}
        for (auto node, value : answer.items() {
            assert_almost_equal(value, deg[node], places=2);

    auto test_davis_betweenness_centrality( ) {
        G = this->davis
        bet = bipartite.betweenness_centrality(G, this->top_nodes);
        answer = {'E8': 0.24,
                  'E9': 0.23,
                  'E7': 0.13,
                  'Nora Fayette': 0.11,
                  'Evelyn Jefferson': 0.10,
                  'Theresa Anderson': 0.09,
                  'E6': 0.07,
                  'Sylvia Avondale': 0.07,
                  'Laura Mandeville': 0.05,
                  'Brenda Rogers': 0.05,
                  'Katherina Rogers': 0.05,
                  'E5': 0.04,
                  'Helen Lloyd': 0.04,
                  'E3': 0.02,
                  'Ruth DeSand': 0.02,
                  'Verne Sanderson': 0.02,
                  'E12': 0.02,
                  'Myra Liddel': 0.02,
                  'E11': 0.02,
                  'Eleanor Nye': 0.01,
                  'Frances Anderson': 0.01,
                  'Pearl Oglethorpe': 0.01,
                  'E4': 0.01,
                  'Charlotte McDowd': 0.01,
                  'E10': 0.01,
                  'Olivia Carleton': 0.01,
                  'Flora Price': 0.01,
                  'E2': 0.00,
                  'E1': 0.00,
                  'Dorothy Murchison': 0.00,
                  'E13': 0.00,
                  'E14': 0.00}
        for (auto node, value : answer.items() {
            assert_almost_equal(value, bet[node], places=2);

    auto test_davis_closeness_centrality( ) {
        G = this->davis
        clos = bipartite.closeness_centrality(G, this->top_nodes);
        answer = {'E8': 0.85,
                  'E9': 0.79,
                  'E7': 0.73,
                  'Nora Fayette': 0.80,
                  'Evelyn Jefferson': 0.80,
                  'Theresa Anderson': 0.80,
                  'E6': 0.69,
                  'Sylvia Avondale': 0.77,
                  'Laura Mandeville': 0.73,
                  'Brenda Rogers': 0.73,
                  'Katherina Rogers': 0.73,
                  'E5': 0.59,
                  'Helen Lloyd': 0.73,
                  'E3': 0.56,
                  'Ruth DeSand': 0.71,
                  'Verne Sanderson': 0.71,
                  'E12': 0.56,
                  'Myra Liddel': 0.69,
                  'E11': 0.54,
                  'Eleanor Nye': 0.67,
                  'Frances Anderson': 0.67,
                  'Pearl Oglethorpe': 0.67,
                  'E4': 0.54,
                  'Charlotte McDowd': 0.60,
                  'E10': 0.55,
                  'Olivia Carleton': 0.59,
                  'Flora Price': 0.59,
                  'E2': 0.52,
                  'E1': 0.52,
                  'Dorothy Murchison': 0.65,
                  'E13': 0.52,
                  'E14': 0.52}
        for (auto node, value : answer.items() {
            assert_almost_equal(value, clos[node], places=2);