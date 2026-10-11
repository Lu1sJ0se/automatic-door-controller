# Rev. B — System Block Diagram

## Project

**Protected Bidirectional DC Motor Controller**

Rev. B redesigns the original automatic-door motor driver into a reusable
bidirectional brushed DC motor-control platform.

The primary engineering focus is the design of the power stage, current
measurement, protection circuitry, power regulation, fault handling, and
hardware validation.

---

## 1. System Architecture

```text
                     DC INPUT
                        |
                        v
              +--------------------+
              | Input Protection   |
              |                    |
              | - Fuse / PTC       |
              | - Reverse Polarity |
              | - TVS / Transient  |
              |   Protection       |
              +---------+----------+
                        |
                        +-----------------------------+
                        |                             |
                        v                             v
              +--------------------+        +--------------------+
              | MOSFET H-Bridge    |        | Voltage Regulator  |
              |                    |        |                    |
              | High-Side MOSFETs  |        | Motor Bus -> 5 V   |
              | Low-Side MOSFETs   |        | Logic Rail         |
              +---------+----------+        +---------+----------+
                        |                             |
                        v                             v
                  +-----------+                  +---------+
                  | DC Motor  |                  |   MCU   |
                  +-----+-----+                  +----+----+
                        |                             |
                        v                             |
              +--------------------+                 |
              | Current Sensing    |-----------------+
              |                    |
              | INA180             |
              | External Shunt     |
              +--------------------+
