#include <cstdlib>
#include <sstream>
#include "Game.h"
#include "Player.h"
#include "InputManager.h"
#include "Camera.h"
#include "Text.h"
#include "Bullet.h"
#include "Defines.h"

Player* Player::player = nullptr;
int Player::coffee_ammo = 0;

Player::Player(float x, float y) : sp("img/playerRunning.png", 6, 0.09){
	this->baseX = (int)x;
	this->subLayer = SUBLAYER_MIDDLE;
	this->layer = LAYER_MIDDLE;
	this->box.Centralize(x,y,sp.GetWidth(),sp.GetHeight());
	this->targetSpeed = speed = PLAYER_NORMAL_SPEED;
	this->acceleration = 1.5;
	this->isRightPosition = true;
	this->powerUp = NONE;

	this->movementState = RUNNING;
    this->isColliding = false;
    this->wasColliding = false;
    this->isPassingMapObject = false;
    this->isIndestructible = false;
	this->hud = Text("font/ComicNeue_Bold.otf", 28, SOLID, "Coffee: 0", TEXT_WHITE, 40,50);
	this->itemEffect = Timer();
    this->powerupMusic = Sound(1);
    this->isPlayingMusic = false;

    this->coffee_ammo = 20;
	std::cout << "Player Construido" << std::endl;


	//TESTES
	this->layer = rand()%3 +1;
//	layer = LAYER_BOTTON;

	this->player = this;
}

Player::~Player() {
	this->player = nullptr;
}

void Player::Update(float dt){
	//atualiza o sprite
	this->sp.Update(dt);

	Movement(); // faz os movimentos do input
    CheckEndPowerupEffects(dt);

    cout << "player box relativo: " << box.x - Camera::pos.x << endl;
    cout << "player.x: " << box.x << endl;
    cout << "Camera::pos.x: " << Camera::pos.x << endl;
    cout << "basex: " << baseX << endl;
	//colocando na posicao certa o player
	float diff = this->box.x - Camera::pos.x;
	if(diff > baseX + DELTA_ACCEPT &&
       baseX - DELTA_ACCEPT > diff ){
       cout << "player alinhado!" << endl;
       this->isRightPosition = true;
       box.x += abs(diff - baseX);//alinha para o valor correto o player
    }else{
		this->isRightPosition = false;
    }

    //Volta a velocidade para o padrão após colisão
    CheckCollisionToResetSpeed();
    AdjustSpeed(dt);
    SetPositionToMovementState(dt);

	//atira cafe
	if(InputManager::GetInstance().KeyPress(SDLK_SPACE)){
		Shoot();
	}

    AdjustGoingUpOrDown();

	this->isColliding = false;
    this->isPassingMapObject = false;
}

void Player::Render(){
	this->sp.Render((int)(this->box.x - Camera::pos.x), (int)(this->box.y - Camera::pos.y));
	this->RenderHud();
	this->SetSpriteScale();
}

bool Player::IsDead(){
	// camera passou player
	if(Camera::pos.x + 30 > pos.x + sp.GetWidth()){
		this->player = nullptr;
		cout<<"TESTE"<<endl;
		return true;
	}
	return false; // retornar true se tiver camera passou, ou se o tempo acabou
	//isso pode ser feito pelo state data.
}

void Player::NotifyCollision(GameObject* other){
    //cout<< "collision with obstacle1" << endl;
    if(other->Is("menina") || other->Is("meninaZumbi") || other->Is("lixeira") || other->Is("parado") || other->Is("menino")){
        if(!isIndestructible){
            this->isColliding = true;
            this->wasColliding = true;
            this->SetTargetSpeed(0.0);
        } else {
            if (this->subLayer == 3){
                this->subLayer--;
            } else if (this->subLayer == 1){
                this->subLayer++;
            }
        }
    }
    if(other->Is("manifestacao")){
        if(this->isIndestructible){
            this->powerUp = NONE;
            cout << "manifest STOP" << endl;
            if(this->powerupMusic.IsPlaying())
                cout << "manifest STOP 222" << endl;
            this->powerupMusic.Stop();
            this->ChangeSpriteSheet("img/playerRunning.png", 6);
            this->isIndestructible = false;
        }

        this->isColliding = true;
        this->wasColliding = true;
        this->speed = 2;

        // se ficar apertando vai mais rapido
        if(InputManager::GetInstance().KeyPress(SDLK_d))
        	this->box.x += 20;
    }

    if(other->Is("COFFEE")){
        this->coffee_ammo++;
    }

    if(other->Is("SKATE")){
        if(!this->isPlayingMusic && this->powerUp != SKATE){
            this->powerupMusic.Open("audio/skate.ogg");
            this->powerupMusic.Play(1);
            this->powerupMusic.SetVolume(180);
            cout << "PLAY SKATE AUDIO" << endl;
        }

        if(this->powerupMusic.IsPlaying()){
            cout << "is playing SKATE" << endl;
        }

        this->SetTargetSpeed(PLAYER_SKATE_SPEED);
        this->powerUp = SKATE;
        this->itemEffect.Restart();
        this->ChangeSpriteSheet("img/playerskating.png", 3);

    }

    if(other->Is("GGLIKO")){
//        this->speed = 3;
        if(this->isIndestructible){
            this->powerUp = NONE;
            this->powerupMusic.Stop();
            cout << "ggliks stop" << endl;
            this->ChangeSpriteSheet("img/playerRunning.png", 6);
            this->isIndestructible = false;
        }
        this->SetTargetSpeed(PLAYER_SLOW_SPEED);
        this->speed = 3.5;
        this->itemEffect.Restart();
        this->powerUp = PowerUp::COMIDA;
    }

    //caca de pombo
    if(other->Is("Caca")){
        if(this->isIndestructible){
            this->powerUp = NONE;
            this->powerupMusic.Stop();
            cout << "caca stop" << endl;
            this->ChangeSpriteSheet("img/playerRunning.png", 6);
            this->isIndestructible = false;
        }
//        this->SetTargetSpeed(PLAYER_SLOW_SPEED);
        this->speed = 4;
        this->itemEffect.Restart();
        this->powerUp = PowerUp::CACA_DE_POMBO;
    }

    if(other->Is("Escada")){
        this->isPassingMapObject = true;
    }

    if(other->Is("Agua")){
//        this->speed = 3;
        if(this->isIndestructible){
            this->powerUp = NONE;
            this->powerupMusic.Stop();
            cout << "water stop" << endl;
            this->ChangeSpriteSheet("img/playerRunning.png", 6);
            this->isIndestructible = false;
        }
//        this->SetTargetSpeed(PLAYER_SLOW_SPEED);
        this->speed = 3.5;
        this->itemEffect.Restart();
    }
        if(this->powerupMusic.IsPlaying()){
            cout << "is SURVIVED" << endl;
        }
}

bool Player::Is(std::string type){
	return (type == "Player");
}

bool Player::IsTargetSpeed(float targetSpeed){
	if(targetSpeed <=0) // se algo a levar para tras
		this->speed = targetSpeed;
	if(abs(this->speed - targetSpeed) <= 0.005)
		return true;
	return false;
}

void Player::SetTargetSpeed(float targetSpeed){
    this->targetSpeed = targetSpeed;
}

float Player::GetSpeed(){
	return this->speed;
}

float Player::GetAcceleration(){
	return this->acceleration;
}

void Player::SetAcceleration(float acceleration){
	this->acceleration = acceleration;
}

void Player::StopSound(){
}

bool Player::IsRightPosition(){
	return this->isRightPosition;
}

void Player::Movement(){
	this->pos = this->box.CenterPos();

	if(this->subLayer > 3)
		this->subLayer = 3;
	if(this->subLayer < 1)
		this->subLayer = 1;

//	if(InputManager::GetInstance().KeyPress(SDLK_a)){
//		std::cout << "DEBUG\n" << std::endl;
//		std::cout << "-------------PLayer---------------------"  << std::endl;
//		std::cout << "Layer: " << layer  << std::endl;
//		std::cout << "suLayer: " << subLayer << std::endl;
//		std::cout << "camera: "<< Camera::pos.x <<std::endl;
//		std::cout << "player: "<<pos.x + sp.GetWidth() <<std::endl;
//	}
//
//	if(InputManager::GetInstance().KeyPress(SDLK_l))
//		targetSpeed = 7.5;
//	// exemplo de diminuir velocidade
//	if(InputManager::GetInstance().KeyPress(SDLK_j))
//		targetSpeed =4.5;
//	// exemplo de velocidade voltou ao normal
//	if(InputManager::GetInstance().KeyPress(SDLK_k))
//		targetSpeed =5;


	//movimento de sublayer
	if(InputManager::GetInstance().KeyPress(SDLK_w)){
		if(this->subLayer <= 2)
			this->subLayer++;
    }

	if(InputManager::GetInstance().KeyPress(SDLK_s)){
		if(this->subLayer >= 2)
			this->subLayer--;
	}

    if(this->layer == LAYER_TOP)
        this->box.y = ITEM_HEIGHT_L3;

    if(this->layer == LAYER_MIDDLE)
        this->box.y = ITEM_HEIGHT_L2;

    if(this->layer == LAYER_BOTTON)
        this->box.y = ITEM_HEIGHT_L1;

    this->box.y = this->box.y - (this->subLayer - 3) * 26;

    if(this->powerUp == PowerUp::NONE){

        if(this->subLayer == SUBLAYER_TOP){

            if(this->layer == LAYER_MIDDLE || this->layer == LAYER_BOTTON)
                if(InputManager::GetInstance().KeyPress(UP_ARROW_KEY) && this->isPassingMapObject){
                    this->layer++;
                    this->subLayer = SUBLAYER_TOP;
                    this->movementState = GOING_UP;
                }

            if(this->layer == LAYER_TOP|| this->layer == LAYER_MIDDLE)
                if(InputManager::GetInstance().KeyPress(DOWN_ARROW_KEY) && isPassingMapObject){
                    this->layer--;
                    this->subLayer = SUBLAYER_TOP;
                    this->movementState = GOING_DOWN;
                }
        }
    }
}

void Player::Shoot(){
	Vec2 shootPos = box.CenterPos();

	if(this->coffee_ammo > 0){
		Bullet* coffee = new Bullet(shootPos.x, shootPos.y, 10, "img/coffee.png", 3, 0.3, false, "Coffee");
		coffee->SetLayers(this->layer, this->subLayer); // para renderizar corretamente
		Game::GetInstance().GetCurrentState().AddObject(coffee);
		coffee_ammo--;
	}
}

void Player::RenderHud(){
    std::stringstream hudString;
    hudString << "Coffee: " << coffee_ammo;
    this->hud.SetText(hudString.str());
	this->hud.Render(0, 0);

}

void Player::SetSpriteScale(){
    if(this->subLayer == 3)
    	this->sp.SetScale(0.95);
    if(this->subLayer == 2)
        this->sp.SetScale(1);
    if(this->subLayer == 1)
        this->sp.SetScale(1.05);
}

bool Player::IsIndestructible(){
    return this->isIndestructible;
}

void Player::ChangeSpriteSheet(string file, int frameCount){
    this->sp.Open(file);
    this->sp.SetFrameCount(frameCount);
    this->sp.SetClip(this->box.x, this->box.y, this->sp.GetWidth(), this->sp.GetHeight());
}

//retorna true se encerrar o powerup
bool Player::EndPowerupEffect(int maxTime){
    if(this->itemEffect.Get() > maxTime){
        this->powerUp = NONE;
        this->SetTargetSpeed(PLAYER_NORMAL_SPEED);

        if(this->powerupMusic.IsPlaying())
            this->powerupMusic.Stop();

        if(this->IsIndestructible())
            this->isIndestructible = false;

        return true;
    }
    return false;
}

void Player::CheckEndPowerupEffects(float dt){
    if(this->powerUp == SKATE){
        this->itemEffect.Update(dt);
        this->isPassingMapObject = false;
        this->isIndestructible = true;
        if (this->EndPowerupEffect(5))
            this->ChangeSpriteSheet("img/playerRunning.png", 6);
    }
    if (this->powerUp == COMIDA){
        this->itemEffect.Update(dt);
        this->EndPowerupEffect(3);
    }
    if(this->powerUp == CACA_DE_POMBO){
        this->itemEffect.Update(dt);
        this->EndPowerupEffect(5);
    }
}

void Player::CheckCollisionToResetSpeed(){
    if(!this->isColliding){
        if(this->wasColliding){
            this->speed = PLAYER_NORMAL_SPEED;
            this->SetTargetSpeed(PLAYER_NORMAL_SPEED);
            this->wasColliding = false;
        }
    }
}

void Player::AdjustSpeed(float dt){
	//ir acelerando at� a velocidade
	if(!this->IsTargetSpeed(targetSpeed)){
		if(this->targetSpeed > this->speed)
			this->speed += this->acceleration * dt;

		if(this->targetSpeed < this->speed)
			this->speed -= this->acceleration * dt;

		if(this->targetSpeed == 0){
			this->speed = 0;
		}
	}
}

//ajusta a posição do Player de acordo com o tipo do movimento
//(se ele se desloca de um lado para o outro ou de cima para baixo)
void Player::SetPositionToMovementState(float dt){

    //correndo
    if(this->movementState == MovementState::RUNNING){
        this->box.x += this->speed * dt * 100;

        if(this->isColliding == false && (this->box.x - Camera::pos.x) < START_POSITION_X){ //corrige a posição do player para a posicao inicial após colisao
                this->box.x += CORRECTION_POSITION_SPEED;
        }
    }

    if(this->movementState == MovementState::GOING_DOWN)
        this->box.y += this->speed * dt * 150;

    if(this->movementState == MovementState::GOING_UP)
        this->box.y -= this->speed * dt * 150;
}

//ajusta a posição do player quando troca de andar
void Player::AdjustGoingUpOrDown(){

    if(this->movementState != RUNNING){

        if(this->layer == LAYER_TOP && abs(this->box.y - ITEM_HEIGHT_L3) < 10){							//
            this->movementState = RUNNING;
            this->box.y = ITEM_HEIGHT_L3 - (this->subLayer - 3)*26;
        }

        if(this->layer == LAYER_MIDDLE && abs(this->box.y - ITEM_HEIGHT_L2) < 10){
            this->movementState = RUNNING;
            this->box.y = ITEM_HEIGHT_L2 - (this->subLayer - 3)*26;
        }

        if(this->layer == LAYER_BOTTON && abs(this->box.y - ITEM_HEIGHT_L1) < 10){
            this->movementState = RUNNING;
            this->box.y = ITEM_HEIGHT_L1 - (this->subLayer - 3)*26;
        }
    }
}

int Player::getX(){
    return pos.x;
}

int Player::getBaseX(){
    return baseX;
}
