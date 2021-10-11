#ifndef _SQUARE_H_
#define _SQUARE_H_

namespace Collision2D {
    
    struct Boundary {
        double x0;
        double y0;
        double size;
    };

    struct Square {
        double x0;
        double y0;
        double size;
        // just for friendly usage
        int __id;
    };
    
}

#endif