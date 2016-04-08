#ifndef OFF_AXIS_H
#define OFF_AXIS_H

/*
        c----------.   y
        |          |   |
        |\ +       |   |
        a--|-------b   '-----x
         '\|   /
           e
*/

/*
  a, b, and c must point to arrays in the format {float x, float y, float z}
  @param a bottom left point.
  @param b bottom right point.
  @param c top left point.
  @param e eye point.
  @param n near plane.
  @param f far plane.
  @param mat pointer for matrix output 4x4 matrix in row major format.
*/
void arb_proj_mat(const float *a, const float *b, const float *c, const float *e, float n, float f, float *mat);

/*
  Calculates the projection matrix assuming that the screen lays on the z = 0 plane.
  @param left x value for left side of screen relative to origin.
  @param right x value for right side of screen.
  @param top y value for top of screen.
  @param bottom how far -y the screen extends.
  @param far far clipping plane. The near clipping plane will be the screen.
  @param eye eye point.
  @param mat matrix output, row major.
*/

void screen_proj_mat(float left, float right, float top, float bottom, float far, float *eye, float *mat);
#endif
