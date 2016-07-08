/*
 * Player.h
 *
 *  Created on: 18 de mai de 2016
 *      Author: apoio
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "GameObject.h"
#include "Timer.h"
#include "Clock.h"
#include "Text.h"
#include "Music.h"
#include "Sound.h"


enum PowerUp{
	NONE,
	SKATE,
	DASH,
	COMIDA,
	CACA_DE_POMBO
};

enum MovementState{
    RUNNING,
    GOING_UP,
    GOING_DOWN
};

class Player : public GameObject{
public:
	Player(float x,float y);
	virtual ~Player();
	void Update(float dt);
	void Render();
	bool IsDead();
	bool Is(std::string type);
	void NotifyCollision(GameObject* other);
	bool IsTargetSpeed(float targetSpeed);
	void SetTargetSpeed(float targetSpeed);

    Player& GetInstance();

	static Player* player;

	float GetSpeed();
	float GetAcceleration();

	void SetAcceleration(float acceleration);

	bool IsRightPosition(); // checa se ta numa posicao na qual a camera pode voltar ao normal;

	void Movement();
	void Shoot();

	void RenderHud();
	void SetSpriteScale();
	bool IsIndestructible();
	void ChangeSpriteSheet(string file, int frameCount);
<<<<<<< HEAD

	void ChangeMusic(std::string musica);
=======
>>>>>>> 928b9815c55b70c15331b0bffb7f570355c91044

	static int coffee_ammo; // caso pegue cafe, tem q aumentar isso aki
    MovementState movementState;
private:
	Sprite sp; // sprite
	float speed; // velocidade
	float acceleration; // acceleratcao
	float targetSpeed;
	Vec2 pos; // posicao atual para facilitar calculos

	PowerUp powerUp;// enumaration de powerup

	Text hud;

	Timer itemEffect;
<<<<<<< HEAD

    bool isColliding;
    bool wasColliding;
	bool isRightPosition;
    bool isPassingMapObject;
	bool isIndestructible;

	Music musica;
=======

    bool isColliding;
    bool wasColliding;
	bool isRightPosition;
    bool isPassingMapObject;
	bool isIndestructible;
>>>>>>> 928b9815c55b70c15331b0bffb7f570355c91044

	Sound powerupMusic;
	bool isPlayingMusic;
};

#endif /* PLAYER_H_ */
