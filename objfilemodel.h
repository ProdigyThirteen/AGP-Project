#pragma once

#define _XM_NO_INTRINSICS_
#define XM_NO_ALIGNMENT

#include <d3d11.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include <stdio.h>
#include <string>
#include <vector>

class ObjFileModel
{
private:
	ID3D11Device*           pD3DDevice;
	ID3D11DeviceContext*    pImmediateContext;



//////////////////////////////////////////////////

	int loadfile(char* fname);

	char* fbuffer;
	long fbuffersize; // filesize
	size_t actualsize; // actual size of loaded data (can be less if loading as text files as ASCII CR (0d) are stripped out)

//////////////////////////////////////////////////

	void parsefile();
	bool getnextline() ;
	bool getnexttoken(int& tokenstart, int& tokenlength);

	unsigned int  tokenptr;

//////////////////////////////////////////////////

	bool createVB();

	ID3D11Buffer* pVertexBuffer; 

public:

	struct xyz { float x, y, z; };	//used for vertices and normals during file parse
	struct xy { float x, y; };		//used for texture coordinates during file parse

	// Define model vertex structure
	struct MODEL_POS_COL_TEX_NORM_VERTEX
	{
		DirectX::XMFLOAT3 Pos;
		DirectX::XMFLOAT4 Col;
		DirectX::XMFLOAT2 TexCoord;
		DirectX::XMFLOAT3 Normal;
	};


	std::string filename;

	ObjFileModel(char* filename, ID3D11Device* device, ID3D11DeviceContext* context);
	~ObjFileModel();

	void Draw(void);

	std::vector <xyz> position_list;		// list of parsed positions
	std::vector <xyz> normal_list;		// list of parsed normals
	std::vector <xy> texcoord_list;		// list of parsed texture coordinates
	std::vector <int> pindices, tindices, nindices; // lists of indicies into above lists derived from faces

	MODEL_POS_COL_TEX_NORM_VERTEX* vertices;
	unsigned int numverts;
};


