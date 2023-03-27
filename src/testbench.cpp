/** This file is used as a test bench we can unit test functions
 */

#include <math.h>
#include <cmath>
#include <utility>
#include "testbench.hpp"
using namespace std;

double dist(double lat1, double lat2, double lon1, double lon2 )  {
    
    double earth_radius = 6371*1000;
    double lat1_radians = lat1 * M_PI/180;
    double lat2_radians = lat2 * M_PI/180;
    double delta_lat_radians = abs(lat2 - lat1) * M_PI/180;
    double delta_lon_radians = abs(lon2 - lon1) * M_PI/180;

    double a = sin(delta_lat_radians/2) + sin(delta_lat_radians/2) + cos(lat1_radians) *
        cos(lat2_radians) * sin(delta_lon_radians/2) * sin(delta_lon_radians/2);

    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    
    double distance = earth_radius * c / 1000; // Convert meters to kilometers
    return distance;
}