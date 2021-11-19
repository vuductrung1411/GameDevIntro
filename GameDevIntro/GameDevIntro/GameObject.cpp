#include "GameObject.h"

GameObject::GameObject(Camera camera, float x, float y, float height, float width, float vx, float vy, const wchar_t* path, int status)
{
	this->camera = camera;
	this->coords.x = x;
	this->coords.y = y;
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

void GameObject::SetCamera(Camera camera)
{
	this->camera = camera;
}

void GameObject::Update(DWORD dt)
{
	switch (this->status)
	{
	case STATUS_STAND:
		break;
	case STATUS_FOLLOW_KEYSTATE:
		break;
	case STATUS_GO_UP:
		GoUp(dt);
		break;
	case STATUS_GO_DOWN:
		GoDown(dt);
		break;
	case STATUS_GO_LEFT:
		GoLeft(dt);
		break;
	case STATUS_GO_RIGHT:
		GoRight(dt);
		break;
	case STATUS_GO_AROUND_FOLLOW_CLOCKWISE:
		GoArroundFollowClockwise(dt);
		break;
	case STATUS_GO_AROUND_COUNTER_CLOCKWISE:
		GoArroundCounterClockwise(dt);
		break;
	case STATUS_HITTING_WALL:
		break;
	default:
		break;
	}
}

void GameObject::MoveUp(DWORD dt)
{
	this->coords.y -= this->vy * dt;

	float minYCamera = this->camera.coords.y;

	if (this->coords.y < minYCamera)
	{
		this->coords.y = minYCamera;
	} 
}

void GameObject::MoveDown(DWORD dt)
{
	this->coords.y += this->vy * dt;

	float maxYCamera = this->camera.coords.y + this->camera.height;

	if (this->coords.y > maxYCamera - this->height)
	{
		this->coords.y = maxYCamera - this->height;
	}
}

void GameObject::MoveLeft(DWORD dt)
{
	this->coords.x -= this->vx * dt;

	float minXCamera = this->camera.coords.x;

	if (this->coords.x < minXCamera)
	{
		this->coords.x = minXCamera;
	}
}

void GameObject::MoveRight(DWORD dt)
{
	this->coords.x += this->vx * dt;

	float maxXCamera = this->camera.coords.x + this->camera.width;

	if (this->coords.x > maxXCamera - this->width)
	{
		this->coords.x = maxXCamera - this->width;
	}
}

void GameObject::GoUp(DWORD dt)
{
	if (isCloseToTheTopEdge())
	{
		float maxYCamera = this->camera.coords.y + this->camera.height;

		this->coords.y = maxYCamera - this->height;
	} 
	else MoveUp(dt);
}

void GameObject::GoDown(DWORD dt)
{
	if (isCloseToTheBotEdge())
	{
		float minYCamera = this->camera.coords.y;

		this->coords.y = minYCamera;
	} 
	else MoveDown(dt);
}

void GameObject::GoLeft(DWORD dt)
{
	if (isCloseToTheLeftEdge())
	{
		float maxXCamera = this->camera.coords.x + this->camera.width;

		this->coords.x = maxXCamera - this->width;
	}
	else MoveLeft(dt);
}

void GameObject::GoRight(DWORD dt)
{
	if (isCloseToTheRightEdge())
	{
		float minXCamera = this->camera.coords.x;

		this->coords.x = minXCamera;
	}
	else MoveRight(dt);
}

void GameObject::GoArroundFollowClockwise(DWORD dt)
{
	if (isCloseToTheTopEdge())
	{
		if (isCloseToTheRightEdge())
		{
			MoveDown(dt);
		}
		else
		{
			MoveRight(dt);
		}
		return;
	}

	if (isCloseToTheRightEdge())
	{
		if (isCloseToTheBotEdge())
		{
			MoveLeft(dt);
		}
		else
		{
			MoveDown(dt);
		}
		return;
	}

	if (isCloseToTheBotEdge())
	{
		if (isCloseToTheLeftEdge())
		{
			MoveUp(dt);
		}
		else
		{
			MoveLeft(dt);
		}
		return;
	}

	if (isCloseToTheLeftEdge())
	{
		if (isCloseToTheTopEdge())
		{
			MoveRight(dt);
		}
		else
		{
			MoveUp(dt);
		}
		return;
	}
}

void GameObject::GoArroundCounterClockwise(DWORD dt)
{
	if (isCloseToTheLeftEdge())
	{
		if (isCloseToTheBotEdge())
		{
			MoveRight(dt);
		}
		else
		{
			MoveDown(dt);
		}
		return;
	}

	if (isCloseToTheBotEdge())
	{
		if (isCloseToTheRightEdge())
		{
			MoveUp(dt);
		}
		else
		{
			MoveRight(dt);
		}
		return;
	}

	if (isCloseToTheRightEdge())
	{
		if (isCloseToTheTopEdge())
		{
			MoveLeft(dt);
		}
		else
		{
			MoveUp(dt);
		}
		return;
	}

	if (isCloseToTheTopEdge())
	{
		if (isCloseToTheLeftEdge())
		{
			MoveDown(dt);
		}
		else
		{
			MoveLeft(dt);
		}
		return;
	}
}

bool GameObject::isCloseToTheTopEdge()
{
	float minYCamera = this->camera.coords.y;

	return (this->coords.y == minYCamera);
}
bool GameObject::isCloseToTheBotEdge()
{
	float maxYCamera = this->camera.coords.y + this->camera.height;

	return (this->coords.y == maxYCamera - this->height);
}
bool GameObject::isCloseToTheRightEdge()
{
	float maxXCamera = this->camera.coords.x + this->camera.width;

	return (this->coords.x == maxXCamera - this->width);
}
bool GameObject::isCloseToTheLeftEdge()
{
	float minXCamera = this->camera.coords.x;

	return (this->coords.x == minXCamera);
}