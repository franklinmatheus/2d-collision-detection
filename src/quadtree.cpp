#include "collision2d.h"

using namespace Collision2D;

void Quadtree::clearTree() {
    squares.clear();

    if (q1 != NULL) {
        q1->clearTree();
        q1 = NULL;
    }
    
    if (q2 != NULL) {
        q2->clearTree();
        q2 = NULL;
    }
    
    if (q3 != NULL) {
        q3->clearTree();
        q3 = NULL;
    }
    
    if (q4 != NULL) {
        q4->clearTree();
        q4 = NULL;
    }
}

void Quadtree::subdivideNode() {
    int childrenLevel = this->level + 1;
    
    auto x0 = this->boundary.x0;
    auto y0 = this->boundary.y0;
    auto childrenSize = this->boundary.size/2;

    this->q1 = new Quadtree(childrenLevel, {x0+childrenSize, y0, childrenSize});
    this->q2 = new Quadtree(childrenLevel, {x0, y0, childrenSize});
    this->q3 = new Quadtree(childrenLevel, {x0, y0+childrenSize, childrenSize});
    this->q4 = new Quadtree(childrenLevel, {x0+childrenSize, y0+childrenSize, childrenSize});
}

Location Quadtree::quadrantSearch(Square _square) {
    bool top = (_square.y0 > (this->boundary.y0 + (this->boundary.size/2)));
    bool bottom = ((_square.y0 + _square.size) < (this->boundary.y0 + (this->boundary.size/2)));
    bool left = ((_square.x0 + _square.size) < (this->boundary.x0 + (this->boundary.size/2)));
    bool right = (_square.x0 > (this->boundary.x0 + (this->boundary.size/2)));
    
    if (top && right) return Location::QUADRANT1;
    else if (top && left) return Location::QUADRANT2;
    else if (bottom && left) return Location::QUADRANT3;
    else if (bottom && right) return Location::QUADRANT4;

    return Location::PARENT;
}

void Quadtree::insertSquare(Square &_square) {
    auto square_loc = this->quadrantSearch(_square);
    
    if (square_loc == Location::QUADRANT1 && this->q1 != NULL) this->q1->insertSquare(_square);
    else if (square_loc == Location::QUADRANT2 && this->q2 != NULL) this->q2->insertSquare(_square);
    else if (square_loc == Location::QUADRANT3 && this->q3 != NULL) this->q3->insertSquare(_square);
    else if (square_loc == Location::QUADRANT4 && this->q4 != NULL) this->q4->insertSquare(_square);
    else {
        this->squares.push_back(_square);

        if (this->squares.size() > this->max_objects && this->q1 == NULL && this->q2 == NULL && this->q3 == NULL && this->q4 == NULL) {
            this->subdivideNode();

            for (unsigned int i(0); i < this->squares.size(); /* empty */) {
                auto loc_temp = this->quadrantSearch(this->squares[i]);

                if (loc_temp == Location::PARENT) i++;
                else {
                    if (loc_temp == Location::QUADRANT1) {
                        this->q1->insertSquare(this->squares[i]);
                        this->squares.erase(this->squares.begin() + i);
                    } else if (loc_temp == Location::QUADRANT2) {
                        this->q2->insertSquare(this->squares[i]);
                        this->squares.erase(this->squares.begin() + i);
                    } else if (loc_temp == Location::QUADRANT3) {
                        this->q3->insertSquare(this->squares[i]);
                        this->squares.erase(this->squares.begin() + i);
                    } else {
                        this->q4->insertSquare(this->squares[i]);
                        this->squares.erase(this->squares.begin() + i);
                    }
                }
            }
        }
    }
}

std::vector<Square> Quadtree::closeSquares(Square _square) {
    std::vector<Square> couldCollide;
    auto square_loc = this->quadrantSearch(_square);

    if (square_loc == Location::QUADRANT1 && this->q1 != NULL) couldCollide = this->q1->closeSquares(_square);
    else if (square_loc == Location::QUADRANT2 && this->q2 != NULL) couldCollide = this->q2->closeSquares(_square);
    else if (square_loc == Location::QUADRANT3 && this->q3 != NULL) couldCollide = this->q3->closeSquares(_square);
    else if (square_loc == Location::QUADRANT4 && this->q4 != NULL) couldCollide = this->q4->closeSquares(_square);

    couldCollide.insert(couldCollide.end(), this->squares.begin(), this->squares.end());
    return couldCollide;
}

void Quadtree::printSquarePath(Square _square) {
    auto square_loc = this->quadrantSearch(_square);
    
    if (square_loc == Location::PARENT || (this->q1 == NULL)) std::cout << " | L" << this->level << ", root";
    else {
        std::cout << " | L" << this->level << ", Q" << square_loc+1;
        if (square_loc == Location::QUADRANT1 && this->q1 != NULL) this->q1->printSquarePath(_square);
        else if (square_loc == Location::QUADRANT2 && this->q2 != NULL) this->q2->printSquarePath(_square);
        else if (square_loc == Location::QUADRANT3 && this->q3 != NULL) this->q3->printSquarePath(_square);
        else if (square_loc == Location::QUADRANT4 && this->q4 != NULL) this->q4->printSquarePath(_square);
    }
}