CXX := g++
CXXFLAGS := -fPIC -O2 -Wall -Wextra -std=gnu++17
PLUGIN_NAME := libgstarducamsrc.so

GST_CFLAGS := $(shell pkg-config --cflags gstreamer-1.0 gstreamer-base-1.0 gstreamer-video-1.0)
GST_LIBS := $(shell pkg-config --libs gstreamer-1.0 gstreamer-base-1.0 gstreamer-video-1.0)

SRC := gstarducamsrc.cpp common/source_common.cpp
OBJ := $(SRC:.cpp=.o)

all: $(PLUGIN_NAME)

%.o: %.cpp gstarducamsrc.h common/frame_types.h
	$(CXX) $(CXXFLAGS) $(GST_CFLAGS) -c $< -o $@

$(PLUGIN_NAME): $(OBJ)
	$(CXX) -shared -o $@ $(OBJ) $(GST_LIBS)

clean:
	rm -f $(OBJ) $(PLUGIN_NAME)