#include "doctest.h"
#include <string>
#include "Direction.hpp"

using namespace ariel;
using namespace std;

Board::Board board;

int MAX = 26;

// Generates random strings with n lenght
string RandomString(int n) 
{  
    // Alphbetic 
    char alphabet[MAX] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 
                          'h', 'i', 'j', 'k', 'l', 'm', 'n',  
                          'o', 'p', 'q', 'r', 's', 't', 'u', 
                          'v', 'w', 'x', 'y', 'z' }; 
    
    string res = ""; 
    for (int i = 0; i < n; i++)  
        res = res + alphabet[rand() % MAX]; 
      
    return res;
} 

TEST_CASE("Checking init values"){
    //Checking if the borad is good initilizted 200*200
    string horizontal_str, vertical_str;
    for(int i=0;i<200;++i){
        horizontal_str+='_';
        vertical_str+='_';
    }
    //Checking horizontal string
    CHECK(board->read(0,0,ariel::Direction::Horizontal,200) == horizontal_str);
    //Checking vertical string
    CHECK(board->read(0,0,ariel::Direction::Vertical,200) == vertical_str);

}

TEST_CASE("Simple Posting"){

    //Checking 20 diffrent posting 
    for(int i=1;i<21;++i){
        //Generated string
        string randomString = RandomString(i);
        //Horizontal check
        CHECK_NOTHROW(board->post(rand()%100, rand()%100, ariel::Direction::Horizontal, RandomString));
        //Vertical check
        CHECK_NOTHROW(board->post(rand()%100, rand()%100, ariel::Direction::Vertical, RandomString));
    }

    //posting empty string
    CHECK_NOTHROW(board->post(0, 0, ariel::Direction::Horizontal, ""));
    CHECK_NOTHROW(board->post(0, 0, ariel::Direction::Vertical, ""));


}

TEST_CASE("Simple Reading"){
    //Checking 20 diffrent reading
    for(int i=0;i<20;++i){
        //Random length from [1,20]
        int randomLength = rand()%20+1 ;
        //Generated string
        string randomString = RandomString(randomLength);
        //Random row
        int row = rand()%100;
        //Random column
        int col = rand()%100;

        //Posting the message
        board->post(row, col, ariel::Direction::Horizontal, RandomString);
        //Checking read functinality works
        CHECK(board->read(row, col, ariel::Direction::Horizontal, randomLength)==RandomString);
    }

    //Zero reading
    CHECK(board->read(0, 0, ariel::Direction::Horizontal, 0)==string(""));
    CHECK(board->read(0, 0, ariel::Direction::Vertical, 0)==string(""));


}


TEST_CASE("Bad posting"){
    //Negative row
    CHECK_THROWS(board->post(-1,0,ariel::Direction::Horizontal, "Hello"));
    CHECK_THROWS(board->post(-1,0,ariel::Direction::Vertical, "Hello"));

    //Negative col
    CHECK_THROWS(board->post(0,-1,ariel::Direction::Horizontal, "Hello"));
    CHECK_THROWS(board->post(0,-1,ariel::Direction::Vertical, "Hello"));

}

TEST_CASE("Bad reading"){
    //Negative row
    CHECK_THROWS(board->read(-1,0,ariel::Direction::Horizontal, 10));
    CHECK_THROWS(board->read(-1,0,ariel::Direction::Vertical, 10));

    //Negative col
    CHECK_THROWS(board->read(0,-1,ariel::Direction::Horizontal, 10));
    CHECK_THROWS(board->read(0,-1,ariel::Direction::Vertical, 10));

    //Negative length values
    CHECK_THROWS(board->read(0,-1,ariel::Direction::Vertical, -1));
    CHECK_THROWS(board->read(0,-1,ariel::Direction::Vertical, -100));
}

