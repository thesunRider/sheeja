![Alt text](assets/logo.png?raw=true "logo")
# Sensitive Heuristic Electrical Expenditure and Joule Analyser
An Ultra-sensitive AI based Power meter for Electrical Activity Analysis

The project aims to build a spyware device that is able to detect small variations in current through through a load through which it can analyse what the device is doing.Essentially a spyware hacking device which works on the analogue domain rather than the software level. The device will be connected as a spy device in the mains line where it will spy on all the attached electrical devices.

The device makes use of Kirchoffs third current law and exploits it. The exploitability of attached devices depends on bad practices in the electrical design of the hackable devices.


## Specs to be built:

1. Simulation and Development of PCB board
2. ADC with 100ksps with adjustable gain 
3. Bootstrapped Opamp 
4. Product detector with notch filter

Since its unsafe to play with AC mains without a proper PCB Board , Will make a DC Version of the device with same specs which works by tapping the low voltage dc cable going to the device rather than the tap at 240V

## Applications of this device are as follows:

1. Detect faults in any device by training for faulty and non faulty conditions.
2. Identify which all instruments connected to the AC Grid
3. Keylogging device connected.
4. Extract Audio played in the device remotely.

## Build

MCU Space: STM32F103RBT6 -> Bluepill

THIS IS A SPYWARE DEVICE BUILT FOR EDUCATIONAL PURPOSES. I DO NOT TAKE ANY RESPONSIBILITY FOR ITS MISUSE, WARNING! : THE DEVICE INTERACTS WITH NON ISOLATED HIGH VOLTAGE AC AND CAN CAUSE FATAL INJURY SO USE/BUILD AT YOUR OWN RISK.