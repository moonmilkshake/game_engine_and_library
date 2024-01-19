#ifndef COMPONENT_H
#define COMPONENT_H
#include <iostream>
#include <SDL2/SDL.h>

// Spelmotor-klass
namespace crane
{
	class Component
	{
	public:
		virtual ~Component() = 0;
		virtual void mouseDown(const SDL_Event &) {}
		virtual void mouseUp(const SDL_Event &) {}
		virtual void keyDown(const SDL_Event &) {}
		virtual void keyUp(const SDL_Event &) {}
		virtual void draw() const = 0;
		virtual void tick() {}
		const SDL_Rect &getRect() const { return rect; }
		virtual bool checkCollision(const Component *other) const;
		virtual void handleCollision(const Component *other) {}
		int getLeft() const;
		int getTop() const;
		int getRight() const;
		int getBottom() const;
		int getWidth() const;
		int getHeight() const;
		int getWeight() const;
	protected:
		Component(int x, int y, int width, int height, int weight);
	private:
		Component(const Component &) = delete;
		const Component &operator=(const Component &) = delete;
		SDL_Rect rect;
		int weight;
		friend class MovableSprite;
	};
}

#endif
