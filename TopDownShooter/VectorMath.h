#pragma once
#include<SFML/Graphics.hpp>
#include<cmath>
using namespace std;
using namespace sf;

Vector2f Normalize(Vector2f vector);

float GetLenght(Vector2f vector);

float GetDistance(Vector2f a, Vector2f b);

Vector2f ChangeLenght(Vector2f vector, float new_lenght);

Vector2f operator-(Vector2f a, Vector2f b);