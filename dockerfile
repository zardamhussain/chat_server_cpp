FROM gcc:latest AS builder

RUN apt-get update && apt-get install -y cmake 

WORKDIR /app

COPY . .

RUN mkdir build && cd build && cmake .. && make

# FROM gcc:latest

# WORKDIR /app

# COPY --from=builder /app/build/crow_server .

EXPOSE 8000

CMD [ "./build/crow_server"]