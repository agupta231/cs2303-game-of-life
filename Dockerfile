FROM ubuntu:18.04

RUN apt-get update && \
		apt-get install -y gcc \
											 g++ \
											 build-essential \
											 gdb && \
		apt-get clean && \
		apt-get autoremove && \
		rm -rf /var/lib/apt/lists*

WORKDIR /program
CMD gcc -Wall life.c && \
	  ./a.out
