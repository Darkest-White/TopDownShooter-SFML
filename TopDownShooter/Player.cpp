#include "Player.h"

Player::Player(Texture texture, Vector2f position) :
	GameObject(texture, position, 0, 100, 0, ObjType::Player)
{

}

Player::~Player()
{

}

void Player::WatchTarget(float mouse_x, float mouse_y)
{
	angle = atan2f((mouse_x - sprite.getPosition().x), (sprite.getPosition().y - mouse_y)) * (180.0 / 3.14);
	sprite.setRotation(angle);
}

void Player::GoSide(int side)
{
	if (side == 0)	 position.x += velocity + 3;
	if (side == 1) { position.x += velocity; position.y += velocity; }
	if (side == 2)   position.y += velocity + 3;
	if (side == 3) { position.x -= velocity; position.y += velocity; }
	if (side == 4)   position.x -= velocity + 3;
	if (side == 5) { position.x -= velocity; position.y -= velocity; }
	if (side == 6)   position.y -= velocity + 3;
	if (side == 7) { position.x += velocity; position.y -= velocity; }
}

void Player::Update(float dt)
{
	if (Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::S)) GoSide(3);
	if (Keyboard::isKeyPressed(Keyboard::D) && Keyboard::isKeyPressed(Keyboard::S)) GoSide(1);
	if (Keyboard::isKeyPressed(Keyboard::D) && Keyboard::isKeyPressed(Keyboard::W)) GoSide(7);
	if (Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::W)) GoSide(5);
	if (Keyboard::isKeyPressed(Keyboard::D)) GoSide(0);
	if (Keyboard::isKeyPressed(Keyboard::S)) GoSide(2);
	if (Keyboard::isKeyPressed(Keyboard::A)) GoSide(4);
	if (Keyboard::isKeyPressed(Keyboard::W)) GoSide(6);
}

void Player::SendMSG(Message* m)
{
	if (m->deal_damage.to_who == this)
	{
		hp -= m->deal_damage.damage;

		/*if (hp <= 0)
		{
			Message* msg = new Message;
			msg->type = MsgType::Death;
			msg->death.type = ObjType::Player;
			msg->death.killer = m->deal_damage.by_whom;
			msg->death.who_to_die = this;
			msg->sender = this;
			GameManager::GetInstance()->SendMsg(msg);
		}*/
	}
}