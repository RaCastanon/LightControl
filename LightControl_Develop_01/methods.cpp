#include "methods.h"

// Global variables declarations
unsigned int middlePoints[5][2];

// Controller variables
int p_err = 0;
int i_err = 0;

double mu_e_vn = 0.0;
double mu_e_n = 0.0;
double mu_e_z = 0.0;
double mu_e_p = 0.0;
double mu_e_vp = 0.0;

double mu_ei_vn = 0.0;
double mu_ei_n = 0.0;
double mu_ei_z = 0.0;
double mu_ei_p = 0.0;
double mu_ei_vp = 0.0;

/* Function name: FuzzyCtl(uint, uint)
 * Developer:     Raul Castañon
 * Details:       Get control signal
 */
unsigned int FuzzyCtl(unsigned int intensityLevel, unsigned int setPoint)
{
    // Local variable declarations
    unsigned int ut = 0; // This will be the return control variable

    // Get the proportional error
    p_err = setPoint - intensityLevel;
    // Verify limits of the proportional error
    if(p_err >= 255)
    {
        p_err = 250;
    }
    else if (p_err <= 0)
    {
        p_err = 5;
    }
    else
    {
        // do nothing
    }
    // Get the integral error
    i_err += p_err;
    // Verify limits of the integral error
    if(i_err >= 255)
    {
        i_err = 250;
    }
    else if (i_err <= 0)
    {
        i_err = 5;
    }
    else
    {
        // do nothing
    }
    // Set the membership degree variables for p_err
    memDegreeP(p_err);
    // Set the membership degree variables for i_err
    memDegreeI(i_err);
    // Apply the fuzzy rules

    // Get the output from the controler

    return 0;
}

/* Function name: memDegreeI(int)
 * Developer:     Raul Castañon
 * Details:       Get membership degree
 */
void memDegreeI(int i_err)
{
    // Function from the VERY_NEGATIVE area
    if((VERY_NEGATIVE <= i_err) && (NEGATIVE > i_err))
    {
        mu_ei_vn = (NEGATIVE - i_err)/(NEGATIVE - VERY_NEGATIVE);
    }
    else
    {
        mu_ei_vn = 0.0;
    }
    // Funtion of the NEGATIVE area
    if((VERY_NEGATIVE <= i_err) && (NEGATIVE > i_err))
    {
        mu_ei_n = (i_err - VERY_NEGATIVE)/(NEGATIVE - VERY_NEGATIVE);
    }
    else if((NEGATIVE <= i_err) && (ZERO > i_err))
    {
        mu_ei_n = (ZERO - i_err)/(ZERO - NEGATIVE);
    }
    else
    {
        mu_ei_n = 0.0;
    }
    // Function of the ZERO area
    if((NEGATIVE <= i_err) && (ZERO> i_err))
    {
        mu_ei_z = (i_err - NEGATIVE)/(ZERO - NEGATIVE);
    }
    else if((ZERO <= i_err) && (POSITIVE > i_err))
    {
        mu_ei_z = (POSITIVE - i_err)/(POSITIVE - ZERO);
    }
    else
    {
        mu_ei_z = 0.0;
    }
    // Function of the POSITIVE area
    if((ZERO <= i_err) && (POSITIVE> i_err))
    {
        mu_ei_p = (i_err - ZERO)/(POSITIVE - ZERO);
    }
    else if((POSITIVE <= i_err) && (VERY_POSITIVE > i_err))
    {
        mu_ei_p = (VERY_POSITIVE - i_err)/(VERY_POSITIVE - POSITIVE);
    }
    else
    {
        mu_ei_p = 0.0;
    }
    // Function of the VERY_POSITIVE area
    if((POSITIVE <= i_err) && (VERY_POSITIVE> i_err))
    {
        mu_ei_p = (i_err - POSITIVE)/(VERY_POSITIVE - POSITIVE);
    }
    else
    {
        mu_ei_p = 0.0;
    }

}

/* Function name: memDegreeP(int)
 * Developer:     Raul Castañon
 * Details:       Get membership degree
 */
void memDegreeP(int p_err)
{
    // Function from the VERY_NEGATIVE area
    if((VERY_NEGATIVE <= p_err) && (NEGATIVE > p_err))
    {
        mu_e_vn = (NEGATIVE - p_err)/(NEGATIVE - VERY_NEGATIVE);
    }
    else
    {
        mu_e_vn = 0.0;
    }
    // Funtion of the NEGATIVE area
    if((VERY_NEGATIVE <= p_err) && (NEGATIVE > p_err))
    {
        mu_e_n = (p_err - VERY_NEGATIVE)/(NEGATIVE - VERY_NEGATIVE);
    }
    else if((NEGATIVE <= p_err) && (ZERO > p_err))
    {
        mu_e_n = (ZERO - p_err)/(ZERO - NEGATIVE);
    }
    else
    {
        mu_e_n = 0.0;
    }
    // Function of the ZERO area
    if((NEGATIVE <= p_err) && (ZERO> p_err))
    {
        mu_e_z = (p_err - NEGATIVE)/(ZERO - NEGATIVE);
    }
    else if((ZERO <= p_err) && (POSITIVE > p_err))
    {
        mu_e_z = (POSITIVE - p_err)/(POSITIVE - ZERO);
    }
    else
    {
        mu_e_z = 0.0;
    }
    // Function of the POSITIVE area
    if((ZERO <= p_err) && (POSITIVE> p_err))
    {
        mu_e_p = (p_err - ZERO)/(POSITIVE - ZERO);
    }
    else if((POSITIVE <= p_err) && (VERY_POSITIVE > p_err))
    {
        mu_e_p = (VERY_POSITIVE - p_err)/(VERY_POSITIVE - POSITIVE);
    }
    else
    {
        mu_e_p = 0.0;
    }
    // Function of the VERY_POSITIVE area
    if((POSITIVE <= p_err) && (VERY_POSITIVE> p_err))
    {
        mu_e_p = (p_err - POSITIVE)/(VERY_POSITIVE - POSITIVE);
    }
    else
    {
        mu_e_p = 0.0;
    }
}

/* Function name: setMiddlePoints(uint, uint)
 * Developer:     Raul Castañon
 * Details:       Get middle points from the data of the image
 */
void setMiddlePoints(unsigned int cols, unsigned int rows)
{
    // Initialize global variable
    memset(middlePoints, 0, sizeof(middlePoints));

    // Get middle points
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
