# --------------------------------------------------------------------
# IMPORT PACKAGES
# --------------------------------------------------------------------
import numpy as np
import os
import sys
import subprocess as sp


# --------------------------------------------------------------------
# GET THE RELEVANT SIMULATION PARAMETERS FOR GETTING DATA
# --------------------------------------------------------------------

MAXLEVEL    = int(sys.argv[1])
BI          = float(sys.argv[2])
RE          = float(sys.argv[3])
CA          = float(sys.argv[4])


inputfolder = "MaxLevel=%i_Bi=%.4f_Re=%.4f_Ca=%.4f" %(MAXLEVEL, BI, RE, CA)
inputpath = "../Output/%s/post" %inputfolder

# --------------------------------------------------------------------
# CREATE THE FOLDER FOR THE OUTPUT
# --------------------------------------------------------------------
outputfolder = "%s/videos" %inputpath
if not os.path.isdir(outputfolder):
    os.makedirs(outputfolder)
else:
    print("The folder \"%s\" already exists!" % outputfolder)


# --------------------------------------------------------------------
# LIST THE VIDEO NAMES
# --------------------------------------------------------------------
names = ["D2", "velocity"]

# --------------------------------------------------------------------
# COLLECT THE DATA FROM EACH FILE
# --------------------------------------------------------------------
for name in names:
    inputfolder = "%s/%s" %(inputpath, name)
    inputfiles = "%s/%s-*.png" %(inputfolder, name)
    outputfile = "%s/%s.mp4" %(outputfolder, name) 
    if not os.path.isdir(inputfolder):
        print("Error!   The folder \"%s\" could not be found!" %inputfolder)
    else:
        print("Success! The folder \"%s\" was found!" %inputfolder)
        command = "ffmpeg  -framerate 25 -pattern_type glob -i '%s' -vf scale=852:880 -c:v libx264 -r 30 -pix_fmt yuv420p %s" %(inputfiles, outputfile)
        os.system(command)                