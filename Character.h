#ifndef CHARACTER_H_
#define CHARACTER_H_

//Player Tank
//Depends on rotation
const unsigned char TankN [] = {
  0x1e, 0x0c, 0x1f, 0x0c, 0x1e
};

const unsigned char TankE [] = {
  0x15, 0x1f, 0x1f, 0x15, 0x04
};

const unsigned char TankS [] = {
  0x0f, 0x06, 0x1f, 0x06, 0x0f
};

const unsigned char TankW [] = {
  0x04, 0x15, 0x1f, 0x1f, 0x15
};

//NPC Tank
//Depends on rotation
const unsigned char NPCns [] = {
  0x1f, 0x0e, 0x0e, 0x0e, 0x1f
};

const unsigned char NPCew [] = {
  0x11, 0x1f, 0x1f, 0x1f, 0x11
};

//Player Deer
const unsigned char Deer [] = {
  0x03, 0x0a, 0x0b, 0x0a, 0x7f, 0x78, 0x78, 0x7f, 0x0a, 0x0b, 0x0a, 0x03
};

//Player Bullet
const unsigned char Weapon [] = {
  0x01
};

#endif
