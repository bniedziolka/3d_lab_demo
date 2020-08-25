#ifndef SCRIPTRUNNER_H
#define SCRIPTRUNNER_H

#include <QObject>
#include <QProcess>

class ScriptRunner : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QByteArray text READ getText NOTIFY textChanged)
    Q_PROPERTY(bool isError READ isError NOTIFY textChanged)

public:
    explicit ScriptRunner(QObject *parent = nullptr);

    QByteArray getText() const;
    bool isError() const;

signals:
    void textChanged();

public slots:
    void trigger();

private:
    void handleReadyReadStandardOutput();
    void handleErrorOccurred(QProcess::ProcessError error);

    QProcess mProcess;
    QByteArray mText;
    bool mIsError{false};
};

#endif // SCRIPTRUNNER_H
