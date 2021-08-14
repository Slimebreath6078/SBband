%define version 1.1.0b
%define release 3

Summary: SBband %{version}
Name: SBband
Version: %{version}
Release: %{release}
Copyright: unknown
Group: Amusements/Games
Packager: Takahiro MIZUNO <tow@plum.freemail.ne.jp>
Url: http://echizen.s5.xrea.com/heng/index.html
Source: SBband-%{version}.tar.bz2
Buildroot: %{_tmppath}/%{name}-%{version}-root

%description
SBband is a variant of Hengband.

Official page is this,
http://echizen.s5.xrea.com/heng/eng-SBband/index.html

More infomation is /usr/doc/SBband-hoge/readme_eng.txt

Summary(ja): SBband %{version}

%description -l ja
SBbandは 変愚蛮怒 のバリアントです。

本ソフトウェアの最新版は以下の場所から入手できます。
http://echizen.s5.xrea.com/heng/index.html

詳しくは /usr/doc/SBband-hoge/readme.txt を参照。

%prep
rm -rf $RPM_BUILD_ROOT

%setup -n %{name}-%{version}

%build
./configure --prefix=%{_prefix} --bindir=%{_bindir} --with-libpath=%{_datadir}/games/SBband/lib
make

%install
mkdir -p $RPM_BUILD_ROOT/%{_bindir}
mkdir -p $RPM_BUILD_ROOT/%{_datadir}/games/SBband
cp src/SBband $RPM_BUILD_ROOT/%{_bindir}
cp -R lib/ -p $RPM_BUILD_ROOT/%{_datadir}/games/SBband/
touch $RPM_BUILD_ROOT/%{_datadir}/games/SBband/lib/apex/scores.raw

%clean
rm -rf $RPM_BUILD_ROOT

%preun
if [ -e %{_datadir}/games/SBband/lib/data/f_info_j.raw ]
then
rm -rf %{_datadir}/games/SBband/lib/data/*.raw
fi
exit 0

%files
%defattr(-,root,root)
%attr(2755,root,games) %{_bindir}/SBband
%dir %{_datadir}/games/SBband/lib
%attr(775,root,games) %dir %{_datadir}/games/SBband/lib/apex
%attr(775,root,games) %dir %{_datadir}/games/SBband/lib/bone
%attr(775,root,games) %dir %{_datadir}/games/SBband/lib/data
%dir %{_datadir}/games/SBband/lib/edit
%dir %{_datadir}/games/SBband/lib/file
%dir %{_datadir}/games/SBband/lib/help
%dir %{_datadir}/games/SBband/lib/info
%dir %{_datadir}/games/SBband/lib/pref
%attr(775,root,games) %dir %{_datadir}/games/SBband/lib/save
%dir %{_datadir}/games/SBband/lib/script
%dir %{_datadir}/games/SBband/lib/user
%dir %{_datadir}/games/SBband/lib/xtra
%dir %{_datadir}/games/SBband/lib/xtra/graf
%{_datadir}/games/SBband/lib/apex/h_scores.raw
%{_datadir}/games/SBband/lib/apex/readme.txt
%attr(664 root,games) %config(noreplace) %{_datadir}/games/SBband/lib/apex/scores.raw
%{_datadir}/games/SBband/lib/bone/delete.me
%{_datadir}/games/SBband/lib/data/delete.me
%{_datadir}/games/SBband/lib/edit/*.txt
%{_datadir}/games/SBband/lib/file/*.txt
%{_datadir}/games/SBband/lib/help/*.hlp
%{_datadir}/games/SBband/lib/help/*.txt
%{_datadir}/games/SBband/lib/info/delete.me
%{_datadir}/games/SBband/lib/pref/*.prf
%{_datadir}/games/SBband/lib/save/delete.me
%{_datadir}/games/SBband/lib/script/delete.me
%{_datadir}/games/SBband/lib/user/delete.me
%{_datadir}/games/SBband/lib/xtra/graf/8x8.bmp
%doc readme.txt readme_angband readme_eng.txt


%changelog

* Fri Jul 05 2002 Takahiro MIZUNO <tow@plum.freemail.ne.jp>
- SBband RPM 1.0.0b release 3
- Add %preun script.
- Change source extension. (tar.gz -> bz2)
- Fix Copyright.
- Fix simply %files.
- Fix %description.

* Mon Jun 17 2002 Takahiro MIZUNO <tow@plum.freemail.ne.jp>
- SBband RPM 1.0.0b release 2
- Fix setgid permission. (Mogamiさん多謝)

* Sun Jun 16 2002 Takahiro MIZUNO <tow@plum.freemail.ne.jp>
- SBband RPM 1.0.0b release 1

* Sun Jun 16 2002 Takahiro MIZUNO <tow@plum.freemail.ne.jp> 
- SBband RPM 1.0.0 release 1

