#include"VectorMath.h"

Vector2f Normalize(Vector2f vector)
{
	float lenght = sqrt(vector.x * vector.x + vector.y * vector.y);
	vector.x /= lenght;
	vector.y /= lenght;
	return vector;
}

float GetLenght(Vector2f vector)
{
	return sqrt(vector.x * vector.x + vector.y * vector.y);
}

float GetDistance(Vector2f a, Vector2f b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

Vector2f ChangeLenght(Vector2f vector, float new_lenght)
{
	float lenght = sqrt(vector.x * vector.x + vector.y * vector.y);
	lenght = (lenght == 0) ? 1 : lenght;
	vector.x *= new_lenght / lenght;
	vector.y *= new_lenght / lenght;
	return vector;
}

Vector2f operator-(Vector2f a, Vector2f b)
{
	return { a.x - b.x, a.y - b.y };
}