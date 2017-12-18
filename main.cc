#include <QApplication>
#include <QLabel>
#include <QPicture>
#include <QPainter>
#include <unistd.h>
#include "obs_avoidance.hh"


int main(int argc, char *argv[])
{
   QApplication a(argc, argv);
   QLabel l;
   QPicture pi;
   QPainter p(&pi);
   int16_t wpts[1000000][2];
   float cpos[2] = {-4000, -2000};
   float fpos[2] = {4000, 2000};
   float opos[nobs][2] = {{1000, 0},
                          {2000, 1000},
                          {-2000, -1000},
                          {0, -1000},
                          {-1000, 0}};

   p.setRenderHint(QPainter::Antialiasing);

   //draw boundaries
   p.setPen(QPen(Qt::black, 8, Qt::SolidLine, Qt::RoundCap));
   p.drawLine(cx2qtc(4500), cy2qtc(3000), cx2qtc(4500), cy2qtc(-3000));
   p.drawLine(cx2qtc(-4500), cy2qtc(3000), cx2qtc(4500), cy2qtc(3000));
   p.drawLine(cx2qtc(-4500), cy2qtc(3000), cx2qtc(-4500), cy2qtc(-3000));
   p.drawLine(cx2qtc(-4500), cy2qtc(-3000), cx2qtc(4500), cy2qtc(-3000));

   //draw direct line
   p.setPen(QPen(Qt::red, 2, Qt::DashDotLine, Qt::RoundCap));
   p.drawLine(cx2qtc(cpos[0]), cy2qtc(cpos[1]), cx2qtc(fpos[0]), cy2qtc(fpos[1]));

   //draw obstacles
   p.setPen(QPen(Qt::black, 18, Qt::SolidLine, Qt::RoundCap));
   for(uint8_t cobs=0; cobs<nobs; cobs++)
   {
     p.drawLine(cx2qtc(opos[cobs][0]), cy2qtc(opos[cobs][1]), cx2qtc(opos[cobs][0]), cy2qtc(opos[cobs][1]));
   }

   uint16_t nwpts = getwpts(cpos, fpos, wpts, opos);

   p.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));
   for(int cpt=0; cpt<nwpts; cpt++)
   {
     p.drawLine(cx2qtc(wpts[cpt][0]), cy2qtc(wpts[cpt][1]), cx2qtc(wpts[cpt+1][0]), cy2qtc(wpts[cpt+1][1]));
   }

   p.end();
   l.setPicture(pi);
   l.show();
   return a.exec();
}
