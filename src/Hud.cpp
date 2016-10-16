#include "Hud.h"

Hud::Hud(){
    cout << "enter contrutor da HUD" << endl;
    this->coffeeAmmo = "";
    this->clock = "";
    cout << "sai contrstutor da HUD" << endl;
}

Hud::~Hud(){
}

void Hud::InitHud(){
    cout << "enter INIT HUD" << endl;

    this->clockText.OpenText("font/ComicNeue_Bold.otf", 40, BLENDED, "CLOCK TEXT", TEXT_WHITE, 800, 17);
//    this->clockText2.OpenText("font/ComicNeue_Bold.otf", 40, BLENDED, "CLOCK TEXT", TEXT_WHITE, 300, 17);
    this->coffeeText.OpenText("font/ComicNeue_Bold.otf", 40, BLENDED, "COFFEE TEXT", TEXT_WHITE, 300, 17);

    cout << "exit INIT HUD" << endl;
}

void Hud::Update(float dt){
    this->clockText.SetText(this->clock);

//    std::stringstream newCoffee;
//    newCoffee << "COFFEE: " << this->coffeeAmmo;
//
    this->coffeeText.SetText(this->coffeeAmmo);

//    this->coffeeText.SetText(newCoffee.str());
}

void Hud::Render(){
//    cout << "coffee: " << this->coffeeAmmo << endl;
//    cout << "clock: " << this->clock << endl;
    this->clockText.Render(75, 0);
    this->coffeeText.Render(75, 0);
//    this->coffeeText.Render(75, 0);

//    this->coffeeText.Render(0,0);
}

void Hud::SetCoffeeAmmo(int coffeeAmmo){
    std::stringstream newCoffeeAmmo;
    newCoffeeAmmo << "Coffee: " << coffeeAmmo;
    this->coffeeAmmo = newCoffeeAmmo.str();
    cout << this->coffeeAmmo << endl;
}

void Hud::SetClock(string clock){
    this->clock = clock;
}