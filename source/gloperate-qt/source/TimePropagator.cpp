#include <gloperate-qt/TimePropagator.h>

#include <gloperate/tools/VirtualTimeController.h>


namespace gloperate_qt
{

/**
*  @brief
*    Constructor
*/
TimePropagator::TimePropagator(gloperate_qt::QtOpenGLWindowBase * window)
:   m_window(window)
,   m_controller(nullptr)
,   m_timer(new QTimer())
{
    // Connect to timer signal
    connect(m_timer.data(), SIGNAL(timeout()), this, SLOT(update()));

    // Start timer
    m_timer->setSingleShot(false);
    m_timer->start(0);
}

void TimePropagator::setController(gloperate::VirtualTimeController * controller)
{
    m_controller = controller;
}

/**
*  @brief
*    Called by the timer when the timer has elapsed
*/
void TimePropagator::update()
{
    if (!m_controller)
    {
        m_window->updateGL();
        return;
    }
    
    // Check if virtual time is enabled
    if (m_controller->active())
    {
        // Trigger update
        m_controller->update();
    }

    // Update window
    m_window->updateGL();
}

} // namespace gloperate_qt
