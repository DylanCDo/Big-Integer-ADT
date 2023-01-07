#include<iostream>
#include<fstream>
#include<string>
#include "BigInteger.h"

using namespace std;

#define MAX_LEN 1024

int main(int argc, char * argv[]){

    ifstream in;
    ofstream out;
    string line;

    // check command line for correct number of arguments
    if( argc != 3 ){
            cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
            return(EXIT_FAILURE);
    }

    // open files for reading and writing 
    in.open(argv[1]);
    if( !in.is_open() ){
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return(EXIT_FAILURE);
    }

    out.open(argv[2]);
    if( !out.is_open() ){
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return(EXIT_FAILURE);
    }

    BigInteger x;
    BigInteger y;

    //Obtaining the two big integers
    for (int i = 0; i < 3; i ++){

        //Retrieving the line
        getline(in, line);

        //If the line is empty, ignore it
        if (line.length() != 0){

            //setting x and y according to the order.
            if (i == 0){
                x = BigInteger(line);
            } else {
                y = BigInteger(line);
            }
            
        }
    }

    //Formatting the output

    //A
    out << x << endl << endl;

    //B
    out << y << endl << endl;

    //A + B
    out << x + y << endl << endl;

    //A - B
    out << x - y << endl << endl;

    //A - A
    out << x - x << endl << endl;

    //Creating two and three for the arithmetic operations.
    BigInteger three = BigInteger("3");
    BigInteger two = BigInteger("2");

    //3A - 2B
    out << three*x - two*y << endl << endl;

    //AB
    out << x * y << endl << endl;

    //A^2
    out << x * x << endl << endl;

    //B^2
    out << y * y << endl << endl;

    //Creating nine and sixteen for the arithmetic operations.
    BigInteger nine = BigInteger("9");
    BigInteger sixteen = BigInteger("16");

    //9A^4 + 16B^5
    out << (nine*(x*x*x*x)) + (sixteen*(y*y*y*y*y)) << endl;

    // close files 
    in.close();
    out.close();

    return(EXIT_SUCCESS);

}
