#include <iostream>
#include <gtest/gtest.h>
#include "FloydClass.h"
#include <fstream>

using namespace std;


TEST(testFloyd, firstTest) {
    setlocale(LC_ALL, "rus");
    ifstream input("C:\\Users\\Dogge!\\CLionProjects\\Laba4\\newInput.txt");
    Floyd newFloyd(input);
    EXPECT_EQ(55, newFloyd.getShortestPath("Хабаровск", "Санкт-Петербург"));
}

TEST(testFloyd, secondTest) {
    ifstream input("C:\\Users\\Dogge!\\CLionProjects\\Laba4\\newInput2.txt");
    Floyd newFloyd(input);
    EXPECT_EQ(39, newFloyd.getShortestPath("Amsterdam", "Berlin"));
}

TEST(testFloyd, errorTest) {
    ifstream input("C:\\Users\\Dogge!\\CLionProjects\\Laba4\\newInput.txt");
    Floyd newFloyd(input);
    try {
        newFloyd.getShortestPath("Хабаровск", "Сыктывкар");
    }
    catch  (invalid_argument error) {
        ASSERT_STREQ("There is no such cities",error.what());
    }
}

TEST(testFloyd, errorInput) {
    ifstream input("C:\\Users\\Dogge!\\CLionProjects\\Laba4\\newInput3.txt");
    try {
        Floyd newFloyd(input);
    }
    catch  (invalid_argument error) {
        ASSERT_STREQ("Wrong type of input",error.what());
    }
}
TEST(testFloyd, errorInput2) {
    ifstream input("C:\\Users\\Dogge!\\CLionProjects\\Laba4\\newInput4.txt");
    try {
        Floyd newFloyd(input);
    }
    catch  (invalid_argument error) {
        ASSERT_STREQ("Wrong type of input",error.what());
    }
}