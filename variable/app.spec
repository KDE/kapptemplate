echo "Creating $LOCATION_ROOT/$APP_NAME_LC.spec...";
cat << EOF > $LOCATION_ROOT/$APP_NAME_LC.spec
Name: ${APP_NAME_LC}
Summary: ${APP_NAME} -- Some description
Version: ${APP_VERSION}
Release: 1
Copyright: GPL
Group: X11/KDE/Utilities
Source: ftp.kde.org/pub/kde/unstable/apps/utils/${APP_NAME_LC}-${APP_VERSION}.tar.gz
Packager: ${AUTHOR} <${EMAIL}>
BuildRoot: /tmp/${APP_NAME_LC}-${APP_VERSION}
Prefix: /opt/kde

%description
A long description

%prep
rm -rf \$RPM_BUILD_ROOT
%setup -n ${APP_NAME_LC}-${APP_VERSION}

%build
./configure
make

%install
make DESTDIR=\$RPM_BUILD_ROOT install

%clean
rm -rf \$RPM_BUILD_ROOT

%files
%{prefix}/bin/${APP_NAME_LC}
%{prefix}/bin/${APP_NAME_LC}_client
%{prefix}/share/applnk/Utilities/${APP_NAME_LC}.desktop
%{prefix}/share/apps/${APP_NAME_LC}/
%{prefix}/share/doc/HTML/en/${APP_NAME_LC}/
%{prefix}/share/icons/medium/locolor/apps/${APP_NAME_LC}.png
%{prefix}/share/icons/small/locolor/apps/${APP_NAME_LC}.png
