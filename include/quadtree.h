#ifndef _QUADTREE_H_
#define _QUADTREE_H_

#include "collision2d.h"

namespace Collision2D {
    
    typedef enum {
        QUADRANT1,
        QUADRANT2,
        QUADRANT3,
        QUADRANT4,
        PARENT
    } Location;

    class Quadtree {
        Quadtree *q1;
        Quadtree *q2;
        Quadtree *q3;
        Quadtree *q4;

        unsigned int level;
        const unsigned int max_objects = 4;
        std::vector<Collision2D::Square> squares;
        Boundary boundary;

        public:
        Quadtree(int _level, Boundary _boundary):
            q1(NULL),
            q2(NULL),
            q3(NULL),
            q4(NULL),
            level(_level),
            boundary(_boundary)
        {}

        Quadtree() { Quadtree(0,{0,0,0}); }

        int squaresQuantity() { return (int) squares.size(); }

        void clearTree();
        void subdivideNode();
        void insertSquare(Square &_square);
        Location quadrantSearch(Square _square);
        std::vector<Square> closeSquares(Square _square);
        void printSquarePath(Square _square);
    };
}

#endif