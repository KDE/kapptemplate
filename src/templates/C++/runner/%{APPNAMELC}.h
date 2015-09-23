#ifndef %{APPNAMEUC}_H
#define %{APPNAMEUC}_H

#include <krunner/abstractrunner.h>

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

#endif
