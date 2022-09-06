Name:           EFL-Border-Sample
Version:        0.0.1
Release:        0
License:        Apache-2.0
Summary:        Window Border test sample
Group:          UI Framework
Source:         %{name}-%{version}.tar.gz
Source1001:     %{name}.manifest

BuildRequires:  meson
BuildRequires:  pkgconfig(elementary)
BuildRequires:  pkgconfig(appcore-efl)
BuildRequires:  pkgconfig(dlog)

%description
This is sample application for Window Border test.

%prep
%setup -q
cp %{SOURCE1001} .
meson \
	  --prefix /usr \
	  builddir

%build
ninja -C builddir all

%install
export DESTDIR=%{buildroot}
ninja -C builddir install

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%manifest %{name}.manifest
%defattr(-,root,root)
/usr/apps/%{name}/*
/usr/share/packages/%{name}.xml
