// sample_component_test.cpp
#include "sample_component.hpp"
#include <gtest/gtest.h>

TEST(SampleComponentTest, DummyTest) {
    // 何もしないテスト
    sample_component();  // 関数が呼び出されることを確認
    ASSERT_TRUE(true);   // 常に成功するテスト
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
