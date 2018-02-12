/*
#include <iostream>
// Vector - STD Vector/Array Library
#include <vector>

// String - STD String Library
#include <string>

// fStream - STD File I/O Library
#include <fstream>

// Math.h - STD math Library
#include <math.h>

// Print progress to console while loading (large models)
#define OBJL_CONSOLE_OUTPUT

// Namespace: OBJL
//
// Description: The namespace that holds eveyrthing that
//	is needed and used for the OBJ Model Loader
namespace objl
{
// Structure: Vector2
//
// Description: A 2D Vector that Holds Positional Data
struct Vector2
{
// Default Constructor
Vector2()
{
X = 0.0f;
Y = 0.0f;
}
// Variable Set Constructor
Vector2(float X_, float Y_)
{
X = X_;
Y = Y_;
}
// Bool Equals Operator Overload
bool operator==(const Vector2& other) const
{
return (this->X == other.X && this->Y == other.Y);
}
// Bool Not Equals Operator Overload
bool operator!=(const Vector2& other) const
{
return !(this->X == other.X && this->Y == other.Y);
}
// Addition Operator Overload
Vector2 operator+(const Vector2& right) const
{
return Vector2(this->X + right.X, this->Y + right.Y);
}
// Subtraction Operator Overload
Vector2 operator-(const Vector2& right) const
{
return Vector2(this->X - right.X, this->Y - right.Y);
}
// Float Multiplication Operator Overload
Vector2 operator*(const float& other) const
{
return Vector2(this->X *other, this->Y * other);
}

// Positional Variables
float X;
float Y;
};

// Structure: Vector3
//
// Description: A 3D Vector that Holds Positional Data
struct Vector3
{
// Default Constructor
Vector3()
{
X = 0.0f;
Y = 0.0f;
Z = 0.0f;
}
// Variable Set Constructor
Vector3(float X_, float Y_, float Z_)
{
X = X_;
Y = Y_;
Z = Z_;
}
// Bool Equals Operator Overload
bool operator==(const Vector3& other) const
{
return (this->X == other.X && this->Y == other.Y && this->Z == other.Z);
}
// Bool Not Equals Operator Overload
bool operator!=(const Vector3& other) const
{
return !(this->X == other.X && this->Y == other.Y && this->Z == other.Z);
}
// Addition Operator Overload
Vector3 operator+(const Vector3& right) const
{
return Vector3(this->X + right.X, this->Y + right.Y, this->Z + right.Z);
}
// Subtraction Operator Overload
Vector3 operator-(const Vector3& right) const
{
return Vector3(this->X - right.X, this->Y - right.Y, this->Z - right.Z);
}
// Float Multiplication Operator Overload
Vector3 operator*(const float& other) const
{
return Vector3(this->X *other, this->Y * other, this->Z - other);
}

// Positional Variables
float X;
float Y;
float Z;
};

// Structure: Vertex
//
// Description: Model Vertex object that holds
//	a Position, Normal, and Texture Coordinate
struct Vertex
{
// Position Vector
Vector3 Position;

// Normal Vector
Vector3 Normal;

// Texture Coordinate Vector
Vector2 TextureCoordinate;
};

struct Material
{
Material()
{
name;
Ns = 0.0f;
Ni = 0.0f;
d = 0.0f;
illum = 0;
}

// Material Name
std::string name;
// Ambient Color
Vector3 Ka;
// Diffuse Color
Vector3 Kd;
// Specular Color
Vector3 Ks;
// Specular Exponent
float Ns;
// Optical Density
float Ni;
// Dissolve
float d;
// Illumination
int illum;
// Ambient Texture Map
std::string map_Ka;
// Diffuse Texture Map
std::string map_Kd;
// Specular Texture Map
std::string map_Ks;
// Specular Hightlight Map
std::string map_Ns;
// Alpha Texture Map
std::string map_d;
// Bump Map
std::string map_bump;
};

// Structure: Mesh
//
// Description: A Simple Mesh Object that holds
//	a name, a vertex list, and an index list
struct Mesh
{
// Default Constructor
Mesh()
{

}
// Variable Set Constructor
Mesh(std::vector<Vertex>& _Vertices, std::vector<unsigned int>& _Indices)
{
Vertices = _Vertices;
Indices = _Indices;
}
// Mesh Name
std::string MeshName;
// Vertex List
std::vector<Vertex> Vertices;
// Index List
std::vector<unsigned int> Indices;

// Material
Material MeshMaterial;
};

// Namespace: Math
//
// Description: The namespace that holds all of the math
//	functions need for OBJL
namespace math
{
// Vector3 Cross Product
Vector3 CrossV3(const Vector3 a, const Vector3 b)
{
return Vector3(a.Y * b.Z - a.Z * b.Y,
a.Z * b.X - a.X * b.Z,
a.X * b.Y - a.Y * b.X);
}

// Vector3 Magnitude Calculation
float MagnitudeV3(const Vector3 in)
{
return (sqrtf(powf(in.X, 2) + powf(in.Y, 2) + powf(in.Z, 2)));
}

// Vector3 DotProduct
float DotV3(const Vector3 a, const Vector3 b)
{
return (a.X * b.X) + (a.Y * b.Y) + (a.Z * b.Z);
}

// Angle between 2 Vector3 Objects
float AngleBetweenV3(const Vector3 a, const Vector3 b)
{
float angle = DotV3(a, b);
angle /= (MagnitudeV3(a) * MagnitudeV3(b));
return angle = acosf(angle);
}
}

// Namespace: Algorithm
//
// Description: The namespace that holds all of the
// Algorithms needed for OBJL
namespace algorithm
{
// Vector3 Multiplication Opertor Overload
Vector3 operator*(const float& left, const Vector3& right)
{
return Vector3(right.X * left, right.Y * left, right.Z * left);
}

// Check to see if a Vector3 Point is within a 3 Vector3 Triangle
bool inTriangle(Vector3 point, Vector3 tri1, Vector3 tri2, Vector3 tri3)
{
// Starting vars
Vector3 u = tri2 - tri1;
Vector3 v = tri3 - tri1;
Vector3 w = point - tri1;
Vector3 n = math::CrossV3(u, v);

float y = (math::DotV3(math::CrossV3(u, w), n) / math::DotV3(n, n));
float b = (math::DotV3(math::CrossV3(u, w), n) / math::DotV3(n, n));
float a = 1 - y - b;

// Projected point
Vector3  p = (a * tri1) + (b * tri2) + (y * tri3);

if (a >= 0 && a <= 1
&& b >= 0 && b <= 1
&& y >= 0 && y <= 1)
{
return true;
}
else
return false;
}

// Split a String into a string array at a given token
inline void split(const std::string &in,
std::vector<std::string> &out,
std::string token)
{
out.clear();

std::string temp;

for (int i = 0; i < int(in.size()); i++)
{
std::string test = in.substr(i, token.size());

if (test == token)
{
if (!temp.empty())
{
out.push_back(temp);
temp.clear();
i += (int)token.size() - 1;
}
else
{
out.push_back("");
}
}
else if (i + token.size() >= in.size())
{
temp += in.substr(i, token.size());
out.push_back(temp);
break;
}
else
{
temp += in[i];
}
}
}

// Get tail of string after first token and possibly following spaces
inline std::string tail(const std::string &in)
{
size_t token_start = in.find_first_not_of(" \t");
size_t space_start = in.find_first_of(" \t", token_start);
size_t tail_start = in.find_first_not_of(" \t", space_start);
size_t tail_end = in.find_last_not_of(" \t");
if (tail_start != std::string::npos && tail_end != std::string::npos)
{
return in.substr(tail_start, tail_end - tail_start + 1);
}
else if (tail_start != std::string::npos)
{
return in.substr(tail_start);
}
return "";
}

// Get first token of string
inline std::string firstToken(const std::string &in)
{
if (!in.empty())
{
size_t token_start = in.find_first_not_of(" \t");
size_t token_end = in.find_first_of(" \t", token_start);
if (token_start != std::string::npos && token_end != std::string::npos)
{
return in.substr(token_start, token_end - token_start);
}
else if (token_start != std::string::npos)
{
return in.substr(token_start);
}
}
return "";
}

// Get element at given index position
template <class T>
inline const T & getElement(const std::vector<T> &elements, std::string &index)
{
int idx = std::stoi(index);
if (idx < 0)
idx = int(elements.size()) + idx;
else
idx--;
return elements[idx];
}
}

// Class: Loader
//
// Description: The OBJ Model Loader
class Loader
{
public:
// Default Constructor
Loader()
{

}
~Loader()
{
LoadedMeshes.clear();
}

// Load a file into the loader
//
// If file is loaded return true
//
// If the file is unable to be found
// or unable to be loaded return false
bool LoadFile(std::string Path)
{
// If the file is not an .obj file return false
if (Path.substr(Path.size() - 4, 4) != ".obj")
return false;


std::ifstream file(Path);

if (!file.is_open())
return false;

LoadedMeshes.clear();
LoadedVertices.clear();
LoadedIndices.clear();

std::vector<Vector3> Positions;
std::vector<Vector2> TCoords;
std::vector<Vector3> Normals;

std::vector<Vertex> Vertices;
std::vector<unsigned int> Indices;

std::vector<std::string> MeshMatNames;

bool listening = false;
std::string meshname;

Mesh tempMesh;

#ifdef OBJL_CONSOLE_OUTPUT
const unsigned int outputEveryNth = 1000;
unsigned int outputIndicator = outputEveryNth;
#endif

std::string curline;
while (std::getline(file, curline))
{
#ifdef OBJL_CONSOLE_OUTPUT
if ((outputIndicator = ((outputIndicator + 1) % outputEveryNth)) == 1)
{
if (!meshname.empty())
{
std::cout
<< "\r- " << meshname
<< "\t| vertices > " << Positions.size()
<< "\t| texcoords > " << TCoords.size()
<< "\t| normals > " << Normals.size()
<< "\t| triangles > " << (Vertices.size() / 3)
<< (!MeshMatNames.empty() ? "\t| material: " + MeshMatNames.back() : "");
}
}
#endif

// Generate a Mesh Object or Prepare for an object to be created
if (algorithm::firstToken(curline) == "o" || algorithm::firstToken(curline) == "g" || curline[0] == 'g')
{
if (!listening)
{
listening = true;

if (algorithm::firstToken(curline) == "o" || algorithm::firstToken(curline) == "g")
{
meshname = algorithm::tail(curline);
}
else
{
meshname = "unnamed";
}
}
else
{
// Generate the mesh to put into the array

if (!Indices.empty() && !Vertices.empty())
{
// Create Mesh
tempMesh = Mesh(Vertices, Indices);
tempMesh.MeshName = meshname;

// Insert Mesh
LoadedMeshes.push_back(tempMesh);

// Cleanup
Vertices.clear();
Indices.clear();
meshname.clear();

meshname = algorithm::tail(curline);
}
else
{
if (algorithm::firstToken(curline) == "o" || algorithm::firstToken(curline) == "g")
{
meshname = algorithm::tail(curline);
}
else
{
meshname = "unnamed";
}
}
}
#ifdef OBJL_CONSOLE_OUTPUT
std::cout << std::endl;
outputIndicator = 0;
#endif
}
// Generate a Vertex Position
if (algorithm::firstToken(curline) == "v")
{
std::vector<std::string> spos;
Vector3 vpos;
algorithm::split(algorithm::tail(curline), spos, " ");

vpos.X = std::stof(spos[0]);
vpos.Y = std::stof(spos[1]);
vpos.Z = std::stof(spos[2]);

Positions.push_back(vpos);
}
// Generate a Vertex Texture Coordinate
if (algorithm::firstToken(curline) == "vt")
{
std::vector<std::string> stex;
Vector2 vtex;
algorithm::split(algorithm::tail(curline), stex, " ");

vtex.X = std::stof(stex[0]);
vtex.Y = std::stof(stex[1]);

TCoords.push_back(vtex);
}
// Generate a Vertex Normal;
if (algorithm::firstToken(curline) == "vn")
{
std::vector<std::string> snor;
Vector3 vnor;
algorithm::split(algorithm::tail(curline), snor, " ");

vnor.X = std::stof(snor[0]);
vnor.Y = std::stof(snor[1]);
vnor.Z = std::stof(snor[2]);

Normals.push_back(vnor);
}
// Generate a Face (vertices & indices)
if (algorithm::firstToken(curline) == "f")
{
// Generate the vertices
std::vector<Vertex> vVerts;
GenVerticesFromRawOBJ(vVerts, Positions, TCoords, Normals, curline);

// Add Vertices
for (int i = 0; i < int(vVerts.size()); i++)
{
Vertices.push_back(vVerts[i]);

LoadedVertices.push_back(vVerts[i]);
}

std::vector<unsigned int> iIndices;

VertexTriangluation(iIndices, vVerts);

// Add Indices
for (int i = 0; i < int(iIndices.size()); i++)
{
unsigned int indnum = (unsigned int)((Vertices.size()) - vVerts.size()) + iIndices[i];
Indices.push_back(indnum);

indnum = (unsigned int)((LoadedVertices.size()) - vVerts.size()) + iIndices[i];
LoadedIndices.push_back(indnum);

}
}
// Get Mesh Material Name
if (algorithm::firstToken(curline) == "usemtl")
{
MeshMatNames.push_back(algorithm::tail(curline));

// Create new Mesh, if Material changes within a group
if (!Indices.empty() && !Vertices.empty())
{
// Create Mesh
tempMesh = Mesh(Vertices, Indices);
tempMesh.MeshName = meshname;
int i = 2;
while (1) {
tempMesh.MeshName = meshname + "_" + std::to_string(i);

for (auto &m : LoadedMeshes)
if (m.MeshName == tempMesh.MeshName)
continue;
break;
}

// Insert Mesh
LoadedMeshes.push_back(tempMesh);

// Cleanup
Vertices.clear();
Indices.clear();
}

#ifdef OBJL_CONSOLE_OUTPUT
outputIndicator = 0;
#endif
}
// Load Materials
if (algorithm::firstToken(curline) == "mtllib")
{
// Generate LoadedMaterial

// Generate a path to the material file
std::vector<std::string> temp;
algorithm::split(Path, temp, "/");

std::string pathtomat = "";

if (temp.size() != 1)
{
for (int i = 0; i < temp.size() - 1; i++)
{
pathtomat += temp[i] + "/";
}
}


pathtomat += algorithm::tail(curline);

#ifdef OBJL_CONSOLE_OUTPUT
std::cout << std::endl << "- find materials in: " << pathtomat << std::endl;
#endif

// Load Materials
LoadMaterials(pathtomat);
}
}

#ifdef OBJL_CONSOLE_OUTPUT
std::cout << std::endl;
#endif

// Deal with last mesh

if (!Indices.empty() && !Vertices.empty())
{
// Create Mesh
tempMesh = Mesh(Vertices, Indices);
tempMesh.MeshName = meshname;

// Insert Mesh
LoadedMeshes.push_back(tempMesh);
}

file.close();

// Set Materials for each Mesh
for (int i = 0; i < MeshMatNames.size(); i++)
{
std::string matname = MeshMatNames[i];

// Find corresponding material name in loaded materials
// when found copy material variables into mesh material
for (int j = 0; j < LoadedMaterials.size(); j++)
{
if (LoadedMaterials[j].name == matname)
{
LoadedMeshes[i].MeshMaterial = LoadedMaterials[j];
break;
}
}
}

if (LoadedMeshes.empty() && LoadedVertices.empty() && LoadedIndices.empty())
{
return false;
}
else
{
return true;
}
}

// Loaded Mesh Objects
std::vector<Mesh> LoadedMeshes;
// Loaded Vertex Objects
std::vector<Vertex> LoadedVertices;
// Loaded Index Positions
std::vector<unsigned int> LoadedIndices;
// Loaded Material Objects
std::vector<Material> LoadedMaterials;

private:
// Generate vertices from a list of positions,
//	tcoords, normals and a face line
void GenVerticesFromRawOBJ(std::vector<Vertex>& oVerts,
const std::vector<Vector3>& iPositions,
const std::vector<Vector2>& iTCoords,
const std::vector<Vector3>& iNormals,
std::string icurline)
{
std::vector<std::string> sface, svert;
Vertex vVert;
algorithm::split(algorithm::tail(icurline), sface, " ");

bool noNormal = false;

// For every given vertex do this
for (int i = 0; i < int(sface.size()); i++)
{
// See What type the vertex is.
int vtype;

algorithm::split(sface[i], svert, "/");

// Check for just position - v1
if (svert.size() == 1)
{
// Only position
vtype = 1;
}

// Check for position & texture - v1/vt1
if (svert.size() == 2)
{
// Position & Texture
vtype = 2;
}

// Check for Position, Texture and Normal - v1/vt1/vn1
// or if Position and Normal - v1//vn1
if (svert.size() == 3)
{
if (svert[1] != "")
{
// Position, Texture, and Normal
vtype = 4;
}
else
{
// Position & Normal
vtype = 3;
}
}

// Calculate and store the vertex
switch (vtype)
{
case 1: // P
{
vVert.Position = algorithm::getElement(iPositions, svert[0]);
vVert.TextureCoordinate = Vector2(0, 0);
noNormal = true;
oVerts.push_back(vVert);
break;
}
case 2: // P/T
{
vVert.Position = algorithm::getElement(iPositions, svert[0]);
vVert.TextureCoordinate = algorithm::getElement(iTCoords, svert[1]);
noNormal = true;
oVerts.push_back(vVert);
break;
}
case 3: // P//N
{
vVert.Position = algorithm::getElement(iPositions, svert[0]);
vVert.TextureCoordinate = Vector2(0, 0);
vVert.Normal = algorithm::getElement(iNormals, svert[2]);
oVerts.push_back(vVert);
break;
}
case 4: // P/T/N
{
vVert.Position = algorithm::getElement(iPositions, svert[0]);
vVert.TextureCoordinate = algorithm::getElement(iTCoords, svert[1]);
vVert.Normal = algorithm::getElement(iNormals, svert[2]);
oVerts.push_back(vVert);
break;
}
default:
{
break;
}
}
}

// take care of missing normals
// these may not be truly acurate but it is the
// best they get for not compiling a mesh with normals
if (noNormal)
{
Vector3 A = oVerts[0].Position - oVerts[1].Position;
Vector3 B = oVerts[2].Position - oVerts[1].Position;

Vector3 normal = math::CrossV3(A, B);

for (int i = 0; i < int(oVerts.size()); i++)
{
oVerts[i].Normal = normal;
}
}
}

// Triangulate a list of vertices into a face by printing
//	inducies corresponding with triangles within it
void VertexTriangluation(std::vector<unsigned int>& oIndices,
const std::vector<Vertex>& iVerts)
{
// If there are 2 or less verts,
// no triangle can be created,
// so exit
if (iVerts.size() < 3)
{
return;
}
// If it is a triangle no need to calculate it
if (iVerts.size() == 3)
{
oIndices.push_back(0);
oIndices.push_back(1);
oIndices.push_back(2);
return;
}

// Create a list of vertices
std::vector<Vertex> tVerts = iVerts;

while (true)
{
// For every vertex
for (int i = 0; i < int(tVerts.size()); i++)
{
// pPrev = the previous vertex in the list
Vertex pPrev;
if (i == 0)
{
pPrev = tVerts[tVerts.size() - 1];
}
else
{
pPrev = tVerts[i - 1];
}

// pCur = the current vertex;
Vertex pCur = tVerts[i];

// pNext = the next vertex in the list
Vertex pNext;
if (i == tVerts.size() - 1)
{
pNext = tVerts[0];
}
else
{
pNext = tVerts[i + 1];
}

// Check to see if there are only 3 verts left
// if so this is the last triangle
if (tVerts.size() == 3)
{
// Create a triangle from pCur, pPrev, pNext
for (int j = 0; j < int(tVerts.size()); j++)
{
if (iVerts[j].Position == pCur.Position)
oIndices.push_back(j);
if (iVerts[j].Position == pPrev.Position)
oIndices.push_back(j);
if (iVerts[j].Position == pNext.Position)
oIndices.push_back(j);
}

tVerts.clear();
break;
}
if (tVerts.size() == 4)
{
// Create a triangle from pCur, pPrev, pNext
for (int j = 0; j < int(iVerts.size()); j++)
{
if (iVerts[j].Position == pCur.Position)
oIndices.push_back(j);
if (iVerts[j].Position == pPrev.Position)
oIndices.push_back(j);
if (iVerts[j].Position == pNext.Position)
oIndices.push_back(j);
}

Vector3 tempVec;
for (int j = 0; j < int(tVerts.size()); j++)
{
if (tVerts[j].Position != pCur.Position
&& tVerts[j].Position != pPrev.Position
&& tVerts[j].Position != pNext.Position)
{
tempVec = tVerts[j].Position;
break;
}
}

// Create a triangle from pCur, pPrev, pNext
for (int j = 0; j < int(iVerts.size()); j++)
{
if (iVerts[j].Position == pPrev.Position)
oIndices.push_back(j);
if (iVerts[j].Position == pNext.Position)
oIndices.push_back(j);
if (iVerts[j].Position == tempVec)
oIndices.push_back(j);
}

tVerts.clear();
break;
}

// If Vertex is not an interior vertex
float angle = math::AngleBetweenV3(pPrev.Position - pCur.Position, pNext.Position - pCur.Position) * (180 / 3.14159265359);
if (angle <= 0 && angle >= 180)
continue;

// If any vertices are within this triangle
bool inTri = false;
for (int j = 0; j < int(iVerts.size()); j++)
{
if (algorithm::inTriangle(iVerts[j].Position, pPrev.Position, pCur.Position, pNext.Position)
&& iVerts[j].Position != pPrev.Position
&& iVerts[j].Position != pCur.Position
&& iVerts[j].Position != pNext.Position)
{
inTri = true;
break;
}
}
if (inTri)
continue;

// Create a triangle from pCur, pPrev, pNext
for (int j = 0; j < int(iVerts.size()); j++)
{
if (iVerts[j].Position == pCur.Position)
oIndices.push_back(j);
if (iVerts[j].Position == pPrev.Position)
oIndices.push_back(j);
if (iVerts[j].Position == pNext.Position)
oIndices.push_back(j);
}

// Delete pCur from the list
for (int j = 0; j < int(tVerts.size()); j++)
{
if (tVerts[j].Position == pCur.Position)
{
tVerts.erase(tVerts.begin() + j);
break;
}
}

// reset i to the start
// -1 since loop will add 1 to it
i = -1;
}

// if no triangles were created
if (oIndices.size() == 0)
break;

// if no more vertices
if (tVerts.size() == 0)
break;
}
}

// Load Materials from .mtl file
bool LoadMaterials(std::string path)
{
// If the file is not a material file return false
if (path.substr(path.size() - 4, path.size()) != ".mtl")
return false;

std::ifstream file(path);

// If the file is not found return false
if (!file.is_open())
return false;

Material tempMaterial;

bool listening = false;

// Go through each line looking for material variables
std::string curline;
while (std::getline(file, curline))
{
// new material and material name
if (algorithm::firstToken(curline) == "newmtl")
{
if (!listening)
{
listening = true;

if (curline.size() > 7)
{
tempMaterial.name = algorithm::tail(curline);
}
else
{
tempMaterial.name = "none";
}
}
else
{
// Generate the material

// Push Back loaded Material
LoadedMaterials.push_back(tempMaterial);

// Clear Loaded Material
tempMaterial = Material();

if (curline.size() > 7)
{
tempMaterial.name = algorithm::tail(curline);
}
else
{
tempMaterial.name = "none";
}
}
}
// Ambient Color
if (algorithm::firstToken(curline) == "Ka")
{
std::vector<std::string> temp;
algorithm::split(algorithm::tail(curline), temp, " ");

if (temp.size() != 3)
continue;

tempMaterial.Ka.X = std::stof(temp[0]);
tempMaterial.Ka.Y = std::stof(temp[1]);
tempMaterial.Ka.Z = std::stof(temp[2]);
}
// Diffuse Color
if (algorithm::firstToken(curline) == "Kd")
{
std::vector<std::string> temp;
algorithm::split(algorithm::tail(curline), temp, " ");

if (temp.size() != 3)
continue;

tempMaterial.Kd.X = std::stof(temp[0]);
tempMaterial.Kd.Y = std::stof(temp[1]);
tempMaterial.Kd.Z = std::stof(temp[2]);
}
// Specular Color
if (algorithm::firstToken(curline) == "Ks")
{
std::vector<std::string> temp;
algorithm::split(algorithm::tail(curline), temp, " ");

if (temp.size() != 3)
continue;

tempMaterial.Ks.X = std::stof(temp[0]);
tempMaterial.Ks.Y = std::stof(temp[1]);
tempMaterial.Ks.Z = std::stof(temp[2]);
}
// Specular Exponent
if (algorithm::firstToken(curline) == "Ns")
{
tempMaterial.Ns = std::stof(algorithm::tail(curline));
}
// Optical Density
if (algorithm::firstToken(curline) == "Ni")
{
tempMaterial.Ni = std::stof(algorithm::tail(curline));
}
// Dissolve
if (algorithm::firstToken(curline) == "d")
{
tempMaterial.d = std::stof(algorithm::tail(curline));
}
// Illumination
if (algorithm::firstToken(curline) == "illum")
{
tempMaterial.illum = std::stoi(algorithm::tail(curline));
}
// Ambient Texture Map
if (algorithm::firstToken(curline) == "map_Ka")
{
tempMaterial.map_Ka = algorithm::tail(curline);
}
// Diffuse Texture Map
if (algorithm::firstToken(curline) == "map_Kd")
{
tempMaterial.map_Kd = algorithm::tail(curline);
}
// Specular Texture Map
if (algorithm::firstToken(curline) == "map_Ks")
{
tempMaterial.map_Ks = algorithm::tail(curline);
}
// Specular Hightlight Map
if (algorithm::firstToken(curline) == "map_Ns")
{
tempMaterial.map_Ns = algorithm::tail(curline);
}
// Alpha Texture Map
if (algorithm::firstToken(curline) == "map_d")
{
tempMaterial.map_d = algorithm::tail(curline);
}
// Bump Map
if (algorithm::firstToken(curline) == "map_Bump" || algorithm::firstToken(curline) == "map_bump" || algorithm::firstToken(curline) == "bump")
{
tempMaterial.map_bump = algorithm::tail(curline);
}
}

// Deal with last material

// Push Back loaded Material
LoadedMaterials.push_back(tempMaterial);

// Test to see if anything was loaded
// If not return false
if (LoadedMaterials.empty())
return false;
// If so return true
else
return true;
}
};
}

// Main function
int main(int argc, char* argv[])
{
// Initialize Loader
objl::Loader myLoader;

// Load .obj File
bool loadout = myLoader.LoadFile("box_stack.obj");

// Check to see if it loaded

// If so continue
if (loadout)
{
// Create/Open e1Out.txt
std::ofstream file("e1Out.txt");

// Go through each loaded mesh and out its contents
for (int i = 0; i < myLoader.LoadedMeshes.size(); i++)
{
// Copy one of the loaded meshes to be our current mesh
objl::Mesh curMesh = myLoader.LoadedMeshes[i];

// Print Mesh Name
file << "Mesh " << i << ": " << curMesh.MeshName << "\n";

// Print Vertices
file << "Vertices:\n";

// Go through each vertex and print its number,
//  position, normal, and texture coordinate
for (int j = 0; j < curMesh.Vertices.size(); j++)
{
file << "V" << j << ": " <<
"P(" << curMesh.Vertices[j].Position.X << ", " << curMesh.Vertices[j].Position.Y << ", " << curMesh.Vertices[j].Position.Z << ") " <<
"N(" << curMesh.Vertices[j].Normal.X << ", " << curMesh.Vertices[j].Normal.Y << ", " << curMesh.Vertices[j].Normal.Z << ") " <<
"TC(" << curMesh.Vertices[j].TextureCoordinate.X << ", " << curMesh.Vertices[j].TextureCoordinate.Y << ")\n";
}

// Print Indices
file << "Indices:\n";

// Go through every 3rd index and print the
//	triangle that these indices represent
for (int j = 0; j < curMesh.Indices.size(); j += 3)
{
file << "T" << j / 3 << ": " << curMesh.Indices[j] << ", " << curMesh.Indices[j + 1] << ", " << curMesh.Indices[j + 2] << "\n";
}

// Print Material
file << "Material: " << curMesh.MeshMaterial.name << "\n";
file << "Ambient Color: " << curMesh.MeshMaterial.Ka.X << ", " << curMesh.MeshMaterial.Ka.Y << ", " << curMesh.MeshMaterial.Ka.Z << "\n";
file << "Diffuse Color: " << curMesh.MeshMaterial.Kd.X << ", " << curMesh.MeshMaterial.Kd.Y << ", " << curMesh.MeshMaterial.Kd.Z << "\n";
file << "Specular Color: " << curMesh.MeshMaterial.Ks.X << ", " << curMesh.MeshMaterial.Ks.Y << ", " << curMesh.MeshMaterial.Ks.Z << "\n";
file << "Specular Exponent: " << curMesh.MeshMaterial.Ns << "\n";
file << "Optical Density: " << curMesh.MeshMaterial.Ni << "\n";
file << "Dissolve: " << curMesh.MeshMaterial.d << "\n";
file << "Illumination: " << curMesh.MeshMaterial.illum << "\n";
file << "Ambient Texture Map: " << curMesh.MeshMaterial.map_Ka << "\n";
file << "Diffuse Texture Map: " << curMesh.MeshMaterial.map_Kd << "\n";
file << "Specular Texture Map: " << curMesh.MeshMaterial.map_Ks << "\n";
file << "Alpha Texture Map: " << curMesh.MeshMaterial.map_d << "\n";
file << "Bump Map: " << curMesh.MeshMaterial.map_bump << "\n";

// Leave a space to separate from the next mesh
file << "\n";
}

// Close File
file.close();
}
// If not output an error
else
{
// Create/Open e1Out.txt
std::ofstream file("e1Out.txt");

// Output Error
file << "Failed to Load File. May have failed to find it or it was not an .obj file.\n";

// Close File
file.close();
}

// Exit the program
return 0;
}
*/


// Demonstrates how to load and display an Wavefront OBJ file.
//Using triangles and normals as static object. No texture mapping.

//OBJ files must be triangulated!!!
//Non triangulated objects wont work!
//You can use Blender to triangulate

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include "freeglut.h" 
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

#define KEY_ESCAPE 27

using namespace std;


class Model_OBJ
{
public:
	Model_OBJ();
	float* Model_OBJ::calculateNormal(float* coord1, float* coord2, float* coord3);
	int Model_OBJ::load(char *filename);	// Loads the model
	void Model_OBJ::draw();					// Draws the model on the screen
	void Model_OBJ::release();				// Release the model

	float* normals;							// Stores the normals
	float* Faces_Triangles;					// Stores the triangles
	float* vertexBuffer;					// Stores the points which make the object
	long TotalConnectedPoints;				// Stores the total number of connected verteces
	long TotalConnectedTriangles;			// Stores the total number of connected triangles

};


#define POINTS_PER_VERTEX 3
#define TOTAL_FLOATS_IN_TRIANGLE 9
using namespace std;

Model_OBJ::Model_OBJ()
{
	this->TotalConnectedTriangles = 0;
	this->TotalConnectedPoints = 0;
}

float* Model_OBJ::calculateNormal(float *coord1, float *coord2, float *coord3)
{
	// calculate Vector1 and Vector2 
	float va[3], vb[3], vr[3], val;
	va[0] = coord1[0] - coord2[0];
	va[1] = coord1[1] - coord2[1];
	va[2] = coord1[2] - coord2[2];

	vb[0] = coord1[0] - coord3[0];
	vb[1] = coord1[1] - coord3[1];
	vb[2] = coord1[2] - coord3[2];

	// cross product 
	vr[0] = va[1] * vb[2] - vb[1] * va[2];
	vr[1] = vb[0] * va[2] - va[0] * vb[2];
	vr[2] = va[0] * vb[1] - vb[0] * va[1];

	// normalization factor 
	val = sqrt(vr[0] * vr[0] + vr[1] * vr[1] + vr[2] * vr[2]);

	float norm[3];
	norm[0] = vr[0] / val;
	norm[1] = vr[1] / val;
	norm[2] = vr[2] / val;

	return norm;
}


int Model_OBJ::load(char* filename)
{
	string line;
	ifstream objFile(filename);
	if (objFile.is_open())													// If obj file is open, continue
	{
		objFile.seekg(0, ios::end);										// Go to end of the file, 
		long fileSize = objFile.tellg();									// get file size
		objFile.seekg(0, ios::beg);										// we'll use this to register memory for our 3d model

		vertexBuffer = (float*)malloc(fileSize);							// Allocate memory for the verteces
		Faces_Triangles = (float*)malloc(fileSize*sizeof(float));			// Allocate memory for the triangles
		normals = (float*)malloc(fileSize*sizeof(float));					// Allocate memory for the normals

		int triangle_index = 0;												// Set triangle index to zero
		int normal_index = 0;												// Set normal index to zero

		while (!objFile.eof())											// Start reading file data
		{
			getline(objFile, line);											// Get line from file

			if (line.c_str()[0] == 'v')										// The first character is a v: on this line is a vertex stored.
			{
				line[0] = ' ';												// Set first character to 0. This will allow us to use sscanf

				sscanf(line.c_str(), "%f %f %f ",							// Read floats from the line: v X Y Z
					&vertexBuffer[TotalConnectedPoints],
					&vertexBuffer[TotalConnectedPoints + 1],
					&vertexBuffer[TotalConnectedPoints + 2]);

				TotalConnectedPoints += POINTS_PER_VERTEX;					// Add 3 to the total connected points
			}
			if (line.c_str()[0] == 'f')										// The first character is an 'f': on this line is a point stored
			{
				line[0] = ' ';												// Set first character to 0. This will allow us to use sscanf

				int vertexNumber[4] = { 0, 0, 0 };
				sscanf(line.c_str(), "%i%i%i",								// Read integers from the line:  f 1 2 3
					&vertexNumber[0],										// First point of our triangle. This is an 
					&vertexNumber[1],										// pointer to our vertexBuffer list
					&vertexNumber[2]);										// each point represents an X,Y,Z.

				vertexNumber[0] -= 1;										// OBJ file starts counting from 1
				vertexNumber[1] -= 1;										// OBJ file starts counting from 1
				vertexNumber[2] -= 1;										// OBJ file starts counting from 1



																			// Create triangles (f 1 2 3) from points: (v X Y Z) (v X Y Z) (v X Y Z).
																			// The vertexBuffer contains all verteces
																			// The triangles will be created using the verteces we read previously


				int tCounter = 0;
				for (int i = 0; i < POINTS_PER_VERTEX; i++)
				{
					Faces_Triangles[triangle_index + tCounter] = vertexBuffer[3 * vertexNumber[i]];
					Faces_Triangles[triangle_index + tCounter + 1] = vertexBuffer[3 * vertexNumber[i] + 1];
					Faces_Triangles[triangle_index + tCounter + 2] = vertexBuffer[3 * vertexNumber[i] + 2];
					tCounter += POINTS_PER_VERTEX;
				}


				// Calculate all normals, used for lighting

				float coord1[3] = { Faces_Triangles[triangle_index], Faces_Triangles[triangle_index + 1],Faces_Triangles[triangle_index + 2] };
				float coord2[3] = { Faces_Triangles[triangle_index + 3],Faces_Triangles[triangle_index + 4],Faces_Triangles[triangle_index + 5] };
				float coord3[3] = { Faces_Triangles[triangle_index + 6],Faces_Triangles[triangle_index + 7],Faces_Triangles[triangle_index + 8] };
				float *norm = this->calculateNormal(coord1, coord2, coord3);

				tCounter = 0;
				for (int i = 0; i < POINTS_PER_VERTEX; i++)
				{
					normals[normal_index + tCounter] = norm[0];
					normals[normal_index + tCounter + 1] = norm[1];
					normals[normal_index + tCounter + 2] = norm[2];
					tCounter += POINTS_PER_VERTEX;
				}

				triangle_index += TOTAL_FLOATS_IN_TRIANGLE;
				normal_index += TOTAL_FLOATS_IN_TRIANGLE;
				TotalConnectedTriangles += TOTAL_FLOATS_IN_TRIANGLE;
			}
		}
		objFile.close();														// Close OBJ file
	}
	else
	{
		cout << "Unable to open file";
	}
	return 0;
}

void Model_OBJ::release()
{
	free(this->Faces_Triangles);
	free(this->normals);
	free(this->vertexBuffer);
}

void Model_OBJ::draw()
{
	glEnableClientState(GL_VERTEX_ARRAY);						// Enable vertex arrays
	glEnableClientState(GL_NORMAL_ARRAY);						// Enable normal arrays
	glVertexPointer(3, GL_FLOAT, 0, Faces_Triangles);				// Vertex Pointer to triangle array
	glNormalPointer(GL_FLOAT, 0, normals);						// Normal pointer to normal array
	glDrawArrays(GL_TRIANGLES, 0, TotalConnectedTriangles);		// Draw the triangles
	glDisableClientState(GL_VERTEX_ARRAY);						// Disable vertex arrays
	glDisableClientState(GL_NORMAL_ARRAY);						// Disable normal arrays
}


Model_OBJ obj;
float g_rotation = 1.0f;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0, 1, 4, 0, 0, 0, 0, 1, 0);
	glPushMatrix();
	glRotatef(g_rotation, 0, 1, 0);
	//glRotatef(90, 0, 1, 0);
	//g_rotation++;
	if (g_rotation > 180.0f)
		g_rotation = 0.0f;
	else
		g_rotation += 0.05f;

	obj.draw();
	glPopMatrix();
	glutSwapBuffers();
}


void initialize()
{
	glMatrixMode(GL_PROJECTION);
	glViewport(0, 0, 640, 480);
	GLfloat aspect = (GLfloat)640 / 480;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, aspect, 1.0f, 500.0f);
	glMatrixMode(GL_MODELVIEW);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.1f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	GLfloat amb_light[] = { 0.1, 0.1, 0.1, 1.0 };
	GLfloat diffuse[] = { 0.6, 0.6, 0.6, 1 };
	GLfloat specular[] = { 0.7, 0.7, 0.3, 1 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb_light);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}


void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case KEY_ESCAPE:
		exit(0);
		break;
	default:
		break;
	}
}

int main(int argc, char **argv)
{

	// initialize and run program
	glutInit(&argc, argv);                                      // GLUT initialization
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);  // Display Mode
	glutInitWindowSize(640, 480);					// set window size
	glutCreateWindow("DHNC Lab4");								// create Window
	glutDisplayFunc(display);									// register Display Function
	glutIdleFunc(display);									// register Idle Function
	glutKeyboardFunc(keyboard);								// register Keyboard Handler
	initialize();
	obj.load("cessna.obj");
	glutMainLoop();												// run GLUT mainloop
	return 0;
}