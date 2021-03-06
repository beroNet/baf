
CUR_DIR		:= $(shell pwd)
USER		:= $(shell whoami)
INST_LOC_FIL	:= $(CUR_DIR)/INSTALL.LOCATION

ifndef PREFIX
	PREFIX = /usr/local
endif

SED_PREFIX	:= $(shell echo $(PREFIX) | sed -e 's/\([[\/.*]\|\]\)/\\&/g')

ifeq ($(USER),root)
	GROUP	:= staff
else
	GROUP	:= $(USER)
endif

check:
	@cd $(CUR_DIR)/install; \
	./check.sh

install: check
	@if [ -z "$(shell echo $(PREFIX) | grep $(USER))" ] && [ "$(USER)" != "root" ]; then \
		echo "You need to be root to install baf into $(PREFIX)!"; \
		exit 1; \
	fi
	@echo "$(PREFIX)" > $(INST_LOC_FIL)
	@echo -n " * Installing components for the build-environment: "
	@install -o $(USER) -g $(GROUP) -m 0755 -d $(PREFIX)/share/baf
	@cp -R $(CUR_DIR)/build/* $(PREFIX)/share/baf/; \
	chown -R $(USER):$(GROUP) $(PREFIX)/share/baf/*
	@echo "Done."
	@echo -n " * Installing baf: "
	@install -o $(USER) -g $(GROUP) -m 0755 -d $(PREFIX)/bin
	@install -o $(USER) -g $(GROUP) -m 0644 $(CUR_DIR)/bin/baf_template $(PREFIX)/bin
	@sed 's/BAF_TOOLCHAIN_BASEPATH/$(SED_PREFIX)/;' $(PREFIX)/bin/baf_template > $(PREFIX)/bin/baf
	@rm -f $(PREFIX)/bin/baf_template
	@chown $(USER):$(GROUP) $(PREFIX)/bin/baf
	@chmod 0755 $(PREFIX)/bin/baf
	@echo "Done."

uninstall:
	@INSTLOC=`cat $(INST_LOC_FIL)`; \
	if [ -z "`echo $$INSTLOC | grep $(USER)`" ] && [ "$(USER)" != "root" ]; then \
		echo "You need to be root to uninstall baf from $$INSTLOC!"; \
		exit 1; \
	fi; \
	echo -n " * Removing baf: "; \
	rm -f $$INSTLOC/bin/baf; \
	echo "Done."; \
	echo -n " * Removing components for the build-environment: "; \
	rm -rf $$INSTLOC/share/baf; \
	echo "Done."
	@rm -f $(INST_LOC_FIL)

