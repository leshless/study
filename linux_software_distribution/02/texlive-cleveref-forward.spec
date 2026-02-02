Name: texlive-cleveref-forward
Summary: Package provides the forward-referencing functionality for the package cleveref
License: LPPL1.3
Version: 20240315
Release: 1
URL: http://www.ctan.org/tex-archive/macros/latex/contrib/cleveref-forward
Group: Publishing
Source0: cleveref-forward.tar.xz
Source1: cleveref-forward.doc.tar.xz
BuildArch: noarch
BuildRequires: texlive-tlpkg
Requires(pre): texlive-tlpkg
Requires(post): texlive-kpathsea

%description
This package aims at providing the forward-referencing
functionality for the package cleveref.
It is derived from the package cleveref-usedon,
with several fixes and enhancements.

%files
%{_texmfdistdir}/tex/latex/cleveref-forward
%doc %{_texmfdistdir}/doc/latex/cleveref-forward

%prep
%setup -c -a0 -a1

%build

%install
mkdir -p %{buildroot}%{_texmfdistdir}
cp -fpar tex doc %{buildroot}%{_texmfdistdir}