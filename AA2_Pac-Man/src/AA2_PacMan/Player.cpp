#include "Player.h"

Player::Player(Text texture, vec2 posGame, vec2 posSprite)
{
	//Inicializar las texturas (ID, mensaje, path)
	pTexture = new Text(texture);

	Renderer* r = Renderer::Instance();
	r->LoadTexture(pTexture->id, pTexture->path);

	rectGame = { posGame.x, posGame.y, r->GetTextureSize(pTexture->id) };
	rectSprite = { posSprite.x, posSprite.y, r->GetTextureSize(pTexture->id) };

	lifes = 3;
	score = 0;
	speed = 0;

	isPowered = false;
}

vec2 Player::getPlayerPosition()
{
	return vec2(rectGame.x, rectGame.y);
}

vec2 Player::getPlayerSize()
{
	return vec2(rectGame.w, rectGame.h);
}

void Player::move()
{
	
}

bool Player::powerUpCollision()
{
	
}

void Player::draw()
{
	// Version del año pasado
	//Renderer::Instance()->PushRotatedSprite(pTexture->id, rectSprite, rectGame, 90);
}

Player::~Player()
{
}
