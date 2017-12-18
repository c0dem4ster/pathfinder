/*functions for trajectory generation*/

#include <stdint.h>

//waypoint distance
#define wptd 15

//number of obstacles
#define nobs 5

//minimum distance between robots
#define mdist 500

//soccer field area
#define height 6000
#define length 9000

//convert mm to pixel coordinates
int16_t cx2qtc(int16_t xpos);
int16_t cy2qtc(int16_t ypos);

//distance between given points
float dist(float pt0[2], float pt1[2]);

//repulsion force as vector
void repulsion(float cpos[2], float opos[2], float fpos[2], float repulsion[2]);

//calculate waypoints
uint16_t getwpts(float cpos[2], float fpos[2], int16_t wpts[1000000][2], float obs[nobs][2]);
