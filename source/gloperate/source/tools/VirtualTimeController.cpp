#include <gloperate/tools/VirtualTimeController.h>

#include <gloperate/painter/AbstractVirtualTimeCapability.h>


namespace gloperate
{

VirtualTimeController::VirtualTimeController(AbstractVirtualTimeCapability* capability)
: m_capability(capability)
, m_loop(true)
, m_speed(1.0)
, m_time(0.0)
{
}

void VirtualTimeController::update()
{
    if (active())
    {
        const Tick now = Clock::now();
        const auto timeDiff = std::chrono::duration_cast<std::chrono::duration<double>>(now - m_lastTick).count();
        m_lastTick = now;

        setTime(m_time + (timeDiff * m_speed));
    }
}

bool VirtualTimeController::active() const
{
    return m_capability->enabled();
}

void VirtualTimeController::setActive(bool newActive)
{
    m_capability->setEnabled(newActive);

    if (newActive)
    {
        m_lastTick = Clock::now();

        if (loop() && m_time >= m_capability->loopDuration())
        {
            setTime(0.0);
        }
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
    return m_capability->loopDuration();
}

bool VirtualTimeController::loop() const
{
    return m_loop && std::abs(duration()) >= std::numeric_limits<double>::epsilon();
}

void VirtualTimeController::setLoop(bool enabled)
{
    m_loop = enabled;

    onLoopChanged(loop());
}

} /* namespace gloperate */
