echo "Creating $LOCATION_ROOT/$APP_NAME_LC.spec...";
cat << EOF > $LOCATION_ROOT/$APP_NAME_LC.spec
%define distversion %( perl -e '$_=\<\>;/(\\d+)\\.(\\d)\\.?(\\d)?/; print "$1$2".($3||0)' /etc/*-release)
Name: ${APP_NAME_LC}
Summary: ${APP_NAME} -- Some description
Version: ${APP_VERSION}
Release: %{_vendor}_%{distversion}
Copyright: GPL
Group: X11/KDE/Utilities
Source: ftp://ftp.kde.org/pub/kde/unstable/apps/utils/%{name}-%{version}.tar.gz
Packager: ${AUTHOR} <${EMAIL}>
BuildRoot: /tmp/%{name}-%{version}
Prefix: `kde-config --prefix`

%description
A long description

%prep
rm -rf \$RPM_BUILD_ROOT
%setup -n %{name}-%{version}
CFLAGS="$RPM_OPT_FLAGS" CXXFLAGS="$RPM_OPT_FLAGS" ./configure \
	--disable-debug --enable-final --prefix=%{prefix}

%build
# Setup for parallel builds
numprocs=`egrep -c ^cpu[0-9]+ /proc/stat || :`
if [ "$numprocs" = "0" ]; then
  numprocs=1
fi

make -j$numprocs

%install
make install-strip DESTDIR=\$RPM_BUILD_ROOT

cd $RPM_BUILD_ROOT
find . -type d | sed '1,2d;s,^\.,\%attr(-\,root\,root) \%dir ,' > $RPM_BUILD_DIR/%{name}-master.list
find . -type f -o -type l | sed 's|^\.||' >> \$RPM_BUILD_DIR/%{name}-master.list

%clean
rm -rf \$RPM_BUILD_DIR/%{name}-%{version}
rm -rf \$RPM_BUILD_DIR/${name}-master.list

%files -f \$RPM_BUILD_DIR/%{name}-master.list
