Name: texlive-hebdomon
Summary: A document class for report writing in university settings
License: LPPL1.3
Version: 0.1
Release: 1
URL: https://www.ctan.org/tex-archive/macros/latex/contrib/hebdomon
Group: Publishing
Source0: hebdomon.tar.xz
Source1: hebdomon.doc.tar.xz
BuildArch: noarch
BuildRequires: texlive-tlpkg
Requires(pre): texlive-tlpkg
Requires(post): texlive-kpathsea

%description
This package provides a documentclass for streamlining document
creation in LaTeX. It does not overwrite any TeX or LaTeX
commands so the user could use their own macros or other
commands as they wish.

%files
%{_texmfdistdir}/tex/latex/hebdomon
%doc %{_texmfdistdir}/doc/latex/hebdomon

%prep
%setup -c -a0 -a1

%build

%install
mkdir -p %{buildroot}%{_texmfdistdir}
cp -fpar tex doc %{buildroot}%{_texmfdistdir}
