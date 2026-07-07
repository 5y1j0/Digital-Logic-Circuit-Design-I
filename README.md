# Digital Logic Circuit Design I

Coursework projects for Digital Logic Circuit Design I, Kwangwoon University (2025)

## 1. Ripple-Carry Adder (Verilog)

Designed a 1-bit full adder and scaled it into 16-bit and 40-bit
Ripple-Carry Adders, each verified with a testbench. Then built two
80-bit adders by cascading:
- **5 × 16-bit** modules (`rca16_80.v`)
- **2 × 40-bit** modules (`rca40_80.v`)

Compared the performance of the two 80-bit implementations.

**Files:** `full_adder.v`, `rca16.v`, `rca40.v`, `rca16_80.v`, `rca40_80.v`,
`tb_rca16_80.v`, `tb_rca40_80.v`

**Tools:** Quartus Prime (synthesis), ModelSim (simulation)

## 2. Quine–McCluskey Logic Minimization (C++)

Implemented the Quine–McCluskey algorithm from scratch to minimize
Boolean functions from minterms and don't-care terms:
- Groups terms by number of 1s and combines adjacent groups differing
  by one variable
- Extracts prime implicants and selects essential prime implicants
- Outputs the minimum-cost SOP expression with transistor count
  (AND/OR: 2n+2, NOT: 2n transistors)

**Files:** `qm.cpp`, `input_minterm.txt` (example input),
`result.txt` (example output)
