echo "Creating $LOCATION_ROOT/$APP_NAME_LC.spec...";
cat << EOF > $LOCATION_ROOT/$APP_NAME_LC.spec
Name: ${APP_NAME_LC}
Summary: ${APP_NAME} -- Some description
Version: ${APP_VERSION}
Release: 1
Copyright: GPL
Group: X11/KDE/Utilities
Source: ftp://ftp.kde.org/pub/kde/unstable/apps/utils/${APP_NAME_LC}-${APP_VERSION}.tar.gz
Packager: ${AUTHOR} <${EMAIL}>
BuildRoot: /tmp/${APP_NAME_LC}-${APP_VERSION}
Prefix: `kde-config --prefix`

%description
A long description

%prep
rm -rf \$RPM_BUILD_ROOT
%setup -n ${APP_NAME_LC}-${APP_VERSION}

%build
CFLAGS="$RPM_OPT_FLAGS" CXXFLAGS="$RPM_OPT_FLAGS" ./configure \
	--disable-debug --enable-final --prefix=%{prefix}

# Setup for parallel builds
numprocs=`egrep -c ^cpu[0-9]+ /proc/stat || :`
if [ "$numprocs" = "0" ]; then
  numprocs=1
fi

make -j$numprocs

%install
make DESTDIR=\$RPM_BUILD_ROOT install

cd $RPM_BUILD_ROOT
find . -type d | sed '1,2d;s,^\.,\%attr(-\,root\,root) \%dir ,' > $RPM_BUILD_DIR/${APP_NAME_LC}-kdoomload-master.list
find . -type f -o -type l | sed 's|^\.||' > \$RPM_BUILD_DIR/${APP_NAME_LC}-master.list

%clean
rm -rf \$RPM_BUILD_DIR/${APP_NAME_LC}-${APP_VERSION}
rm -rf \$RPM_BUILD_DIR/${APP_NAME_LC}-master.list

%files -f \$RPM_BUILD_DIR/master.list
