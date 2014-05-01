# This file is generated by gyp; do not edit.

include $(CLEAR_VARS)

LOCAL_MODULE_CLASS := STATIC_LIBRARIES
LOCAL_MODULE := webkit_webkit_storage_browser_gyp
LOCAL_MODULE_SUFFIX := .a
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_TARGET_ARCH := $(TARGET_$(GYP_VAR_PREFIX)ARCH)
gyp_intermediate_dir := $(call local-intermediates-dir,,$(GYP_VAR_PREFIX))
gyp_shared_intermediate_dir := $(call intermediates-dir-for,GYP,shared,,,$(GYP_VAR_PREFIX))

# Make sure our deps are built first.
GYP_TARGET_DEPENDENCIES := \
	$(call intermediates-dir-for,GYP,third_party_WebKit_public_blink_gyp,,,$(GYP_VAR_PREFIX))/blink.stamp \
	$(call intermediates-dir-for,STATIC_LIBRARIES,skia_skia_library_gyp,,,$(GYP_VAR_PREFIX))/skia_skia_library_gyp.a

GYP_GENERATED_OUTPUTS :=

# Make sure our deps and generated files are built first.
LOCAL_ADDITIONAL_DEPENDENCIES := $(GYP_TARGET_DEPENDENCIES) $(GYP_GENERATED_OUTPUTS)

LOCAL_CPP_EXTENSION := .cc
LOCAL_GENERATED_SOURCES :=

GYP_COPIED_SOURCE_ORIGIN_DIRS :=

LOCAL_SRC_FILES := \
	webkit/browser/appcache/appcache.cc \
	webkit/browser/appcache/appcache_backend_impl.cc \
	webkit/browser/appcache/appcache_database.cc \
	webkit/browser/appcache/appcache_disk_cache.cc \
	webkit/browser/appcache/appcache_group.cc \
	webkit/browser/appcache/appcache_histograms.cc \
	webkit/browser/appcache/appcache_host.cc \
	webkit/browser/appcache/appcache_quota_client.cc \
	webkit/browser/appcache/appcache_request_handler.cc \
	webkit/browser/appcache/appcache_response.cc \
	webkit/browser/appcache/appcache_service.cc \
	webkit/browser/appcache/appcache_storage.cc \
	webkit/browser/appcache/appcache_storage_impl.cc \
	webkit/browser/appcache/appcache_working_set.cc \
	webkit/browser/appcache/appcache_update_job.cc \
	webkit/browser/appcache/appcache_url_request_job.cc \
	webkit/browser/appcache/manifest_parser.cc \
	webkit/browser/blob/blob_data_handle.cc \
	webkit/browser/blob/blob_storage_context.cc \
	webkit/browser/blob/blob_url_request_job.cc \
	webkit/browser/blob/blob_url_request_job_factory.cc \
	webkit/browser/blob/file_stream_reader.cc \
	webkit/browser/blob/local_file_stream_reader.cc \
	webkit/browser/blob/view_blob_internals_job.cc \
	webkit/browser/database/database_quota_client.cc \
	webkit/browser/database/database_tracker.cc \
	webkit/browser/database/database_util.cc \
	webkit/browser/database/databases_table.cc \
	webkit/browser/database/vfs_backend.cc \
	webkit/browser/fileapi/async_file_util_adapter.cc \
	webkit/browser/fileapi/copy_or_move_operation_delegate.cc \
	webkit/browser/fileapi/dragged_file_util.cc \
	webkit/browser/fileapi/external_mount_points.cc \
	webkit/browser/fileapi/file_system_context.cc \
	webkit/browser/fileapi/file_system_dir_url_request_job.cc \
	webkit/browser/fileapi/file_system_file_stream_reader.cc \
	webkit/browser/fileapi/file_system_file_util.cc \
	webkit/browser/fileapi/file_system_operation_context.cc \
	webkit/browser/fileapi/file_system_operation_impl.cc \
	webkit/browser/fileapi/file_system_operation_runner.cc \
	webkit/browser/fileapi/file_system_options.cc \
	webkit/browser/fileapi/file_system_quota_client.cc \
	webkit/browser/fileapi/file_system_url.cc \
	webkit/browser/fileapi/file_system_url_request_job.cc \
	webkit/browser/fileapi/file_system_url_request_job_factory.cc \
	webkit/browser/fileapi/file_system_usage_cache.cc \
	webkit/browser/fileapi/file_writer_delegate.cc \
	webkit/browser/fileapi/isolated_context.cc \
	webkit/browser/fileapi/isolated_file_system_backend.cc \
	webkit/browser/fileapi/local_file_stream_writer.cc \
	webkit/browser/fileapi/local_file_util.cc \
	webkit/browser/fileapi/mount_points.cc \
	webkit/browser/fileapi/native_file_util.cc \
	webkit/browser/fileapi/obfuscated_file_util.cc \
	webkit/browser/fileapi/plugin_private_file_system_backend.cc \
	webkit/browser/fileapi/quota/open_file_handle.cc \
	webkit/browser/fileapi/quota/open_file_handle_context.cc \
	webkit/browser/fileapi/quota/quota_backend_impl.cc \
	webkit/browser/fileapi/quota/quota_reservation.cc \
	webkit/browser/fileapi/quota/quota_reservation_buffer.cc \
	webkit/browser/fileapi/quota/quota_reservation_manager.cc \
	webkit/browser/fileapi/recursive_operation_delegate.cc \
	webkit/browser/fileapi/remove_operation_delegate.cc \
	webkit/browser/fileapi/sandbox_directory_database.cc \
	webkit/browser/fileapi/sandbox_file_stream_writer.cc \
	webkit/browser/fileapi/sandbox_file_system_backend.cc \
	webkit/browser/fileapi/sandbox_file_system_backend_delegate.cc \
	webkit/browser/fileapi/sandbox_isolated_origin_database.cc \
	webkit/browser/fileapi/sandbox_origin_database.cc \
	webkit/browser/fileapi/sandbox_origin_database_interface.cc \
	webkit/browser/fileapi/sandbox_prioritized_origin_database.cc \
	webkit/browser/fileapi/sandbox_quota_observer.cc \
	webkit/browser/fileapi/timed_task_helper.cc \
	webkit/browser/fileapi/transient_file_util.cc \
	webkit/browser/quota/quota_database.cc \
	webkit/browser/quota/quota_manager.cc \
	webkit/browser/quota/quota_manager_proxy.cc \
	webkit/browser/quota/quota_task.cc \
	webkit/browser/quota/quota_temporary_storage_evictor.cc \
	webkit/browser/quota/special_storage_policy.cc \
	webkit/browser/quota/storage_monitor.cc \
	webkit/browser/quota/storage_observer.cc \
	webkit/browser/quota/usage_tracker.cc


# Flags passed to both C and C++ files.
MY_CFLAGS_Debug := \
	--param=ssp-buffer-size=4 \
	-Werror \
	-fno-exceptions \
	-fno-strict-aliasing \
	-Wall \
	-Wno-unused-parameter \
	-Wno-missing-field-initializers \
	-fvisibility=hidden \
	-pipe \
	-fPIC \
	-Wno-unused-local-typedefs \
	-ffunction-sections \
	-funwind-tables \
	-g \
	-fno-short-enums \
	-finline-limit=64 \
	-Wa,--noexecstack \
	-U_FORTIFY_SOURCE \
	-Wno-extra \
	-Wno-ignored-qualifiers \
	-Wno-type-limits \
	-Wno-unused-but-set-variable \
	-Os \
	-g \
	-fomit-frame-pointer \
	-fdata-sections \
	-ffunction-sections \
	-funwind-tables

MY_DEFS_Debug := \
	'-DV8_DEPRECATION_WARNINGS' \
	'-DBLINK_SCALE_FILTERS_AT_RECORD_TIME' \
	'-D_FILE_OFFSET_BITS=64' \
	'-DNO_TCMALLOC' \
	'-DDISABLE_NACL' \
	'-DCHROMIUM_BUILD' \
	'-DUSE_LIBJPEG_TURBO=1' \
	'-DENABLE_WEBRTC=1' \
	'-DUSE_PROPRIETARY_CODECS' \
	'-DENABLE_CONFIGURATION_POLICY' \
	'-DDISCARDABLE_MEMORY_ALWAYS_SUPPORTED_NATIVELY' \
	'-DSYSTEM_NATIVELY_SIGNALS_MEMORY_PRESSURE' \
	'-DENABLE_EGLIMAGE=1' \
	'-DCLD_VERSION=1' \
	'-DENABLE_PRINTING=1' \
	'-DENABLE_MANAGED_USERS=1' \
	'-DWEBKIT_STORAGE_BROWSER_IMPLEMENTATION' \
	'-DAPPCACHE_USE_SIMPLE_CACHE' \
	'-DPOSIX_AVOID_MMAP' \
	'-DSK_ENABLE_INST_COUNT=0' \
	'-DSK_SUPPORT_GPU=1' \
	'-DGR_GL_CUSTOM_SETUP_HEADER="GrGLConfig_chrome.h"' \
	'-DSK_ENABLE_LEGACY_API_ALIASING=1' \
	'-DSK_ATTR_DEPRECATED=SK_NOTHING_ARG1' \
	'-DGR_GL_IGNORE_ES3_MSAA=0' \
	'-DSK_WILL_NEVER_DRAW_PERSPECTIVE_TEXT' \
	'-DSK_SUPPORT_LEGACY_PUBLICEFFECTCONSTRUCTORS=1' \
	'-DSK_SUPPORT_LEGACY_GETTOPDEVICE' \
	'-DSK_SUPPORT_LEGACY_N32_NAME' \
	'-DSK_SUPPORT_LEGACY_PROCXFERMODE' \
	'-DSK_SUPPORT_LEGACY_DERIVED_PICTURE_CLASSES' \
	'-DSK_SUPPORT_LEGACY_PICTURE_HEADERS' \
	'-DSK_SUPPORT_LEGACY_PICTURE_CAN_RECORD' \
	'-DSK_SUPPORT_DEPRECATED_RECORD_FLAGS' \
	'-DSK_SUPPORT_LEGACY_BLURMASKFILTER_STYLE' \
	'-DSK_SUPPORT_LEGACY_GETTOTALCLIP' \
	'-DSK_BUILD_FOR_ANDROID' \
	'-DSK_USE_POSIX_THREADS' \
	'-DSK_DEFERRED_CANVAS_USES_FACTORIES=1' \
	'-DU_USING_ICU_NAMESPACE=0' \
	'-DCHROME_PNG_WRITE_SUPPORT' \
	'-DPNG_USER_CONFIG' \
	'-DCHROME_PNG_READ_PACK_SUPPORT' \
	'-DUSE_SYSTEM_LIBJPEG' \
	'-DUSE_OPENSSL=1' \
	'-DUSE_OPENSSL_CERTS=1' \
	'-D__STDC_CONSTANT_MACROS' \
	'-D__STDC_FORMAT_MACROS' \
	'-DANDROID' \
	'-D__GNU_SOURCE=1' \
	'-DUSE_STLPORT=1' \
	'-D_STLP_USE_PTR_SPECIALIZATIONS=1' \
	'-DCHROME_BUILD_ID=""' \
	'-DDYNAMIC_ANNOTATIONS_ENABLED=1' \
	'-DWTF_USE_DYNAMIC_ANNOTATIONS=1' \
	'-D_DEBUG'


# Include paths placed before CFLAGS/CPPFLAGS
LOCAL_C_INCLUDES_Debug := \
	$(gyp_shared_intermediate_dir)/shim_headers/icuuc/target \
	$(gyp_shared_intermediate_dir)/shim_headers/icui18n/target \
	$(gyp_shared_intermediate_dir)/shim_headers/ashmem/target \
	$(LOCAL_PATH) \
	$(LOCAL_PATH)/skia/config \
	$(LOCAL_PATH)/third_party/WebKit/Source \
	$(LOCAL_PATH)/third_party/khronos \
	$(LOCAL_PATH)/gpu \
	$(LOCAL_PATH)/third_party/leveldatabase/src/include \
	$(LOCAL_PATH)/third_party/leveldatabase/src \
	$(LOCAL_PATH)/third_party/leveldatabase \
	$(LOCAL_PATH)/third_party/sqlite \
	$(LOCAL_PATH)/third_party/WebKit \
	$(LOCAL_PATH)/third_party/WebKit \
	$(LOCAL_PATH)/third_party/skia/src/core \
	$(LOCAL_PATH)/third_party/skia/include/core \
	$(LOCAL_PATH)/third_party/skia/include/effects \
	$(LOCAL_PATH)/third_party/skia/include/pdf \
	$(LOCAL_PATH)/third_party/skia/include/gpu \
	$(LOCAL_PATH)/third_party/skia/include/lazy \
	$(LOCAL_PATH)/third_party/skia/include/pathops \
	$(LOCAL_PATH)/third_party/skia/include/pipe \
	$(LOCAL_PATH)/third_party/skia/include/ports \
	$(LOCAL_PATH)/third_party/skia/include/utils \
	$(LOCAL_PATH)/skia/ext \
	$(PWD)/external/icu4c/common \
	$(PWD)/external/icu4c/i18n \
	$(LOCAL_PATH)/third_party/npapi \
	$(LOCAL_PATH)/third_party/npapi/bindings \
	$(LOCAL_PATH)/v8/include \
	$(LOCAL_PATH)/third_party/libpng \
	$(LOCAL_PATH)/third_party/zlib \
	$(LOCAL_PATH)/third_party/libwebp \
	$(LOCAL_PATH)/third_party/ots/include \
	$(LOCAL_PATH)/third_party/qcms/src \
	$(LOCAL_PATH)/third_party/iccjpeg \
	$(PWD)/external/jpeg \
	$(PWD)/frameworks/wilhelm/include \
	$(PWD)/bionic \
	$(PWD)/external/stlport/stlport


# Flags passed to only C++ (and not C) files.
LOCAL_CPPFLAGS_Debug := \
	-fno-rtti \
	-fno-threadsafe-statics \
	-fvisibility-inlines-hidden \
	-Wsign-compare \
	-Wno-non-virtual-dtor \
	-Wno-sign-promo


# Flags passed to both C and C++ files.
MY_CFLAGS_Release := \
	--param=ssp-buffer-size=4 \
	-Werror \
	-fno-exceptions \
	-fno-strict-aliasing \
	-Wall \
	-Wno-unused-parameter \
	-Wno-missing-field-initializers \
	-fvisibility=hidden \
	-pipe \
	-fPIC \
	-Wno-unused-local-typedefs \
	-ffunction-sections \
	-funwind-tables \
	-g \
	-fno-short-enums \
	-finline-limit=64 \
	-Wa,--noexecstack \
	-U_FORTIFY_SOURCE \
	-Wno-extra \
	-Wno-ignored-qualifiers \
	-Wno-type-limits \
	-Wno-unused-but-set-variable \
	-Os \
	-fno-ident \
	-fdata-sections \
	-ffunction-sections \
	-fomit-frame-pointer \
	-funwind-tables

MY_DEFS_Release := \
	'-DV8_DEPRECATION_WARNINGS' \
	'-DBLINK_SCALE_FILTERS_AT_RECORD_TIME' \
	'-D_FILE_OFFSET_BITS=64' \
	'-DNO_TCMALLOC' \
	'-DDISABLE_NACL' \
	'-DCHROMIUM_BUILD' \
	'-DUSE_LIBJPEG_TURBO=1' \
	'-DENABLE_WEBRTC=1' \
	'-DUSE_PROPRIETARY_CODECS' \
	'-DENABLE_CONFIGURATION_POLICY' \
	'-DDISCARDABLE_MEMORY_ALWAYS_SUPPORTED_NATIVELY' \
	'-DSYSTEM_NATIVELY_SIGNALS_MEMORY_PRESSURE' \
	'-DENABLE_EGLIMAGE=1' \
	'-DCLD_VERSION=1' \
	'-DENABLE_PRINTING=1' \
	'-DENABLE_MANAGED_USERS=1' \
	'-DWEBKIT_STORAGE_BROWSER_IMPLEMENTATION' \
	'-DAPPCACHE_USE_SIMPLE_CACHE' \
	'-DPOSIX_AVOID_MMAP' \
	'-DSK_ENABLE_INST_COUNT=0' \
	'-DSK_SUPPORT_GPU=1' \
	'-DGR_GL_CUSTOM_SETUP_HEADER="GrGLConfig_chrome.h"' \
	'-DSK_ENABLE_LEGACY_API_ALIASING=1' \
	'-DSK_ATTR_DEPRECATED=SK_NOTHING_ARG1' \
	'-DGR_GL_IGNORE_ES3_MSAA=0' \
	'-DSK_WILL_NEVER_DRAW_PERSPECTIVE_TEXT' \
	'-DSK_SUPPORT_LEGACY_PUBLICEFFECTCONSTRUCTORS=1' \
	'-DSK_SUPPORT_LEGACY_GETTOPDEVICE' \
	'-DSK_SUPPORT_LEGACY_N32_NAME' \
	'-DSK_SUPPORT_LEGACY_PROCXFERMODE' \
	'-DSK_SUPPORT_LEGACY_DERIVED_PICTURE_CLASSES' \
	'-DSK_SUPPORT_LEGACY_PICTURE_HEADERS' \
	'-DSK_SUPPORT_LEGACY_PICTURE_CAN_RECORD' \
	'-DSK_SUPPORT_DEPRECATED_RECORD_FLAGS' \
	'-DSK_SUPPORT_LEGACY_BLURMASKFILTER_STYLE' \
	'-DSK_SUPPORT_LEGACY_GETTOTALCLIP' \
	'-DSK_BUILD_FOR_ANDROID' \
	'-DSK_USE_POSIX_THREADS' \
	'-DSK_DEFERRED_CANVAS_USES_FACTORIES=1' \
	'-DU_USING_ICU_NAMESPACE=0' \
	'-DCHROME_PNG_WRITE_SUPPORT' \
	'-DPNG_USER_CONFIG' \
	'-DCHROME_PNG_READ_PACK_SUPPORT' \
	'-DUSE_SYSTEM_LIBJPEG' \
	'-DUSE_OPENSSL=1' \
	'-DUSE_OPENSSL_CERTS=1' \
	'-D__STDC_CONSTANT_MACROS' \
	'-D__STDC_FORMAT_MACROS' \
	'-DANDROID' \
	'-D__GNU_SOURCE=1' \
	'-DUSE_STLPORT=1' \
	'-D_STLP_USE_PTR_SPECIALIZATIONS=1' \
	'-DCHROME_BUILD_ID=""' \
	'-DNDEBUG' \
	'-DNVALGRIND' \
	'-DDYNAMIC_ANNOTATIONS_ENABLED=0' \
	'-D_FORTIFY_SOURCE=2'


# Include paths placed before CFLAGS/CPPFLAGS
LOCAL_C_INCLUDES_Release := \
	$(gyp_shared_intermediate_dir)/shim_headers/icuuc/target \
	$(gyp_shared_intermediate_dir)/shim_headers/icui18n/target \
	$(gyp_shared_intermediate_dir)/shim_headers/ashmem/target \
	$(LOCAL_PATH) \
	$(LOCAL_PATH)/skia/config \
	$(LOCAL_PATH)/third_party/WebKit/Source \
	$(LOCAL_PATH)/third_party/khronos \
	$(LOCAL_PATH)/gpu \
	$(LOCAL_PATH)/third_party/leveldatabase/src/include \
	$(LOCAL_PATH)/third_party/leveldatabase/src \
	$(LOCAL_PATH)/third_party/leveldatabase \
	$(LOCAL_PATH)/third_party/sqlite \
	$(LOCAL_PATH)/third_party/WebKit \
	$(LOCAL_PATH)/third_party/WebKit \
	$(LOCAL_PATH)/third_party/skia/src/core \
	$(LOCAL_PATH)/third_party/skia/include/core \
	$(LOCAL_PATH)/third_party/skia/include/effects \
	$(LOCAL_PATH)/third_party/skia/include/pdf \
	$(LOCAL_PATH)/third_party/skia/include/gpu \
	$(LOCAL_PATH)/third_party/skia/include/lazy \
	$(LOCAL_PATH)/third_party/skia/include/pathops \
	$(LOCAL_PATH)/third_party/skia/include/pipe \
	$(LOCAL_PATH)/third_party/skia/include/ports \
	$(LOCAL_PATH)/third_party/skia/include/utils \
	$(LOCAL_PATH)/skia/ext \
	$(PWD)/external/icu4c/common \
	$(PWD)/external/icu4c/i18n \
	$(LOCAL_PATH)/third_party/npapi \
	$(LOCAL_PATH)/third_party/npapi/bindings \
	$(LOCAL_PATH)/v8/include \
	$(LOCAL_PATH)/third_party/libpng \
	$(LOCAL_PATH)/third_party/zlib \
	$(LOCAL_PATH)/third_party/libwebp \
	$(LOCAL_PATH)/third_party/ots/include \
	$(LOCAL_PATH)/third_party/qcms/src \
	$(LOCAL_PATH)/third_party/iccjpeg \
	$(PWD)/external/jpeg \
	$(PWD)/frameworks/wilhelm/include \
	$(PWD)/bionic \
	$(PWD)/external/stlport/stlport


# Flags passed to only C++ (and not C) files.
LOCAL_CPPFLAGS_Release := \
	-fno-rtti \
	-fno-threadsafe-statics \
	-fvisibility-inlines-hidden \
	-Wsign-compare \
	-Wno-non-virtual-dtor \
	-Wno-sign-promo


LOCAL_CFLAGS := $(MY_CFLAGS_$(GYP_CONFIGURATION)) $(MY_DEFS_$(GYP_CONFIGURATION))
LOCAL_C_INCLUDES := $(GYP_COPIED_SOURCE_ORIGIN_DIRS) $(LOCAL_C_INCLUDES_$(GYP_CONFIGURATION))
LOCAL_CPPFLAGS := $(LOCAL_CPPFLAGS_$(GYP_CONFIGURATION))
LOCAL_ASFLAGS := $(LOCAL_CFLAGS)
### Rules for final target.

LOCAL_LDFLAGS_Debug := \
	-Wl,-z,now \
	-Wl,-z,relro \
	-Wl,--fatal-warnings \
	-Wl,-z,noexecstack \
	-fPIC \
	-nostdlib \
	-Wl,--no-undefined \
	-Wl,--exclude-libs=ALL \
	-Wl,--warn-shared-textrel \
	-Wl,-O1 \
	-Wl,--as-needed


LOCAL_LDFLAGS_Release := \
	-Wl,-z,now \
	-Wl,-z,relro \
	-Wl,--fatal-warnings \
	-Wl,-z,noexecstack \
	-fPIC \
	-nostdlib \
	-Wl,--no-undefined \
	-Wl,--exclude-libs=ALL \
	-Wl,-O1 \
	-Wl,--as-needed \
	-Wl,--gc-sections \
	-Wl,--warn-shared-textrel


LOCAL_LDFLAGS := $(LOCAL_LDFLAGS_$(GYP_CONFIGURATION))

LOCAL_STATIC_LIBRARIES := \
	skia_skia_library_gyp

# Enable grouping to fix circular references
LOCAL_GROUP_STATIC_LIBRARIES := true

LOCAL_SHARED_LIBRARIES := \
	libstlport \
	libdl

# Add target alias to "gyp_all_modules" target.
.PHONY: gyp_all_modules
gyp_all_modules: webkit_webkit_storage_browser_gyp

# Alias gyp target name.
.PHONY: webkit_storage_browser
webkit_storage_browser: webkit_webkit_storage_browser_gyp

include $(BUILD_STATIC_LIBRARY)
