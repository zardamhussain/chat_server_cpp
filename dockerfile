FROM gcc:latest AS builder

RUN apt-get update && apt-get install -y \
    git \
    wget \
    cmake \ 
    wget


WORKDIR /app

RUN mkdir extra
WORKDIR /app/extra

RUN wget https://github.com/CrowCpp/Crow/releases/download/v1.0%2B1/crow-v1.0+1.tar.gz && \
    mkdir crow && cd crow && tar xvfz ../crow-v1.0+1.tar.gz && rm ../crow-v1.0+1.tar.gz

WORKDIR /app/extra
RUN wget https://archives.boost.io/release/1.86.0/source/boost_1_86_0.tar.gz && \
    tar xvfz boost_1_86_0.tar.gz && rm boost_1_86_0.tar.gz

WORKDIR /app

COPY . .

RUN mkdir build && cd build && cmake .. && make



FROM gcc:latest

WORKDIR /app

COPY --from=builder /app/build/crow_server .

EXPOSE 8000

CMD [ "./crow_server"]