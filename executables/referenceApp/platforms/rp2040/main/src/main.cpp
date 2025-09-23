// Copyright 2024 quarterbit

#include <stdint.h>

#include "lifecycle/StaticBsp.h"
#include "systems/BspSystem.h"

#include <async/AsyncBinding.h>
#include <async/Config.h>
#include <etl/alignment.h>
#include <lifecycle/LifecycleManager.h>

extern void app_main();

namespace platform
{
StaticBsp staticBsp;

StaticBsp& getStaticBsp() { return staticBsp; }

::etl::typed_storage<::systems::BspSystem> bspSystem;

/**
 * Callout from main application to give platform the chance to add a
 * ::lifecycle::ILifecycleComponent to the \p lifecycleManager at a given \p level.
 */
void platformLifecycleAdd(::lifecycle::LifecycleManager& lifecycleManager, uint8_t const level)
{
    if (level == 1U)
    {
        lifecycleManager.addComponent("bsp", bspSystem.create(TASK_BSP, staticBsp), level);
    }
}
} // namespace platform

extern "C"
{
void boardInit()
{
    // Initialize basic hardware
    // GPIO, clocks, etc. would be initialized here in a full implementation

    // Any other board-specific initialization can go here
}

int main()
{
    boardInit();

    // Initialize static BSP
    ::platform::staticBsp.init();

    // Start the application
    app_main();

    // Should not reach here
    return 0;
}

}