FROM alpine:latest

RUN apk update && apk upgrade
RUN apk add cmake git g++
