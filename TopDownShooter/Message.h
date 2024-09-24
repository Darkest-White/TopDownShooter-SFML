#pragma once
#include"GameObject.h"

enum class MsgType { Death, Create, DealDamage };
enum class ObjType { Projectile, Enemy, Player };

struct Message
{
	MsgType type;
	GameObject* sender;
	union
	{
		struct
		{
			ObjType type;
			GameObject* who_to_die;
			GameObject* killer;
		} death;

		struct
		{
			ObjType type;
			GameObject* new_object;
		} create;

		struct
		{
			float damage;
			GameObject* to_who;
			GameObject* by_whom;
		} deal_damage;
	};

	Message();
};