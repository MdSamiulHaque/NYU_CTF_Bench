FROM debian:stretch
          
        RUN apt-get update && apt-get upgrade -y && dpkg --add-architecture i386 && apt-get update && apt-get install -y libc6-i386 socat file && rm -rf /var/lib/apt/lists/*

        RUN useradd -M chal

        WORKDIR /opt/chal

        COPY binary_38 .
        COPY message.txt .
        COPY binary_38.txt .

        RUN chown -R chal:chal /opt/chal &&             chmod 444 /opt/chal/message.txt &&             chmod 555 /opt/chal/binary_38 && \ 
            chmod 444 /opt/chal/binary_38.txt

        EXPOSE 5000
        USER chal
        CMD ["socat", "-T60", "TCP-LISTEN:5000,reuseaddr,fork", "EXEC:./binary_38"]
        