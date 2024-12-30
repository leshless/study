Name: texlive-mensa-tex
Summary: A flexible LaTeX2 class for typesetting school cafeteria menus
License: LPPL1.3
Version: 20171203
Release: 1
URL: http://www.ctan.org/tex-archive/macros/latex/contrib/mensa-tex
Group: Publishing
Source0: mensa-tex.tar.xz
Source1: mensa-tex.doc.tar.xz
BuildArch: noarch
BuildRequires: texlive-tlpkg
Requires(pre): texlive-tlpkg
Requires(post): texlive-kpathsea

%description
A LaTeX class for typesetting school cafeteria menus consisting
of two lunches (with dessert) and dinner. This work, 
consisting of the files mensa-tex.cls, mensa-tex-doc.tex and
mensa-tex-example.tex, is licensed under the LPPL, Version 1.3c
(or, at your option, any later version). Current maintainer
of the work is Sebastian Friedl. The file cafe-logo.png
used with mensa-tex-example.tex is licensed as public domain.
It is not part of this work, although it is required to
compile mensa-tex-example.tex. mensa-tex requires LaTeX2e
and depends on the packages array, colortbl, datetime2,
datetime2-calc, geometry, graphicx, lmodern, textcomp
and xcolor

%files
%{_texmfdistdir}/tex/latex/mensa-tex
%doc %{_texmfdistdir}/doc/latex/mensa-tex

%prep
%setup -c -a0 -a1

%build

%install
mkdir -p %{buildroot}%{_texmfdistdir}
cp -fpar tex doc %{buildroot}%{_texmfdistdir}
