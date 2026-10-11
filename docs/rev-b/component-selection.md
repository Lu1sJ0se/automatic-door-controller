# Rev. B — Component Selection

## Project

**Protected Bidirectional DC Motor Controller**

This document records the preliminary component and architecture selections
for Rev. B.

Component selections are divided into three categories:

- **Selected** — decision currently accepted for Rev. B.
- **Preliminary** — preferred solution, pending detailed electrical design.
- **TBD** — cannot be finalized until additional measurements or calculations
  are completed.

Final power-stage components shall not be selected until motor
characterization is complete.

---

# 1. Microcontroller

## Selection

**Arduino Nano / ATmega328P**

**Status:** Selected

---

## Rationale

The Arduino Nano / ATmega328P architecture is retained because Rev. B is
primarily focused on electrical hardware development rather than advanced
embedded processing.

The microcontroller provides sufficient resources for:

- PWM generation
- Direction control
- H-bridge enable / disable
- Current measurement through the ADC
- Bus-voltage measurement
- Fault detection
- Serial telemetry
- Basic state-machine implementation

Using a familiar microcontroller also reduces firmware-development overhead
and allows the project to focus on:

- Power electronics
- Current sensing
- Protection
- PCB design
- Hardware validation

---

# 2. Development Motor

## Selection

**Existing Rev. A 9 V brushed DC motor**

**Status:** Selected as initial DUT

---

## Purpose

The original motor will be used as the first Device Under Test (DUT) for
development and validation of the Rev. B motor controller.

The controller is not intended to remain permanently tied to this specific
motor.

The motor will first be characterized experimentally.

Required measurements include:

- No-load current
- Normal operating current
- Startup current
- Stall current
- Supply voltage during startup

The measured values will establish the electrical requirements of the power
stage.

---

# 3. H-Bridge Architecture

## Preliminary Selection

Discrete MOSFET H-bridge

**Status:** Selected architecture

The preliminary topology consists of:

- 2 P-channel MOSFETs for the high side
- 2 logic-level N-channel MOSFETs for the low side

```text
               VBUS
                |
         +------+------+
         |             |
       Q1 P-MOS      Q2 P-MOS
         |             |
         +---- MOTOR ---+
         |             |
       Q3 N-MOS      Q4 N-MOS
         |             |
         +------+------+
                |
               GND
