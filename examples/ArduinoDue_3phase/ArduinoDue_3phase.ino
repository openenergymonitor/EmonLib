// Example of using Arduino Due as EmonTx box.
// There are 10 CT inputs connected to various household lines (after circuit breakers)
// and 1 AC-AC voltage adapter connected to one of these lines, used to measure voltage.
// 10 lines are connected to different phases, thus, an extra parameter in voltage() function
// used to indicate a particular phase number. The line with voltage adapter must be phase 1.

#include <EmonLib_3PH.h>


//==========================================================
#define NSENSORS 10

// Instance of EmonTX sensors
EnergyMonitor emon[NSENSORS];

// for each sensor we will print out real power and power factor
typedef struct {
  float realPower;    // 4
  float powerFactor;  // 4
} sEmonSensor;

// Instance of measurement data structure
sEmonSensor EmonTx[NSENSORS];
//==========================================================



void setup() {
  Serial.begin(57600);
  
// Arduino Due can have up to 12 bits of ADC resolution
  analogReadResolution(ADC_BITS);

//---------------------------------------------------------------------
// CALIBRATION
// Note: AC-AC voltage adapter must always be connected to phase 1
//---------------------------------------------------------------------
  // Stove: brown (phase 2)
  emon[0].voltage(11, 334.0, 2.0, 2);   // Voltage: pin, calib, phasecal, line phase.
  emon[0].current(0, 97.7);             // Current: pin, calib.
  // Stove: grey (phase 3)
  emon[1].voltage(11, 334.0, 3.0, 3);   // Voltage: pin, calib, phasecal, line phase.
  emon[1].current(1, 96.2);             // Current: pin, calib.
  // Stove: black (phase 1)
  emon[2].voltage(11, 334.0, 1.7, 1);   // Voltage: pin, calib, phasecal, line phase.
  emon[2].current(2, 95.8);             // Current: pin, calib.
  // Dishwasher (phase 2)
  emon[3].voltage(11, 334.0, 2.0, 2);   // Voltage: pin, calib, phasecal, line phase.
  emon[3].current(3, 95.9);             // Current: pin, calib.
  // Kitchen (phase 3)
  emon[4].voltage(11, 334.0, 3.0, 3);   // Voltage: pin, calib, phasecal, line phase.
  emon[4].current(4, 97.7);             // Current: pin, calib.
  // Living room (phase 1)
  emon[5].voltage(11, 334.0, 1.7, 1);   // Voltage: pin, calib, phasecal, line phase.
  emon[5].current(5, 95.9);             // Current: pin, calib.
  // Common (phase 2)
  emon[6].voltage(11, 334.0, 2.0, 2);   // Voltage: pin, calib, phasecal, line phase.
  emon[6].current(6, 96.4);             // Current: pin, calib.
  // Bath-Toilet (phase 3)
  emon[7].voltage(11, 334.0, 3.0, 3);   // Voltage: pin, calib, phasecal, line phase.
  emon[7].current(7, 96.3);             // Current: pin, calib.
  // Washmachine (phase 1)
  emon[8].voltage(11, 334.0, 1.7, 1);   // Voltage: pin, calib, phasecal, line phase.
  emon[8].current(8, 96.4);             // Current: pin, calib.
  // Floor light (phase 1)
  emon[9].voltage(11, 334.0, 1.7, 1);   // Voltage: pin, calib, phasecal, line phase.
  emon[9].current(9, 95.7);             // Current: pin, calib.
}



void loop() {

  for (int i=0; i<NSENSORS; i++)
  {
    // perform measurements
    emon[i].calcVI(16,2000);    // 2 h.c. for buffering + 14 h.c. for measuring
    
    // convert and pack data
    EmonTx[i].realPower = (float)emon[i].realPower;
    EmonTx[i].powerFactor = (float)emon[i].powerFactor;
  }
  
  // Voltage sensor is connected to Washmachine line
  float Voltage = (float)emon[8].Vrms;

  // Printing out
  Serial.print("Voltage: "); Serial.println(Voltage);
  for(int i=0; i<NSENSORS; i++)
  {
    Serial.print(i); Serial.print(": ");
    Serial.print("  RP=");
    Serial.print(EmonTx[i].realPower);
    Serial.print("  PF=");
    Serial.println(EmonTx[i].powerFactor);
  }
}
