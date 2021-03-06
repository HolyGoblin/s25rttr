LOCAL_PATH := ~/androidsdl/project/jni/audioSDL

include $(CLEAR_VARS)

LOCAL_MODULE := audioSDL

APP_SUBDIRS := $(patsubst $(LOCAL_PATH)/%, %, $(shell find $(LOCAL_PATH)/src -type d))

LOCAL_C_INCLUDES := $(foreach D, $(APP_SUBDIRS), $(LOCAL_PATH)/$(D)) $(LOCAL_PATH)/include $(LOCAL_PATH)/../sdl-$(SDL_VERSION)/include $(LOCAL_PATH)/../sdl_mixer/include $(LOCAL_PATH)/../application/s25rttr/driver/src $(LOCAL_PATH)/../application/s25rttr
LOCAL_CFLAGS := -O3

LOCAL_CPP_EXTENSION := .cpp

LOCAL_SRC_FILES := $(foreach F, $(APP_SUBDIRS), $(addprefix $(F)/,$(notdir $(wildcard $(LOCAL_PATH)/$(F)/*.cpp))))
LOCAL_SRC_FILES += $(foreach F, $(APP_SUBDIRS), $(addprefix $(F)/,$(notdir $(wildcard $(LOCAL_PATH)/$(F)/*.c))))

LOCAL_SHARED_LIBRARIES := sdl-$(SDL_VERSION) sdl_mixer

LOCAL_STATIC_LIBRARIES := 

LOCAL_LDLIBS := 

include $(BUILD_SHARED_LIBRARY)
