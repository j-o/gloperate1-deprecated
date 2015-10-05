
#pragma once


#include <gloperate/ext-includes-begin.h>
#include <QObject>
#include <QTimer>
#include <QScopedPointer>
#include <QWidget>
#include <gloperate/ext-includes-end.h>

#include <gloperate-qt/viewer/QtOpenGLWindowBase.h>
#include <gloperate-qt/gloperate-qt_api.h>


namespace gloperate
{
class VirtualTimeController;
}


namespace gloperate_qt
{


/**
*  @brief
*    Tool class to propagate continuous time updates to a window
*
*  @remarks
*    This class is used in a window to allow for continuous updates (e.g., to
*    implement animations). It take a VirtualTimeCapability of a painter to
*    propagate the time change to the painter, and automatically triggers
*    an update of the window containing the painter.
*/
class GLOPERATE_QT_API TimePropagator : public QObject
{
    Q_OBJECT


public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] window
    *    Window that is updated when the timer has elapsed
    *  @param[in] capability
    *    VirtualTimeCapability that is informed about the time change
    */
    TimePropagator(gloperate_qt::QtOpenGLWindowBase * window);
    
    void setController(gloperate::VirtualTimeController * controller);


protected slots:
    /**
    *  @brief
    *    Called by the timer when the timer has elapsed
    */
    void update();


protected:
    gloperate_qt::QtOpenGLWindowBase         * m_window;     /**< Window that is updated when the timer has elapsed */
    gloperate::VirtualTimeController         * m_controller; /**< VirtualTimeController that is triggered */
    QScopedPointer<QTimer> m_timer; /**< Qt timer for continuous updates */
};


} // namespace gloperate_qt
