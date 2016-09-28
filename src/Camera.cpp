#include "Defines.h"
#include "Camera.h"
#include "InputManager.h"
#include "Player.h"


Vec2 Camera::pos = Vec2(0,0);
Vec2 Camera::speed = Vec2(CAMERA_NORMAL_SPEED,2);

int Camera::layer = 2;
bool Camera::pause = false;

Camera::Camera() {
}

Camera::~Camera() {

}

void Camera::Update(float dt){
        if(pause == false){
            if(Player::player){//Se o player for destruido, n�o tem como fazer as chamadas abaixo: SEGFAULT
                float diff = Player::player->GetX() - pos.x;
                switch(Player::player->movementState){
                    case RUNNING:
                        if(Player::player->isInPosition()){
                            pos.x += speed.x*Player::player->GetPositionIncrement();
                        }else if(diff < Player::player->GetBaseX() - DELTA_ACCEPT){
                            pos.x += (speed.x*dt*100)/2;
                        }else if(diff > Player::player->GetBaseX() + DELTA_ACCEPT){
                            pos.x += (speed.x*dt*100)*3/2;
                        }
                        break;
                    case EATING:
                        pos.x += speed.x*Player::player->GetPositionIncrement()/3;
                        break;
                }
                layer = Player::player->layer;
            }
            //move a camera no eixo Y
            if(layer == 3)//se esta na layer 3
                if(pos.y > 0)//e a camera ainda nao est� na origem
                    pos.y = pos.y - speed.y*dt*100;//continua descendo a camera
            if(layer == 2 )
                if(pos.y > 220)
                    pos.y = pos.y - speed.y*dt*100;
            if(layer == 2 )
                if(pos.y < 220)
                    pos.y = pos.y + speed.y*dt*100;
            if(layer == 1)
                if(pos.y < 480)
                    pos.y = pos.y + speed.y*dt*100;
        }
}
