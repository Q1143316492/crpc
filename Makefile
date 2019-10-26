include config.mk

all: 	
	@echo "[$(BUILD_DIR)]"
	@for dir in $(BUILD_DIR); \
	do \
		make -C $$dir; \
	done

clean:
	-rm -rf core/link_obj core/dep crpc
