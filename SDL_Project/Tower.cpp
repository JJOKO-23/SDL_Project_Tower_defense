#include "Tower.h"

Tower::Tower(float money_) {
    maxMoney = money_;
    money = money_;
}

void Tower::TakeDamage(float amount) {
    money -= amount;
    if (money < 0) money = 0;
}