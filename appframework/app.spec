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
Prefix: /opt/kde2

%description
A long description

%prep
rm -rf \$RPM_BUILD_ROOT
%setup -n ${APP_NAME_LC}-${APP_VERSION}

%build
./configure --disable-debug --enable-final --prefix=%{prefix}
make

%install
make DESTDIR=\$RPM_BUILD_ROOT install
find . -type f -o -type l | sed 's|^\.||' > \$RPM_BUILD_ROOT/master.list

%clean
rm -rf \$RPM_BUILD_ROOT

%files -f \$RPM_BUILD_ROOT/master.list
