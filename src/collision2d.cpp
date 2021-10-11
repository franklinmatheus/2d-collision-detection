#include "collision2d.h"

using namespace Collision2D;

bool Collision2D::collide(Square _sq1, Square _sq2) {
    if ((_sq1.x0 + _sq1.size) < _sq2.x0 || _sq1.x0 > (_sq2.x0 + _sq2.size)) return false;
    if (_sq1.y0 > (_sq2.y0 + _sq2.size) || (_sq1.y0 + _sq2.size) < _sq2.y0) return false;
    return true;
}

std::vector<Square> Collision2D::collidingSquares(Square _square, std::vector<Square> _squares) {
    std::vector<Square> colliding;
    for (unsigned int i(0); i < _squares.size(); ++i)
        if (_square.__id != _squares[i].__id)
            if (collide(_square, _squares[i])) colliding.push_back(_squares[i]);
    
    return colliding;
}

std::vector<int> Collision2D::collidingSquaresIds(Square _square, std::vector<Square> _squares) {
    std::vector<int> colliding;
    for (unsigned int i(0); i < _squares.size(); ++i)
        if (_square.__id != _squares[i].__id && collide(_square, _squares[i]))
            colliding.push_back(_squares[i].__id);

    return colliding;
}