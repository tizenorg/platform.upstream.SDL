Name:       org.tizen.sdl2_test
Summary:    sdl2demo
Version:    0.1
Release:    1
Group:      TO_BE/FILLED_IN
License:    Apache
Source0:    %{name}-%{version}.tar.gz

BuildRequires:  edje-bin
BuildRequires:  pkgconfig(dlog)

BuildRequires:  cmake
BuildRequires:  edje-bin
BuildRequires:  embryo-bin
BuildRequires:  gettext-devel


%define _packagedir /opt/usr/apps/%{name}
%define _resdir %{_packagedir}/res



Autoreq: no


%description
Description: sdl_test

%package devel
Summary:    sdl_test library development headers
Group:      Development/Libraries
Requires:   %{name} = %{version}

%description devel
Web App Service library development headers
%prep
%setup -q

%build
export CFLAGS="$CFLAGS %{?__vd_cflags}  -Wno-error"
export CXXFLAGS="$CXXFLAGS %{?__vd_cxxflags} -Wno-error"
cmake . \
	-DCMAKE_INSTALL_PREFIX=%{_packagedir} \
	-DPACKAGE_NAME=%{name} \
	-DVERSION=%{version} \
	-DTIZEN_VERSION=%{tizen}
#make %{?jobs:-j%jobs}
#output different color when make error
make 2>&1 %{?jobs:-j%jobs} | sed -e 's%^.*: error: .*$%\x1b[37;41m&\x1b[m%' -e  's%^.*: warning: .*$%\x1b[30;43m&\x1b[m%'

%install
rm -rf %{buildroot}

%make_install


%clean
rm -rf %{buildroot}

%post

%files
%defattr(-,root,root,-)
%attr(755,root,root) %{_packagedir}/*


%files devel
