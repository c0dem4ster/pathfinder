#include <math.h>
#include <stdint.h>
#include <iostream>
#include "obs_avoidance.hh"

using namespace std;

//convert mm to pixel coordinates
int16_t cx2qtc(int16_t xpos)
{
  return xpos/8;
}

int16_t cy2qtc(int16_t ypos)
{
  return ypos/(-8);
}

//distance between the given points
float dist(float pt0[2], float pt1[2])
{
  //pythagorean theorem
  return sqrt(abs(((pt0[0]-pt1[0])*(pt0[0]-pt1[0]))+((pt0[1]-pt1[1])*(pt0[1]-pt1[1]))));
}

//repulsion force as vector
void repulsion(float cpos[2], float opos[2], float fpos[2], float repulsion[2])
{
  float disto = dist(cpos, opos);
  float distf = dist(cpos, fpos);
  float repmodel;

  if(disto < (3*mdist))
  {
    repmodel=((disto/mdist-3)*(disto/mdist-3))*1;
    repulsion[0] = (((cpos[0]-opos[0])/disto))*repmodel;
    repulsion[1] = (((cpos[1]-opos[1])/disto))*repmodel;
    if(((opos[0]-cpos[0])*(fpos[1]-cpos[1])-(opos[1]-cpos[1])*(fpos[0]-cpos[0]))>0)
    {
      repulsion[0] -= ((fpos[1]-cpos[1])/distf)*repmodel;
      repulsion[1] += ((fpos[0]-cpos[0])/distf)*repmodel;
    }
    else
    {
      repulsion[0] += ((fpos[1]-cpos[1])/distf)*repmodel;
      repulsion[1] -= ((fpos[0]-cpos[0])/distf)*repmodel;
    }
  }
  else
  {
    repulsion[0] = 0;
    repulsion[1] = 0;
  }
}

uint16_t getwpts(float cpos[2], float fpos[2], int16_t wpts[1000000][2], float obs[nobs][2])
{
  uint16_t nwpts = 0;
  float deviation[2];
  float distf = dist(cpos, fpos);
  while(distf > wptd)
  {
    wpts[nwpts][0] = cpos[0];
    wpts[nwpts][1] = cpos[1];
    cpos[0] += ((fpos[0]-cpos[0])/distf)*wptd;
    cpos[1] += ((fpos[1]-cpos[1])/distf)*wptd;
    for(uint8_t cobs=0; cobs<nobs; cobs++)
    {
      repulsion(cpos, obs[cobs], fpos, deviation);
      cpos[0] += deviation[0];
      cpos[1] += deviation[1];
    }
    nwpts++;
    distf = dist(cpos, fpos);
  }
  wpts[nwpts][0] = cpos[0];
  wpts[nwpts][1] = cpos[1];
  return nwpts;
}
