/*
 * TileMap.cpp
 *
 *  Created on: 21 de mar de 2016
 *      Author: Caio
 */

#include "TileMap.h"
#include <cstdio>

//*****************************************************************//
//Fun��o: TileMap::Load(std::string file)*************************//
//Retorno: void**************************************************//
//Parametros: string file***************************************//
//Descri��o: carrega o arquivo e cria a matrix do tile*********//
//************************************************************//
void TileMap::Load(std::string file){
	std::cout << "TileMap::Load" << endl;
	FILE* arq = fopen(file.c_str(), "r");
	if(!arq)
			std::cout << "falha ao abrir arquivo: "  << file << std::endl;
	fscanf(arq, "%i, %i, %i,", &mapWidth, &mapHeight, &mapDepth);
	std::cout << "ROW COLUMNS DEPTH from file" << endl << mapWidth << mapHeight << mapDepth << endl;
	tileMatrix.resize(mapWidth*mapHeight*mapDepth);
	for(int k = 0 ; k< mapDepth; k++)
		for(int j = 0 ; j < mapHeight; j++){
			for(int i = 0; i< mapWidth; i++){
				//std::cout << "entrou no for do load" << std::endl;
				//fscanf(arq, "%i,", &tileMatrix[i + j*mapHeight + k*mapHeight*mapDepth]);
				fscanf(arq, "%d,", &At(i,j,k)); // isso ta bugando
				//std::cout << "TileMatrix(" << i << ", "<< j << ", " << k << ")" << At(i,j,k) << endl; // debugando
			}
		//std::cout << std::endl;
		}
	std::cout << "Tile map succesfuly read" << std::endl;
	//PrintMap();
}

//*****************************************************************//
//Fun��o: TileMap::At(int x, int y, int z)************************//
//Retorno: int&**************************************************//
//Parametros: int x, int y, int z*******************************//
//Descri��o: calcular posicao na matrix************************//
//************************************************************//
int& TileMap::At(int x, int y, int z){
	//std::cout << "Index:" <<(x + y*mapWidth + z*mapHeight*mapWidth) << "(" << x << ", " << y << ", " << z << ")"
		//	<< tileMatrix[x + y*mapWidth + z*mapHeight*mapWidth] << std::endl;
	return tileMatrix[x + y*mapWidth + z*mapHeight*mapWidth];
}

void TileMap::PrintMap(){

	for(int k = 0; k < mapDepth; k++)
		for(int j = 0; j < mapHeight; j++){
			for(int i =0 ; i < mapWidth; i++){
				if(At(i,j,k) <10)
					std::cout << "0";
				std::cout << At(i,j,k) << ",";
			}
			std::cout << std::endl;
		}
}
	//*************************************************************************************//
//Fun��o: TileMap::RenderLayer(int layer, int cameraX = 0 , int cameraY = 0)**********//
//Retorno: void**********************************************************************//
//Parametros: int layer, int cameraX = 0 , int cameraY = 0**************************//
//Descri��o: renderiza uma camada do mapa tile a tile******************************//
//********************************************************************************//
void TileMap::RenderLayer(int layer, int cameraX, int cameraY){
	//std::cout << "TileMap::RenderLayer" << std::endl;
	for(int j = 0; j < mapHeight; j++)
		for(int i = 0; i< mapWidth; i++){
			tileSet->Render(At(i,j,layer),
							tileSet->GetTileWidth()*i
							- cameraX*(layer +1), tileSet->GetTileHeight()*j - cameraY*(layer+1));
			//std::cout << "AT(i,j,layer)" << At(i,j,layer) << endl;

		}
	//std::cout << "terminoouuuuuu o render layer" << std::endl;
}
//*****************************************************************//
//Fun��o: TileMap::Render(int cameraX = 0, int cameraY = 0)*******//
//Retorno: void**************************************************//
//Parametros: int cameraX = 0, int cameraY = 0******************//
//Descri��o: renderiza todas as camadas do mapa****************//
//************************************************************//
void TileMap::Render(int cameraX, int cameraY){
	for(int i = 0;i < mapDepth; i++){
		RenderLayer(i, cameraX, cameraY);
	}
}


//*********************************************************************//
//Fun��o: CONSTRUTOR**************************************************//
//Retorno: N/A*******************************************************//
//Parametros: TileSet* tileSet**************************************//
//Descri��o: constroi o TileMap ja setando o tileSet***************//
//****************************************************************//
TileMap::TileMap(std::string file, TileSet* ttileSet) {
	tileSet = ttileSet;
	Load(file);
}
//*********************************************************************//
//Fun��o: DESTRUTOR***************************************************//
//Retorno: N/A*******************************************************//
//Parametros: TileSet* tileSet**************************************//
//Descri��o: destroi o TileMap*************************************//
//****************************************************************//
TileMap::~TileMap() {

}
//*********************************************************************//
//Fun��o: GetWidth(), GetHeight(), GetDepth()***************************************************//
//Retorno: int dos gets*******************************************************//
//Parametros: void**************************************//
//Descri��o: getters*************************************//
//****************************************************************//
int TileMap::GetWidth(){
	return mapWidth;
}
int TileMap::GetHeight(){
		return mapHeight;
}
int TileMap::GetDepth(){
		return mapDepth;
}

//*********************************************************************//
//Fun��o: TileMap::SetTileMap(TileSet* tileSet)***************************************************//
//Retorno: void*******************************************************//
//Parametros: TileSet* tileset**************************************//
//Descri��o: setter*************************************//
//****************************************************************//
void TileMap::SetTileSet(TileSet* ttileSet){
	tileSet = ttileSet;
}