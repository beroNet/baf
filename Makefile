
CUR_DIR=$(shell pwd)

check:
	@cd $(CUR_DIR)/install; \
	./check.sh

install: check
	@if [ "$(shell whoami)" != "root" ]; then \
		echo "You need to be root to install baf into /usr/local!"; \
		exit 1; \
	fi
	@echo -n " * Installing components for the build-environment: "
	@install -o root -g staff -m 0755 -d /usr/local/share/baf
	@cp -R $(CUR_DIR)/build/* /usr/local/share/baf/; \
	chown -R root:staff /usr/local/share/baf/*
	@echo "Done."
	@echo -n " * Installing baf: "
	@install -o root -g staff -m 0777 $(CUR_DIR)/bin/baf /usr/local/bin
	@echo "Done."

uninstall:
	@if [ "$(shell whoami)" != "root" ]; then \
		echo "You need to be root to install baf into /usr/local!"; \
		exit 1; \
	fi
	@echo -n " * Removing baf: "
	@rm -f /usr/local/bin/baf
	@echo "Done."
	@echo -n " * Removing components for the build-environment: "
	@rm -rf /usr/local/share/baf
	@echo "Done."

