#include <gtest/gtest.h>
#include "Ut/XCEntity/XCText.h"

// Test the constructor of XCText
TEST(XCTextTest, Constructor) {
    XC::XCText text;
    EXPECT_EQ(text.getText().length(), 0);
}

// Test setting and getting text
TEST(XCTextTest, SetAndGetText) {
    XC::XCText text;
    std::string testStr = "Hello, World!";
    text.setText(testStr);
    EXPECT_EQ(text.getText(), testStr);
}

// Test getting the length of the text
TEST(XCTextTest, GetTextLength) {
    XC::XCText text;
    std::string testStr = "Test Text";
    text.setText(testStr);
    EXPECT_EQ(text.getTextLength(), testStr.length());
}