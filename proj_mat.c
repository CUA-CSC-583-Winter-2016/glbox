
void arb_proj_mat(const float *a, const float *b, const float *c, const float *e, float n, float f, float *mat) {
  // I'm not sure this is exactily what is needed if everything is in coordinates relative to the display.
  // TODO implement?
}

void screen_proj_mat(float left, float right, float top, float bottom, float far, float *eye, float *mat){
  right -= eye[0];
  left -= eye[0];
  top -= eye[0];
  bottom -= eye[0];
  far -= eye[2];

  
  // This is basically an implementation of the matrix generated by glFrustrum from OpenGL 1.0. See https://www.opengl.org/sdk/docs/man2/xhtml/glFrustum.xml
  // The difference is that everything is translated to camera space first, then the perspective transform is applied.
  // Link to math i've done so far: https://www.wolframalpha.com/input/?i=[[%282*n%29%2F%28r-l%29,0,%28r%2Bl%29%2F%28r-l%29,0],[0,%282*n%29%2F%28t-b%29,%28t%2Bb%29%2F%28t-b%29,0],[0,0,-%28f%2Bn%29%2F%28f-n%29,-%282*f*n%29%2F%28f-n%29],[0,0,-1,0]]*[[1,0,0,X],[0,1,0,Y],[0,0,1,Z],[0,0,0,1]]



}
