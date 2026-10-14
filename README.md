# Homemade-LiDAR-Sensor

A homemade low cost 3D scanner I built from a time-of-flight sensor and two servos. It sweeps
the sensor across a scene, measuring distance at each angle, and builds a 3D pooint cloud of everything
in a 180 degree field of it.

## How it works

Two servos aim a single ToF sensor. One servo pans left and right, the other tilts up and down. The sensor
can point anywhere in a wide cone. At each position the sensor measures distance, and the Arduino sends the
pan angle, tilt angle, and distance over serial. A MATLAB program reads that stream and converts the two angles
with distance into x, y, z coordinates and plots a live 3D point cloud.

## Hardware

- Arduino Uno R4 WiFi
- VL53L4CX time-of-flight distance sensor (I2C)
- Two MG90 / SG90 micro servos on a pan-tilt bracket
- Separate 5V supply for the servos
- Breadboard and jumper wires

## Software

- Arduino sketch(C++) that sweeps both servos and reads the sensor at point of pan and tilt over serial
- MATLAB program that reads the serial data and converts the readings (two angles plus distance) into Cartesian x, y, z, and renders a live 3D point cloud

## Notes

- This maps in 3D from a single fixed spot, so it captures the surfaces facing the sensor, with shadows behind objects.
- A full 1-degree scan takes around 15 to 20 minutes. It is a work in progress.
