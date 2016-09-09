#include "Obstacle.h"
#include "Manifestacao.h"
#include "Player.h"
#include "Camera.h"

Manifestacao::Manifestacao(){
    this->sp = Sprite("img/manifest.png", 6, 0.2);
	this->speed = 2 + rand()%10/10;
	this->canBlock = true;
	this->isDead = false;
	this->layer = LAYER_MIDDLE;
	this->subLayer = SUBLAYER_BOTTON;
	this->spriteSound = Sound(-1);
	this->isCollidingWithPlayer = false;

	this->box.x = Player::player->box.x + 1200;

    this->box.y = ITEM_HEIGHT_L2 + 30;
    this->box.y -= (this->subLayer - 3) * 26;

    spriteSound.Open("audio/manifestacao_11s.wav");
    spriteSound.Play(1);
}

Manifestacao::~Manifestacao(){
    spriteSound.Stop(2);
}

void Manifestacao::Render(){
    cout<< "manifest render" << endl;
    this->sp.Render(this->box.x - Camera::pos.x, this->box.y - Camera::pos.y - 120);
}

void Manifestacao::NotifyCollision(GameObject* other){
    if(!other->Is("Player"))
        this->isCollidingWithPlayer = false;
    else
        this->isCollidingWithPlayer = true;
    //manifestacao nao faz nada, fica la de boa na dela ,manifestando e atrapalhando o coredor
}

bool Manifestacao::Is(std::string type){
    return type == "Manifestacao";
}

int Manifestacao::GetLayer(){
    return this->layer;
}

int Manifestacao::GetSublayer(){
    if(Player::player != nullptr)
        return Player::player->GetSublayer();
    else
        return SUBLAYER_BOTTON;
}