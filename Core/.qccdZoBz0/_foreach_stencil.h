foreach_stencil(){

#line 108 "shear_square.c"
{
    ke += (0.5*(sq(val(u.x,0,0,0)) + sq(val(u.y,0,0,0))))*sq(Delta);
  } } end_foreach_stencil();