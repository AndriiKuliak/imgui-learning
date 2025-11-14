FROM alpine:latest

RUN apk update && apk upgrade
RUN apk add cmake git g++ libx11-dev libxrandr-dev wayland-dev glfw-dev
