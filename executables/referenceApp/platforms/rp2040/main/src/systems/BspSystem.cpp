// Copyright 2024 quarterbit

#include "systems/BspSystem.h"

namespace systems
{

BspSystem::BspSystem(::async::ContextType const context, StaticBsp& staticBsp)
: ::lifecycle::SingleContextLifecycleComponent(context)
, _context(context)
, _staticBsp(staticBsp)
{}

void BspSystem::init() { transitionDone(); }

void BspSystem::run()
{
    ::async::scheduleAtFixedRate(_context, *this, _timeout, 10u, ::async::TimeUnit::MILLISECONDS);
    transitionDone();
}

void BspSystem::shutdown()
{
    _timeout.cancel();
    transitionDone();
}

void BspSystem::execute()
{
    cyclic();
    _staticBsp.cyclic();
}

void BspSystem::cyclic() {}

} // namespace systems