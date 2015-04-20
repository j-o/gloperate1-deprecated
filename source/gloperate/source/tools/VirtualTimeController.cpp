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
        const auto timeDiff = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_lastTick).count();
        m_lastTick = now;

        setTime(m_time + (timeDiff * m_speed));
    }
}

bool VirtualTimeController::active() const
{
    return m_capability->enabled();
}

void VirtualTimeController::setActive(bool active)
{
    m_capability->setEnabled(active);
}

double VirtualTimeController::speed() const
{
    return m_speed;
}

void VirtualTimeController::setSpeed(double speed)
{
    m_speed = speed;
}

double VirtualTimeController::time() const
{
    return m_time;
}

void VirtualTimeController::setTime(double time)
{
    m_time = time;

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
}

} /* namespace gloperate */
