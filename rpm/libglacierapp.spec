%define rname libglacierapp
%define libname libglacierapp-qt6-1
Name:       libglacierapp-qt6
Summary:    Glacier Application library
Version:    1.1
Release:    1
Group:      System/Libraries
License:    LGPL-2.0-or-later
URL:        https://github.com/nemomobile-ux/libglacierapp
Source0:    https://github.com/nemomobile-ux/%{rname}/archive/refs/tags/%{version}.tar.gz

BuildRequires:  cmake
BuildRequires:  pkgconfig(mlite6)
BuildRequires:  pkgconfig(Qt6Core)
BuildRequires:  pkgconfig(Qt6Qml)
BuildRequires:  pkgconfig(Qt6Quick)

%description
Wrapper library for glacier applications

%package -n %{libname}
Summary:    Glacier Application library

%description -n %{libname}
Wrapper library for glacier applications

%package devel
Summary:    Development package for %{name}
Group:      Development/Libraries
Requires:   %{libname} = %{version}-%{release}

%description devel
Development files for %{name}

%package examples
Summary:    Examples for %{name}
Group:      Development/Libraries
Requires:   %{libname} = %{version}-%{release}

%description examples
Development files for %{name}

%prep
%setup -q -n %{rname}-%{version}

%build
%cmake \
    -DBUILD_EXAMPLES=ON

%cmake_build

%install
rm -rf %{buildroot}
%cmake_install

%post -n %{libname} -p /sbin/ldconfig

%postun -n %{libname} -p /sbin/ldconfig

%files -n %{libname}
%defattr(-,root,root,-)
%{_libdir}/lib*.so.*

%files devel
%{_libdir}/lib*.so
%{_libdir}/pkgconfig/glacierapp6.pc
%{_libdir}/cmake/glacierapp6
%{_datadir}/cmake/Modules/QtVersionCompat.cmake
%{_includedir}/libglacierapp6

%files examples
%{_bindir}/glacierexample6

%changelog
