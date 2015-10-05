#pragma once


#include <signalzeug/Signal.h>

#include <gloperate/gloperate_api.h>


namespace gloperate
{

class VirtualTimeController;
class ResourceManager;
class Painter;


/**
*  @brief
*    Base class for window systems
*/
class GLOPERATE_API AbstractWindow
{
public:
    AbstractWindow(ResourceManager & resourceManager);

    /**
    *  @brief
    *    Get used painter
    *
    *  @return
    *    Painter, can be nullptr
    */
    gloperate::Painter * painter() const;

    /**
    *  @brief
    *    Set used painter
    *
    *  @param[in] painter
    *    Painter, can be nullptr
    */
    void setPainter(gloperate::Painter * painter);

    /**
    *  @brief
    *    Get used resource manager
    *
    *  @return
    *    ResourceManager
    */
    gloperate::ResourceManager & resourceManager();

    /**
    *  @brief
    *    Get used resource manager
    *
    *  @return
    *    ResourceManager (const)
    */
    const gloperate::ResourceManager & resourceManager() const;

    /**
    *  @brief
    *    Get used virtual time controller
    *
    *  @return
    *    VirtualTimeController
    */
    VirtualTimeController * virtualTimeController() const;


public:
    /**
    *  @brief
    *    Triggered before paint
    */
    signalzeug::Signal<> onPrePaint;

    /**
    *  @brief
    *    Triggered after paint
    */
    signalzeug::Signal<> onPostPaint;

    /**
    *  @brief
    *    Triggered when painter changed. Passes new instance.
    */
    signalzeug::Signal<Painter*> onPainterChanged;

protected:
    std::unique_ptr<VirtualTimeController> m_virtualTime;
    gloperate::Painter * m_painter;
    ResourceManager & m_resourceManager;
};

} /* namespace gloperate */
