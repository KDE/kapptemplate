#ifndef %{APPNAMEUC}RESOURCE_H
#define %{APPNAMEUC}RESOURCE_H

#include <AkonadiAgentBase/ResourceBase>

class %{APPNAME}Resource : public Akonadi::ResourceBase,
                           public Akonadi::AgentBase::Observer
{
    Q_OBJECT

public:
    %{APPNAME}Resource(const QString &id);
    ~%{APPNAME}Resource();

public Q_SLOTS:
    void configure(WId windowId) Q_DECL_OVERRIDE;

protected Q_SLOTS:
    void retrieveCollections() Q_DECL_OVERRIDE;
    void retrieveItems(const Akonadi::Collection &col) Q_DECL_OVERRIDE;
    bool retrieveItem(const Akonadi::Item &item, const QSet<QByteArray> &parts) Q_DECL_OVERRIDE;

protected:
    void aboutToQuit() Q_DECL_OVERRIDE;

    void itemAdded(const Akonadi::Item &item, const Akonadi::Collection &collection) Q_DECL_OVERRIDE;
    void itemChanged(const Akonadi::Item &item, const QSet<QByteArray> &parts) Q_DECL_OVERRIDE;
    void itemRemoved(const Akonadi::Item &item) Q_DECL_OVERRIDE;
};

#endif
