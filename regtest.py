import numpy as np

a=np.array([1,2,3,4,5,6,7,8])
b=np.array([8,7,6,5,4,3,2,1])

# Save as binary file
a.tofile("array.bin")
b.tofile("array.bin")

