export BUILD_ROOT = $(shell pwd)
export INCLUDE_PATH = $(BUILD_ROOT)/_include
export DEBUG = true

BUILD_DIR = $(BUILD_ROOT)/tools/ \
			$(BUILD_ROOT)/log/ \
			$(BUILD_ROOT)/conf/ \
			$(BUILD_ROOT)/app/ \
