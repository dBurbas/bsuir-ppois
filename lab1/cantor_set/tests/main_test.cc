//
//  main.cc
//  set_tests
//
//  Created by Dmitry Burbas on 19/10/2025.
//

#include <gtest/gtest.h>
#include <iostream>

int main(int argc, char * argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
