#include "%{APPNAMELC}.h"

#include <QDebug>

K_EXPORT_PLASMA_RUNNER(%{APPNAMELC}, %{APPNAME})

%{APPNAME}::%{APPNAME}(QObject *parent, const QVariantList& args)
    : Plasma::AbstractRunner(parent, args)
{
    Q_UNUSED(args);
    setObjectName("%{APPNAME}");
}

%{APPNAME}::~%{APPNAME}()
{
}


void %{APPNAME}::match(Plasma::RunnerContext &context)
{

    const QString term = context.query();
    if (term.length() < 3) {
        return;
    }
    //TODO
}

void %{APPNAME}::run(const Plasma::RunnerContext &context, const Plasma::QueryMatch &match)
{
    Q_UNUSED(context)
    Q_UNUSED(match)
}

#include "%{APPNAMELC}.moc"
