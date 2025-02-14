import numpy as np
import mmap
import os

size = 4 * 100  # 100 float values (4 bytes each)
shm_file = "shared_mem.bin"

# Create a NumPy array and write to shared memory
arr = np.arange(-5,5,0.2, dtype=np.float32)
with open(shm_file, "wb") as f:
    f.write(arr.tobytes())  # Store in binary format
