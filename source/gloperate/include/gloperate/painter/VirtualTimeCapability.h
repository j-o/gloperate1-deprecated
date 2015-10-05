
#pragma once


#include <gloperate/painter/AbstractVirtualTimeCapability.h>


namespace gloperate
{


/**
*  @brief
*    Default implementation for AbstractVirtualTimeCapability
*/
class GLOPERATE_API VirtualTimeCapability : public AbstractVirtualTimeCapability
{
public:
    /**
    *  @brief
    *    Constructor
    */
    VirtualTimeCapability();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~VirtualTimeCapability();

    // Virtual functions from AbstractVirtualTimeCapability
    virtual bool enabled() const override;
    virtual void setEnabled(bool enabled) override;
    virtual double time() const override;
    virtual void setTime(double time) override;
    virtual double delta() const override;
    virtual double loopDuration() const override;
    virtual void setLoopDuration(double duration) override;


protected:
    bool   m_enabled;    /**< Is virtual time enabled? */
    double m_duration;   /**< Duration after which time is reset to 0 (in seconds) */
    double m_time;       /**< Current time (in seconds) */
    double m_delta;      /**< Last time delta  (in seconds)*/
};


} // namespace gloperate
