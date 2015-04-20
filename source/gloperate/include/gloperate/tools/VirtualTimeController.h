#pragma once

#include <chrono>

#include <gloperate/gloperate_api.h>


namespace gloperate
{

class AbstractVirtualTimeCapability;

class GLOPERATE_API VirtualTimeController
{
public:
    VirtualTimeController(AbstractVirtualTimeCapability* capability);

    void update();

    bool active() const;
    void setActive(bool active);

    double speed() const;
    void setSpeed(double speed);

    double time() const;
    void setTime(double time);

    bool loop() const;
    void setLoop(bool enabled);

    double duration() const;

protected:
    using Clock = std::chrono::high_resolution_clock;
    using Tick = Clock::time_point;

protected:
    AbstractVirtualTimeCapability* m_capability;

    bool m_loop;
    double m_speed;

    double m_time;
    Tick m_lastTick;
};

} /* namespace gloperate */
