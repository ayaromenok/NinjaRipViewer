### Ninja Rip file format

#### Main
4 : magic number DE AD C0 DE
4 : # of vertex in face (3 or 4)
4 : vertex count
4 : vertex size
4 : # of textures
4 : # of shaders
4 : # of VertexAttrib(va)

#### 
8 : str, like "POSITION" or "NORMAL"/"TEXCOORD"/"TANGENT"/"BINORMAL"/
4 : index
4 : offset
4 : size 
4 : # of elements in va
for (i=0; i< #_elems_va; do)
	4 : type of element; 0000 - float32
