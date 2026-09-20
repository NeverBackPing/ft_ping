FROM debian:12-slim

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    iputils-ping \
    build-essential \
    curl \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /ft_ping

COPY . .

CMD ["/bin/bash"]

