
#include "doctest.h"
#include <iostream>
#include <vector>
#include <climits>
#include "range.hpp"
#include "accumulate.hpp"
#include "filterfalse.hpp"
#include "compress.hpp"


using namespace itertools;
TEST_CASE("Range"){
    int checker = 0 ;
    for(int i : range(0,20)) {
        CHECK_EQ(i,checker);        ++checker;
    }
    int max = INT_MAX;    int min = INT_MIN;

    CHECK_NOTHROW(for(int i : range(0,max/20)){});
    CHECK_NOTHROW(for(int i : range(min/20,0)){});
    CHECK_NOTHROW(for(int i : range(min/40,max/40)){});
}
TEST_CASE("accumulate range"){
   int checker=0;
    std::vector<int> check = {1 ,3 ,6 ,10 ,15 ,21 ,28 ,36 ,45 ,55 ,66  };
    //1 3 6 10 15 21 28 36 45 55 66
    for(int i : accumulate(range(1,12))){
        CHECK_EQ(i,check[checker]);
        checker++;
    }
};
TEST_CASE("accumulate range + function"){
    int checker_1 = 0 ;
    std::vector<int> check = {1, 2 ,6, 24 ,120 ,720 ,5040 ,40320 ,362880 ,3628800 ,39916800 };
    for(int i : accumulate(range(1,12),[](int x, int y){return x*y;})){
       CHECK_EQ(i,check[checker_1]);
       checker_1 ++ ;

    }
}
TEST_CASE("accumulate vector<int>"){
    int checker_2 = 0 ;
    std::vector<int> check = {1 ,2 ,10 ,120 ,1560 ,34320 ,858000 ,30888000};
    std::vector<int> vec = {1, 2, 5, 12, 13 , 22 ,25 , 36};

    for(int i : accumulate(vec,[](int x, int y){return x*y;})){
                CHECK_EQ(i,check[checker_2]);
        checker_2 ++ ;
    }
}
TEST_CASE("accumulate vector<double> + function"){
    int checker_3 = 0 ;
    std::vector<double> check = {1.5, 3.7, 8.93, 21.33, 34.53, 56.545, 81.675, 117.675 };
    std::vector<double> vec = {1.5, 2.2, 5.23, 12.4, 13.2 , 22.015 ,25.13 , 36};

    for(double i : accumulate(vec,[](double x, double y){return x+y;})){
       CHECK_EQ(i, check[checker_3]);
       checker_3 ++ ;
    }
}
TEST_CASE("accumulate vector<string>"){
    int checker_4=0;
    std::vector<std::string> check = {"I" ,"IL" ,"ILO" ,"ILOV" ,"ILOVE" ,"ILOVECPP"};
    std::vector<std::string> vec = {"I", "L", "O","V","E","CPP"};
    for(auto i : accumulate(vec)){
        CHECK_EQ(i, check[checker_4]);
        checker_4 ++ ;
    }

}
TEST_CASE("filterfalse with bool vector") {
    typedef struct {
        bool operator()(bool expression) const {
            return expression;
        }
    } boolfunction;

    std::vector<bool> boolVec = {true, false, true, true, false, true, false, true, true, false, true, false, true, true, false};
    boolfunction checker;
    for (auto i : filterfalse(checker, boolVec)) {
        CHECK(i == false);
    }
}

TEST_CASE("filterfalse with bool vector") {

    struct divideBy2 {
        bool operator()(int i) const { return (i%2 == 0); }
    };
    int checker_5=0;
    std::vector<int> vec = {1,2,3,4,5,6,7,8,9,10};
    std::vector<int> checker = {1,3,5,7,9};
    for (auto i : filterfalse(divideBy2{}, vec)) {
        CHECK(checker[checker_5] == i);
        checker_5++;
    }
}
TEST_CASE("Compress with bool vector") {
    std::vector<bool> bvec = {true, true, true, true, true, true, true, true, true, true, true, true, false};
    int checker_6 = 0;
    std::vector<int> check = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    for (auto i: compress(range(0, 13), bvec)) {
        CHECK_EQ(i, check[checker_6]);
        checker_6++;
    }
    CHECK_THROWS(check.at(checker_6+1));


}

TEST_CASE("Compress with bool ") {
    int checker_7 = 0;
    std::vector<bool> bvec = {false, true, true, false, true, true, false,true, true, false,true,true,true};

    std::vector<int> check = {1,2, 4,5, 7,8,10,11,12,13};
    for (auto i: compress(range(0, 13),bvec)) {
        CHECK_EQ(i, check[checker_7]);
        checker_7++;
    }
    CHECK_THROWS(check.at(checker_7+1));


}
