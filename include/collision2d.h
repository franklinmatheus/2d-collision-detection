#ifndef _COLLISION_2D_
#define _COLLISION_2D_

#include <vector>
#include <iostream>
#include <stdlib.h>
#include "square.h"
#include "quadtree.h"

namespace Collision2D {
    bool collide(Square _sq1, Square _sq2);
    std::vector<Square> collidingSquares(Square _square, std::vector<Square> _squares);
    std::vector<int> collidingSquaresIds(Square _square, std::vector<Square> _squares);
}

#endif