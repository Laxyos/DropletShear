#define _call_height_position 1
#define _call_interfacial 1
#define _call_centroids_curvature_fit 1
#define _call_height_curvature_fit 1
#define _call_height_curvature 1
#define _call_vof_concentration_gradient_x 1
#define _call_vof_concentration_gradient_y 1
#define _call_facet_normal 1
#define _call_mycs 1
#if _call_height_position
#  undef _call_pos_x
#  define _call_pos_x 1
#  undef _call_pos_y
#  define _call_pos_y 1
#endif
#if _call_centroids_curvature_fit
#  undef _call_mycs
#  define _call_mycs 1
#endif
#if _call_height_curvature_fit
#  undef _call_mycs
#  define _call_mycs 1
#endif
#if _call_momentum_refine
#  undef _call_refine_bilinear
#  define _call_refine_bilinear 1
#endif
#if _call_vof_concentration_refine
#  undef _call_vof_concentration_gradient_x
#  define _call_vof_concentration_gradient_x 1
#  undef _call_vof_concentration_gradient_y
#  define _call_vof_concentration_gradient_y 1
#endif
#if _call_facet_normal
#  undef _call_mycs
#  define _call_mycs 1
#endif
#if _call_fraction_refine
#  undef _call_mycs
#  define _call_mycs 1
#endif
#if _call_locals_pids
#  undef _call_is_local_prolongation
#  define _call_is_local_prolongation 1
#endif
#if _call_rcv_pid_append
#  undef _call_rcv_append
#  define _call_rcv_append 1
#endif
#if _call_treey
#  undef _call_treey
#  define _call_treey 1
#endif
#if _call_treex
#  undef _call_treex
#  define _call_treex 1
#endif
#if _call_refine_face_solenoidal
#  undef _call_refine_face
#  define _call_refine_face 1
#endif
#if _call_coarsen_cell_recursive
#  undef _call_coarsen_cell
#  define _call_coarsen_cell 1
#  undef _call_coarsen_cell_recursive
#  define _call_coarsen_cell_recursive 1
#endif
#if _call_coarsen_cell
#  undef _call_decrement_neighbors
#  define _call_decrement_neighbors 1
#endif
#if _call_refine_cell
#  undef _call_increment_neighbors
#  define _call_increment_neighbors 1
#  undef _call_refine_cell
#  define _call_refine_cell 1
#endif
#if _call_multigrid_debug
#  undef _call_cartesian_debug
#  define _call_cartesian_debug 1
#endif
#if _call_refine_biquadratic
#  undef _call_biquadratic
#  define _call_biquadratic 1
#endif
#if _call_refine_bilinear
#  undef _call_bilinear
#  define _call_bilinear 1
#endif
#if _call_restriction_face
#  undef _call_face_average
#  define _call_face_average 1
#endif
#if _call_decrement_neighbors
#  undef _call_free_children
#  define _call_free_children 1
#endif
#if _call_increment_neighbors
#  undef _call_alloc_children
#  define _call_alloc_children 1
#endif
