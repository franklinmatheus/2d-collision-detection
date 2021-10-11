#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "collision2d.h"

using namespace Collision2D;
using namespace std;

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("two arguments are required:");
        printf("\n<input file name>");
        printf("\n<output file name>");
        return EXIT_FAILURE;
    }
    
    std::ifstream infile("./data/" + (string) argv[1]);
    if(infile.fail()){
        printf("%s does not exist", argv[1]);
        return EXIT_FAILURE;
    }

    vector<Square> squares;
    string line;

    double window_size;
    bool firstline = true;
    int square_id = 0;

    while (getline(infile, line)) {
        std::istringstream iss(line);
        int x, y, size;
        
        if (firstline) {
            iss >> window_size;
            firstline = false;
            continue;
        }

        if (!(iss >> x >> y >> size)) break; 
        
        Square temp = {(double) x, (double) y, (double) size, square_id};
        squares.push_back(temp);
        square_id++;
    }

    int n = squares.size();
    if (n == 0) {
        printf("zero squares in file");
        return EXIT_FAILURE;
    }

    // we create the quadtree
    Quadtree quadtree(0,{0,0,window_size});
    
    // we add the squares (that were read from file) to the quadtree
    for (unsigned int i(0); i < squares.size(); ++i) 
        quadtree.insertSquare(squares[i]);

    // [start] prints the squares paths through the quadtree
    for (unsigned int i(0); i < squares.size(); ++i) {
        cout << i << " ---> ";
        quadtree.printSquarePath(squares[i]);
        cout << "\n";
    }
    cout << "\n\n";
    // [end] prints the squares paths through the quadtree

    // now we check (for each square) the colliders and assign a bool value to the squares (if it collide or not)
    vector<bool> collide(squares.size(),false);
    for (unsigned int i(0); i < squares.size(); ++i)
        if (collide[i] == false) {
            auto couldCollide = quadtree.closeSquares(squares[i]);
            
            // [start] printing possible 'colliders'
            cout << i << " could collide with " << couldCollide.size() << " points  > ";
            
            for (unsigned int j(0); j < couldCollide.size(); ++j) 
                cout << couldCollide[j].__id << ' ';
            cout << '\n';
            // [end] printing possible 'colliders'

            auto colliders = collidingSquaresIds(squares[i], couldCollide);
            if (!colliders.empty())
                collide[i] = true;
            
            for (unsigned int j(0); j < colliders.size(); ++j)
                collide[colliders[j]] = true;
        }

    // save the data to a file (will be used be the python script to 'draw' the squares)
    std::ofstream outfile("./data/" + (string)argv[2]);
    outfile << window_size << endl;
    for (unsigned int i(0); i < squares.size(); ++i)
        outfile << squares[i].x0 << "," << squares[i].y0 << "," << squares[i].size << "," << collide[i] << endl;

    return EXIT_SUCCESS;
}