# Use Debian slim as the base
FROM debian:bullseye-slim

# avoid interactive prompts
ENV DEBIAN_FRONTEND=noninteractive

# install clang, make, git, etc.
RUN apt-get update \
 && apt-get install -y --no-install-recommends \
      clang \
      build-essential \
      make \
      git \
      sudo \
      ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# add non-root user 'vscode'
ARG USERNAME=vscode
ARG USER_UID=1000
ARG USER_GID=$USER_UID

RUN groupadd --gid $USER_GID $USERNAME \
 && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME -s /bin/bash \
 && echo "$USERNAME ALL=(ALL) NOPASSWD:ALL" > /etc/sudoers.d/$USERNAME \
 && chmod 0440 /etc/sudoers.d/$USERNAME

# set working dir
WORKDIR /workspace

# switch to the vscode user
USER $USERNAME
