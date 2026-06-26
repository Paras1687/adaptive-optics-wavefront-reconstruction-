import numpy as np
import cv2
import os

# --- Configuration ---
num_frames = 100        # Total number of .bmp frames to generate
grid_size = 10          # 10x10 grid of lenslets
image_size = 512        # 512x512 pixel resolution
spacing = image_size // (grid_size + 1)
spot_radius = 4
output_dir = "dummy_sh_wfs_data"

# Create output directory if it doesn't exist
if not os.path.exists(output_dir):
    os.makedirs(output_dir)

print(f"Generating {num_frames} frames in the '{output_dir}' folder...")c

for frame_idx in range(num_frames):
    # 1. Create a blank black image array
    img = np.zeros((image_size, image_size), dtype=np.uint8)
    
    # 2. Draw a grid of white circles (representing the reference spots)
    for i in range(1, grid_size + 1):
        for j in range(1, grid_size + 1):
            # Base reference position
            ref_x = i * spacing
            ref_y = j * spacing
            
            # 3. Simulate atmospheric distortion
            # Frame 0 is kept perfect so you can use it as your Reference Frame calibration
            if frame_idx == 0:
                shift_x, shift_y = 0, 0
            else:
                # Randomly shift coordinates by -3 to +3 pixels
                shift_x = np.random.randint(-3, 4)
                shift_y = np.random.randint(-3, 4)
                
            center = (ref_x + shift_x, ref_y + shift_y)
            
            # Draw the bright spot
            cv2.circle(img, center, spot_radius, 255, -1)
            
    # 4. Add Gaussian noise to simulate science-camera grain
    noise = np.random.normal(0, 15, img.shape).astype(np.int16)
    img_noisy = np.clip(img.astype(np.int16) + noise, 0, 255).astype(np.uint8)
    
    # 5. Export frame as a .bmp file
    filename = os.path.join(output_dir, f"frame_{frame_idx:03d}.bmp")
    cv2.imwrite(filename, img_noisy)

print("Done! Your fake SH-WFS dataset is ready.")