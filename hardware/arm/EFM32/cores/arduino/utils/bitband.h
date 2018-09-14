/* 
  huaweiwx@sina.com 2018.  All right reserved.

  for stm32 m3/m4 sram/peripheral bitband io opration
  add arduino style class BB_PIN 2017.12.20
  add LL_PIN class for all stm32 chips
  add class BB_VAR 2018.2.12 
  support stm32h7x use hallib 2018.4.2 
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef __BITBAND_H__
#define __BITBAND_H__
#include "arduino.h"
#include "em_bitband.h"

#define MEM_ADDR(addr)  *((volatile unsigned long  *)((uint32_t)addr)) 

#if defined(BITBAND_PER_BASE)
//bitband io opration,ʵ��51���Ƶ�GPIO���ƹ���
#define BITBAND(addr, bitnum) (BITBAND_PER_BASE+(((uint32_t)addr)<<5)+(bitnum<<2)) 
#define BITBAND_ADDR(addr, bitnum)   MEM_ADDR(BITBAND((uint32_t)(addr), bitnum)) 
#endif

#ifdef __cplusplus
class BB_PIN{
 public:
     BB_PIN(__ConstPin cpin): cpin(cpin){};
       __ConstPin cpin;

	 const uint32_t inReg  =(const uint32_t)&GPIO->P[cpin.GPIOx_Port].DIN;
	 const uint32_t outReg =(const uint32_t)&GPIO->P[cpin.GPIOx_Port].DOUT;
	 
     const uint32_t bb_inadr = BITBAND(inReg,cpin.pin);
     const uint32_t bb_outadr = BITBAND(outReg,cpin.pin);
	 
     inline __attribute__((always_inline))
     bool read() {return MEM_ADDR(bb_inadr);}

     inline __attribute__((always_inline))
     void write(bool value){MEM_ADDR(this->bb_outadr) = value;}
  
     inline BB_PIN & operator = (bool value) __attribute__((always_inline)) {
       this->write(value);
       return *this;
     }
  
     BB_PIN& operator = (BB_PIN& rhs) {
       this->write(rhs.read());
       return *this;
     }
  
     inline BB_PIN & operator << (bool value) __attribute__((always_inline)) {
       this->write(value);
       return *this;
     }
  
     inline BB_PIN & operator << (int value) __attribute__((always_inline)) {
       this->write((bool)value);
       return *this;
    }

    template<class T> 
    inline BB_PIN & operator >> (T &value){
       value = this->read();
       return *this;
    }

    inline __attribute__((always_inline))
    void high(){MEM_ADDR(this->bb_outadr) = 0x1U;}

    inline __attribute__((always_inline))
    void low(){MEM_ADDR(this->bb_outadr) = 0x0U;}

    inline operator bool () __attribute__((always_inline)) {
      return (MEM_ADDR(this->bb_inadr));
    }

	inline void operator  !() __attribute__((always_inline)) {
      digitalToggle(cpin);
    }

/*----- comptabled with DigitalPin ----------*/
    inline __attribute__((always_inline))
    void toggle(){write(!MEM_ADDR(this->bb_outadr));}

    inline __attribute__((always_inline))
    void config(uint32_t mode, bool value) {  /*compatale with digitalPin*/
	  this->mode(mode);
      this->write(value);
    }

    inline __attribute__((always_inline))
    void mode(uint32_t mode){
           pinMode(cpin,mode);
	}
	  
    inline __attribute__((always_inline))
    void attach(voidFuncPtr callback, uint32_t mode){
	   attachInterrupt(cpin, callback, mode);
    }
  
  inline __attribute__((always_inline))
  void detach(void){
	  detachInterrupt(cpin);
  }
};

#endif //__cplusplus
#endif //__BITBAND_H__