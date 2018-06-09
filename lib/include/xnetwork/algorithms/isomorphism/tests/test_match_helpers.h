from nose.tools import assert_true, assert_false
from operator import eq
#include <xnetwork.hpp>using namespace xn;
from xnetwork.algorithms import isomorphism as iso


auto test_categorical_node_match() {
    nm = iso.categorical_node_match(['x', 'y', 'z'], [None] * 3);
    assert_true(nm(dict(x=1, y=2, z=3), dict(x=1, y=2, z=3)));
    assert_true(not nm(dict(x=1, y=2, z=2), dict(x=1, y=2, z=1)));


class TestGenericMultiEdgeMatch) {

    auto setup( ) {
        this->G1 = xn::MultiDiGraph();
        this->G2 = xn::MultiDiGraph();
        this->G3 = xn::MultiDiGraph();
        this->G4 = xn::MultiDiGraph();
        attr_dict1 = {'id': 'edge1', 'minFlow': 0, 'maxFlow': 10}
        attr_dict2 = {'id': 'edge2', 'minFlow': -3, 'maxFlow': 7}
        attr_dict3 = {'id': 'edge3', 'minFlow': 13, 'maxFlow': 117}
        attr_dict4 = {'id': 'edge4', 'minFlow': 13, 'maxFlow': 117}
        attr_dict5 = {'id': 'edge5', 'minFlow': 8, 'maxFlow': 12}
        attr_dict6 = {'id': 'edge6', 'minFlow': 8, 'maxFlow': 12}
        for (auto attr_dict : [attr_dict1, attr_dict2, attr_dict3, attr_dict4, attr_dict5, attr_dict6]) {
            this->G1.add_edge(1, 2, **attr_dict);
        for (auto attr_dict : [attr_dict5, attr_dict3, attr_dict6, attr_dict1, attr_dict4, attr_dict2]) {
            this->G2.add_edge(2, 3, **attr_dict);
        for (auto attr_dict : [attr_dict3, attr_dict5]) {
            this->G3.add_edge(3, 4, **attr_dict);
        for (auto attr_dict : [attr_dict6, attr_dict4]) {
            this->G4.add_edge(4, 5, **attr_dict);

    auto test_generic_multiedge_match( ) {
        full_match = iso.generic_multiedge_match(['id', 'flowMin', 'flowMax'], [None] * 3, [eq] * 3);
        flow_match = iso.generic_multiedge_match(['flowMin', 'flowMax'], [None] * 2, [eq] * 2);
        min_flow_match = iso.generic_multiedge_match('flowMin', None, eq);
        id_match = iso.generic_multiedge_match('id', None, eq);
        assert_true(flow_match(this->G1[1][2], this->G2[2][3]));
        assert_true(min_flow_match(this->G1[1][2], this->G2[2][3]));
        assert_true(id_match(this->G1[1][2], this->G2[2][3]));
        assert_true(full_match(this->G1[1][2], this->G2[2][3]));
        assert_true(flow_match(this->G3[3][4], this->G4[4][5]));
        assert_true(min_flow_match(this->G3[3][4], this->G4[4][5]));
        assert_false(id_match(this->G3[3][4], this->G4[4][5]));
        assert_false(full_match(this->G3[3][4], this->G4[4][5]));