###############################################################################
#
# Copyright (c) 2016-2017, NVIDIA CORPORATION. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#  * Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#  * Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#  * Neither the name of NVIDIA CORPORATION nor the names of its
#    contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
# EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
# PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
# OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
###############################################################################

include ../../Rules.mk

LIB = libopencv_consumer.so

SRCS := \
	opencv_consumer.cpp \
	Classifier.cpp

OBJS := $(SRCS:.cpp=.o)

# The following trick tries to get the device account from
# a host system when doing cross-compilation, as the tip $(HOME)
# is not working any more in this case.
ifneq ($(wildcard $(TARGET_ROOTFS)/home/nvidia/caffe),)
USER := nvidia
else
USER := ubuntu
endif

CAFFE_DIR := $(TARGET_ROOTFS)/home/$(USER)/caffe

CPPFLAGS += -fPIC -O2 -shared \
	-I"$(CAFFE_DIR)/include" \
	-I"$(CAFFE_DIR)/build/src"

LDFLAGS += \
	-lcaffe \
	-lopencv_highgui -lopencv_imgproc -lopencv_core \
	-L"$(CAFFE_DIR)/build/lib"

.PHONY: all clean

all: $(LIB)

%.o: %.cpp
	@echo "Compiling: $<"
	$(CPP) -c $(CPPFLAGS) $<

$(LIB): $(OBJS)
	@echo "Linking: $@"
	$(CPP) -o $(LIB) $(OBJS) $(CPPFLAGS) $(LDFLAGS)

clean:
	$(AT)rm -f $(OBJS) $(LIB)
