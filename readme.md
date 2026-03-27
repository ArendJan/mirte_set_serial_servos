# MIRTE arm servo calibration

Simple code to easily setup and zero the Hiwonder HTD/HX servos for the MIRTE master arm.

Open in VSCode with Pico plugin installed. Change the define in [./set_servos.cpp#8](./set_servos.cpp#L8) to the servo num you want to setup. 

- Shoulder rotation (pan, HX-12H): 2
- Shoulder lift (HTD-45H): 3
- Elbow (HTD-35H): 4
- Wrist (HX-12H): 5
- Gripper (HX-12H): 6

Compile and flash to a Raspberry Pi Pico. Connect the servo to 12V and Pico pin both GP0 & GP1 to the serial pin of the servo. 

Only connect a single servo as it uses the broadcast ID to set the ID of the servo, resulting in all the connected servos with the same ID and then broken communication.

Open a serial connection to the Pico from your computer.

It'll try to set the id, voltage, range and set the servo to the home position (arm pointing up, rotation forward with gripper output horizontal).

It'll print the current position, it'll never be perfectly on the wanted home position, but you can calibrate it with the `mirte_test` ROS package on the MIRTE master. Within a few degrees (value printed is centidegrees) is good enough, the servo horn will also not fit perfectly.
