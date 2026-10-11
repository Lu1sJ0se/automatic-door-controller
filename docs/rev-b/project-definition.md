# Rev. B — Project Definition

## Project Title

Protected Bidirectional DC Motor Controller

### Subtitle

MOSFET H-Bridge with Current Sensing, PWM Control, and Fault Protection

---

## 1. Background

Rev. A of this project was originally developed as an automatic door
controller for an ELEN 330 academic design project.

The original system used:

- Arduino Uno
- HC-SR04 ultrasonic sensor
- 9 V DC motor
- Discrete BJT H-bridge
- PWM motor control
- Four-state finite state machine

The prototype successfully demonstrated bidirectional DC motor control,
but several electrical limitations were identified during development
and testing.

These included:

- Voltage drop across the BJT H-bridge
- Transistor heating
- Voltage sag from the 9 V battery
- Lack of motor current sensing
- Lack of overcurrent protection
- Limited electrical characterization
- Time-based motor positioning
- Limited design-for-test capability

Rev. B uses these limitations as the starting point for a hardware-focused
redesign.

---

## 2. Rev. B Mission

The objective of Rev. B is to design, build, and experimentally validate
a reusable bidirectional DC motor controller centered around a discrete
MOSFET H-bridge.

Unlike Rev. A, the primary objective is no longer the automatic-door
application.

The motor controller itself becomes the engineering product.

The design will provide controlled bidirectional motor operation,
PWM speed control, current monitoring, electrical protection, fault
handling, and hardware testability.

---

## 3. Engineering Problem

The discrete BJT motor driver used in Rev. A demonstrated basic
bidirectional control but introduced significant conduction losses,
thermal limitations, and limited fault protection.

A more robust motor-control platform is required that can:

- Efficiently drive a small brushed DC motor in both directions
- Control motor speed using PWM
- Measure motor current
- Detect abnormal current conditions
- Disable the power stage during electrical faults
- Protect the system from common power-input faults
- Provide stable power for control electronics
- Support laboratory characterization and validation

---

## 4. System Objectives

Rev. B will:

1. Replace the BJT H-bridge with a MOSFET-based H-bridge.

2. Provide bidirectional motor control.

3. Provide PWM-based motor speed control.

4. Measure motor current using a current-sense amplifier and shunt
   resistor.

5. Detect overcurrent and motor-stall conditions.

6. Disable the H-bridge when a critical fault is detected.

7. Incorporate input and motor-stage protection.

8. Provide regulated power for the microcontroller and low-voltage
   electronics.

9. Implement firmware-based operating and fault states.

10. Provide test points for laboratory measurements.

11. Be implemented on a custom PCB after prototype validation.

12. Be experimentally validated using laboratory instrumentation.

---

## 5. Preliminary System Architecture

    DC INPUT
       |
       v
+----------------------+
| Input Protection     |
|                      |
| Fuse / PTC           |
| Reverse Polarity     |
| Transient Protection |
+----------+-----------+
           |
           +--------------------------+
           |                          |
           v                          v
+----------------------+     +------------------+
| MOSFET H-Bridge      |     | Voltage          |
|                      |     | Regulation       |
| Q1              Q2   |     +--------+---------+
|        MOTOR         |              |
| Q3              Q4   |              v
+----------+-----------+          MCU / Logic
           |
           v
+----------------------+
| Current Sensing      |
| INA180 + Shunt       |
+----------+-----------+
           |
           v
          MCU

MCU outputs:

- Direction control
- PWM command
- Bridge enable

MCU inputs:

- Motor current
- Bus-voltage monitoring
- Fault signals

---

## 6. Operating Modes

The controller will initially support:

- IDLE
- RUN_CW
- RUN_CCW
- BRAKE / STOP
- FAULT_OVERCURRENT

Additional fault states may be added if justified by testing.

Possible future states include:

- FAULT_UNDERVOLTAGE
- FAULT_OVERTEMPERATURE

---

## 7. Preliminary Hardware Architecture

### Controller

Arduino Nano / ATmega328P

The controller is intentionally kept simple so that the primary focus of
the project remains electrical hardware and power-stage design.

### Power Stage

Preliminary architecture:

- 2 P-channel MOSFETs for the high side
- 2 logic-level N-channel MOSFETs for the low side
- Gate resistors
- Gate pull-up / pull-down resistors
- Dead-time between switching states

Final MOSFETs will not be selected until motor characterization is
completed.

### Current Measurement

Preliminary solution:

- INA180 current-sense amplifier
- External shunt resistor

The final shunt resistance and amplifier gain will be determined from
measured motor current.

### Power Supply

The original rectangular 9 V battery will not be used as the primary
Rev. B motor supply.

Initial development and motor characterization will use a regulated
laboratory supply at the motor's nominal 9 V operating voltage.

The final system will include a regulated low-voltage rail for the MCU
and signal electronics.

### Protection

The Rev. B design will investigate and implement:

- Fuse or resettable PTC
- Reverse-polarity protection
- Transient suppression
- Supply decoupling
- Motor-noise suppression
- Overcurrent protection
- Shoot-through prevention

---

## 8. Design for Test

The final PCB will include accessible test points for critical signals.

Preliminary test points include:

- VBUS
- +5 V logic rail
- GND
- Current-sense output
- Motor terminal A
- Motor terminal B
- MOSFET gate-drive signals

Additional test points may be added during schematic development.

---

## 9. Initial Device Under Test

The original 9 V DC motor from Rev. A will be used as the initial
development motor.

The motor is considered the first Device Under Test (DUT), rather than
being permanently tied to an automatic-door application.

Before the power stage is designed, the motor will be characterized to
determine:

- Nominal supply voltage
- No-load current
- Normal operating current
- Startup current
- Stall current
- Supply-voltage behavior during startup

These measurements will establish the electrical design requirements for
the H-bridge.

---

## 10. Validation Strategy

The completed controller will be validated experimentally.

Planned measurements include:

- Motor current
- Startup current
- Stall current
- MOSFET gate waveforms
- H-bridge switching-node waveforms
- PWM frequency and duty cycle
- MOSFET voltage drop
- Conduction losses
- Supply-voltage stability
- Current-sensor accuracy
- Overcurrent trip level
- Fault shutdown response time
- Regulated rail voltage

Testing will be performed using laboratory instrumentation such as:

- Digital multimeter
- Bench power supply
- Oscilloscope

---

## 11. Project Scope

### In Scope

- MOSFET H-bridge design
- Gate-drive design
- PWM motor control
- Bidirectional operation
- Current sensing
- Overcurrent detection
- Fault handling
- Input protection
- Power regulation
- Decoupling and filtering
- Motor transient suppression
- Schematic design
- Circuit simulation
- Breadboard / prototype validation
- Custom PCB design
- PCB bring-up
- Electrical validation
- Troubleshooting documentation
- Root-cause analysis

### Out of Scope

The following Rev. A functions are no longer primary Rev. B requirements:

- Automatic door mechanism
- HC-SR04 proximity detection
- Door opening / closing state machine
- Time-based door position estimation
- Cardboard mechanical structure

Rev. A will remain documented as the original application and motivation
for the redesign.

---

## 12. Development Plan

Rev. B will follow the engineering sequence below:

1. Motor characterization
2. Electrical requirement definition
3. MOSFET selection
4. H-bridge loss analysis
5. Current-sense design
6. Overcurrent threshold definition
7. Gate-drive and protection design
8. H-bridge simulation
9. Hardware prototyping
10. Prototype characterization
11. Schematic finalization
12. PCB layout
13. PCB assembly
14. Board bring-up
15. Validation testing
16. Fault testing
17. Design review and documentation

PCB design will not begin until the major electrical design decisions
have been experimentally justified.
