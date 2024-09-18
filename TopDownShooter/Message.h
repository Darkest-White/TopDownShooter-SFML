#pragma once
#include"GameObject.h"

enum class MsgType { Move, Death, Create, DealDamage, DamageToPlayer };
enum class ObjType { Tower, Projectile, Enemy };

struct Message
{
	MsgType type;
	GameObject* sender;
	union
	{
		struct
		{
			Vector2f old_position;
		} move;

		struct
		{
			GameObject* who_to_die;
			GameObject* killer;
		} death;

		struct
		{
			GameObject* new_object;
		} create;

		struct
		{
			float damage;
			GameObject* to_who;
			GameObject* by_whom;
		} deal_damage;

		struct
		{
			int damage;
			GameObject* by_whom;
		} damage_to_player;
	};

	Message();
};