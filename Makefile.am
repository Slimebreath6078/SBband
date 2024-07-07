## Makefile.am -- Process this file with automake to process Makefile.in

AUTOMAKE_OPTIONS = foreign

visual_studio_files = \
	VisualStudio/SBband.sln \
	VisualStudio/SBband/SBband.vcxproj \
	VisualStudio/SBband/SBband.vcxproj.filters \
	VisualStudio/SBband/packages.config

schema_files = \
	schema/ArtifactDefinitions.schema.json \
	schema/BaseitemDefinitions.schema.json \
	schema/ClassMagicDefinitions.schema.json \
	schema/MonraceDefinitions.schema.json \
	schema/SpellDefinitions.schema.json

EXTRA_DIST = \
	autopick.txt \
	autopick_eng.txt \
	bootstrap \
	readme.md \
	readme_angband \
	readme-eng.md \
	THIRD-PARTY-NOTICES.txt \
	hengband.spec \
	$(visual_studio_files) \
	$(schema_files)

SUBDIRS = src lib
