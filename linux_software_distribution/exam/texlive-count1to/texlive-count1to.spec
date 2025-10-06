Name: texlive-count1to
Summary: Make use of count1 to count9
License: LPPL1.3
Version: 2.11
Release: 1
URL: https://www.ctan.org/tex-archive/macros/latex/contrib/count1to
Group: Publishing
Source0: count1to.tar.xz
Source1: count1to.source.tar.xz
Source2: count1to.doc.tar.xz
BuildArch: noarch
BuildRequires: texlive-tlpkg
Requires(pre): texlive-tlpkg
Requires(post): texlive-kpathsea

%description
A LaTeX package which sets count 1 (to ‘absolute’ page number),
counts 2–8 to the numbers of the current \part, \chapter
(always 0 in article class), ... \subparagraph, and count
9 to 1 or 0, according to whether the page is odd or even.
These values can be used to select pages with some drivers.

%files
%{_texmfdistdir}/tex/latex/count1to
%doc %{_texmfdistdir}/source/latex/count1to
%doc %{_texmfdistdir}/doc/latex/count1to

%prep
%setup -c -a0 -a1 -a2

%build

%install
mkdir -p %{buildroot}%{_texmfdistdir}
cp -fpar tex source doc %{buildroot}%{_texmfdistdir}