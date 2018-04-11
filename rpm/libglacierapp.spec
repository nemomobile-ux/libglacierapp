%{!?qtc_qmake:%define qtc_qmake %qmake}
%{!?qtc_qmake5:%define qtc_qmake5 %qmake5}
%{!?qtc_make:%define qtc_make make}
%{?qtc_builddir:%define _builddir %qtc_builddir}

Name:       libglacierapp
Summary:    Glacier Application library
Version:    0.2
Release:    1
Group:      System/Libraries
License:    LGPL
URL:        https://github.com/nemomobile-ux/libglacierapp
Source0:    %{name}-%{version}.tar.bz2

BuildRequires:  pkgconfig(Qt5Core)
BuildRequires:  pkgconfig(Qt5Qml)
BuildRequires:  pkgconfig(Qt5Quick)

%description
Wrapper librarary for glacier applications

%package devel
Summary:    Development package for %{name}
Group:      Development/Libraries
Requires:   %{name} = %{version}-%{release}

%description devel
Development files for %{name}

%package examples
Summary:    Examples for %{name}
Group:      Development/Libraries
Requires:   %{name} = %{version}-%{release}

%description examples
Development files for %{name}

%prep
%setup -q -n %{name}-%{version}

%build
%qtc_qmake5  VERSION=%{version}
%qtc_make

%install
rm -rf %{buildroot}
%qmake5_install

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%defattr(-,root,root,-)
%{_libdir}/lib*.so.*

%files devel
%{_libdir}/lib*.so
%{_libdir}/pkgconfig/glacierapp.pc
%{_includedir}/%{name}

%files examples
%{_bindir}
%{_datadir}/glacierexample
