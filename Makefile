include config.mk

all:
	@for dir in $(BUILD_DIR); \
	do \
		make -C $$dir; \
	done

clean:
	-rm -rf core/link_obj core/dep crpc
