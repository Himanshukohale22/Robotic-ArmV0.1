import pandas as pd

INPUT = "datafiles/Angles.txt"
OUTPUT = "angles.h"

# Read file (space/tab separated)
df = pd.read_csv(INPUT, delim_whitespace=True)

# Only keep theta_0..theta_3
angles = df[["theta_0", "theta_1", "theta_2", "theta_3"]].values

with open(OUTPUT, "w") as f:
    f.write("#pragma once\n\n")
    f.write(f"#define NUM_POSES {len(angles)}\n")
    f.write(f"#define ANGLE_COUNT 4\n\n")
    f.write("// theta_0, theta_1, theta_2, theta_3\n")
    f.write("const float angle_data[NUM_POSES][ANGLE_COUNT] = {\n")

    for row in angles:
        row_str = ", ".join(f"{x:.6f}" for x in row)
        f.write(f"    {{{row_str}}},\n")

    f.write("};\n")

print(f"Generated {OUTPUT}")
