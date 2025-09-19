import numpy as np
import pandas as pd

INPUT = "datafiles/Angles.txt"
OUTPUT = "angles_bitmap.h"

df = pd.read_csv(INPUT, delim_whitespace=True)

# Only keep binary version (0 or 1)
theta_0 = np.clip(df["theta_0"].astype(int), 0, 1).tolist()
theta_1= np.clip(df["theta_1"].astype(int), 0, 1).tolist()
theta_2 = np.clip(df["theta_2"].astype(int), 0, 1).tolist()
theta_3 = np.clip(df["theta_3"].astype(int), 0, 1).tolist()


def pack_bits(values):
    """Pack list of 0/1 into bytes"""
    out = []
    for i in range(0, len(values), 8):
        byte = 0
        for j, v in enumerate(values[i:i+8]):
            byte |= (v & 1) << j
        out.append(byte)
    return out

theta_0_bytes = pack_bits(theta_0)
theta_1_bytes = pack_bits(theta_1)
theta_2_bytes = pack_bits(theta_2)
theta_3_bytes = pack_bits(theta_3)

with open(OUTPUT, "w") as f:
    f.write("#pragma once\n\n")
    f.write(f"#define NUM_POSES {len(theta_0)}\n")
    f.write(f"#define NUM_BYTES {(len(theta_0)+7)//8}\n\n")

    f.write("const uint8_t theta_0_bitmap[NUM_BYTES] = {\n")
    f.write(", ".join(f"0x{b:02X}" for b in theta_0_bytes))
    f.write("\n};\n")
    f.write("const uint8_t theta_1_bitmap[NUM_BYTES] = {\n")
    f.write(", ".join(f"0x{b:02X}" for b in theta_1_bytes))
    f.write("\n};\n")
    f.write("const uint8_t theta_2_bitmap[NUM_BYTES] = {\n")
    f.write(", ".join(f"0x{b:02X}" for b in theta_2_bytes))
    f.write("\n};\n")
    f.write("const uint8_t theta_3_bitmap[NUM_BYTES] = {\n")
    f.write(", ".join(f"0x{b:02X}" for b in theta_3_bytes))
    f.write("\n};\n")
