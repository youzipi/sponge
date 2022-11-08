file (GLOB LIB_SOURCES "*.cc" "util/*.cc" "tcp_helpers/*.cc")
add_library (sponge STATIC ${LIB_SOURCES} ../ref/ring_buf.cpp ../ref/ring_buf.h)
