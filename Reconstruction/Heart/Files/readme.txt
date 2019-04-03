Given a stereo frame pair N, where N is the frame number in the video sequence (starting from 0), the corresponding depth map to be used can be calculated according to the formulae below:

round(mod((FrameNo/25 + 0.466667)*30,20)), for the sequence

Entries in the depth map are stored as (x,y,z) triplets, with each entry corresponding to a pixel in the left frame. Ground truth depth files contain one (x,y,z) triplet per line, stored in row major format. Each file contains 288*360 entries. If an entry is stored as (0,0,0), no ground truth is available.
