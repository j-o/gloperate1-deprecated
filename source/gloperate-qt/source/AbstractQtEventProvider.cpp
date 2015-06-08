#include <gloperate-qt/AbstractQtEventProvider.h>

#include <gloperate-qt/QtOpenGLWindow.h>

namespace gloperate_qt {

void AbstractQtEventProvider::passEventWithContext(QObject * obj, gloperate::AbstractEvent * event)
{
    auto window = dynamic_cast<QtOpenGLWindow*>(obj);

    if (window != nullptr)
    {
        window->makeCurrent();
    }

    passEvent(event);

    if (window != nullptr)
    {
        window->doneCurrent();
    }
}

} /* namespace gloperate_qt */
