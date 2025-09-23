// Copyright 2024 quarterbit

#pragma once

#include "lifecycle/SingleContextLifecycleComponent.h"
#include "lifecycle/StaticBsp.h"

namespace systems
{

class BspSystem
: public ::lifecycle::SingleContextLifecycleComponent
, private ::async::RunnableType
{
public:
    BspSystem(::async::ContextType context, StaticBsp& staticBsp);

    void init() override;
    void run() override;
    void shutdown() override;

    void execute() override;

    void cyclic();

private:
    ::async::ContextType const _context;
    ::async::TimeoutType _timeout;
    StaticBsp& _staticBsp;
};

} // namespace systems