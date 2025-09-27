# ///float 

# import pandas as pd

# INPUT = "datafiles/Angles.txt"
# OUTPUT = "angles.h"

# df = pd.read_csv(INPUT, delim_whitespace=True)
# angles = {
#     "theta_0": df["theta_0"].values,
#     "theta_1": df["theta_1"].values,
#     "theta_2": df["theta_2"].values,
#     "theta_3": df["theta_3"].values,
# }

# with open(OUTPUT, "w") as f:
#     f.write("#pragma once\n\n")
#     f.write(f"#define NUM_POSES {len(df)}\n\n")

#     for key, vals in angles.items():
#         f.write(f"const float {key}_buf[NUM_POSES] = {{\n")
#         f.write(", ".join(f"{v:int}" for v in vals))
#         f.write("\n};\n\n")

# print(f"Generated {OUTPUT}")


# int 

import pandas as pd

INPUT = "datafiles/Angles_degrees.txt"
OUTPUT = "angles.h"

df = pd.read_csv(INPUT, delim_whitespace=True)
angles = {
    "theta_0": df["theta_0"].values,
    "theta_1": df["theta_1"].values,
    "theta_2": df["theta_2"].values,
    "theta_3": df["theta_3"].values,
}

with open(OUTPUT, "w") as f:
    f.write("#pragma once\n\n")
    f.write(f"#define NUM_POSES {len(df)}\n\n")

    for key, vals in angles.items():
        f.write(f"const uint8_t {key}_buf[NUM_POSES] = {{\n")
        # f.write(", ".join(str(int(v)) for v in vals))   #for integer 
        f.write(", ".join(f"{int(v)}" for v in vals))  # for float
        f.write("\n};\n\n")

print(f"Generated {OUTPUT}")
