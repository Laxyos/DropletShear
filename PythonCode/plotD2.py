# --------------------------------------------------------------------
# Author:           Tom Appleford
# Email:            t.j.appleford@gmail.com
# Group:            FluidLab, Universiteit van Amsterdam
# Last updated:     6-Apr-2022
# 
# Most of the code was actually written by Vatsal Sanjay.
# --------------------------------------------------------------------

# --------------------------------------------------------------------
# This code takes snapshot files and plots their deformation fields
# This code takes the following arguments:
#  - Ldomain:   the width of the domain
#  - Hy:        the height of the domain (i.e. not coverd by solid)
# 
# New stuff: puts it all into one folder, better labelling
# --------------------------------------------------------------------


# --------------------------------------------------------------------
# IMPORT PACKAGES
# --------------------------------------------------------------------
import matplotlib.pyplot as plt
from matplotlib.collections import LineCollection
from matplotlib.ticker import StrMethodFormatter
import numpy as np
import os
import sys

# --------------------------------------------------------------------
# Font Styles
# --------------------------------------------------------------------


# --------------------------------------------------------------------
# GET THE RELEVANT SIMULATION PARAMETERS FOR GETTING DATA
# --------------------------------------------------------------------
MaxLevel    = int(sys.argv[1])
Bi          = float(sys.argv[2])
Re          = float(sys.argv[3])
Ca          = float(sys.argv[4])
Hy          = float(sys.argv[5])
tmax        = float(sys.argv[6])
Ldomain     = float(sys.argv[7])
home        = sys.argv[8]

# Width and height of the domain
Lx = Ldomain
Ly = Hy
# Width and height of the plot.
xmin, xmax, ymin, ymax = [-Lx/2, Lx/2, -Ly/2, Ly/2]

# Number of grid cells in the vertical direction
ny = 100

# --------------------------------------------------------------------
# DEFINE THE FUNCTION FOR GETTING FACETS
# --------------------------------------------------------------------
def gettingFacets(filename):
    ''' 
    This function finds points along the perimeter of the drop

    Arguments: 
     - filename: the directory of binary file for a snapshot
    '''
    # import the packages
    import numpy as np
    import os
    import subprocess as sp
    import matplotlib
    import matplotlib.pyplot as plt
    from matplotlib.collections import LineCollection
    from matplotlib.ticker import StrMethodFormatter
    import sys
    # 
    exe = ["../PostModules/getFacet", filename]
    p = sp.Popen(exe, stdout=sp.PIPE, stderr=sp.PIPE)
    stdout, stderr = p.communicate()
    temp1 = stderr.decode("utf-8")
    temp2 = temp1.split("\n")
    segs = []
    skip = False
    if (len(temp2) > 1e2):
        for n1 in range(len(temp2)):
            temp3 = temp2[n1].split(" ")
            if temp3 == ['']:
                skip = False
                pass
            else:
                if not skip:
                    temp4 = temp2[n1+1].split(" ")
                    r1, z1 = np.array([float(temp3[0]), float(temp3[1])])
                    r2, z2 = np.array([float(temp4[0]), float(temp4[1])])
                    segs.append(((r1, z1),(r2,z2)))
                    skip = True
    return segs

# --------------------------------------------------------------------
# DEFINE THE FUNCTION FOR GETTING FIELD
# --------------------------------------------------------------------
def gettingField(filename, xmin, ymin, xmax, ymax, Ly, ny):
    import subprocess as sp
    import numpy as np
    exe = ["../PostModules/getData", filename, str(xmin), str(ymin), str(xmax), str(ymax), str(Ly), str(ny)]
    p = sp.Popen(exe, stdout=sp.PIPE, stderr=sp.PIPE)
    stdout, stderr = p.communicate()
    temp1 = stderr.decode("utf-8")
    temp2 = temp1.split("\n")
    # print(temp2) #debugging
    Xtemp, Ytemp, D2temp, veltemp = [],[],[],[]
    for n1 in range(len(temp2)):
        temp3 = temp2[n1].split(" ")
        if temp3 == ['']:
            pass
        else:
            Xtemp.append(float(temp3[0]))
            Ytemp.append(float(temp3[1]))
            D2temp.append(float(temp3[2]))
            veltemp.append(float(temp3[3]))
    X = np.asarray(Xtemp)
    Y = np.asarray(Ytemp)
    D2 = np.asarray(D2temp)
    vel = np.asarray(veltemp)
    nx = int(len(X)/ny)
    print("nx is %d" % nx)
    X.resize((nx, ny))
    Y.resize((nx, ny))
    D2.resize((nx, ny))
    vel.resize((nx, ny))

    X = np.rot90(X)
    Y = np.rot90(Y)
    D2 = np.rot90(D2)
    vel = np.rot90(vel)

    X = np.flipud(X)
    Y = np.flipud(Y)
    D2 = np.flipud(D2)
    vel = np.flipud(vel)

    return X, Y, D2, vel, nx

# --------------------------------------------------------------------
# Find simulation input files
# --------------------------------------------------------------------
inputfolder = "MaxLevel=%i_Bi=%.4f_Re=%.4f_Ca=%.4f" %(MaxLevel, Bi, Re, Ca)
inputpath = "../Output/%s" %inputfolder
# --------------------------------------------------------------------
# CREATE THE FOLDER FOR THE OUTPUT
# --------------------------------------------------------------------

outputfolder = "%s/post/D2" %inputpath
if not os.path.isdir(outputfolder):
    os.makedirs(outputfolder)
else:
    print("The folder \"%s\" already exists!" % outputfolder)

# --------------------------------------------------------------------
# CREATE A FILE FOR EACH SNAPSHOT
# --------------------------------------------------------------------

# find the snapshots
tsnap = 0.05
nsnaps = int(tmax/tsnap)

for snap in range(nsnaps):
    time        = tsnap*snap
    snaptime    = "%5.2f" %time
    index       = "%5.4f" %time
    snapindex   = time*1000
    inputfile   = "%s/intermediate/snapshot-%s" %(inputpath, index)
    if not os.path.exists(inputfile):
        a=1
       # print("The input file \"%s\" could not be found!" % inputfile)
    else:
        print("The input file \"%s\" was found!" % inputfile)

        # --------------------------------------------------------------------
        # Check output file does not already exist
        # --------------------------------------------------------------------
        outputfile = "%s/D2-%8.8d.png" %(outputfolder, snapindex)
        if os.path.exists(outputfile):
            print("The image \"%s\" already exists!" % outputfile)
        else:
            # plot the facets
            segments = gettingFacets(inputfile)
            if (len(segments) == 0):
                print("Error in the file \"%s\" !" % inputfile)
            else:
                # --------------------------------------------------------------------
                # Create the figure
                # --------------------------------------------------------------------
                fig, ax = plt.subplots(1,1)
                fig.set_size_inches(19.20, 10.80)

                # --------------------------------------------------------------------
                # Create strings for labels
                # --------------------------------------------------------------------
                scalelabel = r'$\log_{10}$' + r"$(\|\mathcal{D}\| )$"
                title      = "Deformation  "  +r"$\left( \frac{tU}{R} = %4.2f \right) $" %time
                titlesize  = 30
                TickLabel  = 20
                ax.set_title(title, fontsize=titlesize, pad=15)

                # --------------------------------------------------------------------
                # Drawing the Facets
                # --------------------------------------------------------------------
                line_segments = LineCollection(segments, linewidths=5, colors='#1a9850', linestyle='solid')
                ax.add_collection(line_segments)

                # --------------------------------------------------------------------
                # Drawing the Field
                # --------------------------------------------------------------------
                X, Y, D2, vel, nz = gettingField(inputfile, xmin, ymin, xmax, ymax, Ly, ny)
                xminp, xmaxp, yminp, ymaxp = X.min(), X.max(), Y.min(), Y.max()
                cntrl1 = ax.imshow(D2, cmap="hot", interpolation='bilinear', origin='lower', extent=[xminp, xmaxp, yminp, ymaxp], vmax = 1.0, vmin = -3.0)
                
                l, b, w, h = ax.get_position().bounds
                cb1 = fig.add_axes([l+0.05*w, b-0.05, 0.90*w, 0.03])
                c1 = plt.colorbar(cntrl1,cax=cb1,orientation='horizontal')
                c1.set_label(scalelabel,fontsize=TickLabel, labelpad=5)
                c1.ax.tick_params(labelsize=TickLabel)
                c1.ax.xaxis.set_major_formatter(StrMethodFormatter('{x:,.1f}'))

                # --------------------------------------------------------------------
                # Drawing the Border
                # --------------------------------------------------------------------
                # Line width
                lw = 5
                ax.plot([xmin, xmin], [ymin, ymax],'-',color='black',linewidth=lw)
                ax.plot([xmin, xmax], [ymin, ymin],'-',color='black',linewidth=lw)
                ax.plot([xmin, xmax], [ymax, ymax],'-',color='black',linewidth=lw)
                ax.plot([xmax, xmax], [ymin, ymax],'-',color='black',linewidth=lw)

                # --------------------------------------------------------------------
                # Setting the aspect ratio
                # --------------------------------------------------------------------
                ax.set_aspect('equal')
                ax.set_xlim(xmin, xmax)
                ax.set_ylim(ymin, ymax)
                ax.axis('off')
                
                # --------------------------------------------------------------------
                # Saving the figure
                # --------------------------------------------------------------------
                print('Image \"%s\" done!' % outputfile)
                plt.savefig(outputfile, bbox_inches="tight")
                plt.close()


