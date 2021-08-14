## Makefile.am -- Process this file with automake to process Makefile.in

AUTOMAKE_OPTIONS = foreign

visual_studio_files = \
	SBband/SBband.sln \
	SBband/SBband/curl/include/curl/curl.h \
	SBband/SBband/curl/include/curl/curlver.h \
	SBband/SBband/curl/include/curl/easy.h \
	SBband/SBband/curl/include/curl/mprintf.h \
	SBband/SBband/curl/include/curl/multi.h \
	SBband/SBband/curl/include/curl/options.h \
	SBband/SBband/curl/include/curl/stdcheaders.h \
	SBband/SBband/curl/include/curl/system.h \
	SBband/SBband/curl/include/curl/typecheck-gcc.h \
	SBband/SBband/curl/include/curl/urlapi.h \
	SBband/SBband/SBband.vcxproj \
	SBband/SBband/SBband.vcxproj.filters \
	SBband/SBband/packages.config

EXTRA_DIST = \
	autopick.txt \
	autopick_eng.txt \
	bootstrap \
	readme.md \
	readme_angband \
	readme-eng.md \
	SBband.spec \
	$(visual_studio_files)

SUBDIRS = src lib

# Handle some paths in SBband/SBband that have spaces in them and would
# be mishandled by make/automake.
dist-hook:
	(cd $(srcdir)/SBband/SBband/curl && tar -cf - "x86 Debug" "x86 Release" ) | (cd $(distdir)/SBband/SBband/curl && tar -xf -)
