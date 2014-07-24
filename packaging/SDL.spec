%define aalib   0
%bcond_with x

Name:           SDL
Version:        1.2.15
Release:        0
License:        LGPL-2.1+
Summary:        Simple DirectMedia Layer Library
Url:            http://www.libsdl.org/
Group:          System/Libraries
Source:         http://www.libsdl.org/release/SDL-%{version}.tar.gz
Source2:        baselibs.conf
Source1001: 	SDL.manifest
BuildRequires:  autoconf
BuildRequires:  gcc-c++
BuildRequires:  libpulse-devel
BuildRequires:  libstdc++-devel
BuildRequires:  mesa-devel
BuildRequires:  nasm
BuildRequires:  pkgconfig
BuildRequires:  pkgconfig(alsa)
BuildRequires:  pkgconfig(glib-2.0)
BuildRoot:      %{_tmppath}/%{name}-%{version}-build

%description
This is the "Simple DirectMedia Layer" library. It provides a generic
API for access to audio, keyboard, mouse, and display framebuffer
across multiple platforms.

%package -n libSDL
Summary:        Simple DirectMedia Layer Library
Group:          System/Libraries
# SDL was used last in 11.1
Provides:       SDL = %{version}
Obsoletes:      SDL < %{version}

%description -n libSDL
This is the "Simple DirectMedia Layer" library. It provides a generic
API for access to audio, keyboard, mouse, and display framebuffer
across multiple platforms.

%package -n libSDL-devel
Summary:        SDL Library Developer Files
Group:          Development/Libraries/X11
Requires:       gcc
Requires:       libSDL = %{version}
Requires:       libstdc++-devel
Requires:       mesa-devel
Requires:       pkgconfig
Requires:       pkgconfig(alsa)
%if %{with x}
Requires:       pkgconfig(glu)
%endif
Provides:       SDL-devel = %{version}
Obsoletes:      SDL-devel < %{version}

%description -n libSDL-devel
This package contains files needed for development with the SDL
library.

%prep
%setup -q
cp %{SOURCE1001} .

# remove the file to provide sufficient evidence that we are
# not using this file during the build [bnc#508111]
rm -f src/joystick/darwin/10.3.9-FIX/IOHIDLib.h

%build
./autogen.sh
%configure \
    --disable-static \
    --with-pic \
    --disable-rpath \
    --disable-alsa-shared \
%if 0%{?aalib}
    --enable-video-aalib \
%endif
    --disable-video-svga \
    --disable-video-ps3
make %{?_smp_mflags}

%install
%make_install

%post -n libSDL -p /sbin/ldconfig

%postun -n libSDL -p /sbin/ldconfig

%files -n libSDL
%manifest %{name}.manifest
%defattr(-,root,root)
%doc COPYING
%{_libdir}/*.so.*

%files -n libSDL-devel
%manifest %{name}.manifest
%defattr(-,root,root)
%{_bindir}/*
%{_libdir}/*.so
%{_includedir}/SDL
%{_datadir}/aclocal
%{_mandir}/*/*
%{_libdir}/pkgconfig/sdl.pc

%changelog
