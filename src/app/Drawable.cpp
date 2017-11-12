
#include "Drawable.h"

namespace application
{
	namespace sdl
	{

        Drawable::Drawable() :
            m_locker()
        {
            // Nothing to do
        }

        Drawable::~Drawable() {
            // Nothing to do
        }

        bool Drawable::tryLock() {
            return m_locker.try_lock();
        }

        void Drawable::lock() {
            m_locker.lock();
        }

        void Drawable::unlock() {
            m_locker.unlock();
        }

	}
}
