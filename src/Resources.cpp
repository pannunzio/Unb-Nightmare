/*
 * Resources.cpp
 *
 *  Created on: 23 de mar de 2016
 *      Author: Caio
 */

#include "Resources.h"
#include "Game.h"
#include <SDL.h>
#include <SDL_Image.h>
#include <iostream>
#include <string>
#include <sstream>
// inicializando
std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;
std::unordered_map<std::string, Mix_Music*> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable;
std::unordered_map<std::string, TTF_Font*> Resources::fontTable;

Resources::Resources() {

}
//*********************************************************************//
//Fun��o: Resources::GetImage(string file)**********************************************//
//Retorno: SDL_Texture*******************************************************//
//Parametros: string file**************************************************//
//Descri��o: procura se imagem ja esta no tablemap, caso nao, insere***************************************//
//****************************************************************//
SDL_Texture* Resources::GetImage(std::string file){

	auto busca = imageTable.find(file);
	if(busca != imageTable.end()){
		std::cout << "ImageTable : imagem encontrada" << std::endl;
		return busca->second;
	}
	SDL_Renderer* renderer = Game::GetInstance().GetRenderer();
	if(!renderer)
			std::cout << "renderer bugado" << std::endl;
	SDL_Texture* texture = IMG_LoadTexture(renderer,(const char*)file.c_str()); // precisa ser const char
	if(!texture)
		std::cout << "Error ao carregar texture do resources" << std::endl;
	imageTable.emplace(file,texture);
	return texture;
}
//*********************************************************************//
//Fun��o: Resources::ClearImages()************************************//
//Retorno: void******************************************************//
//Parametros: void**************************************************//
//Descri��o: destroi texture por texture***************************//
//****************************************************************//
void Resources::ClearImages(){
	for (std::unordered_map<std::string, SDL_Texture*>::iterator it = imageTable.begin(); it != imageTable.end(); ++it)
		SDL_DestroyTexture(it->second);
	imageTable.clear();
}
Resources::~Resources() {

}



void Resources::ClearMusic(){
	for (std::unordered_map<std::string, Mix_Music*>::iterator it = musicTable.begin(); it != musicTable.end(); ++it)
		Mix_FreeMusic(it->second);
	musicTable.clear();

}

Mix_Music* Resources::GetMusic(std::string file) {
	auto busca = musicTable.find(file);
	if(busca != musicTable.end()){
		std::cout << "ImageTable : musica encontrada" << std::endl;
		return busca->second;
	}
	Mix_Music* music = Mix_LoadMUS((const char*)file.c_str()); // precisa ser const char
	if(!music)
		std::cout << "Error ao carregar texture do resources" << std::endl;
	//imageTable.emplace(file,texture);
	musicTable.emplace(file,music);
	return music;
}

void Resources::ClearSound(){
	for (std::unordered_map<std::string, Mix_Chunk*>::iterator it = soundTable.begin(); it != soundTable.end(); ++it)
		Mix_FreeChunk(it->second);
	soundTable.clear();

}

Mix_Chunk* Resources::GetSound(std::string file) {
	auto busca = soundTable.find(file);
	if(busca != soundTable.end()){
		std::cout << "SoundTable : musica encontrada" << std::endl;
		return busca->second;
	}
	Mix_Chunk* sound = Mix_LoadWAV((const char*)file.c_str()); // precisa ser const char
	if(!sound)
		std::cout << "Error ao carregar sound do resources" << std::endl;
	soundTable.emplace(file,sound);
	return sound;
}


void Resources::ClearFont(){
	for (std::unordered_map<std::string, TTF_Font*>::iterator it = fontTable.begin(); it != fontTable.end(); ++it)
	   TTF_CloseFont(it->second);
	fontTable.clear();

}

TTF_Font* Resources::GetFont(char* file, int fontSize) {
    std::stringstream chave;
    chave << file << fontSize;
    std::unordered_map<string, TTF_Font*>::const_iterator indice = fontTable.find(chave.str());

    if (indice == fontTable.end()){
        TTF_Font* font = TTF_OpenFont(file, fontSize);
        fontTable.emplace(chave.str(), font);
        return font;
    } else {
        return indice->second;
    }
    return nullptr;
}
