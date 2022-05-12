# --------------------------------------------------------------------
# Author:           Tom Appleford
# Email:            t.j.appleford@gmail.com
# Group:            FluidLab, Universiteit van Amsterdam
# Last updated:     6-Apr-2022
# --------------------------------------------------------------------

# --------------------------------------------------------------------
# This code runs the C code "getDeformation" for each snapshot, 
# obtaining the coordinates of the centre of the drop, the minimum 
# and maximum radii, and the Taylor deformation, before storing them
# as a CSV file. You need to feed this code all simulation parameters
# Needs to be moved, with getDeformation, into working directory.
# --------------------------------------------------------------------

# --------------------------------------------------------------------
# IMPORT PACKAGES
# --------------------------------------------------------------------
import pandas as pd
import os
import sys
import numpy as np
import matplotlib.pyplot as plt


# --------------------------------------------------------------------
# DEFINE FUNCTION FOR GETTING DEFORMATIONS
# --------------------------------------------------------------------
def gettingDeformations(filename, Ldomain):
    ''' 
    This function computes the geometry of the drop.

    Arguments: 
     - filename: the directory of binary file for a snapshot
     - Ldomain: the length of the domain.
    '''
    import numpy as np
    import subprocess as sp
    post_process_folder = "../PostModules/getDeformation"
    exe = [post_process_folder, filename, str(Ldomain)]
    p = sp.Popen(exe, stdout=sp.PIPE, stderr=sp.PIPE)
    stdout, stderr = p.communicate()
    temp1 = stderr.decode("utf-8")
    temp2 = temp1.split("\n")
    temp3 = temp2[0].split(" ")

    xcm     = float(temp3[0])
    ycm     = float(temp3[1])
    rminC   = float(temp3[2])
    rmaxC   = float(temp3[3])
    deformC = float(temp3[4])
    xmin    = float(temp3[5])
    ymin    = float(temp3[6])
    rmin    = float(temp3[7])
    xmax    = float(temp3[8])
    ymax    = float(temp3[9])
    rmax    = float(temp3[10])
    deform  = float(temp3[11])
    theta  = float(temp3[12])
        
    return(xcm, ycm, rminC, rmaxC, deformC, xmin, ymin, rmin, xmax, ymax, rmax, deform, theta)


# --------------------------------------------------------------------
# STATE THE RELEVANT SIMULATION PARAMETERS
# --------------------------------------------------------------------
MaxLevel    = int(sys.argv[1])
Bi          = float(sys.argv[2])
Re          = float(sys.argv[3])
Ca          = float(sys.argv[4])
Hy          = float(sys.argv[5])
tmax        = float(sys.argv[6])
Ldomain     = float(sys.argv[7])


# --------------------------------------------------------------------
# FIND THE FOLDER WITH THE DATA
# --------------------------------------------------------------------
inputfolder = "MaxLevel=%i_Bi=%.4f_Re=%.4f_Ca=%.4f" %(MaxLevel, Bi, Re, Ca)
inputpath = "../Output/%s" %inputfolder

# --------------------------------------------------------------------
# CREATE THE FOLDER FOR THE OUTPUT
# --------------------------------------------------------------------
outputfolder = "%s/post/" %inputpath
if not os.path.isdir(outputfolder):
    os.makedirs(outputfolder)


# --------------------------------------------------------------------
# CHECK THERE IS NO FILE THERE ALREADY
# --------------------------------------------------------------------

outputfile = "%s/post/geometry.csv" %inputpath
#outputfile = "%s/geometry-%s.csv" %(outputfolder, inputfolder)
# --------------------------------------------------------------------
# CREATE A FILE FOR EACH SNAPSHOT
# --------------------------------------------------------------------
colnames = ["time", "x-com", "y-com", "r-min (circles method)", "r-max (circles method)", "Taylor Deformation (circles method)", "x-min", "y-min", "r-min", "x-max", "y-max", "r-max", "Taylor Deformation", "Angle"]
geometry = []
timetab = []
deform = []


tsnap = 0.05
nsnaps = int(tmax/tsnap)

for snap in range(nsnaps):
    time        = tsnap*snap
    snaptime    = "%5.2f" %time
    index       = "%5.4f" %time
    inputfile   = "%s/intermediate/snapshot-%s" % (inputpath,index)
            
    if not os.path.exists(inputfile):
        print("The input file \"%s\" could not be found!" % inputfile)
    else:
        print("The input file \"%s\" was found!" % inputfile)
        info = []
        info.append(snaptime)
        info.extend(gettingDeformations(inputfile, Ldomain))
        geometry.append(info)
        print("Geometry extracted from %s!" %inputfile) 

        timetab.append(snaptime)
        deform.append(info[13])
                
        # --------------------------------------------------------------------
        # SAVE THE FILE
        # --------------------------------------------------------------------
        geometry2 = pd.DataFrame(geometry, columns = colnames)
        geometry2.to_csv(outputfile, index = False)

fig, ax = plt.subplots()
plt.plot(timetab, deform)
plt.show()


        
