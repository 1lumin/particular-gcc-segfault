module;

#include <memory>

import filler1;
import filler2;

import testmodp;
import testmod1;

export module test_impl;

export namespace test_impl {
    void test_init(){
        new testmodp<int,float>();
    }
};