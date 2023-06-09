#
# Place the files
#
#   poky-glibc-*.sh
#   libturtlebot3-*.tar.bz2
#
# in the same folder as this file. They can be downloaded from
#
#   https://ftp.k-team.com/Turtlebot3/software/Gumstix%20COM%20Y/light_tools/
#   https://ftp.k-team.com/Turtlebot3/software/Gumstix%20COM%20Y/library/
#
# Then build the image with
#
# docker build -t nestlab/turtlebot3 .
#
# Run the image with
#
# docker run -it bash -l
#
# If you want to share local folders with the virtual machine, use this command:
#
# docker run -it -v /host/directory:/container/directory nestlab/turtlebot3 bash -l
#
# where /host/directory is a directory in your machine, and /container/directory is
# a directory in the container.
#

FROM ubuntu:16.04
ENV LAST_MODIFIED "2021-07-22:19.13"

# Set the working directory
WORKDIR /work

# Copy the contents of the current directory in /work
COPY poky-glibc-*.sh .
COPY libturtlebot3-*.tar.bz2 .

# Install needed packages
RUN apt-get update && \
	apt-get -y install \
	build-essential \
	bzip2 \
	cmake \
	cmake-curses-gui \
	dnsutils \
	emacs-nox \
	git \
	net-tools \
	python

# Install light toolchain
RUN bash poky-glibc-i686-turtlebot34-image-cortexa8hf-vfp-neon-toolchain-1.8.sh && \
  ( echo "source /opt/poky/1.8/environment-setup-cortexa8hf-vfp-neon-poky-linux-gnueabi" >> /root/.bashrc )

# Install libturtlebot3
ENV ARGOS3tb3 /opt/poky/1.8/sysroots/cortexa8hf-vfp-neon-poky-linux-gnueabi/usr
RUN tar xjf libturtlebot3-*.tar.bz2 && \
  rm -f libturtlebot3-*.tar.bz2 && \
  cd libturtlebot3-* && \
  make && \
  mkdir -p $ARGOS3tb3 && \
  cp -a build*/* $ARGOS3tb3

# Get ARGoS and Buzz code
RUN git clone https://github.com/ilpincy/argos3
RUN git clone https://github.com/NESTLab/Buzz.git buzz
RUN git clone https://github.com/ilpincy/argos3-turtlebot3

# Make sure the toolchain configuration is in the environment
SHELL ["/bin/bash", "-c"]
ENV BASH_ENV /opt/poky/1.8/environment-setup-cortexa8hf-vfp-neon-poky-linux-gnueabi

# Compile and install ARGoS
RUN cd argos3 && \
  mkdir build_turtlebot3 && \
  cd build_turtlebot3 && \
  cmake -DARGOS_BUILD_FOR=tb3 ../src -DCMAKE_TOOLCHAIN_FILE=../../argos3-turtlebot3/src/cmake/TargetTurtlebot3.cmake -DCMAKE_INSTALL_PREFIX=$ARGOS3tb3 && \
  make install

# Compile and install Buzz
RUN cd buzz && \
  mkdir build_turtlebot3 && \
  cd build_turtlebot3 && \
  cmake -DARGOS_BUILD_FOR=tb3 -DCMAKE_TOOLCHAIN_FILE=../../argos3-turtlebot3/src/cmake/TargetTurtlebot3.cmake -DCMAKE_INSTALL_PREFIX=$ARGOS3tb3 ../src && \
  make install

# Compile and install ARGoS-Turtlebot3
RUN cd argos3-turtlebot3 && \
  mkdir build_turtlebot3 && \
  cd build_turtlebot3 && \
  cmake -DARGOS_BUILD_FOR=tb3 -DCMAKE_TOOLCHAIN_FILE=../src/cmake/TargetTurtlebot3.cmake -DCMAKE_INSTALL_PREFIX=$ARGOS3tb3 -DTURTLEBOT3_LIBS=$ARGOS3tb3 ../src && \
  make install

# # Cleanup
# RUN rm -rf /work/* && \
#   apt-get autoremove
