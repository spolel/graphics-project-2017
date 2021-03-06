#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>
#include <cmath>

#include "objloader.hpp"

// Very, VERY simple OBJ loader.
// Here is a short list of features a real function would provide :
// - Binary files. Reading a model should be just a few memcpy's away, not parsing a file at runtime. In short : OBJ is not very great.
// - Animations & bones (includes bones weights)
// - Multiple UVs
// - All attributes should be optional, not "forced"
// - More stable. Change a line in the OBJ file and it crashes.
// - More secure. Change another line and you can inject code.
// - Loading from memory, stream, etc

bool loadOBJ(
	const char * path,
        std::vector<Point3d> & out_vertices,
        std::vector<Point2d> & out_uvs,
        std::vector<Point3d> & out_normals,
        Point3d center
){
	printf("Loading OBJ file %s...\n", path);

	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<Point3d> temp_vertices;
    std::vector<Point2d> temp_uvs;
    std::vector<Point3d> temp_normals;

    float min_x = std::numeric_limits<float>::max();
    float min_y = std::numeric_limits<float>::max();
    float min_z = std::numeric_limits<float>::max();

    float max_x = std::numeric_limits<float>::min();
    float max_y = std::numeric_limits<float>::min();
    float max_z = std::numeric_limits<float>::min();

    float cen_x;
    float cen_y;
    float cen_z;


	FILE * file = fopen(path, "r");
	if( file == NULL ){
		printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
		getchar();
		return false;
	}

	while( 1 ){

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader

		if ( strcmp( lineHeader, "v" ) == 0 ){
                        float vx, vy, vz;
                        fscanf(file, "%f %f %f\n", &vx, &vy, &vz );
                        if (vx < min_x)
                        {
                            min_x = vx;
                        }
                        if (vx > max_x)
                        {
                            max_x = vx;
                        }
                        if (vy < min_y)
                        {
                            min_y = vy;
                        }
                        if (vy > max_y)
                        {
                            max_y = vy;
                        }
                        if (vz < min_z)
                        {
                            min_z = vz;
                        }
                        if (vz > max_z)
                        {
                            max_z = vz;
                        }

                        Point3d vertex(vx, vy, vz);
            temp_vertices.push_back(vertex);
                }else if ( strcmp( lineHeader, "vt" ) == 0 ){
                        float uvx, uvy;
                        fscanf(file, "%f %f\n", &uvx, &uvy );
//                        uvy = -uvy; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
                        Point2d uv(uvx, uvy);
			temp_uvs.push_back(uv);
		}else if ( strcmp( lineHeader, "vn" ) == 0 ){
                        float nx, ny, nz;
                        fscanf(file, "%f %f %f\n", &nx, &ny, &nz);
                        Point3d normal(nx, ny, nz);
			temp_normals.push_back(normal);
		}else if ( strcmp( lineHeader, "f" ) == 0 ){
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
                        int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
			if (matches != 9){
				printf("File can't be read by our simple parser :-( Try exporting with other options\n");
                                fclose(file);
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices    .push_back(uvIndex[0]);
			uvIndices    .push_back(uvIndex[1]);
			uvIndices    .push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}else{
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
                        fgets(stupidBuffer, 1000, file);
		}

	}

	// For each vertex of each triangle
	for( unsigned int i=0; i<vertexIndices.size(); i++ ){

		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
        unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];

		// Get the attributes thanks to the index
                Point3d vertex = temp_vertices[ vertexIndex-1 ];
                Point2d uv = temp_uvs[ uvIndex-1 ];
                Point3d normal = temp_normals[ normalIndex-1 ];

		// Put the attributes in buffers
		out_vertices.push_back(vertex);
        out_uvs     .push_back(uv);
		out_normals .push_back(normal);

	}
	fclose(file);

    cen_x = (max_x - min_x)/2;
    cen_y = (max_y - min_y)/2;
    cen_z = (max_z - min_z)/2;

    center = Point3d(cen_x, cen_y, cen_z);

	return true;
}

void vecPoint2dToFloat(std::vector<Point2d> &_vec, std::vector<GLfloat> &_out) {
    _out.clear();
    for(auto i = _vec.begin(); i != _vec.end(); ++i) {
        _out.push_back(i->x());
        _out.push_back(i->y());
    }
}

void vecPoint3dToFloat(std::vector<Point3d> &_vec, std::vector<GLfloat> &_out) {
    _out.clear();
    for(auto i = _vec.begin(); i != _vec.end(); ++i) {
        _out.push_back(i->x());
        _out.push_back(i->y());
        _out.push_back(i->z());
    }
}
