FROM gcc:13

# Create non-root user
RUN groupadd --gid 1001 osuser
RUN useradd -m -s /bin/bash --uid 1001 --gid osuser osuser

# Allow user to sudo
RUN apt-get update
RUN apt install -y sudo
RUN echo osuser ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/osuser
