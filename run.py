# --------------------------------------------------------------------
# Author:           Tom Appleford
# Email:            t.j.appleford@gmail.com
# Group:            FluidLab, Universiteit van Amsterdam
# Last updated:     7-Feb-2022
# --------------------------------------------------------------------


import os
import numpy as np

#---------------------------------------------------------------------
# STATE THE PARAMETERS
#---------------------------------------------------------------------
MAXLEVEL    = np.array([8])
BI          = np.array([0.2])
RE          = np.array([0.1])
CA          = np.array([0.5])
tmax        = 5.0

#---------------------------------------------------------------------
# RUN SHELL SCRIPT FOR EACH SET OF PARAMETERS
#---------------------------------------------------------------------
for MaxLevel in MAXLEVEL:
    for Bi in BI:
        for Re in RE:
            for Ca in CA:
                command = "sh run.sh %i %.4f %.4f %.4f %f" %(MaxLevel, Bi, Re, Ca, tmax)
                os.system(command)
                #deformation_cmd = "python3 logGeometry.py %i %.4f %.4f %.4f 5 %f 5" %(MaxLevel, Bi, Re, Ca, tmax)
                #os.system("cd PythonCode && %s" %deformation_cmd)
