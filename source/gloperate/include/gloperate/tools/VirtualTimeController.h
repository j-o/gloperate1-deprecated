#pragma once


#include <chrono>
#include <deque>

#include <signalzeug/Signal.h>
#include <signalzeug/ScopedConnection.h>

#include <gloperate/gloperate_api.h>


namespace gloperate
{

class AbstractVirtualTimeCapability;

class GLOPERATE_API VirtualTimeController
{
public:
    VirtualTimeController(AbstractVirtualTimeCapability * capability);
    VirtualTimeController(const VirtualTimeController &) = delete;

    void setCapability(AbstractVirtualTimeCapability * capability);
    AbstractVirtualTimeCapability * capability() const;

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

    VirtualTimeController& operator=(const VirtualTimeController &) = delete;

public:
    signalzeug::Signal<double> onTimeChanged;
    signalzeug::Signal<double> onDurationChanged;
    signalzeug::Signal<double> onSpeedChanged;
    signalzeug::Signal<bool>   onLoopChanged;
    signalzeug::Signal<bool>   onActiveChanged;

protected:
    void initializeTimer();

protected:
    using Clock = std::chrono::high_resolution_clock;
    using Tick = Clock::time_point;

protected:
    AbstractVirtualTimeCapability * m_capability;
    std::deque<signalzeug::ScopedConnection> m_capabilityConnections;

    bool m_active;
    bool m_loop;
    double m_speed;

    double m_time;
    Tick m_lastTick;
};

} /* namespace gloperate */
