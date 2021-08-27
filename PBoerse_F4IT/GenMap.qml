import QtQuick 2.0
import QtQuick.Window 2.14
import QtLocation 5.15
import QtPositioning 5.15



//Definition des Anzeigebereichs und der Variablen die aus C++ angesteuert werden können
Rectangle {
    width: 500
    height: 500
    property double centlat: 52.530644
    property double centlng: 13.383068
    property int zlvl: 11
    property double homelat: 52.530644
    property double homelng: 13.383068
    property double firmlat
    property double firmlng
    property string firmname
    property double firmlat1
    property double firmlng1
    property string firmname1
    property bool firmvis1
    property double firmlat2
    property double firmlng2
    property string firmname2
    property bool firmvis2
    property double firmlat3
    property double firmlng3
    property string firmname3
    property bool firmvis3
    property double firmlat4
    property double firmlng4
    property string firmname4
    property bool firmvis4
    property double firmlat5
    property double firmlng5
    property string firmname5
    property bool firmvis5
    property double firmlat6
    property double firmlng6
    property string firmname6
    property bool firmvis6
    property double firmlat7
    property double firmlng7
    property string firmname7
    property bool firmvis7
    property double firmlat8
    property double firmlng8
    property string firmname8
    property bool firmvis8
    property double firmlat9
    property double firmlng9
    property string firmname9
    property bool firmvis9
    property double firmlat10
    property double firmlng10
    property string firmname10
    property bool firmvis10
    property double firmlat11
    property double firmlng11
    property string firmname11
    property bool firmvis11
    property double firmlat12
    property double firmlng12
    property string firmname12
    property bool firmvis12
    property double firmlat13
    property double firmlng13
    property string firmname13
    property bool firmvis13
    property double firmlat14
    property double firmlng14
    property string firmname14
    property bool firmvis14
    property double firmlat15
    property double firmlng15
    property string firmname15
    property bool firmvis15


        //Verbindung zur Kartenwebsite
        Plugin {
                id: mapPlugin
                //name: "esri" //Alternative zu "here", läuft besser^^
                name: "here"
                parameters:
                PluginParameter {name: "here.app_id"
                       value: "G5QkjWjOys7cssvuX6x0"}
                PluginParameter {name: "here.token"
                       value: "qY3kPffSEqNyLYw8OleHjCcfKiUWBy9EIGIHIwC-u8o"}
                }

        //Erstellen und Zentrieren der Karte
        Map {

                id: map
                width: 500
                height: 500

                anchors.fill: parent
                plugin: mapPlugin
                center: QtPositioning.coordinate(centlat, centlng)
                zoomLevel: zlvl



            //Marker auf Homekoordinaten setzen
            MapQuickItem {
                    id: markerhome
                    anchorPoint.x: imagehome.width/2
                    anchorPoint.y: imagehome.height
                    coordinate: QtPositioning.coordinate(homelat, homelng)
                    sourceItem: Image {
                        id: imagehome
                        source: "pics/redmarker.png"
                        sourceSize.width: 42
                        sourceSize.height: 42
                        Text{
                            id: hometext
                            y: imagehome.height/10
                            x: imagehome.width
                            color: "red"
                            font.bold: true
                            font.pixelSize: 16
                            text : "Home"
                            }
                        MouseArea{
                            anchors.fill: parent
                           hoverEnabled: true
                           onClicked: {
                               console.log('clicked')
                              // https://blog.felgo.com/cross-platform-app-development/how-to-expose-a-qt-cpp-class-with-signals-and-slots-to-qml

                           }
                           onDoubleClicked: {
                               console.log('double-clicked')
                           }
                           onPressed: {
                               console.log('pressed')
                           }
                           onEntered: {
                               console.log('Entered')
                           }
                           onExited: {
                               console.log('Exited')
                           }
                        }

                        }

                }

            //Marker auf Firmenkoordinaten setzen
             /*MapQuickItem {
                        id: markerfirm
                        anchorPoint.x: imagefirm.width/2
                        anchorPoint.y: imagefirm.height
                        coordinate: QtPositioning.coordinate(firmlat, firmlng)
                        sourceItem: Image {
                            id: imagefirm
                            source: "pics/bluemarker.png"
                            sourceSize.width: 42
                            sourceSize.height: 42

                            Text{
                                id: firmtext
                                y: imagefirm.height/10
                                x: imagefirm.width
                                color: "blue"
                                font.bold: true
                                font.pixelSize: 16
                                text : firmname
                                }
                            }
                        }*/


             //Multiple Marker erstellen...

             MapQuickItem {
                       id: markerfirm1
                       anchorPoint.x: imagefirm1.width/2
                       anchorPoint.y: imagefirm1.height
                       coordinate: QtPositioning.coordinate(firmlat1, firmlng1)
                       visible: firmvis1
                       sourceItem: Image {
                           id: imagefirm1
                           source: "pics/bluemarker.png"
                           sourceSize.width: 42
                           sourceSize.height: 42

                           Text{
                               id: firmtext1
                               y: imagefirm1.height/10
                               x: imagefirm1.width
                               color: "blue"
                               font.bold: true
                               font.pixelSize: 16
                               text : firmname1
                               }
                           }
                       }

             MapQuickItem {
                       id: markerfirm2
                       anchorPoint.x: imagefirm2.width/2
                       anchorPoint.y: imagefirm2.height
                       coordinate: QtPositioning.coordinate(firmlat2, firmlng2)
                       visible: firmvis2
                       sourceItem: Image {
                           id: imagefirm2
                           source: "pics/bluemarker.png"
                           sourceSize.width: 42
                           sourceSize.height: 42

                           Text{
                               id: firmtext2
                               y: imagefirm2.height/10
                               x: imagefirm2.width
                               color: "blue"
                               font.bold: true
                               font.pixelSize: 16
                               text : firmname2
                               }
                           }
                       }

             MapQuickItem {
                       id: markerfirm3
                       anchorPoint.x: imagefirm3.width/2
                       anchorPoint.y: imagefirm3.height
                       coordinate: QtPositioning.coordinate(firmlat3, firmlng3)
                       visible: firmvis3
                       sourceItem: Image {
                           id: imagefirm3
                           source: "pics/bluemarker.png"
                           sourceSize.width: 42
                           sourceSize.height: 42

                           Text{
                               id: firmtext3
                               y: imagefirm3.height/10
                               x: imagefirm3.width
                               color: "blue"
                               font.bold: true
                               font.pixelSize: 16
                               text : firmname3
                               }
                           }
                       }

             MapQuickItem {
                       id: markerfirm4
                       anchorPoint.x: imagefirm4.width/2
                       anchorPoint.y: imagefirm4.height
                       coordinate: QtPositioning.coordinate(firmlat4, firmlng4)
                       visible: firmvis4
                       sourceItem: Image {
                           id: imagefirm4
                           source: "pics/bluemarker.png"
                           sourceSize.width: 42
                           sourceSize.height: 42

                           Text{
                               id: firmtext4
                               y: imagefirm4.height/10
                               x: imagefirm4.width
                               color: "blue"
                               font.bold: true
                               font.pixelSize: 16
                               text : firmname4
                               }
                           }
                       }


             MapQuickItem {
                       id: markerfirm5
                       anchorPoint.x: imagefirm5.width/2
                       anchorPoint.y: imagefirm5.height
                       coordinate: QtPositioning.coordinate(firmlat5, firmlng5)
                       visible: firmvis5
                       sourceItem: Image {
                           id: imagefirm5
                           source: "pics/bluemarker.png"
                           sourceSize.width: 42
                           sourceSize.height: 42

                           Text{
                               id: firmtext5
                               y: imagefirm5.height/10
                               x: imagefirm5.width
                               color: "blue"
                               font.bold: true
                               font.pixelSize: 16
                               text : firmname5
                               }
                           }
                       }

             MapQuickItem {
                       id: markerfirm6
                       anchorPoint.x: imagefirm6.width/2
                       anchorPoint.y: imagefirm6.height
                       coordinate: QtPositioning.coordinate(firmlat6, firmlng6)
                       visible: firmvis6
                       sourceItem: Image {
                           id: imagefirm6
                           source: "pics/bluemarker.png"
                           sourceSize.width: 42
                           sourceSize.height: 42

                           Text{
                               id: firmtext6
                               y: imagefirm6.height/10
                               x: imagefirm6.width
                               color: "blue"
                               font.bold: true
                               font.pixelSize: 16
                               text : firmname6
                               }
                           }
                       }

             MapQuickItem {
                       id: markerfirm7
                       anchorPoint.x: imagefirm7.width/2
                       anchorPoint.y: imagefirm7.height
                       coordinate: QtPositioning.coordinate(firmlat7, firmlng7)
                       visible: firmvis7
                       sourceItem: Image {
                           id: imagefirm7
                           source: "pics/bluemarker.png"
                           sourceSize.width: 42
                           sourceSize.height: 42

                           Text{
                               id: firmtext7
                               y: imagefirm7.height/10
                               x: imagefirm7.width
                               color: "blue"
                               font.bold: true
                               font.pixelSize: 16
                               text : firmname7
                               }
                           }
                       }

             MapQuickItem {
                       id: markerfirm8
                       anchorPoint.x: imagefirm8.width/2
                       anchorPoint.y: imagefirm8.height
                       coordinate: QtPositioning.coordinate(firmlat8, firmlng8)
                       visible: firmvis8
                       sourceItem: Image {
                           id: imagefirm8
                           source: "pics/bluemarker.png"
                           sourceSize.width: 42
                           sourceSize.height: 42

                           Text{
                               id: firmtext8
                               y: imagefirm8.height/10
                               x: imagefirm8.width
                               color: "blue"
                               font.bold: true
                               font.pixelSize: 16
                               text : firmname8
                               }
                           }
                       }

             MapQuickItem {
                       id: markerfirm9
                       anchorPoint.x: imagefirm9.width/2
                       anchorPoint.y: imagefirm9.height
                       coordinate: QtPositioning.coordinate(firmlat9, firmlng9)
                       visible: firmvis9
                       sourceItem: Image {
                           id: imagefirm9
                           source: "pics/bluemarker.png"
                           sourceSize.width: 42
                           sourceSize.height: 42

                           Text{
                               id: firmtext9
                               y: imagefirm9.height/10
                               x: imagefirm9.width
                               color: "blue"
                               font.bold: true
                               font.pixelSize: 16
                               text : firmname9
                               }
                           }
                       }

             MapQuickItem {
                       id: markerfirm10
                       anchorPoint.x: imagefirm10.width/2
                       anchorPoint.y: imagefirm10.height
                       coordinate: QtPositioning.coordinate(firmlat10, firmlng10)
                       visible: firmvis10
                       sourceItem: Image {
                           id: imagefirm10
                           source: "pics/bluemarker.png"
                           sourceSize.width: 42
                           sourceSize.height: 42

                           Text{
                               id: firmtext10
                               y: imagefirm10.height/10
                               x: imagefirm10.width
                               color: "blue"
                               font.bold: true
                               font.pixelSize: 16
                               text : firmname10
                               }
                           }
                       }

             MapQuickItem {
                       id: markerfirm11
                       anchorPoint.x: imagefirm11.width/2
                       anchorPoint.y: imagefirm11.height
                       coordinate: QtPositioning.coordinate(firmlat11, firmlng11)
                       visible: firmvis11
                       sourceItem: Image {
                           id: imagefirm11
                           source: "pics/bluemarker.png"
                           sourceSize.width: 42
                           sourceSize.height: 42

                           Text{
                               id: firmtext11
                               y: imagefirm11.height/10
                               x: imagefirm11.width
                               color: "blue"
                               font.bold: true
                               font.pixelSize: 16
                               text : firmname11
                               }
                           }
                       }


             MapQuickItem {
                       id: markerfirm12
                       anchorPoint.x: imagefirm12.width/2
                       anchorPoint.y: imagefirm12.height
                       coordinate: QtPositioning.coordinate(firmlat12, firmlng12)
                       visible: firmvis12
                       sourceItem: Image {
                           id: imagefirm12
                           source: "pics/bluemarker.png"
                           sourceSize.width: 42
                           sourceSize.height: 42

                           Text{
                               id: firmtext12
                               y: imagefirm12.height/10
                               x: imagefirm12.width
                               color: "blue"
                               font.bold: true
                               font.pixelSize: 16
                               text : firmname12
                               }
                           }
                       }


             MapQuickItem {
                       id: markerfirm13
                       anchorPoint.x: imagefirm13.width/2
                       anchorPoint.y: imagefirm13.height
                       coordinate: QtPositioning.coordinate(firmlat13, firmlng13)
                       visible: firmvis13
                       sourceItem: Image {
                           id: imagefirm13
                           source: "pics/bluemarker.png"
                           sourceSize.width: 42
                           sourceSize.height: 42

                           Text{
                               id: firmtext13
                               y: imagefirm13.height/10
                               x: imagefirm13.width
                               color: "blue"
                               font.bold: true
                               font.pixelSize: 16
                               text : firmname13
                               }
                           }
                       }


             MapQuickItem {
                       id: markerfirm14
                       anchorPoint.x: imagefirm14.width/2
                       anchorPoint.y: imagefirm14.height
                       coordinate: QtPositioning.coordinate(firmlat14, firmlng14)
                       visible: firmvis14
                       sourceItem: Image {
                           id: imagefirm14
                           source: "pics/bluemarker.png"
                           sourceSize.width: 42
                           sourceSize.height: 42

                           Text{
                               id: firmtext14
                               y: imagefirm14.height/10
                               x: imagefirm14.width
                               color: "blue"
                               font.bold: true
                               font.pixelSize: 16
                               text : firmname14
                               }
                           }
                       }


             MapQuickItem {
                       id: markerfirm15
                       anchorPoint.x: imagefirm15.width/2
                       anchorPoint.y: imagefirm15.height
                       coordinate: QtPositioning.coordinate(firmlat15, firmlng15)
                       visible: firmvis15
                       sourceItem: Image {
                           id: imagefirm15
                           source: "pics/bluemarker.png"
                           sourceSize.width: 42
                           sourceSize.height: 42

                           Text{
                               id: firmtext15
                               y: imagefirm15.height/10
                               x: imagefirm15.width
                               color: "blue"
                               font.bold: true
                               font.pixelSize: 16
                               text : firmname15
                               }
                           }
                       }
               }
        }
