# Rev. B — Motor Characterization

## Project

**Protected Bidirectional DC Motor Controller**

This document records the electrical characterization of the brushed DC motor
used as the initial Device Under Test (DUT) for Rev. B.

The purpose of this characterization is to obtain measured electrical data
before selecting the final MOSFETs, current-sense shunt, protection threshold,
power supply, and related power-stage components.

The motor used for initial development is the 9 V brushed DC motor originally
used in Rev. A.

---

# 1. Purpose

Motor electrical characteristics directly affect the design of the H-bridge.

In particular, the following quantities are required before the Rev. B power
stage can be finalized:

- No-load current
- Normal operating current
- Startup current
- Stall current
- Supply-voltage behavior during startup

These measurements will be treated as design inputs for the Rev. B motor
controller.

---

# 2. Device Under Test

## Motor

**Type:** Brushed DC motor

**Nominal Voltage:** 9 V

**Source:** Rev. A automatic-door prototype

**Manufacturer:** Unknown / TBD

**Part Number:** Unknown / TBD

The motor will initially be characterized independently from the Rev. A
BJT H-bridge.

This prevents the voltage drops and other limitations of the original power
stage from affecting the characterization results.

---

# 3. Test Equipment

The following equipment will be used during characterization.

| Equipment | Model | Purpose |
|---|---|---|
| Bench DC Power Supply | TBD | Motor power |
| Digital Multimeter | TBD | Voltage/current verification |
| Oscilloscope | TBD | Startup and transient measurements |
| Current Measurement Shunt | TBD | Dynamic current measurement |
| Test Leads | TBD | Electrical connections |

Equipment model numbers will be added before final test documentation.

---

# 4. General Test Conditions

Unless otherwise specified, characterization will initially be performed at:

\[
V_{TEST} = 9.0~V
\]

The motor shall initially be powered directly from the laboratory supply.

The Rev. A BJT H-bridge shall not be used during baseline motor
characterization.

Motor temperature shall be allowed to return close to ambient between tests
that produce significant heating.

---

# 5. Parameters to Measure

The following quantities will be characterized:

| Parameter | Symbol | Status |
|---|---|---|
| Motor test voltage | \(V_M\) | Pending |
| No-load current | \(I_{NL}\) | Pending |
| Normal operating current | \(I_{OP}\) | Pending |
| Startup peak current | \(I_{START}\) | Pending |
| Stall current | \(I_{STALL}\) | Pending |
| Supply voltage before startup | \(V_{IDLE}\) | Pending |
| Minimum startup supply voltage | \(V_{START,MIN}\) | Pending |

---

# 6. Test MC-01 — No-Load Current

## Objective

Measure the steady-state current drawn by the motor while rotating without
external mechanical load.

---

## Test Setup

```text
Bench Supply (+)
      |
      |
    DC Motor
      |
      |
Bench Supply (-)
