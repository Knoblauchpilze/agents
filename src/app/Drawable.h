#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <iostream>
#include <SDL.h>
#include <mutex>
#include "Area.h"

namespace application
{
    namespace sdl
    {

        class Drawable {

        public:

            virtual bool tryLock();

            virtual void lock();

            virtual void unlock();

            virtual bool hasChanged() = 0;

            virtual utils::sdl::Area getRenderingArea() = 0;

            virtual SDL_Surface* draw() = 0;

        protected:

            Drawable();

            virtual ~Drawable();

        private:

            std::mutex m_locker;
        };

    }
}

#endif // DRAWABLE_H
