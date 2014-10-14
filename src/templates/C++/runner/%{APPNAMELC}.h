
#ifndef %{APPNAMEUC}_H
#define %{APPNAMEUC}_H

#include <plasma/abstractrunner.h>
#include <KIcon>

// Define our plasma Runner
class %{APPNAME} : public Plasma::AbstractRunner {
    Q_OBJECT

public:
    // Basic Create/Destroy
    %{APPNAME}( QObject *parent, const QVariantList& args );
    ~%{APPNAME}();

    void match(Plasma::RunnerContext &context);
    void run(const Plasma::RunnerContext &context, const Plasma::QueryMatch &match);
};
// This is the command that links your applet to the .desktop file
K_EXPORT_PLASMA_RUNNER(%{APPNAMELC}, %{APPNAME})

#endif
