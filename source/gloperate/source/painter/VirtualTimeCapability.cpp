
#include <gloperate/painter/VirtualTimeCapability.h>

#include <cassert>


namespace gloperate
{


VirtualTimeCapability::VirtualTimeCapability()
: m_enabled(true)
, m_duration(2.0 * 3.141592654)
, m_time(0.0)
, m_delta(0.0)
{
}

VirtualTimeCapability::~VirtualTimeCapability()
{
}

bool VirtualTimeCapability::enabled() const
{
    return m_enabled;
}

void VirtualTimeCapability::setEnabled(bool enabled)
{
    m_enabled = enabled;

    setChanged(true);
}

double VirtualTimeCapability::time() const
{
    return m_time;
}

void VirtualTimeCapability::setTime(double time)
{
    m_delta = time - m_time;
    m_time  = time;

    setChanged(true);
}

double VirtualTimeCapability::delta() const
{
    return m_delta;
}

double VirtualTimeCapability::loopDuration() const
{
    return m_duration;
}

void VirtualTimeCapability::setLoopDuration(double duration)
{
    assert(duration > 0.0);

    m_duration = duration;

    setChanged(true);
}


} // namespace gloperate
