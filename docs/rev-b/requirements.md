# Rev. B — System Requirements

## Project

**Protected Bidirectional DC Motor Controller**

This document defines the functional, electrical, protection, control,
hardware, testing, and documentation requirements for Rev. B.

Rev. B is a hardware-focused redesign derived from the original
automatic-door controller developed in Rev. A.

The primary objective is no longer the automatic-door application.
The motor controller itself is the engineering product.

Requirements that depend on motor electrical characteristics will remain
TBD until motor characterization is completed.

---

# 1. Functional Requirements

### FR-01 — Bidirectional Motor Control

The controller shall drive a brushed DC motor in both directions.

The system shall support:

- Clockwise rotation
- Counterclockwise rotation
- Motor stop

---

### FR-02 — PWM Speed Control

The controller shall provide PWM-based motor speed control.

The commanded motor speed shall be adjustable through the PWM duty cycle.

The final PWM frequency will be determined during the motor-control and
power-stage design phases.

---

### FR-03 — Motor Stop

The controller shall provide a commanded motor-off state in which the
H-bridge does not intentionally apply drive voltage to the motor.

---

### FR-04 — Safe Direction Reversal

The controller shall prevent immediate unsafe reversal of the H-bridge.

A safe transition shall occur between opposite motor directions to reduce
the risk of:

- Shoot-through
- Excessive current
- MOSFET stress
- Power-supply stress

---

### FR-05 — Current Monitoring

The controller shall measure motor current during operation.

Motor-current information shall be available to the microcontroller for:

- Monitoring
- Fault detection
- Experimental characterization
- Diagnostic telemetry

---

### FR-06 — Overcurrent Detection

The controller shall detect when motor current exceeds a defined
overcurrent threshold.

The final threshold shall be established after measuring:

- Normal operating current
- Startup current
- Stall current

---

### FR-07 — Overcurrent Shutdown

When a critical overcurrent condition is detected, the controller shall
disable the motor power stage.

The system shall enter a fault condition rather than continuing normal
motor operation.

---

### FR-08 — Fault Indication

The controller shall provide an indication when a critical fault has
occurred.

The indication may be provided through:

- Status LED
- Serial telemetry
- Firmware fault flag

The final implementation may use one or more of these methods.

---

### FR-09 — Fault Recovery

The controller shall prevent normal motor operation while a critical fault
condition remains active.

The method used to clear or reset a fault will be defined during firmware
development.

---

# 2. Electrical Requirements

### ER-01 — Motor Type

The controller shall initially support a brushed DC motor.

The original Rev. A 9 V brushed DC motor will be used as the first
development Device Under Test (DUT).

---

### ER-02 — Motor Supply

The motor power stage shall operate from an external DC supply.

Initial motor characterization shall be performed using a regulated
laboratory supply at the motor nominal voltage.

The final allowable DC input-voltage range is TBD.

---

### ER-03 — Logic Supply

The system shall provide a regulated logic supply for the microcontroller
and low-voltage circuitry.

The preliminary logic rail is:

**5 V**

---

### ER-04 — Power and Logic Ground

The motor-control circuitry and control electronics shall use an
appropriately defined common electrical reference where required by the
final architecture.

High-current motor return paths shall be routed to minimize interference
with sensitive control and sensing circuitry.

---

### ER-05 — Motor Current Capability

The H-bridge shall safely support:

- Normal motor current
- Startup current
- Short-duration transient current

The required continuous and peak current ratings are TBD pending motor
characterization.

---

### ER-06 — Voltage Margin

The selected power-stage devices shall have voltage ratings greater than
the maximum expected operating and transient voltages.

The required voltage margin will be established during component selection.

---

# 3. H-Bridge Requirements

### HB-01 — MOSFET Power Stage

Rev. B shall replace the BJT-based power stage used in Rev. A with a
MOSFET-based H-bridge.

The current preliminary architecture is:

- Two P-channel MOSFETs on the high side
- Two logic-level N-channel MOSFETs on the low side

Final MOSFET selection shall occur after motor characterization.

---

### HB-02 — Shoot-Through Prevention

The H-bridge shall include a method to prevent simultaneous conduction of
devices that would create a direct path between the motor supply and
ground.

This shall include appropriate switching logic and dead-time.

---

### HB-03 — Defined Gate States

Each MOSFET gate shall have a defined state when the microcontroller is:

- Resetting
- Unpowered
- Starting
- Not actively driving the motor

The motor shall not start unintentionally during MCU startup or reset.

---

### HB-04 — Gate Control

The MOSFET gate-drive network shall include appropriate gate resistance
and pull-up or pull-down resistance as required by the final topology.

Final resistance values are TBD pending MOSFET selection and switching
analysis.

---

### HB-05 — Motor Stop State

The H-bridge shall support a safe motor stop condition.

A dynamic braking mode may be implemented if justified during development,
but it is not required for the initial prototype.

---

# 4. Current-Sensing Requirements

### CS-01 — Current Measurement

Motor current shall be measured using an external current-sensing circuit.

The preliminary architecture uses:

- External shunt resistor
- Current-sense amplifier

The INA180 is the current preliminary amplifier selection.

---

### CS-02 — Current Measurement Range

The current-sensing circuit shall measure the expected normal and abnormal
motor-current range without exceeding the allowed input or output range of
the sensing circuitry or MCU ADC.

The final measurement range is TBD pending motor characterization.

---

### CS-03 — Shunt Selection

The current-shunt resistance shall be selected after the following motor
parameters are experimentally measured:

- No-load current
- Normal operating current
- Startup current
- Stall current

The shunt shall provide sufficient measurement resolution while minimizing
unnecessary voltage drop and power dissipation.

---

### CS-04 — Current-Sensor Output

The current-sense output shall be compatible with the microcontroller ADC
input range.

---

### CS-05 — Current-Sensor Validation

The current-sensing circuit shall be experimentally validated against an
independent current measurement.

---

# 5. Protection Requirements

### PR-01 — Input Overcurrent Protection

The system shall include input-current protection.

The preliminary implementation may use:

- Fuse
- Resettable PTC

The final device and rating shall be selected after motor characterization.

---

### PR-02 — Reverse-Polarity Protection

The controller shall include protection against accidental reverse
connection of the DC input supply.

The protection method shall minimize unnecessary voltage loss during
normal operation.

---

### PR-03 — Transient Protection

The design shall include a method to limit potentially damaging voltage
transients generated by the motor and switching power stage.

The final implementation may include:

- TVS device
- Suppression components
- Appropriate decoupling
- Motor-noise suppression

Final components shall be selected during schematic development.

---

### PR-04 — Overcurrent Protection

The controller shall disable the motor power stage when motor current
exceeds the defined critical current threshold.

The threshold is TBD pending motor characterization.

---

### PR-05 — Safe Fault State

A critical electrical fault shall result in the motor power stage being
placed in a safe OFF condition.

---

# 6. Power-Supply Requirements

### PS-01 — External Motor Supply

The rectangular 9 V alkaline battery used in Rev. A shall not be used as
the primary Rev. B motor power source.

Initial development shall use a regulated laboratory DC supply.

---

### PS-02 — Logic Regulation

The system shall derive a stable logic supply from the available system
power architecture.

The preliminary logic voltage is 5 V.

The final voltage-regulator topology and component selection are TBD.

---

### PS-03 — Decoupling

The design shall include local high-frequency decoupling for active
electronic devices.

---

### PS-04 — Bulk Capacitance

The motor power stage shall include appropriate bulk capacitance to reduce
supply disturbances caused by transient motor current.

The final capacitance value shall be determined during power-stage design
and validation.

---

### PS-05 — Supply Stability

Motor startup and normal operation shall not cause the logic supply to
drop below the reliable operating range of the microcontroller and sensing
electronics.

---

# 7. Control Requirements

### CR-01 — Microcontroller

The preliminary Rev. B controller shall use an:

**Arduino Nano / ATmega328P**

The controller is intentionally kept simple so that the primary focus of
the project remains electrical hardware and power-stage design.

---

### CR-02 — Operating States

The firmware shall support at minimum the following operating states:

- `IDLE`
- `RUN_CW`
- `RUN_CCW`
- `FAULT_OVERCURRENT`

Additional states may be added if supported by engineering requirements.

---

### CR-03 — Default State

Following startup or reset, the controller shall default to a motor-off
state.

---

### CR-04 — PWM Generation

The microcontroller shall generate the control signals required for PWM
motor operation.

---

### CR-05 — Dead-Time

The control strategy shall provide sufficient dead-time during switching
transitions to prevent unsafe simultaneous H-bridge conduction.

The final dead-time value is TBD pending MOSFET and switching
characterization.

---

### CR-06 — Fault Priority

A critical fault condition shall override normal motor commands.

---

### CR-07 — Diagnostic Telemetry

During development, the controller should provide diagnostic information
through the serial interface.

Useful parameters may include:

- Operating state
- PWM duty cycle
- Motor direction
- Motor current
- Bus voltage
- Active fault condition

---

# 8. Voltage-Monitoring Requirements

### VM-01 — Bus Voltage Monitoring

The design should provide a method for the microcontroller to measure the
main DC bus voltage.

A resistive divider connected to an MCU ADC input is the preliminary
implementation.

---

### VM-02 — ADC Compatibility

The voltage-monitoring circuit shall prevent the MCU ADC input from
exceeding its allowable voltage range under normal operating conditions.

---

### VM-03 — Startup Voltage Measurement

The system shall support measurement of motor-supply behavior during motor
startup.

---

### VM-04 — Undervoltage Protection

Firmware-based undervoltage protection may be implemented if experimental
testing demonstrates that it provides useful protection.

The undervoltage threshold is currently TBD and is not an initial mandatory
requirement.

---

# 9. Hardware Requirements

### HR-01 — Prototype Before PCB

The H-bridge and supporting circuitry shall be prototyped and electrically
validated before final PCB layout.

---

### HR-02 — Custom PCB

The final Rev. B controller shall be implemented on a custom PCB after the
major electrical design decisions have been validated.

---

### HR-03 — Test Points

The final PCB shall provide accessible test points for critical electrical
signals.

Preliminary test points include:

- VBUS
- +5 V logic rail
- GND
- Current-sense output
- Motor terminal A
- Motor terminal B
- High-side gate-control signals
- Low-side gate-control signals

---

### HR-04 — Power Routing

PCB traces and copper areas carrying motor current shall be sized according
to the measured motor-current requirements.

---

### HR-05 — Signal Separation

Sensitive analog and logic signals shall be routed to minimize interference
from high-current and switching nodes.

---

### HR-06 — Connectors

Power and motor connections shall use connectors appropriate for the final
voltage and current requirements.

Final connector ratings are TBD.

---

# 10. Motor Characterization Requirements

Before final H-bridge component selection, the development motor shall be
experimentally characterized.

The following parameters shall be measured:

### MC-01

Motor test voltage

\[
V_M
\]

### MC-02

No-load motor current

\[
I_{NL}
\]

### MC-03

Normal operating current

\[
I_{OP}
\]

### MC-04

Startup peak current

\[
I_{START}
\]

### MC-05

Stall current

\[
I_{STALL}
\]

### MC-06

Minimum motor-supply voltage during startup

\[
V_{START,MIN}
\]

These measurements shall become design inputs for the Rev. B power stage.

---

# 11. Verification and Testing Requirements

### TR-01 — Laboratory Validation

The completed design shall be experimentally validated using appropriate
laboratory instrumentation.

Expected instrumentation includes:

- Bench DC power supply
- Digital multimeter
- Oscilloscope

---

### TR-02 — Gate-Waveform Verification

MOSFET gate-drive signals shall be measured with an oscilloscope.

Testing shall verify:

- Correct gate voltage
- Correct switching sequence
- Dead-time
- Absence of unintended simultaneous conduction

---

### TR-03 — PWM Verification

The motor-control PWM signal shall be experimentally verified.

Measurements shall include:

- PWM frequency
- Duty cycle
- Switching behavior

---

### TR-04 — Motor-Current Verification

Motor current shall be measured under:

- No-load operation
- Normal operation
- Startup
- Controlled stall or overload testing

---

### TR-05 — Current-Sensor Accuracy

The current-sensing circuit shall be compared against an independent
reference measurement.

Measurement error shall be documented.

---

### TR-06 — Overcurrent Trip Test

The overcurrent-protection system shall be intentionally tested under a
controlled abnormal-current condition.

The test shall verify:

- Fault detection
- H-bridge shutdown
- Fault-state entry

---

### TR-07 — Protection Response Time

The time between the overcurrent event and power-stage shutdown shall be
measured where practical.

The measured protection response time shall be documented.

---

### TR-08 — Supply Validation

The following supply voltages shall be verified during operation:

- Motor DC bus
- Logic rail
- Current-sensing circuitry supply

---

### TR-09 — Thermal Observation

Power-stage temperature behavior shall be observed during representative
motor operation.

Any significant heating shall be documented and investigated.

---

# 12. Documentation Requirements

### DR-01 — Design Decisions

Major component and architecture decisions shall be documented with their
engineering rationale.

---

### DR-02 — Calculations

Relevant electrical calculations shall be documented, including:

- MOSFET conduction losses
- MOSFET power dissipation
- Shunt-resistor dissipation
- Current-sense gain
- Overcurrent threshold
- Power-supply requirements

---

### DR-03 — Datasheets

Datasheets for major Rev. B components shall be referenced during component
selection.

---

### DR-04 — Test Results

Experimental test results shall be preserved in the repository.

This may include:

- Measurement tables
- CSV data
- Oscilloscope captures
- Photographs
- Test notes

---

### DR-05 — Troubleshooting

Significant hardware failures or unexpected behavior shall be documented.

Documentation should include when applicable:

- Observed symptom
- Initial hypothesis
- Measurements performed
- Root cause
- Corrective action
- Verification after correction

---

### DR-06 — Revision History

Major Rev. B design changes shall be documented to preserve the evolution
of the project.

---

# 13. Out of Scope

The following functions from the original automatic-door application are
not required for Rev. B:

- HC-SR04 proximity detection
- Automatic-door mechanism
- Door-open limit switch
- Door-closed limit switch
- Time-based door-position estimation
- `CLOSED`
- `OPENING`
- `OPENED`
- `CLOSING`

These elements remain part of the Rev. A project history but are not part
of the primary Rev. B motor-controller requirements.

---

# 14. Requirements Pending Motor Characterization

The following design parameters shall remain TBD until experimental motor
characterization is completed:

- Maximum normal motor current
- Startup peak current
- Stall current
- Required continuous H-bridge current rating
- Required peak H-bridge current capability
- Final MOSFET selection
- Final shunt resistance
- Current-sense amplifier gain
- Overcurrent trip threshold
- Fuse / PTC rating
- Bulk capacitance
- Final input-voltage range
- Final power-supply current requirement
- Final connector current rating

These values shall be updated using measured data rather than estimated
motor specifications.
