/**
 * @file <argos3/plugins/robots/turtlebot3/control_interface/ci_turtlebot3_proximity_sensor.cpp>
 *
 * @author Carlo Pinciroli <ilpincy@gmail.com>
 */

#include "ci_turtlebot3_proximity_sensor.h"
#include <argos3/core/utility/math/angles.h>

#ifdef ARGOS_WITH_LUA
#include <argos3/core/wrappers/lua/lua_utility.h>
#endif

namespace argos {

   /****************************************/
   /****************************************/

   static CRadians SPACING = CRadians(ARGOS_PI / 4.0f);

   /****************************************/
   /****************************************/

   CCI_Turtlebot3ProximitySensor::CCI_Turtlebot3ProximitySensor() :
      m_tReadings(8) {
      for(size_t i = 0; i < 8; ++i) {
         m_tReadings[i].Angle = i * SPACING;
         m_tReadings[i].Angle.SignedNormalize();
      }
   }

   /****************************************/
   /****************************************/

   const CCI_Turtlebot3ProximitySensor::TReadings& CCI_Turtlebot3ProximitySensor::GetReadings() const {
     return m_tReadings;
   }

   /****************************************/
   /****************************************/

#ifdef ARGOS_WITH_LUA
   void CCI_Turtlebot3ProximitySensor::CreateLuaState(lua_State* pt_lua_state) {
      CLuaUtility::OpenRobotStateTable(pt_lua_state, "proximity");
      for(size_t i = 0; i < GetReadings().size(); ++i) {
         CLuaUtility::StartTable(pt_lua_state, i+1                           );
         CLuaUtility::AddToTable(pt_lua_state, "angle",  m_tReadings[i].Angle);
         CLuaUtility::AddToTable(pt_lua_state, "value",  m_tReadings[i].Value);
         CLuaUtility::EndTable  (pt_lua_state                                );
      }
      CLuaUtility::CloseRobotStateTable(pt_lua_state);
   }
#endif

   /****************************************/
   /****************************************/

#ifdef ARGOS_WITH_LUA
   void CCI_Turtlebot3ProximitySensor::ReadingsToLuaState(lua_State* pt_lua_state) {
      lua_getfield(pt_lua_state, -1, "proximity");
      for(size_t i = 0; i < GetReadings().size(); ++i) {
         lua_pushnumber(pt_lua_state, i+1                 );
         lua_gettable  (pt_lua_state, -2                  );
         lua_pushnumber(pt_lua_state, m_tReadings[i].Value);
         lua_setfield  (pt_lua_state, -2, "value"         );
         lua_pop(pt_lua_state, 1);
      }
      lua_pop(pt_lua_state, 1);
   }
#endif


   /****************************************/
   /****************************************/

   std::ostream& operator<<(std::ostream& c_os,
                            const CCI_Turtlebot3ProximitySensor::SReading& s_reading) {
      c_os << "Value=<" << s_reading.Value
           << ">, Angle=<" << s_reading.Angle << ">";
      return c_os;
   }

   /****************************************/
   /****************************************/

   std::ostream& operator<<(std::ostream& c_os,
                            const CCI_Turtlebot3ProximitySensor::TReadings& t_readings) {
      if(! t_readings.empty()) {
         c_os << "{ " << t_readings[0].Value << " }";
         for(UInt32 i = 1; i < t_readings.size(); ++i) {
            c_os << " { " << t_readings[i].Value << " }";
         }
         c_os << std::endl;
      }
      return c_os;
   }

   /****************************************/
   /****************************************/

}
