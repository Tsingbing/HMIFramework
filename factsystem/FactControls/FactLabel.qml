import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.4

import HMI.FactSystem 1.0
import HMI.Palette 1.0
import HMI.Controls 1.0

HMILabel {
    property Fact fact: Fact { }
    text: fact.valueString
}
