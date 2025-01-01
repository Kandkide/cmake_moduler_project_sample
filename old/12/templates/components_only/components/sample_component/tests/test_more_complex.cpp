// sample_component_test.cpp
#include "sample_component.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include <sstream>

// `sample_component()`の標準出力をキャプチャするために使うクラス
class RedirectCout {
public:
    RedirectCout() {
        old_buf = std::cout.rdbuf();  // 以前のバッファを保存
        std::cout.rdbuf(ss.rdbuf());  // 新しいバッファを設定
    }

    ~RedirectCout() {
        std::cout.rdbuf(old_buf);  // 標準のバッファに戻す
    }

    std::string getOutput() {
        return ss.str();
    }

private:
    std::stringstream ss;
    std::streambuf* old_buf;
};

// `sample_component()`が正しく出力するかをテストする
TEST(SampleComponentTest, OutputTest) {
    RedirectCout redirect;  // 出力をリダイレクト

    sample_component();  // テスト対象の関数を呼び出す

    // 出力を検証
    std::string expected_output = "This is sample_component() from sample_component.hpp\n";
    EXPECT_EQ(redirect.getOutput(), expected_output);
}

// メイン関数 (Google Testのランナー)
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
