/****************************************************************************
 *
 * (c) 2009-2020 HMI PROJECT <http://www.HMI.org>
 *
 * HMI is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/


/// @file
///     @author Don Gagne <don@thegagnes.com>

import QtQuick 2.3
import QtQuick.Controls 1.2

import HMI.Controls 1.0
import HMI.Palette 1.0

HMIViewDialog {
    property string message

    HMIFlickable {
        anchors.fill:   parent
        contentHeight:  label.contentHeight

        HMILabel {
            id:             label
            anchors.left:   parent.left
            anchors.right:  parent.right
            wrapMode:       Text.WordWrap
            text:           message
        }
    }
}
