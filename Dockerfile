# This Dockerfile is used to build an image for work_01-tad-lista.

# Build the image
# sudo docker build -t work_01-tad-lista .

# Allow root access to the X server
# sudo xhost +local:root

# Run the container with interactive mode and remove it after it exits
# sudo docker run -it --rm --env DISPLAY=$DISPLAY --env XAUTHORITY=$XAUTHORITY --volume /tmp/.X11-unix:/tmp/.X11-unix work_01-tad-lista

# Revoke root access to the X server
# sudo xhost -local:root


FROM ubuntu:24.04

# Install dependencies
RUN apt-get update && apt-get install -y
RUN apt-get -y install meson=0.56.2-0ubuntu1
RUN apt-get -y install libgtk-3-dev=3.24.24-4ubuntu1
RUN apt-get -y install ninja-build=1.10.0-1

# Copy the source code
COPY . /app

# Set the working directory
WORKDIR /app

# Build the application
RUN meson builddir
RUN ninja -C builddir

# Run the application
CMD ["./builddir/work_01-TAD-Lista"]

