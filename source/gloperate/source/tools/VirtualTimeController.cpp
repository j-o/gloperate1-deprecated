#include <gloperate/tools/VirtualTimeController.h>

#include <gloperate/painter/AbstractVirtualTimeCapability.h>


namespace gloperate
{

VirtualTimeController::VirtualTimeController(AbstractVirtualTimeCapability * capability)
: m_capability(nullptr)
, m_active(false)
, m_loop(true)
, m_speed(1.0)
, m_time(0.0)
{
    setCapability(capability);
}

void VirtualTimeController::setCapability(AbstractVirtualTimeCapability * capability)
{
    m_capabilityConnections.clear();

    m_capability = capability;

    if (m_capability != nullptr) {
        m_capabilityConnections.emplace_back(m_capability->onLoopDurationChanged.connect(onDurationChanged));
        m_capabilityConnections.emplace_back(m_capability->onEnabledChanged.connect([this](const bool & enabled) {
            if (active())
            {
                initializeTimer();
            }
            onActiveChanged(active());
        }));
    }
}

AbstractVirtualTimeCapability * VirtualTimeController::capability() const
{
    return m_capability;
}

void VirtualTimeController::initializeTimer()
{
    m_lastTick = Clock::now();

    if (loop() && m_time >= m_capability->loopDuration())
    {
        setTime(0.0);
    }
}

void VirtualTimeController::update()
{
    if (m_capability != nullptr && active())
    {
        const Tick now = Clock::now();
        const auto timeDiff = std::chrono::duration_cast<std::chrono::duration<double>>(now - m_lastTick).count();
        m_lastTick = now;

        setTime(m_time + (timeDiff * m_speed));
    }
}

bool VirtualTimeController::active() const
{
    return m_active && m_capability != nullptr && m_capability->enabled();
}

void VirtualTimeController::setActive(bool newActive)
{
    if (m_capability == nullptr)
    {
        return;
    }

    m_active = newActive;

    if (active())
    {
        initializeTimer();
    }

    onActiveChanged(active());
}

double VirtualTimeController::speed() const
{
    return m_speed;
}

void VirtualTimeController::setSpeed(double newSpeed)
{
    m_speed = newSpeed;

    onSpeedChanged(speed());
}

double VirtualTimeController::time() const
{
    return m_time;
}

void VirtualTimeController::setTime(double newTime)
{
    if (m_capability == nullptr)
    {
        return;
    }

    m_time = newTime;

    if (loop())
    {
        while (m_time > duration())
        {
            m_time -= duration();
        }
    }
    else
    {
        if (m_time > duration())
        {
            m_time = duration();
            setActive(false);
        }
    }

    m_capability->setTime(m_time);

    onTimeChanged(time());
}

double VirtualTimeController::duration() const
{
    return m_capability != nullptr ? m_capability->loopDuration() : 0.0;
}

bool VirtualTimeController::loop() const
{
    return m_loop;
}

void VirtualTimeController::setLoop(bool enabled)
{
    m_loop = enabled;

    onLoopChanged(loop());
}

} /* namespace gloperate */
