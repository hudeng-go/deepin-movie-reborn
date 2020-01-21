#ifndef PRESENTER_H
#define PRESENTER_H

#include <QObject>
#include <MprisPlayer>
#include "mainwindow.h"
#include "mpv_proxy.h"
#include "player_engine.h"
#include "dmr_settings.h"
#include "notification_widget.h"
#include "toolbox_proxy.h"

using namespace dmr;

class Presenter : public QObject
{
    Q_OBJECT
public:
    explicit Presenter(MainWindow* mw, QObject *parent = nullptr);

    void initMpris(MprisPlayer *mprisPlayer);

signals:

public slots:
    void slotpause();
    void slotplaynext();
    void slotplayprev();
    void slotvolumeRequested(double volume);
    void slotopenUriRequested(const QUrl url);
    void slotstateChanged();

private:
    MainWindow* _mw = nullptr;
    MprisPlayer* m_mprisplayer=nullptr;
};

#endif // PRESENTER_H