#ifndef __SMART_H
#define __SMART_H
#include "sys.h"

void mechanical_grip(int mode);
void thing_loction(int point1,int point2,int point3);
void change_wall(void);
void clearfill(void);
void warehouse_finding(int start_location,int corner);
void init_mechanical_grip(void);
void put_thing(int goods);
void smart_put_thing(int view_flag);
void take_photo_mechanical_grip(void);
#endif
