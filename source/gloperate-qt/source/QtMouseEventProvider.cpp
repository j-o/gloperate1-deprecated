/******************************************************************************\
 * gloperate
 *
 * Copyright (C) 2014 Computer Graphics Systems Group at the
 * Hasso-Plattner-Institut (HPI), Potsdam, Germany.
\******************************************************************************/
#include <gloperate-qt/QtMouseEventProvider.h>

#include <gloperate/input/input.h>
#include <gloperate/input/MouseEvent.h>

#include <gloperate-qt/QtEventTransformer.h>

using namespace gloperate;

namespace gloperate_qt
{

/**
*  @brief
*    Constructor
*/
QtMouseEventProvider::QtMouseEventProvider()
{
}

/**
*  @brief
*    Destructor
*/
QtMouseEventProvider::~QtMouseEventProvider()
{
}

bool QtMouseEventProvider::eventFilter(QObject * obj, QEvent * event)
{
    if (event->type() == QEvent::MouseButtonPress ||
        event->type() == QEvent::MouseButtonRelease ||
        event->type() == QEvent::MouseButtonDblClick ||
        event->type() == QEvent::MouseMove)
    {
        QMouseEvent * qMouseEvent = dynamic_cast<QMouseEvent*>(event);
        if (qMouseEvent) {
            auto eventType = QtEventTransformer::mouseTypeFromQtType(qMouseEvent->type());
            auto position = QtEventTransformer::fromQPoint(qMouseEvent->pos());
            auto button = QtEventTransformer::fromQtMouseButton(qMouseEvent->button());
            auto buttonMask = QtEventTransformer::fromQtMouseButtons(qMouseEvent->buttons());
            MouseEvent * mouseEvent =
                    new MouseEvent(eventType,
                                      position,
                                      button,
                                      buttonMask,
                                      static_cast<int>(qMouseEvent->modifiers()));
            passEventWithContext(obj, mouseEvent);
            return false;
        }
    }

    if (event->type() == QEvent::Enter ||
        event->type() == QEvent::Leave)
    {
        auto buttonMask = NoMouseButton;
        QMouseEvent * qMouseEvent = dynamic_cast<QMouseEvent*>(event);
        if (qMouseEvent)
        {
            buttonMask = QtEventTransformer::fromQtMouseButtons(qMouseEvent->buttons());
        }

        auto eventType = QtEventTransformer::mouseTypeFromQtType(event->type());
        MouseEvent * mouseEvent =
                new MouseEvent(eventType, glm::ivec2(),NoMouseButton, buttonMask, static_cast<int>(Qt::NoModifier));
        passEventWithContext(obj, mouseEvent);
        return false;
    }
    return QObject::eventFilter(obj, event);
}

} // namespace gloperate_qt
