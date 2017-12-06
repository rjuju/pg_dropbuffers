EXTENSION = pg_dropbuffers
EXTVERSION   = $(shell grep default_version $(EXTENSION).control | sed -e "s/default_version[[:space:]]*=[[:space:]]*'\([^']*\)'/\1/")
TESTS        = $(wildcard test/sql/*.sql)
REGRESS      = $(patsubst test/sql/%.sql,%,$(TESTS))
REGRESS_OPTS = --inputdir=test
DOCS         = $(wildcard README.md)

PG_CONFIG = pg_config

MODULE_big = pg_dropbuffers
OBJS = pg_dropbuffers.o

all:

release-zip: all
	git archive --format zip --prefix=pg_dropbuffers-${EXTVERSION}/ --output ./pg_dropbuffers-${EXTVERSION}.zip HEAD
	unzip ./pg_dropbuffers-$(EXTVERSION).zip
	rm ./pg_dropbuffers-$(EXTVERSION).zip
	rm ./pg_dropbuffers-$(EXTVERSION)/.gitignore
	sed -i -e "s/__VERSION__/$(EXTVERSION)/g"  ./pg_dropbuffers-$(EXTVERSION)/META.json
	zip -r ./pg_dropbuffers-$(EXTVERSION).zip ./pg_dropbuffers-$(EXTVERSION)/
	rm ./pg_dropbuffers-$(EXTVERSION) -rf


DATA = $(wildcard *--*.sql)
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
