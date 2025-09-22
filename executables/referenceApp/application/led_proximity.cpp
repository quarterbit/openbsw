#include "hcsr04.h"
#include "ws2812b.h"
#include "lifecycle/AsyncLifecycleComponent.h"
#include "async/Async.h"

namespace {
    constexpr uint32_t LED_COUNT = 144;
    constexpr uint32_t LED_DATA_PIN = 78;  // PC14 - configured as GPIO output in ioConfiguration.h
    constexpr uint32_t HCSR04_TRIGGER_PIN = 37; // PB5 - configured as GPIO output in ioConfiguration.h  
    constexpr uint32_t HCSR04_ECHO_PIN = 36;    // PB4 - configured as GPIO input in ioConfiguration.h

    constexpr int32_t DIST_MIN_CM = 1;
    constexpr int32_t DIST_MAX_CM = 100;
    constexpr uint32_t UPDATE_INTERVAL_MS = 100;

    class LedProximityComponent 
    : public ::lifecycle::AsyncLifecycleComponent
    , private ::async::IRunnable {
    public:
        explicit LedProximityComponent(::async::ContextType context)
        : _context(context) {
            setTransitionContext(context);
        }

    protected:
        void init() override {
            hcsr04_init(HCSR04_TRIGGER_PIN, HCSR04_ECHO_PIN);
            ws2812b_init(LED_DATA_PIN, LED_COUNT);
            ws2812b_clear();
            transitionDone();
        }

        void run() override {
            // Schedule periodic updates using scheduleAtFixedRate
            ::async::scheduleAtFixedRate(
                _context, *this, _timeout, UPDATE_INTERVAL_MS, ::async::TimeUnit::MILLISECONDS);
            transitionDone();
        }

        void shutdown() override {
            ws2812b_clear();
            transitionDone();
        }

    private:
        // Implementation of IRunnable::execute()
        void execute() override {
            updateLeds();
        }

        ::async::ContextType _context;
        ::async::TimeoutType _timeout;

        void updateLeds() {
            int32_t distance = hcsr04_measure_cm();
            uint32_t leds_on = 0;
            if (distance > 0 && distance <= DIST_MAX_CM) {
                if (distance < DIST_MIN_CM) distance = DIST_MIN_CM;
                leds_on = LED_COUNT * (DIST_MAX_CM - distance) / (DIST_MAX_CM - DIST_MIN_CM + 1);
            }
            ws2812b_clear();
            for (uint32_t i = 0; i < leds_on; i++) {
                ws2812b_set_led(i, 161, 0, 255); // Purple
            }
            ws2812b_show();
        }
    };

    // Global instance - this is a simplified integration
    static LedProximityComponent* g_ledProximityComponent = nullptr;
}

extern "C" {
    void app_start() {
        // For now, just initialize - proper integration would use lifecycle manager
        // This is a simplified version to make the build work
        if (g_ledProximityComponent == nullptr) {
            // Note: This requires a proper async context, which would normally be
            // provided by the OpenBSW framework
            // g_ledProximityComponent = new LedProximityComponent(someContext);
        }
    }
}
