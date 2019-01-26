FROM gcc
RUN apt update
RUN apt install -y gnuplot
RUN apt install -y fonts-freefont-otf
RUN apt install -y fonts-freefont-ttf
COPY . /src
WORKDIR /src
CMD make
