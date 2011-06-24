// radixsort.cpp : Defines the entry point for the console application.
// this program sorts the class radixtest by the numbers array contained in radixtest.
//It first examines the first integer in the numbers array, then the second.
//the array test of radixtests is sorted, then outputed to the standard output.
//they will be in the proper order.
//this could also be done by an operator< and used with std::sort
//but that operator would have multiple branches
//I wrote an operator< to show why it would be slow

#include "radix.hpp"
#include <cstdlib>
#include <iostream>
#include <time.h>
class radixtest
{
public:
    int numbers[5];
    radixtest()
    {
        numbers[0] = rand() % 10;
        numbers[1] = rand() % 10;
        numbers[2] = rand() % 10;
        numbers[3] = rand() % 10;
        numbers[4] = rand() % 10;
    }
    inline unsigned char operator[](int num)
    {return ((unsigned char*)numbers)[num];}
    //if this was a template class you would have to generate 20-40
    //different versions of it before all the code made for this function
    //added up to the same amount of code generated just for one operator<
    //the size of code this function takes is constant and does not increase with the amount of numbers
    //operator< increases for each number added on
    inline unsigned char operator[](int num) const
    {return ((unsigned char*)numbers)[num];}
    bool operator<(const radixtest& a) const
    {
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //if this was a template class that was used for many different types
        //think of how much code bloat you would have just from this function
        //not to mention all of the other functions that you would have
        if(numbers[0] < a.numbers[0])
        return true;
        else if(numbers[0] == a.numbers[0])
        {
            if (numbers[1] < a.numbers[1])
                return true;
            else if(numbers[1] == a.numbers[1])
            {
                if(numbers[2] < a.numbers[2])
                    return true;
                else if(numbers[2] == a.numbers[2])
                {
                    if(numbers[3] < a.numbers[3])
                        return true;
                    else if(numbers[3] == a.numbers[3])
                    {
                        if(numbers[4] < a.numbers[4])
                        { return true;}
                    }
                }
            }
        }
        return false;
    }
};
std::ostream& operator<<(std::ostream& o, radixtest& t)
{
    return o << "{" << t.numbers[0] << ", " << t.numbers[1] <<  ", " << t.numbers[2] << ", " << t.numbers[3] << ", " << t.numbers[4] << "}";
}
int main(int argc, char* argv[])
{
    srand((unsigned)time(NULL));
    radixtest tests[1000];
    boost::radix_sort(tests, 1000); 
    for(int x = 0; x < 999; x++)
    {
        std::cout << tests[x] << " ";
        if(tests[x + 1] < tests[x])
        {
            cout << "ERROR" << endl;
        }
    }
	return 0;
}

