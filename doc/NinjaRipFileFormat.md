### Ninja Rip file format

#### Main Header
4 : magic number DE AD C0 DE
4 : file version 
4 : # of faces
4 : # of vertecis
4 : vertex size
4 : # of textures
4 : # of shaders
4 : # of VertexAttrib(va)

#### Vertex Attributes
for (i=0; i<# of VertexAttrib; do)
	null-term string : like "POSITION" or "NORMAL"/"TEXCOORD"/"TANGENT"/"BINORMAL"/
	4 : index
	4 : offset
	4 : size 
	4 : # of elements in va
	for (i=0; i< #_elems_va; do)
		4 : type of element; if (0000): float32
for (i=0; i<# of textures; do)
	null-term string : texture filename
for (i=0; i<# of shaders; do)
	null-term string : shader filename

#### Index Data
for (i=0; i<# of faces; do)
	4: 1st index
	4: 2nd index
	4: 3rd index
	
#### Vertex Data	

for (i=0; i<# of vertecies; do)
	4: f32: vx
	4: f32: vy
	4: f32: vz
	4: f32: nx
	4: f32: ny
	4: f32: nz
	4: f32: tcU
	4: f32: tcV
