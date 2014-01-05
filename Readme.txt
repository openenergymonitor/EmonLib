                             _      _ _     
                            | |    (_) |    
   ___ _ __ ___   ___  _ __ | |     _| |__  
  / _ \ '_ ` _ \ / _ \| '_ \| |    | | '_ \ 
 |  __/ | | | | | (_) | | | | |____| | |_) |
  \___|_| |_| |_|\___/|_| |_|______|_|_.__/ 

Arduino Energy Monitoring Library - compatible with Arduino 1.0 
*****************************************************************

Designed for use with emonTx: http://openenergymonitor.org/emon/Modules

Download to Arduino IDE 'libraries' folder. Restart of IDE required.

Git Clone and Git Pull can be easily used to keep the library up-to-date and manage changes. 
JeeLabs has done a good post on the topic: http://jeelabs.org/2011/12/29/out-with-the-old-in-with-the-new/



Update: 5th January 2013: Support Added for Arduino Due (ARM Cortex-M3, 12-bit ADC) by icboredman.

To enable this feature on Arduino Due, add the following statement to setup() function in main sketch:
analogReadResolution(ADC_BITS); This will set ADC_BITS to 12 (Arduino Due), EmonLib will otherwise default to 10 analogReadResolution(ADC_BITS);. 



Arduino Due 3-phase Example by icboredman:

Includes 3-phase buffer-delay algorithm, when CT sensors connected to different line phases.
Support for 10 CT inputs (modifed emonTx hardware) and one AC-AC adapter. AC adapter must be connectred to phase 1

There are 10 CT inputs connected to various household lines (after circuit breakers) and 1 AC-AC voltage adapter connected to one of these lines, used to measure voltage.
10 lines are connected to different phases, therefore, an extra parameter was added to functions voltage() and voltageTX() indicating a particular phase number.
The AC-AC line voltage adapter must be connected to phase 1.
