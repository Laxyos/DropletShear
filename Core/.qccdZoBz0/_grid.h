size_t datasize = 17*sizeof (double);
static int defaults (const int i, const double t, Event * _ev);
static int defaults_expr0 (int * ip, double * tp, Event * _ev);
static int cleanup (const int i, const double t, Event * _ev);
static int cleanup_expr0 (int * ip, double * tp, Event * _ev);
static int defaults_0 (const int i, const double t, Event * _ev);
static int defaults_0_expr0 (int * ip, double * tp, Event * _ev);
static int default_display (const int i, const double t, Event * _ev);
static int default_display_expr0 (int * ip, double * tp, Event * _ev);
static int init (const int i, const double t, Event * _ev);
static int init_expr0 (int * ip, double * tp, Event * _ev);
static int set_dtmax (const int i, const double t, Event * _ev);
static int set_dtmax_expr0 (int * ip, double * tp, Event * _ev);
static int stability (const int i, const double t, Event * _ev);
static int stability_expr0 (int * ip, double * tp, Event * _ev);
static int vof (const int i, const double t, Event * _ev);
static int vof_expr0 (int * ip, double * tp, Event * _ev);
static int tracer_advection (const int i, const double t, Event * _ev);
static int tracer_advection_expr0 (int * ip, double * tp, Event * _ev);
static int tracer_diffusion (const int i, const double t, Event * _ev);
static int tracer_diffusion_expr0 (int * ip, double * tp, Event * _ev);
static int properties (const int i, const double t, Event * _ev);
static int properties_expr0 (int * ip, double * tp, Event * _ev);
static int advection_term (const int i, const double t, Event * _ev);
static int advection_term_expr0 (int * ip, double * tp, Event * _ev);
static int viscous_term (const int i, const double t, Event * _ev);
static int viscous_term_expr0 (int * ip, double * tp, Event * _ev);
static int acceleration (const int i, const double t, Event * _ev);
static int acceleration_expr0 (int * ip, double * tp, Event * _ev);
static int projection (const int i, const double t, Event * _ev);
static int projection_expr0 (int * ip, double * tp, Event * _ev);
static int end_timestep (const int i, const double t, Event * _ev);
static int end_timestep_expr0 (int * ip, double * tp, Event * _ev);
static int adapt (const int i, const double t, Event * _ev);
static int adapt_expr0 (int * ip, double * tp, Event * _ev);
static int defaults_1 (const int i, const double t, Event * _ev);
static int defaults_1_expr0 (int * ip, double * tp, Event * _ev);
static int defaults_2 (const int i, const double t, Event * _ev);
static int defaults_2_expr0 (int * ip, double * tp, Event * _ev);
static int stability_0 (const int i, const double t, Event * _ev);
static int stability_0_expr0 (int * ip, double * tp, Event * _ev);
static int vof_0 (const int i, const double t, Event * _ev);
static int vof_0_expr0 (int * ip, double * tp, Event * _ev);
static int defaults_3 (const int i, const double t, Event * _ev);
static int defaults_3_expr0 (int * ip, double * tp, Event * _ev);
static int properties_0 (const int i, const double t, Event * _ev);
static int properties_0_expr0 (int * ip, double * tp, Event * _ev);
static int defaults_4 (const int i, const double t, Event * _ev);
static int defaults_4_expr0 (int * ip, double * tp, Event * _ev);
static int stability_1 (const int i, const double t, Event * _ev);
static int stability_1_expr0 (int * ip, double * tp, Event * _ev);
static int vof_1 (const int i, const double t, Event * _ev);
static int vof_1_expr0 (int * ip, double * tp, Event * _ev);
static int tracer_advection_0 (const int i, const double t, Event * _ev);
static int tracer_advection_0_expr0 (int * ip, double * tp, Event * _ev);
static int defaults_5 (const int i, const double t, Event * _ev);
static int defaults_5_expr0 (int * ip, double * tp, Event * _ev);
static int acceleration_0 (const int i, const double t, Event * _ev);
static int acceleration_0_expr0 (int * ip, double * tp, Event * _ev);
static int stability_2 (const int i, const double t, Event * _ev);
static int stability_2_expr0 (int * ip, double * tp, Event * _ev);
static int acceleration_1 (const int i, const double t, Event * _ev);
static int acceleration_1_expr0 (int * ip, double * tp, Event * _ev);
static int init_0 (const int i, const double t, Event * _ev);
static int init_0_expr0 (int * ip, double * tp, Event * _ev);
static int adapt_0 (const int i, const double t, Event * _ev);
static int adapt_0_expr0 (int * ip, double * tp, Event * _ev);
static int writingFiles (const int i, const double t, Event * _ev);
static int writingFiles_expr0 (int * ip, double * tp, Event * _ev);
static int writingFiles_expr1 (int * ip, double * tp, Event * _ev);
static int writingFiles_expr2 (int * ip, double * tp, Event * _ev);
static int end (const int i, const double t, Event * _ev);
static int end_expr0 (int * ip, double * tp, Event * _ev);
static int logWriting (const int i, const double t, Event * _ev);
static int logWriting_expr0 (int * ip, double * tp, Event * _ev);
static void _set_boundary0 (void);
static void _set_boundary1 (void);
static void _set_boundary2 (void);
static void _set_boundary3 (void);
static void _set_boundary4 (void);
static void _set_boundary5 (void);
void _init_solver (void) {
  void init_solver();
  init_solver();
  Events = (Event *) pmalloc (sizeof (Event), __func__, __FILE__, __LINE__);
  Events[0].last = 1;
  event_register ((Event){ 0, 1, defaults, {defaults_expr0}, ((int *)0), ((double *)0),
    "/home/laxyos/basilisk/src/run.h", 42, "defaults"});
  event_register ((Event){ 0, 1, defaults_0, {defaults_0_expr0}, ((int *)0), ((double *)0),
    "/home/laxyos/basilisk/src/navier-stokes/centered.h", 126, "defaults"});
  event_register ((Event){ 0, 1, defaults_1, {defaults_1_expr0}, ((int *)0), ((double *)0),
    "/home/laxyos/basilisk/src/vof.h", 103, "defaults"});
  event_register ((Event){ 0, 1, defaults_2, {defaults_2_expr0}, ((int *)0), ((double *)0),
    "/home/laxyos/basilisk/src/vof.h", 123, "defaults"});
  event_register ((Event){ 0, 1, defaults_3, {defaults_3_expr0}, ((int *)0), ((double *)0),
    "./two-phaseVP.h", 27, "defaults"});
  event_register ((Event){ 0, 1, defaults_4, {defaults_4_expr0}, ((int *)0), ((double *)0),
    "/home/laxyos/basilisk/src/navier-stokes/conserving.h", 37, "defaults"});
  event_register ((Event){ 0, 1, defaults_5, {defaults_5_expr0}, ((int *)0), ((double *)0),
    "/home/laxyos/basilisk/src/iforce.h", 30, "defaults"});
  event_register ((Event){ 0, 1, default_display, {default_display_expr0}, ((int *)0), ((double *)0),
    "/home/laxyos/basilisk/src/navier-stokes/centered.h", 179, "default_display"});
  event_register ((Event){ 0, 1, init, {init_expr0}, ((int *)0), ((double *)0),
    "/home/laxyos/basilisk/src/navier-stokes/centered.h", 188, "init"});
  event_register ((Event){ 0, 1, init_0, {init_0_expr0}, ((int *)0), ((double *)0),
    "shear_square.c", 70, "init"});
  event_register ((Event){ 0, 3, writingFiles, {writingFiles_expr0, writingFiles_expr1, writingFiles_expr2}, ((int *)0), ((double *)0),
    "shear_square.c", 96, "writingFiles"});
  event_register ((Event){ 0, 1, end, {end_expr0}, ((int *)0), ((double *)0),
    "shear_square.c", 102, "end"});
  event_register ((Event){ 0, 1, logWriting, {logWriting_expr0}, ((int *)0), ((double *)0),
    "shear_square.c", 106, "logWriting"});
  event_register ((Event){ 0, 1, cleanup, {cleanup_expr0}, ((int *)0), ((double *)0),
    "/home/laxyos/basilisk/src/run.h", 50, "cleanup"});
  event_register ((Event){ 0, 1, set_dtmax, {set_dtmax_expr0}, ((int *)0), ((double *)0),
    "/home/laxyos/basilisk/src/navier-stokes/centered.h", 214, "set_dtmax"});
  event_register ((Event){ 0, 1, stability, {stability_expr0}, ((int *)0), ((double *)0),
    "/home/laxyos/basilisk/src/navier-stokes/centered.h", 216, "stability"});
  event_register ((Event){ 0, 1, stability_0, {stability_0_expr0}, ((int *)0), ((double *)0),
    "/home/laxyos/basilisk/src/vof.h", 136, "stability"});
  event_register ((Event){ 0, 1, stability_1, {stability_1_expr0}, ((int *)0), ((double *)0),
    "/home/laxyos/basilisk/src/navier-stokes/conserving.h", 72, "stability"});
  event_register ((Event){ 0, 1, stability_2, {stability_2_expr0}, ((int *)0), ((double *)0),
    "/home/laxyos/basilisk/src/tension.h", 36, "stability"});
  event_register ((Event){ 0, 1, vof, {vof_expr0}, ((int *)0), ((double *)0),
    "/home/laxyos/basilisk/src/navier-stokes/centered.h", 226, "vof"});
  event_register ((Event){ 0, 1, vof_0, {vof_0_expr0}, ((int *)0), ((double *)0),
    "/home/laxyos/basilisk/src/vof.h", 363, "vof"});
  event_register ((Event){ 0, 1, vof_1, {vof_1_expr0}, ((int *)0), ((double *)0),
    "/home/laxyos/basilisk/src/navier-stokes/conserving.h", 117, "vof"});
  event_register ((Event){ 0, 1, tracer_advection, {tracer_advection_expr0}, ((int *)0), ((double *)0),
    "/home/laxyos/basilisk/src/navier-stokes/centered.h", 227, "tracer_advection"});
  event_register ((Event){ 0, 1, tracer_advection_0, {tracer_advection_0_expr0}, ((int *)0), ((double *)0),
    "/home/laxyos/basilisk/src/navier-stokes/conserving.h", 192, "tracer_advection"});
  event_register ((Event){ 0, 1, tracer_diffusion, {tracer_diffusion_expr0}, ((int *)0), ((double *)0),
    "/home/laxyos/basilisk/src/navier-stokes/centered.h", 228, "tracer_diffusion"});
  event_register ((Event){ 0, 1, properties, {properties_expr0}, ((int *)0), ((double *)0),
    "/home/laxyos/basilisk/src/navier-stokes/centered.h", 235, "properties"});
  event_register ((Event){ 0, 1, properties_0, {properties_0_expr0}, ((int *)0), ((double *)0),
    "./two-phaseVP.h", 61, "properties"});
  event_register ((Event){ 0, 1, advection_term, {advection_term_expr0}, ((int *)0), ((double *)0),
    "/home/laxyos/basilisk/src/navier-stokes/centered.h", 308, "advection_term"});
  event_register ((Event){ 0, 1, viscous_term, {viscous_term_expr0}, ((int *)0), ((double *)0),
    "/home/laxyos/basilisk/src/navier-stokes/centered.h", 337, "viscous_term"});
  event_register ((Event){ 0, 1, acceleration, {acceleration_expr0}, ((int *)0), ((double *)0),
    "/home/laxyos/basilisk/src/navier-stokes/centered.h", 373, "acceleration"});
  event_register ((Event){ 0, 1, acceleration_0, {acceleration_0_expr0}, ((int *)0), ((double *)0),
    "/home/laxyos/basilisk/src/iforce.h", 43, "acceleration"});
  event_register ((Event){ 0, 1, acceleration_1, {acceleration_1_expr0}, ((int *)0), ((double *)0),
    "/home/laxyos/basilisk/src/tension.h", 72, "acceleration"});
  event_register ((Event){ 0, 1, projection, {projection_expr0}, ((int *)0), ((double *)0),
    "/home/laxyos/basilisk/src/navier-stokes/centered.h", 413, "projection"});
  event_register ((Event){ 0, 1, end_timestep, {end_timestep_expr0}, ((int *)0), ((double *)0),
    "/home/laxyos/basilisk/src/navier-stokes/centered.h", 428, "end_timestep"});
  event_register ((Event){ 0, 1, adapt, {adapt_expr0}, ((int *)0), ((double *)0),
    "/home/laxyos/basilisk/src/navier-stokes/centered.h", 438, "adapt"});
  event_register ((Event){ 0, 1, adapt_0, {adapt_0_expr0}, ((int *)0), ((double *)0),
    "shear_square.c", 81, "adapt"});
  void allocate_globals (int);
  allocate_globals (17);
  set_fpe();
  quadtree_methods();
  init_scalar ((scalar){16}, "omega");
  init_scalar ((scalar){15}, "sf");
  init_scalar ((scalar){14}, "rhov");
  init_face_vector ((vector){{12},{13}}, "alphav");
  init_face_vector ((vector){{10},{11}}, "D2f");
  init_scalar ((scalar){9}, "D2");
  init_scalar ((scalar){8}, "f");
  init_face_vector ((vector){{6},{7}}, "uf");
  init_scalar ((scalar){5}, "pf");
  init_vector ((vector){{3},{4}}, "g");
  init_vector ((vector){{1},{2}}, "u");
  init_scalar ((scalar){0}, "p");
  init_const_scalar ((scalar){_NVARMAX+5}, "zeroc",  0.);
  init_const_scalar ((scalar){_NVARMAX+4}, "unity",  1.);
  init_const_vector ((vector){{_NVARMAX+2},{_NVARMAX+3}}, "unityf", (double []) {1.,1.,1.});
  init_const_vector ((vector){{_NVARMAX+0},{_NVARMAX+1}}, "zerof", (double []) {0.,0.,0.});
  _set_boundary0();
  _set_boundary1();
  _set_boundary2();
  _set_boundary3();
  _set_boundary4();
  _set_boundary5();
}
