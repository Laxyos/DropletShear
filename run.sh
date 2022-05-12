# copy
cp -r Core Output/MaxLevel=$1_Bi=$2_Re=$3_Ca=$4
# move
cd Output/MaxLevel=$1_Bi=$2_Re=$3_Ca=$4
# run 
sudo ./shear_square $1 $2 $3 $4 $5
