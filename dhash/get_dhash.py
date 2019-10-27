from PIL import Image
import imagehash
import glob
import os
import sys

video_name = sys.argv[1]
output = open("video_Dhash.txt","w")

# first loop remove sequential image set 

filenames = [os.path.splitext(os.path.basename(x))[0] for x in glob.glob(video_name + '/*.jpg')]
filenames.sort(key=int, reverse=False)

difarr = []

prevhash = 0
preval = ''

for ind, val in enumerate(filenames):
    tmp_img = Image.open(video_name + '/' + val + '.jpg')
    hash1 = imagehash.dhash(tmp_img)
    if(ind == 0):
        #termination
        prevhash = hash1
        preval = val
        continue

    diff = hash1 - prevhash
    output.write(str(diff) + " ")
    prevhash = hash1
    preval = val
