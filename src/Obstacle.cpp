#include "Obstacle.h"
#include "Player.h"
#include "Defines.h"
#include "Camera.h"

void Obstacle::Update(float dt){
	this->sp.Update(dt);
	this->box.x += this->speed * dt * 100;

    if(this->box.x - Camera::pos.x + this->sp.GetWidth()< 0){
		this->isDead = true;
        this->spriteSound.Stop();
    }
}

bool Obstacle::IsDead(){
    return this->isDead;
}

void Obstacle::OpenSound(string fileName){
    this->spriteSound.Open(fileName);
}

void Obstacle::ChangeSpritesheet(string fileName, int frameCount, float frameTime){
    this->sp.Open(fileName);
    this->sp.SetFrameCount(frameCount);
    this->sp.SetFrameTime(frameTime);
    this->sp.SetClip(this->box.x, this->box.y, this->sp.GetWidth(), this->sp.GetHeight());
}
//
//Obstacle::Obstacle(float speed, bool canBlock, std::string obstacleName, std::string sprite, int frameCount, float frameTime) {
//	this->sp = Sprite(sprite,frameCount,frameTime);
//	this->speed = speed;
//	this->speed = speed + rand()%10/10;
//	this->obstacleName = obstacleName;
//	this->canBlock = canBlock;
//	this->isDead = false;
////    this->isSoundHappening = false;
//	this->layer = rand()%3 + 1;
//	this->subLayer = rand()%3 + 1;
//
//	this->spriteSound = Sound(-1);
//    this->captureSound = Sound(-1);
//
//	// ou seja, vai dar respawn se passar no teste
//	this->box.x = Player::player->box.x + 1200;
//    if(this->layer == LAYER_TOP)
//        this->box.y = ITEM_HEIGHT_L3;
//    if(this->layer == LAYER_MIDDLE)
//        box.y = ITEM_HEIGHT_L2;
//    if(this->layer == LAYER_BOTTON)
//        this->box.y = ITEM_HEIGHT_L1;
//
//    if(this->obstacleName == "menina"){
//        this->OpenXingamentoSound(rand()%11 + 1);
//    }
//
//	if(this->obstacleName == "menina" && rand()%100 < 20){
//		this->sp = Sprite("img/meninazumbi.png",frameCount,frameTime);
//		this->obstacleName = "meninaZumbi";
//		this->speed = 3.5;
//		this->OpenZombieSound(rand()%7+1);
//		this->captureSound = spriteSound;
//		this->captureSound.SetChannel(-1);
//		this->spriteSound.Play(rand()%2+1);
//	}
//
//    if(this->obstacleName == "menina" && this->speed == 0){
//
//    	if(rand()%100 > 50)
//            this->sp = Sprite("img/parado1.png", 1, 1);
//        else
//            this->sp = Sprite("img/parada.png", 6, 0.2);
//
//    	this->obstacleName = "parado";
//    	this->OpenXingamentoSound(rand()%11+1);
//    }
//
//	if(this->obstacleName == "menina" && rand()%100 < 50){
//        this->sp = Sprite("img/menino.png",frameCount,frameTime);
//        this->obstacleName = "menino";
//        this->OpenXingamentoSound(rand()%11 + 1);
//        this->captureSound.SetChannel(-1);
//    }
//
//    this->box.y -= (this->subLayer - 3) * 26;
//}
//
//Obstacle::Obstacle(float speed, bool canBlock, std::string obstacleName, std::string sprite, int frameCount, float frameTime,
//		int layer, int subLayer) {
//
//	this->sp = Sprite(sprite,frameCount,frameTime);
//	this->speed = speed;
//	if(this->speed != 0)
//		this->speed += rand()%10/10;
//
//	this->obstacleName = obstacleName;
//	this->canBlock = canBlock;
//	this->isDead = false;
////	this->isSoundHappening = false;
//
//	this->layer = layer;
//	this->subLayer = subLayer;
//
//	this->spriteSound = Sound(-1);
//    this->captureSound = Sound(-1);
//
//
//	// ou seja, vai dar respawn se passar no teste
//	this->box.x = Player::player->box.x + 1200;
//
//    if(this->layer == LAYER_TOP)
//        this->box.y = ITEM_HEIGHT_L3;
//
//    if(layer == LAYER_MIDDLE)
//        this->box.y = ITEM_HEIGHT_L2;
//
//    if(this->layer == LAYER_BOTTON)
//        this->box.y = ITEM_HEIGHT_L1;
//
//    // tem q ser tipo assim os outros tbm, dps alguem arruma ai
//    this->box.y += this->sp.GetHeight();
//    this->box.y -= (this->subLayer - 3) * 26;
//
//    if(this->obstacleName == "manifestacao" && this->subLayer == SUBLAYER_BOTTON){
//    	this->sp = Sprite("img/manifest.png", 6, 0.2);
//    	spriteSound.Open("audio/manifestacao_11s.wav");
////    	spriteSound.PlayArbitraryFadeIn(1, 2);
//    	spriteSound.Play(1);
//    }
//	if(this->obstacleName == "cano"){
//		this->sp = Sprite("img/cano.png",frameCount,frameTime);
//		this->OpenGotaSound(rand()%3 + 1);
//		spriteSound.Play(rand()%2+1);
//	}
//}
//
//Obstacle::Obstacle(float speed, bool canBlock, std::string obstacleName, std::string sprite, int frameCount, float frameTime, int layer)
//{
//	sp = Sprite(sprite,frameCount,frameTime);
//	this->speed = speed;
//	speed = speed + rand()%10/10;
//	this->obstacleName = obstacleName;
//	this->canBlock = canBlock;
//	this->isDead = false;
//
//	this->layer = layer;
//	subLayer = rand()%3 + 1;
//
//	this->spriteSound = Sound(-1);
//    this->captureSound = Sound(-1);
//
//
//	// ou seja, vai dar respawn se passar no teste
//	this->box.x = Player::player->box.x + 1200;
//
//    if(this->layer == LAYER_TOP)
//        this->box.y = ITEM_HEIGHT_L3;
//
//    if(this->layer == LAYER_MIDDLE)
//        this->box.y = ITEM_HEIGHT_L2;
//
//    if(this->layer == LAYER_BOTTON)
//        this->box.y = ITEM_HEIGHT_L1;
//
//    if(this->obstacleName == "lixeira"){
//        this->subLayer = 3;
//        this->box.y += 20;
//        this->captureSound.Open("audio/lixeira.wav");
//    }
//
//    this->box.y -= (this->subLayer - 3) * 26;
//}
//
//Obstacle::~Obstacle(){
//
//}
//
//void Obstacle::Render(){
//    if(this->obstacleName == "cano"){
//    	this->sp.Render(this->box.x - Camera::pos.x, this->box.y - Camera::pos.y - 250);
//
//    }
//    else {
//    	if(this->speed >= 0)
//    		this->sp.Render(this->box.x - Camera::pos.x, this->box.y - Camera::pos.y);
//		else
//			this->sp.RenderFlipped(this->box.x - Camera::pos.x, this->box.y - Camera::pos.y);
//    }
//}
//
//void Obstacle::NotifyCollision(GameObject* other){
//    if(other->Is("Coffee") && this->obstacleName != "manifestacao"){
//    	this->speed = -5;
//
//    	if(this->obstacleName == "meninaZumbi"){
//    		this->sp = Sprite("img/menina.png", 6, 0.2);
//    		//obstacleName = "menina";
//    		this->speed = 8;
//    	}
//    }
//
//    if(other->Is("Player") || other->Is("Coffee")){
//        this->captureSound.Play(1);
//    }
//}
//
//bool Obstacle::Is(std::string type){
//	return (type == obstacleName);
//}
//
//void Obstacle::OpenZombieSound(int num){
//    switch (num){
//    case 0:{
//        this->spriteSound.Open("audio/Zumbi0.ogg");
//        break;
//    }
//    case 1:{
//        this->spriteSound.Open("audio/Zumbi2.ogg");
//        break;
//    }
//    case 2:{
//        this->spriteSound.Open("audio/Zumbi3.ogg");
//        break;
//    }
//    case 3:{
//        this->spriteSound.Open("audio/Zumbi6.ogg");
//        break;
//    }
//    case 4:{
//        this->spriteSound.Open("audio/Zumbi7.ogg");
//        break;
//    }
//    case 5:{
//        this->spriteSound.Open("audio/Zumbi8.ogg");
//        break;
//    }
//    case 6:{
//        this->spriteSound.Open("audio/Zumbi9.ogg");
//        break;
//    }
//    }
//}
//
//void Obstacle::OpenXingamentoSound(int num){
//    switch(num){
//    case 1:{
//        this->captureSound.Open("audio/Oxe2.wav");
//        break;
//    }
//    case 2:{
//        this->captureSound.Open("audio/Odoida3.wav");
//        break;
//    }
//    case 3:{
//        this->captureSound.Open("audio/Oxe1.wav");
//        break;
//    }
//    case 4:{
//        this->captureSound.Open("audio/Odoida2.wav");
//        break;
//    }
//    case 5:{
//        this->captureSound.Open("audio/Odoida3.wav");
//        break;
//    }
//    case 6:{
//        this->captureSound.Open("audio/Ai6.wav");
//        break;
//    }
//    case 7:{
//        this->captureSound.Open("audio/Ai5.wav");
//        break;
//    }case 8:{
//        this->captureSound.Open("audio/Uh2.wav");
//        break;
//    }case 9:{
//        this->captureSound.Open("audio/Ai3.wav");
//        break;
//    }
//    case 10:{
//        this->captureSound.Open("audio/Ai2.wav");
//        break;
//    }
//    case 11:{
//        this->captureSound.Open("audio/Ai1.wav");
//        break;
//    }
//    }
//}
//
//void Obstacle::OpenGotaSound(int num){
//    switch(num){
//    case 1:{
//        this->spriteSound.Open("audio/gota1.wav");
//        break;
//    }
//    case 2:{
//        this->spriteSound.Open("audio/gota2.wav");
//        break;
//    }
//    case 3:{
//        this->spriteSound.Open("audio/gota3.wav");
//        break;
//    }
//    }
//}
