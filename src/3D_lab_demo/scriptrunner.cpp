#include "scriptrunner.h"

#include <QProcess>

const auto kDefaultText{QByteArray("Hello World")};
const auto kScriptName{QString("demo_script.sh")};

ScriptRunner::ScriptRunner(QObject *parent)
    : QObject(parent)
    , mText(kDefaultText)
{
   connect(&mProcess,
           &QProcess::readyReadStandardOutput,
           this,
           &ScriptRunner::handleReadyReadStandardOutput);

   connect(&mProcess,
           &QProcess::errorOccurred,
           this,
           &ScriptRunner::handleErrorOccurred);
}

QByteArray ScriptRunner::getText() const
{
    return mText;
}

bool ScriptRunner::isError() const
{
    return mIsError;
}

void ScriptRunner::trigger()
{
    mProcess.start(kScriptName);
}

void ScriptRunner::handleReadyReadStandardOutput()
{
    mIsError = false;
    mText = mProcess.readAllStandardOutput();

    emit textChanged();
}

void ScriptRunner::handleErrorOccurred(QProcess::ProcessError error)
{
    const QByteArray errorText = [error] {
        switch (error)
        {
        case QProcess::FailedToStart:
            return QByteArray("Failed to start");
        case QProcess::Crashed:
            return QByteArray("Crashed");
        case QProcess::Timedout:
            return QByteArray("Timed out");
        case QProcess::ReadError:
            return QByteArray("Read error");
        case QProcess::WriteError:
            return QByteArray("Write error");
        case QProcess::UnknownError:
            return QByteArray("Unknown error");
        }
    }();

    mIsError = true;
    mText = errorText;

    emit textChanged();
}
