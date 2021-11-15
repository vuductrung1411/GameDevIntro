#include "GameObject.h"

GameObject::GameObject(float x, float y, float height, float width, float vx, float vy, const wchar_t* path, int status)
{
	this->x = x;
	this->y = y;
	this->height = height;
	this->width = width;
	this->vx = vx;
	this->vy = vy;
	this->path = path;
	this->status = status;
}

void GameObject::SetStatus(int status)
{
	this->status = status;
}

void GameObject::Update(float x, float y, int height, int width, DWORD dt)
{
	switch (this->status)
	{
	case STATUS_STAND:
		break;
	case STATUS_FOLLOW_KEYSTATE:
		break;
	case STATUS_GO_UP:
		GoUp(x, y, height, width, dt);
		break;
	case STATUS_GO_DOWN:
		GoDown(x, y, height, width, dt);
		break;
	case STATUS_GO_LEFT:
		GoLeft(x, y, height, width, dt);
		break;
	case STATUS_GO_RIGHT:
		GoRight(x, y, height, width, dt);
		break;
	case STATUS_GO_AROUND_FOLLOW_CLOCKWISE:
		GoArroundFollowClockwise(x, y, height, width, dt);
		break;
	case STATUS_GO_AROUND_COUNTER_CLOCKWISE:
		GoArroundCounterClockwise(x, y, height, width, dt);
		break;
	case STATUS_HITTING_WALL:
		break;
	default:
		break;
	}
}


void GameObject::MoveUp(float x, float y, int height, int width, DWORD dt)
{
	this->y -= this->vy * dt;

	if (this->y < y)
	{
		this->y = y;
	} 
}

void GameObject::MoveDown(float x, float y, int height, int width, DWORD dt)
{
	this->y += this->vy * dt;

	if (this->y > (y + height) - this->height)
	{
		this->y = (y + height) - this->height;
	}
}

void GameObject::MoveLeft(float x, float y, int height, int width, DWORD dt)
{
	this->x -= this->vx * dt;

	if (this->x < x)
	{
		this->x = x;
	}
}

void GameObject::MoveRight(float x, float y, int height, int width, DWORD dt)
{
	this->x += this->vx * dt;

	if (this->x > (x + width) - this->width)
	{
		this->x = (x + width) - this->width;
	}
}

void GameObject::GoUp(float xWnd, float yWnd, int heightWnd, int widthWnd, DWORD dt)
{
	if (isCloseToTheTopEdge(xWnd, yWnd, heightWnd, widthWnd))
	{
		this->y = yWnd + heightWnd - this->height;
	} 
	else MoveUp(xWnd, yWnd, heightWnd, widthWnd, dt);
}

void GameObject::GoDown(float xWnd, float yWnd, int heightWnd, int widthWnd, DWORD dt)
{
	if (isCloseToTheBotEdge(xWnd, yWnd, heightWnd, widthWnd))
	{
		this->y = yWnd;
	} 
	else MoveDown(xWnd, yWnd, heightWnd, widthWnd, dt);
}

void GameObject::GoLeft(float xWnd, float yWnd, int heightWnd, int widthWnd, DWORD dt)
{
	if (isCloseToTheLeftEdge(xWnd, yWnd, heightWnd, widthWnd))
	{
		this->x = xWnd + widthWnd - this->width;
	}
	else MoveLeft(xWnd, yWnd, heightWnd, widthWnd, dt);
}

void GameObject::GoRight(float xWnd, float yWnd, int heightWnd, int widthWnd, DWORD dt)
{
	if (isCloseToTheRightEdge(xWnd, yWnd, heightWnd, widthWnd))
	{
		this->x = xWnd;
	}
	else MoveRight(xWnd, yWnd, heightWnd, widthWnd, dt);
}

void GameObject::GoArroundFollowClockwise(float xWnd, float yWnd, int heightWnd, int widthWnd, DWORD dt)
{
	if (isCloseToTheTopEdge(xWnd, yWnd, heightWnd, widthWnd))
	{
		if (isCloseToTheRightEdge(xWnd, yWnd, heightWnd, widthWnd))
		{
			MoveDown(xWnd, yWnd, heightWnd, widthWnd, dt);
		}
		else
		{
			MoveRight(xWnd, yWnd, heightWnd, widthWnd, dt);
		}
		return;
	}

	if (isCloseToTheRightEdge(xWnd, yWnd, heightWnd, widthWnd))
	{
		if (isCloseToTheBotEdge(xWnd, yWnd, heightWnd, widthWnd))
		{
			MoveLeft(xWnd, yWnd, heightWnd, widthWnd, dt);
		}
		else
		{
			MoveDown(xWnd, yWnd, heightWnd, widthWnd, dt);
		}
		return;
	}

	if (isCloseToTheBotEdge(xWnd, yWnd, heightWnd, widthWnd))
	{
		if (isCloseToTheLeftEdge(xWnd, yWnd, heightWnd, widthWnd))
		{
			MoveUp(xWnd, yWnd, heightWnd, widthWnd, dt);
		}
		else
		{
			MoveLeft(xWnd, yWnd, heightWnd, widthWnd, dt);
		}
		return;
	}

	if (isCloseToTheLeftEdge(xWnd, yWnd, heightWnd, widthWnd))
	{
		if (isCloseToTheTopEdge(xWnd, yWnd, heightWnd, widthWnd))
		{
			MoveRight(xWnd, yWnd, heightWnd, widthWnd, dt);
		}
		else
		{
			MoveUp(xWnd, yWnd, heightWnd, widthWnd, dt);
		}
		return;
	}
}

void GameObject::GoArroundCounterClockwise(float xWnd, float yWnd, int heightWnd, int widthWnd, DWORD dt)
{
	if (isCloseToTheLeftEdge(xWnd, yWnd, heightWnd, widthWnd))
	{
		if (isCloseToTheBotEdge(xWnd, yWnd, heightWnd, widthWnd))
		{
			MoveRight(xWnd, yWnd, heightWnd, widthWnd, dt);
		}
		else
		{
			MoveDown(xWnd, yWnd, heightWnd, widthWnd, dt);
		}
		return;
	}

	if (isCloseToTheBotEdge(xWnd, yWnd, heightWnd, widthWnd))
	{
		if (isCloseToTheRightEdge(xWnd, yWnd, heightWnd, widthWnd))
		{
			MoveUp(xWnd, yWnd, heightWnd, widthWnd, dt);
		}
		else
		{
			MoveRight(xWnd, yWnd, heightWnd, widthWnd, dt);
		}
		return;
	}

	if (isCloseToTheRightEdge(xWnd, yWnd, heightWnd, widthWnd))
	{
		if (isCloseToTheTopEdge(xWnd, yWnd, heightWnd, widthWnd))
		{
			MoveLeft(xWnd, yWnd, heightWnd, widthWnd, dt);
		}
		else
		{
			MoveUp(xWnd, yWnd, heightWnd, widthWnd, dt);
		}
		return;
	}

	if (isCloseToTheTopEdge(xWnd, yWnd, heightWnd, widthWnd))
	{
		if (isCloseToTheLeftEdge(xWnd, yWnd, heightWnd, widthWnd))
		{
			MoveDown(xWnd, yWnd, heightWnd, widthWnd, dt);
		}
		else
		{
			MoveLeft(xWnd, yWnd, heightWnd, widthWnd, dt);
		}
		return;
	}
}

bool GameObject::isCloseToTheTopEdge(float xWnd, float yWnd, int heightWnd, int widthWnd)
{
	return (this->y == yWnd);
}
bool GameObject::isCloseToTheBotEdge(float xWnd, float yWnd, int heightWnd, int widthWnd)
{
	return (this->y == yWnd + heightWnd - this->height);
}
bool GameObject::isCloseToTheRightEdge(float xWnd, float yWnd, int heightWnd, int widthWnd)
{
	return (this->x == xWnd + widthWnd - this->width);
}
bool GameObject::isCloseToTheLeftEdge(float xWnd, float yWnd, int heightWnd, int widthWnd)
{
	return (this->x == xWnd);
}