#include "real_turtlebot3_proximity_sensor.h"

/****************************************/
/****************************************/

CRealTurtlebot3ProximitySensor::CRealTurtlebot3ProximitySensor(knet_dev_t* pt_dspic) :
   CRealTurtlebot3Device(pt_dspic) {
}
   
/****************************************/
/****************************************/

CRealTurtlebot3ProximitySensor::~CRealTurtlebot3ProximitySensor() {
}

/****************************************/
/****************************************/

#define SETREADING(ARGOSIDX, KH4IDX)                                    \
   m_tReadings[ARGOSIDX].Value = (GetBuffer()[KH4IDX*2] | GetBuffer()[KH4IDX*2+1] << 8) / 65536.0;

void CRealTurtlebot3ProximitySensor::Do(Real f_elapsed_time) {
   kh4_proximity_ir(GetBuffer(), GetDSPic());
   SETREADING(0, 3);
   SETREADING(1, 2);
   SETREADING(2, 1);
   SETREADING(3, 0);
   SETREADING(4, 7);
   SETREADING(5, 6);
   SETREADING(6, 5);
   SETREADING(7, 4);
}

/****************************************/
/****************************************/
