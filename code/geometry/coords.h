struct coords{
  p3 o, dx, dy, dz;
  coords(){}
  coords(p3 p, p3 q, p3 r){         ///Creates a R3 space with X-Y plane at PQR
    o = p;
    dx = unit(q-p);
    dz = unit(dx%(r-p));
    dy = dz%dx;
  }

  pt pos2(p3 p){ return pt((p-o)*dx, (p-o)*dy);}            ///2D Coordinates of the orthogonal proj
  p3 pos3(p3 p){ return p3((p-o)*dx, (p-o)*dy, (p-o)*dz);}  ///3D Coordinates in new R3-space
};
