
#pragma once


#include <gloperate/pipeline/InputSlot.h>
#include <gloperate/pipeline/AbstractInput.h>


namespace gloperate
{


/**
*  @brief
*    Data input of a stage
*/
template <typename T>
class Input : public InputSlot<T, AbstractInput>
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] parent
    *    Parent stage (must NOT be null!)
    *  @param[in] name
    *    Property name
    *  @param[in] value
    *    Default value
    *
    *  @remarks
    *    The input is created and added to the given stage.
    */
    Input(Stage * parent, const std::string & name, const T & defaultValue = T());

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Input();
};


} // namespace cppexpose


#include <gloperate/pipeline/Input.hpp>