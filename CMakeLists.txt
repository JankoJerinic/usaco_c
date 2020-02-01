cmake_minimum_required(VERSION 3.7)
project(usaco)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        ariprog/ariprog.c
        barn1/barn1.c
        beads/beads.c
        beads/beads2.c
        combo/combo.c
        crypt1/crypt1.c
        dualpal/dualpal.c
        friday/friday.c
        gift1/gift1.c
        milk/milk.c
        milk2/milk2.c
        milk2/milk_bit.c
        milk3/milk3.c
        namenum/namenum.c
        palsquare/palsquare.c
        ride/ride.c
        ride/ride.cpp
        ride/ride_iterative.cpp
        ride/ride_iterative_fn.cpp
        ride/ride_iterators_fn.cpp
        ride/ride_recursive_fn.cpp
        skidesign/skidesign.c
        transform/transform.c
        wormhole/wormhole.c
        wormhole/wormhole.dbg.c
        main.c
        main.cpp
        test.cpp
        test_2darr_ptrs.c
        usaco)

add_executable(usaco ${SOURCE_FILES})