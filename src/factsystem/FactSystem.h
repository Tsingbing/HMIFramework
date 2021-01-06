/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#pragma once

#include "Fact.h"
#include "FactMetaData.h"
#include "Tool.h"
#include "Toolbox.h"

///FactSystem是一个具有单个数值的Fact。FactMetaData保存与Fact相关联的附加元数据，如描述、最小/最大范围等。

class FactSystem : public Tool
{
    Q_OBJECT

public:
    FactSystem(XApplication* app, Toolbox* toolbox);

    // Override from QGCTool
    virtual void setToolbox(Toolbox* toolbox);

    typedef enum
    {
        ParameterProvider,
    } Provider_t;

    static const int defaultComponentId = -1;

private:
    static const char* _factSystemQmlUri; ///< URI for FactSystem QML imports
};
