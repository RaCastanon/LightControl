#include "methods.h"

//Global variables declarations
unsigned int middlePoints[5][2];

/* Function name: setMiddlePoints(uint, uint)
 * Developer:     Raul Castañon
 * Details:       Get middle points from the data of the image
 */
void setMiddlePoints(unsigned int cols, unsigned int rows)
{
    //Initialize global variable
    memset(middlePoints, 0, sizeof(middlePoints));

    //Get middle points
    middlePoints[0][0] = (unsigned int)(cols/2.0);
    middlePoints[0][1] = (unsigned int)(rows/2.0);

    middlePoints[1][0] = (unsigned int)(cols/4.0);
    middlePoints[1][1] = (unsigned int)(rows/4.0);

    middlePoints[2][0] = (unsigned int)(3*(cols/4.0));
    middlePoints[2][1] = (unsigned int)(rows/4.0);

    middlePoints[3][0] = (unsigned int)(cols/4.0);
    middlePoints[3][1] = (unsigned int)(3*(rows/4.0));

    middlePoints[4][0] = (unsigned int)(3*(cols/4.0));
    middlePoints[4][1] = (unsigned int)(3*(rows/4.0));

}
